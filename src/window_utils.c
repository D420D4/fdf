/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 23:16:07 by plefevre          #+#    #+#             */
/*   Updated: 2022/01/08 00:48:23 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../includes/camera.h"
#include "../minilibx/mlx.h"
#include "../libft/libft.h"

static int	free_all(t_data *vars)
{
	if (vars->mlx && vars->img.img)
		mlx_destroy_image(vars->mlx, vars->img.img);
	if (vars->mlx && vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}
	if (vars->map)
		line_freeall(vars->map, 0);
	if (vars->camera)
		free(vars->camera);
	if (vars->bonus)
	{
		if (vars->bonus->simulateur)
			free(vars->bonus->simulateur);
		if (vars->bonus->stars)
			free (vars->bonus->stars);
		free(vars->bonus);
	}
	return (0);
}

int	win_close(t_data *vars)
{
	mlx_do_key_autorepeaton(vars->mlx);
	exit(free_all(vars));
}

int	clear_win(t_data *data)
{
	ft_bzero(data->img.addr, WIN_TX * WIN_TY * 4);
	return (1);
}
