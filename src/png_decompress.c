/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_decompress.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <njaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 15:00:14 by njaber            #+#    #+#             */
/*   Updated: 2018/08/23 16:12:05 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		check_flags(uchar *buf)
{
	uchar	cmf;
	uchar	flg;

	cmf = buf[0];
	flg = buf[1];
	if ((cmf & 0x0F) != 8 || (flg & 0x20) != 0)
		return (-5);
	if ((((uint)cmf << 8) | flg) % 31 != 0)
		return (-10);
	return (0);
}

uchar			get_next_bits(uchar *buf, uint *pos, uint len)
{
	uint	ret;

	if (len > 8)
		len = 8;
	ret = buf[*pos / 8] >> (*pos % 8);
	if (len < 8 - *pos % 8)
		ret = ret & (0xFF >> (8 - len));
	if (*pos % 8 + len > 8)
		ret |= (buf[*pos / 8 + 1] & (0xFF >> (8 - len - *pos % 8)))
					<< (8 - *pos % 8);
	*pos += len;
	return (ret);
}

static int		decompress_deflate(t_png *png, uchar *buf)
{
	uint	pos;
	uint	data;
	int		final_block;
	int		ret;

	pos = 16;
	final_block = 0;
	ret = 0;
	while (!final_block)
	{
		if ((pos + 3) / 8 > png->_block_len - 4)
			return (-2);
		data = get_next_bits(buf, &pos, 3);
		ft_printf("Header bits: %3.3b\n", data);
		if ((data & 0x1) == 0x1)
			final_block = 1;
		ret = decompress_block(png, buf, data);
		if (ret < 0)
			break ;
	}
	return (ret);
}

int				parse_zlib(t_png *png, uchar *buf)
{
	int		ret;

	if (png->_block_len < 6)
		return (-2);
	if (png->filter != 0)
		return (-5);
	if (png->compression != 0)
		return (-4);
	if ((png->buf = (uchar*)ft_memalloc(sizeof(uchar) * png->dim.v[0] *
					png->dim.v[1])) == NULL)
	{
		free(buf);
		destroy_png(&png);
		ft_error("Malloc error\n");
	}
	if ((ret = check_flags(buf)) >= 0)
		if ((ret = decompress_deflate(png, buf)) >= 0)
			ret = checksum(buf);
	return (ret);
}
