CFLAGS += -ansi -Wall -Wextra -Werror -pedantic
CFLAGS += -DNDEBUG -Ofast -s -flto

all: number

number: number.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	$(RM) number

.PHONY: all clean
