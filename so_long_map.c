/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:06:48 by mjong             #+#    #+#             */
/*   Updated: 2024/05/21 14:35:19 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_makemap3(char indicator, t_game *game, int x, int y)
{
	x *= 100;
	y *= 100;
	if (indicator == 'C')
	{
		mlx_image_to_window(game->mlx, game->collectible, x, y);
		game->colnum += 1;
	}
	else if (indicator == 'E')
	{
		mlx_image_to_window(game->mlx, game->eexit, x, y);
		game->exinum += 1;
	}
	else if (indicator == 'P')
	{
		mlx_image_to_window(game->mlx, game->player, x, y);
		game->planum += 1;
		game->xpos = x;
		game->ypos = y;
	}
	else
		return (1);
	return (0);
}

int	ft_makemap2(char indicator, t_game *game, int x, int y)
{
	x *= 100;
	y *= 100;
	if (indicator == '0')
	{
		mlx_image_to_window(game->mlx, game->ffloor, x, y);
		game->flonum += 1;
	}
	else if (indicator == '1')
		mlx_image_to_window(game->mlx, game->wall, x, y);
	else
		return (1);
	return (0);
}

int	ft_makemap(char indicator, t_game *game, int x, int y)
{
	int	result;

	result = 0;
	if (indicator == '0' || indicator == '1')
		result = ft_makemap2(game->two_d_map[y][x], game, x, y);
	else
		result = ft_makemap3(game->two_d_map[y][x], game, x, y);
	return (result);
}

int	display_map(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (game->two_d_map[0][game->width])
		game->width++;
	game->mlx = mlx_init(game->width * 100,
			game->ylength * 100, "FIFA25", true);
	ft_makeimg(game);
	while (y != game->ylength && x != game->width)
	{
		while (x != game->width)
		{
			if (ft_makemap(game->two_d_map[y][x], game, x, y) == 1)
				return (1);
			x++;
		}
		y++;
		game->height++;
		x = 0;
	}
	return (0);
}
