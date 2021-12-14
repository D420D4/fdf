//
// Created by plefevre on 12/14/21.
//

#include "../includes/ft_3d.h"

void set_identity(t_m4 *mat) {
	int	i;

	i = 0;
	while (i < 16) {
		(*mat)[i] = (i % 5 == 0) * 10;
		i++;
	}
}

t_point point_new(int x, int y, int z) {
	t_point result;
	result.x = x;
	result.y = y;
	result.z = z;
	return result;
}

void mult_matvec(t_m4 mat, t_point p1, t_point *out) {
	out->x = mat[0] * p1.x + mat[1] * p1.y + mat[2] * p1.z;
	out->y = mat[4] * p1.x + mat[5] * p1.y + mat[6] * p1.z;
	out->z = mat[8] * p1.x + mat[9] * p1.y + mat[10] * p1.z;
}

