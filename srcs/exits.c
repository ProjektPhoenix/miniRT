/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:01:25 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/12/05 18:19:27 by hzimmerm         ###   ########.fr       */
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
	ft_putstr_fd(mssg, 2);
	exit(status);
}

void cleanup_scene(t_scene *scene)
{
	if (scene->plane)
	{
		free(scene->plane);
		scene->plane = NULL;
	}
	if (scene->cyl)
	{
		free(scene->cyl);
		scene->cyl = NULL;
	}
	if (scene->sphere)
	{
		free(scene->sphere);
		scene->sphere = NULL;
	}
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
