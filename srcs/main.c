/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 02:37:58 by eshintan          #+#    #+#             */
/*   Updated: 2024/04/28 00:08:33 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	if (n == 0)
// 	{
// 		return (0);
// 	}
// 	while (n > 0)
// 	{
// 		if (*s1 != *s2 || *s1 == '\0' || *s2 == '\0')
// 		{
// 			return ((unsigned char)(*s1) - (unsigned char)(*s2));
// 		}
// 		++s1;
// 		++s2;
// 		--n;
// 	}
// 	return (0);
// }

// size_t	ft_strlen(const char *str)
// {
// 	size_t	i;

// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		i++;
// 	}
// 	return (i);
// }

// void	ft_putstr_fd(char *s, int fd)
// {
// 	if (!s)
// 		return ;
// 	write(fd, s, ft_strlen(s));
// }

// void	malloc_error(void)
// {
// 	ft_putstr_fd("Error\nMalloc error\n", 2);
// 	exit(1);
// }

// // double	atof(const char *str)
// // {
// // 	double	res;
// // 	double	res2;
// // 	char	*c;
// // 	int		len;

// // 	c = (char *)str;
// // 	res = (double)ft_atoi(c);
// // 	while (*c && *c != '.')
// // 		c++;
// // 	if (*c == '.')
// // 		c++;
// // 	res2 = (double)ft_atoi(c);
// // 	len = ft_strlen(c);
// // 	while (len--)
// // 		res2 /= 10;
// // 	if (res >= 0)
// // 		return (res + res2);
// // 	else
// // 		return (res + -res2);
// // }

// /*----------------------------------------------------------------------------------------------------------*/
// int ft_fractal(double z_re, double z_im, double c_re, double c_im)
// {
// 	int n;

// 	n = 0;
// 	while (n < MAX_ITER)
// 	{
// 		double z_re2 = z_re*z_re, z_im2 = z_im*z_im;
// 		if (z_re2 + z_im2 > 4.0)
// 			break; //2を超えると発散する→ループを抜ける
// 		z_im = 2*z_re*z_im + c_im;
// 		z_re = z_re2 - z_im2 + c_re;
// 		++n;
// 	}
// 	return (n);//反復回数に基づいて色を決定
// }

// void fractal_render(t_fractal *fractal, int isJulia)
// {
// 	int x;
// 	int y;
// 	double z_re;
// 	double z_im;

// 	y = 0;
// 	while (y < HEIGHT)
// 	{
// 		x = 0;
// 		while (x < WIDTH)
// 		{
// 			if (isJulia == 1)
// 			{
// 				// ジュリア集合の場合、初期座標zは画面の各ピクセルに対応
// 				z_re = (x - WIDTH/2.0) * 4.0 / WIDTH * fractal->zoom;
// 				z_im = (y - HEIGHT/2.0) * 4.0 / HEIGHT * fractal->zoom;
// 				//julia(引数)
// 				fractal->julia_re = (x - WIDTH/2.0) * 4.0 / WIDTH * fractal->zoom;
// 				fractal->julia_im = (y - HEIGHT/2.0) * 4.0 / HEIGHT * fractal->zoom;
// 			}
// 			else
// 			{
// 				// マンデルブロ集合の場合、初期座標zは常に0
// 				z_re = 0;
// 				z_im = 0;
// 				fractal->julia_re = (x - WIDTH/2.0) * 4.0 / WIDTH * fractal->zoom;
// 				fractal->julia_im = (y - HEIGHT/2.0) * 4.0 / HEIGHT * fractal->zoom;
// 				//mandelbrot(引数)
// 			}
// 			// 集合に属するか計算
// 			int n = ft_fractal(z_re, z_im, fractal->julia_re, fractal->julia_im);
// 			// 色を計算。ここでは単純化のためにnを直接使用
// 			int color = (n % 255) * 0x010101;
// 			// ピクセルに色を設定
// 			*(int*)(fractal->img.addr + y * fractal->img.line_len + x * (fractal->img.bits_per_pixel / 8)) = color;
// 			++x;
// 		}
// 		++y;
// 	}
// }
// /*----------------------------------------------------------------------------------------------------------*/
// void mouse_zoom_in(t_fractal *fractal)
// {
// 	printf("zoom:%f\n", fractal->zoom);
// 	if (fractal->zoom > 0.1)
// 		fractal->zoom *= 0.9;
// 	mlx_destroy_image(fractal->mlx_start, fractal->img.img_ptr);
// 	draw_fractal(fractal, 1);	

