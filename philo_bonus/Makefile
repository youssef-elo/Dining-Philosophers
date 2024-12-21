NAME =philo_bonus

FILES= $(shell ls *.c)

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