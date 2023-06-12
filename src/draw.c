//TODO: Header

#include "fract-ol.h"

// endian: 0 == Little-endian, 1 == Big-endian
// If p is out of bounds, nothing will be drawn
void	draw_pixel(t_img *img, t_point p, int color)
{
	char	*dst;

	if (!check_bounds(p))
		return ;
	dst = img->addr + (p.y * img->line_length + p.x * (img->bpp / 8));
	if (img->endian == 0)
		*(unsigned int*)dst = color;
	else
		*(unsigned int*)dst = invert_int_by_bytes(color, img->bpp / 8);
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