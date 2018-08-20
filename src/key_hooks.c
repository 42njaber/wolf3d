/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 14:52:32 by njaber            #+#    #+#             */
/*   Updated: 2018/08/20 10:22:00 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>

#define SPEED 0.2

void			move(t_env *env)
{
	t_scal		rot;

	rot = env->rot * M_PI / 180;
	if (env->keys[KEY_UP])
		env->pos = vec3(env->pos.v[0] - SPEED * sin(rot), env->pos.v[1],
			env->pos.v[2] + SPEED * cos(rot));
	if (env->keys[KEY_DOWN])
		env->pos = vec3(env->pos.v[0] + SPEED * sin(rot), env->pos.v[1],
			env->pos.v[2] - SPEED * cos(rot));
	if (env->keys[KEY_LEFT])
		env->pos = vec3(env->pos.v[0] - SPEED * cos(rot), env->pos.v[1],
			env->pos.v[2] - SPEED * sin(rot));
	if (env->keys[KEY_RIGHT])
		env->pos = vec3(env->pos.v[0] + SPEED * cos(rot), env->pos.v[1],
			env->pos.v[2] + SPEED * sin(rot));
	clamp_pos(env);
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
