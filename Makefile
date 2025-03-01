CC	=	gcc

PREFIX	=	/usr
BIN_DIR	=	$(PREFIX)/bin
BIN_NAME	=	sbtty

SRCS	=	$(wildcard src/*.c)

OBJS	=	$(SRCS:%.c=%.o)

LIB_HF_PATH	=	lib/

CFLAGS	=	-I./include/
CFLAGS	+=	-Wall
CFLAGS	+=	-Wextra
CFLAGS	+=	-Wpedantic
CFLAGS	+=	-Wunused
CFLAGS	+=	-Wunused-parameter
CFLAGS	+=	-L$(LIB_HF_PATH) -lhf
CFLAGS	+=	-lncurses
CFLAGS	+=	-lmpv

ifeq ($(ENV), dev)
	CFLAGS	+=	-g3
else
	CFLAGS	+=	-O2
endif

TESTS_PATH	=	tests/

all:	$(BIN_NAME)

make_lib:
	make -C $(LIB_HF_PATH)

$(BIN_NAME):	make_lib $(OBJS)
	$(CC) $(OBJS) -o $(BIN_NAME) $(CFLAGS)

make_clean_lib:
	make clean -C $(LIB_HF_PATH)

clean:	make_clean_lib
	rm -f src/*.o

make_fclean_lib:
	make fclean -C $(LIB_HF_PATH)

make_fclean_tests:
	make fclean -C $(TESTS_PATH)

fclean:	clean make_fclean_lib make_fclean_tests
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

## -- CRITERION TESTS -- ##
unit_tests:
	make re -C $(TESTS_PATH)

tests_run:	unit_tests
	./$(TESTS_PATH)/unit_tests

lines:	tests_run
	gcovr --exclude $(TESTS_PATH)

branches:	tests_run
	gcovr --exclude $(TESTS_PATH) --txt-metric branch

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
		make_lib make_clean_lib make_fclean_lib make_fclean_tests	\
		unit_tests tests_run lines branches	\
		install uninstall dependencies \
		coding-style github
