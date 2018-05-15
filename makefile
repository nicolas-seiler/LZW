.PHONY: clean, mrproper, all, cmp

PRG=lzw
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
LDFLAGS=

all: $(PRG)

$(PRG): $(OBJ)
	gcc $^ -o $@ $(LDFLAGS)

%.o: %.c
	gcc -c $< -o $@ $(CFLAGS)

clean:
	rm -f *.o

mrproper: clean
	rm -f $(PRG)

cmp: all clean
