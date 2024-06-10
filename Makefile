NAME	= pipex
CFLAGS	= -Wall -Werror -Wextra

LFTDIR	= ./libft
LIBFT	= $(LFTDIR)/libft.a

LIBS	= $(LIBFT)

SRCDIR	= ./src
SRC		=	$(SRCDIR)/main.c
			# $(SRCDIR)/

OBJS	= ${SRC:.c=.o}

all: $(NAME)

$(LIBFT):
	make -C $(LFTDIR) all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

$(NAME): $(OBJS) $(LIBS)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

clean:
	rm -rf $(OBJS)
	make -C $(LFTDIR) clean -s

fclean:
	rm -rf $(OBJS)
	rm -rf $(NAME)
	make -C $(LFTDIR) fclean

re: clean all

.PHONY: all, clean, fclean, re
