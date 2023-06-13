#include <stdlib.h>
#include "fract-ol.h"

void	get_julia_dimensions(t_dim *dim)
{
	dim->minRe = -2.0;
	dim->maxRe = 1.0;
	dim->minIm = -1.2;
	dim->maxIm = dim->minIm +
		(dim->maxRe - dim->minRe) * SCREEN_HEIGHT / SCREEN_WIDTH;
}

// from http://warp.povusers.org/Mandelbrot/
void	render_julia(t_img *img, t_dim dim, unsigned int max_iterations)
{
	long double Re_factor = (dim.maxRe - dim.minRe) / (SCREEN_WIDTH - 1);
	long double Im_factor = (dim.maxIm - dim.minIm) / (SCREEN_HEIGHT - 1);
	long double k_im = 0.288;
	long double k_re = 0.353;

	for (unsigned y=0; y<SCREEN_HEIGHT; ++y)
	{
		long double c_im = dim.maxIm - y * Im_factor;
		for (unsigned x = 0; x < SCREEN_WIDTH; ++x)
		{
			long double c_re = dim.minRe + x * Re_factor;

			long double Z_re = c_re;
			long double Z_im = c_im;
			int isInside = 1;
			for (unsigned n = 0; n < max_iterations; ++n)
			{
				long double Z_re2 = Z_re * Z_re;
				long double Z_im2 = Z_im * Z_im;
				if (Z_re2 + Z_im2 > 4)
				{
					isInside = 0;
					draw_pixel(img, (t_point){x, y}, (5 * (n + 1)));
					break;
				}
				Z_im = 2 * Z_re * Z_im + k_im;
				Z_re = Z_re2 - Z_im2 + k_re;
			}
			if (isInside)
				draw_pixel(img, (t_point){x, y}, BLACK);
		}
	}
}
