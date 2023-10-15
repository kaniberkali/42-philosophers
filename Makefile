CC = gcc
FLAGS = -Wall -Wextra -Werror #-pthread -fsanitize=thread
PHILO = philo
SRCS = control.c \
		die.c \
		init.c \
		main.c \
		routine.c \
		time.c \
		utils.c \
		mutexes.c \
		threads.c

all:  $(PHILO)

$(PHILO) : $(SRCS)
	$(CC) $(FLAGS) $(SRCS) -o $(PHILO)
	@echo "FINISH"

norm:
	norminette  source

clean:
	rm -rf $(PHILO)

fclean: clean
	rm -rf $(PHILO)

re: fclean all

.PHONY: clean re fclean all
