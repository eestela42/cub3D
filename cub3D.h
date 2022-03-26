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

# define RESX 1600
# define RESY 900
# define FOV 100 * M_PI / 180

# define ROTATE_LEFT	65361
# define ROTATE_RIGHT	65363
# define FORWARD_W_Z	119
# define BACK_S_S		115
# define RIGHT_D_D		100
# define LEFT_A_Q		97

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
	int		width;
	int		height;
}				t_data;



typedef	struct s_rep_sprites
{
	t_data	n;
	t_data	s;
	t_data	e;
	t_data	w;
}				t_rep_sprites;

typedef struct s_mast
{
	int				secu;
	int				r;
	char			mem;
	char			**map;
	int				height;
	int				width;
	void			*mlx;
	void			*win;
	int				floor;
	int				ceil;
	t_cam			cam;
	t_rep_sprites	sp;
	t_data			img;
}				t_mast;

/* PARSING */

int		parsing(t_mast *ee, char *file);
int		parsing_map(t_mast *ee, char *line, int i);


/* PARSING UTILS */
int		ft_atoi(char *str);
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
int		fct_tab_floor(t_mast *ee, char *line, int i);
int		fct_tab_ceiling(t_mast *ee, char *line, int i);


/* POINT */
t_point	add(t_point a, t_point b);
t_point mult(float m, t_point p);
float	distance(t_point a, t_point b);
t_point	normalize(t_point a);
t_point	diff(t_point a, t_point b);
float	dot(t_point a, t_point b);

int	create_trgb(int t, int r, int g, int b);

int fill_image(t_data *img, t_cam *cam, t_mast *ee);


#endif