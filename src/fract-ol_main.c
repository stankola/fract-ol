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
#include <stdio.h>

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;		// length in bits, I suppose
	int		endian;
} t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	int		cur_img;
} t_data;


// endian 0 == Little-endian, 1 == Big-endian
void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	if (img->endian == 0)		// TODO figure this shit out
		*(unsigned int*)dst = color;
	else
		*(unsigned int*)dst = color;
}


// Delete this
void	print_pixel_data(t_img *data)
{
	char	*address;
	int		i;

	address = data->addr;
	i = 0;
	while (i < data->line_length)
	{
		ft_printf("%d", (int)address[i]);
		i+=4;
	}
}

int render_square(t_img *img, int x, int y, int size)
{
	int	i;
	int j;

	i = y;
	while (i < y + size)
	{
		j = x;
		while (j < x + size)
			my_mlx_pixel_put(img, j++, i, 0x00FFFF00);
		++i;
	}
	return (0);
}

void	render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 480)
	{
		j = 0;
		while (j < 640)
		{
			my_mlx_pixel_put(img, j++, i, color);
		}
		++i;
	}
}

//int	render(t_data *data)
int	render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);
//	my_mlx_pixel_put(&(data->img), 20, 20, 0x000000FF);
//	my_mlx_pixel_put(&(data->img), 20, 21, 0x0000FF00);
//	my_mlx_pixel_put(&(data->img), 21, 20, 0x00FF0000);
//	my_mlx_pixel_put(&(data->img), 21, 21, 0x00FFFFFF);
	render_background(&(data->img), 0x00FFFF00);
	render_square(&(data->img), 20, 20, 20);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);

	return (0);
}

int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, 640, 480, "titteli");
	data.img.img = mlx_new_image(data.mlx_ptr, 640, 480);
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bits_per_pixel, &data.img.line_length,
								&data.img.endian);
	ft_printf("%d %d %d\n", data.img.bits_per_pixel, data.img.line_length, data.img.endian);
//	print_pixel_data(&img);
	mlx_loop_hook(data.mlx_ptr, &render, &data);
//	mlx_string_put(data.mlx_ptr, data.win_ptr, 320, 240, 0x0000FF00, "All your base are belong to us");
//	mlx_put_image_to_window(mlx, window, img.img, 0, 0);

	mlx_loop(data.win_ptr);
	getchar();
	return (0);
}