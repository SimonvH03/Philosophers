NAME	= philo
CC		= cc
CFLAGS	= -g
# CFLAGS	= -Wall -Werror -Wextra

SRCDIR	= ./src
SRC		=	$(SRCDIR)/main.c \
			$(SRCDIR)/error_exit.c \
			$(SRCDIR)/init_table.c \
			$(SRCDIR)/state_log.c \
			$(SRCDIR)/utils.c \

OBJS	= ${SRC:.c=.o}

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean:
	rm -rf $(OBJS)
	rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re
