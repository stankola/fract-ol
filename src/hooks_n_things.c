/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:29:04 by tsankola          #+#    #+#             */
/*   Updated: 2023/06/15 18:29:05 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "mlx.h"
#include "fractol.h"

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
	if (keycode == ESC)
		destroy(data);
	else if (keycode == R)
	{
		data->initialize = 1;
		render_fractal(data);
	}
	else if (keycode == LEFT_ARROW || keycode == UP_ARROW
		|| keycode == DOWN_ARROW || keycode == RIGHT_ARROW)
	{
		shift(&(data->dim), keycode, SHIFT_MULTIPLIER);
		render_fractal(data);
	}
	return (0);
}

int	mouse_hook(int button, int x, int y, t_data *data)
{
//	ft_printf("Mouse button %d in x %d y %d\n", button, x, y);
	if (button == SCROLL_UP || button == LEFT_BUTTON)
		zoom(&(data->dim), (t_point){x, y}, ZOOM_FACTOR);	// I get different y for scroll and button, wtf? Seems to be inverse.
	else if (button == SCROLL_DOWN || button == RIGHT_BUTTON)
		zoom(&(data->dim), (t_point){x, y}, 1 / ZOOM_FACTOR);
	else
		return (0);
	render_fractal(data);
	return (0);
}
