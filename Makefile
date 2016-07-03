src = $(wildcard *.c)
obj = $(src:.c=.o)

CFLAGS = -std=c11 -g -fstack-protector-all -Wall -fopenmp -march=native -O3
LDFLAGS = -std=c11 -fopenmp

mandel: $(obj) ;    $(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean: ;rm -f $(obj) myprog



