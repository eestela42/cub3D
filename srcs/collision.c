/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maskedduck <maskedduck@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:40:20 by maskedduck        #+#    #+#             */
/*   Updated: 2022/03/28 15:40:21 by maskedduck       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

t_point	colision_y(t_mast *ee, t_ray ray)
{
	t_point	col;
	int		dir;

	col.y = floor(ee->cam.pos.y);
	dir = -1;
	if (ray.dir.y > 0)
	{
		dir = 1;
		col.y = ceil(ee->cam.pos.y);
	}
	while (ray.dir.y != 0)
	{
		col.x = equation_x(ray, col.y);
		if ((int)floor(col.x) >= ee->height || (int)col.y - (dir == -1)
			>= ee->width || (int)floor(col.x) < 0
			|| (int)col.y - (dir == -1) < 0)
			break ;
		if (ee->map[(int)floor(col.x)][(int)col.y - (dir == -1)] == '1')
			return (col);
		col.y += dir;
	}
	return ((t_point){-1, -1});
}

t_point	colision_x(t_mast *ee, t_ray ray)
{
	t_point	col;
	int		dir;

	col.x = floor(ee->cam.pos.x);
	dir = -1;
	if (ray.dir.x > 0)
	{
		dir = 1;
		col.x = ceil(ee->cam.pos.x);
	}
	while (ray.dir.x != 0)
	{
		col.y = equation_y(ray, col.x);
		if ((int)floor(col.y) >= ee->width || (int)col.x - (dir == -1)
			>= ee->height || (int)floor(col.y) < 0
			|| (int)col.x - (dir == -1) < 0)
			break ;
		if (ee->map[(int)col.x - (dir == -1)][(int)floor(col.y)] == '1')
			return (col);
		col.x += dir;
	}
	return ((t_point){-1, -1});
}

char	find_colision(t_mast *ee, t_ray ray, t_point *col)
{
	t_point	col_x;
	t_point	col_y;

	col_x = colision_x(ee, ray);
	col_y = colision_y(ee, ray);
	if ((col_x.x == -1) || (col_y.y != -1
			&& distance(ray.pos, col_x) > distance(ray.pos, col_y)))
	{
		*col = col_y;
		return ('y');
	}
	*col = col_x;
	return ('x');
}
