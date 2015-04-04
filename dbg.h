#ifndef _DBG_H_
#define _DBG_H_

/* macro definitions */
#define log_err(M) fprintf(stderr, "[ERROR] %s in %s:%d reported with:\n\t" M "\n", __func__,  __FILE__, __LINE__) 

#define errno_print() { fprintf(stderr, "ERRNO = %d\n\t", errno); perror(NULL); }


#endif
