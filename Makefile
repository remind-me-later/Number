PROGRAM = number

SRC = $(wildcard *.c)
OBJ = $(SRC:%.c=%.o)

CWARN = -ansi -Wall -Wextra -Werror -pedantic
CFLAGS = -DNDEBUG -Ofast -s -flto

.PHONY: all 
all: $(PROGRAM)

.PHONY: debug
debug: CFLAGS = $(CWARN) -DDEBUG -O0 -g3 -fsanitize=address \
	-fsanitize=undefined
debug: LDFLAGS += -fsanitize=address -fsanitize=undefined
debug: clean all

.PHONY: clean
clean:
	$(RM) $(OBJ)

$(PROGRAM): $(PROGRAM).o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
