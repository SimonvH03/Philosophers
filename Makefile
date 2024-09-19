NAME	=	philo
CC		=	gcc
CFLAGS	=	-g
# CFLAGS	=	-Wall -Werror -Wextra
HEADERS	=	philo.h

SRCDIR	=	./src
SRC		=	$(SRCDIR)/main.c \
			$(SRCDIR)/error_exit.c \
			$(SRCDIR)/init_table.c \
			$(SRCDIR)/state_log.c \
			$(SRCDIR)/parse.c

OBJS	=	${SRC:.c=.o}

all: $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean:
	rm -rf $(OBJS)
	rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
