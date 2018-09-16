/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_block_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <njaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 14:19:30 by njaber            #+#    #+#             */
/*   Updated: 2018/09/15 23:21:18 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		parse_ihdr(int fd, t_png *png)
{
	t_uchar	buf[13];

	if (png->init)
		return (-1);
	png->init = 1;
	if (png->_block_len != 13)
		return (-2);
	if (read(fd, buf, 13) != 13)
		return (-3);
	png->dim.v[0] = (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];
	png->dim.v[1] = (buf[4] << 24) | (buf[5] << 16) | (buf[6] << 8) | buf[7];
	png->bdepth = buf[8];
	png->ctype = buf[9];
	png->compression = buf[10];
	png->filter = buf[11];
	png->interlace = buf[12];
	if (png->bdepth != 8 || !(png->ctype == 2 || png->ctype == 6) ||
			png->compression != 0 || png->filter != 0 || png->interlace != 0)
		return (-4);
	png->pxsize = png->ctype == 2 ? 3 : 4;
	ft_printf("Image size: %d, %d\nBit depth: %hu\nColortype: %hu\nCompression "
			"methode: %hu\nFilter methode: %hu\nInterlace method: %hu\n",
			png->dim.v[0], png->dim.v[1], png->bdepth, png->ctype,
			png->compression, png->filter, png->interlace);
	return (validate_crc(fd, buf, png));
}

int		parse_phys(int fd, t_png *png)
{
	t_uchar	buf[9];

	if (!png->init || png->_zlib_stream != NULL)
		return (-1);
	if (png->_block_len != 9)
		return (-2);
	if (read(fd, buf, 9) != 9)
		return (-3);
	png->aratio.v[0] = (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];
	png->aratio.v[1] = (buf[4] << 24) | (buf[5] << 16) | (buf[6] << 8) | buf[7];
	png->aunit = buf[8];
	return (validate_crc(fd, buf, png));
}

int		parse_idat(int fd, t_png *png)
{
	t_uchar	*buf;
	int		ret;

	if (!png->init)
		return (-1);
	if ((buf = (t_uchar*)ft_memalloc(sizeof(t_uchar) * (png->_block_len +
						png->_zlib_len))) == NULL && destroy_png(&png))
		return (-666);
	if (png->_zlib_stream != NULL)
	{
		ft_memcpy(buf, png->_zlib_stream, png->_zlib_len);
		free(png->_zlib_stream);
		png->_zlib_stream = NULL;
	}
	if (read(fd, buf + png->_zlib_len, png->_block_len) != png->_block_len)
	{
		free(buf);
		return (-3);
	}
	ret = validate_crc(fd, buf + png->_zlib_len, png);
	png->_zlib_stream = buf;
	png->_zlib_len += png->_block_len;
	return (ret);
}

int		parse_iend(int fd, t_png *png)
{
	int		ret;

	if (!png->init || png->_zlib_stream == NULL)
		return (-1);
	if (png->_block_len != 0)
		return (-2);
	if ((png->buf = (t_uint*)ft_memalloc(sizeof(t_uint) *
					png->dim.v[0] * png->dim.v[1])) == NULL)
		return (-666);
	if ((ret = parse_zlib(png)) >= 0)
		if ((ret = recompose_image(png)) >= 0)
			ret = validate_crc(fd, NULL, png);
	free(png->_zlib_stream);
	png->_zlib_stream = NULL;
	free(png->_data);
	png->_data = NULL;
	if (ret < 0)
		return (ret);
	return (1);
}

int		parse_unkown(int fd, t_png *png)
{
	t_uchar	*buf;
	int		ret;

	if ((png->_block_type[0] & 0x20) == 0)
		return (-4);
	if (!png->init)
		return (-1);
	if ((buf = (t_uchar*)ft_memalloc(sizeof(char) * png->_block_len)) == NULL)
		return (-666);
	if (read(fd, buf, png->_block_len) != png->_block_len)
	{
		free(buf);
		return (-3);
	}
	ret = validate_crc(fd, buf, png);
	free(buf);
	return (ret);
}
