#include "../cub3D.h"

t_point	add(t_point a, t_point b)
{
	return (t_point){a.x + b.x, a.y + b.y};
}

t_point mult(float m, t_point p)
{
	return (t_point){p.x * m, p.y * m};
}

float	norm(t_point a)
{
	return (sqrt(a.x * a.x + a.y * a.y));
}

float	distance(t_point a, t_point b)
{
	return (norm(diff(a, b)));
}

t_point	normalize(t_point a)
{
	if (!norm(a))
		return (a);
	return (mult(1 / norm(a), a));
}

float	dot(t_point a, t_point b)
{
	return(a.x * b.x + a.y * b.y);
}

t_point	diff(t_point a, t_point b)
{
	return ((t_point){a.x - b.x, a.y - b.y});
}