/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_tab_sprites2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maskedduck <maskedduck@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:40:25 by maskedduck        #+#    #+#             */
/*   Updated: 2022/03/28 15:40:29 by maskedduck       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	check_rgb(int rgb[3])
{
	int	i;

	i = 0;
	while (i < 3)
		if (rgb[i] < 0 || rgb[i++] > 255)
			return (1);
	return (0);
}

int	fct_tab_floor(t_mast *ee, char *line, int i)
{
	int	x;
	int	y;
	int	floor[3];

	while (++i && line[i] && line[i] == ' ')
		;
	x = 0;
	while (x < 3)
	{
		y = 0;
		floor[x] = ft_atoi(&line[i]);
		while (y++ < 3 && line[i] >= '0' && line[i] <= '9')
			i++;
		if (x < 2 && line[i++] != ',')
			return (-93);
		x++;
	}
	if (check_rgb(floor))
		return (-666);
	ee->floor = create_trgb(0, floor[0], floor[1], floor[2]);
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] != '\n')
		return (-94);
	return (i);
}

int	fct_tab_ceiling(t_mast *ee, char *line, int i)
{
	int	x;
	int	y;
	int	ceil[3];

	while (++i && line[i] && line[i] == ' ')
		;
	x = 0;
	while (x < 3)
	{
		y = 0;
		ceil[x] = ft_atoi(&line[i]);
		while (y++ < 3 && line[i] >= '0' && line[i] <= '9')
			i++;
		if (x < 2 && line[i++] != ',')
			return (-93);
		x++;
	}
	if (check_rgb(ceil))
		return (-666);
	ee->ceil = create_trgb(0, ceil[0], ceil[1], ceil[2]);
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] != '\n')
		return (-94);
	return (i);
}
