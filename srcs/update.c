/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:06:09 by marykman          #+#    #+#             */
/*   Updated: 2023/11/30 19:06:23 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_builder.h"
#include "ft_printf.h"

static void	update_keytimes(t_sc_builder *sc)
{
	int	i;

	i = -1;
	while (++i < KEYBIND_LEN)
		if (sc->active_keys[i])
			sc->active_keys[i]++;
}

static void	update_tile_selector(t_sc_builder *sc)
{
	if (sc->active_keys[KEYBIND_Z])
		tile_selector_rotate(sc, -3);
	if (sc->active_keys[KEYBIND_X])
		tile_selector_rotate(sc, -1);
	if (sc->active_keys[KEYBIND_C])
		tile_selector_rotate(sc, 1);
	if (sc->active_keys[KEYBIND_V])
		tile_selector_rotate(sc, 3);
}

#define RATIO	3

static void	update_cursor(t_sc_builder *sc)
{
	if (sc->active_keys[KEYBIND_LEFT] % RATIO == 1)
		cursor_move(sc, -1, 0);
	if (sc->active_keys[KEYBIND_RIGHT] % RATIO == 1)
		cursor_move(sc, 1, 0);
	if (sc->active_keys[KEYBIND_UP] % RATIO == 1)
		cursor_move(sc, 0, -1);
	if (sc->active_keys[KEYBIND_DOWN] % RATIO == 1)
		cursor_move(sc, 0, 1);
}

void	update(t_sc_builder *sc)
{
	update_keytimes(sc);
	update_tile_selector(sc);
	update_cursor(sc);
}