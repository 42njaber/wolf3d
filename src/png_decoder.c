/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_decoder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <njaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 11:01:29 by njaber            #+#    #+#             */
/*   Updated: 2018/09/04 22:10:41 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** Error codes:
** -1: Wrong block order
** -2: Wrong block length
** -3: Unexpected EOF
** -4: Unhandled critical data
** -5: Wrong parameter
** -10: Incorrect checksum
** -66: Malloc error?
** -666: Malloc error
*/

static int		mbytes(int fd)
{
	uchar	bytes[8];

	if (read(fd, bytes, 8) != 8)
		return (0);
	if (bytes[0] != 137 ||
		bytes[1] != 80 ||
		bytes[2] != 78 ||
		bytes[3] != 71 ||
		bytes[4] != 13 ||
		bytes[5] != 10 ||
		bytes[6] != 26 ||
		bytes[7] != 10)
		return (-1);
	return (0);
}

static int		parse_block(int fd, t_png *png)
{
	ft_printf("Chunk type: %4.4s\nSize: %u\n",
			png->_block_type, png->_block_len);
	if (*(uint*)png->_block_type == 0x52444849)
		return (parse_ihdr(fd, png));
	else if (*(uint*)png->_block_type == 0x73594870)
		return (parse_phys(fd, png));
	else if (*(uint*)png->_block_type == 0x54414449)
		return (parse_idat(fd, png));
	else if (*(uint*)png->_block_type == 0x444E4549)
		return (parse_iend(fd, png));
	else
		return (parse_unkown(fd, png));
}

static int		decode_blocks(int fd, t_png *png)
{
	uchar	buf[4];
	int		i;
	int		ret;

	i = 0;
	while (++i)
	{
		if (read(fd, buf, 4) != 4)
			return (0);
		png->_block_len = (buf[0] << 12) | (buf[1] << 8) |
			(buf[2] << 4) | buf[3];
		if (read(fd, png->_block_type, 4) != 4)
			return (-2);
		ret = parse_block(fd, png);
		if (ret < 0)
			return (ret);
		else if (ret == 1)
			 break ;
	}
	return (0);
}

int				destroy_png(t_png **png)
{
	if ((*png)->_zlib_stream != NULL)
		free((*png)->_zlib_stream);
	if ((*png)->_codes != NULL)
		free((*png)->_codes);
	if ((*png)->_data != NULL)
		free((*png)->_data);
	free(*png);
	*png = NULL;
	return (1);
}

t_png			*decode_png(void *mlx, char *path)
{
	t_png	*ret;
	int		fd;
	int		tmp;

	if ((fd = open(path, O_RDONLY)) < 0)
		return (NULL);
	ft_printf("Decoding: %s\n", path);
	if (mbytes(fd) != 0)
		return (NULL);
	if ((ret = (t_png*)ft_memalloc(sizeof(t_png))) == NULL)
		ft_error("Malloc error\n");
	ret->dim = ivec(100, 100);
	tmp = decode_blocks(fd, ret);
	close(fd);
	if (tmp < 0)
	{
		destroy_png(&ret);
		ft_printf("%<#FFAA00>[PNG parser]%<0> Error code: %d\n", tmp);
		return (NULL);
	}
	init_new_image(mlx, &ret->img, ret->dim);
	for (int i = 0, j = 0; j < ret->dim.v[1]; i = (i + 1) % 
			ret->dim.v[0], j += (i == 0 ? 1 : 0))
		img_px(&ret->img, ret->buf[i + j * ret->dim.v[0]], ivec(i, j));
	return (ret);
}
