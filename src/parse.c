/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:27:39 by plefevre          #+#    #+#             */
/*   Updated: 2022/01/06 12:31:15 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "get_next_line.h"
#include "linemap.h"
#include "libft.h"

char	*go_next_start(char *line)
{
	while (*line && ft_strchr(" \t", *line))
		line++;
	while (*line && !ft_strchr(" \t", *line))
		line++;
	return (line);
}

int	count_element(char *line)
{
	int	nb;

	nb = 0;
	while (*line)
	{
		line = go_next_start(line);
		nb++;
	}
	return (nb);
}

int	*convert_int(char *line, int *nb)
{
	static int	nb_element = -1;
	int			*line_int;
	int			i;

	i = 0;
	if (nb_element == -1)
		nb_element = count_element(line);
	if (nb_element != count_element(line))
		return (0);
	line_int = malloc(sizeof(int) * nb_element);
	if (!line_int)
		return (0);
	while (i < nb_element)
	{
		line = go_next_start(line);
		line_int[i] = ft_atoi(line);
		i++;
	}
	*nb = nb_element;
	return (line_int);
}

t_linemap	*parse_file(char *file)
{
	char		*line;
	t_linemap	*linemap;
	t_linemap	*p_linemap;
	int			fd;
	int			nb;

	//TODO check error
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	linemap = 0;
	while (line)
	{
		p_linemap = line_new(convert_int(line, &nb));
		p_linemap->size = nb;
		if (!p_linemap)
			return (line_freeall(linemap));
		line_add(&linemap, p_linemap);
		line = get_next_line(fd);
	}
	map_finalize(linemap);
	close(fd);
	return (linemap);
}
