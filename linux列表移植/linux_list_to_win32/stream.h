#ifndef _MY_STTREAM_H_
#define _MY_STTREAM_H_

#ifdef __cplusplus
extern "C" {
#endif

struct malloc_ops {
	void *(*malloc)(uint32_t  size);
	void *(*free)(void *ptr);
	void *(*malloc_dbg)(uint32_t  size, uint16_t  *file, uint32_t  line);
	void *(*free_dbg)(void *ptr, uint16_t *file, uint32_t  line);
};

#define min(a, b)   ((a)<(b)?(a):(b))

struct stream_param {
	struct malloc_ops mem_ops;
	uint16_t  max_num;
};

#define STRM_TYPE_VALUE      (1<<0)
#define STRM_TYPE_USRPTR     (1<<1)
#define STRM_TYPE_DYNAMIC    (1<<2)
#define STRM_MODE_FIFO       (1<<3)

void* stream_open(uint16_t  type, struct stream_param *param);
int stream_close(void *hdl);
uint32_t  stream_get(void *hdl, void *data, uint32_t  size, uint32_t  mode);
uint32_t  stream_put(void *hdl, void *data, uint32_t  size, uint32_t  mode);


#ifdef __cplusplus
}
#endif


#endif
