#include "fdf_sourses/minilibx/mlx.h"
#include <math.h>

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
	while (i < x + r)
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