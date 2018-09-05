/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_create_huffman_tree.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <njaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 15:53:14 by njaber            #+#    #+#             */
/*   Updated: 2018/09/03 14:34:28 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static t_btree	*place_node(t_btree **tree, ushort pos, uchar bits, short val)
{
	while (bits-- > 0)
	{
		if (*tree == NULL &&
				(*tree = (t_btree*)ft_memalloc(sizeof(t_btree))) == NULL)
			return (NULL);
		(*tree)->val = -1;
		tree = (pos >> bits) & 0x1 ? &(*tree)->b1: &(*tree)->b0;
	}
	if (*tree != NULL ||
			(*tree = (t_btree*)ft_memalloc(sizeof(t_btree))) == NULL)
		return (NULL);
	(*tree)->val = val;
	return (*tree);
}

static t_btree	*place_default_node(t_btree **tree, short val)
{
	t_btree		*ret;

	if (val < 144)
		ret = place_node(tree, 0x30 + val, 8, val);
	else if (val < 256)
		ret = place_node(tree, 0x190 + val - 144, 9, val);
	else if (val < 280)
		ret = place_node(tree, val - 256, 7, val);
	else if (val < 288)
		ret = place_node(tree, 0xC0 + val - 280, 8, val);
	else
		return (NULL);
	return (ret);
}

void			free_tree(t_btree **tree)
{
	if (*tree != NULL)
	{
		free_tree(&(*tree)->b0);
		free_tree(&(*tree)->b1);
		free(*tree);
		*tree = NULL;
	}
}

t_btree			*gen_default_tree(void)
{
	t_btree		*tree;
	short		val;

	val = 0;
	tree = NULL;
	while (val < 288)
		if (place_default_node(&tree, val++) == NULL)
		{
			free_tree(&tree);
			return (NULL);
		}
	return (tree);
}
