#ifndef _DBG_H_
#define _DBG_H_

#include <stdio.h>
#include <errno.h>

#include <unistd.h>

#include "colors.h"

/* macro definitions */
#define log_err(M) isatty(STDERR_FILENO) ? fprintf(stderr, COL_FG_RED "[ERROR]" COL_RESET " %s() in %s:%d:\n\t" M "\n", __func__,  __FILE__, __LINE__) \
					 : fprintf(stderr, "[ERROR] %s in %s:%d:\n\t" M "\n", __func__,  __FILE__, __LINE__)
#define log_warn(M) isatty(STDERR_FILENO) ? fprintf(stderr, COL_FG_BLU "[WARN!]" COL_RESET " " M "\n") \
					  : fprintf(stderr, "[WARN!] %s:\n\t" M "\n", __func__)

#define errno_print() \
do { \
	isatty(STDERR_FILENO) ? fprintf(stderr, COL_FG_RED "[ERROR]" COL_RESET " %s in %s:%d errno = %d\n\t", __func__, __FILE__, __LINE__, errno) \
			      : fprintf(stderr, "[ERROR] %s in %s:%d errno = %d\n\t", __func__, __FILE__, __LINE__, errno); \
	perror(NULL); \
} while(0)


#endif
