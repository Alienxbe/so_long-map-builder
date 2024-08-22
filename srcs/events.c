/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:01:29 by marykman          #+#    #+#             */
/*   Updated: 2024/08/21 04:42:09 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "ft_printf.h"
#include "sfe_event.h"
#include "map_builder.h"

static void	get_map_value(int fd, int value)
{
	if (value == 0xf0)
		ft_fprintf(fd, "xP");
	else if (value == 0xd0)
		ft_fprintf(fd, "xC");
	else if (value == 0xd1)
		ft_fprintf(fd, "xW");
	else if (value == 0xc0)
		ft_fprintf(fd, "xE");
	else
		ft_fprintf(fd, "%02x", value);
}

static void	print_map(t_sc_builder *sc)
{
	int		fd;
	char	*line;
	
	ft_printf("Enter file path : ");
	if (get_next_line(STDIN_FILENO, &line) < 0)
		return ;
	fd = open(line, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
	free(line);
	if (fd < 0)
		return ;
	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
			get_map_value(fd, sc->tab[y][x]);
		if (y < 15)
			ft_fprintf(fd, "\n");
	}
	if (close(fd) < 0)
		ft_printf("Error on closing file map\n");
	else
		ft_printf("Map wrote in file successfully\n");
}

int	on_key_down(int key, t_sc_builder *sc)
{
	if (key == SFE_KEY_ESC)
		sc->running = false;
	else if (key == SFE_KEY_SPACE && sc->assets == sc->assets_base)
		sc->tab[sc->cursor.y][sc->cursor.x] = sc->selected_tile_value;
	else if (key == SFE_KEY_SPACE && sc->assets == sc->assets_special)
	{
		if (sc->selected_tile_value == ASSET_PLAYER)
			sc->tab[sc->cursor.y][sc->cursor.x] = 0xf0;
		else if (sc->selected_tile_value == ASSET_STRAWBERRY)
			sc->tab[sc->cursor.y][sc->cursor.x] = 0xd0;
		else if (sc->selected_tile_value == ASSET_WALL)
			sc->tab[sc->cursor.y][sc->cursor.x] = 0xd1;
		else if (sc->selected_tile_value == ASSET_CRISTAL)
			sc->tab[sc->cursor.y][sc->cursor.x] = 0xd2;
		else if (sc->selected_tile_value == ASSET_EXIT)
			sc->tab[sc->cursor.y][sc->cursor.x] = 0xc0;
	}
	else if (key == SFE_KEY_DEL)
		sc->tab[sc->cursor.y][sc->cursor.x] = 0;
	else if (key == SFE_KEY_S)
	{
		sc->assets = (sc->assets == sc->assets_base) ? sc->assets_special : sc->assets_base;
		sc->selected_tile_value = 0;
	}
	else if (key == SFE_KEY_ENTER)
		print_map(sc);
	update(sc, key);
	return (1);
}
