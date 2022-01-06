//
// Created by plefevre on 1/6/22.
//
#include "ft_3d.h"
#include "fdf.h"
#include "draw_utils.h"
#include "maths.h"

static int ressere_left(t_point2 *t1, t_point2 *t2) {
	if ((t1->x < 0 && t2->x < 0) || (t1->x > WIN_TAILLEX && t2->x > WIN_TAILLEX))
		return (0);
	if (t1->x < 0) {
		t1->y = t2->y + t2->x * ((t2->y - t1->y) / (t1->x - t2->x));
		t1->x = 0;
	}
	if (t1->x > WIN_TAILLEX) {
		t1->y = t2->y + (t2->x - WIN_TAILLEX) * ((t2->y - t1->y) / (t1->x - t2->x));
		t1->x = WIN_TAILLEX;
	}
	if ((t1->y < 0 && t2->y < 0) || (t1->y > WIN_TAILLEY && t2->y > WIN_TAILLEY))
		return (0);
	if (t1->y < 0) {
		t1->x = t2->x + t2->y * ((t2->x - t1->x) / (t1->y - t2->y));
		t1->y = 0;
	}
	if (t1->y > WIN_TAILLEY) {
		t1->x = t2->x + (t2->y - WIN_TAILLEY) * ((t2->x - t1->x) / (t1->y - t2->y));
		t1->y = WIN_TAILLEY;
	}
	return (1);
}

static int ressere(t_point2 *t1, t_point2 *t2) {
	return (ressere_left(t1, t2) && ressere_left(t2, t1));
}

static int drawline_win(t_data *data, t_point2 t1, t_point2 t2) {
	if (!ressere(&t1, &t2))
		return (0);
	int d1 = ft_abs(t1.x - t2.x);
	int d2 = ft_abs(t1.y - t2.y);
	int max = ft_max(d1, d2);
	int i;
	int x;
	int y;
	int z;

	i = 0;
	while (i < max) {

		x = t1.x + (t2.x - t1.x) * i / max;
		y = t1.y + (t2.y - t1.y) * i / max;
		z = t1.z + (t2.z - t1.z) * i / max;
		if (x >= 0 && x < WIN_TAILLEX && y >= 0 && y < WIN_TAILLEY)
			my_mlx_pixel_put(&(data->img),
							 x, y, z,
							 0x00FFFFFF);
		i++;
	}

	return (1);
}

int drawline(t_data *data, t_point t1, t_point t2, t_m4 mat) {
	t_point2 bt1;
	t_point2 bt2;

	mult_matvec(mat, t1, &bt1);
	mult_matvec(mat, t2, &bt2);
	drawline_win(data, bt1, bt2);

	return (0);
}
