/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:20:51 by mjong             #+#    #+#             */
/*   Updated: 2024/02/07 17:57:07 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
			mlx_close_window(game->mlx);
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

void	ft_makemap(char indicator, struct t_data *game, int x, int y)
{
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
	}
	if (indicator == '0')
		mlx_image_to_window(game->mlx, game->ffloor, x, y);
	if (indicator == '1')
		mlx_image_to_window(game->mlx, game->wall, x, y);
}

int display_map(char **map, struct t_data *game)
{
	int i = 0;
	int j = 0;
	int x = 0;
	int y =	0;
	int length = 0;
	while(map[0][length])
	{
		length++;
	}
	while(j != game->ylength && i != length)
	{
		while(i != length)
		{
			ft_makemap(map[j][i], game, x, y);
			x += 100;
			i++;
		}
		j++;
		x = 0;
		y += 100;
		i = 0;
	}
	return (1);
}

char 	*ft_filetomap(struct t_data *game)
{
	int		fd;
	char	*map;
	char	*temp;
	
	fd = open("swmap.ber", O_RDONLY);
	while(1)
	{
		temp = get_next_line(fd);
		if(!temp)
			break;
		game->ylength++;
		printf("%s\n", temp);
		map = ft_strjoin2(map, temp);
	}
	close(fd);
	return (map);
}

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

int32_t	main(void)
{
	mlx_t	*mlx;
	mlx = mlx_init(2100, 1700, "starwars", true);
	Game game = {100, 100, 100, 100, 0, 0, 0, 0, mlx, NULL, NULL, NULL, NULL, NULL};
	// struct t_data game = {0};
	// int i = 0;
	// int j = 0;
	ft_makeimg(&game);
	char *map = ft_filetomap(&game);
	char **two_d_map = ft_split(map, '\n');
	display_map(two_d_map, &game);
	if (ft_mapcheck(game) == 0)
		mlx_close_window(game.mlx);
	mlx_key_hook(mlx, (void *)&ft_hooks, &game);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return 0;
}
