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
  float dx;
  float dy;
  float xMin;
  float xMax;
  float yMin;
  float yMax;
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
	return (iterations);
}

int set_pixel_value(data_t *data, int pixel, int iterations, int maxiterations)
{
	rgb palette[256] = {{.r = 24, .g = 16, .b = 0},
						{.r = 27, .g = 16, .b = 0},
						{.r =30, .g =16, .b =0},
						{.r =33, .g =16, .b =0},
						{.r =36, .g =16, .b =0},
						{.r =39, .g =16, .b =0},
						{.r =42, .g =16, .b =0},
						{.r =45, .g =16, .b =0},
						{.r =48, .g =16, .b =0},
						{.r =51, .g =16, .b =0},
						{.r =54, .g =16, .b =0},
						{.r =57, .g =16, .b =0},
						{.r =60, .g =16, .b =0},
						{.r =63, .g =16, .b =0},
						{.r =66, .g =16, .b =0},
						{.r =69, .g =16, .b =0},
						{.r =72, .g =16, .b =0},
						{.r =75, .g =16, .b =0},
						{.r =78, .g =16, .b =0},
						{.r =81, .g =16, .b =0},
						{.r =84, .g =16, .b =0},
						{.r =87, .g =16, .b =0},
						{.r =90, .g =16, .b =0},
						{.r =93, .g =16, .b =0},
						{.r =96, .g =16, .b =0},
						{.r =99, .g =16, .b =0},
						{.r =102, .g =16, .b =0},
						{.r =105, .g =16, .b =0},
						{.r =108, .g =16, .b =0},
						{.r =111, .g =16, .b =0},
						{.r =114, .g =16, .b =0},
						{.r =117, .g =16, .b =0},
						{.r =120, .g =16, .b =0},
						{.r =123, .g =16, .b =0},
						{.r =126, .g =16, .b =0},
						{.r =129, .g =16, .b =0},
						{.r =132, .g =16, .b =0},
						{.r =135, .g =16, .b =0},
						{.r =138, .g =16, .b =0},
						{.r =141, .g =16, .b =0},
						{.r =144, .g =16, .b =0},
						{.r =147, .g =16, .b =0},
						{.r =150, .g =16, .b =0},
						{.r =153, .g =16, .b =0},
						{.r =156, .g =16, .b =0},
						{.r =159, .g =16, .b =0},
						{.r =162, .g =16, .b =0},
						{.r =165, .g =16, .b =0},
						{.r =168, .g =16, .b =0},
						{.r =171, .g =16, .b =0},
						{.r =174, .g =16, .b =0},
						{.r =177, .g =16, .b =0},
						{.r =180, .g =16, .b =0},
						{.r =183, .g =16, .b =0},
						{.r =186, .g =16, .b =0},
						{.r =189, .g =16, .b =0},
						{.r =192, .g =16, .b =0},
						{.r =195, .g =16, .b =0},
						{.r =198, .g =16, .b =0},
						{.r =201, .g =16, .b =0},
						{.r =204, .g =16, .b =0},
						{.r =207, .g =16, .b =0},
						{.r =210, .g =16, .b =0},
						{.r =213, .g =16, .b =0},
						{.r =216, .g =16, .b =0},
						{.r =216, .g =19, .b =0},
						{.r =216, .g =22, .b =0},
						{.r =216, .g =25, .b =0},
						{.r =216, .g =28, .b =0},
						{.r =216, .g =31, .b =0},
						{.r =216, .g =34, .b =0},
						{.r =216, .g =37, .b =0},
						{.r =216, .g =40, .b =0},
						{.r =216, .g =43, .b =0},
						{.r =216, .g =46, .b =0},
						{.r =216, .g =49, .b =0},
						{.r =216, .g =52, .b =0},
						{.r =216, .g =55, .b =0},
						{.r =216, .g =58, .b =0},
						{.r =216, .g =61, .b =0},
						{.r =216, .g =64, .b =0},
						{.r =216, .g =67, .b =0},
						{.r =216, .g =70, .b =0},
						{.r =216, .g =73, .b =0},
						{.r =216, .g =76, .b =0},
						{.r =216, .g =79, .b =0},
						{.r =216, .g =82, .b =0},
						{.r =216, .g =85, .b =0},
						{.r =216, .g =88, .b =0},
						{.r =216, .g =91, .b =0},
						{.r =216, .g =94, .b =0},
						{.r =216, .g =97, .b =0},
						{.r =216, .g =100, .b =0},
						{.r =216, .g =103, .b =0},
						{.r =216, .g =106, .b =0},
						{.r =216, .g =109, .b =0},
						{.r =216, .g =112, .b =0},
						{.r =216, .g =115, .b =0},
						{.r =216, .g =118, .b =0},
						{.r =216, .g =121, .b =0},
						{.r =216, .g =124, .b =0},
						{.r =216, .g =127, .b =0},
						{.r =216, .g =130, .b =0},
						{.r =216, .g =133, .b =0},
						{.r =216, .g =136, .b =0},
						{.r =216, .g =139, .b =0},
						{.r =216, .g =142, .b =0},
						{.r =216, .g =145, .b =0},
						{.r =216, .g =148, .b =0},
						{.r =216, .g =151, .b =0},
						{.r =216, .g =154, .b =0},
						{.r =216, .g =157, .b =0},
						{.r =216, .g =160, .b =0},
						{.r =216, .g =163, .b =0},
						{.r =216, .g =166, .b =0},
						{.r =216, .g =169, .b =0},
						{.r =216, .g =172, .b =0},
						{.r =216, .g =175, .b =0},
						{.r =216, .g =178, .b =0},
						{.r =216, .g =181, .b =0},
						{.r =216, .g =184, .b =0},
						{.r =216, .g =187, .b =0},
						{.r =216, .g =190, .b =0},
						{.r =216, .g =193, .b =0},
						{.r =216, .g =196, .b =0},
						{.r =216, .g =199, .b =0},
						{.r =216, .g =202, .b =0},
						{.r =216, .g =205, .b =0},
						{.r =216, .g =208, .b =0},
						{.r =216, .g =208, .b =3},
						{.r =216, .g =208, .b =6},
						{.r =216, .g =208, .b =9},
						{.r =216, .g =208, .b =12},
						{.r =216, .g =208, .b =15},
						{.r =216, .g =208, .b =18},
						{.r =216, .g =208, .b =21},
						{.r =216, .g =208, .b =24},
						{.r =216, .g =208, .b =27},
						{.r =216, .g =208, .b =30},
						{.r =216, .g =208, .b =33},
						{.r =216, .g =208, .b =36},
						{.r =216, .g =208, .b =39},
						{.r =216, .g =208, .b =42},
						{.r =216, .g =208, .b =45},
						{.r =216, .g =208, .b =48},
						{.r =216, .g =208, .b =51},
						{.r =216, .g =208, .b =54},
						{.r =216, .g =208, .b =57},
						{.r =216, .g =208, .b =60},
						{.r =216, .g =208, .b =63},
						{.r =216, .g =208, .b =66},
						{.r =216, .g =208, .b =69},
						{.r =216, .g =208, .b =72},
						{.r =216, .g =208, .b =75},
						{.r =216, .g =208, .b =78},
						{.r =216, .g =208, .b =81},
						{.r =216, .g =208, .b =84},
						{.r =216, .g =208, .b =87},
						{.r =216, .g =208, .b =90},
						{.r =216, .g =208, .b =93},
						{.r =216, .g =208, .b =96},
						{.r =216, .g =208, .b =99},
						{.r =216, .g =208, .b =102},
						{.r =216, .g =208, .b =105},
						{.r =216, .g =208, .b =108},
						{.r =216, .g =208, .b =111},
						{.r =216, .g =208, .b =114},
						{.r =216, .g =208, .b =117},
						{.r =216, .g =208, .b =120},
						{.r =216, .g =208, .b =123},
						{.r =216, .g =208, .b =126},
						{.r =216, .g =208, .b =129},
						{.r =216, .g =208, .b =132},
						{.r =216, .g =208, .b =135},
						{.r =216, .g =208, .b =138},
						{.r =216, .g =208, .b =141},
						{.r =216, .g =208, .b =144},
						{.r =216, .g =208, .b =147},
						{.r =216, .g =208, .b =150},
						{.r =216, .g =208, .b =153},
						{.r =216, .g =208, .b =156},
						{.r =216, .g =208, .b =159},
						{.r =216, .g =208, .b =162},
						{.r =216, .g =208, .b =165},
						{.r =216, .g =208, .b =168},
						{.r =216, .g =208, .b =171},
						{.r =216, .g =208, .b =174},
						{.r =216, .g =208, .b =177},
						{.r =216, .g =208, .b =180},
						{.r =216, .g =208, .b =183},
						{.r =216, .g =208, .b =186},
						{.r =216, .g =208, .b =189},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192},
						{.r =216, .g =208, .b =192}};

	int color;
	if (iterations == maxiterations)
		color = 0;
	else
	{
		int index = (int)(((double)iterations / (double)(maxiterations - 1)) * 255);
//		printf("%d %d\n", iterations, maxiterations - 1);
		color = rgb_to_int(palette[index].r, palette[index].g, palette[index].b);
	}
	data->buffer[pixel] = (color);
	return (0);
}

double *linspace(double start, double end, int size)
{
	double step;
	int i;
	double val;
	double *dest;

	dest = (double *)malloc(size * sizeof(double));
	if (!dest)
		return (NULL);
	step = (end - start) / size;
	i = -1;
	val = start;
	while (++i < size)
	{
		dest[i] = val;
		val += step;
	}
	return (dest);
}

int	update_image(data_t *data)
{
	int	x;
	int	y;
	int	pixel;
	float dx;
	float dy;
	int it;

	dy = 0;
//		bt = data.buffer;
//		if (bt)
//			free(bt);
	y = -1;
	pixel = 0;

	while (++y < data->y)
	{
		x = -1;
		dx = 0;
		while (++x < data->x)
		{
			it = iterateEquation(100, dx + data->xMin,dy + data->yMin);
//			printf("%d dx:%f dy:%f\n", it, dx, dy);
			set_pixel_value(data, pixel, it, 100);
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
	data.x = 640;
	data.y = 360;
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
