/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:01:25 by hzimmerm          #+#    #+#             */
/*   Updated: 2025/01/21 13:26:13 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include "vector_setup.h"
#include "scene.h"
#include <mlx.h>

int	error_return(char *mssg)
{
	ft_putstr_fd(mssg, 2);
	return (1);
}

int	error_exit(char *mssg)
{
	ft_putstr_fd(mssg, 2);
	exit(1);
}

int	perror_exit(char *mssg)
{
	perror(mssg);
	exit(1);
}

int	error_exit_status(char *mssg, int status)
{
	if (mssg)
		ft_putstr_fd(mssg, 2);
	exit(status);
}

void cleanup_scene(t_scene *scene)
{
	t_plane *temp_p;
	t_cylinder *temp_c;
	t_sphere *temp_s;

	while (scene->plane)
	{
		temp_p = scene->plane->next;
		free(scene->plane);
		scene->plane = temp_p;
	}
	while (scene->cyl)
	{
		temp_c = scene->cyl->next;
		free(scene->cyl);
		scene->cyl = temp_c;
	}
	while(scene->sphere)
	{
		temp_s = scene->sphere->next;
		free(scene->sphere);
		scene->sphere = temp_s;
	}
	scene->plane = NULL;
	scene->cyl = NULL;
	scene->sphere = NULL;
}

void cleanup_scene_exit(t_scene *scene, char *mssg, int status)
{
	cleanup_scene(scene);
	error_exit_status(mssg, status);
}

void	cleanup_mlx(t_minirt *rt)
{
	#ifdef __linux__
		mlx_loop_end(rt->screen.mlx);
	#endif
	mlx_destroy_image(rt->screen.mlx, rt->img.ptr);
	mlx_destroy_window(rt->screen.mlx, rt->screen.win);
	#ifdef __linux__
			mlx_destroy_display(rt->screen.mlx);
	#endif
}

void	cleanup_exit(t_minirt *rt, char *mssg, int status)
{
	cleanup_scene(&(rt->scene));
	cleanup_mlx(rt);
	if (mssg)
		error_exit(mssg);
	else
		exit(status);
}

int	loop_cleanup(t_minirt *rt)
{
	cleanup_exit(rt, NULL, 0);
	return (0);
}

void	free_array(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}
