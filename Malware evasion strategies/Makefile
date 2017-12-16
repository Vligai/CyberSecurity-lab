CC=gcc
NAME=malware
SRC=malware.c
OBJ=$(SRC:.c=.o)
NAME7=supermalware
SRC7=supermalware.c
OBJ7=$(SRC7:.c=.o)
NAME6=malware5
SRC6=malware5.c
OBJ6=$(SRC6:.c=.o)
NAME5=malware4
SRC5=malware4.c
OBJ5=$(SRC5:.c=.o)
NAME4=malware3
SRC4=malware3.c
OBJ4=$(SRC4:.c=.o)
NAME3=malware2
SRC3=malware2.c
OBJ3=$(SRC3:.c=.o)
NAME2=packer
SRC2=packer.c
OBJ2=$(SRC2:.c=.o)
NAME1=malware1
SRC1=malware1.c
OBJ1=$(SRC1:.c=.o)
CFLAGS = -g
RM=rm -f

all:
	$(CC) -o $(NAME) $(SRC) $(CFLAGS)
	$(CC) -o $(NAME1) $(SRC1) $(CFLAGS)
	$(CC) -o $(NAME2) $(SRC2) $(CFLAGS)
	$(CC) -o $(NAME3) $(SRC3) $(CFLAGS)
	$(CC) -o $(NAME4) $(SRC4) $(CFLAGS)
	$(CC) -o $(NAME5) $(SRC5) $(CFLAGS)
	$(CC) -o $(NAME6) $(SRC6) $(CFLAGS)
	$(CC) -o $(NAME7) $(SRC7) $(CFLAGS)

clean:
	-$(RM) *~
	-$(RM) *.o
	-$(RM) *.core
	-$(RM) \#*
	-$(RM) *.exe

fclean: clean

re: fclean all
