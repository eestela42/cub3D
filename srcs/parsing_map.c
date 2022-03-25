#include "../cub3D.h"

int	check_space(char **map, int x, int y)
{
	if (x != 0 && map[x - 1][y] == '0')
		return (1);
	if (map[x + 1] && map[x + 1][y] == '0')
		return (1);
	if (y != 0 && map[x][y - 1] == '0')
		return (1);
	if (map[x][y + 1] && map[x][y + 1] == '0')
		return (1);
	return (0);
}

int	error_in_map(char **map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] == ' ' && check_space(map, x, y))
				return (-1);
			y++;
		}
		x++;
	}
	return (0);
}

int	map_height(char *line, int i)
{
	int	height;
	int	in_map;

	height = 0;
	in_map = 1;
	while (line[i])
	{
		if (line[i] == '1')
		{
			if (in_map == -1)
				return (-1);
			in_map = 1;
		}
		if (line[i] == '\n' && in_map == 1)
		{
			height++;
			in_map = 0;
		}
		else if (line[i] == '\n')
			in_map = -1;
		i++;
	}
	return (height);
}

int	map_width(char *line, int height, int i)
{
	int	width;
	int	w_line;

	width = 0;
	while (line[i] && height)
	{
		w_line = 0;
		while (line[i] && line[i] != '\n')
		{
			i++;
			w_line++;
		}
		if (w_line > width)
			width = w_line;
		i++;
		height--;
	}
	return (width);
}

char **make_map(char *line, int start, int height, int width)
{
	char	**map;
	int		i;
	int		y;

	map = malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	map[height] = NULL;
	i = 0;
	while (i < height)
	{
		map[i] = malloc(sizeof(char) * (width + 1));
		if (!map[i])
		{
			while (i)
				free(map[i--]);
			free(map);
			return (NULL);
		}
		y = 0;
		while (line[start] && line[start] != '\n')
		{
			map[i][y++] = line[start++];
		}
		start++;
		while (y < width)
			map[i][y++] = ' ';
		map[i][y] = 0;
		i++;
	}
	return (map);
}

int	parsing_map(t_mast *ee, char *line)
{
	int	i;
	int	height;
	int	width;
	int	start;

	i = 0;
	while (line [i] && line[i] != '1' && line[i] != '0')
		i++;
	while (i >= 0 && line[i] != '\n')
		i--;
	start = ++i;
	height = map_height(line, start);
	width = map_width(line, height, start);
	ee->map = make_map(line, start, height, width);
	return (error_in_map(ee->map));
	(void)ee;
}