/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestela <eestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:40:36 by maskedduck        #+#    #+#             */
/*   Updated: 2022/04/16 13:33:13 by eestela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	init_mast(t_mast *ee)
{
	ee->sp.n.img = NULL;
	ee->sp.s.img = NULL;
	ee->sp.e.img = NULL;
	ee->sp.w.img = NULL;
}

void	init_fct_tab(int (*fct_tab[256])(t_mast *ee, char *line, int i))
{
	int	i;

	i = 0;
	while (i < 256)
		fct_tab[i++] = fct_tab_error;
	fct_tab['S'] = fct_tab_south;
	fct_tab['N'] = fct_tab_north;
	fct_tab['E'] = fct_tab_east;
	fct_tab['W'] = fct_tab_west;
	fct_tab['1'] = fct_tab_map;
	fct_tab['0'] = fct_tab_map;
	fct_tab['F'] = fct_tab_floor;
	fct_tab['C'] = fct_tab_ceiling;
}

int	get_info(t_mast *ee, char *line)
{
	int	i;
	int	(*fct_tab[256])(t_mast *ee, char *line, int i);

	init_mast(ee);
	init_fct_tab(fct_tab);
	i = 0;
	while (i >= 0 && line[i])
	{
		while (line[i] && (line[i] == ' ' || line[i] == '\n'))
			i++;
		if (!line[i])
			break ;
		i = fct_tab[(int)line[i]](ee, line, i);
	}
	free(line);
	return (i);
}

void	init_ee(t_mast *ee)
{
	ee->mv_forw = 0;
	ee->mv_backw = 0;
	ee->mv_left = 0;
	ee->mv_right = 0;
	ee->rot_right = 0;
	ee->rot_left = 0;
	ee->img.img = NULL;
	ee->map = NULL;
	ee->win = NULL;
	ee->sp.n.img = NULL;
	ee->sp.s.img = NULL;
	ee->sp.e.img = NULL;
	ee->sp.w.img = NULL;
	ee->hauteur = HAUTEUR;
	ee->jump = 0;
}

int	parsing(t_mast *ee, char *file)
{
	char	*buff;
	char	*line;
	int		fd;
	int		r;

	init_ee(ee);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	buff = malloc(sizeof(char) * 1025);
	if (!buff)
		return (-26);
	line = ft_strdup("");
	r = read(fd, buff, 1024);
	while (line && r > 0)
	{
		buff[r] = 0;
		line = ft_strjoin_free(line, buff);
		r = read(fd, buff, 1024);
	}
	close(fd);
	free(buff);
	if (!line)
		return (-3);
	line = ft_strjoin_free(line, "\n");
	return (get_info(ee, line));
}
