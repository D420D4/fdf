/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 18:51:35 by plefevre          #+#    #+#             */
/*   Updated: 2022/01/08 01:18:23 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../minilibx/mlx.h"
#include "../includes/fdf.h"
#include "../includes/linemap.h"
#include "../includes/ft3d.h"
#include "../includes/maths.h"
#include "../includes/basic_drawer.h"
#include "../includes/camera.h"
#include "../libft/libft.h"
#include "../includes/xpm.h"
#include "../includes/bonus_functions.h"

int	key_hook(int keycode, t_data *vars)
{
	if (keycode == 65307)
		win_close(vars);
	key_bonus_down(keycode, vars);
	return (0);
}

int	key_hook_up(int keycode, t_data *vars)
{
	key_bonus_up(keycode, vars);
	return (0);
}

void	render_simulateur(t_m4 *mat, t_data *data)
{
	perspective_mat(mat, 1, 2);
	rotate_x_mat(mat, data->bonus->simulateur->angle_x);
	rotate_z_mat(mat, data->bonus->simulateur->angle_y);
	rotate_y_mat(mat, data->bonus->simulateur->angle_z);
	if (data->bonus->stars)
		draw_stars(mat, data->bonus->stars, data);
	translate_mat(mat,
		data->bonus->simulateur->px,
		data->bonus->simulateur->py,
		data->bonus->simulateur->pz);
	update_simulateur(data->bonus->simulateur);
}

int	render(t_data *data)
{
	t_m4	mat;

	if (!data->win)
		win_close(data);
	if (!clear_win(data))
		win_close(data);
	set_identity(&mat);
	if (data->bonus->simulateur)
		render_simulateur(&mat, data);
	else
	{
		if (data->bonus->projection == 1)
			perspective_mat(&mat, 1, 2);
		apply_camera(data->camera, &mat);
		update_camera(data);
		if (data->bonus->projection == 1)
			translate_mat(&mat, 0, 0, data->bonus->object_z);
	}
	draw_map(data, mat);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (0);
	data.map = parse_file(argv[1]);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIN_TX, WIN_TY, "Fdf");
	data.img.img = mlx_new_image(data.mlx, WIN_TX, WIN_TY);
	data.img.addr = mlx_get_data_addr(data.img.img, &(data.img.bits_per_pixel),
			&(data.img.line_length), &(data.img.endian));
	data.bonus = init_bonus();
	data.camera = init_camera();
	if (!data.mlx || !data.camera || !data.map || !data.bonus)
		win_close(&data);
	reset_camera(data.camera, data.map, WIN_TX, WIN_TY);
	mlx_do_key_autorepeatoff(data.mlx);
	mlx_put_image_to_window(data.mlx, data.win, data.img.img, 0, 0);
	mlx_hook(data.win, 2, 1L << 0, &key_hook, &data);
	mlx_hook(data.win, 3, 1L << 1, &key_hook_up, &data);
	mlx_hook(data.win, 33, 1L << 17, win_close, &data);
	mlx_loop_hook(data.mlx, render, &data);
	print_intro_text();
	mlx_loop(data.mlx);
}
