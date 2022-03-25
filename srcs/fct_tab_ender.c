#include "../cub3D.h"

int	fct_tab_error(t_mast *ee, char *line, int i)
{
	(void)ee;
	(void)line;
	(void)i;
	return (-19);
}

int	fct_tab_map(t_mast *ee, char *line, int i)
{
	if (ee->sp.n.add && ee->sp.s.add && ee->sp.e.add && ee->sp.w.add)
		printf("All sprites good \n");
	else
		return (-205);
	while (line[i] == '1' || line[i] == '0')
		i++;
	return (i);
}