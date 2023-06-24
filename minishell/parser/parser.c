/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:03:30 by oait-bad          #+#    #+#             */
/*   Updated: 2023/06/21 13:27:58 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_pipe	*init_cmd(char *line)
{
	t_pipe	*cmd;

	cmd = (t_pipe *)malloc(sizeof(t_pipe));
	cmd->input = ft_strdup(line);
	cmd->next = NULL;
	return (cmd);
}

void	skip_whitespaces(char *str)
{
	if (*str == 32 && (*str >= 9 && *str <= 13))
		str++;
}

t_pipe	*create_cmd_list(char *line)
{
	t_pipe	*cmd;
	t_pipe	*head;
	char	**pipes;
	int		i;

	i = 0;
	pipes = split_by_pipes(&line);
	skip_whitespaces(line);
	cmd = init_cmd(pipes[i]);
	head = cmd;
	while (pipes[++i])
	{
		cmd->next = init_cmd(pipes[i]);
		cmd = cmd->next;
	}
	return (head);
}

// int	check_pipe(char **input)
// {
// 	char	**pipes;
// 	int		i;
// 	int		j;
// 	int		k;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	pipes = (char **)malloc(sizeof(char *) * (ft_strlen(*input) + 1));
// 	while ((*input)[i])
// 	{
// 		if ((*input)[i] == '\'' || (*input)[i] == '\"')
// 		{
// 			i++;
// 			while ((*input)[i] && (*input)[i] != '\'' && (*input)[i] != '\"')
// 				i++;
// 		}
// 		if ((*input)[i] == '|')
// 		{
// 			pipes[j] = ft_substr(*input, k, i - k);
// 			j++;
// 			k = i + 1;
// 		}
// 		i++;
// 	}
// 	pipes[j] = ft_substr(*input, k, i - k);
// 	pipes[j + 1] = 0;
// 	return (pipes);
//}

// main function to test this file in a loop using readline

// int main(int ac, char **av, char **env)
// {
// 	char *line;
// 	t_pipe *cmd;
// 	while (1)
// 	{
// 		line = readline("minishell$ ");
// 		cmd = create_cmd_list(line);
// 		while (cmd)
// 		{
// 			printf("cmd->input = %s\n", cmd->input);
// 			cmd = cmd->next;
// 		}
// 	}
// 	env = NULL;
// 	printf("%d, %s", ac, av[0]);
// 	return (0);
// }