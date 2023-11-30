/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 04:36:38 by marykman          #+#    #+#             */
/*   Updated: 2023/11/30 18:28:53 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "ft_printf.h"
#include "sfe_event.h"
#include "map_builder.h"

// ./map_builder [map file]
int	main(int argc, char **argv)
{
	t_sfe			*sfe;
	t_sc_builder	sc;

	if (argc > 2)
		return (1);

	sfe = sfe_init(WIN_NAME, (t_point){WIN_DIM});
	sfe_set_max_fps(sfe, 30);

	ft_bzero(&sc, sizeof(t_sc_builder));

	if (argc == 2)
		load_map(argv[1], (int *)sc.tab);

	sc.scene = sfe_new_scene(sfe, &sc);
	sc.scene.f_init = &sc_builder_init;
	sc.scene.f_update = &sc_builder_update;
	sc.scene.f_destroy = &sc_builder_destroy;
	sc.sfe = sfe;

	sfe_set_active_scene(sfe, &sc.scene);
	sfe_hook_on_keydown(sfe->win, &on_key_down, &sc);
	sfe_hook_on_keyup(sfe->win, &on_key_up, &sc);
	sfe_loop(sfe);
	return (0);
}