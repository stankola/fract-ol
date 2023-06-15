/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_helpers_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:27:34 by tsankola          #+#    #+#             */
/*   Updated: 2023/06/12 14:27:35 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "libft.h"
#include "fractol_bonus.h"

// Acceptable values are of type [+/-]123.123 or [+/-].123
int	check_float_form(char *s)
{
	if (*s == '\0')
		return (0);
	if (*s == '+' || *s == '-')
		s++;
	if (*s == '\0')
		return (0);
	while (*s >= '0' && *s <= '9')
		s++;
	if (*s == '\0')
		return (1);
	if (*s == '.')
		s++;
	if (*s == '\0')
		return (0);
	if (*s >= '0' && *s <= '9')
		s++;
	while (*s >= '0' && *s <= '9')
		s++;
	if (*s == '\0')
		return (1);
	return (0);
}

// Might overflow. No good way to detect this. We assume that form has been
// checked.
long double	ft_atof(char *s)
{
	char		*i;
	int			sign;
	long double	d;
	int			j;

	i = s;
	d = 0;
	sign = 1;
	if (*i == '-')
		sign = -1;
	if (*i == '-' || *i == '+')
		i++;
	while (*i != '\0' && *i != '.' && *i >= '0' && *i <= '9')
		d = 10 * d + (*(i++) - '0');
	if (*(i++) != '.')
		return (sign * d);
	j = 1;
	while (*i != '\0' && *i >= '0' && *i <= '9')
		d = d + (long double)(*(i++) - '0') / pow(10, j++);
	return (sign * d);
}

// Factor should be between ]0,1[
// Procedure before compressing it for the Norm (for clarity):
//	double x_offset = (double)center.x / (double)SCREEN_WIDTH;
//	double x_width = dim->maxRe - dim->minRe;
//	double x_coordinate = x_width * x_offset + dim->minRe;
//	double new_x_width = x_width * factor;
//	double new_minRe = x_coordinate - new_x_width * x_offset;
//	double new_maxRe = new_minRe + new_x_width;
void	zoom(t_dim *dim, t_point center, long double factor)
{
	double	width;
	double	new_width;
	double	height;
	double	new_height;

	width = dim->max_r - dim->min_r;
	new_width = width * factor;
	dim->min_r = (width - new_width)
		* (double)center.x / (double)SCREEN_WIDTH + dim->min_r;
	dim->max_r = dim->min_r + new_width;
	height = dim->max_i - dim->min_i;
	new_height = height * factor;
	dim->min_i = (height - new_height)
		* (1 - (double)center.y / (double)SCREEN_HEIGHT) + dim->min_i;
	dim->max_i = dim->min_i + new_height;
}

void	shift(t_dim *dim, int direction, double distance_multiplier)
{
	double	length;

	if (direction == DOWN_ARROW)
		distance_multiplier *= -1;
	if (direction == UP_ARROW || direction == DOWN_ARROW)
	{
		length = dim->max_i - dim->min_i;
		dim->max_i += length * distance_multiplier;
		dim->min_i += length * distance_multiplier;
		return ;
	}
	if (direction == LEFT_ARROW)
		distance_multiplier *= -1;
	if (direction == RIGHT_ARROW || direction == LEFT_ARROW)
	{
		length = dim->max_r - dim->min_r;
		dim->max_r += length * distance_multiplier;
		dim->min_r += length * distance_multiplier;
	}
}

int	invert_int_by_bytes(int i, unsigned int byteamount)
{
	int	inverted_i;
	int	j;
	int	shift_range;

	if (byteamount > 4)
	{
		ft_fprintf(STDERR_FILENO, "invert_int_by_bytes: %s\n", strerror(33));
		exit (33);
	}
	inverted_i = 0;
	j = -1;
	while (++j < (int)byteamount)
	{
		shift_range = (-byteamount + 2 * j + 1) * 8;
		if (shift_range >= 0)
			inverted_i += (i & (0xFF << (j * 8))) >> shift_range;
		else
			inverted_i += (i & (0xFF << (j * 8))) << -shift_range;
	}
	return (inverted_i);
}
