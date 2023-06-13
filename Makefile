##
## EPITECH PROJECT, 2022
## make file
## File description:
## make file
##

SRC	=	bruteforce.c		\
		initialisation.c	\
		main.c				\
		utils1.c			\
		utils2.c


OBJ	=	$(SRC:.c=.o)

NAME	=	bsq

CFLAGS += #-W -Wall -Wextra -Wshadow -Wimplicit -Werror

CPPFLAGS += -I./include

all:	$(NAME)
PHONY	+= all

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)
PHONY	+= clean

fclean:	clean
	rm -f $(NAME)

PHONY	+= fclean

re:	fclean all
PHONY	+= re

unit_tests:
PHONY	+= unit_tests

tests_run:
PHONY	+= tests_run

.PHONY:	$(PHONY)
