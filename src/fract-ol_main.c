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
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	return (0);
}

int	destroy(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.img);
	exit(0);
	return (0);
}

int	key_hook(int keycode, t_data *data)
{
	ft_printf("Key %d upped(?)\n", keycode);
	if (keycode == ESC)
		destroy(data);
	else if (keycode == R)
	{
		data->initialize = 1;
		render_fractal(data);
	}
	else if (keycode == LEFT_ARROW || keycode == UP_ARROW || keycode == DOWN_ARROW || keycode == RIGHT_ARROW)
	{
		shift(&(data->dim), keycode, SHIFT_MULTIPLIER);
		render_fractal(data);
	}
	return (0);
}

int	mouse_hook(int button, int x, int y, t_data *data)
{
	data +=0;
	ft_printf("Mouse button %d in x %d y %d\n", button, x, y);
	printf("Coordinates Re %Lf Im %Lf\n", (data->dim.maxRe - data->dim.minRe) * (double)x / (double)SCREEN_WIDTH + data->dim.minRe,
										(data->dim.maxIm - data->dim.minIm) * (double)y / (double)SCREEN_HEIGHT + data->dim.minIm);
	if (button == SCROLL_UP || button == LEFT_BUTTON)
		zoom(&(data->dim), (t_point){x, y}, ZOOM_FACTOR);
	else if (button == SCROLL_DOWN || button == RIGHT_BUTTON)
		zoom(&(data->dim), (t_point){x, y}, 1 / ZOOM_FACTOR);
	else
		return (0);
	printf("New dimensions minRe %Lf maxRe %Lf minIm %Lf maxIm %Lf\n", data->dim.minRe, data->dim.maxRe, data->dim.minIm, data->dim.maxIm);
	render_fractal(data);
	return (0);
}

int	parse(int argc, char *argv[])
{
	char	*s;
	int		i;

	if (argc == 2)
	{
		i = ft_atoi(argv[1]);
		s = ft_itoa(i);
		if (s != NULL)
		{
			if (ft_strncmp(s, argv[1], ft_strlen(argv[1])) != 0)
				i = -1;
			free(s);
			if (i == MANDELBROT || i == JULIA)
				return (i);
		}
	}
	ft_printf("Please select the fractal to be drawn:\n");
	ft_printf("\t%d - Mandelbrot\n", MANDELBROT);
	ft_printf("\t%d - Julia\n", JULIA);
	ft_printf("e.g. \"./fract-ol %d\"\n", MANDELBROT);
	exit(0);
	return (-1);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	data.fractal = parse(argc, argv);
	data.initialize = 1;
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (-1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
	if (data.win_ptr == NULL)
	{
		free(data.mlx_ptr);
		return (-1);
	}
	data.img.img = mlx_new_image(data.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);		// Might fail
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bpp, &data.img.line_length,
								&data.img.endian);
	ft_printf("bpp %d linlen %d endian %d\n", data.img.bpp, data.img.line_length, data.img.endian);
	render_fractal(&data);
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_key_hook(data.win_ptr, &key_hook, &data);
	mlx_mouse_hook(data.win_ptr, &mouse_hook, &data);
	mlx_hook(data.win_ptr, ON_DESTROY, 0L, destroy, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
