/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:52:55 by mjong             #+#    #+#             */
/*   Updated: 2024/01/23 18:25:18 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

typedef struct
{
	int	xpos;
	int	ypos;
	int	width;
	int	height;
	mlx_image_t	player;
} Player;

void move_rectangle(Player *player, uint32_t xdir, uint32_t ydir)
{
    player->xpos += xdir;
    player->ypos += ydir;
	printf("xpos: %d\n", player->xpos);
	printf("ypos: %d\n", player->ypos);
	// printf("%s\n", "Rectangle moved!");
}

void ft_hooks(mlx_key_data_t keydata, Player *player)
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
			ydir = -10;
        if (keydata.key == MLX_KEY_A)
            xdir = -10;
        if (keydata.key == MLX_KEY_S)
            ydir = 10;
        if (keydata.key == MLX_KEY_D)
            xdir = 10;
        move_rectangle(player, xdir, ydir);
    }
	// printf("Key pressed: %c\n", keydata.key);
}

mlx_image_t *ft_draw_rect(mlx_t *mlx, uint32_t width, uint32_t height, uint32_t color)
{
	mlx_image_t	*img;
	uint32_t	i;
	uint32_t	j;
	
	img = mlx_new_image(mlx, width, height);
	i = 0;
	while (i++ < width)
	{
		mlx_put_pixel(img, i, 0, color);
		mlx_put_pixel(img, i, height - 1, color);
	}
	j = 1;
 	while (j++ < height - 1)
	{
		mlx_put_pixel(img, 0, j, color);
		mlx_put_pixel(img, width - 1, j, color);
		i = 1;
		while (i++ < width - 1)
			mlx_put_pixel(img, i, j, color);
	}
	printf("%s\n", "Rectangle printed!");
	return (img);
}

int32_t	main(void)
{
	mlx_t		*mlx;
	mlx_image_t	*rect;
	Player player = {380, 200, 30, 30};

	mlx = mlx_init(800, 400, "kroeg", true);
	rect = ft_draw_rect(mlx, player.width, player.height, 0x70BFFF);
	mlx_image_to_window(mlx, rect, player.xpos, player.ypos);
	mlx_key_hook(mlx, (void *)&ft_hooks, &player);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
