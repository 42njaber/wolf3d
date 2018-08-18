/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 13:17:27 by njaber            #+#    #+#             */
/*   Updated: 2018/08/18 20:30:15 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			init_environment(t_ptr *env)
{
	ft_bzero(env, sizeof(*env));
	if ((env->win = (t_win*)ft_memalloc(sizeof(t_win))) == NULL)
		ft_error("[Erreur] Failed to allocate memory\n");
	env->pos = (t_vec3){0, 3, 0};
	env->rot = (t_vec3){0, 0, 0};
	env->pos.v[0] = 0.0;
	env->pos.v[1] = 3.0;
	env->pos.v[2] = 0.0;
	env->rot.v[0] = 0.0;
	env->rot.v[1] = 0.0;
}
