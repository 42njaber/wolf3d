/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 17:01:19 by njaber            #+#    #+#             */
/*   Updated: 2018/08/20 14:43:15 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		launch_window(t_env *env)
{
	t_ivec		win_size;

	win_size.v[0] = DEFAULT_WINDOW_WIDTH;
	win_size.v[1] = DEFAULT_WINDOW_HEIGHT;
	if ((env->mlx = mlx_init()) == NULL)
		ft_error("[Error] Failed to initialize mlx\n");
	if ((init_new_win(env, &env->win, win_size, "Wolf3D")) == EXIT_FAILURE)
		ft_error("[Error] Failed to initialize window\n");
	if ((env->text = decode_png(env->mlx, "ressource/tmp.png")) == NULL)
		ft_error("[Error] Failed to read tmp.png\n");
	set_hooks(env);
}

void static		parse_arguments(t_env *env, int argc, char **argv)
{
	int		i;

	env->win.w = DEFAULT_WINDOW_WIDTH;
	env->win.h = DEFAULT_WINDOW_HEIGHT;
	i = 0;
	while (++i < argc)
	{
		if (add_map(env, argv[i]) == NULL)
		ft_error("Failed to allocate map structure.\n");
	}
}

void			end_environment(t_env *env, int status)
{
	while (env->map_list != NULL)
		(void)delete_map(env->map_list);
	if (env->win.img.link != NULL)
		mlx_destroy_image(env->mlx, env->win.img.link);
	if (env->win.win != NULL)
		mlx_destroy_window(env->mlx, env->win.win);
	exit(status);
}

void			end_environment_callback(void *env, int status)
{
	end_environment(env, status);
}

int				main(int argc, char **argv)
{
	t_env	env;

	ft_set_error_callback(end_environment_callback, &env);
	init_environment(&env);
	parse_arguments(&env, argc, argv);
	read_map_list(&env);
	launch_window(&env);
	mlx_loop(env.mlx);
}
