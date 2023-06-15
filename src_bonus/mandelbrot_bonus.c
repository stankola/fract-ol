/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:52:38 by tsankola          #+#    #+#             */
/*   Updated: 2023/06/12 20:52:38 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <math.h>
#include "fractol_bonus.h"

void	get_mandelbrot_dimensions(t_dim *dim)
{
	dim->min_r = -2.0;
	dim->max_r = 1.0;
	dim->min_i = -1.2;
	dim->max_i = dim->min_i
		+ (dim->max_r - dim->min_r) * SCREEN_HEIGHT / SCREEN_WIDTH;
}

static int	get_outside_color(int iterations, int max_iterations)
{
	int	color;

	color = (int)round((double)iterations / (double)max_iterations * 255) << 8;
	return (color);
}

static int	get_inside_color(void)
{
	return (BLACK);
}

static int	iterate(t_complex z, t_complex c, int max_iterations)
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
		z.i = 2 * z.r * z.i + c.i;
		z.r = z2.r - z2.i + c.r;
	}
	return (n);
}

// adapted from http://warp.povusers.org/Mandelbrot/
void	render_mandelbrot(t_img *img, t_dim dim, int max_iterations)
{
	int			n;
	int			y;
	int			x;
	t_complex	c;

	y = -1;
	while (++y < SCREEN_HEIGHT)
	{
		c.i = dim.max_i - y * (dim.max_i - dim.min_i) / (SCREEN_HEIGHT - 1);
		x = -1;
		while (++x < SCREEN_WIDTH)
		{
			c.r = dim.min_r + x * (dim.max_r - dim.min_r) / (SCREEN_WIDTH - 1);
			n = iterate((t_complex){c.r, c.i}, c, max_iterations);
			if (n < max_iterations)
				draw_pixel(img, (t_point){x, y},
					get_outside_color(n, max_iterations));
			else
				draw_pixel(img, (t_point){x, y}, get_inside_color());
		}
	}
}
