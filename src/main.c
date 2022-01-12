/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 18:51:35 by plefevre          #+#    #+#             */
/*   Updated: 2022/01/08 13:28:42 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include "linemap.h"
#include "ft3d.h"
#include "basic_drawer.h"
#include "camera.h"

int	key_hook(int keycode, t_data *vars)
{
	if (keycode == 65307)
		win_close(vars);
	return (0);
}

int	render(t_data *data)
{
	t_m4		mat;

	if (!data->win)
		win_close(data);
	set_identity(&mat);
	apply_camera(data->camera, &mat);
	draw_map(data, mat);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data		data;

	if (argc != 2)
		return (0);
	data.camera = init_camera();
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIN_TX, WIN_TY, "Fdf");
	data.img.img = mlx_new_image(data.mlx, WIN_TX, WIN_TY);
	data.img.addr = mlx_get_data_addr(data.img.img, &(data.img.bits_per_pixel),
			&(data.img.line_length), &(data.img.endian));
	data.bonus = 0;
	data.map = parse_file(argv[1]);
	if (!data.mlx || !data.camera || !data.map)
		win_close(&data);
	reset_camera(data.camera, data.map, WIN_TX, WIN_TY);
	data.camera->rz = 0.5;
	data.camera->rx = 1;
	mlx_put_image_to_window(data.mlx, data.win, data.img.img, 0, 0);
	mlx_key_hook(data.win, key_hook, &data);
	mlx_hook(data.win, 33, 1L << 17, win_close, &data);
	render(&data);
	mlx_loop(data.mlx);
}
