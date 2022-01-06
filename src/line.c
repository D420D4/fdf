/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 22:46:12 by plefevre          #+#    #+#             */
/*   Updated: 2022/01/06 22:49:39 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft3d.h"
#include "../includes/fdf.h"
#include "../includes/draw_utils.h"
#include "../includes/maths.h"
#include "../includes/color.h"

static int	ressere_left(t_point2 *t1, t_point2 *t2)
{
	if ((t1->x < 0 && t2->x < 0) || (t1->x > WIN_TX && t2->x > WIN_TX))
		return (0);
	if (t1->x < 0)
	{
		t1->y = t2->y + t2->x * ((t2->y - t1->y) / (t1->x - t2->x));
		t1->x = 0;
	}
	if (t1->x > WIN_TX)
	{
		t1->y = t2->y + (t2->x - WIN_TX) * ((t2->y - t1->y) / (t1->x - t2->x));
		t1->x = WIN_TX;
	}
	if ((t1->y < 0 && t2->y < 0) || (t1->y > WIN_TY && t2->y > WIN_TY))
		return (0);
	if (t1->y < 0)
	{
		t1->x = t2->x + t2->y * ((t2->x - t1->x) / (t1->y - t2->y));
		t1->y = 0;
	}
	if (t1->y > WIN_TY)
	{
		t1->x = t2->x + (t2->y - WIN_TY) * ((t2->x - t1->x) / (t1->y - t2->y));
		t1->y = WIN_TY;
	}
	return (1);
}

static int	ressere(t_point2 *t1, t_point2 *t2)
{
	return (ressere_left(t1, t2) && ressere_left(t2, t1));
}

static int	drawline_win(t_data *data, t_point2 t1, t_point2 t2)
{
	int	max;
	int	i;
	int	x;
	int	y;
	int	c;

	if (!ressere(&t1, &t2))
		return (0);
	max = ft_max(ft_abs(t1.x - t2.x), ft_abs(t1.y - t2.y));
	i = 0;
	while (i < max)
	{
		x = t1.x + (t2.x - t1.x) * i / max;
		y = t1.y + (t2.y - t1.y) * i / max;
		c = t1.c + (t2.c - t1.c) * i / max;
		if (x >= 0 && x < WIN_TX && y >= 0 && y < WIN_TY)
			my_mlx_pixel_put(&(data->img),
				x, y, z_to_color(c));
		i++;
	}
	return (1);
}

int	drawline(t_data *data, t_point t1, t_point t2, t_m4 mat)
{
	t_point2	bt1;
	t_point2	bt2;

	mult_matvec(mat, t1, &bt1);
	mult_matvec(mat, t2, &bt2);
	bt1.c = t1.z;
	bt2.c = t2.z;
	drawline_win(data, bt1, bt2);
	return (0);
}
