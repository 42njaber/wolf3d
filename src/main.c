/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 17:01:19 by njaber            #+#    #+#             */
/*   Updated: 2018/08/18 14:11:56 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "wolf.h"
#include "mlx.h"
#include "gnl.h"

static void		launch_window(t_ptr *p)
{
	if ((init_new_win(p->mlx, p->win, (t_ivec){1200, 800}, "Wolf3D")) == 0)
		ft_error("[Erreur] Failed to initialize window\n");
	set_hooks(p);
	mlx_loop(p->mlx);
}

static void		read_map_line(t_ptr *p, char *line, int y)
{
	int		i;
	char	*tmp;

	if ((p->map[y] = (int*)ft_memalloc(sizeof(int) * p->mdim.x)) == NULL)
		ft_error("Malloc error\n");
	i = -1;
	tmp = line;
	while (++i < p->mdim.x)
	{
		p->map[y][i] = ft_atoi(tmp);
		tmp = ft_strchr(tmp, ',');
		if (i < p->mdim.x - 1 && tmp == NULL)
			ft_error("Error while reading file: "
					"not enough numbers on line %i\n", y);
		if (i == p->mdim.x - 1 && tmp != NULL)
			ft_error("Error while reading file: "
					"too many numbers on line %i\n", y);
		tmp++;
	}
}

static void		read_map(t_ptr *p, int fd)
{
	int		i;
	int		ret;
	char	*line;

	if ((ret = get_next_line(fd, &line)) != 1 || ft_strchr(line, ',') == NULL)
		ft_error("Error while reading file (line: %d)\n", line);
	p->mdim.x = ft_atoi(line);
	p->mdim.y = ft_atoi(ft_strchr(line, ',') + 1);
	free(line);
	if ((p->map = (int**)ft_memalloc(sizeof(int*) * p->mdim.y)) == NULL)
		ft_error("Malloc error\n");
	i = -1;
	while (++i < p->mdim.y)
	{
		if (get_next_line(fd, &line) !=  1)
			ft_error("Error while reading file: not enough lines\n");
		read_map_line(p, line, i);
		free(line);
	}
}

int				main(int argc, char **argv)
{
	t_ptr	p;
	int		fd;

	if (argc != 2)
		ft_error("You need to give a single map file as argument\n");
	ft_bzero(&p, sizeof(p));
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		ft_error("Could not read file\n");
	read_map(&p, fd);
	close(fd);
	if ((p.mlx = mlx_init()) == 0)
		ft_error("[Error] Failed to initialize mlx\n");
	init_struct(&p);
	launch_window(&p);
}
