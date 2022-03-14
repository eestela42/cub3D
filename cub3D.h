#ifndef CUB3D_H
# define CUB3D_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
#include <math.h>

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

typedef struct s_mast
{
	int			secu;
	int			r;
	int			y;
	int			x;
	char		mem;
	void		*mlx;
	void		*win;
	t_data		img;
}				t_mast;


t_point	add(t_point a, t_point b);
t_point mult(float m, t_point p);

#endif