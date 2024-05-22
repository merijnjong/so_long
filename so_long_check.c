/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:22:00 by mjong             #+#    #+#             */
/*   Updated: 2024/05/22 16:24:34 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_mapcheck(t_game *game)
{
	int	result;

	result = game->colnum + game->exinum + game->planum + game->flonum;
	if (result != game->countc)
		return (1);
	if (game->colnum < 1 || game->exinum != 1 || game->planum != 1)
		return (1);
	return (0);
}

int	elementcheck2(t_game *game, char indicator)
{
	if (indicator == '0')
		game->flonum += 1;
	else if (indicator == '1')
		return (0);
	else if (indicator == 'C')
		game->colnum += 1;
	else if (indicator == 'E')
		game->exinum += 1;
	else if (indicator == 'P')
		game->planum += 1;
	else
		return (1);
	return (0);
}

void	elementcheck1(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (elementcheck2(game, game->two_d_map[y][x]) == 1)
				ft_exitgame(game, "fail");
			x++;
		}
		y++;
	}
}

void	flood_fill(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->width || y < 0 || y >= game->height)
	{
		game->countc = -1000;
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

int	ft_bercheck(char *line)
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
