/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_decoder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <njaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 11:01:29 by njaber            #+#    #+#             */
/*   Updated: 2018/08/20 13:07:43 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_img			*decode_png(void *mlx, char *path)
{
	t_img	*ret;
	int		fd;

	if ((fd = open(path, O_RDONLY)) < 0)
		return (NULL);
	close(fd);
	ft_printf("Decoding: %s\n", path);
	if ((ret = (t_img*)ft_memalloc(sizeof(t_img))) == NULL)
		ft_error("Malloc error\n");
	init_new_image(mlx, ret, ivec(100, 100));
	return (ret);
}
