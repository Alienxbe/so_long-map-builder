/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:35:18 by marykman          #+#    #+#             */
/*   Updated: 2024/06/12 21:55:40 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_sfe.h"
#include "sfe_pixel.h"
#include "map_builder.h"

static void	draw_selected_tile(t_sc_builder *sc)
{
	static int	old_selection;

	if (old_selection != sc->selected_tile_value)
	{
		old_selection = sc->selected_tile_value;
		sfe_image_destroy(sc->sfe->mlx_ptr, sc->selected_tile);
		sc->selected_tile = sfe_image_resize(
			sc->sfe->mlx_ptr,
			sc->assets[sc->selected_tile_value],
			(t_point){64, 64});
	}
	sfe_image_cpy(sc->selected_tile, *sc->scene.img, (t_point){256 - 32, 512 + 18});
}

void	draw_tile_selector(t_sc_builder *sc)
{
	// Draw background
	sfe_pixel_fill(*sc->scene.img, (t_area){{0, 512}, {512, 612}}, 0x808080);
	sfe_pixel_fill(*sc->scene.img, (t_area){{256 - 32 - 5, 512 + 18 - 5}, {256 + 32 + 5, 512 + 18 + 64 + 5}}, 0x404040);
	
	// Draw side tiles
	int	y = 512 + 34;
	for (int i = 0; i < 3; i++)
	{
		if (sc->selected_tile_value - 1 - i >= 1)
			sfe_image_cpy(sc->assets[sc->selected_tile_value - 1 - i], *sc->scene.img, (t_point){256 - 85 - 32 - i * 53, y});
		else
			sfe_pixel_fill(*sc->scene.img, (t_area){{256 - 85 - 32 - i * 53, y}, {256 - 85 - 32 - i * 53 + 32, y + 32}}, 0x808080);
		if ((sc->assets == sc->assets_base && sc->selected_tile_value + 1 + i < 256)
			|| (sc->assets == sc->assets_special && sc->selected_tile_value + 1 + i < ASSETS_S_MAX))
			sfe_image_cpy(sc->assets[sc->selected_tile_value + 1 + i], *sc->scene.img, (t_point){256 + 85 + 53 * i, y});
		else
			sfe_pixel_fill(*sc->scene.img, (t_area){{256 + 85 + 53 * i, y}, {256 + 85 + 53 * i + 32, y + 32}}, 0x808080);
	}
	draw_selected_tile(sc);
}

void	draw_map(t_sc_builder *sc)
{
	int	x;
	int	y;

	y = -1;
	while (++y < 16)
	{
		x = -1;
		while (++x < 16)
		{
			if (sc->tab[y][x])
				sfe_image_cpy(
					sc->assets_base[sc->tab[y][x]],
					*sc->scene.img,
					(t_point){x * 32, y * 32});
			else
				sfe_pixel_fill(
					*sc->scene.img,
					(t_area){{x * 32, y * 32}, {(x + 1) * 32, (y + 1) * 32}},
					0);
		}
	}
}

void	draw_cursor(t_sc_builder *sc, t_color color)
{
	t_area	pos[4];
	int		i;

	pos[0] = pos_to_area(
			sc->cursor.x * 32, sc->cursor.y * 32,
			(sc->cursor.x + 1) * 32, sc->cursor.y * 32 + 5
			);
	pos[1] = pos_to_area(
			sc->cursor.x * 32, (sc->cursor.y + 1) * 32 - 5,
			(sc->cursor.x + 1) * 32, (sc->cursor.y + 1) * 32
			);
	pos[2] = pos_to_area(
			sc->cursor.x * 32, sc->cursor.y * 32,
			sc->cursor.x * 32 + 5, (sc->cursor.y + 1) * 32
			);
	pos[3] = pos_to_area(
			(sc->cursor.x + 1) * 32 - 5, sc->cursor.y * 32,
			(sc->cursor.x + 1) * 32, (sc->cursor.y + 1) * 32
			);
	i = -1;
	while (++i < 4)
		sfe_pixel_fill(*sc->scene.img, pos[i], color);
}
