CC=gcc
NAME=libmyprot.so
SRC=pmalloc.c pfree.c pcalloc.c prealloc.c # pmemalign.c
OBJ=$(SRC:.c=.o)
RM = rm -f
INCLPATH = ../include
LIBPATH = ../lib
CFLAGS += -I$(INCLPATH) -g -Wall
all:$(OBJ) 
	$(CC) $(CFLAGS) -c -fPIC $(SRC)
	$(CC) $(CFLAGS) -shared -o $(LIBPATH)/$(NAME) $(OBJ) -ldl

clean:
	-$(RM) *~
	-$(RM) *.o
	-$(RM) *.core
	-$(RM) \#*

fclean: clean
	-$(RM) $(LIBPATH)/$(NAME)

re: fclean all
