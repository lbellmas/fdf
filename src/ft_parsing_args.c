/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:02:31 by lbellmas          #+#    #+#             */
/*   Updated: 2025/02/10 12:28:12 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_fdf.h"
#include "../printf/header/ft_printf.h"
#include <fcntl.h>

int	ft_parsing(char *argv)
{
	int	fd;

	if (ft_strncmp((argv + (ft_strlen(argv) - 4)), ".fdf", 4))
		return (-1);
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return (-1);
	ft_printf("finish pars\n");
	return (fd);
}

int	ft_check_matrix(int **matrix)
{
	int	y;

	y = 1;
	while (matrix[y])
	{
		if (ft_xcalculate(matrix[0]) != ft_xcalculate(matrix[y]))
			return (-1);
		y++;
	}
	ft_printf("finish check matrix\n");
	return (0);
}
