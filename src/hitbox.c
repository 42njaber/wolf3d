/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitbox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <njaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 08:50:38 by njaber            #+#    #+#             */
/*   Updated: 2018/09/16 19:00:33 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		hit_tile(t_map *map, t_vec2 point)
{
	t_ivec	tile;

	tile = ivec((int)floor(point.v[0] / SIZE), (int)floor(point.v[1] / SIZE));
	if (tile.v[0] < 0 || tile.v[1] < 0 || tile.v[0] >= map->dim.v[0] ||
			tile.v[1] >= map->dim.v[1])
		return (-1);
	return (map->grid[tile.v[1]][tile.v[0]]);
}

void	clamp_move(t_env *env)
{
	t_vec2	pos;
	t_scal	tmp;
	t_scal	dir;

	pos = vec2(env->pos.v[0], env->pos.v[2]);
	if (hit_tile(env->map_list, pos) == 0)
	{
		tmp = remainder(pos.v[0], SIZE);
		dir = copysign(1, env->mov.v[0]);
		if (dir != 0 && !(fabs(tmp) < 1 && (tmp >= 0) != (dir > 0) &&
				(hit_tile(env->map_list, vec2(pos.v[0] + dir,
				pos.v[1] - 1)) != 0 || hit_tile(env->map_list,
				vec2(pos.v[0] + dir, pos.v[1] + 1)) != 0)))
			env->pos.v[0] += env->mov.v[0];
		tmp = remainder(pos.v[1], SIZE);
		dir = copysign(1, env->mov.v[1]);
		if (dir != 0 && !(fabs(tmp) < 1 && (tmp >= 0) != (dir > 0) &&
				(hit_tile(env->map_list, vec2(pos.v[0] - 1,
				pos.v[1] + dir)) != 0 || hit_tile(env->map_list,
				vec2(pos.v[0] + 1, pos.v[1] + dir)) != 0)))
			env->pos.v[2] += env->mov.v[1];
	}
	else
		env->pos = vec3_add(env->pos, vec3(env->mov.v[0], 0, env->mov.v[1]));
}
