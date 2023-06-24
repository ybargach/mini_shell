/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 17:23:00 by oait-bad          #+#    #+#             */
/*   Updated: 2023/05/27 00:57:36 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t len)
{
	unsigned int	i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	if (str1 == 0 || str2 == 0 || len == 0)
		return (0);
	while (i < len && (str1[i] || str2[i]))
	{
		if (str1[i] > str2[i])
		{
			return (1);
		}
		if (str1[i] < str2[i])
		{
			return (-1);
		}
		i++;
	}
	return (0);
}
