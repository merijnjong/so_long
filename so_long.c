/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:52:55 by mjong             #+#    #+#             */
/*   Updated: 2024/01/24 18:12:42 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

typedef struct
{
	int	xpos;
	int	ypos;
	int	width;
	int	height;
} Player;

mlx_t *mlx;
mlx_image_t *playeroneimg;
mlx_image_t *floorimg;

// typedef struct mlx_image
// {
// 	const uint32_t	width;
// 	const uint32_t	height;
// 	uint8_t			*pixels;
// 	mlx_instance_t	*instances;
// 	int32_t			count;
// 	bool			enabled;
// 	void			*context;
// } collectibleimg;

void move_player(Player *vader, uint32_t xdir, uint32_t ydir)
{
    uint32_t prevxdir = vader->xpos;
	uint32_t prevydir = vader->ypos;
	mlx_image_to_window(mlx, floorimg, prevxdir, prevydir);
	vader->xpos += xdir;
    vader->ypos += ydir;
	printf("xpos: %d\n", vader->xpos);
	printf("ypos: %d\n", vader->ypos);
}

void ft_hooks(mlx_key_data_t keydata, Player *vader)
{
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
        uint32_t xdir;
		uint32_t ydir;
		
		xdir = 0;
		ydir = 0;
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
        move_player(vader, xdir, ydir);
		mlx_image_to_window(mlx, playeroneimg, vader->xpos, vader->ypos);
    }
	// printf("Key pressed: %c\n", keydata.key);
}

void ft_textures(mlx_t *mlx, char *texture)
{
	if (ft_strcmp(texture, "collectible") == 0)
	{
        mlx_texture_t *collectible = mlx_load_png("./assets/collectible.png");
        mlx_image_t *collectibleimg = mlx_texture_to_image(mlx, collectible);
        mlx_image_to_window(mlx, collectibleimg, 0, 0);
    }
    if (ft_strcmp(texture, "eexit") == 0)
	{
        mlx_texture_t *eexit = mlx_load_png("./assets/exit.png");
        mlx_image_t *exitimg = mlx_texture_to_image(mlx, eexit);
        mlx_image_to_window(mlx, exitimg, 0, 0);
    }
    if (ft_strcmp(texture, "floor") == 0)
	{
        mlx_texture_t *floor = mlx_load_png("./assets/floor.png");
        mlx_image_t *floorimg = mlx_texture_to_image(mlx, floor);
        mlx_image_to_window(mlx, floorimg, 0, 0);
    }
    if (ft_strcmp(texture, "player") == 0)
	{
        mlx_texture_t *player = mlx_load_png("./assets/player.png");
        mlx_image_t *playerimg = mlx_texture_to_image(mlx, player);
        mlx_image_to_window(mlx, playerimg, 0, 0);
    }
    if (ft_strcmp(texture, "wall") == 0)
	{
        mlx_texture_t *wall = mlx_load_png("./assets/wall.png");
        mlx_image_t *wallimg = mlx_texture_to_image(mlx, wall);
        mlx_image_to_window(mlx, wallimg, 0, 0);
    }
}

void	ft_makemap(mlx_t *mlx)
{
	int	fd;
	int i;
	char *line;
	
	fd = open("swmap.ber", O_RDONLY);
	i = 0;
	while (i < 4)
	{
		line = get_next_line(fd);
		if (ft_strcmp(line, "C") == 0)
			ft_textures(mlx, "collectible");
		if (ft_strcmp(line, "E") == 0)
			ft_textures(mlx, "eexit");
		if (ft_strcmp(line, "0") == 0)
			ft_textures(mlx, "floor");
		if (ft_strcmp(line, "P") == 0)
			ft_textures(mlx, "player");
		if (ft_strcmp(line, "1") == 0)
			ft_textures(mlx, "wall");
		free(line);
		i++;
	}
	close(fd);
}

int32_t main(void)
{
	// mlx_t *mlx;
	Player vader = {350, 350, 350, 350};

	mlx = mlx_init(2100, 1400, "starwars", true);
	ft_makemap(mlx);
	mlx_texture_t *playerone = mlx_load_png("./assets/player.png");
   	playeroneimg = mlx_texture_to_image(mlx, playerone);
	mlx_image_to_window(mlx, playeroneimg, vader.xpos, vader.ypos);
	mlx_texture_t *floor = mlx_load_png("./assets/floor.png");
	floorimg = mlx_texture_to_image(mlx, floor);
	mlx_key_hook(mlx, (void *)&ft_hooks, &vader);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_FAILURE);
}
