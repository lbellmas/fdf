/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:30:39 by lbellmas          #+#    #+#             */
/*   Updated: 2025/02/03 16:54:44 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_fdf.h"
#include "../get_next_line/get_next_line_bonus.h"



int	**ft_matrix_join(int **matrix, int *add)
{
	int	**new;
	int	x;
	int	y;

	y = 0;
	new = (int **)malloc(ft_ycalculate(matrix) * sizeof(int *));
	while (matrix[y])
	{
		new[y] = (int *)malloc(ft_xcalculate(matrix[y]) * sizeof(int));
		x = 0;
		while (matrix[y][x])
		{
			new[y][x] = matrix[y][x];
			x++;
		}
		y++;
	}
	x = 0;
	matrix[y] = (int *)malloc(ft_xcalculate(matrix[y]) * sizeof(int));
	while (add[x])
	{
		new[y][x] = add[x];
		x++;
	}
	return (new);
}

int	ft_setup(int fd)
{
	int	**matrix;
	int	*temp;

	str = get_next_line(fd);
	while (str)
	{
		temp = ft_atoiloop;
		matrix = ft_matrix_join(matrix, temp);
		str = get_next_line(fd);
	}
}
