/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 02:37:58 by eshintan          #+#    #+#             */
/*   Updated: 2024/09/23 07:29:26 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#define ERRMSG "Usage: ./fractol [mandelbrot/julia] [julia_re julia_im]\n"

int	is_double(char *str)
{
	int	i;
	int	dot;

	i = 0;
	dot = 0;
	if (str[i] == '\0' || ((str[i] == '.') && (str[i + 1] == '\0')))
		return (0);
	if ((str[i] == '-' || str[i] == '+') && !ft_isdigit(str[i + 1]))
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '.')
		return (0);
	while (str[i])
	{
		if (str[i] == '.' && (!ft_isdigit(str[i + 1])))
			return (0);
		if (str[i] == '.')
			dot++;
		if (!ft_isdigit(str[i]) && str[i] != '.')
			return (0);
		i++;
	}
	return (!(dot > 1));
}

int	valid_arg(int argc, char **argv)
{
	if (argc == 2 && !ft_memcmp(argv[1], "mandelbrot", 10))
		return (1);
	if (argc == 4 && !ft_memcmp(argv[1], "julia", 5)
		&& (is_double(argv[2])) && (is_double(argv[3])))
		return (1);
	return (0);
}

void	fractal_init(t_fractal *fractal)
{
	fractal->mlx_start = mlx_init();
	if (fractal->mlx_start == NULL)
		malloc_error();
	fractal->mlx_window = mlx_new_window(fractal->mlx_start, WIDTH, HEIGHT,
			"fractol");
	fractal->zoom = 1.0;
}

int	main(int ac, char **av)
{
	t_fractal	fractal;

	if (!valid_arg(ac, av))
		ft_putstr_fd("Usage: error!\n", 2);
	else if (ac == 2 && !ft_memcmp(av[1], "mandelbrot", 11))
	{
		fractal_init(&fractal);
		draw_fractal(&fractal, 0);
	}
	else if (ac == 4 && !ft_memcmp(av[1], "julia", 6))
	{
		if (atof(av[2]) < -2.0 || atof(av[2]) > 2.0 || atof(av[3]) < -2.0
			|| atof(av[3]) > 2.0)
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
		ft_putstr_fd(ERRMSG, 2);
	return (0);
}
