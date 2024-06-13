/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eshintan <eshintan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 04:00:10 by emma              #+#    #+#             */
/*   Updated: 2024/06/13 22:29:02 by eshintan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_fractal(double z_re, double z_im, double c_re, double c_im)
{
	int		n;
	double	z_re2;
	double	z_im2;

	n = 0;
	while (n < MAX_ITER)
	{
		z_re2 = z_re * z_re;
		z_im2 = z_im * z_im;
		if (z_re2 + z_im2 > 4.0)
			break ;
		z_im = 2 * z_re * z_im + c_im;
		z_re = z_re2 - z_im2 + c_re;
		++n;
	}
	return (n);
}

int	define_color(int n)
{
	double	t;
	int		red;
	int		green;
	int		blue;

	if (n == MAX_ITER)
		return (0x000000);
	t = (double)n / (double)MAX_ITER;
	red = (int)(9 * (1 - t) * t * t * t * 255);
	green = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
	blue = (int)(9 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	return ((red << 16) | (green << 8) | blue);
}

void	calculate_r_julia(t_fractal *fractal, double x, double y, t_render *r)
{
	r->re = (x - WIDTH / 2.0) * 4.0 / WIDTH * fractal->zoom;
	r->im = (y - HEIGHT / 2.0) * 4.0 / HEIGHT * fractal->zoom;
}

void	calculate_r_mandel(t_fractal *fractal, double x, double y, t_render *r)
{
	r->re = 0;
	r->im = 0;
	fractal->julia_re = (x - WIDTH / 2.0) * 4.0 / WIDTH * fractal->zoom;
	fractal->julia_im = (y - HEIGHT / 2.0) * 4.0 / HEIGHT * fractal->zoom;
}

void	plot_pixel(t_fractal *fractal, int x, int y, t_render r)
{
	int	n;

	n = ft_fractal(r.re, r.im, fractal->julia_re, fractal->julia_im);
	*(int *)(fractal->img.addr + y * fractal->img.line_len + x
			* (fractal->img.bits_per_pixel / 8)) = define_color(n);
}

void	fractal_render(t_fractal *fractal, int isjulia)
{
	int			x;
	int			y;
	t_render	r;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (isjulia)
				calculate_r_julia(fractal, x, y, &r);
			else
				calculate_r_mandel(fractal, x, y, &r);
			plot_pixel(fractal, x, y, r);
			++x;
		}
		++y;
	}
}
// void	fractal_render(t_fractal *fractal, int isjulia)
// {
// 	int			x;
// 	int			y;
// 	int			n;
// 	t_render	r;

// 	y = 0;
// 	while (y < HEIGHT)
// 	{
// 		x = 0;
// 		while (x < WIDTH)
// 		{
// 			if (isjulia == 1)
// 			{
// 				r.re = (x - WIDTH / 2.0) * 4.0 / WIDTH * fractal->zoom;
// 				r.im = (y - HEIGHT / 2.0) * 4.0 / HEIGHT * fractal->zoom;
// 			}
// 			else
// 			{
// 				r.re = 0;
// 				r.im = 0;
// 				fractal->julia_re = (x - WIDTH / 2.0) * 4.0 / WIDTH
// 					* fractal->zoom;
// 				fractal->julia_im = (y - HEIGHT / 2.0) * 4.0 / HEIGHT
// 					* fractal->zoom;
// 			}
// 			n = ft_fractal(r.re, r.im, fractal->julia_re, fractal->julia_im);
// 			*(int *)(fractal->img.addr + y * fractal->img.line_len + x
// 					* (fractal->img.bits_per_pixel / 8)) = define_color(n);
// 			++x;
// 		}
// 		++y;
// 	}
// }

void	draw_fractal(t_fractal *fractal, int isjulia)
{
	fractal->isjulia = isjulia;
	if (fractal->mlx_window == NULL)
	{
		mlx_destroy_window(fractal->mlx_start, fractal->mlx_window);
		free(fractal->mlx_start);
		malloc_error();
	}
	fractal->img.img_ptr = mlx_new_image(fractal->mlx_start, WIDTH, HEIGHT);
	if (fractal->img.img_ptr == NULL)
	{
		mlx_destroy_window(fractal->mlx_start, fractal->mlx_window);
		free(fractal->mlx_start);
		malloc_error();
	}
	fractal->img.addr = mlx_get_data_addr(fractal->img.img_ptr,
			&fractal->img.bits_per_pixel, &fractal->img.line_len,
			&fractal->img.endian);
	fractal_render(fractal, fractal->isjulia);
	mlx_put_image_to_window(fractal->mlx_start, fractal->mlx_window,
		fractal->img.img_ptr, 0, 0);
	mlx_mouse_hook(fractal->mlx_window, mouse_zoom_hook, fractal);
	mlx_hook(fractal->mlx_window, 2, 1L << 0, close_esc_buttun, fractal);
	mlx_hook(fractal->mlx_window, 17, 1L << 17, close_window_buttun, fractal);
	mlx_loop(fractal->mlx_start);
}
