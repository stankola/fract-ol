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
#include "fract-ol.h"
#include <math.h>

void	render_fractal(t_data *data)
{
	if (data->fractal == MANDELBROT)
	{
		if (data->initialize)
			get_mandelbrot_dimensions(&(data->dim));
		render_mandelbrot(&(data->img), data->dim, MANDELBROT_ITERATIONS);
	}
	else if (data->fractal == JULIA)
	{
		if (data->initialize)
			get_julia_dimensions(&(data->dim));
		render_julia(&(data->img), data->dim, JULIA_ITERATIONS);
	}
	data->initialize = 0;
}

// Draws a circle centered at x,y with radius
int render_circle(t_img *img, t_point p, int radius, int color)
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

int render_square(t_img *img, t_point p, int size, int color)
{
	int	i;
	int j;

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
