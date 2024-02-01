/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:53:38 by mjong             #+#    #+#             */
/*   Updated: 2024/02/01 16:07:43 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

int	ft_mapcheck(char *map)
{
	int	C;
	int	E;
	int P;
	int i;

	C = 0;
	E = 0;
	P = 0;
	i = 0;
	while (map[i] != '\0')
	{
		if (map[i] == 'C')
			C++;
		if (map[i] == 'E')
			E++;
		if (map[i] == 'P')
			P++;
		i++;
	}
	if (C < 1 || E != 1 || P != 1)
		return (0);
	else 
		return (1);
}
