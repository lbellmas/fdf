/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapping.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:47:50 by lbellmas          #+#    #+#             */
/*   Updated: 2025/02/11 11:08:48 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_fdf.h"
#include "../printf/header/ft_printf.h"

void	ft_checking_matrix(int **matrix, t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			ft_printf("%i", matrix[y][x]);
			x++;
		}
		ft_printf("\n");
		y++;
	}
}

t_map	*ft_mapping(int	**matrix, t_map *map)
{
	int		y;
	int		x;
	int		p;
	t_point	**points;

	y = 0;
	p = 0;
	points = (t_point **)malloc(map->height * map->width
			* sizeof(t_point *));
	ft_checking_matrix(matrix, map);
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			points[p] = (t_point *)malloc(sizeof(t_point));
			points[p]->x = x;
			points[p]->y = matrix[y][x];
			points[p]->z = y;
			p++;
			x++;
		}
		y++;
	}
	map->points = points;
	return (map);
}
