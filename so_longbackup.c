/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_longbackup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:20:51 by mjong             #+#    #+#             */
/*   Updated: 2024/03/13 15:53:23 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	flood_fill(t_game *game, int x, int y)
{
	if (game->two_d_mapcheck[y][x] == '1' || game->two_d_mapcheck[y][x] == 'N')
		return ;
	if (game->two_d_mapcheck[y][x] == 'C')
		game->countc++;
	if (game->two_d_mapcheck[y][x] == 'E')
		game->countc++;
	if (game->two_d_mapcheck[y][x] == 'P')
		game->countc++;
	if (game->two_d_mapcheck[y][x] == '0')
		game->countc++;

	game->two_d_mapcheck[y][x] = 'N';
	flood_fill(game, x + 1, y);
	flood_fill(game, x - 1, y);
	flood_fill(game, x, y + 1);
	flood_fill(game, x, y - 1);
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

void	move_player(t_game *game, uint32_t xdir, uint32_t ydir)
{
	uint32_t	prevxdir;
	uint32_t	prevydir;

	prevxdir = game->xpos;
	prevydir = game->ypos;
	int x = (game->xpos + xdir) / 100;
	int y = (game->ypos + ydir) / 100;
	if (game->two_d_map[y][x] == '0' || game->two_d_map[y][x] == 'P')
		move_player2(game, xdir, ydir);
	if (game->two_d_map[y][x] == 'C')
	{
		game->colnum--;
		move_player2(game, xdir, ydir);
		game->two_d_map[y][x] = '0';
	}
	if (game->two_d_map[y][x] == 'E' && game->colnum == 0)
	{
		move_player2(game, xdir, ydir);
		ft_printf("YOU WIN!\n");
		ft_exitgame(game);
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

int	ft_makemap(char indicator, t_game *game, int x, int y)
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
	else if (indicator == '0')
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

int display_map(t_game *game)
{
	int x = 0;
	int y =	0;
	while (game->two_d_map[0][game->width])
		game->width++;
	game->mlx = mlx_init(game->width * 100, game->ylength * 100, "MOVETHATBOX", true);
	ft_makeimg(game);
	while (y != game->ylength && x != game->width)
	{
		while (x != game->width)
		{
			if (ft_makemap(game->two_d_map[y][x], game, x, y) == 1)
				return(1) ;
			x++;
		}
		y++;
		x = 0;
	}
	return (0);
}

char	*ft_filetomap(t_game *game)
{
	int		fd;
	char	*map;
	char	*temp;

	fd = open("map.ber", O_RDONLY);
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
		free(temp);
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
	
	mlx_delete_texture(c);
	mlx_delete_texture(e);
	mlx_delete_texture(f);
	mlx_delete_texture(p);
	mlx_delete_texture(w);
}

void	init(t_game *game)
{
	game->width = 0;
	game->height = 0;
	game->colnum = 0;
	game->exinum = 0;
	game->planum = 0;
	game->flonum = 0;
	game->ylength = 0;
	game->movecount = 0;
	game->countc = 0;
	game->mlx = NULL;
	game->collectible = NULL;
	game->eexit = NULL;
	game->ffloor = NULL;
	game->player = NULL;
	game->wall = NULL;
	game->two_d_map = NULL;
	game->two_d_mapcheck = NULL;
}

int32_t	main(void)
{
	t_game	game;
	char	*map;

	init(&game);

	map = ft_filetomap(&game);
	game.two_d_map = ft_split(map, '\n');
	game.two_d_mapcheck = ft_split(map, '\n');
	flood_fill(&game, 4, 1);
	free(map);
	if (display_map(&game) == 1 || ft_mapcheck(&game) == 0)
	{
		ft_exitgame(&game);
		ft_printf("Error\nINVALID MAP\n");
		exit(EXIT_FAILURE);
	}
	mlx_key_hook(game.mlx, (void *)&ft_hooks, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (0);
}
