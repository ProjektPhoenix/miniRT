/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:41:39 by hzimmerm          #+#    #+#             */
/*   Updated: 2025/01/26 14:12:49 by hzimmerm         ###   ########.fr       */
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
		cleanup_scene_exit(&rt.scene, NULL, 2, NULL);
	init_mlx_interface(&rt);
	draw_image(&rt);
	minirt_init_loop(&rt);
	return (0);
}
