/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 14:16:09 by ybargach          #+#    #+#             */
/*   Updated: 2023/06/11 15:18:14 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_unset(t_builtin *arr, char **add)
{
	if (!((add[arr->a][arr->b] >= 'a' && add[arr->a][arr->b] <= 'z')
		|| (add[arr->a][arr->b] >= 'A' && add[arr->a][arr->b] <= 'Z')
		|| (add[arr->a][arr->b] >= '0' && add[arr->a][arr->b] <= '9')
		|| add[arr->a][arr->b] == '_'))
	{
		ft_putstr_fd(add[arr->a], 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		exit(1);
	}
}

void	check_cmd_unset(t_builtin *arr, char **add)
{
	arr->a = 0;
	while (add[arr->a])
	{
		arr->b = 0;
		while (add[arr->a][arr->b])
		{
			check_unset(arr, add);
			arr->b++;
		}
		arr->a++;
	}
}

void	delete_unset(t_env **head, t_builtin *arr)
{
	t_env	*new_node;
	t_env	*delete_node;

	new_node = *head;
	delete_node = NULL;
	arr->new_name = ft_strdup_unset(new_node->name);
	while (new_node != NULL && strcmp(arr->new_name, arr->name) != 0)
	{
		free(arr->new_name);
		delete_node = new_node;
		new_node = new_node->next;
		arr->new_name = ft_strdup_unset(new_node->name);
	}
	free(arr->new_name);
	if (new_node == NULL)
		return ;
	if (delete_node == NULL)
		*head = new_node->next;
	else
		delete_node->next = new_node->next;
	free(new_node->name);
	free(new_node->value);
	free(new_node);
}

void	builtin_check(t_env **head, t_builtin *arr, char **add)
{
	check_cmd_unset(arr, add);
	arr->a = 0;
	while (add[arr->a])
	{
		arr->b = 0;
		while (add[arr->a][arr->b])
		{
			if (add[arr->a][arr->b + 1] == '\0')
			{
				arr->name = ft_substr(add[arr->a], 0, arr->b + 1);
				delete_unset(head, arr);
				break ;
			}
			arr->b++;
		}
		arr->a++;
	}
}

void	builtin_unset(t_env *head, t_builtin *arr, char **add)
{
	if (*add != NULL)
		builtin_check(&head, arr, add);
}

int main(int ac, char **av, char **env)
{
	char *input;
	char **args;
    int num_args;
	char **token;
	t_builtin	*arr;

	arr = (t_builtin *)malloc(sizeof(t_builtin));
	t_env	*head = NULL;
	t_env	*new_env = builtin_env(env, arr, head);
	while (1)
	{
		input = readline("> ");
		if (!input)
			return 0;
		num_args = 0;
		token = ft_split(input, ' ');
		while (token[num_args])
			num_args++;
		arr->b = 1;
		arr->a = 0;
		args = malloc(sizeof(char *) * num_args);
		while (token[arr->b])
		{
			args[arr->a] = ft_strdup(token[arr->b]);
			arr->b++;
			arr->a++;
		}
		args[arr->a] = NULL;
		if (strcmp(token[0], "pwd") == 0)
			builtin_pwd();
		else if (strcmp(token[0], "cd") == 0)
			builtin_cd(args);
		else if (strcmp(token[0], "env") == 0)
			print_env(new_env);
		else if (strcmp(token[0], "export") == 0)
		 	builtin_export(new_env, args, arr);
		else if (strcmp(token[0], "echo") == 0)
			builtin_echo(args, num_args, arr);
		else if (strcmp(token[0], "unset") == 0)
			builtin_unset(new_env, arr, args);
		else
		{
			printf("%s\n", input);
		}
	}
}