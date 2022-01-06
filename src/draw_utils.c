//
// Created by plefevre on 1/6/22.
//
#include "fdf.h"
#include "maths.h"

void my_mlx_pixel_put(t_img *img, int x, int y, int z, int color) {
	char *dst;

	int dist;
	dist = ft_sqrt(x * x + y * y + z * z) + 1;
	if (dist == 1)
		return;
	//x = 250 + 250 * (1 + x) / dist;
	//y = 250 + 250 * (1 + y) / dist;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}