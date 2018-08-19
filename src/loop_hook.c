/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 16:00:11 by njaber            #+#    #+#             */
/*   Updated: 2018/08/19 11:03:39 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		print_data(t_env *env)
{
	t_vec2	dir;
	t_vec2	v;
	t_vec2	comp;
	int		col;

	col = 600;
	dir = m2dotv2(env->cam_mat, vec2((t_scal)(col - env->win.size.v[0] / 2) /
				(env->win.size.v[0] / 2), 1.));
	v = vec2(env->pos.v[0], env->pos.v[2]);
	comp = vec2(fabs(fmod(fmod(copysign(v.v[0], -dir.v[0]), 100) + 100, 100) / dir.v[0]),
			fabs(fmod(fmod(copysign(v.v[1], -dir.v[1]), 100) + 100, 100) / dir.v[1]));

	display_data_scal(&env->win, "FPS:", env->win.fps, 10);
	display_data_vec3(&env->win, "Positon:", env->pos, 30);
	display_data_vec2(&env->win, "Rotation:", env->rot, 50);
	display_data_scal(&env->win, "Button:", env->button, 70);
	display_data_vec2(&env->win, "Comp:", comp, 90);
}

static void		update(t_env *env)
{
	env->cam_mat = m2rotation(env->rot.v[1] / 180 * M_PI);
}

int				loop_hook(t_env *env)
{
	move(env);
	update(env);
	display(env);
	paint_window(&env->win, 1);
	print_data(env);
	return (0);
}
