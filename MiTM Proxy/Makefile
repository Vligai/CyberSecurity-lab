NAME=vproxy
SRC=server.c
SRC2=sslstuff.c
OBJ=$(SRC:.c=.o)
OBJ2=$(SRC2:.c=.o)
RM=rm -f
OSSL=/usr/include/openssl
CFLAGS += -I$(OSSL) -g -O2
LDLIBS += -lcrypto -lssl

all: $(NAME)

$(NAME): $(OBJ) $(OBJ2)
	$(CC) -o $(NAME) $(OBJ) $(OBJ2) $(LDLIBS)

clean:
	-$(RM) *~
	-$(RM) *.o
	-$(RM) *.core
	-$(RM) *.swp
	-$(RM) \#*

fclean: clean all

re: fclean all
