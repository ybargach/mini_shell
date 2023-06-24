/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:37:31 by oait-bad          #+#    #+#             */
/*   Updated: 2023/06/11 15:46:08 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
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

typedef struct s_env
{
	char	*name;
	char	*value;
	struct s_env *next;
}	t_env;

typedef struct s_builtin
{
	int		a;
	int		b;
	int		c;
	int		d;
	int		args;
	int		space;
	int		new_line;
	char	**phrase;
	char	*name;
	char	*new_name;
	char	*line;
	char	*value;
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
	char			**args;
	char			**envp;
	char			*cmd;
	struct s_cmd	*next;
}				t_cmd;

 /* start builtin function */

void	builtin_cd(char **av);
void	builtin_pwd(void);
int		echo_space(t_builtin *arr);
void	print_echo(t_builtin *arr);
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

int		check_tokens(t_lexer *lexer, t_lexer **token);
int		check_quotes(t_lexer *lexer, t_lexer **token);
t_lexer	*the_lexer(char *input);
char	*check_words(t_lexer *lexer, int *index);
int		node_init(t_lexer **token);
char	**get_env(char **env);
char	**dollar_sign(char **args, char **envp);
char	*get_env_value(char *key, char **env);
char	*get_env_key(char *input);
char	*delete_quotes(char *str);
char	*expand_inside_quotes(char *str);
char	**get_env(char **env);
void	handle_redirections(t_cmd *cmd);

#endif