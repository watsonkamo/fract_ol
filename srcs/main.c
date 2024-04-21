/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 02:37:58 by eshintan          #+#    #+#             */
/*   Updated: 2024/04/21 13:22:29 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft/libft.h"

#include <libc.h>
#include "fractol.h"
#include <math.h>

#define MAX_ITER 100 // 最大反復回数

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
	{
		return (0);
	}
	while (n > 0)
	{
		if (*s1 != *s2 || *s1 == '\0' || *s2 == '\0')
		{
			return ((unsigned char)(*s1) - (unsigned char)(*s2));
		}
		++s1;
		++s2;
		--n;
	}
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

static void	malloc_error(void)
{
	ft_putstr_fd("Error\nMalloc error\n", 2);
	exit(1);
}





//rendering fractals
// void	fractal_render(t_fractal *fractal)
// {
// 	int x;
// 	int y;
	
// 	y = 0;
// 	while (y < HEIGHT)
// 	{
// 		x = 0;
// 		while (x < WIDTH)
// 		{
// 			fractal->img.addr[y * fractal->img.line_len + x * (fractal->img.bits_per_pixel / 8)] = 0;
// 			fractal->img.addr[y * fractal->img.line_len + x * (fractal->img.bits_per_pixel / 8) + 1] = 0;
// 			fractal->img.addr[y * fractal->img.line_len + x * (fractal->img.bits_per_pixel / 8) + 2] = 255;
// 			fractal->img.addr[y * fractal->img.line_len + x * (fractal->img.bits_per_pixel / 8) + 3] = 0;
// 			++x;
// 		}
// 		++y;
// 	}

// }


#define JULIA_RE -0.7 // ジュリア集合の実数部
#define JULIA_IM 0.27015 // ジュリア集合の虚数部

int ft_fractal(double z_re, double z_im, double c_re, double c_im)
{
    int n = 0;
    for (; n < MAX_ITER; ++n)
    {
        double z_re2 = z_re*z_re, z_im2 = z_im*z_im;
        if (z_re2 + z_im2 > 4.0)
            break; // 2を超えると発散するため、ループを抜ける
        z_im = 2*z_re*z_im + c_im;
        z_re = z_re2 - z_im2 + c_re;
    }
    return n; // 反復回数に基づいて色を決定
}

void fractal_render(t_fractal *fractal, int isJulia)
{
    int x, y;
    double c_re, c_im;

    for (y = 0; y < HEIGHT; ++y)
    {
        for (x = 0; x < WIDTH; ++x)
        {
            // 座標を集合の範囲に変換
            double z_re = (x - WIDTH/2.0)*4.0/WIDTH;
            double z_im = (y - HEIGHT/2.0)*4.0/WIDTH;
            
            if (isJulia)
            {
                // ジュリア集合の場合
                c_re = JULIA_RE;
                c_im = JULIA_IM;
            }
            else
            {
                // マンデルブロ集合の場合
                c_re = z_re;
                c_im = z_im;
                z_re = 0;
                z_im = 0;
            }
            // 集合に属するかを計算
            int n = ft_fractal(z_re, z_im, c_re, c_im);
            // 色を計算（ここでは単純化のためにnを直接使用）
            int color = (n % 255) * 0x010101;
            // ピクセルに色を設定
            *(int*)(fractal->img.addr + y * fractal->img.line_len + x * (fractal->img.bits_per_pixel / 8)) = color;
        }
    }
}


void	draw_fractal(t_fractal *fractal)
{
	fractal->mlx_start = mlx_init();
	if (NULL == fractal->mlx_start)
		malloc_error();
	fractal->mlx_window = mlx_new_window(fractal->mlx_start, WIDTH, HEIGHT, "fractol");
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
	fractal_render(fractal, 1);
	mlx_put_image_to_window(fractal->mlx_start, fractal->mlx_window, fractal->img.img_ptr, 0, 0);
	mlx_loop(fractal->mlx_start);
}

int	main(int ac, char **av)
{
	t_fractal	fractal;

	if (ac == 2 && !ft_strncmp(av[1], "mandelbrot", 10))
	{
		draw_fractal(&fractal);
	}
	else if (ac == 2 && !ft_strncmp(av[1], "julia", 5))
	{
		draw_fractal(&fractal);
	}
	else
	{
		ft_putstr_fd("Usage: ./fractol [mandelbrot/julia]\n", 2);
		return (0);
	}
}