#include "fract-ol.h"
#include <math.h>

// Draws a circle centered at x,y with radius
int render_circle(t_img *img, t_point p, int radius, int color)
{
	int		x;
	int		y;
	double	r;

	r = radius * radius;
	x = -my_round(r);
	while (x <= my_round(r))
	{
		y = my_round(sqrt(r - x * x));
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