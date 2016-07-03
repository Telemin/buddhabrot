src = $(wildcard *.c)
obj = $(src:.c=.o)

CFLAGS = -std=c11 -g
LDFLAGS = -std=c11 -fopenmp

mandel: $(obj) ;    $(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean: ;rm -f $(obj) myprog



