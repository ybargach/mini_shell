/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 21:20:38 by ybargach          #+#    #+#             */
/*   Updated: 2023/06/21 17:47:01 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_multi_cmd(t_pipe **cmd, t_builtin *arr)
{
	if ((access((*cmd)->input, X_OK) == 0 && strncmp((*cmd)->input, "./", 2) == 0)
		|| strncmp((*cmd)->input, "/", 1) == 0
		|| strncmp((*cmd)->input, "./", 2) == 0)
	{
		arr->cmd = ft_split((*cmd)->input, ' ');
		execve_path_cmd((*cmd)->input, arr);
	}
	else
		access_multi_cmd(cmd, arr);
}

void	access_multi_cmd(t_pipe **cmd, t_builtin *arr)
{
	arr->b = 0;
	arr->cmd = ft_split((*cmd)->input, ' ');
	arr->a = 0;
	while (arr->full_path && arr->full_path[arr->b])
	{
		arr->fcmd = ft_strjoin_exe(arr->full_path[arr->b], arr->cmd[0]);
		if (access(arr->fcmd, X_OK) == 0)
			break ;
		free(arr->fcmd);
		arr->b++;
	}
	execve_cmd_test(arr);
}

void	execve_cmd_test(t_builtin *arr)
{
	close(arr->p[0]);
	close(arr->p[1]);
	arr->exe = execve(arr->fcmd, arr->cmd, arr->env);
	if (arr->exe == -1)
	{
		ft_putstr_fd((*arr->cmd), 2);
		ft_putstr_fd(": Command not found\n", 2);
	}
	exit(127);
}

void	execve_cmd_last(t_builtin *arr)
{
	close(arr->p[0]);
	close(arr->p[1]);
	arr->exe = execve(arr->fcmd, arr->cmd, arr->env);
	if (arr->exe == -1)
	{
		ft_putstr_fd((*arr->cmd), 2);
		ft_putstr_fd(": Command not found\n", 2);
	}
	exit(127);
}

void	access_multi_cmd_last(t_pipe **cmd, t_builtin *arr)
{
	arr->b = 0;
	arr->cmd = ft_split((*cmd)->input, ' ');
	arr->a = 0;
	while (arr->full_path && arr->full_path[arr->b])
	{
		arr->fcmd = ft_strjoin_exe(arr->full_path[arr->b], arr->cmd[0]);
		if (access(arr->fcmd, X_OK) == 0)
			break ;
		free(arr->fcmd);
		arr->b++;
	}
	execve_cmd_last(arr);
}

void	exec_multi_last_cmd(t_pipe **cmd, t_builtin *arr)
{
	if ((access((*cmd)->input, X_OK) == 0 && strncmp((*cmd)->input, "./", 2) == 0)
		|| strncmp((*cmd)->input, "/", 1) == 0
		|| strncmp((*cmd)->input, "./", 2) == 0)
	{
		arr->cmd = ft_split((*cmd)->input, ' ');
		execve_path_cmd((*cmd)->input, arr);
	}
	else
		access_multi_cmd_last(cmd, arr);
}

void	exec_multi_seco_cmd(t_pipe **cmd, t_builtin *arr)
{
	exit(0);
	if ((access((*cmd)->input, X_OK) == 0 && strncmp((*cmd)->input, "./", 2) == 0)
		|| strncmp((*cmd)->input, "/", 1) == 0
		|| strncmp((*cmd)->input, "./", 2) == 0)
	{
		arr->cmd = ft_split((*cmd)->input, ' ');
		execve_path_cmd((*cmd)->input, arr);
	}
	else
		execve_cmd_test(arr);
}

void	welcome_to_multi(t_pipe **cmd, t_builtin *arr, t_env *new_env)
{
	char	**toke;
	char	**args;

	arr->a = 0;
	arr->b = 1;
	arr->args = 0;
	toke = ft_split((*cmd)->input, ' ');
	while (toke[arr->args])
		arr->args++;
	args = malloc(sizeof(char *) * arr->args);
	while (toke[arr->b])
	{
		args[arr->a] = ft_strdup(toke[arr->b]);
		arr->b++;
		arr->a++;
	}
	args[arr->a] = NULL;
	if (strcmp(toke[0], "pwd") == 0)
		builtin_pwd();
	else if (strcmp(toke[0], "cd") == 0)
		builtin_cd(args);
	else if (strcmp(toke[0], "env") == 0)
		print_env(new_env);
	else if (strcmp(toke[0], "export") == 0)
		builtin_export(new_env, args, arr);
	else if (strcmp(toke[0], "echo") == 0)
		builtin_echo(args, arr->args, arr);
	else if (strcmp(toke[0], "unset") == 0)
		builtin_unset(new_env, arr, args);
	else if (arr->c == 0)
		first_cmd(cmd, arr);
	else if ((*cmd)->next == NULL)
		last_cmd(cmd, arr);
	else
		second_cmd(cmd, arr);
}

void	last_cmd(t_pipe **cmd, t_builtin *arr)
{
	arr->a = 0;
	if (pipe(arr->p) == -1)
		perror("pipe error");
	arr->pid = fork();
	if (arr->pid == -1)
		perror("fork");
	if (arr->pid == 0)
		exec_multi_last_cmd(cmd, arr);
	else
	{
		dup(arr->p[0]);
		close(arr->p[1]);
		close(arr->p[0]);
		wait(NULL);
	}
}

void	second_cmd(t_pipe **cmd, t_builtin *arr)
{
	arr->a = 0;
	if (pipe(arr->p) == -1)
		perror("pipe error");
	arr->pid = fork();
	if (arr->pid == -1)
		perror("fork");
	if (arr->pid == 0)
	{
		dup2(arr->p[1], 1);
		exec_multi_seco_cmd(cmd, arr);
	}
	else
	{
		dup2(arr->p[0], 0);
		close(arr->p[1]);
		close(arr->p[0]);
		wait(NULL);
	}
}

void	first_cmd(t_pipe **cmd, t_builtin *arr)
{
	arr->a = 0;
	if (pipe(arr->p) == -1)
		perror("pipe error");
	arr->pid = fork();
	if (arr->pid == -1)
		perror("fork");
	if (arr->pid == 0)
	{
		dup2(arr->p[1], 1);
		exec_multi_cmd(cmd, arr);
	}
	else
	{
		close(arr->p[1]);
		wait(NULL);
	}
}

void	check_cmd(t_pipe **cmd, t_builtin *arr, t_env *new_env)
{
	arr->space = size_list(&new_env, arr);
	arr->env = put_env_array(&new_env, arr, arr->space);
	arr->full_path = check_env_path(&new_env, arr);
	arr->c = 0;
	while ((*cmd))
	{
		welcome_to_multi(cmd, arr, new_env);
		arr->c++;
		*cmd = (*cmd)->next;
	}
}
