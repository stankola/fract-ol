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

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;		// length in bits, I suppose
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;

}

void	print_pixel_data(t_data *data)
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

int	main(void)
{
	void	*mlx;
	void	*window;
	t_data	img;

	mlx = mlx_init();
	window = mlx_new_window(mlx, 640, 480, "titteli");
	img.img = mlx_new_image(mlx, 640, 480);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	ft_printf("%d %d %d\n", img.bits_per_pixel, img.line_length, img.endian);
	my_mlx_pixel_put(&img, 0, 0, 0xFFFFFF00);
	my_mlx_pixel_put(&img, 0, 1, 0xFFFFFF00);
	my_mlx_pixel_put(&img, 1, 0, 0xFFFFFF00);
	my_mlx_pixel_put(&img, 1, 1, 0xFFFFFF00);
	print_pixel_data(&img);
	mlx_string_put(mlx, window, 320, 240, 0x0000FF00, "All your base are belong to us");
	mlx_put_image_to_window(mlx, window, img.img, 0, 0);
	mlx_loop(window);
	return (0);
}