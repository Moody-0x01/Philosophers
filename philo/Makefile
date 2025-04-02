LIB_PHILO=./libphilo.a
PHILO_MAIN=./main.c
SRCS=atol.c ft_isspace.c ft_strlen.c
OBJS=$(SRCS:%.c=%.o)
NAME=./philo
CC=cc
LIBS=-L. -lphilo -pthread
INCLUDE=-I./include
CFLAGS=-Wall -Wextra -Werror $(INCLUDE) # -ggdb # -fsanitize=address -g
AR=ar rsc
RM=rm -f

all: $(NAME)
%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@
$(LIB_PHILO): $(OBJS)
	$(AR) $@ $?
$(NAME): $(LIB_PHILO) $(PHILO_MAIN)
	$(CC) $(CFLAGS) $(PHILO_MAIN) -o $@ $(LIBS)
clean:
	$(RM) $(OBJS)
	$(RM) $(LIB_PHILO)
fclean: clean
	$(RM) $(NAME)
re: fclean all
.PHONY: re fclean clean bonus
