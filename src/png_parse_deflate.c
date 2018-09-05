/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_parse_deflate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <njaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 15:53:14 by njaber            #+#    #+#             */
/*   Updated: 2018/09/04 21:42:31 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		copy_noncompressed_data(t_png *png, uchar *stream, uint *pos)
{
	uint	byte;
	ushort	len;
	ushort	nlen;

	byte = *pos / 8 + 1;
	len = (stream[byte + 1] << 8) + stream[byte];
	nlen = (stream[byte + 3] << 8) + stream[byte + 2];
	if ((~len & 0xFFFF) != nlen)
		return (-10);
	ft_printf("Uncompressed data len: %hu\n", len);
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

int				decompress_block(t_png *png, uchar *stream, uint *pos)
{
	t_btree	*tree;
	int		ret;
	uchar	header;

	if ((*pos + 1) / 8 >= png->_zlib_len - 6)
		return (-2);
	header = get_next_bits(stream, pos, 1);
	ret = 0;
	if ((header >> 1) == 0)
		ret = copy_noncompressed_data(png, stream, pos);
	else if ((header >> 1) == 0x1)
	{
		if ((tree = gen_default_tree()) == NULL)
			return (-66);
		//ret = read_codes(png, stream, tree);
		free_tree(&tree);
	}
	else
		return (-4);
	return (ret);
}
