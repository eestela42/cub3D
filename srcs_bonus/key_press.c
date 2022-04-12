/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestela <eestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 11:29:39 by eestela           #+#    #+#             */
/*   Updated: 2022/04/12 11:29:41 by eestela          ###   ########.fr       */
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
