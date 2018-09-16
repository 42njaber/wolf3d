/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_parse_deflate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <njaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 15:53:14 by njaber            #+#    #+#             */
/*   Updated: 2018/09/15 23:23:32 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		copy_noncompressed_data(t_png *png, t_uchar *stream, t_uint *pos)
{
	t_uint		byte;
	t_ushort	len;
	t_ushort	nlen;

	byte = (*pos + 7) / 8;
	len = (stream[byte + 1] << 8) + stream[byte];
	nlen = (stream[byte + 3] << 8) + stream[byte + 2];
	if ((~len & 0xFFFF) != nlen)
		return (-10);
	byte += 4;
	while (len-- > 0)
	{
		if (png->_codes_len >= png->_data_size)
			return (-2);
		png->_codes[png->_codes_len] = stream[byte++];
		png->_codes_len++;
	}
	*pos = byte * 8;
	return (0);
}

int				decompress_block(t_png *png, t_uchar *stream, t_uint *pos)
{
	int		ret;
	t_uchar	header;

	if ((*pos + 1) / 8 >= png->_zlib_len - 6)
		return (-2);
	header = get_next_bits(stream, pos, 2);
	ret = 0;
	if (header == 0)
		ret = copy_noncompressed_data(png, stream, pos);
	else if (header == 3)
		return (-4);
	else
	{
		if (header == 2)
		{
			if ((ret = read_tree(png, stream, pos)) < 0)
				return (ret);
		}
		else if ((ret = gen_default_tree(png)) < 0)
			return (ret);
		ret = read_codes(png, stream, pos);
	}
	free_tree(&png->ltree);
	free_tree(&png->dtree);
	free_tree(&png->cltree);
	return (ret);
}
