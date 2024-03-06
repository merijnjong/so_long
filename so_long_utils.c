/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:53:38 by mjong             #+#    #+#             */
/*   Updated: 2024/03/06 18:14:43 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_mapcheck(t_game *game)
{
	// int j;
	// int i;
	// int answer;

	// j = 0;
	// i = 0;
	// while (game->two_d_map[j] != NULL && game->two_d_map[j][0] != '\0')
    // 	j++;
	// if (j > 0)
	// {
    // 	while (game->two_d_map[0][i] != '\0')
    //  	   i++;
	// }
	// answer = i * j;
	// ft_printf("%d", answer);
	// if (answer == '\0')
	// 	return (0);
	if (game->colnum < 1 || game->exinum != 1 || game->planum != 1)
		return (0);
	else
		return (1);
}

void ft_exitgame(t_game *game)
{
	int	j;

	j = 0;
	while (game->two_d_map[j])
	{
		free(game->two_d_map[j]);
		j++;
	}
	free(game->two_d_map);
	mlx_close_window(game->mlx);
}
