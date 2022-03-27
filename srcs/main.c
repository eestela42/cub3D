#include "../cub3D.h"

int	ft_end(t_mast *ee)
{

	int		i;

	i = 0;
	if (ee->map)
		while (ee->map[i])
			free(ee->map[i++]);
	if (ee->map)
		free(ee->map);
	if (ee->win)
		mlx_destroy_window(ee->mlx, ee->win);
	if (ee->mlx)
		mlx_destroy_display(ee->mlx);
	free(ee->mlx);
	i = 0;
	exit(1);
}


# define ROTATE_LEFT	65361
# define ROTATE_RIGHT	65363


/*t_point	intersection(t_ray ray, int *map)
{
	(void)ray;
	int	i;
	//int j;
	(void)map;
	//float	coef_x = - ray.dir.y;
	//float	coef_y = ray.dir.x;

	i = 0;
	while (i < 4)
	{
		
		i++;
	}
	return (NULL);
}*/

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int	my_mlx_pixel_get(t_data *data, int x, int y)
{
	char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    return(*(unsigned int*)dst);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

float	equation_x(t_ray ray, int y)
{
	float	x;

	x = ray.pos.x + ((y - ray.pos.y) / ray.dir.y) * ray.dir.x;
	return (x);
}

float	equation_y(t_ray ray, int x)
{
	float	y;

	y = ray.pos.y + ((x - ray.pos.x) / ray.dir.x) * ray.dir.y;
	return (y);
}

t_point	colision_y(t_mast *ee, t_ray ray)
{
	t_point col;
	int		dir;

	col.y = floor(ee->cam.pos.y);
	dir = -1;
	if (ray.dir.y > 0)
	{
		dir = 1;
		col.y = ceil(ee->cam.pos.y);
	}
	while (ray.dir.y != 0)
	{
		col.x = equation_x(ray, col.y);
		// printf("pour y = %f equation x = %f\n", col.y, col.x);
		if ((int)floor(col.x) >= ee->height || (int)col.y - (dir == -1) >= ee->width
			|| (int)floor(col.x) < 0 || (int)col.y - (dir == -1) < 0)
			break ;
		if (ee->map[(int)floor(col.x)][(int)col.y - (dir == -1)] == '1')
			return (col);
		col.y += dir;
	}
	return((t_point){-1, -1});
}

t_point colision_x(t_mast *ee, t_ray ray)
{
	t_point col;
	int		dir;

	col.x = floor(ee->cam.pos.x);
	dir = -1;
	if (ray.dir.x > 0)
	{
		dir = 1;
		col.x = ceil(ee->cam.pos.x);
	}
	while (ray.dir.x != 0)
	{
		col.y = equation_y(ray, col.x);
		// printf("pour x = %f equation y = %f\n", col.x, col.y);
		if ((int)floor(col.y) >= ee->width || (int)col.x - (dir == -1) >= ee->height
			|| (int)floor(col.y) < 0 || (int)col.x - (dir == -1) < 0)
			break ;
		if (ee->map[(int)col.x - (dir == -1)][(int)floor(col.y)] == '1')
			return (col);
		col.x += dir;
	}
	return((t_point){-1, -1});
}

char	find_colision(t_mast *ee, t_ray ray, t_point *col)
{
	t_point	col_x;
	t_point	col_y;

	col_x = colision_x(ee, ray);
	col_y = colision_y(ee, ray);
	if ((col_x.x == -1) || (col_y.y != -1
		&& distance(ray.pos, col_x) > distance(ray.pos, col_y)))
	{
		*col = col_y;
		return ('y');
	}
	*col = col_x;
	return ('x');
}

int	color_pix(t_mast *ee, t_point col, char finder, t_point ray_dir, float zone)
{
	t_data	texture;
	float	offset;
	int		i;
	int		j;
(void)finder;
	if (finder == 'x')
	{
		if (ray_dir.x > 0)
			texture = ee->sp.n;
		else
			texture = ee->sp.s;
		offset = col.y - floor(col.y);
		if (ray_dir.x > 0)
			offset = 1 - offset;
	}
	else
	{
		if (ray_dir.y > 0)
			texture = ee->sp.w;
		else
			texture = ee->sp.e;
		offset = col.x - floor(col.x);
		if (ray_dir.y <= 0)
			offset = 1 - offset;
	}
	i = ((zone + 1) / 2) * texture.height;
	j = offset * texture.width;
	return (my_mlx_pixel_get(&texture, j, i));
}

int	fill_column(t_mast *ee, int x, char finder, float dist, t_point col, t_point ray_dir)
{
	int		y;
	float	zone;
	float 	coef_fov;

	coef_fov = tan(FOV * (float) RESY / RESX / 2) * 3;
	y = 0;
	while (y < RESY)
	{
		zone = (y - (float) RESY / 2) / (RESY / 2) * coef_fov * dist;
		if (zone > 1)
			my_mlx_pixel_put(&ee->img, x, y, ee->floor);
		else if (zone < -1)
			my_mlx_pixel_put(&ee->img, x, y, ee->ceil);
		else
			my_mlx_pixel_put(&ee->img, x, y,
				color_pix(ee, col, finder, ray_dir, zone));
		y++;
	}
	return (0);
	(void)finder;
}

float	projection(t_cam *cam, t_point col)
{
	t_point	ret;
	t_point	dir;

	ret = diff(col, cam->pos);
	dir = (t_point){cos(cam->angle), sin(cam->angle)};
	return (fabs(dot(ret, dir)));
}

int	fill_image(t_data *img, t_cam *cam, t_mast *ee)
{
	t_ray	ray;
	t_point	ortho;
	t_point	col;
	char	finder;
	int		i;
	float	coef_fov;

	(void) img;
	i = 0;
	coef_fov = tan(FOV / 2);
	ray.pos = (t_point){cam->pos.x, cam->pos.y};
	ray.dir = (t_point){cos(cam->angle), sin(cam->angle)};
	ortho = (t_point){ray.dir.y, -ray.dir.x};
	while (i < RESX)
	{
		ray.dir = (t_point){cos(cam->angle), sin(cam->angle)};
		ray.dir = normalize(add(ray.dir,
					mult(coef_fov * (i - RESX / 2.0f) / (RESX / 2.0f), ortho)));
		finder = find_colision(ee, ray, &col);
		fill_column(ee, i, finder, projection(cam, col), col, ray.dir);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_mast	ee;
	int		check;

	(void)ac;
	ee.mlx = mlx_init();
	ee.win = mlx_new_window(ee.mlx, RESX, RESY, "cub3D");
	ee.map = NULL;
	check = parsing(&ee, av[1]);
	if (check != -1024)
	{
		printf("ERROR %i\n", -check);
		ft_end(&ee);
	}
	printf("cehck = %i\n", check);
	ee.img.img = mlx_new_image(ee.mlx, RESX, RESY);
	ee.img.addr = mlx_get_data_addr(ee.img.img,
			&ee.img.bits_per_pixel, &ee.img.line_length, &ee.img.endian);
	mlx_hook(ee.win, ClientMessage, NoEventMask, ft_end, &ee);
	mlx_hook (ee.win, 2, 1L << 0, key_pressed, &ee);
	mlx_loop_hook(ee.mlx, key_action, &ee);
	mlx_hook (ee.win, 3, 1L << 1, key_release, &ee);
	fill_image(&ee.img, &ee.cam, &ee);
	mlx_put_image_to_window(ee.mlx, ee.win, ee.img.img, 0, 0);
	mlx_loop(ee.mlx);
	ft_end(&ee);
}
