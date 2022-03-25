#ifndef CUB3D_H
# define CUB3D_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>

#define RESX 1600
#define RESY 900
#define FOV 120

typedef	struct	s_point
{
	float	x;
	float	y;
}				t_point;

typedef	struct s_cam
{
	t_point	pos;
	float	angle;
}				t_cam;

typedef	struct s_ray
{
	t_point	pos;
	t_point	dir;
}				t_ray;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_sprite
{
	void	*add;
	int		width;
	int		height;
}				t_sprite;

typedef	struct s_rep_sprites
{
	t_sprite	n;
	t_sprite	s;
	t_sprite	e;
	t_sprite	w;
}				t_rep_sprites;

typedef struct s_mast
{
	int				secu;
	int				r;
	int				y;
	int				x;
	char			mem;
	char			**map;
	void			*mlx;
	void			*win;
	t_rep_sprites	sp;
	t_data			img;
}				t_mast;

/* PARSING */

int		parsing(t_mast *ee, char *file);
int		parsing_map(t_mast *ee, char *line);


/* PARSING UTILS */
char	*ft_strdup(const char *s1);
char	*ft_strjoin_free(char *s1, char *s2);
int		ft_strlen(const char *s);
char	*ft_substr(char *s, int start, int len);

/* FCT_TAB*/

int		fct_tab_error(t_mast *ee, char *line, int i);
int		fct_tab_map(t_mast *ee, char *line, int i);
int		fct_tab_north(t_mast *ee, char *line, int i);
int		fct_tab_south(t_mast *ee, char *line, int i);
int		fct_tab_east(t_mast *ee, char *line, int i);
int		fct_tab_west(t_mast *ee, char *line, int i);



/* POINT */
t_point	add(t_point a, t_point b);
t_point mult(float m, t_point p);

#endif