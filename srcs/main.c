/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpriess <rpriess@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:41:39 by hzimmerm          #+#    #+#             */
/*   Updated: 2025/01/23 22:44:46 by rpriess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector_setup.h"
#include "scene.h"
#include "error_utils.h"

int	main(int argc, char **argv)
{
	t_minirt	rt;

	if (argc == 1)
		return (error_return("Error\nno .rt file provided\n"));
	if (argc > 2)
		return (error_return("Error\ntoo many arguments\n"));
	if (parse_file(argv[1], &rt.scene))
		cleanup_scene_exit(&rt.scene, NULL, 2);
	init_mlx_interface(&rt);
	draw_image(&rt);
	minirt_init_loop(&rt);
	return (0);
}
