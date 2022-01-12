/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 00:21:01 by plefevre          #+#    #+#             */
/*   Updated: 2022/01/08 01:21:21 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include <stdlib.h>
# include "ft3d.h"
# include "linemap.h"

typedef struct s_camera
{
	float	x;
	float	y;
	float	z;
	float	rx;
	float	ry;
	float	rz;
	float	zoom;
}	t_camera;

t_camera	*init_camera(void);
void		camera_center(t_camera *camera, t_linemap *map, int tx, int ty);
void		reset_camera(t_camera *camera, t_linemap *map, int tx, int ty);
void		apply_camera(t_camera *camera, t_m4 *mat);

#endif
