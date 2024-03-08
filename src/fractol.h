/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eshintan <eshintan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 03:11:33 by eshintan          #+#    #+#             */
/*   Updated: 2024/03/08 11:28:56 by eshintan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H

//# include "libft.h"
# include "minilibx-linux/mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

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
}               t_fractal;

int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *str);
void	draw_fractal(t_fractal *fractal);
static void	malloc_error(void);

# define WIDTH 800

# define HEIGHT 800

# define MAX_ITER 100

# define ZOOM 1.1

# define MOVE 0.1

# define RED 0x00FF0000

# define GREEN 0x0000FF00

# define BLUE 0x000000FF

# define WHITE 0x00FFFFFF

# define BLACK 0x00000000

# define YELLOW 0x00FFFF00

# define PURPLE 0x00FF00FF

# define CYAN 0x0000FFFF

# define ORANGE 0x00FFA500

# define PINK 0x00FFC0CB

# define BROWN 0x00A52A2A

# define GREY 0x00808080

#endif