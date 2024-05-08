/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:53:38 by mjong             #+#    #+#             */
/*   Updated: 2024/05/08 17:42:30 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_linelen(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	return (i);
}

int	ft_rect_check(t_game *game, char *argv[])
{
	int			temp;
	int			fd;
	char		*one_line;
	static int	x_end = 0;
	static int	y_end = 0;

	temp = 0;
	fd = open(argv[1], O_RDONLY);
	one_line = get_next_line(fd);
	temp = ft_linelen(one_line);
	while (one_line != NULL)
	{
		x_end = ft_linelen(one_line);
		if (x_end != temp)
			return (1);
		game->num += ft_strlen(one_line);
		ft_free2(&one_line);
		one_line = get_next_line(fd);
		y_end++;
	}
	ft_free2(&one_line);
	close(fd);
	return (0);
}

int	ft_mapcheck(t_game *game)
{
	int	result;

	result = game->colnum + game->exinum + game->planum + game->flonum;
	printf("result: %d\n", result);
	printf("countc: %d\n", game->countc);
	if (result != game->countc)
		return (1);
	if (game->colnum < 1 || game->exinum != 1 || game->planum != 1)
		return (1);
	return (0);
}

void	ft_exitgame(t_game *game, char *msg)
{
	static int	i = 0;

	while (game->two_d_map[i])
	{
		free(game->two_d_map[i]);
		i++;
	}
	i = 0;
	while (game->two_d_mapcheck[i])
	{
		free(game->two_d_mapcheck[i]);
		i++;
	}
	free(game->two_d_map);
	free(game->two_d_mapcheck);
	mlx_close_window(game->mlx);
	if (ft_strncmp(msg, "fail", 4) == 0)
	{
		ft_printf("Error\nINVALID MAP\n");
		exit(EXIT_FAILURE);
	}
	else if (ft_strncmp(msg, "exit", 4) == 0)
		ft_printf("EXITED GAME\n");
}
