//
// Created by plefevre on 12/13/21.
//

#ifndef FDF_LINEMAP_H
# define FDF_LINEMAP_H

typedef struct s_linemap {
	int *line;
	int	size;
	int size_tot;
	struct s_linemap *next;
}               t_linemap;

t_linemap	*line_new(int *line);
int			line_add(t_linemap **start, t_linemap *linemap);
t_linemap	*line_freeall(t_linemap *map);
void		line_print(t_linemap *map);
void map_finalize(t_linemap *map);

#endif //FDF_LINEMAP_H
