/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_longbackup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:52:55 by mjong             #+#    #+#             */
/*   Updated: 2024/02/01 17:20:57 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

typedef struct
{
	int		xpos;
	int		ypos;
	int		width;
	int		height;
	mlx_t	*mlx;
} Player;

typedef struct
{
	mlx_texture_t	*collectible;
	mlx_texture_t	*eexit;
	mlx_texture_t	*floor;
	mlx_texture_t	*player;
	mlx_texture_t	*wall;
} Assets;

Assets	ft_textures(void)
{
	Assets textures =
	{
		.collectible = mlx_load_png("./assets/collectible.png"),
		.eexit = mlx_load_png("./assets/exit.png"),
		.floor = mlx_load_png("./assets/floor.png"),
		.player = mlx_load_png("./assets/player.png"),
		.wall = mlx_load_png("./assets/wall.png"),
	};
	return (textures);
}

void	move_player(mlx_t *mlxp, Player *vader, uint32_t xdir, uint32_t ydir)
{
	uint32_t	prevxdir = vader->xpos;
	uint32_t	prevydir = vader->ypos;
	Assets textures = ft_textures();

	mlx_image_to_window(mlxp, mlx_texture_to_image(mlxp, textures.floor), prevxdir, prevydir);
	vader->xpos += xdir;
	vader->ypos += ydir;
	printf("xpos: %d\n", vader->xpos);
	printf("ypos: %d\n", vader->ypos);
}

void	ft_hooks(mlx_key_data_t keydata, Player *player)
{
	uint32_t	xdir;
	uint32_t	ydir;

	xdir = 0;
	ydir = 0;
	Assets textures = ft_textures();
	mlx_t *mlxp = player->mlx;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
		{
			puts("EXIT");
			exit(EXIT_SUCCESS);
		}
		if (keydata.key == MLX_KEY_W)
			ydir = -350;
		if (keydata.key == MLX_KEY_A)
			xdir = -350;
		if (keydata.key == MLX_KEY_S)
			ydir = 350;
		if (keydata.key == MLX_KEY_D)
			xdir = 350;
		move_player(mlxp, player, xdir, ydir);
		mlx_image_to_window(mlxp, mlx_texture_to_image(mlxp, textures.player), player->xpos, player->ypos);
	}
}

void	ft_makemap(mlx_t *mlx, char *map, Assets textures, int x, int y)
{
	int i;

	i = 0;
	while (map[i] != '\n' && map[i] != '\0')
	{
		if (map[i] == 'C')
			mlx_image_to_window(mlx, mlx_texture_to_image(mlx, textures.collectible), x, y);
		if (map[i] == 'E')
			mlx_image_to_window(mlx, mlx_texture_to_image(mlx, textures.eexit), x, y);
		if (map[i] == '0')
			mlx_image_to_window(mlx, mlx_texture_to_image(mlx, textures.floor), x, y);
		if (map[i] == 'P')
			mlx_image_to_window(mlx, mlx_texture_to_image(mlx, textures.player), x, y);
		if (map[i] == '1')
			mlx_image_to_window(mlx, mlx_texture_to_image(mlx, textures.wall), x, y);
		i++;
		x += 350;
	}
}

void ft_filetomap(mlx_t *mlx, Assets textures)
{
	int x;
	int y;
	int fd;
	int check;
	char *map;

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
			break;
		}
		x = 0;
		ft_makemap(mlx, map, textures, x, y);
		y += 350;
		free(map);
	}
	close(fd);
}

int32_t	main(void)
{
	mlx_t	*mlx;
	
	mlx = mlx_init(2100, 1400, "starwars", true);
	Player player = {350, 350, 350, 350, mlx};
	Assets textures = ft_textures();

	ft_filetomap(mlx, textures);
	mlx_image_to_window(mlx, mlx_texture_to_image(mlx, textures.player), player.xpos, player.ypos);
	mlx_key_hook(mlx, (void *)&ft_hooks, &player);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_FAILURE);
}
