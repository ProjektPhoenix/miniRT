/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:41:39 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/12/05 16:57:11 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector_setup.h"
#include "scene.h"

int	main(int argc, char **argv)
{
	t_minirt	rt;

	// init_rt() # tbd
	if (argc == 1) //replace with real error handling
		return (error_return("Error\nno .rt file provided\n"));
	if (parse_file(argv[1], &rt.scene))
		cleanup_scene_exit(&rt.scene, NULL, 2);
	init_mlx_interface(&rt);
	draw_image(&rt);
	minirt_init_loop(&rt);
	// cleanup_exit(&rt, NULL, 2);
	return (0);
}
