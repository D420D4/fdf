/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 23:18:50 by plefevre          #+#    #+#             */
/*   Updated: 2022/01/06 23:19:15 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	linear(int deb, int fin, float v)
{
	return (v * fin + (1 - v) * deb);
}

int	z_to_color(float z)
{
	if (z < 10)
	{
		return (linear(0x0000ff, 0x00ff00, z / 10));
	}
	if (z < 100)
	{
		return (linear(0x0000ff, 0x00ff00, (z - 10) / 90));
	}
	return (0xff0000);
}
