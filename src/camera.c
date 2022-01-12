/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 23:16:20 by plefevre          #+#    #+#             */
/*   Updated: 2022/01/08 00:49:26 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

t_camera	*init_camera(void)
{
	t_camera	*camera;

	camera = malloc(sizeof(t_camera));
	if (!camera)
		return (0);
	camera->x = 0;
	camera->y = 0;
	camera->z = 0;
	camera->rx = 0;
	camera->ry = 0;
	camera->rz = 0;
	return (camera);
}

void	camera_center(t_camera *camera, t_linemap *map, int tx, int ty)
{
	int	max_x;
	int	max_y;

	max_x = map->size;
	max_y = map->size_tot;
	if (!max_y || !max_x)
		camera->zoom = 1;
	else if (max_x * ty > max_y * tx)
		camera->zoom = ((tx * 1.0 - 100.0) / max_x) / 1.5;
	else
		camera->zoom = ((ty * 1.0 - 100.0) / max_y) / 1.5;
}

void	apply_camera(t_camera *camera, t_m4 *mat)
{
	translate_mat(mat, camera->x, camera->y, camera->z);
	rotate_z_mat(mat, camera->rz);
	rotate_x_mat(mat, camera->rx);
	rotate_y_mat(mat, camera->ry);
	resize_mat(mat, camera->zoom, camera->zoom, camera->zoom);
}

void	reset_camera(t_camera *camera, t_linemap *map, int tx, int ty)
{
	camera->x = 0;
	camera->y = 0;
	camera->z = 0;
	camera->rx = 0;
	camera->ry = 0;
	camera->rz = 0;
	camera->zoom = 1;
	(void ) map;
	(void) tx;
	(void) ty;
	camera_center(camera, map, tx, ty);
}
