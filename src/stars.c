/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stars.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 01:16:23 by plefevre          #+#    #+#             */
/*   Updated: 2022/01/08 01:16:47 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bonus_functions.h"
#include "../includes/draw_utils.h"

void	draw_stars(t_m4 *mat, t_stars *stars, t_data *data)
{
	t_point2	bt;
	int			i;

	i = 0;
	while (i < NB_STARS)
	{
		mult_matvec(*mat, stars->stars[i], &bt);
		if (bt.w > 0)
		{
			bt.x /= bt.w;
			bt.y /= bt.w;
			bt.x += WIN_TX / 2;
			bt.y += WIN_TX / 2;
			if (bt.x >= 2 && bt.x < WIN_TX - 2
				&& bt.y >= 2 && bt.y < WIN_TY - 2)
			{
				my_mlx_pixel_put(&(data->img), bt.x + 1, bt.y, 0xffffff);
				my_mlx_pixel_put(&(data->img), bt.x - 1, bt.y, 0xffffff);
				my_mlx_pixel_put(&(data->img), bt.x, bt.y + 1, 0xffffff);
				my_mlx_pixel_put(&(data->img), bt.x, bt.y - 1, 0xffffff);
			}
		}
		i++;
	}
}

t_stars	*generate_stars(void)
{
	t_stars	*stars;
	float	a1;
	float	a2;
	int		i;

	stars = malloc(sizeof(t_stars));
	if (!stars)
		return (0);
	i = 0;
	while (i < NB_STARS)
	{
		a1 = rand() * 1.0 / RAND_MAX * M_PI * 2;
		a2 = rand() * 1.0 / RAND_MAX * M_PI - M_PI_2;
		stars->stars[i] = point_new(STARS_DISTANCE * cosf(a2) * sinf(a1),
				STARS_DISTANCE * cosf(a2) * cosf(a1),
				STARS_DISTANCE * sinf(a2));
		i++;
	}
	return (stars);
}
