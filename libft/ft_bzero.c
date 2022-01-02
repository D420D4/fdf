/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:34:53 by plefevre          #+#    #+#             */
/*   Updated: 2021/12/09 02:44:53 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, int n)
{
	int	i;
	int	n2;

	n2 = n / 8;
	i = 0;
	while (i < n2)
	{
		((double *) s)[i] = 0;
		i++;
	}
	i = n2 * 8;
	while (i < n)
	{
		((char *) s)[i] = 0;
		i++;
	}
}
