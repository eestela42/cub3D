#include "../cub3D.h"

	
int	xpm_to_image(void *mlx_ptr, char *line, int i, t_sprite *ptr_sprite)
{
	t_sprite	sprite;
	int			start;
	int			end;
	char		*path;

	if (ptr_sprite->add)
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
	sprite.add = mlx_xpm_file_to_image(mlx_ptr, path, &sprite.width, &sprite.height);
	free(path);
	if (!sprite.add)
		return (-13);
	*ptr_sprite = sprite;
	return (i);
}

int	fct_tab_north(t_mast *ee, char *line, int i)
{
	printf("NORTH\n");
	if (line[++i] != 'O' || ee->sp.n.add)
		return (-150);
	i += 1;
	while (line[i] == ' ')
	 	 i++;
	return(xpm_to_image(ee->mlx, line, i, &ee->sp.n));
}

int	fct_tab_south(t_mast *ee, char *line, int i)
{
	printf("SOUTH\n");
	if (line[++i] != 'O' || ee->sp.s.add)
		return (-1);
	i += 1;
	while (line[i] == ' ')
	 	 i++;
	return(xpm_to_image(ee->mlx, line, i, &ee->sp.s));
}

int	fct_tab_east(t_mast *ee, char *line, int i)
{
	printf("EAST\n");
	if (line[++i] != 'A' || ee->sp.e.add)
		return (-1);
	i += 1;
	while (line[i] == ' ')
	 	 i++;
	return(xpm_to_image(ee->mlx, line, i, &ee->sp.e));
}

int	fct_tab_west(t_mast *ee, char *line, int i)
{
	printf("WEST\n");
	if (line[++i] != 'E' || ee->sp.w.add)
		return (-1);
	i += 1;
	while (line[i] == ' ')
	 	 i++;
	return(xpm_to_image(ee->mlx, line, i, &ee->sp.w));
}
