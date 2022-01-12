/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 01:16:56 by plefevre          #+#    #+#             */
/*   Updated: 2022/01/08 01:17:21 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bonus_functions.h"

static void	key_simulateur(int keycode, t_data *vars)
{
	if (keycode == 65451)
		vars->bonus->simulateur->angle_z += M_PI_4 / 8;
	if (keycode == 65453)
		vars->bonus->simulateur->angle_z -= M_PI_4 / 8;
	if (keycode == 97)
		vars->bonus->simulateur->key_a = 1;
	if (keycode == 100)
		vars->bonus->simulateur->key_d = 1;
	if (keycode == 119)
		vars->bonus->simulateur->key_w = 1;
	if (keycode == 115)
		vars->bonus->simulateur->key_s = 1;
	if (keycode == 101)
	{
		if (vars->bonus->stars)
			free(vars->bonus->stars);
		vars->bonus->stars = generate_stars();
	}
	if (keycode == 113)
	{
		free(vars->bonus->simulateur);
		vars->bonus->simulateur = 0;
	}
}

static void	key_bonus_camera(int keycode, t_data *vars)
{
	if (keycode == 65436)
		vars->bonus->vrx += ROTATION_SPEED;
	if (keycode == 65433)
		vars->bonus->vrx -= ROTATION_SPEED;
	if (keycode == 65430)
		vars->bonus->vry += ROTATION_SPEED;
	if (keycode == 65437)
		vars->bonus->vry -= ROTATION_SPEED;
	if (keycode == 65429)
		vars->bonus->vrz += ROTATION_SPEED;
	if (keycode == 65431)
		vars->bonus->vrz -= ROTATION_SPEED;
	if (keycode == 65451)
		vars->camera->zoom += ZOOM_SPEED;
	if (keycode == 65453)
		vars->camera->zoom -= ZOOM_SPEED;
	if (keycode == 65361)
		vars->camera->x -= vars->camera->zoom * MOVE_SPEED_FACTOR;
	if (keycode == 65363)
		vars->camera->x += vars->camera->zoom * MOVE_SPEED_FACTOR;
	if (keycode == 65362)
		vars->camera->y -= vars->camera->zoom * MOVE_SPEED_FACTOR;
	if (keycode == 65364)
		vars->camera->y += vars->camera->zoom * MOVE_SPEED_FACTOR;
}

void	key_bonus_up(int keycode, t_data *vars)
{
	if (vars->bonus->simulateur)
	{
		if (keycode == 97)
			vars->bonus->simulateur->key_a = 0;
		if (keycode == 100)
			vars->bonus->simulateur->key_d = 0;
		if (keycode == 119)
			vars->bonus->simulateur->key_w = 0;
		if (keycode == 115)
			vars->bonus->simulateur->key_s = 0;
	}
}

void	key_bonus_down(int keycode, t_data *vars)
{
	if (vars->bonus->simulateur)
		key_simulateur(keycode, vars);
	else
	{
		key_bonus_camera(keycode, vars);
		if (keycode == 65434)
			vars->bonus->object_z *= 1.3;
		if (keycode == 65432)
			vars->bonus->object_z /= 1.3;
		if (keycode == 118)
			vars->bonus->simulateur = init_simulateur(vars);
		if (keycode == 114)
		{
			reset_bonus(vars->bonus);
			reset_camera(vars->camera, vars->map, WIN_TX, WIN_TY);
		}
		if (keycode == 112)
			vars->bonus->projection = (vars->bonus->projection + 1) % 2;
	}
}
