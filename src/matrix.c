/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdittric <cdittric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 17:23:33 by cdittric          #+#    #+#             */
/*   Updated: 2018/08/19 08:49:54 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** Matrices are column major. The first indexes are inside the first column.
** Transformation of vectors is done with (matrix * vector): the vector is on
** the right so that each column of the matrix is a vector of the new base in
** which the resulting vector will be expressed
*/

t_mat2	m2identity(void)
{
	t_mat2 ret;

	ret.m[0] = 1.0;
	ret.m[0] = 1.0;
	ret.m[0] = 1.0;
	ret.m[0] = 1.0;
	return (ret);
}

t_mat2	m2rotation(t_scal angle)
{
	t_mat2	ret;

	ret.m[0] = cos(angle);
	ret.m[1] = sin(angle);
	ret.m[2] = -sin(angle);
	ret.m[3] = cos(angle);
	return (ret);
}

t_mat2	m2dot(t_mat2 m1, t_mat2 m2)
{
	t_mat2	ret;

	ret.m[0] = m1.m[0] * m2.m[0] + m1.m[2] * m2.m[1];
	ret.m[1] = m1.m[1] * m2.m[0] + m1.m[3] * m2.m[1];
	ret.m[2] = m1.m[0] * m2.m[2] + m1.m[2] * m2.m[3];
	ret.m[3] = m1.m[1] * m2.m[2] + m1.m[3] * m2.m[3];
	return (ret);
}

t_vec2	m2dotv2(t_mat2 m, t_vec2 v)
{
	t_vec2	ret;

	ret.v[0] = m.m[0] * v.v[0] + m.m[2] * v.v[1];
	ret.v[1] = m.m[1] * v.v[0] + m.m[3] * v.v[1];
	return (ret);
}
