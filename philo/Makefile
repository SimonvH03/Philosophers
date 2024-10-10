NAME	=	philo
CC		=	cc
# CFLAGS	=	-g
CFLAGS	=	-Wall -Werror -Wextra

HEADERS	=	philo.h

SRCDIR	=	./src
SRC		=	$(SRCDIR)/main.c \
			$(SRCDIR)/error_exit.c \
			$(SRCDIR)/init_table.c \
			$(SRCDIR)/safe_read.c \
			$(SRCDIR)/log_change.c \
			$(SRCDIR)/philo_actions.c \
			$(SRCDIR)/parse.c

OBJS	=	${SRC:.c=.o}

all: $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@echo "\e[34mcompiling $(NAME)...\e[0m"
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@echo "\e[33mclean\e[0m"
	rm -rf $(OBJS)

fclean:
	@echo "\e[31mfclean\e[0m"
	rm -rf $(OBJS)
	rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
