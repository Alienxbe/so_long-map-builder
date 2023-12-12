/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sc_builder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 05:00:33 by marykman          #+#    #+#             */
/*   Updated: 2023/12/12 11:19:04 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_printf.h"
#include "t_sfe.h"
#include "sfe_pixel.h"
#include "sfe_color.h"
#include "sfe_event.h"
#include "map_builder.h"

static t_img	filter(t_sfe *sfe, t_img img)
{
	t_img	new;

	new = sfe_image_resize(
			sfe->mlx_ptr,
			img,
			(t_point){img.size.x * 2, img.size.y * 2});
	sfe_image_destroy(sfe->mlx_ptr, img);
	return (new);
}

int	sc_builder_init(t_sc_builder *sc)
{
	ft_printf("Init scene main\n");
	sc->running = true;
	sc->assets = sfe_load_sprite_sheet(
			sc->sfe,
			F_SPRITE_SHEET,
			(t_point){16, 16},
			&filter);
	if (!sc->assets)
		return (0);
	sc->selected_tile_value = 3;
	sc->selected_tile = sfe_image_resize(
			sc->sfe->mlx_ptr,
			sc->assets[sc->selected_tile_value],
			(t_point){64, 64});
	sc->cursor = (t_point){0};
	return (1);
}

int		sc_builder_destroy(t_sc_builder *sc)
{
	int	i;

	i = -1;
	while (sc->assets && sc->assets[++i].img)
		sfe_image_destroy(sc->sfe->mlx_ptr, sc->assets[i]);
	sc->assets = NULL;
	sfe_image_destroy(sc->sfe->mlx_ptr, sc->selected_tile);
	return (0);
}

int	sc_builder_update(t_sc_builder *sc)
{
	draw_tile_selector(sc);
	draw_map(sc);
	draw_cursor(sc, 0xFF0000);
	ft_printf("Fps: %d\n", sc->sfe->fps);
	return (sc->running);
}
