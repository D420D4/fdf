/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linemap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:25:13 by plefevre          #+#    #+#             */
/*   Updated: 2022/01/06 12:26:37 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../includes/linemap.h"

t_linemap *line_new(int *line)
{
	t_linemap *linemap;

	linemap = malloc(sizeof(*linemap));
	if (!linemap)
		return (0);
	linemap->line = line;
	linemap->next = 0;
	linemap->size = 0;
	linemap->size_tot = 0;
	return (linemap);
}

int line_add(t_linemap **start, t_linemap *linemap)
{
	if (*start)
	{
		(*start)->size_tot += 1;
		return (line_add(&((*start)->next), linemap));
	}
	*start = linemap;
	return (0);
}

void map_finalize(t_linemap *map)
{
	int taille;

	taille = map->size_tot;

	while (map)
	{
		map->size_tot = taille;
		map = map->next;
	}
}

void line_print(t_linemap *map)
{
	int i;

	if (map)
	{
		i = 0;
		while (i < map->size)
		{
			printf("%d\t", map->line[i]);
			i++;
		}
		printf("\n");
		line_print(map->next);
	}
}

t_linemap *line_freeall(t_linemap *map)
{
	if (!map)
		return (0);
	free(map->line);
	return (line_freeall(map->next));
}
