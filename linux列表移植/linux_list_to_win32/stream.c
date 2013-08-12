#include "stdio.h"
#include "string.h"
#include "types.h"
#include "errors.h"
#include "list.h"
#include "stream.h"

//MEM_DEBUG_SUPPORT
#define STRM_MALLOC_NODBG(strmhdl, size)  (((struct stream*)(strmhdl))->mem_ops.malloc(size))
#define STRM_FREE_NODBG(strmhdl, ptr)     (((struct stream*)(strmhdl))->mem_ops.free(ptr))

#define STRM_PRINT   printf
#define STRM_DEBUG   printf

#define DBG_LIB "\t\t\t<lib>"

#if 0//MEM_DEBUG_SUPPORT
#define STRM_MALLOC_DBG(strmhdl, size)  (((struct stream*)(strmhdl))->mem_ops.malloc_dbg(size, __FILE__, __LINE__))
#define STRM_FREE_DBG(strmhdl, ptr)     (((struct stream*)(strmhdl))->mem_ops.free_dbg(ptr, __FILE__, __LINE__))
#else
#define STRM_MALLOC_DBG(strmhdl, size)  STRM_MALLOC_NODBG(strmhdl, size)
#define STRM_FREE_DBG(strmhdl, ptr)     STRM_FREE_NODBG(strmhdl, ptr)
#endif
#if 0//MEM_DEBUG_SUPPORT
#define STRM_MALLOC(strmhdl, size)  STRM_MALLOC_DBG(strmhdl, size)
#define STRM_FREE(strmhdl, ptr)     STRM_FREE_DBG(strmhdl, ptr) 
#else
#define STRM_MALLOC(strmhdl, size)  STRM_MALLOC_NODBG(strmhdl, size)
#define STRM_FREE(strmhdl, ptr)     STRM_FREE_NODBG(strmhdl, ptr) 
#endif



struct stream_node {
	struct list_head list;	/**< list list		*/	
	uint16_t  idx;
	uint16_t  size;
	void * ptr;
};

struct stream {
	struct list_head header;	/**< list header 	*/
	struct malloc_ops mem_ops;
	struct stream_node *node_pool;
	struct stream_node *(*new_node)(struct stream *strm);
	void (*delete_node)(struct stream *strm, struct stream_node *node);
	uint16_t max_num;
	uint16_t num;
	uint16_t idx;
	uint16_t type;
};


static struct stream_node *new_node_static(struct stream *strm)
{
	int i =0;
	
	if (strm)
 	STRM_PRINT("\t\t"DBG_LIB"snew %d\n", strm->num);
	for (; i<strm->max_num; i++)
	{
		if (list_is_del(&strm->node_pool[i].list)) {
			return &strm->node_pool[i];
		}
	}
	//return (struct stream_node*)malloc(sizeof(struct stream));
	return NULL;
}

static void free_node_static(struct stream *strm, struct stream_node *node)
{
	if (node)
 	STRM_PRINT("\t\t"DBG_LIB"sfree %d\n", node->idx);
	//free(node);
}


static struct stream_node *new_node_dynamic(struct stream *strm)
{
	//if (strm)
 	//STRM_PRINT("\t\t"DBG_LIB"dnew %d\n", strm->num);
	return (struct stream_node*)malloc(sizeof(struct stream));
}

static void free_node_dynamic(struct stream *strm, struct stream_node *node)
{
	//if (node)
 	//STRM_PRINT("\t\t"DBG_LIB"dfree %d\n", node->idx);

	free(node);
}

