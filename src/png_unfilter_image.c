/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_unfilter_image.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <njaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 21:33:19 by njaber            #+#    #+#             */
/*   Updated: 2018/09/04 22:57:39 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		unfilter_color(t_png *png, uchar *color,
											uchar filter, t_ivec pos)
{
	if (filter == 1)
	{
		color[3] = (uchar)(color[3] + (((pos.v[0] == 0 ? 0 : png->buf[pos.v[0] +
					pos.v[1] * png->dim.v[0] - 1]) >> 24) & 0xFF));
		color[2] = (uchar)(color[2] + (((pos.v[0] == 0 ? 0 : png->buf[pos.v[0] +
					pos.v[1] * png->dim.v[0] - 1]) >> 16) & 0xFF));
		color[1] = (uchar)(color[1] + (((pos.v[0] == 0 ? 0 : png->buf[pos.v[0] +
					pos.v[1] * png->dim.v[0] - 1]) >> 8) & 0xFF));
		color[0] = (uchar)(color[0] + ((pos.v[0] == 0 ? 0 : png->buf[pos.v[0] +
					pos.v[1] * png->dim.v[0] - 1]) & 0xFF));
	}
	else if (filter == 2)
	{
		color[3] = (uchar)(color[3] + (((pos.v[1] == 0 ? 0 : png->buf[pos.v[0] +
					(pos.v[1] - 1) * png->dim.v[0]]) >> 24) & 0xFF));
		color[2] = (uchar)(color[2] + (((pos.v[1] == 0 ? 0 : png->buf[pos.v[0] +
					(pos.v[1] - 1) * png->dim.v[0]]) >> 16) & 0xFF));
		color[1] = (uchar)(color[1] + (((pos.v[1] == 0 ? 0 : png->buf[pos.v[0] +
					(pos.v[1] - 1) * png->dim.v[0]]) >> 8) & 0xFF));
		color[0] = (uchar)(color[0] + ((pos.v[1] == 0 ? 0 : png->buf[pos.v[0] +
					(pos.v[1] - 1) * png->dim.v[0]]) & 0xFF));
	}
	return ;
}

int				unfilter_image(t_png *png)
{
	int			i;
	int			j;
	uchar		color[4];
	uchar		filter;

	j = -1;
	while (++j < png->dim.v[1])
	{
		filter = png->_data[j * (1 + png->dim.v[0] * 3)];
		ft_printf("filter: %hhu\n", filter);
		i = -1;
		while (++i < png->dim.v[0])
		{
			color[2] = png->_data[1 + i * 3 + j * (1 + png->dim.v[0] * 3)];
			color[1] = png->_data[2 + i * 3 + j * (1 + png->dim.v[0] * 3)];
			color[0] = png->_data[3 + i * 3 + j * (1 + png->dim.v[0] * 3)];
			unfilter_color(png, color, filter, ivec(i, j));
			ft_printf("px color: %08X\n", *(uint*)color);
			png->buf[i + j * png->dim.v[0]] = *(uint*)color;
		}
	}
	return (0);
}
