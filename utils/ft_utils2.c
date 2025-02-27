/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:37:52 by lbellmas          #+#    #+#             */
/*   Updated: 2025/02/27 12:02:05 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line/get_next_line_bonus.h"
#include "../header/ft_fdf.h"

void	ft_black(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(map->img, x, y, 0x000000FF);
			x++;
		}
		y++;
	}
}

void	ft_checkpoint(t_point *point)
{
	if (!point)
		return ;
	if (point->y >= HEIGHT)
		point->y = HEIGHT - 1;
	else if (point->y < 0)
		point->y = 0;
	if (point->x >= WIDTH)
		point->x = WIDTH - 1;
	else if (point->x < 0)
		point->x = 0;
}

int	ft_lenght(char **split)
{
	int	p;

	p = 0;
	while (split[p])
		p++;
	return (p);
}

void	ft_errase_map(t_map *map)
{
	int	i;

	if (map && map->points)
	{
		i = map->height * map->width;
		while (i)
		{
			free(map->points[i - 1]);
			i--;
		}
		free(map->points);
	}
	free(map);
}

void	ft_clear(int **matrix, int height)
{
	while (height)
	{
		free ((matrix[height - 1]));
		height--;
	}
	free (matrix);
}
