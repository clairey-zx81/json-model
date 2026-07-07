F.c = $(wildcard *.c)
F.o = $(F.c:%.c=%.o)

.PHONY: clean
clean:
	$(RM) $(F.o)

.PHONY: compile
compile: $(F.o)

REGEX       = RE2   # RE2 or PCRE2
URLIB       = NONE  # NONE or CURL

CC.inc      = -I/usr/local/include -I.

CFLAGS      = -Wall -O3 -ffast-math -mtune=native -Wno-unused-function
CPPFLAGS    = -DREGEX_ENGINE_$(REGEX) -DURL_PARSER_$(URLIB) -DCHECK_FUNCTION_NAME=check_model $(CC.inc)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<
