/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:40:30 by maskedduck        #+#    #+#             */
/*   Updated: 2022/03/28 19:05:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	key_release(int key, t_mast *ee)
{
	if (key == FORWARD_W_Z)
		ee->mv_forw = 0;
	if (key == BACK_S_S)
		ee->mv_backw = 0;
	if (key == RIGHT_D_D)
		ee->mv_right = 0;
	if (key == LEFT_A_Q)
		ee->mv_left = 0;
	if (key == ROTATE_LEFT)
		ee->rot_left = 0;
	if (key == ROTATE_RIGHT)
		ee->rot_right = 0;
	return (0);
}

int	key_pressed(int key, t_mast *ee)
{
	if (key == ROTATE_LEFT)
		ee->rot_left = 1;
	if (key == ROTATE_RIGHT)
		ee->rot_right = 1;
	if (key == 32 && ee->jump == 0)
		ee->jump = 1;
	if (key == 65307)
		ft_end(ee);
	if (key == FORWARD_W_Z)
		ee->mv_forw = 1;
	if (key == BACK_S_S)
		ee->mv_backw = 1;
	if (key == RIGHT_D_D)
		ee->mv_right = 1;
	if (key == LEFT_A_Q)
		ee->mv_left = 1;
	return (0);
}

int	not_in_a_wall(char **map, t_point pos, t_mast *ee)
{
	if (map[(int)floor(ee->cam.pos.x)][(int)floor(pos.y)] == '1'
		&& map[(int)floor(ee->cam.pos.x)][(int)floor(ee->cam.pos.y)] == '1')
		return (0);
	if (map[(int)floor(pos.x)][(int)floor(pos.y)] == '0')
		return (1);
	return (0);
}

void	jump(t_mast *ee)
{
	if (ee->jump > 0.5)
	{
		ee->hauteur -= 0.2;
		ee->jump -= 0.1;
	}
	else
	{
		ee->hauteur += 0.1;
		ee->jump -= 0.05;
	}
	if (ee->jump < 0)
	{
		ee->jump = 0;
		ee->hauteur = HAUTEUR;
	}
}

int	key_action(t_mast *ee)
{
	t_point	dir;
	t_point	ortho;

	dir = (t_point){cos(ee->cam.angle), sin(ee->cam.angle)};
	ortho = (t_point){dir.y, -dir.x};
	if (ee->jump > 0)
		jump(ee);
	if (ee->mv_forw == 1 && not_in_a_wall(ee->map,
			add(ee->cam.pos, mult(0.33, dir)), ee))
		ee->cam.pos = add(ee->cam.pos, mult(foot_velocity, dir));
	if (ee->mv_backw == 1 && not_in_a_wall(ee->map,
			add(ee->cam.pos, mult(-0.33, dir)), ee))
		ee->cam.pos = add(ee->cam.pos, mult(-foot_velocity, dir));
	if (ee->mv_right == 1 && not_in_a_wall(ee->map,
			add(ee->cam.pos, mult(0.33, ortho)), ee))
		ee->cam.pos = add(ee->cam.pos, mult(foot_velocity, ortho));
	if (ee->mv_left == 1 && not_in_a_wall(ee->map,
			add(ee->cam.pos, mult(-0.33, ortho)), ee))
		ee->cam.pos = add(ee->cam.pos, mult(-foot_velocity, ortho));
	if (ee->rot_left == 1)
		ee->cam.angle += (neck_velocity + 0.15) * M_PI / 180;
	if (ee->rot_right == 1)
		ee->cam.angle -= neck_velocity * M_PI / 180;
	fill_image(&ee->img, &ee->cam, ee);
	ee->mem_img = ee->img;
	mlx_put_image_to_window(ee->mlx, ee->win, ee->mem_img.img, 0, 0);
	return (1);
}
