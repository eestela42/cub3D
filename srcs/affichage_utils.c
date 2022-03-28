/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichage_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maskedduck <maskedduck@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:40:13 by maskedduck        #+#    #+#             */
/*   Updated: 2022/03/28 15:40:14 by maskedduck       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

int	my_mlx_pixel_get(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int *) dst);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

float	equation_x(t_ray ray, int y)
{
	float	x;

	x = ray.pos.x + ((y - ray.pos.y) / ray.dir.y) * ray.dir.x;
	return (x);
}

float	equation_y(t_ray ray, int x)
{
	float	y;

	y = ray.pos.y + ((x - ray.pos.x) / ray.dir.x) * ray.dir.y;
	return (y);
}
