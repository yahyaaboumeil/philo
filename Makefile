CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCS = ft_isdigit.c ft_atoi.c ft_isspace.c  err.c parsing.c routin.c helper.c philo.c


OBJS = ${SRCS:.c=.o}

NAME = philo 

.c.o:
	${CC} ${CFLAGS} -c $< -o $@

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} $^ -o $@

clean:
	${RM} ${OBJS} 

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all fclean re 