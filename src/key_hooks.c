/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 14:52:32 by njaber            #+#    #+#             */
/*   Updated: 2018/08/18 12:53:56 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <math.h>

void			move(t_ptr *p)
{
	t_vec3		rot;

	rot = (t_vec3){p->rot.x * M_PI / 180, p->rot.y * M_PI / 180,
		p->rot.z * M_PI / 180};
	if (p->keys[K_UP])
		p->pos = (t_vec3){p->pos.x - 0.5 * sin(rot.y), p->pos.y,
			p->pos.z + 0.5 * cos(rot.y)};
	if (p->keys[K_DOWN])
		p->pos = (t_vec3){p->pos.x + 0.5 * sin(rot.y), p->pos.y,
			p->pos.z - 0.5 * cos(rot.y)};
	if (p->keys[K_LEFT])
		p->pos = (t_vec3){p->pos.x - 0.5 * cos(rot.y), p->pos.y,
			p->pos.z - 0.5 * sin(rot.y)};
	if (p->keys[K_RIGHT])
		p->pos = (t_vec3){p->pos.x + 0.5 * cos(rot.y), p->pos.y,
			p->pos.z + 0.5 * sin(rot.y)};
}

int				key_press_hook(int key_code, void *parm)
{
	t_ptr	*p;

	p = (t_ptr*)parm;
	p->keys[key_code] = 1;
	if (key_code == K_ESC)
		exit(0);
	//ft_printf("Key pressed: %d\n", key_code);
	return (0);
}

int				key_release_hook(int key_code, void *parm)
{
	t_ptr	*p;

	p = (t_ptr*)parm;
	p->keys[key_code] = 0;
	return (0);
}
