/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:02:31 by lbellmas          #+#    #+#             */
/*   Updated: 2025/02/27 12:03:03 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../printf/header/ft_printf.h"
#include "../header/ft_fdf.h"
#include <fcntl.h>

int	ft_parsing(char *argv)
{
	int	fd;

	if (ft_strncmp((argv + (ft_strlen(argv) - 4)), ".fdf", 4))
		return (-1);
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return (-1);
	return (fd);
}
