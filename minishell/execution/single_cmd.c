/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 10:37:13 by ybargach          #+#    #+#             */
/*   Updated: 2023/06/21 14:47:23 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	access_single_cmd(char *cmd, t_builtin *arr)
{
	arr->b = 1;
	arr->cmd = ft_split(cmd, ' ');
	arr->a = 0;
	while (arr->full_path && arr->full_path[arr->b])
	{
		arr->fcmd = ft_strjoin_exe(arr->full_path[arr->b], arr->cmd[0]);
		if (access(arr->fcmd, X_OK) == 0)
			break ;
		free (arr->fcmd);
		arr->b++;
	}
	execve_cmd(arr);
}

void	single_cmd(char *cmd, t_builtin *arr)
{
	if ((access(cmd, X_OK) == 0 && strncmp(cmd, "./", 2) == 0)
		|| strncmp(cmd, "/", 1) == 0
		|| strncmp(cmd, "./", 2) == 0)
	{
		arr->cmd = ft_split(cmd, ' ');
		execve_path_cmd(cmd, arr);
	}
	else
		access_single_cmd(cmd, arr);
}

void	welcome_to_single_excute(char **args, t_env **new_env, t_builtin *arr)
{
	arr->space = size_list(new_env, arr);
	arr->env = put_env_array(new_env, arr, arr->space);
	arr->pid = fork();
	if (arr->pid == -1)
		perror("fork: ");
	if (arr->pid == 0)
		single_cmd(*args, arr);
	else
		wait(NULL);
}

void	check_single_cmd(char **toke, char **ag, t_env *new_env, t_builtin *arr)
{
	arr->full_path = check_env_path(&new_env, arr);
	if (strcmp(toke[0], "pwd") == 0)
		builtin_pwd();
	else if (strcmp(toke[0], "cd") == 0)
		builtin_cd(ag);
	else if (strcmp(toke[0], "env") == 0)
		print_env(new_env);
	else if (strcmp(toke[0], "export") == 0)
		builtin_export(new_env, ag, arr);
	else if (strcmp(toke[0], "echo") == 0)
		builtin_echo(ag, arr->args, arr);
	else if (strcmp(toke[0], "unset") == 0)
		builtin_unset(new_env, arr, ag);
	else if (strcmp(toke[0], "<<") == 0)
		single_here_doc(arr, ag);
	else
		welcome_to_single_excute(toke, &new_env, arr);
}

// void	builtin_child(char *input, t_env *new_env, t_builtin *arr)
// {
// 	char	**args;
// 	char	**token;
// 	t_pipe *cmd;
// 	//int a = 0;
// 	arr->a = 0;
// 	arr->b = 1;
// 	arr->args = 0;
// 	token = ft_split(input, ' ');
// 	while (token[arr->args])
// 		arr->args++;
// 	args = malloc(sizeof(char *) * arr->args);
// 	while (token[arr->b])
// 	{
// 		args[arr->a] = ft_strdup(token[arr->b]);
// 		arr->b++;
// 		arr->a++;
// 	}
// 	args[arr->a] = NULL;
// 	// if (a == 1)
// 	// 	check_single_cmd(token, args, new_env, arr);
// 	// else
// 	// {
// 		cmd = create_cmd_list(input);
// 		check_cmd(&cmd, arr, new_env);
// 	// }
// }

int main(int ac, char **av, char **env)
{
	char	*input;
	t_env	*head;
	t_env	*new_env;
	t_builtin	*arr;
	t_pipe *cmd;

	head = NULL;
	arr = (t_builtin *)malloc(sizeof(t_builtin));
	new_env = builtin_env(env, arr, head);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			return 0;
		cmd = create_cmd_list(input);
		check_cmd(&cmd, arr, new_env);
	}
	printf("%s\n %d\n", *av, ac);
}
