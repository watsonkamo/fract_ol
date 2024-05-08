/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 04:01:55 by emma              #+#    #+#             */
/*   Updated: 2024/05/08 15:16:22 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	close_esc_buttun(int key, t_fractal *fractal)
{
	if (key == 53)
	{
		mlx_destroy_window(fractal->mlx_start, fractal->mlx_window);
		exit(0);
	}
	return (0);
}

int	close_window_buttun(t_fractal *fractal)
{
	mlx_destroy_window(fractal->mlx_start, fractal->mlx_window);
	exit(0);
}
