/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 12:00:35 by tsankola          #+#    #+#             */
/*   Updated: 2023/06/01 12:00:35 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fract-ol.h"
#include "mlx.h"
#include "libft.h"
#include <limits.h>
#include <stdio.h>
#include <math.h>

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

// Draws a circle centered at x,y with radius
int render_circle(t_img *img, t_point p, int radius, int color)
{
	int		x;
	int		y;
	double	r;

	r = pow(radius, 2);
	x = -my_round(r);
	while (x <= my_round(r))
	{
		y = my_round(sqrt(r - pow(x, 2)));
//		ft_printf("y = %d\n", y);
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

int	render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);
	render_background(&data->img, 0x00FF0000);
	render_square(&(data->img), (t_point){10, 10}, 10, 0x00FFFFFF);
	render_circle(&(data->img), (t_point){320, 240}, 200, 0x000000FF);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	mlx_string_put(data->mlx_ptr, data->win_ptr, 320, 240, 0x0000FF00, "All your base are belong to us");

	return (0);
}

int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
	data.img.img = mlx_new_image(data.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bpp, &data.img.line_length,
								&data.img.endian);
	ft_printf("bpp %d linlen %d endian %d\n", data.img.bpp, data.img.line_length, data.img.endian);
	
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}