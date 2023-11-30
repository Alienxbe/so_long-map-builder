/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 23:39:09 by marykman          #+#    #+#             */
/*   Updated: 2023/11/30 17:22:41 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "ft_string.h"
#include "ft_math.h"
#include "get_next_line.h"
#include "map_builder.h"

int	load_map(char *filename, int *tab)
{
	int		fd;
	int		ret;
	char	*line;
	int		y;
	int		x;

	if (!filename)
		return (1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (1);
	y = -1;
	ret = 1;
	while (ret)
	{
		ret = get_next_line(fd, &line);
		if (ret < 0)
			return (1);
		if (++y < 16)
		{
			x = -1;
			while (++x < 16)
				*(tab + x + 16 * y) = ft_atoi_base_l(line + x * 2, BASE_HEXA_L, 2);
		}
		free(line);
	}
	close(fd);
	return (0);
}
