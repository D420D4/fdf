/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linemap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 00:25:06 by plefevre          #+#    #+#             */
/*   Updated: 2022/01/07 00:26:36 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINEMAP_H
# define LINEMAP_H

typedef struct s_linemap {
	int					*line;
	int					size;
	int					size_tot;
	struct s_linemap	*next;
}	t_linemap;

t_linemap	*line_new(int *line);
int			line_add(t_linemap **start, t_linemap *linemap);
t_linemap	*line_freeall(t_linemap *map, t_linemap *previous);
void		line_print(t_linemap *map);
void		map_finalize(t_linemap *map);

#endif //FDF_LINEMAP_H
