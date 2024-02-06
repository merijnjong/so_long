/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:20:51 by mjong             #+#    #+#             */
/*   Updated: 2024/02/06 18:42:01 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_makeimg(struct t_data *game)
{
	mlx_texture_t	*c;
	mlx_texture_t	*e;
	mlx_texture_t	*f;
	mlx_texture_t	*p;
	mlx_texture_t	*w;

	c = mlx_load_png("./assets/collectible.png");
	e = mlx_load_png("./assets/exit.png");
	f = mlx_load_png("./assets/floor.png");
	p = mlx_load_png("./assets/player.png");
	w = mlx_load_png("./assets/wall.png");
	game->collectible = mlx_texture_to_image(game->mlx, c);
	game->eexit = mlx_texture_to_image(game->mlx, e);
	game->ffloor = mlx_texture_to_image(game->mlx, f);
	game->player = mlx_texture_to_image(game->mlx, p);
	game->wall = mlx_texture_to_image(game->mlx, w);
}

void	move_player(struct t_data *game, uint32_t xdir, uint32_t ydir)
{
	uint32_t	prevxdir;
	uint32_t	prevydir;

	prevxdir = game->xpos;
	prevydir = game->ypos;
	mlx_image_to_window(game->mlx, game->ffloor, prevxdir, prevydir);
	game->xpos += xdir;
	game->ypos += ydir;
	printf("xpos: %d\n", game->xpos);
	printf("ypos: %d\n", game->ypos);
	// if (game->xpos != game->wall || game->ypos != game->wall)
		mlx_image_to_window(game->mlx, game->player, game->xpos, game->ypos);
}

void	ft_hooks(mlx_key_data_t keydata, struct t_data *game)
{
	uint32_t	xdir;
	uint32_t	ydir;

	xdir = 0;
	ydir = 0;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
		{
			puts("EXIT");
			exit(EXIT_SUCCESS);
		}
		if (keydata.key == MLX_KEY_W)
			ydir = -100;
		if (keydata.key == MLX_KEY_A)
			xdir = -100;
		if (keydata.key == MLX_KEY_S)
			ydir = 100;
		if (keydata.key == MLX_KEY_D)
			xdir = 100;
		move_player(game, xdir, ydir);
	}
}

void	ft_makemap(char *map, struct t_data *game, int x, int y)
{
	while (*map != '\n' && *map != '\0')
	{
		if (*map == 'C')
		{
			mlx_image_to_window(game->mlx, game->collectible, x, y);
			game->colnum += 1;
		}
		if (*map == 'E')
		{
			mlx_image_to_window(game->mlx, game->eexit, x, y);
			game->exinum += 1;
		}
		if (*map == 'P')
		{
			mlx_image_to_window(game->mlx, game->player, x, y);
			game->planum += 1;
		}
		if (*map == '0')
			mlx_image_to_window(game->mlx, game->ffloor, x, y);
		if (*map == '1')
			mlx_image_to_window(game->mlx, game->wall, x, y);
		map++;
		x += 100;
	}
}

void	ft_filetomap(struct t_data *game)
{
	int		x;
	int		y;
	int		fd;
	int		check;
	char	*map;

	check = 0;
	y = 0;
	fd = open("swmap.ber", O_RDONLY);
	while (!check)
	{
		map = get_next_line(fd);
		if (!map || map[0] == '\0')
		{
			check = 1;
			free(map);
			break ;
		}
		x = 0;
		ft_makemap(map, game, x, y);
		y += 100;
		free(map);
	}
	close(fd);
}

int32_t	main(void)
{
	mlx_t	*mlx;
	mlx = mlx_init(2100, 1400, "starwars", true);
	Game game = {100, 100, 100, 100, 0, 0, 0, mlx, NULL, NULL, NULL, NULL, NULL};

	ft_makeimg(&game);
	ft_filetomap(&game);
	if (ft_mapcheck(game) == 0)
	{
		puts("INVALID MAP");
		exit(EXIT_SUCCESS);
	}
	mlx_key_hook(mlx, (void *)&ft_hooks, &game);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
