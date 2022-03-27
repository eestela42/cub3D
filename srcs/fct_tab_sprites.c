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

int	check_rgb(int rgb[3])
{
	int	i;

	i = 0;
	while (i < 3)
		if (rgb[i] < 0 || rgb[i++] > 255)
			return (1);
	return (0);
}

int	fct_tab_floor(t_mast *ee, char *line, int i)
{
	int	x;
	int	y;
	int	start;
	int	floor[3];

	i++;
	while (line[i] && line[i] == ' ')
		i++;
	start = i;
	x = 0;
	y = 0;
	while (x < 3)
	{
		y = 0;
		floor[x] = ft_atoi(&line[start]);
		while (y++ < 3 && line[i] >= '0' && line[i] <= '9')
			i++;
		if (x < 2 && line[i++] != ',')
			return (-93);
		start = i;
		x++;
	}
	if (check_rgb(floor))
		return (-666);
	ee->floor = create_trgb(0, floor[0], floor[1], floor[2]);
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] != '\n')
		return (-94);
	return (i);
}

int	fct_tab_ceiling(t_mast *ee, char *line, int i)
{
	int	x;
	int	y;
	int	start;
	int	ceil[3];

	i++;
	while (line[i] && line[i] == ' ')
		i++;
	start = i;
	x = 0;
	y = 0;
	while (x < 3)
	{
		y = 0;
		ceil[x] = ft_atoi(&line[start]);
		while (y++ < 3 && line[i] >= '0' && line[i] <= '9')
			i++;
		if (x < 2 && line[i++] != ',')
			return (-93);
		start = i;
		x++;
	}
	if (check_rgb(ceil))
		return (-666);
	ee->ceil = create_trgb(0, ceil[0], ceil[1], ceil[2]);
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] != '\n')
		return (-94);
	return (i);
}
