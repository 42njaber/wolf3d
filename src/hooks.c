/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 14:52:32 by njaber            #+#    #+#             */
/*   Updated: 2018/08/18 20:20:52 by cdittric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "mlx.h"

static int		close_hook(t_env *env)
{
	end_environment(env, EXIT_SUCCESS);
	return (0);
}

void		set_hooks(t_env *env)
{
	mlx_loop_hook(env->win->mlx, loop_hook, env);
	mlx_hook(env->win->win, EVENT_KEY_PRESS, 0, key_press_hook, env);
	mlx_hook(env->win->win, EVENT_KEY_RELEASE, 0, key_release_hook, env);
	mlx_hook(env->win->win, EVENT_MOUSE_PRESS, 0, button_press_hook, env);
	mlx_hook(env->win->win, EVENT_MOUSE_RELEASE, 0, button_release_hook, env);
	mlx_hook(env->win->win, EVENT_MOUSE_MOVE, 0, motion_hook, env);
	mlx_hook(env->win->win, EVENT_CLOSE, 0, close_hook, env);
	mlx_hook(env->win->win, EVENT_EXPOSE, 0, loop_hook, env);
}
