NAME=philo

FILES= $(shell ls *.c)

OFILES= $(FILES:.c=.o)

EXTRA = -fsanitize=thread

FLAGS= -Wall -Wextra -Werror $(EXTRA)

HEADER=philo.h

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