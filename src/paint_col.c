/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_col.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <njaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 15:31:52 by njaber            #+#    #+#             */
/*   Updated: 2018/09/16 19:42:15 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static t_uint	tex_px(t_png *tex, t_vec2 uv)
{
	t_uint		ret;

	if (tex == NULL || !isfinite(uv.v[0]) || !isfinite(uv.v[1]))
		return (0x445566);
	uv.v[0] -= floor(uv.v[0]);
	uv.v[1] -= floor(uv.v[1]);
	ret = tex->buf[(int)(uv.v[0] * tex->dim.v[0]) +
			(int)(uv.v[1] * tex->dim.v[1]) * tex->dim.v[0]];
	return (ret);
}

void			paint_col(t_env *env, int col, t_vec2 ray, t_vec2 v)
{
	int		i;
	t_scal	dist;
	t_scal	scal;
	t_ivec	hbounds;
	t_scal	tmp[8];

	(void)ray;
	dist = sqrt(sqr(v.v[0] - env->pos.v[0]) + sqr(v.v[1] - env->pos.v[2]));
	scal = (t_scal)(col - env->win.size.v[0] / 2) / (env->win.size.v[0] / 2);
	scal = sqrt(scal * scal + 1);
	hbounds.v[0] = (env->pos.v[1] - SIZE) / (dist / scal) *
		(env->win.size.v[0] / 2) + env->win.size.v[1] / 2;
	hbounds.v[1] = (env->pos.v[1]) / (dist / scal) *
		(env->win.size.v[0] / 2) + env->win.size.v[1] / 2;
	tmp[0] = (fabs(remainder(v.v[0], SIZE)) > fabs(remainder(v.v[1], SIZE))
				? v.v[0] : v.v[1]) / SIZE;
	tmp[1] = (hbounds.v[1] - hbounds.v[0]);
	tmp[2] = (SIZE - env->pos.v[1]) * env->win.size.v[0] / 2 * scal;
	tmp[3] = env->pos.v[1] * env->win.size.v[0] / 2 * scal;
	i = -1;
	while (++i < hbounds.v[0] && i < env->win.size.v[1])
		img_px(&env->win.img, tex_px(env->ceil, vec2_mult(vec2_add(
			vec2(env->pos.v[0], env->pos.v[2]), vec2_mult(ray,
			tmp[2] / (env->win.size.v[1] / 2 - i))), 1 / SIZE)), ivec(col, i));
	i--;
	while (++i < hbounds.v[1] && i < env->win.size.v[1])
		img_px(&env->win.img, tex_px(env->walls, vec2(tmp[0],
				(i - hbounds.v[0]) / tmp[1])), ivec(col, i));
	i--;
	while (++i < env->win.size.v[1])
		img_px(&env->win.img, tex_px(env->floor, vec2_mult(vec2_add(
			vec2(env->pos.v[0], env->pos.v[2]), vec2_mult(ray,
			tmp[3] / (i - env->win.size.v[1] / 2))), 1 / SIZE)), ivec(col, i));
}
