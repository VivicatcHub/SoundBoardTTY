##
## EPITECH PROJECT, 2024
## EmptyRepo
## File description:
## Makefile
##

SRCS	=	$(wildcard *.c)

OBJS	=	$(SRCS:%.c=%.o)

NAME	=	libhf.a

CFLAGS	=	-I../../include/
CFLAGS	+=	-Wall
CFLAGS	+=	-Wextra
CFLAGS	+=	-Wpedantic

ifeq ($(ENV), dev)
	CFLAGS	+=	-g3
else
	CFLAGS	+=	-O2
endif

all:	$(NAME)

$(NAME):	$(OBJS)
	ar rc $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re