//
// Created by plefevre on 12/14/21.
//

#ifndef FT_3D_H
#define FT_3D_H

typedef struct s_point
{
    float x;
    float y;
    float z;
} t_point;

typedef struct s_point2
{
    int x;
    int y;
    int z;
} t_point2;

typedef float t_m4[16];

void set_identity(t_m4 *mat);
void mult_matvec(t_m4 mat, t_point p1, t_point2 *out);
void rotateX_mat(t_m4 *mat, float angle);
void rotateY_mat(t_m4 *mat, float angle);
void rotateZ_mat(t_m4 *mat, float angle);
void translate_mat(t_m4 *mat, float x, float y, float z);
void resize_mat(t_m4 *mat, float x, float y, float z);
void perspective_mat(t_m4 *mat, float larg, float haut, float near, float from);
t_point point_new(float x, float y, float z);

#endif //FDF_3D_H
