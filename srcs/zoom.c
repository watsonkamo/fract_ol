/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 04:01:11 by emma              #+#    #+#             */
/*   Updated: 2024/05/08 15:27:56 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mouse_zoom_in(t_fractal *fractal)
{
	printf("zoom:%f\n", fractal->zoom);
	if (fractal->zoom > 0.1)
		fractal->zoom *= 0.9;
	mlx_destroy_image(fractal->mlx_start, fractal->img.img_ptr);
	draw_fractal(fractal, fractal->isjulia);
}

void	mouse_zoom_out(t_fractal *fractal)
{
	printf("zoom:%f\n", fractal->zoom);
	fractal->zoom *= 1.1;
	mlx_destroy_image(fractal->mlx_start, fractal->img.img_ptr);
	draw_fractal(fractal, fractal->isjulia);
}

int	mouse_zoom_hook(int mouse, int x, int y, t_fractal *fractal)
{
	(void) x;
	(void) y;
	if (mouse == 4)
		mouse_zoom_in(fractal);
	if (mouse == 5)
		mouse_zoom_out(fractal);
	return (0);
}
