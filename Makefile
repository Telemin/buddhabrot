src = $(wildcard *.c)
obj = $(src:.c=.o)

CFLAGS = -std=c11 -g -O3 -march=native -fopenmp
LDFLAGS = -lm -fopenmp

mandel: $(obj) ;    $(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean: ;rm -f $(obj) myprog



