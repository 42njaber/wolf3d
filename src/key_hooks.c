/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 14:52:32 by njaber            #+#    #+#             */
/*   Updated: 2018/08/19 08:56:43 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>

void			move(t_env *env)
{
	t_vec2		rot;

	rot = vec2(env->rot.v[0] * M_PI / 180, env->rot.v[1] * M_PI / 180);
	if (env->keys[KEY_UP])
		env->pos = vec3(env->pos.v[0] - 0.5 * sin(rot.v[1]), env->pos.v[1],
			env->pos.v[2] + 0.5 * cos(rot.v[1]));
	if (env->keys[KEY_DOWN])
		env->pos = vec3(env->pos.v[0] + 0.5 * sin(rot.v[1]), env->pos.v[1],
			env->pos.v[2] - 0.5 * cos(rot.v[1]));
	if (env->keys[KEY_LEFT])
		env->pos = vec3(env->pos.v[0] - 0.5 * cos(rot.v[1]), env->pos.v[1],
			env->pos.v[2] - 0.5 * sin(rot.v[1]));
	if (env->keys[KEY_RIGHT])
		env->pos = vec3(env->pos.v[0] + 0.5 * cos(rot.v[1]), env->pos.v[1],
			env->pos.v[2] + 0.5 * sin(rot.v[1]));
}

int				key_press_hook(int key_code, t_env *env)
{
	env->keys[key_code] = 1;
	if (key_code == KEY_ESCAPE)
		exit(0);
	//ft_printf("Key pressed: %d\n", key_code);
	return (0);
}

int				key_release_hook(int key_code, t_env *env)
{
	env->keys[key_code] = 0;
	return (0);
}
