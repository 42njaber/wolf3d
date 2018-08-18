/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 17:01:19 by njaber            #+#    #+#             */
/*   Updated: 2018/08/18 20:38:18 by cdittric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		launch_window(t_env *env)
{
	if ((env.mlx = mlx_init()) == 0)
		ft_error("[Error] Failed to initialize mlx\n");
	if ((init_new_win(env->mlx, env->win,
					(t_ivec){env->win.w, env->win.h}, "Wolf3D")) == 0)
		ft_error("[Error] Failed to initialize window\n");
	set_hooks(env);
}

static void		read_map_line(t_env *env, char *line, int y)
{
	int		i;
	char	*tmp;

	if ((env->map[y] = (int*)ft_memalloc(sizeof(int) * env->mdim.x)) == NULL)
		ft_error("Malloc error\n");
	i = -1;
	tmp = line;
	while (++i < env->mdim.x)
	{
		env->map[y][i] = ft_atoi(tmp);
		tmp = ft_strchr(tmp, ',');
		if (i < env->mdim.x - 1 && tmp == NULL)
			ft_error("Error while reading file: "
					"not enough numbers on line %i\n", y);
		if (i == env->mdim.x - 1 && tmp != NULL)
			ft_error("Error while reading file: "
					"too many numbers on line %i\n", y);
		tmp++;
	}
}

static int		read_map(t_map *map)
{
	int		i;
	int		ret;
	char	*line;

	if ((ret = get_next_line(fd, &line)) != 1 || ft_strchr(line, ',') == NULL)
		ft_error("Error while reading file (line: %d)\n", line);
	env->mdim.x = ft_atoi(line);
	env->mdim.y = ft_atoi(ft_strchr(line, ',') + 1);
	free(line);
	if ((env->map = (int**)ft_memalloc(sizeof(int*) * env->mdim.y)) == NULL)
		ft_error("Malloc error\n");
	i = -1;
	while (++i < env->mdim.y)
	{
		if (get_next_line(fd, &line) !=  1)
			ft_error("Error while reading file: not enough lines\n");
		read_map_line(env, line, i);
		free(line);
	}
	return (EXIT_SUCCESS);
}

static void		read_map_list(t_env *env)
{
	t_map	*map;
	int		fd;

	map = env->map_list;
	while (map != NULL)
	{
		fd = fopen(map->path, O_RDONLY);
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
		end_environment(env);
	}
}

void static		parse_arguments(t_env *env, int argc, char *argv)
{
	env->win.w = DEFAULT_WINDOW_WIDTH;
	env->win.h = DEFAULT_WINDOW_HEIGHT;
	while (--argc > 0 && ++argv != NULL)
	{
		if (add_map(env, *argv) == NULL)
		{
			ft_error("Failed to allocate map structure.\n");
			end_environment(env);
		}
	}
}

void			end_environment(t_env *env, int status);
{
	while (env->map_list != NULL)
		(void)delete_map(env);
	return (status);
}

int				main(int argc, char **argv)
{
	t_env	env;

	init_environment(&env);
	parse_arguments(&env, argc, argv);
	read_maps(&env;
	launch_window(&env);
	mlx_loop(env.mlx);
}
