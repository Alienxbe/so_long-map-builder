/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 04:36:38 by marykman          #+#    #+#             */
/*   Updated: 2023/11/29 23:21:55 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "ft_printf.h"
#include "get_next_line.h"
#include "sfe_event.h"
#include "map_builder.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

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

static int	on_key_down(int key, t_sc_builder *sc)
{
	if (key == SFE_KEY_ESC)
		sc->running = false;
	else if (key == SFE_KEY_C && sc->selected_tile < 256)
		sc->selected_tile++;
	else if (key == SFE_KEY_V && sc->selected_tile < 256 - 3)
		sc->selected_tile += 3;
	else if (key == SFE_KEY_X && sc->selected_tile  > 1)
		sc->selected_tile--;
	else if (key == SFE_KEY_Z && sc->selected_tile > 3)
		sc->selected_tile -= 3;
	else if (key == SFE_KEY_RIGHT && sc->cursor.x < 15) // Droite
		sc->cursor.x++;
	else if (key == SFE_KEY_LEFT && sc->cursor.x > 0) // Gauche
		sc->cursor.x--;
	else if (key == SFE_KEY_UP && sc->cursor.y > 0) // Haut
		sc->cursor.y--;
	else if (key == SFE_KEY_DOWN && sc->cursor.y < 15) // Bas
		sc->cursor.y++;
	else if (key == SFE_KEY_SPACE) // Space
		sc->tab[sc->cursor.y][sc->cursor.x] = sc->selected_tile;
	else if (key == SFE_KEY_DEL)
		sc->tab[sc->cursor.y][sc->cursor.x] = 0;
	else if (key == SFE_KEY_ENTER)
		print_map(sc->tab);
	ft_printf("Key pressed: %d\n", key);
	return (1);
}

// ./map_builder [map file]
int	main(int argc, char **argv)
{
	t_sfe			*sfe;
	t_sc_builder	sc;

	(void)argc;
	(void)argv;
	sfe = sfe_init(WIN_NAME, (t_point){WIN_DIM});
	sfe_set_max_fps(sfe, 30);

	ft_bzero(&sc, sizeof(t_sc_builder));

	sc.scene = sfe_new_scene(sfe, &sc);
	sc.scene.f_init = &sc_builder_init;
	sc.scene.f_update = &sc_builder_update;
	sc.scene.f_destroy = &sc_builder_destroy;
	sc.sfe = sfe;

	sfe_set_active_scene(sfe, &sc.scene);
	sfe_hook(sfe, ON_KEYDOWN, &on_key_down, &sc);
	sfe_loop(sfe);
	return (0);
}