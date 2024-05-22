/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:53:38 by mjong             #+#    #+#             */
/*   Updated: 2024/05/22 16:28:24 by mjong            ###   ########.fr       */
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

void	ft_exitgame(t_game *game, char *msg)
{
	static int	i = -1;

	while (game->two_d_map[++i])
		free(game->two_d_map[i]);
	i = -1;
	while (game->two_d_mapcheck[++i])
		free(game->two_d_mapcheck[i]);
	free(game->two_d_map);
	free(game->two_d_mapcheck);
	if (ft_strncmp(msg, "fail", 4) == 0)
	{
		ft_printf("Error\nINVALID MAP\n");
		exit(EXIT_FAILURE);
	}
	else if (ft_strncmp(msg, "exit", 4) == 0
		|| ft_strncmp(msg, "success", 7) == 0)
	{
		mlx_close_window(game->mlx);
		ft_printf("EXITED GAME\n");
	}
}
