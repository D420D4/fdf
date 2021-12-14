//
// Created by plefevre on 12/14/21.
//

#ifndef FT_3D_H
#define FT_3D_H

typedef struct s_point{
	int	x;
	int	y;
	int	z;
}				t_point;

typedef int t_m4[16];

void	set_identity(t_m4 *mat);
void	mult_matvec(t_m4 mat, t_point p1, t_point *out);
t_point	point_new(int x, int y, int z);

#endif //FDF_3D_H
