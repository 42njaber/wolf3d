/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 05:31:19 by njaber            #+#    #+#             */
/*   Updated: 2018/08/19 15:35:57 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

#define SIZE 20.

static void		paint_col(t_env *env, int col, unsigned int color, t_scal dist)
{
	int		i;

	i = -1;
	while (++i < env->win.size.v[1])
	{
		if (fabs((t_scal)(i - env->win.size.v[1] / 2.) /
				(env->win.size.v[0] / 2)) * dist > SIZE / 2)
			img_px(&env->win.img, 0xAAAAAA, ivec(col, i));
		else
			img_px(&env->win.img, color, ivec(col, i));
	}
}

static void		cast(t_env *env, int col)
{
	t_vec2			dir;
	t_vec2			v;
	t_vec2			comp;

	dir = m2dotv2(env->cam_mat, vec2((t_scal)(col - env->win.size.v[0] / 2) /
				(env->win.size.v[0] / 2), 1.));
	dir = vec2(dir.v[0] / sqrt(dir.v[0] * dir.v[0] + dir.v[1] * dir.v[1]),
		dir.v[1] / sqrt(dir.v[0] * dir.v[0] + dir.v[1] * dir.v[1]));
	v = vec2(env->pos.v[0], env->pos.v[2]);
	comp.v[0] = dir.v[0] > 0 ? (ceil(v.v[0] / SIZE) * SIZE - v.v[0]) / dir.v[0]
		: (floor(v.v[0] / SIZE) * SIZE - v.v[0]) / dir.v[0];
	comp.v[1] = dir.v[1] > 0 ? (ceil(v.v[1] / SIZE) * SIZE - v.v[1]) / dir.v[1]
		: (floor(v.v[1] / SIZE) * SIZE - v.v[1]) / dir.v[1];
	if (comp.v[0] < comp.v[1])
		paint_col(env, col, 0xFFAA00, comp.v[0]);
	else
		paint_col(env, col, 0x0033FF, comp.v[1]);
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
