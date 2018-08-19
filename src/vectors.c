/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 01:17:25 by njaber            #+#    #+#             */
/*   Updated: 2018/08/19 05:41:18 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgxns.h"

t_vec3	vec_sub(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){v1.v[0] - v2.v[0], v1.v[1] - v2.v[1], v1.v[2] - v2.v[2]});
}

t_vec3	vec_add(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){v1.v[0] + v2.v[0], v1.v[1] + v2.v[1], v1.v[2] + v2.v[2]});
}

t_vec3	vec_mult(t_vec3 v1, t_scal d)
{
	return ((t_vec3){v1.v[0] * d, v1.v[1] * d, v1.v[2] * d});
}

t_scal	length(t_vec3 v1)
{
	return (sqrt(sqr(v1.v[0]) + sqr(v1.v[1]) + sqr(v1.v[2])));
}

t_scal	scalar(t_vec3 v1, t_vec3 v2)
{
	return (v1.v[0] * v2.v[0] + v1.v[1] * v2.v[1] + v1.v[2] * v2.v[2]);
}
