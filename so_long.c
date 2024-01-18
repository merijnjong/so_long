/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:52:55 by mjong             #+#    #+#             */
/*   Updated: 2024/01/18 16:32:11 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void my_keyhook(mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		puts("EXIT");
		exit(EXIT_SUCCESS);
	}
}

// typedef void (*mlx_closefunc)
// {
// 	if (keydata.key == MLX_KEY_X && keydata.action == MLX_PRESS)
// 	{
// 		puts("EXIT_SUCCESS");
// 		exit(EXIT_SUCCESS);
// 	}
// }

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
	return (img);
}

int32_t	main(void)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx_image_t	*rect;
	uint32_t	x;
	uint32_t	y;

	mlx = mlx_init(800, 400, "kroeg", true);
	img = mlx_new_image(mlx, 800, 400);
	rect = ft_draw_rect(mlx, 30, 30, 0x70BFFF);
	x = 380;
	y = 200;
	while (x++ <= 420)
		mlx_put_pixel(img, x, y, 0xffffff);
	x = 400;
	y = 180;
	while (y++ <= 220)
		mlx_put_pixel(img, x, y, 0xffffff);
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_image_to_window(mlx, rect, 0, 0);
	mlx_key_hook(mlx, (void *)&my_keyhook, rect);
	// mlx_loop_hook(mlx, (void *)&my_keyhook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
