/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 00:24:40 by plefevre          #+#    #+#             */
/*   Updated: 2022/01/07 00:24:56 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XPM_H
# define XPM_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

int	generate_black_xpm(char *s);

#endif
