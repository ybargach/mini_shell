/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 14:15:52 by ybargach          #+#    #+#             */
/*   Updated: 2023/06/11 14:55:19 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo_space(t_builtin *arr)
{
	arr->d = 1;
	if (strncmp(arr->phrase[0], "-n", 2) == 0)
	{
		arr->b = 1;
		while (arr->phrase[0][arr->b])
		{
			if (arr->phrase[0][arr->b] != 'n')
				arr->c++;
			arr->b++;
		}
		if (arr->c == 0)
			arr->d = 0;
		else
			arr->d = 1;
	}
	return (arr->d);
}

void	print_echo(t_builtin *arr)
{
	while (arr->a < arr->args - 1)
	{
		printf("%s", arr->phrase[arr->a]);
		if (arr->a != arr->args - 1)
			printf(" ");
		arr->a++;
	}
	if (arr->space == 1)
		printf("\n");
}

void	builtin_echo(char **av, int args, t_builtin	*arr)
{
	arr->phrase = av;
	arr->args = args;
	arr->a = 0;
	if (arr->phrase[0] == NULL)
	{
		write(1, "\n", 1);
		return ;
	}
	arr->space = echo_space(arr);
	if (arr->space == 1)
		arr->a = 0;
	else
		arr->a = 1;
	print_echo(arr);
}
