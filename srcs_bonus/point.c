/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maskedduck <maskedduck@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:40:39 by maskedduck        #+#    #+#             */
/*   Updated: 2022/03/28 15:40:40 by maskedduck       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

float	norm(t_point a)
{
	return (sqrt(a.x * a.x + a.y * a.y));
}

float	distance(t_point a, t_point b)
{
	return (norm(diff(a, b)));
}

t_point	normalize(t_point a)
{
	if (!norm(a))
		return (a);
	return (mult(1 / norm(a), a));
}

float	dot(t_point a, t_point b)
{
	return (a.x * b.x + a.y * b.y);
}

t_point	diff(t_point a, t_point b)
{
	return ((t_point){a.x - b.x, a.y - b.y});
}
