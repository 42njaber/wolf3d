/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 14:52:32 by njaber            #+#    #+#             */
/*   Updated: 2018/08/18 20:30:30 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "mlx.h"

static int		close_hook(void *parm)
{
	(void)parm;
	exit(0);
	return (0);
}

void		set_hooks(t_ptr *p)
{
	mlx_loop_hook(p->win->mlx, loop_hook, (void*)p);
	mlx_expose_hook(p->win->win, loop_hook, (void*)p);
	mlx_hook(p->win->win, 6, 0, motion_hook, (void*)p);
	mlx_hook(p->win->win, 4, 0, button_press_hook, (void*)p);
	mlx_hook(p->win->win, 5, 0, button_release_hook, (void*)p);
	mlx_hook(p->win->win, 2, 0, key_press_hook, (void*)p);
	mlx_hook(p->win->win, 3, 0, key_release_hook, (void*)p);
	mlx_hook(p->win->win, 17, 0, close_hook, (void*)p);
}
