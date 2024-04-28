/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 04:00:10 by emma              #+#    #+#             */
/*   Updated: 2024/04/28 13:25:20 by emma             ###   ########.fr       */
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

int define_color(int n)
{
	int max_iter = 255; //最大繰り返し回数
	double t = (double)n / (double)max_iter; //nを正規化
	//RGB成分を計算。ここでは例として線形グラデーションを使用
	int r = (int)(9 * (1 - t) * t * t * t * 255);
	int g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
	int b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	//RGB値を組み合わせて色を作成
	int color = (r << 16) | (g << 8) | b;
	return (color);
}

void fractal_render(t_fractal *fractal, int isjulia)
{
	int x;
	int y;
	double z_re;
	double z_im;
	int n;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (isjulia == 1)
			{
				z_re = (x - WIDTH/2.0) * 4.0 / WIDTH * fractal->zoom;// ジュリア集合の場合、初期座標zは画面の各ピクセルに対応
				z_im = (y - HEIGHT/2.0) * 4.0 / HEIGHT * fractal->zoom;
			}
			else
			{
				z_re = 0;// マンデルブロ集合の場合、初期座標zは常に0
				z_im = 0;
				fractal->julia_re = (x - WIDTH/2.0) * 4.0 / WIDTH * fractal->zoom;
				fractal->julia_im = (y - HEIGHT/2.0) * 4.0 / HEIGHT * fractal->zoom;
			}
			n = ft_fractal(z_re, z_im, fractal->julia_re, fractal->julia_im);// 集合に属するか計算
			// 色を計算
			int color = define_color(n);
			// ピクセルに色を設定
			*(int*)(fractal->img.addr + y * fractal->img.line_len + x * (fractal->img.bits_per_pixel / 8)) = color;
			++x;
		}
		++y;
	}
}

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
	fractal->img.addr = mlx_get_data_addr(fractal->img.img_ptr, &fractal->img.bits_per_pixel, &fractal->img.line_len, &fractal->img.endian);
	fractal_render(fractal, fractal->isjulia);
	mlx_put_image_to_window(fractal->mlx_start, fractal->mlx_window, fractal->img.img_ptr, 0, 0);
	mlx_mouse_hook(fractal->mlx_window, mouse_zoom_hook, fractal);//←add line
	mlx_hook(fractal->mlx_window, 2, 1L<<0, close_esc_buttun, fractal);
	mlx_hook(fractal->mlx_window, 17, 1L<<17, close_window_buttun, fractal);
	mlx_loop(fractal->mlx_start);
}