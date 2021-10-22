#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>

typedef struct data_s
{
  void *mlx_ptr;
  void *mlx_win;
  void *image;
  void *buffer;
  int x;
  int y;
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

int iterate(int x, int y, int maxiterations, data_t data, char *buffer, int endian, int line_bytes, int zoom)
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

	float x0;
	float y0;
	float offsetx = (float)-data.x / 2;
	float offsety = (float)-data.y / 2;
	float panx = -200;
	float pany = 0;
	x0 = (float)((float)x + offsetx + panx) / (float)zoom;
	y0 = (float)((float)y + offsety + pany) / (float)zoom;
	float xtemp;
	float rx = 0;
	float ry = 0;


	int iterations = 0;
	while (iterations < maxiterations && (rx * rx + ry * ry <= 4))
	{
		xtemp = rx * rx - ry * ry + x0;
		ry = 2 * rx * ry + y0;

		// Next iteration
		rx = xtemp;
		iterations++;
	}

	int color;
	if (iterations == maxiterations)
	{
		color = 0;
	} else
	{
		int index = (int)(((double)iterations / (double)(maxiterations - 1)) * 255);
//		printf("%d %d\n", iterations, maxiterations - 1);
		color = rgb_to_int(palette[index].r, palette[index].g, palette[index].b);
	}
	int pixel = (y * line_bytes) + (x * 4);
	if (endian == 1)        // Most significant (Alpha) byte first
	{
		buffer[pixel + 0] = (char)(color >> 24);
		buffer[pixel + 1] = (char)((color >> 16) & 0xFF);
		buffer[pixel + 2] = (char)((color >> 8) & 0xFF);
		buffer[pixel + 3] = (char)((color) & 0xFF);
	}
	else if (endian == 0)   // Least significant (Blue) byte first
	{
		buffer[pixel + 0] = (char)((color) & 0xFF);
		buffer[pixel + 1] = (char)((color >> 8) & 0xFF);
		buffer[pixel + 2] = (char)((color >> 16) & 0xFF);
		buffer[pixel + 3] = (char)(color >> 24);
	}
	return (0);
}

int main(void)
{
	data_t data;

	int x;
	int y;
	data.mlx_ptr = mlx_init();
	data.x = 2560;
	data.y = 1440;

	if (!(data.mlx_ptr))
		return (EXIT_FAILURE);
	data.mlx_win = mlx_new_window(data.mlx_ptr, data.x, data.y, "Hello world");
	if (!(data.mlx_win))
		return (EXIT_FAILURE);

	int zoom = 398;
	x = -1;
	char *bt;
	data.buffer = NULL;
	while (++zoom < 400)
	{
		data.image = mlx_new_image(data.mlx_ptr, data.x, data.y);
		int pixel_bits;
		int line_bytes;
		int endian;
//		bt = data.buffer;
		data.buffer = mlx_get_data_addr(data.image, &pixel_bits, &line_bytes, &endian);
//		if (bt)
//			free(bt);
		printf("%d\n", zoom);
		while (++x < data.x)
		{
			y = -1;
			while (++y < data.y)
//			mlx_pixel_put(data.mlx_ptr, data.mlx_win, x, y, rgb_to_int(230, 10, 124));
				iterate(x, y, 200, data, data.buffer, endian, line_bytes, zoom);
		}
		mlx_put_image_to_window(data.mlx_ptr, data.mlx_win, data.image, 0, 0);
		free(data.image);
	}
	mlx_loop(data.mlx_ptr);
	return (EXIT_SUCCESS);
}
