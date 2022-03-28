/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maskedduck <maskedduck@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:40:35 by maskedduck        #+#    #+#             */
/*   Updated: 2022/03/28 15:40:35 by maskedduck       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	check_space(char **map, int x, int y)
{
	if (x != 0 && map[x - 1][y] == '0')
		return (1);
	if (map[x + 1] && map[x + 1][y] == '0')
		return (1);
	if (y != 0 && map[x][y - 1] == '0')
		return (1);
	if (map[x][y + 1] && map[x][y + 1] == '0')
		return (1);
	return (0);
}

int	check_border(char **map, int height, int width)
{
	int	i;

	i = -1;
	while (++i < height)
		if (map[i][0] != ' ' && map[i][0] != '1')
			return (1);
	i = -1;
	while (++i < width)
		if (map[0][i] != ' ' && map[0][i] != '1')
			return (1);
	i = -1;
	while (++i < height)
		if (map[i][width - 1] != ' ' && map[i][width - 1] != '1')
			return (1);
	i = -1;
	while (++i < width)
		if (map[height - 1][i] != ' ' && map[height - 1][i] != '1')
			return (1);
	return (0);
}

int	char_in_map(t_mast *ee, int x, int y)
{
	char	c;

	c = ee->map[x][y];
	if (ee->cam.pos.x != -1)
		return (1);
	if (c != 'N' && c != 'E' && c != 'W' && c != 'S')
		return (1);
	ee->map[x][y] = '0';
	ee->cam.pos.x = x + 0.5;
	ee->cam.pos.y = y + 0.5;
	if (c == 'E')
		ee->cam.angle = 0.5 * M_PI;
	if (c == 'W')
		ee->cam.angle = 1.5 * M_PI;
	if (c == 'N')
		ee->cam.angle = 1 * M_PI;
	if (c == 'S')
		ee->cam.angle = 0;
	return (0);
}

int	parse_map(t_mast *ee, int x, int y)
{
	x = 0;
	while (ee->map[x])
	{
		y = 0;
		while (ee->map[x][y])
		{
			if (ee->map[x][y] == ' ')
			{
				if (check_space(ee->map, x, y))
					return (-47);
			}
			else if (ee->map[x][y] == '1' || ee->map[x][y] == '0')
				;
			else if (char_in_map(ee, x, y))
				return (-36);
			y++;
		}
		x++;
	}
	return (1);
}

int	error_in_map(t_mast *ee, int height, int width)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	ee->cam.pos.x = -1;
	ee->cam.pos.y = -1;
	if (check_border(ee->map, height, width))
		return (-75);
	if (!parse_map(ee, x, y))
		return (-47);
	if (ee->cam.pos.y == -1)
		return (-89);
	return (-1024);
}
