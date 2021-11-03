#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mlx.h>

typedef struct mlx_s
{
  void *mlx_ptr;
  void *mlx_win;
  int *buffer;
  char *image;
  int height;
  int width;
  int pixel_bits;
  int line_bytes;
  int endian;
} mlx_t;

typedef struct data_s
{
  double zoom;

  double dx;
  double dy;
  double xMin;
  double xMax;
  double yMin;
  double yMax;
} data_t;

typedef struct colour_s
{
  int r;
  int g;
  int b;
} colour_t;

typedef struct all_s
{
  mlx_t *mlx;
  colour_t *start;
  colour_t *end;
  data_t *mandel;
} all_t;

unsigned int rgb_to_int(unsigned int r, unsigned int g, unsigned int b)
{
	unsigned int color = 0;
	color |= b;
	color |= g << 8;
	color |= r << 16;
	return (color);
}

unsigned int pickColor(int max_iterations, int iterations, colour_t *start, colour_t *end)
{
 	int v;
 	int r;
	int g;
	int b;

	if ( iterations == max_iterations)
		return (0);
	v = (int)log((double)iterations / (double)max_iterations * 255);

	r = (int)(((double)end->r - (double)start->r) * v / log(255));
	g = (int)(((double)end->g - (double)start->g) * v / log(255));
	b = (int)(((double)end->b - (double)start->b) * v / log(255));

	if (end->r > start->r)
		r += start->r;
	else
		r += end->r;
	if (end->g > start->g)
		g += start->g;
	else
		g += end->g;
	if (end->b > start->b)
		b += start->b;
	else
		b += end->b;

	return rgb_to_int(r, g, b);
}

unsigned int iterate_mandelbrot(int maxiterations, double x0, double y0, all_t *a)
{
	double xtemp;
	double x;
	double y;
	int iterations;

	x = 0;
	y = 0;
	iterations = 0;
	while (iterations < maxiterations && (x * x + y * y <= 4))
	{
		xtemp = x * x - y * y + x0;
		y = 2 * x * y + y0;
		x = xtemp;
		iterations++;
	}
	return (pickColor(maxiterations, iterations, a->start, a->end));
}

//int iterate_julia(int maxiterations, double x0, double y0)
//{
//	int iterations = 0;
//	double xtemp;
//
//	double cy = 0;
//	double cx = 0;
//	while (x0 * x0 + y0 * y0 < 4  &&  iterations < maxiterations)
//	{
//		xtemp = x0 * x0 - x0 * x0;
//		y0 = 2 * x0 * x0  + cy;
//		x0 = xtemp + cx;
//		iterations++;
//	}
//	return (pickColor(maxiterations, iterations));
//}

int	update_image(all_t *a)
{
	int	x;
	int	y;
	int	pixel;
	double dx;
	double dy;
	int colour;

	dy = 0;
	y = -1;
	pixel = 0;

//	int iterations = 2 * (a->mandel->xMax - a->mandel->xMin);
//	printf("iterations: %d\n", iterations);
	while (++y < a->mlx->height)
	{
		x = -1;
		dx = 0;
		while (++x < a->mlx->width)
		{
			colour = (int)iterate_mandelbrot(500, dx + a->mandel->xMin,dy + a->mandel->yMin, a);
//			printf("%d dx:%f dy:%f\n", it, dx, dy);
			a->mlx->buffer[pixel++] = colour;
			dx += a->mandel->dx;
		}
		dy += a->mandel->dy;
	}
	mlx_put_image_to_window(a->mlx->mlx_ptr, a->mlx->mlx_win, a->mlx->image, 0, 0);
	return (1);
}


int mandelbrot(all_t *a)
{
	a->mandel->xMin = -2.0;
	a->mandel->xMax = 0.47;
	a->mandel->yMin = -1.12;
	a->mandel->yMax = 1.12;

	a->mandel->dx = (a->mandel->xMax - a->mandel->xMin) / a->mlx->width;
	a->mandel->dy = (a->mandel->yMax - a->mandel->yMin) / a->mlx->height;

	update_image(a);
	return (1);
}

