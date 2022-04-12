/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestela <eestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:40:32 by maskedduck        #+#    #+#             */
/*   Updated: 2022/04/12 11:11:39 by eestela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	destroy_sprites(t_mast *ee)
{
	if (ee->sp.n.img)
		mlx_destroy_image(ee->mlx, ee->sp.n.img);
	if (ee->sp.s.img)
		mlx_destroy_image(ee->mlx, ee->sp.s.img);
	if (ee->sp.e.img)
		mlx_destroy_image(ee->mlx, ee->sp.e.img);
	if (ee->sp.w.img)
		mlx_destroy_image(ee->mlx, ee->sp.w.img);
}

int	ft_end(t_mast *ee)
{
	int	i;

	i = 0;
	if (!ee)
	{
		printf("ARGUMENTS ERROR\n");
		exit(1);
	}
	if (ee->check != -1024)
		printf("ERROR %i\n", -ee->check);
	if (ee->map)
		while (ee->map[i])
			free(ee->map[i++]);
	if (ee->map)
		free(ee->map);
	destroy_sprites(ee);
	if (ee->win)
		mlx_destroy_window(ee->mlx, ee->win);
	if (ee->img.img)
		mlx_destroy_image(ee->mlx, ee->img.img);
	if (ee->mlx)
		mlx_destroy_display(ee->mlx);
	free(ee->mlx);
	i = 0;
	exit(2);
}

int	ft_strend_is(char *str, char *end)
{
	int	i;
	int	j;

	i = ft_strlen(str) - ft_strlen(end);
	j = 0;
	if (i < 0)
		return (0);
	while (str[i + j])
	{
		if (str[i + j] != end[j])
			return (0);
		j++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_mast	ee;

	if (ac != 2 || !ft_strend_is(av[1], ".cub"))
		ft_end(NULL);
	ee.mlx = mlx_init();
	ee.map = NULL;
	ee.check = parsing(&ee, av[1]);
	if (ee.check != -1024)
		ft_end(&ee);
	ee.win = mlx_new_window(ee.mlx, RESX, RESY, "cub3D");
	ee.img.img = mlx_new_image(ee.mlx, RESX, RESY);
	ee.img.addr = mlx_get_data_addr(ee.img.img,
			&ee.img.bits_per_pixel, &ee.img.line_length, &ee.img.endian);
	mlx_hook(ee.win, ClientMessage, NoEventMask, ft_end, &ee);
	mlx_hook (ee.win, 2, 1L << 0, key_pressed, &ee);
	mlx_loop_hook(ee.mlx, key_action, &ee);
	mlx_hook (ee.win, 3, 1L << 1, key_release, &ee);
	fill_image(&ee.img, &ee.cam, &ee);
	mlx_put_image_to_window(ee.mlx, ee.win, ee.img.img, 0, 0);
	mlx_loop(ee.mlx);
	ft_end(&ee);
}
