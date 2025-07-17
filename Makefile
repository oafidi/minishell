CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline

SRCS = srcs/main.c srcs/lexer/tokenizer.c srcs/lexer/tokenizer_utils.c \
		srcs/utils/utils.c srcs/utils/free.c libft/ft_putstr_fd.c libft/ft_strlen.c libft/ft_strdup.c \

OBJS = $(SRCS:.c=.o)
TARGET = minishell

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(TARGET)