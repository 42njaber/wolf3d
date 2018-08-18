/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 14:52:32 by njaber            #+#    #+#             */
/*   Updated: 2018/08/18 20:25:18 by cdittric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <math.h>

void			move(t_ptr *env)
{
	t_vec3		rot;

	rot = (t_vec3){env->rot.x * M_PI / 180, env->rot.y * M_PI / 180,
		env->rot.z * M_PI / 180};
	if (env->keys[K_UP])
		env->pos = (t_vec3){env->pos.x - 0.5 * sin(rot.y), env->pos.y,
			env->pos.z + 0.5 * cos(rot.y)};
	if (env->keys[K_DOWN])
		env->pos = (t_vec3){env->pos.x + 0.5 * sin(rot.y), env->pos.y,
			env->pos.z - 0.5 * cos(rot.y)};
	if (env->keys[K_LEFT])
		env->pos = (t_vec3){env->pos.x - 0.5 * cos(rot.y), env->pos.y,
			env->pos.z - 0.5 * sin(rot.y)};
	if (env->keys[K_RIGHT])
		env->pos = (t_vec3){env->pos.x + 0.5 * cos(rot.y), env->pos.y,
			env->pos.z + 0.5 * sin(rot.y)};
}

int				key_press_hook(int key_code, void *parm)
{
	t_ptr	*env;

	env = (t_ptr*)parm;
	env->keys[key_code] = 1;
	if (key_code == K_ESC)
		exit(0);
	//ft_printf("Key pressed: %d\n", key_code);
	return (0);
}

int				key_release_hook(int key_code, void *parm)
{
	t_ptr	*env;

	env = (t_ptr*)parm;
	env->keys[key_code] = 0;
	return (0);
}
