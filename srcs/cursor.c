/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:14:28 by marykman          #+#    #+#             */
/*   Updated: 2023/11/30 18:46:16 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_point.h"
#include "map_builder.h"

/**
 * @brief Add to the cursor position the given values while checking collision
 * with "window border"
 * 
 */
void	cursor_move(t_sc_builder *sc, int x, int y)
{
	t_point	new_pos;

	new_pos = add_point(sc->cursor, (t_point){x, y});
	if (!(new_pos.x < 0 || new_pos.x > 15
		|| new_pos.y < 0 || new_pos.y > 15))
		sc->cursor = new_pos;
}
