/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdittric <cdittric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 12:29:47 by cdittric          #+#    #+#             */
/*   Updated: 2018/09/25 18:30:49 by cdittric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			debug_map(t_env *env)
{
	static t_wall	walls[5] = {
		{{}, 0, 0, 0, {{{0, 0}}}, {{{0, 0}}}},
		{{}, 0, 0, 0, {{{0, 0}}}, {{{0, 0}}}},
		{{}, 0, 0, 0, {{{0, 0}}}, {{{0, 0}}}},
		{{}, 0, 0, 0, {{{0, 0}}}, {{{0, 0}}}},
		{{}, 0, 0, 0, {{{0, 0}}}, {{{0, 0}}}}};
	static t_sector	sector = {0., SIZE, NULL, NULL, 0, 0, 5, 0, 0};
	static t_map	map = {};

	walls[0].pos = vec3(cos(M_PI * 2. * 0. / 5.), sin(M_PI * 2. * 0. / 5.), 1.);
	walls[1].pos = vec3(cos(M_PI * 2. * 1. / 5.), sin(M_PI * 2. * 1. / 5.), 1.);
	walls[2].pos = vec3(cos(M_PI * 2. * 2. / 5.), sin(M_PI * 2. * 2. / 5.), 1.);
	walls[3].pos = vec3(cos(M_PI * 2. * 3. / 5.), sin(M_PI * 2. * 3. / 5.), 1.);
	walls[4].pos = vec3(cos(M_PI * 2. * 4. / 5.), sin(M_PI * 2. * 4. / 5.), 1.);
	map.path = "test";
	map.walls = walls;
	map.walls_count = 5;
	map.sectors = &sector;
	map.sectors_count = 1;
	map.self = &env->map_list;
	map.next = env->map_list;
	env->map_list = &map;
	env->map = &map;
}

static void		transform_map(t_env *env)
{
	unsigned int i;

	i = 0;
	while (i < env->map->walls_count)
	{
		i++;
	}
}

static void		sort_entities(t_env *env, int sector)
{
	env = NULL;
	sector = 0;
}

static void		sort_walls(t_env *env, int sector)
{
	env = NULL;
	sector = 0;
}

static void		generate_drawing_stack(t_env *env)
{
	unsigned int	i;
	int				wall_count;
	int				sector;

	i = 0;
	wall_count = 0;
	sector = env->current_sector;
	while (1)
	{
		sort_entities(env, sector);
		sort_walls(env, sector);
		i = 0;
		while (i < env->map->sectors[sector].walls_count)
			;
	}
}

static void		render_drawing_stack(t_env *env)
{
	env = NULL;
	return ;
}

static void		render_background(t_env *env)
{
	int		x;
	int		y;

	x = 0;
	while (x < env->win.size.v[0])
	{
		if (!env->cam.occlusion_column[x])
		{
			y = env->cam.occlusion_top[x];
			while (y < env->win.size.v[1] - env->cam.occlusion_bottom[x])
			{
				if (env->cam.occlusion[x * env->win.size.v[1] + y] < 255)
				{
					// TODO: Apply transparency + texture mapping to background
					img_px(&env->win.img, 0xff0000, ivec(x, y));
				}
				y++;
			}
		}
		x++;
	}
}

void	engine(t_env *env)
{
	ft_bzero(env->cam.occlusion, env->win.w * env->win.h * sizeof(char));
	ft_bzero(env->cam.occlusion_top, env->win.w * sizeof(int));
	ft_bzero(env->cam.occlusion_bottom, env->win.w * sizeof(int));
	ft_bzero(env->cam.occlusion_column, env->win.w * sizeof(char));
	ft_bzero(env->cam.visited_sectors, env->map->sectors_count * sizeof(char));
	env->cam.clusters_count = 0;
	env->cam.entities_count = 0;
	transform_map(env);
	generate_drawing_stack(env);
	render_drawing_stack(env);
	render_background(env);
}
