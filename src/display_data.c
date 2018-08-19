/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 12:10:10 by njaber            #+#    #+#             */
/*   Updated: 2018/08/19 10:53:27 by cdittric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "mlx.h"

void	display_data_scal(t_win *win, char *name, t_scal data, int y)
{
	char	*tmp;

	tmp = ft_printb("%s %.3g", name, data);
	if (tmp == NULL)
		ft_error("[Error] display_data_scal: Failed allocation.\n");
	mlx_string_put(win->mlx, win->win, 10, y, 0x777777, tmp);
	free(tmp);
}

void	display_data_vec2(t_win *win, char *name, t_vec2 data, int y)
{
	char	*tmp;

	tmp = ft_printb("%s %g, %g", name, data.v[0], data.v[1]);
	if (tmp == NULL)
		ft_error("[Error] display_data_vec2: Failed allocation.\n");
	mlx_string_put(win->mlx, win->win, 10, y, 0x777777, tmp);
	free(tmp);
}

void	display_data_vec3(t_win *win, char *name, t_vec3 data, int y)
{
	char	*tmp;

	tmp = ft_printb("%s %g, %g, %g", name, data.v[0], data.v[1], data.v[2]);
	if (tmp == NULL)
		ft_error("[Error] display_data_vec3: Failed allocation.\n");
	mlx_string_put(win->mlx, win->win, 10, y, 0x777777, tmp);
	free(tmp);
}

void	display_data_str(t_win *win, char *name, char *data, int y)
{
	char	*tmp;

	tmp = ft_printb("%s %s", name, data);
	if (tmp == NULL)
		ft_error("[Error] display_data_str: Failed allocation.\n");
	mlx_string_put(win->mlx, win->win, 10, y, 0x777777, tmp);
	free(tmp);
}
