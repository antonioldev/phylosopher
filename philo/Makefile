NAME	=	philo
CC		=	cc
DEPS	=	philo.h
FLAGS	=	-Wall -Wextra -Werror -pthread -g3 -gdwarf-3 -fsanitize=thread 
SRC		=	main.c initiate.c dinner.c action.c utils.c dinner_operation.c
OBJ		=	$(SRC:.c=.o)
RM		=	rm -f

all		:	$(NAME)

$(NAME)	:	$(OBJ)
			$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o		:	%.c
			$(CC) $(FLAGS) -c -o $@ $<

clean	:
			$(RM) $(OBJ)

fclean	:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY	: all clean fclean re