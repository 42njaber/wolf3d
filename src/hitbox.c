/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitbox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <njaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 08:50:38 by njaber            #+#    #+#             */
/*   Updated: 2018/08/20 10:20:18 by njaber           ###   ########.fr       */
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

void	clamp_pos(t_env *env)
{
	t_vec2	pos;
	t_scal	tmp;

	pos = vec2(env->pos.v[0], env->pos.v[2]);
	if (hit_tile(env->map_list, pos) == 0)
	{
		tmp = remainder(pos.v[0], SIZE);
		if (tmp > 0 && tmp < 1 && hit_tile(env->map_list,
					vec2(pos.v[0] - 1, pos.v[1])) != 0)
			env->pos.v[0] += 1 - tmp;
		else if (tmp < 0 && tmp > -1 && hit_tile(env->map_list,
					vec2(pos.v[0] + 1, pos.v[1])) != 0)
			env->pos.v[0] -= 1 + tmp;
		tmp = remainder(pos.v[1], SIZE);
		if (tmp > 0 && tmp < 1 && hit_tile(env->map_list,
					vec2(pos.v[0], pos.v[1] - 1)) != 0)
			env->pos.v[2] += 1 - tmp;
		else if (tmp < 0 && tmp > -1 && hit_tile(env->map_list,
					vec2(pos.v[0], pos.v[1] + 1)) != 0)
			env->pos.v[2] -= 1 + tmp;
	}
}
