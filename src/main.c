/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 18:51:35 by plefevre          #+#    #+#             */
/*   Updated: 2021/12/13 20:06:55 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "mlx.h"
#include "fdf.h"
#include "linemap.h"
#include "ft_3d.h"
#include "libft.h"

#define WIN_TAILLEX 800
#define WIN_TAILLEY 800


typedef struct s_img
{
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_img;

typedef struct s_data
{
    void *mlx;
    void *win;
    t_img img;
    t_linemap *map;
} t_data;

int ft_sqrt(int nb) {
    int i;
    int b;
    int max;

    max = 46341;
    if (nb < max)
        max = nb;
    if (nb <= 0)
        return (0);
    i = 0;
    i = (max + 1) / 2;
    b = i / 2;
    while (i != nb / i && b > 0) {
        if (i > nb / i)
            i -= b;
        else
            i += b;
        if (b > 1)
            b = (b + 1) / 2;
        else
            b = 0;
        if (i > 46340)
            i = 46340;
    }
     return (i);

}

void my_mlx_pixel_put(t_img *img, int x, int y, int z, int color) {
    char *dst;

    int dist;
    dist = ft_sqrt(x * x + y * y + z * z) + 1;
    if (dist == 1)
        return;
    x = 250 + 250 * (1 + x) / dist;
    y = 250 + 250 * (1 + y) / dist;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int *) dst = color;
}

int key_hook(int keycode, t_data *vars) {
    printf("Hello from key_hook! %d \n", keycode);
    if (keycode == 65307)
        mlx_destroy_window(vars->mlx, vars->win);
    return (0);
}

int renderFrame(t_data *img) {
    static int k = 0;

    k++;
    (void) img;
    printf("%d\n", k);

    return (0);
}

int ft_abs(int n) {
    if (n > 0)
        return (n);
    return (-n);
}

int ft_max(int n1, int n2) {
    if (n1 > n2)
        return (n1);
    return (n2);
}

int ressere_left(t_point2 *t1, t_point2 *t2) {

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

int ressere(t_point2 *t1, t_point2 *t2) {
    return (ressere_left(t1, t2) && ressere_left(t2, t1));
}

int drawline_win(t_data *data, t_point2 t1, t_point2 t2) {
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
                             0x00FF0000);
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

void clear_win(t_data *data) {
    ft_bzero(data->img.addr, WIN_TAILLEX * WIN_TAILLEY * 4);
}

int draw_inter_row(t_data *data, t_m4 mat, t_linemap line, int y) {
    int i;
    t_point t1;
    t_point t2;

    i = 0;
    while (i < line.size) {
        t1 = point_new(i, y, line.line[i]);
        t2 = point_new(i, y + 1, line.next->line[i]);
        drawline(data, t1, t2, mat);
        i++;
    }
    return (0);
}

int draw_row(t_data *data, t_m4 mat, t_linemap line, int y) {
    int i;
    t_point t1;
    t_point t2;

    i = 0;
    while (i < line.size - 1) {
        t1 = point_new(i, y, line.line[i]);
        t2 = point_new(i + 1, y, line.line[i + 1]);
        drawline(data, t1, t2, mat);
        i++;
    }
    if (line.next)
        draw_inter_row(data, mat, line, y);
    return (0);
}

int render(t_data *data) {
    t_m4 mat;
    static int cmp = 0;
    t_linemap *linemap;
    int i;

    if (!data->win)
        return (0);

    i = 0;
    clear_win(data);
    set_identity(&mat);
    //perspective_mat(&mat, 1, 1, 1.0, 1.1 + 200.0 / cmp);
    translate_mat(&mat, 350, 350, 0);
    rotateZ_mat(&mat, cmp / 100.0);
    rotateX_mat(&mat, cmp / 200.0);
    rotateY_mat(&mat, cmp / 400.0);
    translate_mat(&mat, -100, -100, 0);
    resize_mat(&mat, 10, 10, 10);

    cmp++;
    linemap = data->map;
    while (linemap) {
        draw_row(data, mat, *linemap, i);
        i++;
        linemap = linemap->next;
    }


    mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);

    //    printf(".");
    return (1);
}

int main(int argc, char **argv) {
    t_data data;

    t_linemap *map;

    if (argc != 2)
        return (0);
    map = parseFile(argv[1]);
    //	line_print(map);

    data.map = map;
    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, WIN_TAILLEX, WIN_TAILLEY, "Fdf");

    data.img.img = mlx_new_image(data.mlx, WIN_TAILLEX, WIN_TAILLEY);
    data.img.addr = mlx_get_data_addr(data.img.img, &(data.img.bits_per_pixel),
                                      &(data.img.line_length), &(data.img.endian));

    mlx_put_image_to_window(data.mlx, data.win, data.img.img, 0, 0);

    mlx_key_hook(data.win, key_hook, &data);

    mlx_loop_hook(data.mlx, render, &data);

    mlx_loop(data.mlx);
}
