/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:52:38 by tsankola          #+#    #+#             */
/*   Updated: 2023/06/12 20:52:38 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <math.h>
#include "fract-ol.h"

void	get_mandelbrot_dimensions(t_dim *dim)
{
	dim->minRe = -2.0;
	dim->maxRe = 1.0;
	dim->minIm = -1.2;
	dim->maxIm = dim->minIm +
		(dim->maxRe - dim->minRe) * SCREEN_HEIGHT / SCREEN_WIDTH;
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

// adapted from http://warp.povusers.org/Mandelbrot/
void	render_mandelbrot(t_img *img, t_dim dim, int max_iterations)
{
	long double Re_factor = (dim.maxRe - dim.minRe) / (SCREEN_WIDTH - 1);
	long double Im_factor = (dim.maxIm - dim.minIm) / (SCREEN_HEIGHT - 1);
	int	n;

	for (unsigned y=0; y<SCREEN_HEIGHT; ++y)
	{
		long double c_im = dim.maxIm - y * Im_factor;
		for (unsigned x = 0; x < SCREEN_WIDTH; ++x)
		{
			long double c_re = dim.minRe + x * Re_factor;

			long double Z_im = c_im;
			long double Z_re = c_re;
			int isInside = 1;
			n = -1;
			while (++n < max_iterations)
			{
				long double Z_re2 = Z_re * Z_re;
				long double Z_im2 = Z_im * Z_im;
				if (Z_re2 + Z_im2 > 4)
				{
					isInside = 0;
					draw_pixel(img, (t_point){x, y}, get_outside_color(n, max_iterations));
					break;
				}
				Z_im = 2 * Z_re * Z_im + c_im;
				Z_re = Z_re2 - Z_im2 + c_re;
			}
			if (isInside)
				draw_pixel(img, (t_point){x, y}, get_inside_color());
		}
	}
}
