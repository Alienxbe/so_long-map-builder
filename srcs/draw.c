/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:35:18 by marykman          #+#    #+#             */
/*   Updated: 2023/11/30 18:26:39 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_sfe.h"
#include "sfe_pixel.h"
#include "map_builder.h"

void	draw_tile_selector(t_sc_builder *sc)
{
	// static int		selected_value;
	// static t_img	selected;
	// if (selected_value != sc->selected_tile)
	// {
	// 	selected_value = sc->selected_tile;
		
	// }
	// Draw background
	sfe_pixel_fill(*sc->scene.img, (t_area){{0, 512}, {512, 612}}, 0x808080);
	sfe_pixel_fill(*sc->scene.img, (t_area){{256 - 32 - 5, 512 + 18 - 5}, {256 + 32 + 5, 512 + 18 + 64 + 5}}, 0x404040);
	// sfe_image_cpy(selected, *sc->scene.img, (t_point){256 - 32, 512 + 18});

	int	y = 512 + 34;
	for (int i = 0; i < 3; i++)
	{
		if (sc->selected_tile_value - 1 - i >= 1)
			sfe_image_cpy(sc->assets[sc->selected_tile_value - 1 - i], *sc->scene.img, (t_point){256 - 85 - 32 - i * 53, y});
		else
			sfe_pixel_fill(*sc->scene.img, (t_area){{256 - 85 - 32 - i * 53, y}, {256 - 85 - 32 - i * 53 + 32, y + 32}}, 0x808080);
		if (sc->selected_tile_value + 1 + i < 256)
			sfe_image_cpy(sc->assets[sc->selected_tile_value + 1 + i], *sc->scene.img, (t_point){256 + 85 + 53 * i, y});
		else
			sfe_pixel_fill(*sc->scene.img, (t_area){{256 + 85 + 53 * i, y}, {256 + 85 + 53 * i + 32, y + 32}}, 0x808080);
	}
	// sfe_image_destroy(sc->sfe->mlx_ptr, selected);
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
					sc->assets[sc->tab[y][x]],
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
