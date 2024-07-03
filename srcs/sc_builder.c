/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sc_builder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 05:00:33 by marykman          #+#    #+#             */
/*   Updated: 2024/06/24 08:11:48 by marykman         ###   ########.fr       */
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

static void	set_assets_special(t_sc_builder *sc, t_img *assets)
{
	assets[ASSET_PLAYER] = sc->assets_base[0xf0];
	assets[ASSET_STRAWBERRY] = sc->assets_base[0xd0];
	assets[ASSET_WALL] = sc->assets_base[0xd1];
	assets[ASSET_EXIT] = sc->assets_base[0x0];
	assets[ASSET_CRISTAL] = sc->assets_base[0xd2];
}

int	sc_builder_init(t_sc_builder *sc)
{
	ft_printf("Init scene main\n");
	sc->running = true;
	sc->assets_base = sfe_load_sprite_sheet(
			sc->sfe,
			F_SPRITE_SHEET,
			(t_point){16, 16},
			&filter);
	set_assets_special(sc, sc->assets_special);
	sc->assets = sc->assets_base;
	ft_printf("Hello world\n");
	if (!sc->assets)
		return (0);
	sc->selected_tile_value = 0;
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
