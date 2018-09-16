/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 22:58:17 by njaber            #+#    #+#             */
/*   Updated: 2018/09/16 19:40:12 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_uint		color_gradiant(t_uint c1, t_uint c2, t_scal gradiant)
{
	unsigned int		ret;

	ret = 0;
	ret += (t_uint)((c1 >> 24) * (1 - gradiant) +
			(c2 >> 24) * gradiant - 0.5) << 24;
	ret += (t_uint)(((c1 >> 16) & 0xFF) * (1 - gradiant) +
			((c2 >> 16) & 0xFF) * gradiant - 0.5) << 16;
	ret += (t_uint)(((c1 >> 8) & 0xFF) * (1 - gradiant) +
			((c2 >> 8) & 0xFF) * gradiant - 0.5) << 8;
	ret += (t_uint)((c1 & 0xFF) * (1 - gradiant) +
			(c2 & 0xFF) * gradiant - 0.5);
	return (ret);
}
