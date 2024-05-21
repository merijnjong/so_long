/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_backup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:20:51 by mjong             #+#    #+#             */
/*   Updated: 2024/05/21 14:52:01 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_ber(char *line)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(line);
	if (len < 4)
		return (1);
	i = len - 4;
	if (line[i] != '.' || line[i + 1] != 'b'
		|| line[i + 2] != 'e' || line[i + 3] != 'r')
		return (1);
	return (0);
}

void	flood_fill(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->width || y < 0 || y >= game->height)
	{
		game->countc = -100000;
		return ;
	}
	if (game->two_d_mapcheck[y][x] == '1' || game->two_d_mapcheck[y][x] == 'N')
		return ;
	else if (game->two_d_mapcheck[y][x] == 'C')
		game->countc++;
	else if (game->two_d_mapcheck[y][x] == 'E')
		game->countc++;
	else if (game->two_d_mapcheck[y][x] == 'P')
		game->countc++;
	else if (game->two_d_mapcheck[y][x] == '0')
		game->countc++;
	game->two_d_mapcheck[y][x] = 'N';
	flood_fill(game, x + 1, y);
	flood_fill(game, x - 1, y);
	flood_fill(game, x, y + 1);
	flood_fill(game, x, y - 1);
}

char	*ft_filetomap(t_game *game, char *argv[])
{
	int		fd;
	char	*map;
	char	*temp;

	fd = open(argv[1], O_RDONLY);
	map = NULL;
	if (fd < 0 || ft_rect_check(game, argv) == 1)
	{
		ft_printf("Error\nINVALID MAP\n");
		exit(EXIT_FAILURE);
	}
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
	game->num = 0;
	game->mlx = NULL;
	game->collectible = NULL;
	game->eexit = NULL;
	game->ffloor = NULL;
	game->player = NULL;
	game->wall = NULL;
	game->two_d_map = NULL;
	game->two_d_mapcheck = NULL;
}

int32_t	main(int argc, char *argv[])
{
	t_game	game;
	char	*map;

	if (!argv[1] || argc > 2 || ft_ber(argv[1]))
	{
		ft_printf("Error\n");
		exit(1);
	}
	init(&game);
	map = ft_filetomap(&game, argv);
	game.two_d_map = ft_split(map, '\n');
	game.two_d_mapcheck = ft_split(map, '\n');
	free(map);
	if (display_map(&game) == 1)
		ft_exitgame(&game, "fail");
	flood_fill(&game, 1, 1);
	if (ft_mapcheck(&game) == 1)
		ft_exitgame(&game, "fail");
	mlx_key_hook(game.mlx, (void *)&ft_hooks, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (0);
}
