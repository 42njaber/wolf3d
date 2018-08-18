/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 15:19:13 by njaber            #+#    #+#             */
/*   Updated: 2018/08/18 13:31:54 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include "libgxns.h"

typedef struct	s_ptr {
	t_win		*win;
	void		*mlx;
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
	t_ivec		mdim;
}				t_ptr;

void			init_struct(t_ptr *p);
void			set_hooks(t_ptr *p);

int				loop_hook(void *parm);

int				button_press_hook(int button, int x, int y, void *parms);
int				button_release_hook(int button, int x, int y, void *parms);
int				motion_hook(int x, int y, void *parm);
int				key_press_hook(int key_code, void *parm);
int				key_release_hook(int key_code, void *parm);
void			move(t_ptr *p);

void			display(t_ptr *p);

#endif
