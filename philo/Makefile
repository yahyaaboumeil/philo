CC = cc -g -O0 -pthread 
CFLAGS = -Wall -Wextra -Werror 
RM = rm -f

SRCS = helper2.c monitor.c utils.c parsing.c routin.c helper.c philo.c


OBJS = ${SRCS:.c=.o}

NAME = philo 

.c.o:
	${CC}  -c $< -o $@

all: ${NAME}

${NAME}: ${OBJS}
	${CC} $^ -o $@

clean:
	${RM} ${OBJS} 

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all fclean re 