/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 04:00:10 by emma              #+#    #+#             */
/*   Updated: 2024/04/27 22:34:40 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int ft_fractal(double z_re, double z_im, double c_re, double c_im)
{
	int n;
	double z_re2;
	double z_im2;

	n = 0;
	while (n < MAX_ITER)
	{
		z_re2 = z_re*z_re, z_im2 = z_im*z_im;
		if (z_re2 + z_im2 > 4.0)
			break; //2を超えると発散する→ループを抜ける
		z_im = 2*z_re*z_im + c_im;
		z_re = z_re2 - z_im2 + c_re;
		++n;
	}
	return (n);//反復回数に基づいて色を決定
}

void fractal_render(t_fractal *fractal, int isJulia)
{
	int x;
	int y;
	double z_re;
	double z_im;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (isJulia == 1)
			{
				// ジュリア集合の場合、初期座標zは画面の各ピクセルに対応
				z_re = (x - WIDTH/2.0) * 4.0 / WIDTH * fractal->zoom;
				z_im = (y - HEIGHT/2.0) * 4.0 / HEIGHT * fractal->zoom;
				//julia(引数)
				fractal->julia_re = (x - WIDTH/2.0) * 4.0 / WIDTH * fractal->zoom;
				fractal->julia_im = (y - HEIGHT/2.0) * 4.0 / HEIGHT * fractal->zoom;
			}
			else
			{
				// マンデルブロ集合の場合、初期座標zは常に0
				z_re = 0;
				z_im = 0;
				fractal->julia_re = (x - WIDTH/2.0) * 4.0 / WIDTH * fractal->zoom;
				fractal->julia_im = (y - HEIGHT/2.0) * 4.0 / HEIGHT * fractal->zoom;
				//mandelbrot(引数)
			}
			// 集合に属するか計算
			int n = ft_fractal(z_re, z_im, fractal->julia_re, fractal->julia_im);
			// 色を計算。ここでは単純化のためにnを直接使用
			int color = (n % 255) * 0x010101;
			// ピクセルに色を設定
			*(int*)(fractal->img.addr + y * fractal->img.line_len + x * (fractal->img.bits_per_pixel / 8)) = color;
			++x;
		}
		++y;
	}
}

void	draw_fractal(t_fractal *fractal, int isjulia)
{
	if (NULL == fractal->mlx_window)
	{
		mlx_destroy_window(fractal->mlx_start, fractal->mlx_window);
		free(fractal->mlx_start);
		malloc_error();
	}
	fractal->img.img_ptr = mlx_new_image(fractal->mlx_start, WIDTH, HEIGHT);
	if (NULL == fractal->img.img_ptr)
	{
		mlx_destroy_window(fractal->mlx_start, fractal->mlx_window);
		free(fractal->mlx_start);
		malloc_error();
	}
	fractal->img.addr = mlx_get_data_addr(fractal->img.img_ptr, &fractal->img.bits_per_pixel, &fractal->img.line_len, &fractal->img.endian);
	fractal_render(fractal, isjulia);
	mlx_put_image_to_window(fractal->mlx_start, fractal->mlx_window, fractal->img.img_ptr, 0, 0);
	mlx_mouse_hook(fractal->mlx_window, mouse_zoom_hook, fractal);//←add line
	mlx_hook(fractal->mlx_window, 2, 1L<<0, close_esc_buttun, fractal);
	mlx_hook(fractal->mlx_window, 17, 1L<<17, close_window_buttun, fractal);
	mlx_loop(fractal->mlx_start);
}