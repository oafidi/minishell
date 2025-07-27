#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

#define NO_QUOTE 0
#define SINGLE_QUOTE 1
#define DOUBLE_QUOTE 2

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

typedef struct s_token
{
    char            *value;
    t_token_type    type;
    struct s_token  *next;
    struct s_token  *prev;
}   t_token;

typedef struct s_redir
{
    t_token_type    type;
    char            *target;
    int             fd;
    int             ambiguous_flag;
    int             should_expand;
    struct s_redir  *next;
}   t_redir;

typedef struct s_cmd
{
    char			*line;
    char            **args;
    int             argc;
    t_redir         *redirs;
    struct s_cmd    *next;
}   t_cmd;

typedef struct s_env
{
    char			*key;
	char			*value;
    struct s_env    *next;
}   t_env;

typedef struct global_struct
{
    int     last_exit_status;
    t_env   *env;
    t_token *tokens;
    t_cmd	*cmds;
}   global_struct;

void	ft_putstr_fd(char *s, int fd);
char	*ft_strdup(char *s1);
size_t	ft_strlen(char *s);
char	*ft_strjoin(char *s1, char *s2);
int     is_space(char c);
int     is_operator(char c);
int     is_quote(char c);
int     check_quotes_balance(char *input);
int     get_word_length(char *str);
t_token *create_token(char *value, t_token_type type);
void    add_token_to_list(t_token **head, t_token **tail, t_token *new_token);
t_token *lexer(char *input, global_struct *global_struct);
void    free_token_list(t_token *tokens);
void    free_redirections(t_redir *redirs);
void    free_command(t_cmd *cmd);
void    free_command_list(t_cmd *commands);
t_cmd   *parser(t_token *tokens, global_struct *global_struct);
t_env	*copy_environment(char **env);
void	free_environment(t_env **env);
int     validate_syntax(t_token *tokens, global_struct *global_struct);
t_cmd	*init_command_parsing(t_token *token);
t_redir *create_redirection(t_token_type type, char *target);
void    add_redirection_to_cmd(t_cmd *cmd, t_redir *redir);
void	free_command(t_cmd *cmd);
int     ft_strcmp(char *s1, char *s2);
char	*ft_strjoin_char(char *s1, char c);
char	*get_env_value(t_env *env, char *name);
void	process_heredoc_delimiter(t_redir *redir);
int     check_quotes_type(char *str);
char	*remove_quotes(char *target);
int     check_quotes_type(char *str);

# endif