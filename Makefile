CC = gcc
LDLIBS = -lm
CFLAGS= -Wall -Os

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all: lib.o ;

lib.o: $(OBJS)
	@ld -o $@ -r $(OBJS)
	@echo Updated: $?

$(OBJS): %.o: %.c
	@$(CC) -c $< $(LDLIBS)

clean:
	@rm -f $(OBJS)

.PHONY: clean all phony
