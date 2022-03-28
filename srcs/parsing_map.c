/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:40:34 by maskedduck        #+#    #+#             */
/*   Updated: 2022/03/28 19:00:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	line_in_map(char *line, int i)
{
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == '1')
			return (1);
		i++;
	}
	return (0);
}

int	map_height(char *line, int i)
{
	int	height;
	int	in_map;

	height = 0;
	in_map = 1;
	while (line[i])
	{
		if (line_in_map(line, i))
		{
			if (in_map == -1)
				return (-63);
			in_map = 1;
		}
		else if (line[i] == '\n' && in_map == 1)
		{
			height++;
			in_map = 0;
		}
		else if (line[i] == '\n')
			in_map = -1;
		else if (line[i] != ' ')
			return (-63);
		i++;
	}
	if (in_map == 1)
		height++;
	return (height);
}

int	map_width(char *line, int height, int i)
{
	int	width;
	int	w_line;

	width = 0;
	while (line[i] && height)
	{
		w_line = 0;
		while (line[i] && line[i] != '\n')
		{
			i++;
			w_line++;
		}
		if (w_line > width)
			width = w_line;
		i++;
		height--;
	}
	return (width);
}

char	**make_map(char *line, int start, int height, int width)
{
	char	**map;
	int		i;
	int		y;

	map = malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	map[height] = NULL;
	i = 0;
	while (i < height)
	{
		map[i] = malloc(sizeof(char) * (width + 1));
		if (!map[i])
			return (error_map(map, i));
		y = 0;
		while (line[start] && line[start] != '\n')
			map[i][y++] = line[start++];
		start++;
		while (y < width)
			map[i][y++] = ' ';
		map[i][y] = 0;
		i++;
	}
	return (map);
}

int	parsing_map(t_mast *ee, char *line, int i)
{
	int	start;

	while (i >= 0 && line[i] != '\n')
		i--;
	start = ++i;
	ee->height = map_height(line, start);
	if (ee->height <= 0)
		return (-63);
	ee->width = map_width(line, ee->height, start);
	ee->map = make_map(line, start, ee->height, ee->width);
	return (error_in_map(ee, ee->height, ee->width));
}
