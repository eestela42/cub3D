/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:40:10 by maskedduck        #+#    #+#             */
/*   Updated: 2022/03/28 18:46:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

t_data	texture_offset(t_mast *ee, t_pix_column column, float *offset)
{
	t_data	texture;

	if (column.finder == 'x')
	{
		if (column.ray_dir.x > 0)
			texture = ee->sp.n;
		else
			texture = ee->sp.s;
		*offset = column.col.y - floor(column.col.y);
		if (column.ray_dir.x > 0)
			*offset = 1 - *offset;
	}
	else
	{
		if (column.ray_dir.y > 0)
			texture = ee->sp.w;
		else
			texture = ee->sp.e;
		*offset = column.col.x - floor(column.col.x);
		if (column.ray_dir.y <= 0)
			*offset = 1 - *offset;
	}
	return (texture);
}

int	color_pix(t_mast *ee, float zone, t_pix_column column)
{
	t_data	texture;
	float	offset;
	int		i;
	int		j;

	texture = texture_offset(ee, column, &offset);
	i = ((zone + 1) / 2) * texture.height;
	j = offset * texture.width;
	return (my_mlx_pixel_get(&texture, j, i));
}

int	fill_column(t_mast *ee, t_pix_column column)
{
	int		y;
	float	zone;
	float	coef_fov;

	coef_fov = tan(FOV / 2) * ((float) RESY / RESX) * 2;
	y = 0;
	while (y < RESY)
	{
		zone = (y - (float) RESY / 2) / (RESY / 2) * coef_fov * column.dist;
		if (zone > 1 - ee->hauteur)
			my_mlx_pixel_put(&ee->img, column.x, y, ee->floor);
		else if (zone < -1 - ee->hauteur)
			my_mlx_pixel_put(&ee->img, column.x, y, ee->ceil);
		else
			my_mlx_pixel_put(&ee->img, column.x, y,
				color_pix(ee, zone + ee->hauteur, column));
		y++;
	}
	return (0);
}

float	projection(t_cam *cam, t_point col)
{
	t_point	ret;
	t_point	dir;

	ret = diff(col, cam->pos);
	dir = (t_point){cos(cam->angle), sin(cam->angle)};
	return (fabs(dot(ret, dir)));
}

int	fill_image(t_data *img, t_cam *cam, t_mast *ee)
{
	t_ray			ray;
	t_point			ortho;
	t_pix_column	column;
	float			coef_fov;

	(void) img;
	column.x = 0;
	coef_fov = tan(FOV / 2);
	ray.pos = (t_point){cam->pos.x, cam->pos.y};
	ray.dir = (t_point){cos(cam->angle), sin(cam->angle)};
	ortho = (t_point){ray.dir.y, -ray.dir.x};
	while (column.x < RESX)
	{
		ray.dir = (t_point){cos(cam->angle), sin(cam->angle)};
		ray.dir = normalize(add(ray.dir, mult(coef_fov
						* (column.x - RESX / 2.0f) / (RESX / 2.0f), ortho)));
		column.finder = find_colision(ee, ray, &column.col);
		column.dist = projection(cam, column.col);
		column.ray_dir = ray.dir;
		fill_column(ee, column);
		column.x++;
	}
	return (0);
}
