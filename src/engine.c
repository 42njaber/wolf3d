/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdittric <cdittric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 12:29:47 by cdittric          #+#    #+#             */
/*   Updated: 2018/09/16 20:05:30 by cdittric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		sort_entities(t_env, int sector)
{
}

static void		sort_walls(t_env *env, int sector)
{
}

static void		generate_drawing_stack(t_env *env)
{
	int		i;
	int		wall_count
	int		sector;

	i = 0;
	wall_count = 0;
	sector = env->current_sector;
	while (1)
	{
		sort_entities(env, sector);
		sort_walls(env, sector);
		i = 0;
		while (i < env->map.sectors[sector].wall_count)
			env->win.clusters
	}
}

static void		render_drawing_stack(t_env *env)
{
	return ;
}

static void		render_background(t_env *env)
{
	int		x;
	int		y;

	x = 0;
	while (x < env->win.w)
	{
		if (!env->win.column_occlusion[x])
		{
			y = env->top_occlusion[x];
			while (y < env->win.h - env->win.bottom_occlusion[x])
			{
				if (env->win.occlusion[x * env->win.h + y] < 255)
				{
					// TODO: Apply transparency + texture mapping to background
					img_px(&env->img, 0xff0000, ivec(x, y));
				}
				y++;
			}
		}
		x++;
	}
}

void	engine(t_env *env)
{
	mlx_clear_window(env->mlx);
	ft_bzero(env->win.occlusion, env->win.w * env->win.h * sizeof(char));
	ft_bzero(env->win.top_occlusion, env->win.w * sizeof(int));
	ft_bzero(env->win.bottom_occlusion, env->win.w * sizeof(int));
	ft_bzero(env->win.column_occlusion, env->win.w * sizeof(char));
	ft_bzero(env->win.visited_sectors, env->map.sectors_count * sizeof(char));
	env->win.clusters_count = 0;
	env->win.entities_count = 0;
	generate_drawing_stack(env);
	render_drawing_stack(env);
	render_background(env);
}
	
