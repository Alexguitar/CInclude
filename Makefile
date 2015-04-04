CC = gcc
LDFLAGS = -lm -Wall
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))

lib.o: $(OBJS)
	@ld -o $@ -r $(OBJS)
	@echo Updated: $?

$(OBJS): %.o: %.c
	@$(CC) -c $< $(LDFLAGS)

clean:
	@rm -f $(OBJS)

.PHONY: clean
