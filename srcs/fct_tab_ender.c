/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_tab_ender.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maskedduck <maskedduck@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:40:17 by maskedduck        #+#    #+#             */
/*   Updated: 2022/03/28 15:40:18 by maskedduck       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	fct_tab_error(t_mast *ee, char *line, int i)
{
	(void)ee;
	(void)line;
	(void)i;
	return (-190);
}

int	fct_tab_map(t_mast *ee, char *line, int i)
{
	if (line[i] == '0')
		return (-96);
	if (ee->sp.n.img && ee->sp.s.img && ee->sp.e.img && ee->sp.w.img)
		printf("All sprites good \n");
	else
		return (-205);
	return (parsing_map(ee, line, i));
}
