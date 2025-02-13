##
## EPITECH PROJECT, 2025
## B-PSU-200-LYN-2-1-minishell1-valentin.guinet
## File description:
## Makefile
##

CC	=	gcc

NAME	=	unit_tests

SRCS	=	$(wildcard *.c)	\
			$(wildcard ../lib/hf/*.c)	\
			$(wildcard ../src/*.c)
SRCS	:=	$(filter-out ../src/main.c, $(SRCS))

LIB_HF_PATH	=	../lib/hf/

CFLAGS	=	-I../include/
CFLAGS	+=	-Wall
CFLAGS	+=	-Wextra
CFLAGS	+=	-Wpedantic
CFLAGS	+=	-L$(LIB_HF_PATH) -lhf

ifeq ($(ENV), dev)
	CFLAGS	+=	-g3
else
	CFLAGS	+=	-O2
endif

FLAGS	=	-I../include/ -lcriterion --coverage

all:	$(NAME)

$(NAME):
	$(CC) $(SRCS) -o $(NAME) $(FLAGS)

fclean:
	rm -f *.gcda
	rm -f *.gcno
	rm -f $(NAME)

re:	fclean all

.PHONY:	all fclean re