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

int	check_border(char **map, int height, int width)
{
	int i;

	i = -1;
	while (++i < height)
		if (map[i][0] != ' ' && map[i][0] != '1')
			return (1);
	i = -1;
	while (++i < width)
		if (map[0][i] != ' ' && map[0][i] != '1')
			return (1);
	i = -1;
	while (++i < height)
		if (map[i][width - 1] != ' ' && map[i][width - 1] != '1')
			return (1);
	i = -1;
	while (++i < width)
		if (map[height - 1][i] != ' ' && map[height - 1][i] != '1')
			return (1);
	return (0);
}

int	char_in_map(t_mast *ee, int x, int y)
{
	char	c;

	c = ee->map[x][y];
	if (ee->cam.pos.x != -1)
		return (1);
	if (c != 'N' && c != 'E' && c != 'W' && c != 'S')
		return (1);
	ee->map[x][y] = '0';
	ee->cam.pos.x = x + 0.5;
	ee->cam.pos.y = y + 0.5;
	if (c == 'E')
		ee->cam.angle = 0.5 * M_PI;
	if (c == 'W')
		ee->cam.angle = 1.5 * M_PI;
	if (c == 'N')
		ee->cam.angle = 1 * M_PI;
	if (c == 'S')
		ee->cam.angle = 0;
	return (0);
}


int	error_in_map(t_mast *ee, int height, int width)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	ee->cam.pos.x = -1;
	ee->cam.pos.y = -1;
	if (check_border(ee->map, height, width))
		return (-75);
	x = 0;
	while (ee->map[x])
	{
		y = 0;
		while (ee->map[x][y])
		{
			if (ee->map[x][y] == ' ')
			{
				if (check_space(ee->map, x, y))
					return (-47);
			}
			else if (ee->map[x][y] == '1' || ee->map[x][y] == '0')
				;
			else if (char_in_map(ee, x, y))
				return (-36);
			y++;
		}
		x++;
	}
	if (ee->cam.pos.y == -1)
		return (-89);
	return (-1024);
}

int	line_in_map(char *line, int i)
{
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == '1')
			return (1);
		i++;
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
		if (line_in_map(line, i))
		{
			if (in_map == -1)
				return (-63);
			in_map = 1;
		}
		else if (line[i] == '\n' && in_map == 1)
		{
			height++;
			in_map = 0;
		}
		else if (line[i] == '\n')
			in_map = -1;
		else if (line[i] != ' ')
			return (-63);
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

int	parsing_map(t_mast *ee, char *line, int i)
{
	int	start;

	while (i >= 0 && line[i] != '\n')
		i--;
	start = ++i;
	ee->height = map_height(line, start);
	if (ee->height <= 0)
		return (-63);
	ee->width = map_width(line, ee->height, start);
	ee->map = make_map(line, start, ee->height, ee->width);
	return (error_in_map(ee, ee->height, ee->width));
}