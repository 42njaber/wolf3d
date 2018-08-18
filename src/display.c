/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 05:31:19 by njaber            #+#    #+#             */
/*   Updated: 2018/08/18 20:22:12 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static unsigned int		cast(t_ptr *p, t_vec3 dir)
{
	t_vec3 ori;

	ori = p->pos;
	dir = apply_mat_vec3(dir, p->cam_mat);
	return (0x00000);
}

void					display(t_ptr *p)
{
	t_ivec			px;
	unsigned int	color;

	px = (t_ivec){0, 0};
	while (px.y < p->win->img.size.y)
	{
		color = cast(p, (t_vec3){px.x, px.y, 1});
		img_px(&p->win->img, color, px);
		px.x = (px.x + 1) % p->win->img.size.x;
		if (px.x == 0)
			px.y++;
	}
}
