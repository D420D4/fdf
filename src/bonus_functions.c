/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 00:52:18 by plefevre          #+#    #+#             */
/*   Updated: 2022/01/09 14:47:52 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bonus_functions.h"

static void	print_c(char	*s, int couleur)
{
	ft_putstr_fd("\033[1;", 1);
	ft_putnbr_fd(couleur, 1);
	ft_putstr_fd("m", 1);
	ft_putstr_fd(s, 1);
	ft_putstr_fd("\033[0m", 1);
}

static void	print_cmd(char *s1, char *s2)
{
	ft_putstr_fd("\033[1;34m", 1);
	ft_putstr_fd(s1, 1);
	ft_putstr_fd("\033[0m", 1);
	ft_putstr_fd(s2, 1);
}

void	print_intro_text(void)
{
	print_c("Bonjour! Bienvenue sur mon magnifique fdf!\n", 32);
	print_c("Installez vous confortablement et profitez du spectacle!\n", 32);
	print_c("----------------------------------------------------------\n", 33);
	print_c("Input :\n", 35);
	print_cmd("Arrow   : ", "Move left, right, up, down \n");
	print_cmd("+, -    : ", "Zoom in, out \n");
	print_cmd("6, 9    : ", "Z position in perspective \n");
	print_cmd("1, 2    : ", "Change speed rotation X \n");
	print_cmd("4, 5    : ", "Change speed rotation Y \n");
	print_cmd("7, 8    : ", "Change speed rotation Z \n");
	print_cmd("r       : ", "Reset \n");
	print_cmd("p       : ", "Change projection view \n");
	print_cmd("v       : ", "Enter the fuckin plane simulator mode!!! \n");
	print_c("----------------------------------------------------------\n", 33);
	print_c("Simulator mode input :\n", 35);
	print_cmd("s       : ", "Go up \n");
	print_cmd("w       : ", "Go down \n");
	print_cmd("a, d    : ", "Go left, right \n");
	print_cmd("e       : ", "🤩\n");
	print_cmd("q       : ", "Quit\n");
	print_c("----------------------------------------------------------\n", 33);
}

void	update_camera(t_data *data)
{
	data->camera->rx += data->bonus->vrx;
	data->camera->ry += data->bonus->vry;
	data->camera->rz += data->bonus->vrz;
}
