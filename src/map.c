/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdittric <cdittric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 19:14:05 by cdittric          #+#    #+#             */
/*   Updated: 2018/08/18 20:28:04 by cdittric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** add_map:
** Add a map element at the beginning of env->map_list and returns its address.
*/

t_map	*add_map(t_env *env, char *name)
{
	t_map	*map;

	map = (t_map)malloc(sizeof(t_map));
	if (new == NULL)
		return (NULL);
	ft_bzero(map, sizeof(map));
	map->path = name;
	map->self = &env->map_list;
	map->next = env->map_list;
	map->map_list = map;
	return (map);
}

/*
** delete_map:
** Deletes the map and returns the next element.
*/

t_map	*delete_map(t_map *map)
{
	t_map	*ret;
	
	ret = map->next;
	if (map->next != NULL)
		map->next->self = map->self;
	*map->self = map->next;
	free(map);
	return (ret);
}
