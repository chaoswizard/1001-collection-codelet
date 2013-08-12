#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "types.h"
#include "stream.h"


int stream_test();


int main()
{
	stream_test();
	return 0;
}



int stream_test()
{
	struct stream_param param = {0};
	void *out_hdl;
	void *in_hdl;
	void *hdl;
	uint32_t ret, len,tmp;
	char buf[34];
	char *str;
	int opt;
	
	param.max_num = 9;
	param.mem_ops.malloc = malloc;
	param.mem_ops.free = free;
	in_hdl = stream_open(STRM_TYPE_VALUE, &param);
	if (!in_hdl) {
		stream_close(out_hdl);
		return 0;
	}

	param.max_num = 0;
	out_hdl = stream_open(STRM_TYPE_VALUE | STRM_TYPE_DYNAMIC, &param);
	if (!out_hdl) return 0;
	tmp = 0;

	while (tmp++<143)
	{
		srand(100000+tmp);
		opt = rand()%4;
		switch (opt) {
		case 0:
		case 2:
			str = "input";
			hdl = in_hdl;
		break;
		case 1:
		case 3:
			#if 0
			str = "output";
			hdl = out_hdl;
			#else
			str = "input";
			hdl = in_hdl;
			#endif
			break;
		default:
			printf("..skip %d:%d\n", tmp, opt);
			continue;
		break;
		}

		if ((0 == opt) || (3 == opt)) {
			sprintf(buf, "%s_%d", str, tmp);
			len = strlen(buf);
			ret = stream_put(hdl, buf, len, STRM_MODE_FIFO);//STRM_MODE_FIFO
			if (ret)
				printf("put %s Ok:%d/%d\n", buf, ret, len);
			else
				printf("put %s Fail:%d/%d \n", buf, ret, len);
		} else if ((1 == opt) || (4 == opt)) {
			len = 34;
			ret = stream_get(hdl, buf, len, STRM_MODE_FIFO);//STRM_MODE_FIFO
			if (ret)
				printf("get %s Ok:%d/%d\n", buf, ret, len);
			else
				printf("get %s Fail:%d/%d \n", str, ret, len);
		}

	}
	
	stream_close(out_hdl);
	stream_close(in_hdl);
	return 0;
}


