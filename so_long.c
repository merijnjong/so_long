/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:52:55 by mjong             #+#    #+#             */
/*   Updated: 2024/01/17 18:18:16 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void my_keyhook(mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_X && keydata.action == MLX_PRESS)
	{
		puts("EXIT_SUCCESS");
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

int32_t	main(void)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	uint32_t	x;
	uint32_t	y;

	mlx = mlx_init(800, 400, "kroeg", true);
	img = mlx_new_image(mlx, 800, 400);
	x = 380;
	y = 200;
	while (x <= 420)
	{
		mlx_put_pixel(img, x, y, 0xffffff);
		x++;
	}
	x = 400;
	y = 180;
	while (y <= 220)
	{
		mlx_put_pixel(img, x, y, 0xffffff);
		y++;
	}
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_key_hook(mlx, (void *)&my_keyhook, NULL);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
