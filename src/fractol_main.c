/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 12:00:35 by tsankola          #+#    #+#             */
/*   Updated: 2023/06/01 12:00:35 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <limits.h>
#include <stdio.h>
#include <math.h>
#include "fractol.h"
#include "mlx.h"
#include "libft.h"

static int	parse(int argc, char *argv[])
{
	if (argc == 2 || argc == 4)
	{
		if (argc == 2 && argv[1][0] - '0' == MANDELBROT && ft_strlen(argv[1])
			== 1)
			return (MANDELBROT);
		else if (argc == 4 && argv[1][0] - '0' == JULIA && ft_strlen(argv[1])
			== 1 && check_float_form(argv[2]) && check_float_form(argv[3]))
			return (JULIA);
	}
	ft_printf("Please select the fractal to be drawn:\n");
	ft_printf("\t%d - Mandelbrot eg. \"./fract-ol %d\"\n",
		MANDELBROT, MANDELBROT);
	ft_printf("\t%d [K_real] [K_imaginary] - Julia eg. \"./fract-ol "
		"%d 0.353 0.288\"\n", JULIA, JULIA);
	exit(0);
	return (-1);
}

int	init(t_data *data, int fractal)
{
	data->fractal = fractal;
	data->initialize = 1;
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (-1);
	data->win_ptr = mlx_new_window(data->mlx_ptr, SCREEN_WIDTH,
			SCREEN_HEIGHT, TITLE);
	if (data->win_ptr == NULL)
	{
		free(data->mlx_ptr);
		return (-1);
	}
	data->img.img = mlx_new_image(data->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (data->img.img == NULL)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		free(data->mlx_ptr);
		return (-1);
	}
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp,
			&data->img.line_length, &data->img.endian);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (init(&data, parse(argc, argv)) != 0)
		return (-1);
	if (data.fractal == JULIA)
		data.parameter = (t_complex){ft_atof(argv[2]), ft_atof(argv[3])};
	render_fractal(&data);
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_key_hook(data.win_ptr, &key_hook, &data);
	mlx_mouse_hook(data.win_ptr, &mouse_hook, &data);
	mlx_hook(data.win_ptr, ON_DESTROY, 0L, destroy, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
