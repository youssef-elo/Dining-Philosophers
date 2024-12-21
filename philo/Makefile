NAME=philo

FILES= $(shell ls *.c)

OFILES= $(FILES:.c=.o)

# EXTRA =  -fsanitize=thread
# EXTRA = -fsanitize=undefined

FLAGS= -Wall -Wextra -Werror $(EXTRA)

HEADER= philo.h

REMOVE = Makefile

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