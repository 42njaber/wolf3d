/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_integrity_checks.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <njaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 16:51:35 by njaber            #+#    #+#             */
/*   Updated: 2018/08/22 18:14:03 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				checksum(uchar *buf)
{
	(void)buf;
	return (0);
}

int				validate_crc(int fd, uchar *data, t_png *png)
{
	uchar	crc[4];

	(void)data;
	(void)png;
	if (read(fd, crc, 4) != 4)
		return (-3);
	return (0);
}
