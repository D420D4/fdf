//
// Created by plefevre on 12/14/21.
//

#include "../includes/ft_3d.h"
#include <math.h>
#include <stdio.h>

void set_identity(t_m4 *mat) {
    int i;

    i = 0;
    while (i < 16) {
        (*mat)[i] = 0;
        if (i % 5 == 0)
            (*mat)[i] = 1;
        i++;
    }
}

void set_null(t_m4 *mat) {
    int i;

    i = 0;
    while (i < 16) {
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

void mult_matvec(t_m4 mat, t_point p1, t_point2 *out) {
    out->x = mat[0] * p1.x + mat[1] * p1.y + mat[2] * p1.z + mat[3];
    out->y = mat[4] * p1.x + mat[5] * p1.y + mat[6] * p1.z + mat[7];
    out->z = mat[8] * p1.x + mat[9] * p1.y + mat[10] * p1.z + mat[11];
}

// cos  -sin 0
// sin   cos 0
//  0     0  1

void matcpy(t_m4 *m1, t_m4 m2) {
    int i;

    i = 0;
    while (i < 16) {
        (*m1)[i] = m2[i];
        i++;
    }
}

void mult_matmat(t_m4 *m1, t_m4 m2) {
    t_m4 res;
    int i;
    int j;
    int k;

    i = 0;
    while (i < 4) {
        j = 0;
        while (j < 4) {
            k = 0;
            res[i + j * 4] = 0;
            while (k < 4) {
                res[i + j * 4] += (*m1)[k + j * 4] * m2[i + k * 4];
                k++;
            }
            j++;
        }
        i++;
    }
    matcpy(m1, res);
}

void set_rotationX_mat(t_m4 *mat, float angle) {
    set_identity(mat);
    (*mat)[5] = cosf(angle);
    (*mat)[6] = -sinf(angle);
    (*mat)[9] = sinf(angle);
    (*mat)[10] = cosf(angle);
}

void set_rotationY_mat(t_m4 *mat, float angle) {
    set_identity(mat);
    (*mat)[0] = cosf(angle);
    (*mat)[1] = sinf(angle);
    (*mat)[4] = -sinf(angle);
    (*mat)[5] = cosf(angle);
}

void set_rotationZ_mat(t_m4 *mat, float angle) {
    set_identity(mat);
    (*mat)[0] = cosf(angle);
    (*mat)[2] = -sinf(angle);
    (*mat)[8] = sinf(angle);
    (*mat)[10] = cosf(angle);
}

void set_translation_mat(t_m4 *mat, float x, float y, float z) {
    set_identity(mat);
    (*mat)[3] = x;
    (*mat)[7] = y;
    (*mat)[11] = z;
}

void set_resize_mat(t_m4 *mat, float x, float y, float z) {
    set_identity(mat);
    (*mat)[0] = x;
    (*mat)[5] = y;
    (*mat)[10] = z;
}

void set_perspective_mat(t_m4 *mat, float larg, float haut, float near, float from) {
    set_identity(mat);
    (*mat)[0] = near / larg;
    (*mat)[5] = near / haut;
    (*mat)[10] = -(from + near) / (from - near);
    (*mat)[11] = -2 * from * near / (from - near);
    (*mat)[14] = -1;
    (*mat)[15] = 0;

}

void perspective_mat(t_m4 *mat, float larg, float haut, float near, float from)
{
    t_m4 m;
    set_perspective_mat(&m, larg, haut, near, from);
    mult_matmat(mat, m);
}

void rotateX_mat(t_m4 *mat, float angle) {
    t_m4 m;
    set_rotationX_mat(&m, angle);
    mult_matmat(mat, m);
}

void rotateY_mat(t_m4 *mat, float angle) {
    t_m4 m;
    set_rotationY_mat(&m, angle);
    mult_matmat(mat, m);
}

void rotateZ_mat(t_m4 *mat, float angle) {
    t_m4 m;
    set_rotationZ_mat(&m, angle);
    mult_matmat(mat, m);
}

void translate_mat(t_m4 *mat, float x, float y, float z) {
    t_m4 m;
    set_translation_mat(&m, x, y, z);
    mult_matmat(mat, m);
}

void resize_mat(t_m4 *mat, float x, float y, float z) {
    t_m4 m;
    set_resize_mat(&m, x, y, z);
    mult_matmat(mat, m);
}
