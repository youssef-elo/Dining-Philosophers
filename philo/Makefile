NAME= philo

FILES= time.c\
	philo.c   \
	cleanup.c  \
	parsing.c   \
	parsing_2.c  \
	routine.c     \
	ft_atoi.c      \
	monitor.c       \
	initialize.c     \
	routine_utils.c   \

OFILES= $(FILES:.c=.o)

FLAGS= -Wall -Wextra -Werror 

HEADER= philo.h

all : $(NAME)

$(NAME) : $(OFILES) $(HEADER)
	cc $(FLAGS) $(OFILES) -o $(NAME)

%.o : %.c $(HEADER)
	cc -c $(FLAGS) $< -o $@

clean : 
	rm -f $(OFILES)

fclean : clean
	rm -f $(NAME)

re : fclean all
