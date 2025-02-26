/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:30:39 by lbellmas          #+#    #+#             */
/*   Updated: 2025/02/26 11:54:27 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_fdf.h"
#include "../get_next_line/get_next_line_bonus.h"

int	**ft_add_matrix(int	**new, int *add, t_map *map, int y)
{
	int	x;

	x = 0;
	while (x < map->width)
	{
		new[y][x] = add[x];
		x++;
	}
	return (new);
}

int	**ft_matrix_join(int **matrix, int *add, t_map *map)
{
	int	**new;
	int	x;
	int	y;

	y = 0;
	new = (int **)malloc((map->height + 1) * sizeof(int *));
	while (matrix && y < map->height)
	{
		new[y] = (int *)malloc(map->width * sizeof(int));
		x = 0;
		while (x < map->width)
		{
			new[y][x] = matrix[y][x];
			x++;
		}
		y++;
	}
	new[y] = (int *)malloc(map->width * sizeof(int));
	if (matrix)
		ft_clear(matrix, map->height);
	new = (ft_add_matrix(new, add, map, y));
	free(add);
	return (new);
}

t_map	*ft_setup(int fd, char *argv)
{
	int		**matrix;
	t_map	*map;
	char	*str;

	map = (t_map *)malloc(sizeof(t_map));
	matrix = NULL;
	map->height = 0;
	str = get_next_line(fd);
	while (str)
	{
		matrix = ft_matrix_join(matrix, ft_atoiloop(str, map), map);
		if (!matrix)
			return (ft_clear(matrix, map->height), NULL);
		map->height += 1;
		free (str);
		str = get_next_line(fd);
	}
	close(fd);
	map = ft_mapping(matrix, map);
	ft_colors(map, fd, argv, str);
	map->zoom = 0;
	ft_clear(matrix, map->height);
	return (map);
}
