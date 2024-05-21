/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:52:52 by mjong             #+#    #+#             */
/*   Updated: 2024/05/21 14:55:21 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "MLX42/MLX42.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>

typedef struct t_data
{
	int			xpos;
	int			ypos;
	int			width;
	int			height;
	int			colnum;
	int			exinum;
	int			planum;
	int			flonum;
	int			ylength;
	int			movecount;
	int			countc;
	int			num;
	mlx_t		*mlx;
	mlx_image_t	*collectible;
	mlx_image_t	*eexit;
	mlx_image_t	*ffloor;
	mlx_image_t	*player;
	mlx_image_t	*wall;
	char		**two_d_map;
	char		**two_d_mapcheck;
}	t_game;

int		ft_mapcheck(t_game *game);
int		ft_rect_check(t_game *game, char *argv[]);
void	ft_makeimg(t_game *game);
void	ft_exitgame(t_game *game, char *msg);
void	ft_hooks(mlx_key_data_t keydata, t_game *game);
int		display_map(t_game *game);
// void	flood_fill(t_game *game, int x, int y);

#endif
