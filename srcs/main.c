/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 02:37:58 by eshintan          #+#    #+#             */
/*   Updated: 2024/04/21 21:13:59 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

int ft_fractal(double z_re, double z_im, double c_re, double c_im)
{
    int n;

	n = 0;
    while (n < MAX_ITER)
    {
        double z_re2 = z_re*z_re, z_im2 = z_im*z_im;
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
            if (isJulia)
            {
                // ジュリア集合の場合、初期座標zは画面の各ピクセルに対応
                z_re = (x - WIDTH/2.0) * 4.0 / WIDTH;
                z_im = (y - HEIGHT/2.0) * 4.0 / HEIGHT;
				//julia(引数)
            }
            else
            {
                // マンデルブロ集合の場合、初期座標zは常に0
                z_re = 0;
                z_im = 0;
                fractal->julia_re = (x - WIDTH/2.0) * 4.0 / WIDTH;
                fractal->julia_im = (y - HEIGHT/2.0) * 4.0 / HEIGHT;
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

int mouse_zoom_hook(int mouse, int x, int y, t_fractal *fractal)
{
	//zoom_in_function
	if (mouse == 4)
	{
		fractal->julia_re += (x - WIDTH / 2.0) * 4.0 / WIDTH * (ZOOM - 1);
		fractal->julia_im += (y - HEIGHT / 2.0) * 4.0 / HEIGHT * (ZOOM - 1);
	}
	//zoom_out_function
	else if (mouse == 5)
	{
		fractal->julia_re -= (x - WIDTH / 2.0) * 4.0 / WIDTH * (ZOOM - 1);
		fractal->julia_im -= (y - HEIGHT / 2.0) * 4.0 / HEIGHT * (ZOOM - 1);
	}
	return(0);
}

void	draw_fractal(t_fractal *fractal, int isjulia)
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
	fractal_render(fractal, isjulia);
	mlx_put_image_to_window(fractal->mlx_start, fractal->mlx_window, fractal->img.img_ptr, 0, 0);
	mlx_mouse_hook(fractal->mlx_window, mouse_zoom_hook, fractal);//←add line
	mlx_loop(fractal->mlx_start);
}



int	main(int ac, char **av)
{
	t_fractal	fractal = {0};

	if (ac == 2 && !ft_strncmp(av[1], "mandelbrot", 10))
		draw_fractal(&fractal, 0);
	else if (ac == 4 && !ft_strncmp(av[1], "julia", 5))
	{
		if (atof(av[2]) < -2.0 || atof(av[2]) > 2.0 || atof(av[3]) < -2.0 || atof(av[3]) > 2.0)
		{
			ft_putstr_fd("Error\nInvalid julia set\n", 2);
			return (0);
		}
		fractal.julia_re = atof(av[2]);
		fractal.julia_im = atof(av[3]);
		draw_fractal(&fractal, 1);
	}
	else
	{
		ft_putstr_fd("Usage: ./fractol [mandelbrot/julia] [julia_re julia_im]\n", 2);
		return (0);
	}
}
