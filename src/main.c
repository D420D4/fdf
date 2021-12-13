/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 18:51:35 by plefevre          #+#    #+#             */
/*   Updated: 2021/12/13 20:06:55 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include "linemap.h"


typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct	s_data{
	void	*mlx;
	void	*win;
	t_img	img;
}				t_data;

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	key_hook(int keycode, t_data *vars)
{
	printf("Hello from key_hook! %d \n", keycode);
	if (keycode == 65307)
		mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

int	renderFrame(t_data	*img)
{
	static int k = 0;

	k++;
	(void) img;
	printf("%d\n", k);

	return (0);
}

int render(t_data *data)
{
    if (!data->win)
        return (0);
    for (int i = 0; i < 10; ++i) {
        my_mlx_pixel_put(&data->img, rand() % 500, rand() % 500, 0x00FF0000);
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);

//    printf(".");
	return (1);
}

int	main()
{
	t_data	data;
	int	i,j;

	t_linemap *map;

	map = parseFile("maps/test_maps/42.fdf");
	line_print(map);

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, 500, 500, "Fdf");

	data.img.img = mlx_new_image(data.mlx, 500, 500);
	data.img.addr = mlx_get_data_addr(data.img.img, &(data.img.bits_per_pixel),
                                      &(data.img.line_length),&(data.img.endian));

	i = 0;
	while (i < 500)
	{
		j = 0;
		while (j < 500)
		{
			my_mlx_pixel_put(&(data.img), i, j, i * 256 / 500+ (j * 256 /500) * 256);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data.mlx, data.win, data.img.img, 0, 0);

	mlx_key_hook(data.win, key_hook, &data);

    mlx_loop_hook(data.mlx, render, &data);

    mlx_loop(data.mlx);
}
