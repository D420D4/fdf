//
// Created by plefevre on 12/14/21.
//

#include "../includes/ft_3d.h"
#include <math.h>

void set_identity(t_m4 *mat) {
	int	i;

	i = 0;
	while (i < 16) {
		(*mat)[i] = (i % 5 == 0);
		i++;
	}
}

void set_null(t_m4 *mat)
{
  int i;

  i = 0;
  while (i < 16)
  {
    (*mat)[i] = 0;
    i++;
  }
}

t_point point_new(float x, float y, float z) {
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

// cos  -sin 0
// sin   cos 0
//  0     0  1

void matcpy(t_m4 *m1, t_m4 m2)
{
  int i;

  i = 0;
  while (i < 16)
  {
    *m1[i] = m2[i];
    i++;
  }
}

void  mult_matmat(t_m4 *m1, t_m4 m2)
{
  t_m4 res;
  int i;
  int j;
  int k;

  i = 0;
  while (i < 4)
  {
    j = 0;
    while (j < 4)
    {
      k = 0;
      res[i + j * 4] = 0;
      while (k < 4)
      {
        res[i + j * 4] += *m1[k + j * 4] * m2[i + k * 4];
      }
    }
  }
  matcpy(m1, res);
}

void  set_rotationXmat(t_m4 *mat, float angle)
{
  set_identity(mat);
  *mat[0] = cos(angle);
  *mat[1] = sin(angle);
  *mat[4] = -sinf(angle);
  *mat[5] = cos(angle);
} 

void rotateX_mat(t_m4 *mat, float angle)
{
  t_m4 m;
  set_rotationXmat(&m, angle);
  mult_matmat(mat, m);
}
