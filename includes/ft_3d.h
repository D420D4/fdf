//
// Created by plefevre on 12/14/21.
//

#ifndef FT_3D_H
#define FT_3D_H

typedef struct s_point{
	float	x;
	float	y;
	float	z;
}				t_point;

typedef float t_m4[16];

void	set_identity(t_m4 *mat);
void	mult_matvec(t_m4 mat, t_point p1, t_point *out);
void  rotateX_mat(t_m4 *mat, float angle);

t_point	point_new(float x, float y, float z);

#endif //FDF_3D_H
