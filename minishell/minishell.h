/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:37:31 by oait-bad          #+#    #+#             */
/*   Updated: 2023/06/21 13:59:13 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

# define KRED  "\x1B[31m"
# define KWHT  "\x1B[37m"

# define PIPE 1
# define LESSER 2
# define GREATER 3
# define LEFT_PAR 4
# define RIGHT_PAR 5
# define DOLLAR_SIGN 6
# define ASTERISK 7
# define SINGLE_QUOTE 8
# define DOUBLE_QUOTE 9
# define SPACE 10
# define HEREDOC 11
# define APPEND 12
# define WORD 13
# define INDOUBLE 14
# define INSINGLE 15
# define DEFAULT 16

typedef struct s_pipe
{
	char	*input;
	struct s_pipe *next;
}		t_pipe;

typedef struct s_env
{
	char	*name;
	char	*value;
	struct s_env *next;
}		t_env;

typedef struct s_builtin
{
	int		a;
	int		b;
	int		c;
	int		d;
	int		args;
	int		space;
	int		new_line;
	int		pid;
	int		p[2];
	int		exe;
	char	**pipe_cmd;
	char	**phrase;
	char	*name;
	char	**env;
	char	*new_name;
	char	*line;
	char	*value;
	char	**split_path;
	char	**full_path;
	char	**cmd;
	char	*fcmd;
	char	*path;
	char	*path1;
	char	*path2;
}			t_builtin;

typedef struct s_lexer
{
	char			*input;
	int				i;
	int				type;
	char			*value;
	struct s_lexer	*tokens;
	struct s_lexer	*current_token;
	struct s_lexer	*prev;
	struct s_lexer	*next;
}				t_lexer;

typedef struct s_cmd
{
	char			*input;
	int				i;
	int				type;
	char			**args;
	char			**pipes;
	char			**redirections;
	char			*value;
	struct s_cmd	*next;
}				t_cmd;

enum e_type
{
	ARG = 1,
	FILE_IN,
	FILE_OUT,
	HERE_DOC,
	FILE_OUT_APPEND,
	OPEN_FILE,
	DELIMITER,
	EXIT_FILE,
	EXIT_FILE_APPEND,
};

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

/* test_function */

void	check_cmd(t_pipe **cmd, t_builtin *arr, t_env *new_env);
void	first_cmd(t_pipe **cmd, t_builtin *arr);
void	second_cmd(t_pipe **cmd, t_builtin *arr);
void	last_cmd(t_pipe **cmd, t_builtin *arr);
void	exec_multi_seco_cmd(t_pipe **cmd, t_builtin *arr);
void	execve_cmd_test(t_builtin *arr);
void	access_multi_cmd(t_pipe **cmd, t_builtin *arr);
void	exec_multi_cmd(t_pipe **cmd, t_builtin *arr);
t_pipe	*create_cmd_list(char *line);
void	skip_whitespaces(char *str);
t_pipe	*init_cmd(char *line);

 /* start builtin function */

void	builtin_cd(char **av);
void	builtin_pwd(void);
int		echo_space(char **av, t_builtin *arr);
void	print_echo(char **av, int args, t_builtin *arr);
void	builtin_echo(char **av, int args, t_builtin	*arr);
t_env	*add_env(char *name, char *value);
t_env	*last_node(t_env **env);
void	add_back(t_env **head, char *name, char *value);
void	print_env(t_env *head);
t_env	*builtin_env(char **env, t_builtin *arr, t_env *head);
void	print_export(t_env *head);
t_env	*sort_export(t_env *head, t_builtin *arr);
t_env	*before_sort(t_env *head);
void	builtin_add(t_env **head, t_builtin *arr, char **add);
void	builtin_export(t_env *head, char **add, t_builtin *arr);
void	check_unset(t_builtin *arr, char **add);
void	check_cmd_unset(t_builtin *arr, char **add);
void	delete_unset(t_env **head, t_builtin *arr);
void	builtin_check(t_env **head, t_builtin *arr, char **add);
void	builtin_unset(t_env *head, t_builtin *arr, char **add);
void	check_first_char(t_builtin *arr, char **add);
void	swap_env(t_env *new_node, t_env *tmp, t_builtin *arr);
char	*ft_strdup_unset(const char *s1);
int		size_stack(t_env *head);
int		check_add(t_env **head, t_builtin *arr);
void	check_after_back(t_builtin *arr, char **add);
void	check_path(t_builtin *arr, char **add);
void	check_char(t_builtin *arr, char **add);

 /* end builtin function */

 /* start single cmd function */

void	builtin_child(char *input, t_env *new_env, t_builtin *arr);
void	check_single_cmd(char **token, char **args, t_env *new_env, t_builtin *arr);
void	welcome_to_single_excute(char **args, t_env **new_env, t_builtin *arr);
void	single_cmd(char *cmd, t_builtin *arr);
void	access_single_cmd(char *cmd, t_builtin *arr);
char	**put_env_array(t_env **new_env, t_builtin *arr, int space);
int		size_list(t_env **new_env, t_builtin *arr);
char	*ft_strjoin_exe(char const *s1, char const *s2);
char	**check_env_path(t_env **new_env, t_builtin *arr);
void	single_here_doc(t_builtin *arr, char **args);
void	execve_cmd(t_builtin *arr);
void	execve_path_cmd(char *cmd, t_builtin *arr);

 /* end single cmd function */

int	check_tokens(t_lexer *lexer, t_lexer **token);
int	check_quotes(t_lexer *lexer, t_lexer **token);
t_lexer	*the_lexer(char *input);
char	*check_words(t_lexer *lexer, int *index);
int	node_init(t_lexer **token);
char	**get_env(char **env);
char	**dollar_sign(char **args, char **envp);
char	*get_env_value(char *key, char **env);
char	*get_env_key(char *input);
char	*delete_quotes(char *str);
char	*expand_inside_quotes(char *str);
char	**get_env(char **env);
int		is_between_quotes(char *str);
char	**split_by_pipes(char **input);
void	skip_whitespaces(char *str);


/* start get_next_line function */

char	*get_next_line(int fd);
char	**ft_split(char const *s, char c);
char	*ft_strjoin_get(char *s1, char *s2);
char	*ft_strdup_get(char *str);
int		ft_strlen_get(const char *str);
char	*ft_read(char *stock, int fd);
char	*ft_line(char *str);
char	*ft_save(char *str);
char	*ft_strchr_get(char *str, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strtrim(char const *s1, char const *set);

/* end get_next_line function */

#endif