/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 10:48:43 by ybargach          #+#    #+#             */
/*   Updated: 2023/06/14 10:49:33 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execve_path_cmd(char *cmd, t_builtin *arr)
{
	arr->exe = execve(cmd, arr->cmd, arr->env);
	if (arr->exe == -1)
	{
		ft_putstr_fd((*arr->cmd), 2);
		ft_putstr_fd(": Command not found\n", 2);
	}
	exit(127);
}

void	execve_cmd(t_builtin *arr)
{
	arr->exe = execve(arr->fcmd, arr->cmd, arr->env);
	if (arr->exe == -1)
	{
		ft_putstr_fd((*arr->cmd), 2);
		ft_putstr_fd(": Command not found\n", 2);
	}
	exit(127);
}
