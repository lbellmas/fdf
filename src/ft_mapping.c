/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapping.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:47:50 by lbellmas          #+#    #+#             */
/*   Updated: 2025/02/27 12:01:26 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_fdf.h"

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
