/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_longbackup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:20:51 by mjong             #+#    #+#             */
/*   Updated: 2024/03/06 14:06:35 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_player2(t_game *game, uint32_t xdir, uint32_t ydir)
{
	uint32_t	prevxdir;
	uint32_t	prevydir;

	prevxdir = game->xpos;
	prevydir = game->ypos;
	game->xpos += xdir;
	game->ypos += ydir;
	printf("xpos: %d\n", game->xpos);
	printf("ypos: %d\n", game->ypos);
	mlx_image_to_window(game->mlx, game->ffloor, prevxdir, prevydir);
	mlx_image_to_window(game->mlx, game->player, game->xpos, game->ypos);
}

void	move_player(t_game *game, uint32_t xdir, uint32_t ydir)
{
	uint32_t	prevxdir;
	uint32_t	prevydir;

	prevxdir = game->xpos;
	prevydir = game->ypos;
	int x = (game->xpos + xdir) / 100;
	int y = (game->ypos + ydir) / 100;
	if (game->two_d_map[y][x] != '1')
	{
		if (game->two_d_map[y][x] == 'C')
			game->colnum--;
		if (game->two_d_map[y][x] == 'E' && game->colnum == 0)
			ft_exitgame(game);
		move_player2(game, xdir, ydir);
	}
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
			ft_exitgame(game);
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

void	ft_makemap(char indicator, t_game *game, int x, int y)
{
	x *= 100;
	y *= 100;
	if (indicator == 'C')
	{
		mlx_image_to_window(game->mlx, game->collectible, x, y);
		game->colnum += 1;
	}
	if (indicator == 'E')
	{
		mlx_image_to_window(game->mlx, game->eexit, x, y);
		game->exinum += 1;
	}
	if (indicator == 'P')
	{
		mlx_image_to_window(game->mlx, game->player, x, y);
		game->planum += 1;
		game->xpos = x;
		game->ypos = y;
	}
	if (indicator == '0')
		mlx_image_to_window(game->mlx, game->ffloor, x, y);
	if (indicator == '1')
		mlx_image_to_window(game->mlx, game->wall, x, y);
}

int display_map(t_game *game)
{
	int x = 0;
	int y =	0;
	while (game->two_d_map[0][game->width])
		game->width++;
	// printf("H: %d - W: %d\n", game->ylength, game->width);
	game->mlx = mlx_init(game->width * 100, game->ylength * 100, "starwars", true);
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
	return (1);
}

char	*ft_filetomap(t_game *game)
{
	int		fd;
	char	*map;
	char	*temp;

	fd = open("swmap.ber", O_RDONLY);
	map = NULL;
	if (fd < 0)
		return (NULL);
	while (1)
	{
		temp = get_next_line(fd);
		if (!temp)
			break ;
		game->ylength++;
		map = ft_strjoin2(map, temp);
	}
	close(fd);
	return (map);
}

void	ft_makeimg(t_game *game)
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

void	init(t_game *game)
{
	// game->xpos = 100;
	// game->ypos = 100;
	game->width = 0;
	game->height = 0;
	game->colnum = 0;
	game->exinum = 0;
	game->planum = 0;
	game->ylength = 0;
	game->mlx = NULL;
	game->collectible = NULL;
	game->eexit = NULL;
	game->ffloor = NULL;
	game->player = NULL;
	game->wall = NULL;
	game->two_d_map = NULL;	
}


int32_t	main(void)
{
	t_game	game;
	char	*map;

	init(&game);

	map = ft_filetomap(&game);
	game.two_d_map = ft_split(map, '\n');

	// GRID CHECK
	int i = 0;
	int o = 0;
	printf("\n");
	while (i < 4)
	{
		while (o < 6)
		{
			printf("%c", game.two_d_map[i][o]);
			o++;
		}
		o = 0;
		i++;
		printf("\n");
	}
	// END CHECK
	
	display_map(&game);
	if (ft_mapcheck(&game) == 0)
		ft_exitgame(&game);
	mlx_key_hook(game.mlx, (void *)&ft_hooks, &game);
	mlx_loop(game.mlx);
	free(game.two_d_map);
	mlx_terminate(game.mlx);
	return (0);
}
