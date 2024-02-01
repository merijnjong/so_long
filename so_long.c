/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:20:51 by mjong             #+#    #+#             */
/*   Updated: 2024/02/01 17:56:15 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void ft_makeimg(struct t_data *game)
{
	mlx_texture_t *c = mlx_load_png("./assets/collectible.png");
	mlx_texture_t *e = mlx_load_png("./assets/exit.png");
	mlx_texture_t *f = mlx_load_png("./assets/floor.png");
	mlx_texture_t *p = mlx_load_png("./assets/player.png");
	mlx_texture_t *w = mlx_load_png("./assets/wall.png");
	game->collectible = mlx_texture_to_image(game->mlx, c);
	game->eexit = mlx_texture_to_image(game->mlx, e);
	game->ffloor = mlx_texture_to_image(game->mlx, f);
	game->player = mlx_texture_to_image(game->mlx, p);
	game->wall = mlx_texture_to_image(game->mlx, w);
}

void	move_player(mlx_t *mlxp, struct t_data *game, uint32_t xdir, uint32_t ydir)
{
	uint32_t	prevxdir = game->xpos;
	uint32_t	prevydir = game->ypos;

	mlx_image_to_window(mlxp, game->ffloor, prevxdir, prevydir);
	game->xpos += xdir;
	game->ypos += ydir;
	printf("xpos: %d\n", game->xpos);
	printf("ypos: %d\n", game->ypos);
}

void	ft_hooks(mlx_key_data_t keydata, struct t_data *game)
{
	uint32_t	xdir;
	uint32_t	ydir;

	xdir = 0;
	ydir = 0;
	mlx_t *mlxp = game->mlx;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
		{
			puts("EXIT");
			exit(EXIT_SUCCESS);
		}
		if (keydata.key == MLX_KEY_W)
			ydir = -100;
		if (keydata.key == MLX_KEY_A)
			xdir = -100;
		if (keydata.key == MLX_KEY_S)
			ydir = 100;
		if (keydata.key == MLX_KEY_D)
			xdir = 100;
		move_player(mlxp, game, xdir, ydir);
		mlx_image_to_window(mlxp, game->player, game->xpos, game->ypos);
	}
}

void	ft_makemap(mlx_t *mlx, char *map, struct t_data *game, int x, int y)
{
	int i;

	i = 0;
	while (map[i] != '\n' && map[i] != '\0')
	{
		if (map[i] == 'C')
			mlx_image_to_window(mlx, game->collectible, x, y);
		if (map[i] == 'E')
			mlx_image_to_window(mlx, game->eexit, x, y);
		if (map[i] == '0')
			mlx_image_to_window(mlx, game->ffloor, x, y);
		if (map[i] == 'P')
			mlx_image_to_window(mlx, game->player, x, y);
		if (map[i] == '1')
			mlx_image_to_window(mlx, game->wall, x, y);
		i++;
		x += 100;
	}
}

void ft_filetomap(mlx_t *mlx, struct t_data *game)
{
    int x;
    int y;
    int fd;
    int check;
    char *map;

    check = 0;
    y = 0;
    fd = open("map.ber", O_RDONLY);
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
        ft_makemap(mlx, map, game, x, y);
        y += 100;
        free(map);
    }
    close(fd);
}

int32_t main(void)
{
    mlx_t *mlx;

	mlx = mlx_init(2100, 1400, "starwars", true);
    Game game = {100, 100, 100, 100, mlx, NULL, NULL, NULL, NULL, NULL};
    ft_makeimg(&game);
    ft_filetomap(mlx, &game);
    mlx_key_hook(mlx, (void *)&ft_hooks, &game);
    mlx_loop(mlx);
    mlx_terminate(mlx);
    return (EXIT_SUCCESS);
}
