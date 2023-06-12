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
#include "fract-ol.h"

//void	iterate(t_point p, double Z_re, double Z_im)

// from http://warp.povusers.org/Mandelbrot/
void	render_mandelbrot(t_img *img, unsigned int MaxIterations)
{
	double MinRe = -2.0;
	double MaxRe = 1.0;
	double MinIm = -1.2;
	double MaxIm = MinIm + (MaxRe - MinRe) * SCREEN_HEIGHT / SCREEN_WIDTH;
	double Re_factor = (MaxRe - MinRe) / (SCREEN_WIDTH - 1);
	double Im_factor = (MaxIm - MinIm) / (SCREEN_HEIGHT - 1);

	for(unsigned y=0; y<SCREEN_HEIGHT; ++y)
	{
		double c_im = MaxIm - y * Im_factor;
		for(unsigned x = 0; x < SCREEN_WIDTH; ++x)
		{
			double c_re = MinRe + x * Re_factor;

			double Z_re = c_re;
			double Z_im = c_im;
			int isInside = 1;
			for(unsigned n = 0; n < MaxIterations; ++n)
			{
				double Z_re2 = Z_re * Z_re;
				double Z_im2 = Z_im * Z_im;
				if(Z_re2 + Z_im2 > 4)
				{
					isInside = 0;
					draw_pixel(img, (t_point){x, y}, (n * 5) << 16);
					break;
				}
				Z_im = 2 * Z_re * Z_im + c_im;
				Z_re = Z_re2 - Z_im2 + c_re;
			}
			if(isInside)
			{
				draw_pixel(img, (t_point){x, y}, BLACK);
			}
		}
	}
}