/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maskedduck <maskedduck@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:40:43 by maskedduck        #+#    #+#             */
/*   Updated: 2022/03/28 15:40:44 by maskedduck       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

t_point	add(t_point a, t_point b)
{
	return ((t_point){a.x + b.x, a.y + b.y});
}

t_point	mult(float m, t_point p)
{
	return ((t_point){p.x * m, p.y * m});
}

char	**error_map(char **map, int i)
{
	while (i)
		free(map[i--]);
	free(map);
	return (NULL);
}
