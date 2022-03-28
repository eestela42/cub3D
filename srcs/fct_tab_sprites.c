/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_tab_sprites.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maskedduck <maskedduck@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:40:22 by maskedduck        #+#    #+#             */
/*   Updated: 2022/03/28 15:40:23 by maskedduck       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	xpm_to_image(void *mlx_ptr, char *line, int i, t_data *sprite)
{
	int			start;
	int			end;
	char		*path;

	if (sprite->img)
		return (-5);
	start = i;
	while (line[i] != ' ' && line[i] != '\n')
		i++;
	end = i;
	while (line[i] && line[i] != '\n')
		if (line[i++] != ' ')
			return (-2);
	path = ft_substr(line, start, end - start);
	if (!path)
		return (-1);
	sprite->img = mlx_xpm_file_to_image(mlx_ptr, path,
			&sprite->width, &sprite->height);
	if (sprite->img)
		sprite->addr = mlx_get_data_addr(sprite->img, &sprite->bits_per_pixel,
				&sprite->line_length, &sprite->endian);
	free(path);
	if (!sprite->img || !sprite->addr)
		return (-13);
	return (i);
}

int	fct_tab_north(t_mast *ee, char *line, int i)
{
	if (line[++i] != 'O' || ee->sp.n.img)
		return (-150);
	i += 1;
	while (line[i] == ' ')
		i++;
	return (xpm_to_image(ee->mlx, line, i, &ee->sp.n));
}

int	fct_tab_south(t_mast *ee, char *line, int i)
{
	if (line[++i] != 'O' || ee->sp.s.img)
		return (-1);
	i += 1;
	while (line[i] == ' ')
		i++;
	return (xpm_to_image(ee->mlx, line, i, &ee->sp.s));
}

int	fct_tab_east(t_mast *ee, char *line, int i)
{
	if (line[++i] != 'A' || ee->sp.e.img)
		return (-1);
	i += 1;
	while (line[i] == ' ')
		i++;
	return (xpm_to_image(ee->mlx, line, i, &ee->sp.e));
}

int	fct_tab_west(t_mast *ee, char *line, int i)
{
	if (line[++i] != 'E' || ee->sp.w.img)
		return (-1);
	i += 1;
	while (line[i] == ' ')
		i++;
	return (xpm_to_image(ee->mlx, line, i, &ee->sp.w));
}
