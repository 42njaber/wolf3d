/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_parse_zlib.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <njaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 15:00:14 by njaber            #+#    #+#             */
/*   Updated: 2018/09/04 22:03:17 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

uchar			get_next_bits(uchar *stream, uint *pos, uint len)
{
	uint	ret;

	if (len > 8)
		len = 8;
	ret = stream[*pos / 8] >> (*pos % 8);
	if (len < 8 - *pos % 8)
		ret = ret & (0xFF >> (8 - len));
	if (*pos % 8 + len > 8)
		ret |= (stream[*pos / 8 + 1] & (0xFF >> (8 - len - *pos % 8)))
					<< (8 - *pos % 8);
	*pos += len;
	return (ret);
}

static int		check_flags(uchar *stream)
{
	uchar	cmf;
	uchar	flg;

	cmf = stream[0];
	flg = stream[1];
	if ((cmf & 0x0F) != 8 || (flg & 0x20) != 0)
		return (-5);
	if ((((uint)cmf << 8) | flg) % 31 != 0)
		return (-10);
	return (0);
}

static int		parse_deflate(t_png *png, uchar *stream)
{
	uint	pos;
	int		final;
	int		ret;

	pos = 0;
	final = 0;
	ret = 0;
	while (!final)
	{
		if (pos / 8 >= png->_zlib_len - 6)
			return (-2);
		final = get_next_bits(stream, &pos, 1);
		ret = decompress_block(png, stream, &pos);
		if (ret < 0)
			break ;
	}
	return (ret);
}

static int		expand_length_codes(t_png *png)
{
	int		i;

	if ((png->_data = (uchar*)ft_memalloc(sizeof(uint) *
					png->_data_size)) == NULL)
		return (-666);
	i = -1;
	while ((size_t)++i < png->_data_size)
		png->_data[i] = (uchar)png->_codes[i];
	return (0);
}

int				parse_zlib(t_png *png)
{
	int		ret;

	if (png->_zlib_len < 6)
		return (-2);
	if (png->filter != 0)
		return (-5);
	if (png->compression != 0)
		return (-4);
	png->_data_size = png->dim.v[0] * png->dim.v[1] * 3 + png->dim.v[1];
	if ((png->_codes = (uint*)ft_memalloc(sizeof(uint) *
					png->_data_size)) == NULL)
		return (-666);
	if ((ret = check_flags(png->_zlib_stream)) >= 0)
		if ((ret = parse_deflate(png, png->_zlib_stream + 2)) >= 0)
			if ((ret = expand_length_codes(png)) >= 0)
				ret = checksum(png->_zlib_stream);
	free(png->_codes);
	png->_codes = NULL;
	return (ret);
}