void* stream_open(uint16_t type, struct stream_param *param)
{
	struct stream *strm;

	if (NULL == param) {
		return NULL;
	}

	if ((NULL == param->mem_ops.malloc) || (NULL == param->mem_ops.free)) {
		return NULL;
	}
	strm = (struct stream *)param->mem_ops.malloc(sizeof(struct stream));

	if (NULL == strm) {
		return NULL;
	}
	
	memset(strm, 0, sizeof(struct stream));
	
	memcpy(&strm->mem_ops, &param->mem_ops, sizeof(struct malloc_ops)); 
	INIT_LIST_HEAD(&strm->header);
	strm->max_num = param->max_num;
	strm->type = type;
	
	STRM_PRINT(DBG_LIB "strm: hdl=%x, type=%x, num=%d/%d\n", 
		strm,
		strm->type,
		strm->num,
		strm->max_num);
	
	if (STRM_TYPE_DYNAMIC & strm->type) {
		strm->new_node  = new_node_dynamic;
		strm->delete_node = free_node_dynamic;
	} else {
		uint32_t sz;
		if (0 == strm->max_num) {
			STRM_PRINT(DBG_LIB"Param Err@max_num\n");
			goto INIT_STRM_ERROR;
		}
		sz = strm->max_num * sizeof(struct stream_node);
		strm->node_pool = (struct stream_node *)STRM_MALLOC(strm, sz);
		if (NULL == strm->node_pool) {
			goto INIT_STRM_ERROR;
		}
		STRM_PRINT(DBG_LIB"create pool\n");
		memset(strm->node_pool, 0, sz);
		strm->new_node  = new_node_static;
		strm->delete_node = free_node_static;
	}
	return (void*)strm;
INIT_STRM_ERROR:
	param->mem_ops.free(strm);
	return NULL;
}

int stream_close(void *hdl)
{
	struct stream *strm = (struct stream *)hdl;
    struct stream_node *node = NULL;
	
	while (!list_empty(&strm->header)) 
    {/* Delete. */
        
		node = list_first_entry(&strm->header,
			struct stream_node , list);
		list_del(&node->list);
		/* Free node */
		//STRM_PRINT("Remove id %d\n", node->idx);
		//free(node->user_data);
		strm->num--;
		strm->delete_node(strm, node);
	}
	if ((!(STRM_TYPE_DYNAMIC & strm->type)) && (strm->node_pool))
	{
		STRM_PRINT(DBG_LIB"delete pool\n");
		STRM_FREE(strm, strm->node_pool);
	}
	STRM_FREE(strm, strm);
	return ENOERROR;
}

uint32_t stream_get(void *hdl, void *data, uint32_t size, uint32_t mode)
{
	struct stream *strm = (struct stream *)hdl;
    struct stream_node *node = NULL;
	uint16_t sz = 0;

	if (list_empty(&strm->header))
	{
		STRM_DEBUG(DBG_LIB"empty\n");
		return 0;
	}
	
	// del as queue mode, del tail
	if (STRM_MODE_FIFO & mode) 
	{
		node = list_first_entry(&strm->header,
			struct stream_node, list);
	}
	else //del as stack mode, del head
	{
		node = list_last_entry(&strm->header,
			struct stream_node, list);
	}
	

	if (node) {
		STRM_DEBUG(DBG_LIB"get %d\n", node->idx);
		if (strm->type & STRM_TYPE_USRPTR)
		{
			sz = node->size;
			*(uint32_t*)data = (uint32_t)node->ptr;
		}
		else
		{
			sz = (uint16_t)size;
			sz = min(node->size, sz);
			memcpy(data, node->ptr, sz);
			STRM_FREE(strm, node->ptr);
		}
		list_del(&node->list);
		strm->delete_node(strm, node);
		strm->num--;
	} 
	
	return sz;
}

uint32_t stream_put(void *hdl, void *data, uint32_t size, uint32_t mode)
{
	struct stream *strm = (struct stream *)hdl;
	struct stream_node *node;
	uint16_t  sz = 0;

	if ((strm->max_num > 0) && (strm->num >= strm->max_num)) {
		STRM_DEBUG(DBG_LIB"full %d/%d\n", strm->num, strm->max_num);
		return 0;
	}

	if (NULL == (node = strm->new_node(strm))) {
		STRM_DEBUG(DBG_LIB"new err\n");
		return 0;
	}

	node->idx = strm->idx++;
	if (strm->type & STRM_TYPE_USRPTR)
	{
		sz = (uint16_t)size;
		node->ptr = data;
		node->size = sz;
	}
	else
	{
		if (NULL == (node->ptr = STRM_MALLOC(strm, size))) {
			strm->delete_node(strm, node);
			return 0;
		}
		
		sz = (uint16_t)size;
		memcpy(node->ptr, data, sz);
		node->size = sz ;
	}
	
	// add as queue mode, add to tail
	//if (STRM_MODE_FIFO & mode) 
	{
		list_add_tail(&node->list, &strm->header);
	}
	//else // add as stack mode, add to head
	//{
	//	list_add(&node->list, &strm->header);
	//}
	STRM_DEBUG(DBG_LIB"put %d\n", node->idx);
	strm->num++;
	
	return sz;
}


