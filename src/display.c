/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 05:31:19 by njaber            #+#    #+#             */
/*   Updated: 2018/09/15 15:32:34 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static t_vec2	next_wall(t_vec2 v, t_vec2 ray)
{
	t_vec2	ret;
	t_vec2	dist;

	ret.v[0] = ray.v[0] > 0 ? ceil((v.v[0] + 0.00001) / SIZE) * SIZE :
		floor((v.v[0] - 0.00001) / SIZE) * SIZE;
	ret.v[1] = ray.v[1] > 0 ? ceil((v.v[1] + 0.00001) / SIZE) * SIZE :
		floor((v.v[1] - 0.00001) / SIZE) * SIZE;
	dist.v[0] = (ret.v[0] - v.v[0]) / ray.v[0];
	dist.v[1] = (ret.v[1] - v.v[1]) / ray.v[1];
	if (ray.v[0] != 0 && (ray.v[1] == 0 || dist.v[0] < dist.v[1]))
		ret.v[1] = v.v[1] + dist.v[0] * ray.v[1];
	else
		ret.v[0] = v.v[0] + dist.v[1] * ray.v[0];
	return (ret);
}

static void		cast_ray(t_env *env,  int col)
{
	t_vec2			ray;
	t_vec2			v;

	v = vec2(env->pos.v[0], env->pos.v[2]);
	ray = m2dotv2(env->cam_mat, vec2((t_scal)(col - env->win.size.v[0] / 2) /
				(env->win.size.v[0] / 2), 1.));
	ray = vec2(ray.v[0] / sqrt(ray.v[0] * ray.v[0] + ray.v[1] * ray.v[1]),
		ray.v[1] / sqrt(ray.v[0] * ray.v[0] + ray.v[1] * ray.v[1]));
	while (!!!0)
	{
		v = next_wall(v, ray);
		if (hit_tile(env->map_list, vec2(v.v[0] + copysign(0.0001, ray.v[0]),
							v.v[1] + copysign(0.0001, ray.v[1]))) != 0)
		{
			paint_col(env, col, ray, v);
			break ;
		}
	}
}

void			display(t_env *env)
{
	int				x;

	x = 0;
	while (x < env->win.img.size.v[0])
	{
		cast_ray(env, x);
		x++;
	}
}
