//
// Created by plefevre on 12/13/21.
//

#include "../includes/fdf.h"
#include "../includes/linemap.h"

t_linemap *line_new(int *line) {
	t_linemap *linemap;

	linemap = malloc(sizeof(*linemap));
	if (!linemap)
		return (0);
	linemap->line = line;
	linemap->next = 0;
	linemap->size = 0;
	return (linemap);
}

int line_add(t_linemap **start, t_linemap *linemap)
{
	if (*start)
		return (line_add(&((*start)->next), linemap));
	*start = linemap;
	return (0);
}

void line_print(t_linemap *map) {
	int i;

	if (map)
	{
		i = 0;
		while (i < map->size)
		{
			printf("%d\t",map->line[i]);
			i++;
		}
		printf("\n");
		line_print(map->next);
	}
}

t_linemap *line_freeall(t_linemap *map) {
	if (!map)
		return (0);
	free(map->line);
	return line_freeall(map->next);
}

