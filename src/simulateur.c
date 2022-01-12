/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulateur.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 00:57:01 by plefevre          #+#    #+#             */
/*   Updated: 2022/01/08 00:58:06 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bonus_data.h"
#include "../includes/fdf.h"
#include "../includes/bonus_functions.h"

t_simulateur	*init_simulateur(t_data *data)
{
	t_simulateur	*simulateur;

	(void) data;
	simulateur = malloc(sizeof(t_simulateur));
	if (!simulateur)
		return (0);
	simulateur->angle_x = M_PI_2;
	simulateur->angle_z = M_PI_2;
	simulateur->angle_y = 0;
	simulateur->vitesse = 10;
	simulateur->px = data->map->size / 2;
	simulateur->px = 0;
	simulateur->py = 0.0;
	simulateur->pz = -16;
	simulateur->key_d = 0;
	simulateur->key_s = 0;
	simulateur->key_a = 0;
	simulateur->key_w = 0;
	return (simulateur);
}

void	update_simulateur(t_simulateur *simulateur)
{
	if (simulateur->angle_x > M_PI_2 * 0.8)
		simulateur->angle_x -= 0.005 * simulateur->key_w;
	if (simulateur->angle_x < M_PI_2 * 1.2)
		simulateur->angle_x += 0.005 * simulateur->key_s;
	simulateur->angle_z -= 0.01 * simulateur->key_a;
	simulateur->angle_z += 0.01 * simulateur->key_d;
	if (simulateur->key_d)
		simulateur->angle_y = 0.3 + (simulateur->angle_y - 0.3) * 0.9;
	else if (simulateur->key_a)
		simulateur->angle_y = -0.3 + (simulateur->angle_y + 0.3) * 0.9;
	else
		simulateur->angle_y *= 0.9;
	simulateur->px += simulateur->vitesse * SIMULATOR_SPEED_FACTOR
		* sinf(simulateur->angle_x) * sinf(-simulateur->angle_z);
	simulateur->py += simulateur->vitesse * SIMULATOR_SPEED_FACTOR
		* sinf(simulateur->angle_x) * cosf(-simulateur->angle_z);
	simulateur->pz += simulateur->vitesse * SIMULATOR_SPEED_FACTOR
		* cosf(simulateur->angle_x);
}
