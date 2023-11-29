/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sc_builder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 05:00:33 by marykman          #+#    #+#             */
/*   Updated: 2023/11/29 20:48:26 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_printf.h"
#include "t_sfe.h"
#include "sfe_pixel.h"
#include "sfe_color.h"
#include "map_builder.h"

static t_img	filter(t_sfe *sfe, t_img img)
{
	t_img	new;

	new = sfe_image_resize(sfe->mlx_ptr, img, (t_point){img.size.x * 2, img.size.y * 2});
	sfe_image_destroy(sfe->mlx_ptr, img);
	return (new);
}

int	sc_builder_init(t_sc_builder *sc)
{
	ft_printf("Init scene main\n");
	sc->running = true;
	sc->assets = sfe_load_sprite_sheet(sc->sfe, F_SPRITE_SHEET, (t_point){16, 16}, &filter);
	if (!sc->assets)
		return (0);

	// Print tile selector
	sfe_pixel_fill(*sc->scene.img, (t_area){{0, 512}, {512, 612}}, 0x808080);
	sfe_pixel_fill(*sc->scene.img, (t_area){{256 - 32 - 5, 512 + 18 - 5}, {256 + 32 + 5, 512 + 18 + 64 + 5}}, 0x404040);

	sc->selected_tile = 1;
	sc->cursor = (t_point){0};

	return (1);
}

int		sc_builder_destroy(t_sc_builder *sc)
{
	int	i;

	i = -1;
	while (sc->assets[++i].img)
		sfe_image_destroy(sc->sfe->mlx_ptr, sc->assets[i]);
	sc->assets = NULL;
	return (0);
}

#include "t_sfe.h"

int	sc_builder_update(t_sc_builder *sc)
{
	int		selected_value = sc->selected_tile;
	t_img	selected = sfe_image_resize(sc->sfe->mlx_ptr, sc->assets[selected_value], (t_point){64, 64});
	sfe_image_cpy(selected, *sc->scene.img, (t_point){256 - 32, 512 + 18});

	int	y = 512 + 34;
	for (int i = 0; i < 3; i++)
	{
		if (selected_value - 1 - i >= 1)
			sfe_image_cpy(sc->assets[selected_value - 1 - i], *sc->scene.img, (t_point){256 - 85 - 32 - i * 53, y});
		else
			sfe_pixel_fill(*sc->scene.img, (t_area){{256 - 85 - 32 - i * 53, y}, {256 - 85 - 32 - i * 53 + 32, y + 32}}, 0x808080);
		if (selected_value + 1 + i < 256)
			sfe_image_cpy(sc->assets[selected_value + 1 + i], *sc->scene.img, (t_point){256 + 85 + 53 * i, y});
		else
			sfe_pixel_fill(*sc->scene.img, (t_area){{256 + 85 + 53 * i, y}, {256 + 85 + 53 * i + 32, y + 32}}, 0x808080);
	}
	sfe_image_destroy(sc->sfe->mlx_ptr, selected);

	// print map
	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			if (sc->tab[y][x])
				sfe_image_cpy(sc->assets[sc->tab[y][x]], *sc->scene.img, (t_point){x * 32, y * 32});
			else
				sfe_pixel_fill(*sc->scene.img, (t_area){{x * 32, y * 32}, {(x + 1) * 32, (y + 1) * 32}}, 0);
		}
	}
	
	// Printing cursor
	sfe_pixel_fill(*sc->scene.img, (t_area){{sc->cursor.x * 32, sc->cursor.y * 32 - 5}, {(sc->cursor.x + 1) * 32, sc->cursor.y * 32}}, 0xFF0000);
	sfe_pixel_fill(*sc->scene.img, (t_area){{sc->cursor.x * 32, (sc->cursor.y + 1) * 32}, {(sc->cursor.x + 1) * 32, (sc->cursor.y + 1) * 32 + 5}}, 0xFF0000);
	sfe_pixel_fill(*sc->scene.img, (t_area){{sc->cursor.x * 32 - 5, sc->cursor.y * 32}, {sc->cursor.x * 32, (sc->cursor.y + 1) * 32}}, 0xFF0000);
	sfe_pixel_fill(*sc->scene.img, (t_area){{(sc->cursor.x + 1) * 32, sc->cursor.y * 32}, {(sc->cursor.x + 1) * 32 + 5, (sc->cursor.y + 1) * 32}}, 0xFF0000);
	// ft_printf("Fps: %d\n", sc->sfe->fps);
	return (sc->running);
}
