#include <stdlib.h>
#include "dbg.h"
#include <errno.h>

int main()
{
	log_err("This is an error");
	log_warn("This is a warning");
	errno = 22;
	errno_print();

	return 0;
}
