//
// Created by plefevre on 12/13/21.
//

#include "../includes/fdf.h"
#include "../includes/get_next_line.h"
#include "../includes/linemap.h"
#include "../libft/libft.h"

char *go_next_start(char *line)
{
	while(*line && ft_strchr(" \t", *line))
		line++;
	while(*line && !ft_strchr(" \t", *line))
		line++;
	return (line);
}

int	count_element(char *line)
{
	int nb;

	nb = 0;
	while (*line)
	{
		line = go_next_start(line);
		nb++;
	}
	return (nb);
}


int *convert_int(char *line, int *nb)
{
	static int	nb_element = -1;
	int 		*line_int;
	int i;

	i = 0;
	if (nb_element == -1)
		nb_element = count_element(line);
	if(nb_element != count_element(line))
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

t_linemap	*parseFile(char *file) {
	char		*line;
	t_linemap	*linemap;
	int 		fd;
	int 		nb;

	//TODO check error
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	linemap = 0;
	while (line)
	{
		t_linemap *pLinemap = line_new(convert_int(line, &nb));
		pLinemap->size = nb;
		if (!pLinemap)
			return (line_freeall(linemap));
		line_add(&linemap, pLinemap);
		line = get_next_line(fd);
	}
	close(fd);

	return (linemap);
}
