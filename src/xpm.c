/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 23:27:30 by plefevre          #+#    #+#             */
/*   Updated: 2022/01/06 23:27:32 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/xpm.h"
#include "../includes/fdf.h"
#include "../libft/libft.h"

static void	print_header(int fd)
{
	ft_putstr_fd("/* XPM */\n", fd);
	ft_putstr_fd("static char *black[] = {\n\"", fd);
	ft_putnbr_fd(WIN_TX, fd);
	ft_putstr_fd(" ", fd);
	ft_putnbr_fd(WIN_TY, fd);
	ft_putstr_fd(" 2 1\",\n", fd);
	ft_putstr_fd("\". c #272323\",\n", fd);
	ft_putstr_fd("\"o c #27ff23\",\n", fd);
}

int	generate_black_xpm(char *s)
{
	int	fd;
	int	i;
	int	j;

	fd = open(s, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		return (0);
	print_header(fd);
	i = 0;
	while (i < WIN_TX)
	{
		j = 0;
		write(fd, "\"", 1);
		while (j < WIN_TY)
			j += write(fd, ".", 1);
		i += write(fd, "\"", 1);
		if (i < WIN_TX)
			write(fd, ",\n", 2);
	}
	write(fd, "};", 2);
	close(fd);
	return (1);
}
