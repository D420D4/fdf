/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 18:51:35 by plefevre          #+#    #+#             */
/*   Updated: 2021/12/13 20:06:55 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include "linemap.h"
#include "ft_3d.h"


typedef struct s_img {
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_img;

typedef struct s_data {
	void *mlx;
	void *win;
	t_img img;
	t_linemap *map;
} t_data;

void my_mlx_pixel_put(t_img *img, int x, int y, int color) {
	char *dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

int key_hook(int keycode, t_data *vars) {
	printf("Hello from key_hook! %d \n", keycode);
	if (keycode == 65307)
		mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

int renderFrame(t_data *img) {
	static int k = 0;

	k++;
	(void) img;
	printf("%d\n", k);

	return (0);
}

int ft_abs(int n) {
	if (n > 0)
		return (n);
	return (-n);
}

int ft_max(int n1, int n2) {
	if (n1 > n2)
		return (n1);
	return (n2);
}

int drawline_win(t_data *data, t_point t1, t_point t2) {
	int d1 = ft_abs(t1.x - t2.x);
	int d2 = ft_abs(t1.y - t2.y);
	int max = ft_max(d1, d2);
	int i;

	while (i < max) {
		my_mlx_pixel_put(&data->img,
						 t1.x + (t2.x - t1.x) * i / max,
						 t1.y + (t2.y - t1.y) * i / max,
						 0x00FF0000);
		i++;
	}

	return (0);
}


int drawline(t_data *data, t_point t1, t_point t2, t_m4 mat)
{
	t_point bt1;
	t_point bt2;

	mult_matvec(mat, t1, &bt1);
	mult_matvec(mat, t2, &bt2);
	drawline_win(data, bt1, bt2);

	return (0);
}

int draw_row(t_data *data, t_m4 mat, t_linemap line, int y) {
	int i;
	t_point t1;
	t_point t2;

	i = 0;
	while (i < line.size - 1) {
		t1 = point_new(i, y, line.line[i]);
		t2 = point_new(i + 1, y, line.line[i + 1]);
		drawline(data, t1, t2, mat);
		i++;
	}
	return (0);
}

int render(t_data *data) {
	static t_m4 mat;
	t_linemap *linemap;
	int i;

	i = 0;
	set_identity(&mat);

	if (!data->win)
		return (0);

	linemap = data->map;
	while (linemap) {
		draw_row(data, mat, *linemap, i);
		i++;
		linemap = linemap->next;
	}


	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);

//    printf(".");
	return (1);
}

int main() {
	t_data data;

	t_linemap *map;

	map = parseFile("maps/test_maps/42.fdf");
	line_print(map);

	data.map = map;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 500, 500, "Fdf");

	data.img.img = mlx_new_image(data.mlx, 500, 500);
	data.img.addr = mlx_get_data_addr(data.img.img, &(data.img.bits_per_pixel),
									  &(data.img.line_length), &(data.img.endian));


	mlx_put_image_to_window(data.mlx, data.win, data.img.img, 0, 0);

	mlx_key_hook(data.win, key_hook, &data);

	mlx_loop_hook(data.mlx, render, &data);

	mlx_loop(data.mlx);
}
