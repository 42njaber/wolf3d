/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdittric <cdittric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 17:23:33 by cdittric          #+#    #+#             */
/*   Updated: 2018/09/18 18:07:57 by cdittric         ###   ########.fr       */
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
	ret.m[1] = 0.0;
	ret.m[2] = 0.0;
	ret.m[3] = 1.0;
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

t_mat3	m3rotation(t_scal angle)
{
	t_mat3	ret;

	ret.m[0] = cos(angle);
	ret.m[1] = sin(angle);
	ret.m[2] = 0.0;
	ret.m[3] = -sin(angle);
	ret.m[4] = cos(angle);
	ret.m[5] = 0.0;
	ret.m[6] = 0.0;
	ret.m[7] = 0.0;
	ret.m[8] = 1.0;
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

t_mat3	m3dot(t_mat3 m1, t_mat3 m2)
{
	t_mat3	ret;

	ret.m[0] = m1.m[0] * m2.m[0] + m1.m[3] * m2.m[1] + m1.m[6] * m2.m[2];
	ret.m[1] = m1.m[1] * m2.m[0] + m1.m[4] * m2.m[4] + m1.m[7] * m2.m[5];
	ret.m[2] = m1.m[2] * m2.m[0] + m1.m[5] * m2.m[7] + m1.m[8] * m2.m[8];
	ret.m[3] = m1.m[0] * m2.m[3] + m1.m[3] * m2.m[1] + m1.m[6] * m2.m[2];
	ret.m[4] = m1.m[1] * m2.m[3] + m1.m[4] * m2.m[4] + m1.m[7] * m2.m[5];
	ret.m[5] = m1.m[2] * m2.m[3] + m1.m[5] * m2.m[7] + m1.m[8] * m2.m[8];
	ret.m[6] = m1.m[0] * m2.m[6] + m1.m[3] * m2.m[1] + m1.m[6] * m2.m[2];
	ret.m[7] = m1.m[1] * m2.m[6] + m1.m[4] * m2.m[4] + m1.m[7] * m2.m[5];
	ret.m[8] = m1.m[2] * m2.m[6] + m1.m[5] * m2.m[7] + m1.m[8] * m2.m[8];
	return (ret);
}

t_vec2	m2dotv2(t_mat2 m, t_vec2 v)
{
	t_vec2	ret;

	ret.v[0] = m.m[0] * v.v[0] + m.m[2] * v.v[1];
	ret.v[1] = m.m[1] * v.v[0] + m.m[3] * v.v[1];
	return (ret);
}

t_vec3	m3dotv3(t_mat3 m, t_vec3 v)
{
	t_vec3	ret;

	ret.v[0] = m.m[0] * v.v[0] + m.m[3] * v.v[1] + m.m[6] * v.v[2];
	ret.v[1] = m.m[1] * v.v[0] + m.m[4] * v.v[1] + m.m[7] * v.v[2];
	ret.v[2] = m.m[2] * v.v[0] + m.m[5] * v.v[1] + m.m[8] * v.v[2];
	return (ret);
}
