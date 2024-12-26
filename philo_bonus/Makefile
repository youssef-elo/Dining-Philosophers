NAME =philo_bonus

FILES= time.c  \
	watchers.c  \
	philo_bonus.c\
	child_philo.c \
	manage_philo.c \
	parsing_bonus.c \
	ft_atoi_bonus.c  \
	initialize_bonus.c\

OFILES = $(FILES:.c=.o)

FLAGS= -Wall -Wextra -Werror

HEADER= philo_bonus.h

all : $(NAME)

$(NAME) : $(OFILES)
	cc $(FLAGS) $(OFILES) -o $(NAME) 

%.o : %.c $(HEADER)
	cc $(FLAGS) -c $< -o $@ 

clean :
	rm -f $(OFILES)

fclean : clean
	rm -f $(NAME)

re : fclean all
