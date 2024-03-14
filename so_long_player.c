/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:04:21 by mjong             #+#    #+#             */
/*   Updated: 2024/03/14 15:10:11 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_player3(t_game *game, uint32_t xdir, uint32_t ydir)
{
	uint32_t	prevxdir;
	uint32_t	prevydir;

	prevxdir = game->xpos;
	prevydir = game->ypos;
	game->xpos += xdir;
	game->ypos += ydir;
	mlx_image_to_window(game->mlx, game->eexit, prevxdir, prevydir);
	mlx_image_to_window(game->mlx, game->player, game->xpos, game->ypos);
}

void	move_player2(t_game *game, uint32_t xdir, uint32_t ydir)
{
	uint32_t	prevxdir;
	uint32_t	prevydir;

	prevxdir = game->xpos;
	prevydir = game->ypos;
	game->xpos += xdir;
	game->ypos += ydir;
	mlx_image_to_window(game->mlx, game->ffloor, prevxdir, prevydir);
	mlx_image_to_window(game->mlx, game->player, game->xpos, game->ypos);
	game->movecount += 1;
	ft_printf("Number of movements: %d\n", game->movecount);
}

void	move_player_e(t_game *game, uint32_t xdir, uint32_t ydir)
{
	int	x;
	int	y;

	x = (game->xpos + xdir) / 100;
	y = (game->ypos + ydir) / 100;
	if (game->two_d_map[y][x] == 'E' && game->colnum != 0)
		move_player2(game, xdir, ydir);
	else if (game->two_d_map[y][x] == 'E' && game->colnum == 0)
	{
		move_player2(game, xdir, ydir);
		ft_printf("YOU WIN!\n");
		ft_exitgame(game);
	}
}

void	move_player(t_game *game, uint32_t xdir, uint32_t ydir)
{
	int			x;
	int			y;
	uint32_t	prevxdir;
	uint32_t	prevydir;

	x = (game->xpos + xdir) / 100;
	y = (game->ypos + ydir) / 100;
	prevxdir = game->xpos;
	prevydir = game->ypos;
	if (game->two_d_map[prevydir / 100][prevxdir / 100] == 'E')
		move_player3(game, xdir, ydir);
	else if (game->two_d_map[y][x] == '0' || game->two_d_map[y][x] == 'P')
		move_player2(game, xdir, ydir);
	else if (game->two_d_map[y][x] == 'C')
	{
		game->colnum--;
		move_player2(game, xdir, ydir);
		game->two_d_map[y][x] = '0';
	}
	else if (game->two_d_map[y][x] == 'E')
		move_player_e(game, xdir, ydir);
}

void	ft_hooks(mlx_key_data_t keydata, t_game *game)
{
	uint32_t	xdir;
	uint32_t	ydir;

	xdir = 0;
	ydir = 0;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
		{
			ft_printf("EXITED GAME\n");
			ft_exitgame(game);
		}
		if (keydata.key == MLX_KEY_W)
			ydir = -100;
		if (keydata.key == MLX_KEY_A)
			xdir = -100;
		if (keydata.key == MLX_KEY_S)
			ydir = 100;
		if (keydata.key == MLX_KEY_D)
			xdir = 100;
		if (xdir || ydir)
			move_player(game, xdir, ydir);
	}
}
