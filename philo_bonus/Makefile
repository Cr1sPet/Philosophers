NAME			=	philo_bonus

SRCS_FILES		=	main.c\
					ft_atoi.c\
					ft_strlen.c\
					valid.c\
					ft_isdigit.c\
					init.c\
					utils.c\
					death_monitor.c\
					work_philo.c
					

SRCS_FILES_B	=	

SRCS				=	$(addprefix ./src/, $(SRCS_FILES))
SRCS_B				=	$(addprefix ./src/, $(SRCS_FILES_B))

HEADER			= ./includes/


OBJ				= $(SRCS:.c=.o)

OBJ_B			= $(SRCS_B:.c=.o)

CC				= gcc

RM				= @rm -f

SEMAPHORS			= -pthread

FLAGS			=  -Wall -Wextra -Werror 

.PHONY:			all clean fclean re bonus

all:			$(NAME)

$(NAME):		$(OBJ) $(OBJ_B) $(HEADER)
				$(CC) $(SEMAPHORS) -o $(NAME) $(OBJ)

%.o:			%.c $(HEADER)
				$(CC) -g $(FLAGS) -I${HEADER} -c $< -o $@

bonus:			
				

clean	:	
	@rm -f $(OBJ) $(OBJ_B)

fclean	:	clean
	@rm -f $(NAME) $(NAME_B)
re		: fclean all
