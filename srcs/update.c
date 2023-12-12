/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:06:09 by marykman          #+#    #+#             */
/*   Updated: 2023/12/12 11:24:58 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_builder.h"
#include "sfe_event.h"
#include "ft_printf.h"

static void	update_tile_selector(t_sc_builder *sc, int key)
{
	if (key == SFE_KEY_Z)
		tile_selector_rotate(sc, -3);
	if (key == SFE_KEY_X)
		tile_selector_rotate(sc, -1);
	if (key == SFE_KEY_C)
		tile_selector_rotate(sc, 1);
	if (key == SFE_KEY_V)
		tile_selector_rotate(sc, 3);
}

static void	update_cursor(t_sc_builder *sc, int key)
{
	if (key == SFE_KEY_LEFT)
		cursor_move(sc, -1, 0);
	if (key == SFE_KEY_RIGHT)
		cursor_move(sc, 1, 0);
	if (key == SFE_KEY_UP)
		cursor_move(sc, 0, -1);
	if (key == SFE_KEY_DOWN)
		cursor_move(sc, 0, 1);
}

void	update(t_sc_builder *sc, int key)
{
	update_tile_selector(sc, key);
	update_cursor(sc, key);
}