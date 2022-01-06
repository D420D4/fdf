/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 00:21:01 by plefevre          #+#    #+#             */
/*   Updated: 2022/01/07 00:22:05 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include <stdlib.h>
# include "fdf.h"
# include "ft3d.h"

typedef struct s_camera
{
	float	x;
	float	y;
	float	z;
	float	rx;
	float	ry;
	float	rz;
}	t_camera;

t_camera	*camera_init(void);
float		camera_center(t_camera *camera, t_linemap *map);
void		apply_camera(t_camera *camera, t_m4 *mat, float zoom);

#endif
