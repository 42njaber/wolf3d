/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_decoder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <njaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 11:01:29 by njaber            #+#    #+#             */
/*   Updated: 2018/09/15 17:46:09 by njaber           ###   ########.fr       */
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
** -6: Unkown error
** -7: Wrong lens for huffman tree
** -10: Incorrect checksum
** -666: Malloc error
*/

static int		mbytes(int fd)
{
	t_uchar	bytes[8];

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
	if (*(t_uint*)png->_block_type == 0x52444849)
		return (parse_ihdr(fd, png));
	else if (*(t_uint*)png->_block_type == 0x73594870)
		return (parse_phys(fd, png));
	else if (*(t_uint*)png->_block_type == 0x54414449)
		return (parse_idat(fd, png));
	else if (*(t_uint*)png->_block_type == 0x444E4549)
		return (parse_iend(fd, png));
	else
		return (parse_unkown(fd, png));
}

static int		decode_blocks(int fd, t_png *png)
{
	t_uchar	buf[4];
	int		i;
	int		ret;

	i = 0;
	while (++i)
	{
		if (read(fd, buf, 4) != 4)
			return (0);
		png->_block_len = (buf[0] << 24) | (buf[1] << 16) |
			(buf[2] << 8) | buf[3];
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
	if ((*png)->buf != NULL)
		free((*png)->buf);
	if ((*png)->ltree != NULL)
		free_tree(&(*png)->ltree);
	if ((*png)->dtree != NULL)
		free_tree(&(*png)->dtree);
	if ((*png)->cltree != NULL)
		free_tree(&(*png)->cltree);
	free(*png);
	*png = NULL;
	return (1);
}

t_png			*decode_png(char *path)
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
		ft_printf("%<#FFAA00>[PNG parser]%<0> Error code: %d\n", tmp);
		destroy_png(&ret);
		return (NULL);
	}
	return (ret);
}