int mouse_event(int button, int x, int y, all_t *a)
{
	double xm;
	double ym;
	// Whenever the event is triggered, print the value of button to console.
//	printf("bb::%d x:%d y:%d dx:%f dy:%f xmin:%f xmax:%f ymin:%f ymax:%f\n", button, x, y, data->dx, data->dy, data->xMin, data->xMax, data->yMin, data->yMax);
	if (button == 4)
	{
		xm = a->mandel->dx * x + a->mandel->xMin;
		ym = a->mandel->dy * y + a->mandel->yMin;

		a->mandel->dx /= a->mandel->zoom;
		a->mandel->dy /= a->mandel->zoom;

		a->mandel->xMin= xm - x * a->mandel->dx;
		a->mandel->xMax= xm + (a->mlx->width - x) * a->mandel->dx;

		a->mandel->yMin= ym - y * a->mandel->dy;
		a->mandel->yMax= ym + (a->mlx->height - y) * a->mandel->dy;
		//		printf("b::%d x:%d y:%d dx:%f dy:%f xmin:%f xmax:%f ymin:%f ymax:%f\n", button, x, y, data->dx, data->dy, data->xMin, data->xMax, data->yMin, data->yMax);
	}
	else if (button == 5)
	{
		xm = a->mandel->dx * x + a->mandel->xMin;
		ym = a->mandel->dy * y + a->mandel->yMin;

		a->mandel->dx *= a->mandel->zoom;
		a->mandel->dy *= a->mandel->zoom;

		a->mandel->xMin= xm - x * a->mandel->dx;
		a->mandel->xMax= xm + (a->mlx->width - x) * a->mandel->dx;

		a->mandel->yMin= ym - y * a->mandel->dy;
		a->mandel->yMax= ym + (a->mlx->height - y) * a->mandel->dy;

//		printf("bb::%d x:%d y:%d dx:%f dy:%f xmin:%f xmax:%f ymin:%f ymax:%f\n", button, x, y, data->dx, data->dy, data->xMin, data->xMax, data->yMin, data->yMax);
	}
	update_image(a);
	return (1);
}

int kbd_event(int button, all_t *a)
{
	double step;

	printf("key:: %d\n", button);
	if (button == 124)
	{
		step = a->mandel->dx * 4;
		a->mandel->xMin += step;
		a->mandel->xMax += step;
	}
	else if (button == 123)
	{
		step = a->mandel->dx * 4;
		a->mandel->xMin -= step;
		a->mandel->xMax -= step;
	}
	else if (button == 125)
	{
		step = a->mandel->dy * 4;
		a->mandel->yMin += step;
		a->mandel->yMax += step;
	}
	else if (button == 126)
	{
		step = a->mandel->dy * 4;
		a->mandel->yMin -= step;
		a->mandel->yMax -= step;
	}
	else if (button == 53)
	{
		mlx_destroy_image(a->mlx->mlx_ptr, a->mlx->image);
		exit(0);
	}
	update_image(a);
	return (1);
}

int main(void)
{
	all_t all;
	mlx_t mlx;
	data_t *mand = (data_t *)malloc(sizeof(data_t));

	all.mlx = &mlx;
	all.mandel = mand;
	mlx.mlx_ptr = mlx_init();
	mlx.height = 896;
	mlx.width = 988;

	colour_t *start = (colour_t *)malloc(sizeof(colour_t));
	colour_t *end = (colour_t *)malloc(sizeof(colour_t));
	start->r = 206;
	start->g = 41;
	start->b = 0;
	all.start = start;
	end->r = 175;
	end->g = 206;
	end->b = 0;
	all.end = end;
	mand->zoom = 1.1;

	if (!(mlx.mlx_ptr))
		return (EXIT_FAILURE);
	mlx.mlx_win = mlx_new_window(mlx.mlx_ptr, mlx.width, mlx.height, "Hello world");
	if (!(mlx.mlx_win))
		return (EXIT_FAILURE);

	mlx.image = mlx_new_image(mlx.mlx_ptr, mlx.width, mlx.height);
	mlx.buffer = (int *)mlx_get_data_addr(mlx.image, &mlx.pixel_bits, &mlx.line_bytes, &mlx.endian);
	mlx.line_bytes /= 4;

	mandelbrot(&all);
	mlx_mouse_hook(mlx.mlx_win, &mouse_event, &all);
	mlx_key_hook(mlx.mlx_win, &kbd_event, &all);
	mlx_loop(mlx.mlx_ptr);
	return (EXIT_SUCCESS);
}
