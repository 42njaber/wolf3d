/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 01:32:56 by njaber            #+#    #+#             */
/*   Updated: 2018/08/18 12:07:54 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		button_press_hook(int button, int x, int y, void *parms)
{
	t_ptr	*p;

	(void)(x + y);
	p = (t_ptr*)parms;
	if (button == 1)
	{
		p->tmp_mouse_pos = (t_ivec){x, y};
		p->mouse_pos = (t_ivec){x, y};
		p->origin_rot = p->rot;
	}
	if (button < 4)
		p->button = button;
	return (0);
}

int		button_release_hook(int button, int x, int y, void *parms)
{
	t_ptr	*p;

	p = (t_ptr*)parms;
	(void)(button + x + y);
	if (button == 1)
	{
		p->rot = (t_vec3){fmax(-90, fmin(90, p->origin_rot.x + (p->mouse_pos.y
					- p->tmp_mouse_pos.y) * -0.25)), fmod(p->origin_rot.y +
					(p->mouse_pos.x - p->tmp_mouse_pos.x) * -0.25, 360), 0};
	}
	if (button == p->button)
		p->button = -1;
	return (0);
}

int		motion_hook(int x, int y, void *parm)
{
	t_ptr	*p;

	p = (t_ptr*)parm;
	p->mouse_pos = (t_ivec){x, y};
	if (p->button == 1)
	{
		p->rot = (t_vec3){fmax(-90, fmin(90, p->origin_rot.x + (p->mouse_pos.y
					- p->tmp_mouse_pos.y) * -0.25)), fmod(p->origin_rot.y +
					(p->mouse_pos.x - p->tmp_mouse_pos.x) * -0.25, 360), 0};
	}
	return (0);
}
