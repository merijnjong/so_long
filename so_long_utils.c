/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:53:38 by mjong             #+#    #+#             */
/*   Updated: 2024/03/13 18:27:17 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_mapcheck3(t_game *game)
{
	int	j;
	int	i;
	int	answer;
	int	result;

	j = 0;
	i = 0;
	answer = 0;
	result = 0;
	while (game->two_d_map[j] != NULL && game->two_d_map[j][0] != '\0')
	{
		i = 0;
		while (game->two_d_map[j][i] != '\0')
		{
			i++;
		}
		answer += i;
		j++;
	}
	printf("%d\n", answer);
	result = answer % j;
	printf("%d\n", result);
	if (answer % j != 0)
		return (1);
		// return (1);
	return (0);
}

int	ft_mapcheck2(t_game *game)
{
	int	result;

	result = game->colnum + game->exinum + game->planum + game->flonum;
	if (result != game->countc)
		return (1);
	if (game->colnum < 1 || game->exinum != 1 || game->planum != 1)
		return (1);
	return (0);
}

int	ft_mapcheck(t_game *game)
{
	int	result;

	result = 0;
	if (ft_mapcheck2(game) == 1 || ft_mapcheck3(game) == 1)
		return (1);
	return (0);
}

void	ft_exitgame(t_game *game)
{
	int	i;
	// int result = 59 % 6;

	// printf("%d\n", result);
	i = 0;
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
}
