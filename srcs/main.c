#include "cub3D.h"

int	ft_end(t_mast *ee)
{

	int		i;

	i = 0;
	if (ee->win)
		mlx_destroy_window(ee->mlx, ee->win);
	if (ee->mlx)
		mlx_destroy_display(ee->mlx);
	free(ee->mlx);

	i = 0;
	// error(ee->secu);

	exit(1);
}

int key_pressed(int key, t_mast *ee)
{
	if (key == 65307)
		ft_end(ee);
}

t_point	intersection(t_ray ray, int *map)
{
	int	i;
	int j;
	float	coef_x = - ray.dir.y;
	float	coef_y = ray.dir.x;

	i = 0;
	while (i < 4)
	{
		
		i++;
	}

}

int fill_image(t_data *img, t_cam *cam)
{
	t_ray	ray;
	t_point	ortho;

	int map[4*4] = {1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1};
	int i = 0;
	float coef_fov = tan2(FOV);

	ray.pos = (t_point){cam->pos.x, cam->pos.y};
	ray.dir = (t_point){cos(cam->angle), sin(cam->angle)};
	ortho = (t_point){ray.dir.y, -ray.dir.x};
	while (i < RESX)
	{
		ray.dir = (t_point){cos(cam->angle), sin(cam->angle)};
		ray.dir = add(ray.dir, mult((i - RESX / 2.0f) / (RESX / 2.0f) , ortho));

		i++;
	}


	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
}

int	main(int ac, char **av)
{
	t_mast	ee;

	(void)ac;
	(void)av;

	ee.mlx = mlx_init();
	//ft_display();
	ee.win = mlx_new_window(ee.mlx, RESX, RESY, "cub3D");

	ee.img.img = mlx_new_image(ee.mlx, RESX, RESY);
	ee.img.addr = mlx_get_data_addr(ee.img.img, &ee.img.bits_per_pixel, &ee.img.line_length,
								&ee.img.endian);
	mlx_hook(ee.win, ClientMessage, NoEventMask, ft_end, &ee);
	mlx_key_hook (ee.win, key_pressed, &ee);
	fill_image(&ee.img);
	mlx_put_image_to_window(ee.mlx, ee.win, ee.img.img, 0, 0);
	mlx_loop(ee.mlx);
}