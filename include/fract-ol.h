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
# define SCREEN_WIDTH 1000
# define SCREEN_HEIGHT 900
# define TITLE "Fract-ol"
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define BLACK 0x00000000
# define WHITE 0x00FFFFFF

enum e_keycodes {
	ESC = 53
};

enum e_events {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

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

int		check_bounds(t_point p);

int		invert_int_by_bytes(int i, unsigned int byteamount);

void	draw_pixel(t_img *img, t_point p, int color);

void	render_background(t_img *img, int color);

void	render_mandelbrot(t_img *img, unsigned int MaxIterations);

/* These are not required for fract-ol */

int render_circle(t_img *img, t_point p, int radius, int color);

int render_square(t_img *img, t_point p, int size, int color);

#endif