/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 12:00:02 by tsankola          #+#    #+#             */
/*   Updated: 2023/06/01 12:00:02 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FRACTOL_H
# define FRACTOL_H
# define SCREEN_WIDTH 900
# define SCREEN_HEIGHT 900
# define TITLE "Fract-ol"
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define BLACK 0x00000000
# define WHITE 0x00FFFFFF
# define ZOOM_FACTOR 0.8	// ZOOM_FACTOR should be between ]0, 1[
# define SHIFT_MULTIPLIER 0.1
# define MANDELBROT_ITERATIONS 50
# define JULIA_ITERATIONS 50
# ifdef __linux__
#  define ESC 65307
#  define R 114
#  define UP_ARROW 65362
#  define DOWN_ARROW 65364
#  define LEFT_ARROW 65361
#  define RIGHT_ARROW 65363
# else
#  define ESC 53
#  define R 15
#  define UP_ARROW 0x7E
#  define DOWN_ARROW 0x7D
#  define LEFT_ARROW 0x7B
#  define RIGHT_ARROW 0x7C
# endif

enum e_mousecodes {
	LEFT_BUTTON = 1,
	RIGHT_BUTTON = 2,
	SCROLL_UP = 4,
	SCROLL_DOWN = 5
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

enum e_fractals {
	MANDELBROT,
	JULIA
};

typedef struct s_complex
{
	long double	r;
	long double	i;
}	t_complex;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_dim
{
	long double	min_r;
	long double	max_r;
	long double	min_i;
	long double	max_i;
}	t_dim;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	int			cur_img;
	t_dim		dim;
	int			fractal;
	int			initialize;
	t_complex	parameter;

}	t_data;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

int			render(t_data *data);

int			destroy(t_data *data);

int			key_hook(int keycode, t_data *data);

int			mouse_hook(int button, int x, int y, t_data *data);

long double	ft_atof(char *s);

int			check_float_form(char *s);

void		zoom(t_dim *dim, t_point center, long double factor);

void		shift(t_dim *dim, int direction, double distance_multiplier);

int			check_bounds(t_point p);

int			invert_int_by_bytes(int i, unsigned int byteamount);

void		draw_pixel(t_img *img, t_point p, int color);

void		get_mandelbrot_dimensions(t_dim *dim);

void		render_mandelbrot(t_img *img, t_dim dim, int max_iterations);

void		get_julia_dimensions(t_dim *dim);

void		render_julia(t_img *img, t_dim dim, t_complex k,
				int max_iterations);

void		render_fractal(t_data *data);

#endif