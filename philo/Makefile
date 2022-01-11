NAME			=	philo

SRCS_FILES		=	main.c 
SRCS_FILES_B	=	

SRCS				=	$(addprefix ./src/, $(SRCS_FILES))
SRCS_B				=	$(addprefix ./src/, $(SRCS_FILES_B))

HEADER			= ./includes/


OBJ				= $(SRCS:.c=.o)

OBJ_B			= $(SRCS_B:.c=.o)

CC				= gcc

RM				= @rm -f

FLAGS			= -Wall -Wextra -Werror -I${HEADER}

.PHONY:			all clean fclean re bonus

all:			$(NAME)

$(NAME):		$(OBJ) $(OBJ_B) $(HEADER)
				$(CC) -o $(NAME) $(OBJ)

%.o:			%.c $(HEADER)
				$(CC) -g $(FLAGS) -c $< -o $@

bonus:			
				

clean	:	
	@rm -f $(OBJ) $(OBJ_B)

fclean	:	clean
	@rm -f $(NAME) $(NAME_B)
re		: fclean all
