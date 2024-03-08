/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eshintan <eshintan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 02:37:58 by eshintan          #+#    #+#             */
/*   Updated: 2024/03/08 12:50:34 by eshintan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "fractol.h"
// #include "libft/libft.h"
#include "fractol.h"

static void	malloc_error(void)
{
	ft_putstr_fd("Error\nMalloc error\n", 2);
	exit(1);
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

void	draw_fractal(t_fractal *fractal)
{
	fractal->mlx_start = mlx_init();
	if (NULL == fractal->mlx_start)
	{
		malloc_error();
	}
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
		//mlx_destroy_display(fractal->mlx_start);
		free(fractal->mlx_start);
		malloc_error();
	}
	fractal->img.addr = mlx_get_data_addr(fractal->img.img_ptr, &fractal->img.bits_per_pixel, &fractal->img.line_len, &fractal->img.endian);
	mlx_put_image_to_window(fractal->mlx_start, fractal->mlx_window, fractal->img.img_ptr, 0, 0);
	mlx_loop(fractal->mlx_start);
}

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

//rendering fractals
void	fractal_render(t_fractal *fractal)
{
	int x;
	int y;
	
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			fractal->img.addr[y * fractal->img.line_len + x * (fractal->img.bits_per_pixel / 8)] = 0;
			fractal->img.addr[y * fractal->img.line_len + x * (fractal->img.bits_per_pixel / 8) + 1] = 0;
			fractal->img.addr[y * fractal->img.line_len + x * (fractal->img.bits_per_pixel / 8) + 2] = 0;
			fractal->img.addr[y * fractal->img.line_len + x * (fractal->img.bits_per_pixel / 8) + 3] = 0;
			++x;
		}
		++y;
	}

}

