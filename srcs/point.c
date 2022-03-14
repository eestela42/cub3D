#include "cub3D.h"

t_point	add(t_point a, t_point b)
{
	return (t_point){a.x + b.x, a.y + b.y};
}

t_point mult(float m, t_point p)
{
	return (t_point){p.x * m, p.y * m};
}