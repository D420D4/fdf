/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 00:23:36 by plefevre          #+#    #+#             */
/*   Updated: 2022/01/08 01:22:54 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define WIN_TX 800
# define WIN_TY 800

# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "linemap.h"
# include "camera.h"
# include "bonus_data.h"

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_linemap	*map;
	t_camera	*camera;
	t_bonus		*bonus;
}	t_data;

t_linemap	*parse_file(char *file);
int			win_close(t_data *vars);
int			clear_win(t_data *data);
int			drawline(t_data *data, t_point t1, t_point t2, t_m4 mat);

#endif
