F.c = $(wildcard *.c)
F.o = $(F.c:%.c=%.o)

.PHONY: clean
clean:
	$(RM) *.o

.PHONY: compile
compile: $(F.o)

CFLAGS      = -Ofast -Wall
CPPFLAGS    = -DREGEX_ENGINE_RE2 -DCHECK_FUNCTION_NAME=check_model -I.

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<
