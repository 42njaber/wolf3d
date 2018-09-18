/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdittric <cdittric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 16:28:34 by cdittric          #+#    #+#             */
/*   Updated: 2018/09/16 20:29:44 by cdittric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
#include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
# include "ft_printf.h"
# include "gnl.h"

# include "qwerty.h"
// NOTE: Window width and height are set in parse_arguments.

# define DEFAULT_WINDOW_WIDTH 1200
# define DEFAULT_WINDOW_HEIGHT 800

# define WALL_MAX INT_MAX
# define VWALL_MAX USHRT_MAX
# define CLUSTER_STACK_SIZE 1024
# define ENTITY_STACK_SIZE 1024
// Map tile size
# define SIZE 10.

typedef double			t_scal;

typedef struct			s_vec2 {
	t_scal	v[2];
}						t_vec2;

typedef struct			s_vec3 {
	t_scal	v[3];
}						t_vec3;

typedef struct			s_vec4 {
	t_scal	v[4];
}						t_vec4;

typedef struct			s_mat2 {
	t_scal	m[4];
}						t_mat2;

typedef struct			s_ivec {
	int		v[2];
}						t_ivec;

typedef struct			s_texture {
	char	*buf;
	t_ivec	dim;
}						t_texture;

typedef struct			s_sprite {
	t_texture	**tex[8];
	int			frame_count;
}						t_sprite;

typedef struct			s_entity {
	t_vec3			pos;
	t_sprite		spr;
	int				frame;
	int				frame_delay;
	int				frame_timer;
	struct s_entity	*next;
}						t_entity;

/*
** t_wall:
** Contains a vertex of the wall geometry and data of the wall of which it is
** the first vertex.
** - sector:
** 		0 or positive:	The wall is a portal toward the sector of this index.
** 		-1:				Solid wall.
**		-2:				End of wall. The next wall won't be drawn.
*/

typedef struct			s_wall {
	t_vec2			pos;
	int				sector;
	unsigned int	wall_reference;
	unsigned int	texture;
}						t_wall;

typedef struct			s_sector {
	t_scal			floor_height;
	t_scal			ceiling_height;
	t_entity		*entity_list;
	t_wall			*vwalls;
	unsigned int	vwalls_count;
	unsigned int	walls_start;
	unsigned int	walls_count;
	unsigned int	sprites_start;
	unsigned int	texture;
}						t_sector;

typedef struct			s_cluster {
	unsigned int		wall_start;
	unsigned int		wall_count;
}						t_cluster;

typedef struct s_map	t_map;

struct					s_map {
	char		*path;
	int			**grid;
	t_ivec		dim;
	t_wall		*walls;
	t_sector	*sectors;
	int			sectors_count;
	t_map		**self;
	t_map		*next;
};

typedef struct	s_img {
	void			*link;
	unsigned char	*buf;
	t_ivec			size;
	int				px_size;
	int				line;
	int				endian;
}				t_img;

typedef struct	s_env	t_env;

/*
** s_win:
** Contains variable local to the window including rendering data such as:
** - occlusion: Screen buffer of opacity of colors currently on the screen.
** - occlusion_top: Number of pixels occluded on the top for each column.
** - occlusion_bottom: Number of pixels occluded on the bottom for each column.
** - occlusion_column: For each column wether it is occluded or not.
** - clusters: Stack of clusters to be sorted in depth order before rendering.
** - entities: Stack of entities to be sorted in depth order before rendering.
** - visited_sectors: For each sector wether it has been visited during render.
*/

typedef struct			s_win {
	t_env			*env;
	void			*mlx;
	void			*win;
	t_img			img;
	int				w;
	int				h;
	t_ivec			size; //TODO: Delete size. Replaced by w and h.
	int				frame;
	t_scal			fps;
	unsigned long	frames[30];
	unsigned char	*occlusion;
	unsigned int	*occlusion_top;
	unsigned int	*occlusion_bottom;
	unsigned char	*occlusion_column;
	int				clusters_count;
	t_cluster		clusters[CLUSTER_STACK_SIZE];
	int				entities_count;
	t_entity		*entities[ENTITY_STACK_SIZE];
	char			*visited_sectors;
}						t_win;

struct					s_env {
	void		*mlx;
	t_win		win;
	char		keys[512];
	int			button;
	t_ivec		mouse_pos;
	t_ivec		tmp_mouse_pos;
	int			timer;
	t_vec3		pos;
	t_scal		rot;
	t_scal		origin_rot;
	t_mat2		cam_mat;
	t_map		*map_list;
	t_map		*map;
	int			current_sector;
	t_img		*text;
};

void			init_environment(t_env *env);
void			end_environment(t_env *env, int status);
void			end_environment_callback(void *env, int status);
void			set_hooks(t_env *env);

int				loop_hook(t_env *env);

int				button_press_hook(int button, int x, int y, t_env *env);
int				button_release_hook(int button, int x, int y, t_env *env);
int				motion_hook(int x, int y, t_env *env);
int				key_press_hook(int key_code, t_env *env);
int				key_release_hook(int key_code, t_env *env);
void			move(t_env *env);

void			display(t_env *env);
int				hit_tile(t_map *map, t_vec2 point);
void			clamp_pos(t_env *env);

t_vec3			vec3(t_scal x, t_scal y, t_scal z);
t_vec2			vec2(t_scal x, t_scal y);
t_ivec			ivec(int x, int y);
t_scal			sqr(t_scal n);

t_mat2			m2identity(void);
t_mat2			m2rotation(t_scal angle);
t_mat2			m2dot(t_mat2 m1, t_mat2 m2);
t_vec2			m2dotv2(t_mat2 m, t_vec2 v);

t_vec3			vec_sub(t_vec3 v1, t_vec3 v2);
t_vec3			vec_add(t_vec3 v1, t_vec3 v2);
t_vec3			vec_mult(t_vec3 v1, t_scal d);
t_scal			length(t_vec3 v1);
t_scal			scalar(t_vec3 v1, t_vec3 v2);

int				init_new_win(t_env *env, t_win *win, t_ivec size, char *title);
void			paint_window(t_win *win, int clear);

void			display_data_scal(t_win *win, char *name, t_scal data, int y);
void			display_data_vec2(t_win *win, char *name, t_vec2 data, int y);
void			display_data_vec3(t_win *win, char *name, t_vec3 data, int y);
void			display_data_str(t_win *win, char *name, char *data, int y);

void			init_new_image(void *mlx, t_img *img, t_ivec size);
void			img_px(t_img *img, unsigned int color, t_ivec pixel);
void			clear_img(t_img *img);

unsigned int	color_gradiant(unsigned int *colors, t_scal gradiant);
int				get_key_digit(int key_code);

void			read_map_list(t_env *env);
t_map			*delete_map(t_map *map);
t_map			*add_map(t_env *env, char *path);

t_img			*decode_png(void *mlx, char *path);

#endif
