#ifndef FDF_H
# define FDF_H
#define WIN_TAILLEX 800
#define WIN_TAILLEY 800

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "linemap.h"

typedef struct s_img
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_img;

typedef struct s_data
{
	void *mlx;
	void *win;
	t_img img;
	t_linemap *map;
} t_data;

t_linemap	*parse_file(char *file);
#endif
