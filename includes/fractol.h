/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 03:11:33 by eshintan          #+#    #+#             */
/*   Updated: 2024/09/23 07:17:30 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H

//# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <libc.h>

//image
//this is basically a pixels buffer
//values from mlx_get_data_addr
//mlx_get_data_addr returns a pointer to the image data
typedef struct s_image
{
    void    *img_ptr;//pointer to the image
    char    *addr;//pointer to the first pixel in the image
    int     bits_per_pixel;//number of bits needed to represent a pixel color
    int     line_len;//size of a line in bytes
    int     endian;//endianness of the image

}   t_image;

//fractal
//mlxstuff
//this is the main struct that holds all the mlx stuff

typedef struct s_fractal
{
    //MLX
    void    *mlx_start;
    void    *mlx_window;
    //image
    t_image img;
    //hooks member variables
    double  julia_re;
    double  julia_im;
    double  zoom;
    int     isjulia;
    double  c_re;
    double  c_im;
}               t_fractal;

typedef struct s_coords {
    double  z_re;
    double  z_im;
    double  julia_re;
    double  julia_im;
    int     isjulia;
}   t_coords;

int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *str);
int     ft_fractal(double z_re, double z_im, double c_re, double c_im);
void    fractal_render(t_fractal *fractal, int isjulia);
void	draw_fractal(t_fractal *fractal, int isjulia);
void	malloc_error(void);
void    mouse_zoom_in(t_fractal *fractal);
void    mouse_zoom_out(t_fractal *fractal);
int     mouse_zoom_hook(int mouse, int x, int y, t_fractal *fractal);
int     close_esc_buttun(int key, t_fractal *fractal);
int     close_window_buttun(t_fractal *fractal);
void    fractal_init(t_fractal *fractal);
int 	valid_arg(int argc, char **argv);
void	calculate_julia(int x, int y, t_fractal *fractal, t_coords *coords);
void	calculate_mandelbrot(int x, int y, t_fractal *fractal, t_coords *coords);
void	render_pixel(t_fractal *fractal, int x, int y, int isjulia);
int	define_color(int n);
int is_double(char *str);
int ft_isdigit(int c);
int	ft_memcmp(const void *s1, const void *s2, size_t n);

# define WIDTH 700

# define HEIGHT 700

# define MAX_ITER 255//最大反復回数

# define ZOOM 1.1

# define MOVE 0.1

# define WHITE 0x00FFFFFF

# define BLACK 0x00000000

# define BLUE 0x000000FF


#endif