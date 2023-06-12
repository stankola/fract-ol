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
	if (data.mlx_ptr == NULL)
		return (-1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
	if (data.win_ptr == NULL)
	{
		free(data.mlx_ptr);
		return (-1);
	}
	data.img.img = mlx_new_image(data.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bpp, &data.img.line_length,
								&data.img.endian);
	ft_printf("bpp %d linlen %d endian %d\n", data.img.bpp, data.img.line_length, data.img.endian);
	
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}