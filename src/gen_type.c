/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <njaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 06:20:57 by njaber            #+#    #+#             */
/*   Updated: 2018/08/19 06:30:46 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_vec3		vec3(float x, float y, float z)
{
	t_vec3	ret;

	ret.v[0] = x;
	ret.v[1] = y;
	ret.v[2] = z;
	return (ret);
}

t_vec2		vec2(float x, float y)
{
	t_vec2	ret;

	ret.v[0] = x;
	ret.v[1] = y;
	return (ret);
}

t_ivec		ivec(int x, int y)
{
	t_ivec	ret;

	ret.v[0] = x;
	ret.v[1] = y;
	return (ret);
}