// }

// void mouse_zoom_out(t_fractal *fractal)
// {
// 	printf("zoom:%f\n", fractal->zoom);
// 	fractal->zoom *= 1.1;
// 	mlx_destroy_image(fractal->mlx_start, fractal->img.img_ptr);
// 	draw_fractal(fractal, 1);
// }

// int mouse_zoom_hook(int mouse, int x, int y, t_fractal *fractal)
// {
// 	(void)x;
// 	(void)y;
// 	//zoom_in_function
// 	if (mouse == 4)
// 		mouse_zoom_in(fractal);
// 	//zoom_out_function
// 	if (mouse == 5)
// 		mouse_zoom_out(fractal);
// 	return(0);
// }

void fractal_init(t_fractal *fractal)
{
	fractal->mlx_start = mlx_init();
	if (fractal->mlx_start == NULL)
		malloc_error();
	fractal->mlx_window = mlx_new_window(fractal->mlx_start, WIDTH, HEIGHT, "fractol");
	fractal->zoom = 1.0;
}

// int close_esc_buttun(int key, t_fractal *fractal)
// {
// 	if (key == 53)
// 	{
// 		mlx_destroy_window(fractal->mlx_start, fractal->mlx_window);
// 		exit(0);
// 	}
// 	return (0);
// }

// int close_window_buttun(t_fractal *fractal)
// {
// 	mlx_destroy_window(fractal->mlx_start, fractal->mlx_window);
// 	exit(0);
// }
// /*----------------------------------------------------------------------------------------------------------*/
// void	draw_fractal(t_fractal *fractal, int isjulia)
// {
// 	if (NULL == fractal->mlx_window)
// 	{
// 		mlx_destroy_window(fractal->mlx_start, fractal->mlx_window);
// 		free(fractal->mlx_start);
// 		malloc_error();
// 	}
// 	fractal->img.img_ptr = mlx_new_image(fractal->mlx_start, WIDTH, HEIGHT);
// 	if (NULL == fractal->img.img_ptr)
// 	{
// 		mlx_destroy_window(fractal->mlx_start, fractal->mlx_window);
// 		free(fractal->mlx_start);
// 		malloc_error();
// 	}
// 	fractal->img.addr = mlx_get_data_addr(fractal->img.img_ptr, &fractal->img.bits_per_pixel, &fractal->img.line_len, &fractal->img.endian);
// 	fractal_render(fractal, isjulia);
// 	mlx_put_image_to_window(fractal->mlx_start, fractal->mlx_window, fractal->img.img_ptr, 0, 0);
// 	mlx_mouse_hook(fractal->mlx_window, mouse_zoom_hook, fractal);//←add line
// 	mlx_hook(fractal->mlx_window, 2, 1L<<0, close_esc_buttun, fractal);
// 	mlx_hook(fractal->mlx_window, 17, 1L<<17, close_window_buttun, fractal);
// 	mlx_loop(fractal->mlx_start);
// }
/*----------------------------------------------------------------------------------------------------------*/
int	main(int ac, char **av)
{
	t_fractal	fractal = {0};

	if (ac == 2 && !ft_strncmp(av[1], "mandelbrot", 10))
	{
		fractal_init(&fractal);
		draw_fractal(&fractal, 0);
	}
	else if (ac == 4 && !ft_strncmp(av[1], "julia", 5))
	{
		if (atof(av[2]) < -2.0 || atof(av[2]) > 2.0 || atof(av[3]) < -2.0 || atof(av[3]) > 2.0)
		{
			ft_putstr_fd("Error\nInvalid julia set\n", 2);
			return (0);
		}
		fractal.julia_re = atof(av[2]);
		fractal.julia_im = atof(av[3]);
		fractal_init(&fractal);
		draw_fractal(&fractal, 1);
	}
	else
	{
		ft_putstr_fd("Usage: ./fractol [mandelbrot/julia] [julia_re julia_im]\n", 2);
		return (0);
	}
}
