#include "../cub3D.h"


void	init_mast(t_mast *ee)
{
	ee->sp.n.add = NULL;
	ee->sp.s.add = NULL;
	ee->sp.e.add = NULL;
	ee->sp.w.add = NULL;
}

void	init_fct_tab(int	(*fct_tab[256])(t_mast *ee, char *line, int i))
{
	int	i;

	i = 0;
	while (i < 256)
		fct_tab[i++] = fct_tab_error;
	fct_tab['S'] = fct_tab_south;
	fct_tab['N'] = fct_tab_north;
	fct_tab['E'] = fct_tab_east;
	fct_tab['W'] = fct_tab_west;
	fct_tab['1'] = fct_tab_map;
	fct_tab['0'] = fct_tab_map;
}

int	get_sprites(t_mast *ee, char *line)
{
	int	i;
	int	(*fct_tab[256])(t_mast *ee, char *line, int i);

	init_mast(ee);
	init_fct_tab(fct_tab);
	i = 0;
	while (i >= 0 && line[i])
	{
		while (line[i] && (line[i] == ' ' || line[i] == '\n'))
			i++;
		if (!line[i])
			break ;
		i = fct_tab[(int)line[i]](ee, line, i);
	}
	if (i < 0)
		return (i);
	return (parsing_map(ee, line));
}


int parsing(t_mast *ee, char *file)
{
	char	*buff;
	char	*line;
	int  	fd;
	int  	r;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	buff = malloc(sizeof(char) * 1025);
	if (!buff)
		return (-26);
	line = ft_strdup("");
	r = read(fd, buff, 1024);
	while (line && r > 0)
	{
		buff[r] = 0;
		line = ft_strjoin_free(line, buff);
		r = read(fd, buff, 1024);
	}
	free(buff);
	if (!line)
		return (-3);
	return (get_sprites(ee, line));
}