/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 14:52:32 by njaber            #+#    #+#             */
/*   Updated: 2018/09/16 19:01:46 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

#define SPEED 0.5

static void		update_jump(t_env *env)
{
	env->pos.v[1] += env->inertia;
	if (env->inertia < 0 && env->pos.v[1] <= 6)
		env->inertia = 0;
	if (env->pos.v[1] > SIZE - 1)
	{
		env->pos.v[1] = SIZE - 1;
		if (env->inertia > 0)
			env->inertia = 0;
	}
	else if (env->pos.v[1] < 6)
		env->pos.v[1] = 6;
	else
		env->inertia -= 0.1;
}

void			move(t_env *env)
{
	t_scal		rot;

	rot = env->rot * M_PI / 180;
	env->mov = vec2(0, 0);
	if ((env->keys[KEY_UP] || env->keys[KEY_W]))
		env->mov = vec2_add(env->mov,
				vec2(-SPEED * sin(rot), SPEED * cos(rot)));
	if (env->keys[KEY_DOWN] || env->keys[KEY_S])
		env->mov = vec2_add(env->mov,
				vec2(SPEED * sin(rot), -SPEED * cos(rot)));
	if (env->keys[KEY_LEFT] || env->keys[KEY_A])
		env->mov = vec2_add(env->mov,
				vec2(-SPEED * cos(rot), -SPEED * sin(rot)));
	if (env->keys[KEY_RIGHT] || env->keys[KEY_D])
		env->mov = vec2_add(env->mov,
				vec2(SPEED * cos(rot), SPEED * sin(rot)));
	clamp_move(env);
	update_jump(env);
}

int				key_press_hook(int key_code, t_env *env)
{
	env->keys[key_code] = 1;
	if (key_code == KEY_SPACE && env->pos.v[1] <= 6)
		env->inertia = 0.7;
	if (key_code == KEY_ESCAPE)
		end_environment(env, EXIT_SUCCESS);
	//ft_printf("Key pressed: %d\n", key_code);
	return (0);
}

int				key_release_hook(int key_code, t_env *env)
{
	env->keys[key_code] = 0;
	return (0);
}
