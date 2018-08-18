/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libgxns.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 23:56:43 by njaber            #+#    #+#             */
/*   Updated: 2018/08/18 19:42:26 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBGXNS_H
# define LIBGXNS_H

# include <time.h>
# include <math.h>
# include "ft_printf.h"
# include "libft.h"

typedef float	t_scal;

# include "qwerty.h"

typedef struct	s_vec2 {
	t_scal	x;
	t_scal	y;
}				t_vec2;

typedef struct	s_vec3 {
	t_scal	x;
	t_scal	y;
	t_scal	z;
}				t_vec3;

typedef t_scal	t_mat4[16];

typedef struct	s_ivec {
	int		x;
	int		y;
}				t_ivec;

typedef struct	s_img {
	void			*link;
	unsigned char	*buf;
	t_ivec			size;
	int				px_size;
	int				line;
	int				endian;
	int				line_draw_mode;
}				t_img;

typedef struct	s_win {
	void				*mlx;
	void				*win;
	t_img				img;
	t_ivec				size;
	int					frame;
	t_scal				fps;
	unsigned long		frames[30];
}				t_win;

t_vec3			apply_mat_vec3(t_vec3 v, t_mat4 m);
void			print_mat(t_mat4 m);

void			identity(t_mat4 m);
void			translate(t_mat4 m, t_vec3 v);
void			scale(t_mat4 m, t_vec3 v);
void			rotate(t_mat4 m, t_vec3 v);
void			multiply(t_mat4 m1, t_mat4 m2, int stock_in_m2);

t_scal			sqr(t_scal n);

t_vec2			c_mult(t_vec2 z1, t_vec2 z2);
t_vec2			c_add(t_vec2 z1, t_vec2 z2);
t_vec2			c_pow(t_vec2 z1, int pow);

t_vec3			vec_sub(t_vec3 v1, t_vec3 v2);
t_vec3			vec_add(t_vec3 v1, t_vec3 v2);
t_vec3			vec_mult(t_vec3 v1, t_scal d);
t_scal			length(t_vec3 v1);
t_scal			scalar(t_vec3 v1, t_vec3 v2);

int				init_new_win(void *mlx, t_win *win, t_ivec size, char *title);
void			paint_window(t_win *win, int clear);

void			display_data_scal(t_win *win, char *name, t_scal data, int y);
void			display_data_vec2(t_win *win, char *name, t_vec2 data, int y);
void			display_data_vec3(t_win *win, char *name, t_vec3 data, int y);
void			display_data_str(t_win *win, char *name, char *data, int y);

void			init_new_image(void *mlx, t_img *img, t_ivec size);
void			img_px(t_img *img, unsigned int color, t_ivec pixel);
void			clear_img(t_img *img);

void			draw_line(t_img *img, unsigned int *color, t_vec2 *verticies);
unsigned int	color_gradiant(unsigned int *colors, t_scal gradiant);

int				get_key_digit(int key_code);

#endif
