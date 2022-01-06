/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft3d_perspective.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 23:41:11 by plefevre          #+#    #+#             */
/*   Updated: 2022/01/06 23:41:14 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft3d.h"

void	set_perspective_mat(t_m4 *mat, float larg, float haut, float from)
{
	float	near;

	near = 1;
	set_identity(mat);
	(*mat)[0] = near / larg;
	(*mat)[5] = near / haut;
	(*mat)[10] = -(from + near) / (from - near);
	(*mat)[11] = -2 * from * near / (from - near);
	(*mat)[14] = -1;
	(*mat)[15] = 0;
}

void	perspective_mat(t_m4 *mat, float larg, float haut, float from)
{
	t_m4	m;

	set_perspective_mat(&m, larg, haut, from);
	mult_matmat(mat, m);
}
