#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mlx.h>
#include "libft/libft.h"

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

typedef struct fract_s
{
  double zoom;
  double dx;
  double dy;
  double xMin;
  double xMax;
  double yMin;
  double yMax;
} fract_t;

typedef struct colour_s
{
  int sr;
  int sg;
  int sb;
  int er;
  int eg;
  int eb;
} colour_t;

typedef struct all_s
{
  mlx_t *mlx;
  colour_t *colour;
  fract_t *fractal;
} all_t;

unsigned int rgb_to_int(unsigned int r, unsigned int g, unsigned int b)
{
	unsigned int color = 0;
	color |= b;
	color |= g << 8;
	color |= r << 16;
	return (color);
}

unsigned int pickColor(int max_iterations, int iterations, colour_t *c)
{
 	int v;
 	int r;
	int g;
	int b;

	if ( iterations == max_iterations)
		return (0);
	v = (int)log((double)iterations / (double)max_iterations * 255);

	r = (int)(((double)c->er - (double)c->sr) * v / log(255));
	g = (int)(((double)c->eg - (double)c->sg) * v / log(255));
	b = (int)(((double)c->eb - (double)c->sb) * v / log(255));

	if (c->er > c->sr)
		r += c->sr;
	else
		r += c->er;
	if (c->eg > c->sg)
		g += c->sg;
	else
		g += c->eg;
	if (c->eb > c->sb)
		b += c->sb;
	else
		b += c->eb;

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
	return (pickColor(maxiterations, iterations, a->colour));
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
			colour = (int)iterate_mandelbrot(500, dx + a->fractal->xMin,dy + a->fractal->yMin, a);
//			printf("%d dx:%f dy:%f\n", it, dx, dy);
			a->mlx->buffer[pixel++] = colour;
			dx += a->fractal->dx;
		}
		dy += a->fractal->dy;
	}
	mlx_put_image_to_window(a->mlx->mlx_ptr, a->mlx->mlx_win, a->mlx->image, 0, 0);
	return (1);
}


int mandelbrot(all_t *a)
{
	a->fractal->xMin = -2.0;
	a->fractal->xMax = 0.47;
	a->fractal->yMin = -1.12;
	a->fractal->yMax = 1.12;

	a->fractal->dx = (a->fractal->xMax - a->fractal->xMin) / a->mlx->width;
	a->fractal->dy = (a->fractal->yMax - a->fractal->yMin) / a->mlx->height;

	update_image(a);
	return (1);
}

int julia(all_t *a)
{
	a->fractal->xMin = -2.0;
	a->fractal->xMax = 0.47;
	a->fractal->yMin = -1.12;
	a->fractal->yMax = 1.12;

	a->fractal->dx = (a->fractal->xMax - a->fractal->xMin) / a->mlx->width;
	a->fractal->dy = (a->fractal->yMax - a->fractal->yMin) / a->mlx->height;

	update_image(a);
	return (1);
}

void init_fractal(mlx_t *mlx, int i)
{
	(void)i;
	mlx->height = 896;
	mlx->width = 988;
}

all_t *get_all()
{
	all_t *all;
	mlx_t *mlx;
	colour_t *colour;
	fract_t *fractal;

	all = (all_t *)malloc(sizeof(all_t));
	if (!all)
		return (NULL);
	mlx = (mlx_t *)malloc(sizeof(mlx_t));
	if (!mlx)
		return (NULL);
	colour = (colour_t *)malloc(sizeof(colour_t));
	if (!colour)
	{
		free(all);
		return (NULL);
	}
	fractal = (fract_t *)malloc(sizeof(fract_t));
	if (!fractal)
	{
		free(all);
		free(colour);
		return (NULL);
	}
	all->mlx = mlx;
	all->fractal = fractal;
	all->colour = colour;
	return (all);
}

int init(int i)
{
	all_t *all;

	all = get_all();
	all->mlx->mlx_ptr = mlx_init();
	init_fractal(all->mlx, i);
	all->colour->sr = 206;
	all->colour->sg = 41;
	all->colour->sb = 0;
	all->colour->er = 175;
	all->colour->eg = 206;
	all->colour->eb = 0;
	all->fractal->zoom = 1.1;
	if (!(all->mlx->mlx_ptr))
		return (EXIT_FAILURE);
	all->mlx->mlx_win = mlx_new_window(all->mlx->mlx_ptr, all->mlx->width, all->mlx->height, "Hello world");
	if (!(all->mlx->mlx_win))
		return (EXIT_FAILURE);
	all->mlx->image = mlx_new_image(all->mlx->mlx_ptr, all->mlx->width, all->mlx->height);
	all->mlx->buffer = (int *)mlx_get_data_addr(all->mlx->image, &all->mlx->pixel_bits, &all->mlx->line_bytes, &all->mlx->endian);
	all->mlx->line_bytes /= 4;
	if (i == 1)
		mandelbrot(all);
	else
		julia(all);
	mlx_mouse_hook(all->mlx->mlx_win, &mouse_event, &all);
	mlx_key_hook(all->mlx->mlx_win, &kbd_event, &all);
	mlx_loop(all->mlx->mlx_ptr);
	return (EXIT_SUCCESS);
}


int main(int argc, char **argv)
{
	int	i;

	if (argc != 2)
	{
		ft_putendl_fd("usage: fractol", 1);
		return (1);
	}
	else
	{
		i = 0;
		if (ft_strncmp(argv[1], "julia", 5) == 0)
			i = 2;
		else if (ft_strncmp(argv[1], "mandelbrot", 10) == 0)
			i = 1;
		if (i != 0)
			init(i);
	}
}
