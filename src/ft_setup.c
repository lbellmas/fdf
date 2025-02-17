/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:30:39 by lbellmas          #+#    #+#             */
/*   Updated: 2025/02/17 14:27:54 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_fdf.h"
#include "../get_next_line/get_next_line_bonus.h"

int	ft_ycalculate(int **matrix)
{
	int	p;

	if (matrix == NULL)
		return (0);
	p = 0;
	while (matrix[p])
		p++;
	return (p);
}

int	ft_xcalculate(int *matrix)
{
	int	p;

	p = 0;
	while (matrix[p])
		p++;
	return (p);
}

int	**ft_matrix_join(int **matrix, int *add, t_map *map)
{
	int	**new;
	int	x;
	int	y;
	int	first;

	first = 0;
	y = 0;
	if (matrix == NULL)
		first = 1;
	new = (int **)malloc((map->height + 1) * sizeof(int *));
	while (first == 0 && y < map->height)
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
	x = 0;
	new[y] = (int *)malloc(map->width * sizeof(int));
	while (x < map->width)
	{
		new[y][x] = add[x];
		x++;
	}
	if (matrix)
		ft_clear(matrix, map->height);
	return (new);
}

t_map	*ft_setup(int fd)
{
	int		**matrix;
	int		*temp;
	t_map	*map;
	char	*str;

	map = (t_map *)malloc(sizeof(t_map));
	matrix = NULL;
	map->height = 0;
	str = get_next_line(fd);
	while (str)
	{
		ft_printf("ft_atoiloop\n");
		temp = ft_atoiloop(str, map);
		if (!temp)
			return (ft_clear(matrix, ft_ycalculate(matrix)), NULL);
		ft_printf("ft_matrix\n");
		matrix = ft_matrix_join(matrix, temp, map);
		ft_printf("get_next_line\n");
		map->height += 1;
		free (str);
		str = get_next_line(fd);
	}
	//if (ft_check_matrix(matrix) != -1)
	map = ft_mapping(matrix, map);
	map->zoom = 1;
	//ft_clear(matrix, map->width); // PETA 
	ft_printf("finish setup\n");
	return (map);
}
