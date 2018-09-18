/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 16:00:11 by njaber            #+#    #+#             */
/*   Updated: 2018/09/15 15:18:26 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		print_data(t_env *env)
{
	display_data_scal(&env->win, "FPS:", env->win.fps, 10);
	display_data_vec3(&env->win, "Positon:", env->pos, 30);
	display_data_scal(&env->win, "Rotation:", env->rot, 50);
	display_data_scal(&env->win, "Button:", env->button, 70);
}

static void		update(t_env *env)
{
	env->cam_mat = m2rotation(env->rot / 180 * M_PI);
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
