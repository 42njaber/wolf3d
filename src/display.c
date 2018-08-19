/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 05:31:19 by njaber            #+#    #+#             */
/*   Updated: 2018/08/19 06:17:06 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		cast(t_env *env, int col)
{
	t_vec3 ori;

	(void)col;
	ori = env->pos;
	//img_px(&env->win.img, color, px);
}

void			display(t_env *env)
{
	int				x;

	x = 0;
	while (x < env->win.img.size.v[1])
	{
		cast(env, x);
		x++;
	}
}
