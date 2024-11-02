typedef struct s_interface {
	void	*mlx;
	void	*win_ptr;
	int	height;
	int	width;
}	t_interface

typedef struct s_img {
    void    *ptr;
    void    *content;
    void    *line;
    void    *bpp;
}   t_img

typedef struct  s_viewport {
    t_pxl   **pxl
    t_
}   t_viewport

typedef struct s_pixel {
    t_vec   pxl
    t_vec   color
}

write_pxl_to_viewport


/*
 * Based on camera information 
 */
create_rays()

/*
 * Based on camera information, creates viewport information,
 * which is passed to the function as a modifiable viewport struct.
 * Returns True if successful, False otherwise.
 */
bool    create_viewport(t_cam *cam, t_viewport *vp)


/*
 * Input: viewport struct with pxl and color information and img struct to draw viewport to.
 * Draws the viewport information into the img buffer, which can then be displayed in a window
 * or manipulated further.
 * Returns True if successful, False otherwise.
 */
bool    draw_viewport(t_viewport *vp, t_img *img)




/*
 * Input: image struct to write to, coordinate of pxl in image and pxl color.
 * Function modifies img content buffer made available through miniLibX.
 * Returns: True upon success, False if copying of pixel information fails.
 */
bool	draw_pixel(t_img *img, t_point *pxl, t_color *pxl_color)
{

}


