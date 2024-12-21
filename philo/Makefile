NAME=philo

FILES= philo/cleanup.c philo/initialize.c philo/parsing.c philo/routine.c philo/time.c\
	philo/ft_atoi.c philo/monitor.c philo/philo.c philo/routine_utils.c

OFILES= $(FILES:.c=.o)

#EXTRA =  -fsanitize=thread
# EXTRA = -fsanitize=undefined

FLAGS= -Wall -Wextra -Werror $(EXTRA)

HEADER= philo.h

REMOVE = Makefile

# t : 
# 	@echo $(OFILES) 

all : $(NAME) 

$(NAME) : $(OFILES) $(HEADER)
	cc $(FLAGS) $(OFILES) -o $(NAME)

%.o : %.c $(HEADER) $(REMOVE)
	cc -c $(FLAGS) $< -o $@

clean : 
	rm -f $(OFILES)

fclean : clean
	rm -f $(NAME)

re : fclean all
