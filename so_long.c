/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:20:51 by mjong             #+#    #+#             */
/*   Updated: 2024/05/22 16:28:19 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_rect_check(t_game *game, char *argv[])
{
	int			temp;
	int			fd;
	char		*line;

	temp = 0;
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	temp = ft_linelen(line);
	while (line != NULL)
	{
		game->width = ft_linelen(line);
		if (game->width != temp)
		{
			ft_free2(&line);
			return (1);
		}
		game->num += ft_strlen(line);
		ft_free2(&line);
		line = get_next_line(fd);
		game->height++;
	}
	ft_free2(&line);
	close(fd);
	return (0);
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

	if (!argv[1] || argc > 2 || ft_bercheck(argv[1]))
	{
		ft_printf("Error\n");
		exit(1);
	}
	init(&game);
	map = ft_filetomap(&game, argv);
	game.two_d_map = ft_split(map, '\n');
	game.two_d_mapcheck = ft_split(map, '\n');
	free(map);
	flood_fill(&game, 1, 1);
	elementcheck1(&game);
	if (ft_mapcheck(&game) == 1)
		ft_exitgame(&game, "fail");
	display_map(&game);
	mlx_key_hook(game.mlx, (void *)&ft_hooks, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (0);
}
