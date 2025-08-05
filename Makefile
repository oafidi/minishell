CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3


SRC = \
libft/ft_isalnum.c \
libft/ft_isalpha.c \
libft/ft_itoa.c \
libft/ft_strjoin_char.c \
libft/ft_putstr_fd.c \
libft/ft_strcmp.c \
libft/ft_strdup.c \
libft/ft_strjoin.c \
libft/ft_strlen.c \
libft/ft_substr.c \
srcs/main.c \
srcs/lexer/tokenizer.c \
srcs/lexer/utils.c \
srcs/parser/parser.c \
srcs/parser/syntax_errors.c \
srcs/parser/utils.c \
srcs/expander/expand_heredoc.c \
srcs/expander/expand_target.c \
srcs/expander/expander.c \
srcs/expander/quotes.c \
srcs/expander/utils.c \
srcs/executer/utils/env_management.c \
srcs/utils/free.c \
srcs/utils/utils.c

OBJS = $(SRC:.c=.o)
TARGET = minishell

all: $(TARGET)

READLINE_COMPILE = -I$(shell brew --prefix readline)/include
READLINE_LINK = -lreadline -L$(shell brew --prefix readline)/lib

$(TARGET): includes/minishell.h $(OBJS)
	$(CC) $(CFLAGS) $(READLINE_COMPILE) $(OBJS) -o $(TARGET) $(READLINE_LINK)

%.o: %.c
	$(CC) $(CFLAGS) $(READLINE_COMPILE) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(TARGET)

re: fclean all
