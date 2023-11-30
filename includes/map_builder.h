/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_builder.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 04:44:47 by marykman          #+#    #+#             */
/*   Updated: 2023/11/30 14:09:44 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_BUILDER_H
# define MAP_BUILDER_H

# include "sfe.h"
# include "sfe_image.h"

# define F_SPRITE_SHEET	"assets/CelestePico8.xpm"

# define WIN_NAME	"so_long map builder"
# define WIN_DIM	512, 612

typedef struct s_sc_builder
{
	t_sfe	*sfe;
	t_scene	scene;
	t_bool	running;

	t_img	*assets;
	int		tab[16][16]; // [y][x]
	int		selected_tile;
	t_point	cursor;
}	t_sc_builder;

typedef t_img	(*t_filter)(t_sfe *sfe, t_img img);

t_img	*sfe_load_sprite_sheet(t_sfe *sfe, char *filename, t_point sprite_size,
			t_filter filter);

int	load_map(char *filename, int *tab);

// Scene special callback
int	sc_builder_init(t_sc_builder *sc);
int	sc_builder_update(t_sc_builder *sc);
int	sc_builder_destroy(t_sc_builder *sc);

// Draw functions
void	draw_tile_selector(t_sc_builder *sc);
void	draw_map(t_sc_builder *sc);
void	draw_cursor(t_sc_builder *sc, t_color color);

#endif