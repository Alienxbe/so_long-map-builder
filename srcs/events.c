/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:01:29 by marykman          #+#    #+#             */
/*   Updated: 2023/11/30 19:00:49 by marykman         ###   ########.fr       */
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

static void	print_map(int tab[16][16])
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
			ft_fprintf(fd, "%02x", tab[y][x]);
		ft_fprintf(fd, "\n");
	}
	if (close(fd) < 0)
		ft_printf("Error on closing file map\n");
	else
		ft_printf("Map wrote in file successfully\n");
}

int	on_key_down(int key, t_sc_builder *sc)
{
	int	i;

	if (key == SFE_KEY_ESC)
		sc->running = false;
	else if (key == SFE_KEY_SPACE)
		sc->tab[sc->cursor.y][sc->cursor.x] = sc->selected_tile_value;
	else if (key == SFE_KEY_DEL)
		sc->tab[sc->cursor.y][sc->cursor.x] = 0;
	else if (key == SFE_KEY_ENTER)
		print_map(sc->tab);
	i = -1;
	while (++i < KEYBIND_LEN)
		if (sc->keys[i] == key && !sc->active_keys[i])
			sc->active_keys[i] = 1;
	return (1);
}

int	on_key_up(int key, t_sc_builder *sc)
{
	int	i;

	i = -1;
	while (++i < KEYBIND_LEN)
		if (sc->keys[i] == key)
			sc->active_keys[i] = 0;
	return (1);
}
