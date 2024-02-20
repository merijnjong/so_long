/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:53:38 by mjong             #+#    #+#             */
/*   Updated: 2024/02/20 17:45:28 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_mapcheck(t_game *game)
{
	if (game->colnum < 1 || game->exinum != 1 || game->planum != 1)
		return (0);
	else
		return (1);
}

void ft_exitgame(t_game *game)
{
	free(game->two_d_map);
	mlx_terminate(game->mlx);
}
