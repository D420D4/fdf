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

#include <stdbool.h>
#include "mlx.h"
#include "includes/fdf.h"
#include "includes/linemap.h"
#include "includes/ft3d.h"
#include "includes/maths.h"
#include "includes/basic_drawer.h"
#include "includes/camera.h"
#include "libft.h"
#include "includes/xpm.h"

int free_all(t_data *vars)
{
	if (vars->mlx && vars->img.img)
		mlx_destroy_image(vars->mlx, vars->img.img);
	if (vars->mlx && vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
		mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	return (0);
}

int win_close(t_data *vars)
{
	exit(free_all(vars));
}

int key_hook(int keycode, t_data *vars)
{
	printf("Hello from key_hook! %d \n", keycode);
	if (keycode == 65307)
		win_close(vars);
	return (0);
}

int clear_win(t_data *data)
{
	ft_bzero(data->img.addr, WIN_TAILLEX * WIN_TAILLEY * 4);
	return (1);
}

int render(t_data *data)
{
	t_m4 mat;
	t_linemap *linemap;
	static t_camera *camera = 0;
	static float zoom;
	int i;

	zoom = 10;
	if (!camera)
	{
		camera = camera_init();
		zoom = camera_center(camera, data->map) / 1.5;
		camera->rz = 0.5;
		camera->rx = 1;
	}
	if (!camera)
		return (0);
	if (!data->win)
	{
		free(camera);
		return (0);
	}


	i = 0;
	if (!clear_win(data))
		win_close(data);
	set_identity(&mat);
	perspective_mat(&mat, 1, 1, 1.0, 1.1);
	translate_mat(&mat, camera->x, camera->y, camera->z);
	rotateZ_mat(&mat, camera->rz);
	rotateX_mat(&mat, camera->rx);
	rotateY_mat(&mat, camera->ry);
	resize_mat(&mat, zoom, zoom, zoom);
	camera->rx+=.1;
	linemap = data->map;
	while (linemap && linemap->line)
	{
		draw_row(data, mat, *linemap, i);
		i++;
		linemap = linemap->next;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);

	//    printf(".");
	return (1);
}

int main(int argc, char **argv)
{
	t_data data;
	t_linemap *map;

	if (argc != 2)
		return (0);
	map = parse_file(argv[1]);
	if (!map)
		return (0);
	//	line_print(map);

	if (!generate_black_xpm("black.xpm"))
		return (0);

	data.map = map;
	data.mlx = mlx_init();
	if (!data.mlx)
		return (0);
	data.win = mlx_new_window(data.mlx, WIN_TAILLEX, WIN_TAILLEY, "Fdf");

	data.img.img = mlx_new_image(data.mlx, WIN_TAILLEX, WIN_TAILLEY);
	data.img.addr = mlx_get_data_addr(data.img.img, &(data.img.bits_per_pixel),
									  &(data.img.line_length), &(data.img.endian));

	mlx_put_image_to_window(data.mlx, data.win, data.img.img, 0, 0);

	mlx_key_hook(data.win, key_hook, &data);

	mlx_hook(data.win, 33, 1L << 17, win_close, &data);

	render(&data);
//	mlx_loop_hook(data.mlx, render, &data);

	mlx_loop(data.mlx);
}
