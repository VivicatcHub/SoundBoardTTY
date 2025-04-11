CC	=	gcc

PREFIX	=	/usr
BIN_DIR	=	$(PREFIX)/bin
BIN_NAME	=	sbtty

SRCS	=	$(wildcard src/*.c)

OBJS	=	$(SRCS:%.c=%.o)

CFLAGS	=	-I./include/
CFLAGS	+=	-Wall
CFLAGS	+=	-Wextra
CFLAGS	+=	-Wpedantic
CFLAGS	+=	-Wunused
CFLAGS	+=	-Wunused-parameter
CFLAGS	+=	-lncurses
CFLAGS	+=	-lmpv

ifeq ($(ENV), dev)
	CFLAGS	+=	-g3
else
	CFLAGS	+=	-O2
endif

all:	$(BIN_NAME)

$(BIN_NAME):	$(OBJS)
	$(CC) $(OBJS) -o $(BIN_NAME) $(CFLAGS)

clean:
	rm -f src/*.o

fclean:	clean
	rm -f $(BIN_NAME)
	rm -f *.txt

re:	fclean all

## -- INSTALL -- ##
dependencies:
	sudo apt-get install libao-dev libmpg123-dev

install:	dependencies all
	sudo install -m 755 $(BIN_NAME) $(BIN_DIR)

uninstall:
	sudo rm -f $(BIN_DIR)/$(BIN_NAME)

coding-style:
	./format.sh include/header.h
	./format.sh include/help_fc.h
	clear
	mango

github:
	git remote get-url origin |	\
	sed 's/git@github.com:/https:\/\/github.com\//' |	\
	xargs xdg-open

.PHONY: all clean fclean re	\
		install uninstall dependencies \
		coding-style github
