/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:29:46 by rpriess           #+#    #+#             */
/*   Updated: 2024/12/13 15:09:44 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx_wrapper.h"
#include <libft.h>
#include <mlx.h>
#include <stdbool.h>
#include <math.h>

#include "debug.h"

/*
 * Input: image struct to write to, coordinate of pxl in image and pxl color.
 * Function modifies img content.
 * Returns: "0" upon success, "1" if pxl coordinates are outside image boundaries,
 * "2" if color information cannot be interpreted and "3" in case of other errors.
 */
bool draw_pixel(t_img *img, t_pxl *pxl)
{
    unsigned int color;

    //color = ft_argb_color(255, (int)pxl->color.e[0], (int)pxl->color.e[1], (int)pxl->color.e[2]);
    color = ft_rgb_color((int)pxl->color.e[0], (int)pxl->color.e[1], (int)pxl->color.e[2]);


    if (pxl->a > img->width || pxl->b > img->height || pxl->a < 0 || pxl->b < 0)
        return (1);
    ft_memcpy(img->content + (pxl->b * img->line + pxl->a * img->bpp / 8), &color, img->bpp / 8);
    return (0);
}

/*
 * REMOVE BEFORE SUBMISSION
 */
// static void draw_animation(t_minirt *rt)
// {
//     double i;
//     double k;
//     double deg;
//     t_pxl pxl;

//     pxl.color.e[0] = 255;
//     pxl.color.e[1] = 0;
//     pxl.color.e[2] = 0;
//     i = 0.0;
//     deg = 0.0;
//     while (true)
//     {
//         while (i < rt->img.width / 2)
//         {
//             k = i;
//             while (deg <= 2 * 355.0 / 113.0)
//             {

//                 while (i < (k + 20.0))
//                 {
//                     pxl.x = rt->img.width / 2 + i * cos(deg);
//                     pxl.y = rt->img.height / 2 - i * sin(deg);
//                     printf("Pixel to draw <%i, %i> while i= %.2f, k=%.2f and deg=%.2f\n", pxl.x, pxl.y, i, k, deg);
//                     draw_pixel(&(rt->img), &pxl);
//                     i = i + 1.0;
//                 }
//                 deg = deg + 355.0 / 678.0;
//                 i = k;
//             }
//             usleep(200000);
//             mlx_put_image_to_window(rt->screen.mlx, rt->screen.win, rt->img.ptr, 0, 0);
//             mlx_destroy_image(rt->screen.mlx, rt->img.ptr);
//             init_img(rt);
//             deg = 0.0;
//             i = i + 20.0;
//         }
//         i = 0.0;
//     }
// }

// static void draw_square(t_img *img)
// {
//     t_pxl   pxl;
//     int     i;
//     int     j;

//     i = 200;
//     j = 200;
//     pxl.color.e[0] = 255;
//     pxl.color.e[1] = 50;
//     pxl.color.e[2] = 50;
//     while (j < 250)
//     {
//         while (i < 250)
//         {
//             pxl.a = i;
//             pxl.b = j;
//             draw_pixel(img, &pxl);
//             i++;
//         }
//         i = 200;
//         j++;
//     }
// }
/*static void	draw_frame(t_img *img, int frame_width)
{
    t_pxl   pxl;
	int j;
    int i;

    pxl.color.e[0] = 255;
    pxl.color.e[1] = 50;
    pxl.color.e[2] = 50;

	debug("Draw frame with frame thickness of %i in img of size %i x %i", frame_width, img->width, img->height);
    j = 0;
    i = 0;
    while (j < img->height)
    {
        while (i < img->width)
        {
            if (i < frame_width || i >= img->width - frame_width \
                || j <= frame_width || j >= img->height - frame_width)
            {
                pxl.a = i;
                pxl.b = j;
                draw_pixel(img, &pxl);
            }
            i++;
        }
        i = 0;
        j++;
    }
}*/

/*
 * the function allows to save an mlx image to an xpm image file, which can be
 * viewed later using other means. Files are saved in a hidden directory ".output"
 * relative to the working directory.
 */
// void	save_img_to_xpm()
// {
//
// }
//
// void    draw_viewport()
// {
//
// }

void draw_image(t_minirt *rt)
{
	debug("");
	init_viewport(rt);
	calculate_rays(rt);
    // draw_viewport_to_img()
    // draw_square(&(rt->img));
    //draw_frame(&(rt->img), 2);
    // draw_animation(rt);
    mlx_put_image_to_window(rt->screen.mlx, rt->screen.win, rt->img.ptr, 0, 0);
}
