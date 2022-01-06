/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 23:16:20 by plefevre          #+#    #+#             */
/*   Updated: 2022/01/06 23:18:36 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

t_camera	*camera_init(void)
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

float	camera_center(t_camera *camera, t_linemap *map)
{
	int	max_x;
	int	max_y;

	max_x = map->size;
	max_y = map->size_tot;
	camera->x = WIN_TX / 2;
	camera->y = WIN_TY / 2;
	if (!max_y || !max_x)
		return (0);
	if (max_x * WIN_TY > max_y * WIN_TX)
		return ((WIN_TX * 1.0 - 100.0) / max_x);
	else
		return ((WIN_TY * 1.0 - 100.0) / max_y);
}

void	apply_camera(t_camera *camera, t_m4 *mat, float zoom)
{
	translate_mat(mat, camera->x, camera->y, camera->z);
	rotate_z_mat(mat, camera->rz);
	rotate_x_mat(mat, camera->rx);
	rotate_y_mat(mat, camera->ry);
	resize_mat(mat, zoom, zoom, zoom);
}
