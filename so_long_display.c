/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:06:48 by mjong             #+#    #+#             */
/*   Updated: 2024/05/22 16:49:17 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_makemap(char indicator, t_game *game, int x, int y)
{
	x *= 100;
	y *= 100;
	if (indicator == '0')
		mlx_image_to_window(game->mlx, game->ffloor, x, y);
	else if (indicator == '1')
		mlx_image_to_window(game->mlx, game->wall, x, y);
	else if (indicator == 'C')
		mlx_image_to_window(game->mlx, game->collectible, x, y);
	else if (indicator == 'E')
		mlx_image_to_window(game->mlx, game->eexit, x, y);
	else if (indicator == 'P')
	{
		mlx_image_to_window(game->mlx, game->player, x, y);
		game->xpos = x;
		game->ypos = y;
	}
}

void	ft_makeimg(t_game *game)
{
	mlx_texture_t	*c;
	mlx_texture_t	*e;
	mlx_texture_t	*f;
	mlx_texture_t	*p;
	mlx_texture_t	*w;

	c = mlx_load_png("./textures/collectible.png");
	e = mlx_load_png("./textures/exit.png");
	f = mlx_load_png("./textures/floor.png");
	p = mlx_load_png("./textures/player.png");
	w = mlx_load_png("./textures/wall.png");
	game->collectible = mlx_texture_to_image(game->mlx, c);
	game->eexit = mlx_texture_to_image(game->mlx, e);
	game->ffloor = mlx_texture_to_image(game->mlx, f);
	game->player = mlx_texture_to_image(game->mlx, p);
	game->wall = mlx_texture_to_image(game->mlx, w);
	mlx_delete_texture(c);
	mlx_delete_texture(e);
	mlx_delete_texture(f);
	mlx_delete_texture(p);
	mlx_delete_texture(w);
}

void	display_map(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	game->mlx = mlx_init(game->width * 100,
			game->ylength * 100, "FIFA25", true);
	ft_makeimg(game);
	while (y != game->ylength && x != game->width)
	{
		while (x != game->width)
		{
			ft_makemap(game->two_d_map[y][x], game, x, y);
			x++;
		}
		y++;
		x = 0;
	}
}
