CC=g++
NAME=basesniffer
NAME1=seachmod
NAME2=flowmod
SRC=basesniffer.cpp
SRC1=searchmod.cpp
SRC2=flowmod.cpp
OBJ=$(SRC:.cpp=.o)
OBJ1=$(SRC1:.cpp=.o)
OBJ2=$(SRC2:.cpp=.o)
RM = rm -f
CFLAGS += -lpcap
all: $(OBJ) $(OBJ1)
	$(CC) -o $(NAME) $(SRC) $(CFLAGS)
	$(CC) -o $(NAME1) $(SRC1) $(CFLAGS)
	$(CC) -o $(NAME2) $(SRC2) $(CFLAGS)
clean:
	-$(RM) *~
	-$(RM) *.o
	-$(RM) *.core
	-$(RM) \#*

fclean: clean
	-$(RM) $(LIBPATH)/$(NAME)

re: fclean all
