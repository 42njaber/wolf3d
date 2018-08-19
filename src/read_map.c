/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 05:37:55 by njaber            #+#    #+#             */
/*   Updated: 2018/08/19 08:34:44 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		read_map_line(t_map *map, char *line, int y)
{
	int		i;
	char	*tmp;

	if ((map->grid[y] = (int*)ft_memalloc(sizeof(int) * map->dim.v[0])) == NULL)
		ft_error("Malloc error\n");
	i = -1;
	tmp = line;
	while (++i < map->dim.v[0])
	{
		map->grid[y][i] = ft_atoi(tmp);
		tmp = ft_strchr(tmp, ',');
		if (i < map->dim.v[0] - 1 && tmp == NULL)
			ft_error("Error while reading file: "
					"not enough numbers on line %i\n", y);
		if (i == map->dim.v[0] - 1 && tmp != NULL)
			ft_error("Error while reading file: "
					"too many numbers on line %i\n", y);
		tmp++;
	}
}

static int		read_map(t_map *map, int fd)
{
	int		i;
	int		ret;
	char	*line;

	if ((ret = get_next_line(fd, &line)) != 1
			|| ft_strchr(line, ',') == NULL)
		ft_error("Error while reading file (line: %d)\n", line);
	map->dim.v[0] = ft_atoi(line);
	map->dim.v[1] = ft_atoi(ft_strchr(line, ',') + 1);
	free(line);
	if ((map->grid = (int**)ft_memalloc(sizeof(int*) * map->dim.v[1])) == NULL)
		ft_error("Malloc error\n");
	i = -1;
	while (++i < map->dim.v[1])
	{
		if (get_next_line(fd, &line) !=  1)
			ft_error("Error while reading file: not enough lines\n");
		read_map_line(map, line, i);
		free(line);
	}
	return (EXIT_SUCCESS);
}

t_map			*delete_map(t_map *map)
{
	int		i;
	t_map	*ret;

	ret = map->next;
	if (map->next != NULL)
		map->next->self = map->self;
	*map->self = map->next;
	if (map->grid != NULL)
	{
		i = -1;
		while (i < map->dim.v[1])
			if (map->grid[i] != NULL)
				free(map->grid[i]);
		free(map->grid);
	}
	free(map);
	return (ret);
}

void			read_map_list(t_env *env)
{
	t_map	*map;
	int		fd;

	map = env->map_list;
	while (map != NULL)
	{
		fd = open(map->path, O_RDONLY);
		if (fd < 0)
		{
			ft_error("Could not read file %s\n", map->path);
			map = delete_map(map);
			continue ;
		}
		else if (read_map(map, fd) == EXIT_FAILURE)
			map = delete_map(map);
		else
			map = map->next;
		close(fd);
	}
	if (env->map_list == NULL)
	{
		ft_error("Could not open any map\n");
		end_environment(env, 0);
	}
}

t_map			*add_map(t_env *env, char *path)
{
	t_map	**lst;
	t_map	*map;

	if ((map = (t_map*)ft_memalloc(sizeof(t_map))) == NULL)
		return (NULL);
	lst = &env->map_list;
	while (*lst != NULL)
		lst = &(*lst)->next;
	*lst = map;
	map->self = lst;
	map->path = path;
	return (map);
}
