//
// Created by plefevre on 1/6/22.
//

#ifndef CAMERA_H
#define CAMERA_H

#include <stdlib.h>
#include "fdf.h"

typedef struct s_camera
{
	float x;
	float y;
	float z;
	float rx;
	float ry;
	float rz;
} t_camera;

t_camera *camera_init();
int camera_center(t_camera *camera, t_linemap *map);

#endif
