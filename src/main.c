/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 17:01:19 by njaber            #+#    #+#             */
/*   Updated: 2018/08/19 07:04:07 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		launch_window(t_env *env)
{
	t_ivec		win_size;

	win_size.v[0] = DEFAULT_WINDOW_WIDTH;
	win_size.v[1] = DEFAULT_WINDOW_HEIGHT;
	if ((env->mlx = mlx_init()) == 0)
		ft_error("[Error] Failed to initialize mlx\n");
	if ((init_new_win(env->mlx, &env->win, win_size, "Wolf3D")) == 0)
		ft_error("[Error] Failed to initialize window\n");
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
		{
			ft_error("Failed to allocate map structure.\n");
			end_environment(env, 0);
		}
	}
}

void			end_environment(t_env *env, int status)
{
	t_map	*lst;
	t_map	*lst2;

	lst = env->map_list;
	while (lst != NULL)
	{
		lst2 = lst->next;
		delete_map(lst);
		lst = lst2;
	}
	exit(status);
}

int				main(int argc, char **argv)
{
	t_env	env;

	init_environment(&env);
	ft_printf("Test3\n");
	parse_arguments(&env, argc, argv);
	ft_printf("Test5\n");
	read_map_list(&env);
	ft_printf("Test7\n");
	launch_window(&env);
	ft_printf("Test9\n");
	mlx_loop(env.mlx);
}
