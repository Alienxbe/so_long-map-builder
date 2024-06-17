/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 23:39:09 by marykman          #+#    #+#             */
/*   Updated: 2024/06/14 07:47:35 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "ft_string.h"
#include "ft_math.h"
#include "get_next_line.h"
#include "map_builder.h"

static int	load_special(const char c)
{
	if (c == 'P')
		return (0xf0);
	else if (c == 'C')
		return (0xd0);
	else if (c == 'W')
		return (0xd1);
	else if (c == 'E')
		return (0);
	return (0);
}

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
			{
				if (line[x * 2] == 'x')
					*(tab + x + 16 * y) = load_special(line[x * 2 + 1]);
				else
					*(tab + x + 16 * y) = ft_atoi_base_l(line + x * 2, BASE_HEXA_L, 2);
			}
		}
		free(line);
	}
	close(fd);
	return (0);
}
