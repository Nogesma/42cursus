/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 03:38:40 by msegrans          #+#    #+#             */
/*   Updated: 2021/11/08 03:38:41 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

//int	error(void)
//{
//	ft_putendl_fd("usage: fractol [mandelbrot/julia] {-1.0/1.0} {-1.0/1.0}", 1);
//	return (1);
//}

//void	start_hooks(t_all *all)
//{
//	mlx_mouse_hook(all->mlx->mlx_win, &mouse_event, all);
//	mlx_hook(all->mlx->mlx_win, 6, 1L << 8, &click_and_drag, all);
//	mlx_hook(all->mlx->mlx_win, 5, 1L << 3, &release, all);
//	mlx_key_hook(all->mlx->mlx_win, &kbd_event, all);
//	mlx_loop(all->mlx->mlx_ptr);
//}

#include <math.h>
#include <stdio.h>

typedef struct s_vec3
{
  double x;
  double y;
  double z;
} t_vec3;

typedef t_vec3 t_point;
typedef t_vec3 t_colour;

typedef struct s_ray
{
  t_vec3 direction;
  t_point origin;
} t_ray;

t_vec3 mult3(t_vec3 a, double n)
{
	a.x *= n;
	a.y *= n;
	a.z *= n;
	return (a);
}

t_vec3 div3(t_vec3 a, double n)
{
	a.x /= n;
	a.y /= n;
	a.z /= n;
	return (a);
}

t_vec3 plus3(t_vec3 a, double n)
{
	a.x += n;
	a.y += n;
	a.z += n;
	return (a);
}

t_vec3 min3(t_vec3 a, double n)
{
	a.x -= n;
	a.y -= n;
	a.z -= n;
	return (a);
}

t_vec3 min_vec(t_vec3 a, t_vec3 b)
{
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
	return (a);
}

t_vec3 plus_vec(t_vec3 a, t_vec3 b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return (a);
}

double dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}




//int	has_intersection(int x, int y)
//{
//	t_vector cam;
//	t_vector circle;
//
//	cam.x = 0;
//	cam.y = 0;
//
//	circle.x = 1;
//	circle.y = 1;
//
//	int r = 1;
//	return (1);
//
//}

double len3(t_vec3 a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_vec3 unit_vector(t_vec3 a)
{
	return (div3(a, len3(a)));
}

//int	colour()
//{
//	int	c;
//
//	c = (color) & 0xFF;
//	c = (color >> 8) & 0xFF;
//	c = (color >> 16) & 0xFF;
//	buffer[pixel + 3] = (color >> 24);
//}


int	hit_sphere(const t_point center, double radius, t_ray r) {
	t_vec3 oc = min_vec(r.origin, center);
	double a = dot(r.direction, r.direction);
	double b = 2.0 * dot(oc, r.direction);
	double c = dot(oc, oc) - radius * radius;
	double discriminant = b * b - 4 * a * c;
	return (discriminant > 0);
}

int ray_color(t_ray r)
{
	t_point sphere = {0, 0, -1};
	if (hit_sphere(sphere, 0.5, r))
		return (0xFFFFFF);
	t_vec3 unit_direction = unit_vector(r.direction);
	double t = 0.5 * (unit_direction.y + 1.0);
	return (int)((1.0 - t) * 0xFFFFFF + t * 0xFF0000);
}

int main(void)
{
	const double aspect_ratio = 16.0 / 9.0;
	const int img_width = 480;
	const int img_height = (int)(img_width / aspect_ratio);

	double viewport_height = 2.0;
	double viewport_width = aspect_ratio * viewport_height;

	t_vec3 focal_length = {0, 0, 1};
	t_vec3 origin = {0, 0, 0};
	t_vec3 horizontal = {viewport_width, 0, 0};
	t_vec3 vertical = {0, viewport_height, 0};

	t_vec3 lower_left_corner = min_vec(
		min_vec(min_vec(origin, div3(horizontal, 2)), div3(vertical, 2)),
		focal_length);


	printf("%dx%d\n", img_width, img_height);

	void *mlx = mlx_init();
	void *win = mlx_new_window(mlx, img_width, img_height,
							   "Tutorial Window - Create Image");

	void *image = mlx_new_image(mlx, img_width, img_height);

	int pixel_bits;
	int line_bytes;
	int endian;
	int *buffer = (int *) mlx_get_data_addr(image, &pixel_bits, &line_bytes,
											&endian);
	printf("%d\n", endian);

	int px = 0;
	for (int y = 0; y < img_height; ++y)
		for (int x = 0; x < img_width; ++x)
		{
			double w = (double) x / img_width;
			double h = (double) y / img_height;

			t_ray ray;
			ray.origin = origin;
			ray.direction = min_vec(
				plus_vec(plus_vec(lower_left_corner, mult3(horizontal, w)),
						 mult3(vertical, h)), origin);
			buffer[px++] = ray_color(ray);
		}
	mlx_put_image_to_window(mlx, win, image, 0, 0);
	mlx_loop(mlx);

}
