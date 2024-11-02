/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:41:39 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/10/30 17:48:38 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
#include "../includes/vector_setup.h"
#include "../../includes/scene.h"

int	main(int argc, char **argv)
{
	t_scene scene;

	if (argc == 1) //replace with real error handling
		return (error_return("Error\nno .rt file provided\n"));
	if (parse_file(argv[1], &scene))
		cleanup_exit(&scene, NULL, 2);
	cleanup_exit(&scene, NULL, 2);
	return (0);
}


