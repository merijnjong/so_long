/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:52:52 by mjong             #+#    #+#             */
/*   Updated: 2024/01/24 16:18:16 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "MLX42/MLX42.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 6
# endif

int		ft_strcmp(const char *s1, const char *s2);
char	*get_next_line(int fd);
char	*ft_strjoin2(char *s1, char *s2);
int		ft_strlen2(const char *str);
char	*ft_strchr2(char *s, int c);
char	*ft_free2(char **str);

#endif
