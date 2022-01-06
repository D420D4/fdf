//
// Created by plefevre on 1/6/22.
//

#include "camera.h"


t_camera *camera_init() {
	t_camera *camera;

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

int camera_center(t_camera *camera, t_linemap *map) {
	int maxX;
	int maxY;

	maxX = map->size;
	maxY = map->size_tot;

	camera->x = WIN_TAILLEX / 2 - maxX / 2;
	camera->y = WIN_TAILLEY / 2 - maxY / 2;

	if (!maxY || !maxX)
		return (0);
	if (maxX * WIN_TAILLEY > maxY * WIN_TAILLEX)
		return (WIN_TAILLEX / maxX);
	else
		return (WIN_TAILLEY / maxY);
}