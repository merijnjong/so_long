/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:52:55 by mjong             #+#    #+#             */
/*   Updated: 2024/01/25 14:50:56 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// mlx_t *mlx;
// mlx_image_t *playeroneimg;
// mlx_image_t *floorimg;

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

void	move_player(Player *vader, uint32_t xdir, uint32_t ydir)
{
	// uint32_t	prevxdir = vader->xpos;
	// uint32_t	prevydir = vader->ypos;
	// Assets textures = ft_textures();

	// mlx_image_to_window(mlx, mlx_texture_to_image(mlx, textures.floor), prevxdir, prevydir);
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
	mlx_t *mlx = player->mlx;
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
		move_player(player, xdir, ydir);
		mlx_image_to_window(mlx, mlx_texture_to_image(mlx, textures.player), player->xpos, player->ypos);
	}
}

void	ft_makemap(mlx_t *mlx)
{
	int		fd;
	int		i;
	char	*line;

	Assets textures = ft_textures();
	fd = open("swmap.ber", O_RDONLY);
	i = 0;
	while (i < 4)
	{
		line = get_next_line(fd);
		if (ft_strcmp(line, "C") == 0)
			mlx_image_to_window(mlx, mlx_texture_to_image(mlx, textures.collectible), 0, 0);
		if (ft_strcmp(line, "E") == 0)
			mlx_image_to_window(mlx, mlx_texture_to_image(mlx, textures.eexit), 0, 0);
		if (ft_strcmp(line, "0") == 0)
			mlx_image_to_window(mlx, mlx_texture_to_image(mlx, textures.floor), 0, 0);
		if (ft_strcmp(line, "P") == 0)
			mlx_image_to_window(mlx, mlx_texture_to_image(mlx, textures.player), 0, 0);
		if (ft_strcmp(line, "1") == 0)
			mlx_image_to_window(mlx, mlx_texture_to_image(mlx, textures.wall), 0, 0);
		free(line);
		i++;
	}
	close(fd);
}

int32_t	main(void)
{
	mlx_t *mlx;
	
	mlx = mlx_init(2100, 1400, "starwars", true);
	Player player = {350, 350, 350, 350, mlx};
	Assets textures = ft_textures();

	ft_makemap(mlx);
	mlx_image_to_window(mlx, mlx_texture_to_image(mlx, textures.player), player.xpos, player.ypos);
	mlx_key_hook(mlx, (void *)&ft_hooks, &player);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_FAILURE);
}
