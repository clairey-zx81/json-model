.PHONY:
clean:
	$(RM) *.o

CXX        ?= g++
CXXFLAGS   = -Ofast -Wall -DCHECK_FUNCTION_NAME=check_model -I.

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
