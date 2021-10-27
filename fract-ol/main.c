#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mlx.h>

typedef struct data_s
{
  void *mlx_ptr;
  void *mlx_win;
  double zoom;
  int x;
  int y;
  double panx;
  double pany;
  int *buffer;
  char *image;
  int pixel_bits;
  int line_bytes;
  int endian;
  double dx;
  double dy;
  double xMin;
  double xMax;
  double yMin;
  double yMax;
} data_t;

typedef struct rgb_s
{
  int r;
  int g;
  int b;
} rgb;


int rgb_to_int(int r, int g, int b)
{
	int color = 0;
	color |= b;
	color |= g << 8;
	color |= r << 16;
	return (color);
}

int iterate(int max_iter, float x0, float y0)
{
	float xtemp;
	float x;
	float y;
	int iter;

	x = 0;
	y = 0;
	iter = 0;
	while (iter < max_iter && (x * x + y * y <= 4))
	{
		xtemp = x * x - y * y + x0;
		y = 2 * x * y + y0;
		// Next iteration
		x = xtemp;
		iter++;
	}
	return (iter);
}

int pickColor(int max_iterations, int iterations, double Tr, double Ti)
{
	int v;

	float logBase = 1.0 / log(2.0);
	float logHalfBase = log(0.5) * logBase;

	if ( iterations == max_iterations ) // converged?
		return (0);
	v = 512 * (5 + iterations - logHalfBase - log(log(Tr + Ti)) * logBase) / iterations;
	if ( v > 255 ) v = 255;
	return rgb_to_int(v, v, v);
}

int iterateEquation(int maxiterations, double Cr, double Ci)
{
	double Zr = 0;
	double Zi = 0;
	double Tr = 0;
	double Ti = 0;
	int iterations = 0;

	while (iterations < maxiterations && (Tr + Ti <= 4))
	{
		Zi = 2 * Zr * Zi + Ci;
		Zr = Tr - Ti + Cr;
		Tr = Zr * Zr;
		Ti = Zi * Zi;
		iterations++;
	}
	return pickColor(maxiterations, iterations, Tr, Ti);
}

int	update_image(data_t *data)
{
	int	x;
	int	y;
	int	pixel;
	float dx;
	float dy;
	int colour;

	dy = 0;
	y = -1;
	pixel = 0;

	#pragma omp parallel
	while (++y < data->y)
	{
		x = -1;
		dx = 0;
		#pragma omp parallel
		while (++x < data->x)
		{
			colour = iterateEquation(500, dx + data->xMin,dy + data->yMin);
//			printf("%d dx:%f dy:%f\n", it, dx, dy);
			data->buffer[pixel] = (colour);
			pixel++;
			dx += data->dx;
		}
		dy += data->dy;
//			mlx_pixel_put(data.mlx_ptr, data.mlx_win, x, y, rgb_to_int(230, 10, 124));
	}
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->image, 0, 0);
	//	mlx_destroy_image(data->mlx_ptr, data->image);
	return (1);
}

int mandelbrot(data_t *data)
{
	data->xMin = -2.0;
	data->xMax = 0.47;
	data->yMin = -1.12;
	data->yMax = 1.12;

	data->dx = (data->xMax - data->xMin) / data->x;
	data->dy = (data->yMax - data->yMin) / data->y;

	update_image(data);
	return (1);
}

int mouse_event(int button, int x, int y, data_t *data)
{

	// Whenever the event is triggered, print the value of button to console.
	printf("bb::%d x:%d y:%d dx:%f dy:%f xmin:%f xmax:%f ymin:%f ymax:%f\n", button, x, y, data->dx, data->dy, data->xMin, data->xMax, data->yMin, data->yMax);
	if (button == 4)
	{
		double xm = data->dx * x + data->xMin;
		double ym = data->dy * y + data->yMin;

		data->dx /= data->zoom;
		data->dy /= data->zoom;

		data->xMin= xm - x * data->dx;
		data->xMax= xm + (data->x - x) * data->dx;

		data->yMin= ym - y * data->dy;
		data->yMax= ym + (data->y - y) * data->dy;
		update_image(data);
		printf("b::%d x:%d y:%d dx:%f dy:%f xmin:%f xmax:%f ymin:%f ymax:%f\n", button, x, y, data->dx, data->dy, data->xMin, data->xMax, data->yMin, data->yMax);

		update_image(data);
	}
	else if (button == 5)
	{
		double xm = data->dx * data->zoom * x + data->xMin;
		double ym = data->dy * data->zoom * y + data->yMin;

		data->xMin= xm - (data->x - x) * data->dx;
		data->xMax= xm + x * data->dx;

		data->yMin= ym - y * data->dy;
		data->yMax= ym + (data->y - y) * data->dy;

		data->dx *= data->zoom;
		data->dy *= data->zoom;


		update_image(data);
		printf("bb::%d x:%d y:%d dx:%f dy:%f xmin:%f xmax:%f ymin:%f ymax:%f\n", button, x, y, data->dx, data->dy, data->xMin, data->xMax, data->yMin, data->yMax);
	}
	return 1;
}

//int kbd_event(int button, data_t *data)
//{
//	// Whenever the event is triggered, print the value of button to console.
//	printf("key:: %d px0:%f\n", button, data->panx);
//	if (button == 65363)
//	{
//		data->panx += 5;
//		update_image(data);
//	}
//	else if (button == 65361)
//	{
//		data->panx -= 5;
//		update_image(data);
//	}
//	else if (button == 65362)
//	{
//		data->pany += 5;
//		update_image(data);
//	}
//	else if (button == 65364)
//	{
//		data->pany -= 5;
//		update_image(data);
//	}
//	return 1;
//}

int main(void)
{
	data_t data;

	data.mlx_ptr = mlx_init();
	data.x = 988;
	data.y = 896;
	data.zoom = 1.1;
	data.panx = 0;
	data.pany = 0;

	if (!(data.mlx_ptr))
		return (EXIT_FAILURE);
	data.mlx_win = mlx_new_window(data.mlx_ptr, data.x, data.y, "Hello world");
	if (!(data.mlx_win))
		return (EXIT_FAILURE);

	data.image = mlx_new_image(data.mlx_ptr, data.x, data.y);
	data.buffer = (int *)mlx_get_data_addr(data.image, &data.pixel_bits, &data.line_bytes, &data.endian);
	data.line_bytes /= 4;

	mandelbrot(&data);
	mlx_mouse_hook(data.mlx_win, &mouse_event, &data);
//	mlx_key_hook(data.mlx_win, &kbd_event, &data);
	mlx_loop(data.mlx_ptr);
	return (EXIT_SUCCESS);
}
