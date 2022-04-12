/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestela <eestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:40:30 by maskedduck        #+#    #+#             */
/*   Updated: 2022/04/12 11:31:58 by eestela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	not_out_of_map(char **map, t_point pos, t_mast *ee)
{
	(void)map;
	if (((int)floor(pos.x) < ee->height - 1 && (int)floor(pos.x) > 0)
		&& ((int)floor(pos.y) < ee->width - 1 && (int)floor(pos.y) > 0))
		return (1);
	return (0);
}

void	jump(t_mast *ee)
{
	if (ee->jump > 0.5)
	{
		ee->hauteur -= JUMP_HEIGHT / 10;
		ee->jump -= 0.1;
	}
	else
	{
		ee->hauteur += JUMP_HEIGHT / 20;
		ee->jump -= 0.05;
	}
	if (ee->jump < 0)
	{
		ee->jump = 0;
		ee->hauteur = HAUTEUR;
	}
}

void	action(t_mast *ee, t_point dir, t_point ortho)
{
	if (ee->jump > 0)
		jump(ee);
	if (ee->mv_forw == 1 && not_out_of_map(ee->map,
			add(ee->cam.pos, mult(0.33, dir)), ee))
		ee->cam.pos = add(ee->cam.pos, mult(foot_velocity, dir));
	if (ee->mv_backw == 1 && not_out_of_map(ee->map,
			add(ee->cam.pos, mult(-0.33, dir)), ee))
		ee->cam.pos = add(ee->cam.pos, mult(-foot_velocity, dir));
	if (ee->mv_right == 1 && not_out_of_map(ee->map,
			add(ee->cam.pos, mult(0.33, ortho)), ee))
		ee->cam.pos = add(ee->cam.pos, mult(foot_velocity, ortho));
	if (ee->mv_left == 1 && not_out_of_map(ee->map,
			add(ee->cam.pos, mult(-0.33, ortho)), ee))
		ee->cam.pos = add(ee->cam.pos, mult(-foot_velocity, ortho));
	if (ee->rot_left == 1)
		ee->cam.angle += (neck_velocity + 0.15) * M_PI / 180;
	if (ee->rot_right == 1)
		ee->cam.angle -= neck_velocity * M_PI / 180;
}

int	key_action(t_mast *ee)
{
	t_point	dir;
	t_point	ortho;

	dir = (t_point){cos(ee->cam.angle), sin(ee->cam.angle)};
	ortho = (t_point){dir.y, -dir.x};
	action(ee, dir, ortho);
	fill_image(&ee->img, &ee->cam, ee);
	ee->mem_img = ee->img;
	mlx_put_image_to_window(ee->mlx, ee->win, ee->mem_img.img, 0, 0);
	return (1);
}
