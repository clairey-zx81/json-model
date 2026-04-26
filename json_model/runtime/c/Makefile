F.c = $(wildcard *.c)
F.o = $(F.c:%.c=%.o)

.PHONY: clean
clean:
	$(RM) $(F.o)

.PHONY: compile
compile: $(F.o)

# RE2 or PCRE2
REGEX       = RE2
CC.inc      = -I/usr/local/include -I.

CFLAGS      = -Wall -Ofast -mtune=native -Wunused-function
CPPFLAGS    = -DREGEX_ENGINE_$(REGEX) -DCHECK_FUNCTION_NAME=check_model $(CC.inc)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<
