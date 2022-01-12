/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_data.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 01:19:52 by plefevre          #+#    #+#             */
/*   Updated: 2022/01/08 01:21:09 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_DATA_H
# define BONUS_DATA_H
# define NB_STARS 5000
# define STARS_DISTANCE 3600
# include <stdlib.h>
# include "ft3d.h"

typedef struct t_simulateur
{
	float	vitesse;
	float	angle_x;
	float	angle_z;
	float	angle_y;
	float	px;
	float	py;
	float	pz;
	int		key_w;
	int		key_s;
	int		key_a;
	int		key_d;
}	t_simulateur;

typedef struct s_stars
{
	t_point	stars[NB_STARS];
}	t_stars;

typedef struct s_bonus
{
	float			vrx;
	float			vry;
	float			vrz;
	int				projection;
	float			object_z;
	t_simulateur	*simulateur;
	t_stars			*stars;
}	t_bonus;

t_bonus	*init_bonus(void);
void	reset_bonus(t_bonus *bonus);

#endif
