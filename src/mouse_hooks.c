/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 01:32:56 by njaber            #+#    #+#             */
/*   Updated: 2018/08/19 06:47:01 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		button_press_hook(int button, int x, int y, t_env *env)
{
	if (button == 1)
	{
		env->tmp_mouse_pos = ivec(x, y);
		env->mouse_pos = ivec(x, y);
		env->origin_rot = env->rot;
	}
	if (button < 4)
		env->button = button;
	return (0);
}

int		button_release_hook(int button, int x, int y, t_env *env)
{
	(void)x, (void)y;
	if (button == 1)
	{
		env->rot = vec3(fmax(-90, fmin(90, env->origin_rot.v[0] +
					(env->mouse_pos.v[1] - env->tmp_mouse_pos.v[1]) * -0.25)),
					fmod(env->origin_rot.v[1] + (env->mouse_pos.v[0] -
							env->tmp_mouse_pos.v[0]) * -0.25, 360), 0);
	}
	if (button == env->button)
		env->button = -1;
	return (0);
}

int		motion_hook(int x, int y, t_env *env)
{
	env->mouse_pos = ivec(x, y);
	if (env->button == 1)
	{
		env->rot = vec3(fmax(-90, fmin(90, env->origin_rot.v[0] +
					(env->mouse_pos.v[1] - env->tmp_mouse_pos.v[1]) * -0.25)),
					fmod(env->origin_rot.v[1] + (env->mouse_pos.v[0] -
							env->tmp_mouse_pos.v[0]) * -0.25, 360), 0);
	}
	return (0);
}
