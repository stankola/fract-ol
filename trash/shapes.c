/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:27:19 by tsankola          #+#    #+#             */
/*   Updated: 2023/06/12 14:27:26 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <math.h>
#include "fractol.h"

void	render_fractal(t_data *d)
{
	if (d->fractal == MANDELBROT)
	{
		if (d->initialize)
			get_mandelbrot_dimensions(&(d->dim));
		render_mandelbrot(&(d->img), d->dim, MANDELBROT_ITERATIONS);
	}
	else if (d->fractal == JULIA)
	{
		if (d->initialize)
			get_julia_dimensions(&(d->dim));
		render_julia(&(d->img), d->dim, d->parameter, JULIA_ITERATIONS);
	}
	d->initialize = 0;
}

// Draws a circle centered at x,y with radius
int	render_circle(t_img *img, t_point p, int radius, int color)
{
	int		x;
	int		y;
	double	r;

	r = radius * radius;
	x = -round(r);
	while (x <= r)
	{
		y = round(sqrt(r - x * x));
		draw_pixel(img, (t_point){p.x + x, p.y + y}, color);
		draw_pixel(img, (t_point){p.x + x, p.y - y}, color);
		x++;
	}
	return (0);
}

int	render_square(t_img *img, t_point p, int size, int color)
{
	int	i;
	int	j;

	i = p.x;
	while (i < p.y + size)
	{
		j = p.x;
		while (j < p.x + size)
			draw_pixel(img, (t_point){j++, i}, color);
		++i;
	}
	return (0);
}

void	render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < SCREEN_HEIGHT)
	{
		j = 0;
		while (j < SCREEN_WIDTH)
		{
			draw_pixel(img, (t_point){j++, i}, color);
		}
		++i;
	}
}
