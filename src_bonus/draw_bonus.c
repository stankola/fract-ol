/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:27:12 by tsankola          #+#    #+#             */
/*   Updated: 2023/06/12 14:27:16 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol_bonus.h"

// Might need to reconsider this. If origin is in the center of the screen,
// negative values should be permitted.
int	check_bounds(t_point p)
{
	if (p.x < 0 || p.y < 0 || p.x > SCREEN_WIDTH || p.y > SCREEN_HEIGHT)
		return (0);
	return (1);
}

// endian: 0 == Little-endian, 1 == Big-endian
// If p is out of bounds, nothing will be drawn
void	draw_pixel(t_img *img, t_point p, int color)
{
	char	*dst;

	if (!check_bounds(p))
		return ;
	dst = img->addr + (p.y * img->line_length + p.x * (img->bpp / 8));
	if (img->endian == 0)
		*(unsigned int *)dst = color;
	else
		*(unsigned int *)dst = invert_int_by_bytes(color, img->bpp / 8);
}

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
