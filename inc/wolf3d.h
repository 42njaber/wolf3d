/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdittric <cdittric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 16:28:34 by cdittric          #+#    #+#             */
/*   Updated: 2018/09/25 18:19:17 by cdittric         ###   ########.fr       */
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

typedef unsigned int	t_uint;
typedef unsigned char	t_uchar;
typedef unsigned short	t_ushort;

typedef struct			s_vec2 {
	union {t_scal v[2]; struct {t_scal x; t_scal y;};};
}						t_vec2;

typedef struct			s_vec3 {
	union {t_scal v[3]; struct {t_scal x; t_scal y; t_scal z;};};
}						t_vec3;

typedef struct			s_vec4 {
	union {t_scal v[4]; struct {t_scal x; t_scal y; t_scal z; t_scal w;};};
}						t_vec4;

typedef struct			s_mat2 {
	t_scal	m[4];
}						t_mat2;

typedef struct			s_mat3 {
	t_scal	m[9];
}						t_mat3;

typedef struct			s_ivec {
	union {int v[2]; struct {int x; int y;};};
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
** - tex: texture index.
** - tex_span: offsets to add to the texture coordinates.
** - tex_grad: gradiants by which to multiply the texture coordinates.
** texture coordinates by default 
*/

typedef struct			s_wall {
	t_vec3			pos;
	int				sector;
	unsigned int	wall_reference;
	unsigned int	tex;
	t_vec2			tex_span;
	t_vec2			tex_grad;
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
	t_uint		walls_count;
	t_sector	*sectors;
	int			sectors_count;
	t_map		**self;
	t_map		*next;
};

typedef struct			s_img {
	void			*link;
	unsigned char	*buf;
	t_ivec			size;
	int				px_size;
	int				line;
	int				endian;
}						t_img;

typedef struct s_btree	t_btree;

struct					s_btree {
	t_btree		*parent;
	t_btree		*b0;
	t_btree		*b1;
	short		val;
};

typedef struct			s_png {
	t_ivec	dim;
	t_uint	*buf;
	t_uchar	init;
	t_uchar	bdepth;
	t_uchar	ctype;
	t_uchar	pxsize;
	t_uchar	compression;
	t_uchar	filter;
	t_uchar	interlace;
	t_ivec	aratio;
	t_uchar	aunit;
	t_uint	_block_len;
	t_uchar	_block_type[4];
	t_uchar	*_zlib_stream;
	size_t	_zlib_len;
	int		*_codes;
	size_t	_codes_len;
	size_t	_data_size;
	t_uchar	*_data;
	t_btree	*ltree;
	t_btree	*dtree;
	t_btree	*cltree;
}						t_png;

typedef struct s_env	t_env;

/*
** s_cam:
** Contains variable local to the camera/viewport used for render:
** - occlusion: Screen buffer of opacity of colors currently on the screen.
** - occlusion_top: Number of pixels occluded on the top for each column.
** - occlusion_bottom: Number of pixels occluded on the bottom for each column.
** - occlusion_column: For each column wether it is occluded or not.
** - clusters: Stack of clusters to be sorted in depth order before rendering.
** - entities: Stack of entities to be sorted in depth order before rendering.
** - visited_sectors: For each sector wether it has been visited during render.
** - walls: Walls transformed into window space.
** - rot: Position
*/

typedef struct			s_cam {
	unsigned char	*occlusion;
	int				*occlusion_top;
	int				*occlusion_bottom;
	unsigned char	*occlusion_column;
	int				clusters_count;
	t_cluster		clusters[CLUSTER_STACK_SIZE];
	int				entities_count;
	t_entity		*entities[ENTITY_STACK_SIZE];
	char			*visited_sectors;
	t_wall			*walls;
	t_vec3			pos;
	t_vec3			rot;
	t_vec3			mat;
}						t_cam;



typedef struct			s_win {
	t_env			*env;
	void			*mlx;
	void			*win;
	t_img			img;
	union {t_ivec size; struct {int w; int h;};}; // TODO: w and h are better.
	int				frame;
	t_scal			fps;
	unsigned long	frames[30];
}						t_win;

struct					s_env {
	void		*mlx;
	t_win		win;
	t_cam		cam;
	char		keys[512];
	int			button;
	t_ivec		mouse_pos;
	t_ivec		tmp_mouse_pos;
	int			timer;
	t_vec3		pos;
	t_vec2		mov;
	t_scal		inertia;
	t_scal		rot;
	t_scal		origin_rot;
	t_mat2		cam_mat;
	t_map		*map_list;
	t_map		*map;
	int			current_sector;
	t_png		*walls;
	t_png		*ceil;
	t_png		*floor;
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
void			paint_col(t_env *env, int col, t_vec2 ray, t_vec2 v);
int				hit_tile(t_map *map, t_vec2 point);
void			clamp_move(t_env *env);

t_vec3			vec3(t_scal x, t_scal y, t_scal z);
t_vec2			vec2(t_scal x, t_scal y);
t_ivec			ivec(int x, int y);
t_scal			sqr(t_scal n);

t_mat2			m2identity(void);
t_mat2			m2rotation(t_scal angle);
t_mat2			m2dot(t_mat2 m1, t_mat2 m2);
t_vec2			m2dotv2(t_mat2 m, t_vec2 v);
t_mat2			m3identity(void);
t_mat3			m3rotation(t_scal angle);
t_mat3			m3dot(t_mat3 m1, t_mat3 m2);
t_vec3			m3dotv2(t_mat3 m, t_vec3 v);

t_vec3			vec3_sub(t_vec3 v1, t_vec3 v2);
t_vec3			vec3_add(t_vec3 v1, t_vec3 v2);
t_vec3			vec3_mult(t_vec3 v1, t_scal d);
t_scal			vec3_length(t_vec3 v1);
t_scal			vec3_scalar(t_vec3 v1, t_vec3 v2);

t_vec2			vec2_sub(t_vec2 v1, t_vec2 v2);
t_vec2			vec2_add(t_vec2 v1, t_vec2 v2);
t_vec2			vec2_mult(t_vec2 v1, t_scal d);
t_scal			vec2_length(t_vec2 v1);
t_scal			vec2_scalar(t_vec2 v1, t_vec2 v2);

int				init_new_win(t_env *env, t_win *win, t_ivec size, char *title);
void			paint_window(t_win *win, int clear);

void			display_data_scal(t_win *win, char *name, t_scal data, int y);
void			display_data_vec2(t_win *win, char *name, t_vec2 data, int y);
void			display_data_vec3(t_win *win, char *name, t_vec3 data, int y);
void			display_data_str(t_win *win, char *name, char *data, int y);

void			init_new_image(void *mlx, t_img *img, t_ivec size);
void			img_px(t_img *img, unsigned int color, t_ivec pixel);
void			clear_img(t_img *img);

t_uint			color_gradiant(t_uint c1, t_uint c2, t_scal gradiant);
int				get_key_digit(int key_code);

void			read_map_list(t_env *env);
t_map			*delete_map(t_map *map);
t_map			*add_map(t_env *env, char *path);

t_png			*decode_png(char *path);
int				validate_crc(int fd, t_uchar *buf, t_png *png);
int				checksum(t_uchar *buf, t_uint len, t_uchar *alder);
int				destroy_png(t_png **png);
int				parse_ihdr(int fd, t_png *png);
int				parse_phys(int fd, t_png *png);
int				parse_idat(int fd, t_png *png);
int				parse_iend(int fd, t_png *png);
int				parse_unkown(int fd, t_png *png);

t_uint			get_next_bits(t_uchar *buf, t_uint *pos, t_uint len);
int				decompress_block(t_png *png, t_uchar *stream, t_uint *pos);
int				parse_zlib(t_png *png);
int				gen_default_tree(t_png *png);
int				read_tree(t_png *png, t_uchar *stream, t_uint *pos);
int				create_cltree(t_btree **cltree, t_uchar *clens);
int				create_tree(t_btree **tree, t_uchar *lens, t_ushort max);
short			read_next(t_png *png, t_uchar *stream, t_uint *pos, t_btree *tree);
void			free_tree(t_btree **tree);
int				read_codes(t_png *png, t_uchar *buf, t_uint *pos);
int				recompose_image(t_png *png);

void			debug_map(t_env *env);
void			engine(t_env *env);

#endif
