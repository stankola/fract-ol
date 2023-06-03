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

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (img->endian)		// TODO figure this shit out
		dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	else
		dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;

}

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

//int	render(t_data *data)
int	render(t_data *data)
{
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);

	return (0);
}

int	main(void)
{
	t_img	img;
	t_data	data;

	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, 640, 480, "titteli");
	img.img = mlx_new_image(data.mlx_ptr, 640, 480);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	data.img = img;
	ft_printf("%d %d %d\n", img.bits_per_pixel, img.line_length, img.endian);
	my_mlx_pixel_put(&img, 20, 20, 0x000000FF);
	getchar();
	my_mlx_pixel_put(&img, 20, 21, 0x0000FF00);
	my_mlx_pixel_put(&img, 21, 20, 0x00FF0000);
	my_mlx_pixel_put(&img, 21, 21, 0x00FFFFFF);
//	print_pixel_data(&img);
	mlx_string_put(data.mlx_ptr, data.win_ptr, 320, 240, 0x0000FF00, "All your base are belong to us");
//	mlx_put_image_to_window(mlx, window, img.img, 0, 0);
	mlx_loop_hook(data.mlx_ptr, render, &data);

	mlx_loop(data.win_ptr);
	getchar();
	return (0);
}