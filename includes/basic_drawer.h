/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_drawer.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 00:24:22 by plefevre          #+#    #+#             */
/*   Updated: 2022/01/07 00:24:29 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASIC_DRAWER_H
# define BASIC_DRAWER_H

# include "fdf.h"
# include "ft3d.h"

int	draw_row(t_data *data, t_m4 mat, t_linemap line, int y);

#endif //FDF_BASIC_DRAWER_H
