/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:40:32 by maskedduck        #+#    #+#             */
/*   Updated: 2022/04/13 17:47:00 by user42           ###   ########.fr       */
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

char	*ft_error_message2(int check)
{
	if (check == 666)
		return("Wrong rgb values\n");
	if (check == 2)
		return("Invalid char after informations in 'map'.cub\n");
	if (check == 142)
		return("Malloc failed in xpm_to_image\n");
	if (check == 13)
		return("Function xpm_to_image failed\n");
	if (check == 94)
		return("Invalid char after rgb value in 'map'.cub\n");
	if (check == 93)
		return("Invalid rgb form\n");
	if (check == 205)
		return("Missing sprite(s) in the file 'map'.cub\n");
	if (check == 63)
		return("Invalid map, cut by at least one empty line\n");
	return("\n");
}

char	*ft_error_message1(int check)
{
	if (check == 75)
		return("Map not closed\n");
	if (check == 36)
		return("Unvalid char in map\n");
	if (check == 89)
		return("No starting position\n");
	if (check == 47)
		return("Map not closed because of a space\n");
	if (check == 26)
		return("Malloc failed to allocate for char *buff in parsing\n");
	if (check == 1)
		return("Failed to open the file 'map'.cub\n");
	if (check == 3)
		return("Malloc failed to allocate for char *line in parsing\n");
	if (check == 190)
		return("Unvalid char in the file 'map'.cub\n");
	if (check == 150)
		return("Unvalid sprite id\n");
	return(ft_error_message2(check));
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
		printf("ERROR %s", ft_error_message1(-ee->check));
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
