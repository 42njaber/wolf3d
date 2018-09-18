/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_parse_zlib.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <njaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 15:00:14 by njaber            #+#    #+#             */
/*   Updated: 2018/09/15 23:23:27 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_uint			get_next_bits(t_uchar *stream, t_uint *pos, t_uint len)
{
	t_uint	ret;
	t_uchar	offset;

	if (len > 32)
		len = 32;
	ret = stream[*pos / 8] >> (*pos % 8);
	offset = 8 - *pos % 8;
	while (offset < len)
	{
		ret |= stream[(*pos + offset) / 8] << offset;
		offset += 8;
	}
	ret &= 0xFFFFFFFF >> (32 - len);
	*pos += len;
	return (ret);
}

static int		check_flags(t_uchar *stream)
{
	t_uchar	cmf;
	t_uchar	flg;

	cmf = stream[0];
	flg = stream[1];
	if ((cmf & 0x0F) != 8 || (flg & 0x20) != 0)
		return (-5);
	if ((((t_uint)cmf << 8) | flg) % 31 != 0)
		return (-10);
	return (0);
}

static int		parse_deflate(t_png *png, t_uchar *stream)
{
	t_uint	pos;
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
	int		j;
	int		len;
	int		pos;

	i = -1;
	j = 0;
	while ((size_t)++i < png->_codes_len)
	{
		if ((size_t)j >= png->_data_size)
			return (-2);
		if (png->_codes[i] >= 0)
			png->_data[j++] = (t_uchar)png->_codes[i];
		else
		{
			len = -png->_codes[i++];
			if ((size_t)i >= png->_codes_len || (pos = j - png->_codes[i]) < 0)
				return (-2);
			while (len-- > 0)
			{
				if ((size_t)j >= png->_data_size)
					return (-2);
				png->_data[j++] = png->_data[pos++];
			}
		}
	}
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
	png->_data_size = png->dim.v[0] * png->dim.v[1] *
		png->pxsize + png->dim.v[1];
	if ((png->_codes = (int*)ft_memalloc(sizeof(t_uint) *
					png->_data_size)) == NULL)
		return (-666);
	if ((png->_data = (t_uchar*)ft_memalloc(sizeof(t_uint) *
					png->_data_size)) == NULL)
		return (-666);
	if ((ret = check_flags(png->_zlib_stream)) >= 0)
		if ((ret = parse_deflate(png, png->_zlib_stream + 2)) >= 0)
			if ((ret = expand_length_codes(png)) >= 0)
				ret = checksum(png->_data, png->_data_size,
						png->_zlib_stream + png->_zlib_len - 4);
	free(png->_codes);
	png->_codes = NULL;
	return (ret);
}
