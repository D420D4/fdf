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
#include "fdf.h"
#include "linemap.h"
#include "ft_3d.h"
#include "maths.h"
#include "basic_drawer.h"
#include "camera.h"
#include "libft.h"

int key_hook(int keycode, t_data *vars) {
	printf("Hello from key_hook! %d \n", keycode);
	if (keycode == 65307)
		mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

void clear_win(t_data *data) {
    ft_bzero(data->img.addr, WIN_TAILLEX * WIN_TAILLEY * 4);
}


int render(t_data *data) {
    t_m4 mat;
    t_linemap *linemap;
	static t_camera *camera;
	static int zoom;
	int i;

	zoom = 10;
	camera = camera_init();
	if (!camera)
		return (0);
    if (!data->win)
	{
		free(camera);
		return (0);
	}
	zoom = camera_center(camera, data->map);

    i = 0;
    clear_win(data);
    set_identity(&mat);
    perspective_mat(&mat, 1, 1, 1.0, 1.1);
	translate_mat(&mat, camera->x, camera->y, camera->z);
	rotateZ_mat(&mat, camera->rz);
	rotateX_mat(&mat, camera->rx);
	rotateY_mat(&mat, camera->ry);
	resize_mat(&mat, zoom, zoom, zoom);
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

int main(int argc, char **argv) {
    t_data data;

    t_linemap *map;

    if (argc != 2)
        return (0);
    map = parse_file(argv[1]);
	if (!map)
		return (0);
    //	line_print(map);

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

    mlx_loop_hook(data.mlx, render, &data);

    mlx_loop(data.mlx);
}
