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
#include "ft3d.h"
#include "maths.h"
#include "basic_drawer.h"
#include "camera.h"
#include "libft.h"
#include "xpm.h"

int	key_hook(int keycode, t_data *vars)
{
	printf("Hello from key_hook! %d \n", keycode);
	if (keycode == 65307)
		win_close(vars);
	return (0);
}

int	render(t_data *data)
{
	t_m4			mat;
	t_linemap		*linemap;
	t_camera		*camera;
	float			zoom;
	int				i;

	camera = camera_init();
	zoom = camera_center(camera, data->map) / 1.5;
	camera->rz = 0.5;
	camera->rx = 1;
	if (!camera || !data->win)
		return (0);
	i = 0;
	set_identity(&mat);
	perspective_mat(&mat, 1, 1, 1.1);
	apply_camera(camera, &mat, zoom);
	linemap = data->map;
	while (linemap && linemap->line)
	{
		draw_row(data, mat, *linemap, i++);
		linemap = linemap->next;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	free (camera);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_linemap	*map;

	if (argc != 2)
		return (0);
	map = parse_file(argv[1]);
	if (!map)
		return (0);
	data.map = map;
	data.mlx = mlx_init();
	if (!data.mlx)
		return (0);
	data.win = mlx_new_window(data.mlx, WIN_TX, WIN_TY, "Fdf");
	data.img.img = mlx_new_image(data.mlx, WIN_TX, WIN_TY);
	data.img.addr = mlx_get_data_addr(data.img.img, &(data.img.bits_per_pixel),
			&(data.img.line_length), &(data.img.endian));
	mlx_put_image_to_window(data.mlx, data.win, data.img.img, 0, 0);
	mlx_key_hook(data.win, key_hook, &data);
	mlx_hook(data.win, 33, 1L << 17, win_close, &data);
	render(&data);
	mlx_loop(data.mlx);
}
