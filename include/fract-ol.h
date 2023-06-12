/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 12:00:02 by tsankola          #+#    #+#             */
/*   Updated: 2023/06/01 12:00:02 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FRACT_OL_H
# define FRACT_OL_H
# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 450
# define TITLE "Fract-ol"

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
} t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	int		cur_img;
} t_data;

typedef struct s_point
{
	int	x;
	int	y;
} t_point;

int	my_round(double d);

int	check_bounds(t_point p);

int	invert_int_by_bytes(int i, unsigned int byteamount);

void	draw_pixel(t_img *img, t_point p, int color);

void	render_background(t_img *img, int color);

/* These are not required for fract-ol */

int render_circle(t_img *img, t_point p, int radius, int color);

int render_square(t_img *img, t_point p, int size, int color);

#endif