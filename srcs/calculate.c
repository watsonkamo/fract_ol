/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 05:19:47 by emma              #+#    #+#             */
/*   Updated: 2024/09/23 07:16:34 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	calculate_julia(int x, int y, t_fractal *fractal, t_coords *coords)
{
	coords->z_re = (x - WIDTH / 2.0) * 4.0 / WIDTH * fractal->zoom;
	coords->z_im = (y - HEIGHT / 2.0) * 4.0 / WIDTH * fractal->zoom;
}

void	calculate_mandelbrot(int x, int y, t_fractal *fractal, t_coords *coords)
{
	coords->julia_re = (x - WIDTH / 2.0) * 4.0 / WIDTH * fractal->zoom;
	coords->julia_im = (y - HEIGHT / 2.0) * 4.0 / WIDTH * fractal->zoom;
}

void	render_pixel(t_fractal *fractal, int x, int y, int isjulia)
{
	t_coords	coords;
	int			n;
	int			color;

	coords.isjulia = isjulia;
	if (coords.isjulia == 1)
	{
		coords.julia_re = fractal->julia_re;
		coords.julia_im = fractal->julia_im;
		calculate_julia(x, y, fractal, &coords);
	}
	else
	{
		coords.z_re = 0;
		coords.z_im = 0;
		calculate_mandelbrot(x, y, fractal, &coords);
	}
	n = ft_fractal(coords.z_re, coords.z_im, coords.julia_re, coords.julia_im);
	color = define_color(n);
	*(int *)(fractal->img.addr + y * fractal->img.line_len + x
			* (fractal->img.bits_per_pixel / 8)) = color;
}
