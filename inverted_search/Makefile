SRC := $(wildcard *.c)
OBJ := $(patsubst %.c, %.o, $(SRC))
a.out : $(OBJ)
	gcc -o $@ $^
clean :
	rm *.o *.out
