#ifndef __MY_ERRORS_H__
#define __MY_ERRORS_H__
#define ENOERROR      (0)
#define ELIBPROC      (1)
#define EPARAM        (2)
#define EDRAIN        (3)

typedef enum {
	FILTER_NULL,
	FILTER_RESAMPLE,
	FILTER_AUTOMUTE,
	FILTER_LAST,
}T_eFILTER_TYPE;

#endif
