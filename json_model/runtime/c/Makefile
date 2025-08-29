.PHONY:
clean:
	$(RM) *.o

CFLAGS      = -Ofast -Wall
CPPFLAGS    = -DREGEX_ENGINE_RE2 -DCHECK_FUNCTION_NAME=check_model -I.

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<
