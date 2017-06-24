src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)

CXXFLAGS = -std=c++11 -g -O3 -march=native -Wall
LDFLAGS = -ltbb

mandel: $(obj) ;    $(CXX) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean: ;rm -f $(obj) myprog



