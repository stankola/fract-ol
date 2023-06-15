/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:36:15 by tsankola          #+#    #+#             */
/*   Updated: 2023/06/15 17:36:15 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <math.h>
#include "fractol_bonus.h"

void	get_julia_dimensions(t_dim *dim)
{
	dim->min_r = -2.0;
	dim->max_r = 2.0;
	dim->min_i = -2;
	dim->max_i = dim->min_i
		+ (dim->max_r - dim->min_r) * SCREEN_HEIGHT / SCREEN_WIDTH;
}

static int	get_outside_color(int iterations, int max_iterations)
{
	int	color;

	color = (int)round((2 - (2
					/ (1 + (double)iterations / (double)max_iterations)))
			* 255);
	return (color);
}

static int	get_inside_color(void)
{
	return (WHITE);
}

static int	iterate(t_complex z, t_complex k, int max_iterations)
{
	int			n;
	t_complex	z2;

	n = -1;
	while (++n < max_iterations)
	{
		z2.r = z.r * z.r;
		z2.i = z.i * z.i;
		if (z2.r + z2.i > 4)
			break ;
		z.i = 2 * z.r * z.i + k.i;
		z.r = z2.r - z2.i + k.r;
	}
	return (n);
}

// adapted from http://warp.povusers.org/Mandelbrot/
void	render_julia(t_img *img, t_dim dim, t_complex k, int max_iterations)
{
	int			n;
	int			y;
	int			x;
	t_complex	z;

	y = -1;
	while (++y < SCREEN_HEIGHT)
	{
		z.i = dim.max_i - y * (dim.max_i - dim.min_i) / (SCREEN_HEIGHT - 1);
		x = -1;
		while (++x < SCREEN_WIDTH)
		{
			z.r = dim.min_r + x * (dim.max_r - dim.min_r) / (SCREEN_WIDTH - 1);
			n = iterate(z, k, max_iterations);
			if (n < max_iterations)
				draw_pixel(img, (t_point){x, y},
					get_outside_color(n, max_iterations));
			else
				draw_pixel(img, (t_point){x, y}, get_inside_color());
		}
	}
}
