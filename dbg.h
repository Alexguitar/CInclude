#ifndef _DBG_H_
#define _DBG_H_

/* macro definitions */
#define log_err(M) fprintf(stderr, "[ERROR] %s in %s:%d:\n\t" M "\n", __func__,  __FILE__, __LINE__)
#define log_warn(M) fprintf(stderr, "[WARN] %s:\n\t" M "\n", __func__)

#define errno_print() { fprintf(stderr, "[ERROR] %s in %s:%d errno = %d\n", __func__, __FILE__, __LINE__, errno); perror(NULL); }


#endif
