/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 05:31:19 by njaber            #+#    #+#             */
/*   Updated: 2018/08/19 11:04:41 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		paint_col(t_env *env, int col, unsigned int color)
{
	int		i;

	i = -1;
	while (++i < env->win.size.v[1])
		img_px(&env->win.img, color, ivec(col, i));
}

static void		cast(t_env *env, int col)
{
	t_vec2	dir;
	t_vec2	v;
	t_vec2	comp;

	(void)col;
	dir = m2dotv2(env->cam_mat, vec2((t_scal)(col - env->win.size.v[0] / 2) /
				(env->win.size.v[0] / 2), 1.));
	v = vec2(env->pos.v[0], env->pos.v[2]);
	comp = vec2(fabs(fmod(fmod(copysign(v.v[0], -dir.v[0]), 100) + 100, 100) / dir.v[0]),
			fabs(fmod(fmod(copysign(v.v[1], -dir.v[1]), 100) + 100, 100) / dir.v[1]));
	if (comp.v[0] > comp.v[1])
		paint_col(env, col, 0xFFAA00);
	else
		paint_col(env, col, 0x00AAFF);
}

void			display(t_env *env)
{
	int				x;

	x = 0;
	while (x < env->win.img.size.v[0])
	{
		cast(env, x);
		x++;
	}
}
