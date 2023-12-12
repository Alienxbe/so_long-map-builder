/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile_selector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:07:56 by marykman          #+#    #+#             */
/*   Updated: 2023/12/12 10:52:52 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_builder.h"
#include "t_sfe.h"

void	tile_selector_rotate(t_sc_builder *sc, int val)
{
	int	new_val;

	new_val = sc->selected_tile_value + val;
	if (!(new_val < 1 || new_val > 255))
		sc->selected_tile_value = new_val;
}
