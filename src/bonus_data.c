/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 00:49:38 by plefevre          #+#    #+#             */
/*   Updated: 2022/01/08 01:18:39 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../includes/bonus_data.h"
#include "../includes/ft3d.h"
#include "../includes/fdf.h"
#include "../includes/draw_utils.h"

t_bonus	*init_bonus(void)
{
	t_bonus	*bonus;

	bonus = malloc(sizeof(t_bonus));
	if (!bonus)
		return (0);
	bonus->vrx = 0;
	bonus->vry = 0;
	bonus->vrz = 0;
	bonus->projection = 0;
	bonus->object_z = -16;
	bonus->simulateur = 0;
	bonus->stars = 0;
	return (bonus);
}

void	reset_bonus(t_bonus *bonus)
{
	bonus->vrx = 0;
	bonus->vry = 0;
	bonus->vrz = 0;
	bonus->projection = 0;
}
