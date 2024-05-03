/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 02:37:58 by eshintan          #+#    #+#             */
/*   Updated: 2024/05/01 17:25:13 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int is_double(char *str)
{
	int i;
	int dot;

	i = 0;
	dot = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (!ft_isdigit(str[i + 1]))
			return (0);
		i++;
	}
	while (str[i])
	{
		if (str[i] == '.')
			dot++;
		if (!ft_isdigit(str[i]) && str[i] != '.')
			return (0);
		i++;
	}
	if (dot > 1)
		return (0);
	return (1);

}

int valid_arg(int argc, char **argv)
{
	if (argc == 2 && !ft_strncmp(argv[1], "mandelbrot", 10))
		return (1);
	if (argc == 4 && !ft_strncmp(argv[1], "julia", 5) && is_double(argv[2]) && is_double(argv[3]))
		return (1);
	return (0);
}

void fractal_init(t_fractal *fractal)
{
	fractal->mlx_start = mlx_init();
	if (fractal->mlx_start == NULL)
		malloc_error();
	fractal->mlx_window = mlx_new_window(fractal->mlx_start, WIDTH, HEIGHT, "fractol");
	fractal->zoom = 1.0;
}
/*----------------------------------------------------------------------------------------------------------*/
int	main(int ac, char **av)
{
	t_fractal	fractal = {0};

	if (!valid_arg(ac, av))
	{
		ft_putstr_fd("Usage: arg error!\n", 2);
		return (0);
	}
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
