/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_deflate_code_reader.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <njaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 14:17:43 by njaber            #+#    #+#             */
/*   Updated: 2018/09/04 15:49:48 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static uint			lencode(short val)
{
	uint	len;

	if (val == 285)
		len = 258;
	else
	{
		len = 3 + val - 257
			+ (val < 266 ? 0 : 1 * (val - 265))
			+ (val < 270 ? 0 : 2 * (val - 269))
			+ (val < 274 ? 0 : 4 * (val - 273))
			+ (val < 278 ? 0 : 8 * (val - 277))
			+ (val < 282 ? 0 : 16 * (val - 281));
	}
	return (len);
}

static uint			distcode(short val)
{
	uint	dist;

	if (val > 29)
		return (0);
	dist = 1 + val
		+ (val < 5 ? 0 : 1 * (val - 4))
		+ (val < 7 ? 0 : 2 * (val - 6))
		+ (val < 9 ? 0 : 4 * (val - 8))
		+ (val < 11 ? 0 : 8 * (val - 10))
		+ (val < 13 ? 0 : 16 * (val - 12))
		+ (val < 15 ? 0 : 32 * (val - 14))
		+ (val < 17 ? 0 : 64 * (val - 16))
		+ (val < 19 ? 0 : 128 * (val - 18))
		+ (val < 21 ? 0 : 256 * (val - 20))
		+ (val < 23 ? 0 : 512 * (val - 22))
		+ (val < 25 ? 0 : 1024 * (val - 24))
		+ (val < 27 ? 0 : 2048 * (val - 26))
		+ (val < 29 ? 0 : 4096 * (val - 28));
	return (dist);
}

static int			code_tobuf(t_png *png, short val, uint *pos, uchar *buf)
{
	uint	stockval;
	uint	tmp;

	stockval = 0;
	ft_printf("Val: %02hX | %hd\n", val, val);
	if ((int)png->_codes_pos >= png->dim.v[0] * png->dim.v[1])
		return (-2);
	if (png->_codes_pos != 0 && png->_codes_buf[png->_codes_pos - 1] < 0)
	{
		stockval = distcode(val);
		ft_printf("Dist: %i\n", stockval);
		if (stockval == 0)
			return (-1);
	}
	else if (val > 256 && val < 285)
	{
		stockval = lencode(val);
		if (val > 264)
		{
			if ((int)(*pos + (val - 265) / 4) / 8 >= (int)png->_block_len - 4)
				return (-2);
			tmp = get_next_bits(buf, pos, 1 + (val - 265) / 4);
			ft_printf("%0*b\n", 1 + (val - 265) / 4, tmp);
			stockval +=tmp;
		}
		ft_printf("Len: %i\n", stockval);
		stockval = -stockval;
	}
	else
		stockval = val;
	png->_codes_buf[png->_codes_pos++] = stockval;
	return (0);
}

int					read_codes(t_png *png, uchar *buf, t_btree *tree)
{
	t_btree		*current;
	uint		pos;
	int			ret;

	current = tree;
	pos = 20;
	while (1)
	{
		if (current->val != -1)
		{
			ft_printf("\n", pos);
			if ((ret = code_tobuf(png, current->val, &pos, buf)) < 0)
				return (ret);
			if (current->val == 256)
				break ;
			ft_printf("Pos: %u\n", pos);
			current = tree;
		}
		else if (pos / 8 >= png->_block_len - 4)
			return (-2);
		else if (get_next_bits(buf, &pos, 1))
		{
			current = current->b1;
			ft_printf("1");
		}
		else
		{
			current = current->b0;
			ft_printf("0");
		}
	}
	return (0);
}

