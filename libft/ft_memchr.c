/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:10:58 by mjong             #+#    #+#             */
/*   Updated: 2023/10/25 13:34:34 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*src;
	unsigned char		ch;

	i = 0;
	src = (const unsigned char *)s;
	ch = (unsigned char)c;
	while (i < n)
	{
		if (src[i] == ch)
			return ((void *)src + i);
		i++;
	}
	return (0);
}
