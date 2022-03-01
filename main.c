#include <mlx.h>

void drawline(void *mlx_ptr, void *win_ptr, int x, int y)
{
	while (x < 485)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0xffffff);
		x++;
	}
}

int main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "42");
	drawline(mlx_ptr, win_ptr, 115, 250);
	mlx_loop(mlx_ptr);
	return (0);
}