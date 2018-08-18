/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdittric <cdittric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 16:28:34 by cdittric          #+#    #+#             */
/*   Updated: 2018/08/18 19:41:32 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
#include "stdio.h"
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"

typedef double			t_scal;

typedef struct			s_vec2
{
	t_scal	v[2];
}						t_vec2;

typedef struct			s_vec3
{
	t_scal	v[3];
}						t_vec3;

typedef struct			s_vec4
{
	t_scal	v[4];
}						t_vec4;

typedef struct			s_mat2
{
	t_sca	m[4];
}						t_mat2;

typedef struct s_map	t_map;

struct					s_map
{
	int		fd;
	t_map	*next;
}

/*
** TODO:
** Move map information in chained list node t_map.
*/

typedef struct			s_env
{
	void		*mlx;
	t_win		win;
	char		keys[512];
	int			button;
	t_ivec		mouse_pos;
	t_ivec		tmp_mouse_pos;
	int			timer;
	t_vec3		pos;
	t_vec3		rot;
	t_vec3		origin_rot;
	t_mat4		cam_mat;
	int			**map;
	t_map		*map_list;
	t_ivec		mdim;
}				t_env;

void			init_environment(t_env *env);
void			end_environment(t_env *env);
void			set_hooks(t_ptr *env);

int				loop_hook(void *parm);

int				button_press_hook(int button, int x, int y, void *parms);
int				button_release_hook(int button, int x, int y, void *parms);
int				motion_hook(int x, int y, void *parm);
int				key_press_hook(int key_code, void *parm);
int				key_release_hook(int key_code, void *parm);
void			move(t_ptr *p);

void			display(t_ptr *p);

#endif
