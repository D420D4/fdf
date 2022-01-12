/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_functions.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 01:21:29 by plefevre          #+#    #+#             */
/*   Updated: 2022/01/08 01:22:44 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_FUNCTIONS_H
# define BONUS_FUNCTIONS_H
# define ROTATION_SPEED 0.005
# define ZOOM_SPEED 1
# define MOVE_SPEED_FACTOR 1
# define SIMULATOR_SPEED_FACTOR 0.005
# include "../libft/libft.h"
# include "fdf.h"

void			print_intro_text(void);
void			update_camera(t_data *data);
void			key_bonus_down(int keycode, t_data *vars);
void			key_bonus_up(int keycode, t_data *vars);

t_simulateur	*init_simulateur(t_data *data);

void			update_simulateur(t_simulateur *simulateur);
void			draw_stars(t_m4 *mat, t_stars *stars, t_data *data);
t_stars			*generate_stars(void);

#endif //BONUS_FUNCTIONS_H
