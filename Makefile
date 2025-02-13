CC	=	gcc

NAME	=	sbtty

SRCS	=	$(wildcard src/*.c)

OBJS	=	$(SRCS:%.c=%.o)

CFLAGS	=	-I./include/
CFLAGS	+=	-Wall
CFLAGS	+=	-Wextra
CFLAGS	+=	-Wpedantic
CFLAGS	+=	-Wunused
CFLAGS	+=	-Wunused-parameter
CFLAGS	+=	-lncurses

ifeq ($(ENV), dev)
	CFLAGS	+=	-g3
else
	CFLAGS	+=	-O2
endif

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(CFLAGS)

clean:
	rm -f src/*.o

fclean:	clean
	rm -f $(NAME)
	rm -f *.txt

re:	fclean all

.PHONY: all clean fclean re
