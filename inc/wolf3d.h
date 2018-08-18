/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdittric <cdittric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 16:28:34 by cdittric          #+#    #+#             */
/*   Updated: 2018/08/18 19:04:19 by cdittric         ###   ########.fr       */
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

# define EVENT_KEY_PRESS 2
# define EVENT_KEY_RELEASE 3
# define EVENT_MOUSE_PRESS 4
# define EVENT_MOUSE_RELEASE 5
# define EVENT_MOUSE_MOVE 6
# define EVENT_EXPOSE 12
# define EVENT_CLOSE 17

# define BUTTON_LEFT 1
# define BUTTON_RIGHT 2
# define BUTTON_OTHER 3
# define BUTTON_SCROLLUP 4
# define BUTTON_SCROLLDOWN 5

# define KEY_Q			12
# define KEY_W			13
# define KEY_E			14
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2
# define KEY_Z			6
# define KEY_R			15
# define KEY_C			8
# define KEY_G			5
# define KEY_K			40
# define KEY_L			37
# define KEY_M			41
# define KEY_MINUS		27
# define KEY_EQUAL		24
# define KEY_TAB		48
# define KEY_BACKQUOTE	50
# define KEY_LCONTROL	256
# define KEY_RCONTROL	269
# define KEY_LALT		261
# define KEY_RALT		262
# define KEY_LSHIFT		257
# define KEY_RSHIFT		258
# define KEY_SPACE		49
# define KEY_RETURN		36
# define KEY_DELETE		51
# define KEY_SUPPRESS	117
# define KEY_UP			126
# define KEY_LEFT		123
# define KEY_DOWN		125
# define KEY_RIGHT		124
# define KEY_ESCAPE		53
# define KEY_NUM0		82
# define KEY_NUM1		83
# define KEY_NUM2		84
# define KEY_NUM3		85
# define KEY_NUM4		86
# define KEY_NUM5		87
# define KEY_NUM6		88
# define KEY_NUM7		89
# define KEY_NUM8		91
# define KEY_NUM9		92
# define KEY_NUMPLUS	69
# define KEY_NUMMINUS	78
# define KEY_PAGEUP		116
# define KEY_PAGEDOWN	121
# define KEY_HOME		115
# define KEY_END		119
# define KEY_0			29
# define KEY_1			18
# define KEY_2			19
# define KEY_3			20
# define KEY_4			21
# define KEY_5			23
# define KEY_6			22
# define KEY_7			26
# define KEY_8			28
# define KEY_9			25

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
