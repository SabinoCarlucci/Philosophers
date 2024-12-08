NO_COLOR = '\033[0m'
YELLOW = '\033[0;33m'
GREEN = '\033[0;32m'
RED = '\033[0;31m'
BLUE = '\033[0;34m'
CYAN = '\033[0;36m'
MAGENTA = '\033[0;35m'


NAME = philo

SRCS = main.c parsing.c utils.c init.c philo_things.c
OBJS = ${SRCS:.c=.o}

CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread -g #-fsanitize=thread #-O3

all: ${NAME}

${NAME}: ${OBJS} philo.h
	@echo $(YELLOW) "compiling philo..."$(NO_COLOR)
	@$(CC) ${CFLAGS} ${OBJS} -o ${NAME}
	@echo $(GREEN)"compiled philo ✓✓✓"$(NO_COLOR)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo $(YELLOW) "removing .o files..."$(NO_COLOR)
	@rm -f ${OBJS}
	@echo $(GREEN)"removed .o files ✓✓✓"$(NO_COLOR)

fclean: clean
	@echo $(YELLOW) "removing NAME file..."$(NO_COLOR)
	@rm -f ${NAME}
	@echo $(GREEN)"removed NAME file ✓✓✓"$(NO_COLOR)

re: fclean all

test: re 
	gdb ${NAME}

.PHONY: all clean fclean re