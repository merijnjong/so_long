/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:20:51 by mjong             #+#    #+#             */
/*   Updated: 2024/02/08 16:11:58 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_player(struct t_data *game, uint32_t xdir, uint32_t ydir)
{
	uint32_t	prevxdir;
	uint32_t	prevydir;
	char		nextchar;

	prevxdir = game->xpos;
	prevydir = game->ypos;
	nextchar = game->two_d_map[game->ypos + ydir][game->xpos + xdir];
	// printf("%c\n", nextchar);
	if (nextchar != '1')
	{
		game->xpos += xdir;
		game->ypos += ydir;
		printf("xpos: %d\n", game->xpos);
		printf("ypos: %d\n", game->ypos);
		mlx_image_to_window(game->mlx, game->ffloor, prevxdir, prevydir);
		mlx_image_to_window(game->mlx, game->player, game->xpos, game->ypos);
	}
	if (nextchar == '1')
		ft_printf("CANNOT MOVE THERE IS A WALL THERE!\n");
	if (nextchar == 'C')
		ft_printf("PICKED UP COLLECTIBLE!\n");		
	if (nextchar == 'E')
	{
		mlx_close_window(game->mlx);
		ft_printf("YOU MADE IT!\n");
	}
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
			mlx_close_window(game->mlx);
			ft_printf("EXITED GAME SUCCESFULLY\n");
		}
		if (keydata.key == MLX_KEY_W)
			ydir = -100;
		if (keydata.key == MLX_KEY_A)
			xdir = -100;
		if (keydata.key == MLX_KEY_S)
			ydir = 100;
		if (keydata.key == MLX_KEY_D)
			xdir = 100;
		if(xdir || ydir)
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

int display_map(struct t_data *game)
{
	int i = 0;
	int j = 0;
	int x = 0;
	int y =	0;
	int width = 0;
	while(game->two_d_map[0][width])
		width++;
	while(j != game->ylength && i != width)
	{
		while(i != width)
		{
			ft_makemap(game->two_d_map[j][i], game, x, y);
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
	map = NULL;
	if (fd < 0)
		return (NULL);
	while(1)
	{
		temp = get_next_line(fd);
		if(!temp)
			break;
		game->ylength++;
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
	Game game = {100, 100, 100, 100, 0, 0, 0, 0, mlx, NULL, NULL, NULL, NULL, NULL, NULL};
	ft_makeimg(&game);
	char *map = ft_filetomap(&game);
	game.two_d_map = ft_split(map, '\n');
	display_map(&game);
	if (ft_mapcheck(game) == 0)
	{
		mlx_close_window(game.mlx);
		ft_printf("ERROR: INVALID MAP");
	}
	mlx_key_hook(mlx, (void *)&ft_hooks, &game);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return 0;
}
