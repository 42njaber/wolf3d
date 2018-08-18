/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 16:00:11 by njaber            #+#    #+#             */
/*   Updated: 2018/08/18 20:31:19 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		print_data(t_ptr *p)
{
	display_data_scal(p->win, "FPS:", p->win->fps, 10);
	display_data_vec3(p->win, "Positon:", p->pos, 30);
	display_data_vec3(p->win, "Rotation:", p->rot, 50);
	display_data_scal(p->win, "Button:", p->button, 70);
}

static void		update(t_ptr *p)
{
	identity(p->cam_mat);
	translate(p->cam_mat, (t_vec3){-p->win->img.size.x / 2,
			-p->win->img.size.y / 2, 0});
	scale(p->cam_mat, (t_vec3){
				2. / (t_scal)	ft_max(p->win->img.size.x, p->win->img.size.y),
				2. / (t_scal)ft_max(p->win->img.size.x, p->win->img.size.y), 1});
	rotate(p->cam_mat, p->rot);
}

int				loop_hook(void *parm)
{
	t_ptr	*p;

	p = (t_ptr*)parm;
	move(p);
	update(p);
	display(p);
	paint_window(p->win, NULL, 1);
	print_data(p);
	return (0);
}
