#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_token_type
{
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIR_IN,
    TOKEN_REDIR_OUT,
    TOKEN_APPEND,
    TOKEN_HEREDOC,
    TOKEN_END
}   t_token_type;

typedef enum e_quote_state
{
    QUOTE_NONE,
    QUOTE_SINGLE,
    QUOTE_DOUBLE
}   t_quote_state;

typedef struct s_token
{
    char            *value;
    t_token_type    type;
    int             should_expand;
    struct s_token  *next;
    struct s_token  *prev;
}   t_token;

typedef struct s_redir
{
    t_token_type    type;
    char            *target;
    char            *heredoc_content;
    int             heredoc_expand;
    struct s_redir  *next;
}   t_redir;

typedef struct s_cmd
{
    char            **args;
    int             argc;
    t_redir         *redirs;
    struct s_cmd    *next;
}   t_cmd;

typedef struct s_parse_ctx
{
    char    **env;
    int     last_exit_status;
    t_token *tokens;
    t_token *current;
    int     error;
    char    *error_msg;
}   t_parse_ctx;

void	ft_putstr_fd(char *s, int fd);
char	*ft_strdup(char *s1);
size_t	ft_strlen(char *s);
int     is_space(char c);
int     is_metachar(char c);
int     is_quote(char c);
int     check_quotes_balance(char *input);
int     get_word_length(char *str);
t_token *create_token(char *value, t_token_type type, int should_expand);
void    add_token_to_list(t_token **head, t_token **tail, t_token *new_token);
t_token *lexer(char *input);
void    free_token_list(t_token *head);
t_cmd   *create_command(void);
t_redir *create_redirection(t_token_type type, char *target);

# endif