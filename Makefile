CC	=	gcc

NAME	=	sbtty

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

ifeq ($(ENV), dev)
	CFLAGS	+=	-g3
else
	CFLAGS	+=	-O2
endif

TESTS_PATH	=	tests/

all:	$(NAME)

make_lib:
	make -C $(LIB_HF_PATH)

$(NAME):	make_lib $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(CFLAGS)

make_clean_lib:
	make clean -C $(LIB_HF_PATH)

clean:	make_clean_lib
	rm -f src/*.o

make_fclean_lib:
	make fclean -C $(LIB_HF_PATH)

make_fclean_tests:
	make fclean -C $(TESTS_PATH)

fclean:	clean make_fclean_lib make_fclean_tests
	rm -f $(NAME)
	rm -f *.txt

re:	fclean all

## -- CRITERION TESTS -- ##
unit_tests:
	make re -C $(TESTS_PATH)

tests_run:	unit_tests
	./$(TESTS_PATH)/unit_tests

lines:	tests_run
	gcovr --exclude $(TESTS_PATH)

branches:	tests_run
	gcovr --exclude $(TESTS_PATH) --txt-metric branch

github:
	git remote get-url origin |	\
	sed 's/git@github.com:/https:\/\/github.com\//' |	\
	xargs xdg-open

.PHONY: all clean fclean re	\
		make_lib make_clean_lib make_fclean_lib make_fclean_tests	\
		unit_tests tests_run lines branches	\
		github
