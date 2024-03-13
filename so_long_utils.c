/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:53:38 by mjong             #+#    #+#             */
/*   Updated: 2024/03/13 16:27:43 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_mapcheck(t_game *game)
{
	int	result;

	result = game->colnum + game->exinum + game->planum + game->flonum;
	if (result != game->countc)
		return (0);
	if (game->colnum < 1 || game->exinum != 1 || game->planum != 1)
		return (0);
	else
		return (1);
}

void	ft_exitgame(t_game *game)
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
