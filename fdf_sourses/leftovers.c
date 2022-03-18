#include "fdf_sourses/minilibx/mlx.h"
#include <math.h>
#include "fdf.h"

void	print_map(t_map *map) //temp function
{
	int	i;
	int	j;

	i = 0;
	printf("%d, %d\n", map->width, map->height);
	while (i < map->height)
	{
		j = 0;
		while (j != map->width)
		{
			printf("%d ", map->lines[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

// int	min_altitude(t_map *map)
// {
// 	int	i;
// 	int	j;
// 	int	min;

// 	i = 0;
// 	min = 0;
// 	while (i < map->height)
// 	{
// 		j = 0;
// 		while (j < map->width)
// 		{
// 			if (map->lines[i][j] < min)
// 				min = map->lines[i][j];
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (min);
// }


// void	bresenham_algo(t_mlx *mlx, int x, int y, int x1, int y1)
// {
// 	int	x_step;
// 	int	y_step;
// 	int	max;

// 	x_step = ABS(x1 - x);
// 	y_step = ABS(y1 - y);
// 	max = MAX(x_step, y_step);
// 	printf("MAX: %d\n", max); //
// 	x_step /= max;
// 	y_step /= max;
// 	while ((int)(x - x1) || (int)(y - y1))
// 	{
// 		my_mlx_pixel_put(mlx, x, y, 0x00FF0000);
// 		x += x_step;
// 		y += y_step;
// 	}
// }

// void	draw_circle(t_mlx *mlx, int x, int y, int r)
// {
// 	int	i;
// 	double	j1, j2;
// 	int	d;

// 	d = r * 2;
// 	i = x - r;
// 	while (i <= x + r)
// 	{
// 		j1 = sqrt(r * r - (i - x) * (i - x)) + y;
// 		j2 = -j1 + y * 2;
// 		my_mlx_pixel_put(mlx, j1, i, 0x00FF0000);
// 		my_mlx_pixel_put(mlx, j2, i, 0x00FF0000);
// 		i++;
// 	}
// }

// void iso(t_p *p, int z)
// {
// 	int	previous_x;
// 	int	previous_y;

// 	previous_x = p->x;
// 	previous_y = p->y;
// 	p->x = (previous_x - previous_y) * cos(0.523599);
// 	p->y = -z + (previous_x + previous_y) * sin(0.523599);
// }

typedef struct	s_data
{
	void	*img;
	void	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_square(void *mlx, t_data img, int x, int y, int len)
{
	int	i;

	while (y < len)
	{
		i = x;
		while (i < len)
		{
			my_mlx_pixel_put(&img, i, y, 0x00FF0000);
			i++;
		}
		y++;
	}
}

void	draw_circle(void *mlx, t_data img, int x, int y, int r)
{
	int	i;
	double	j1, j2;
	int	d;

	d = r * 2;
	i = x - r;
	while (i <= x + r)
	{
		j1 = sqrt(r * r - (i - x) * (i - x)) + y;
		j2 = -j1 + y * 2;
		my_mlx_pixel_put(&img, j1, i, 0x00FF0000);
		my_mlx_pixel_put(&img, j2, i, 0x00FF0000);
		i++;
	}
}

int main(void)
{
	void	*mlx;
	t_data	img;
	void	*window;

	mlx = mlx_init();
	window = mlx_new_window(mlx, 500, 500, "42");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	//draw_square(mlx, img, 5, 5, 50);
	//draw_square(mlx, img, 100, 100, 100 + 50);
	draw_circle(mlx, img, 100, 100, 150);
	//my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(mlx, window, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
