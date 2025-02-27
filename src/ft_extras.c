/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extras.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:49:22 by lbellmas          #+#    #+#             */
/*   Updated: 2025/02/27 12:00:36 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../header/ft_fdf.h"

void	ft_isometric(t_point *final)
{
	double	angle;
	double	prev_x;

	angle = 0.523599;
	prev_x = final->x;
	final->x = (prev_x - final->y) * cos(angle);
	final->y = (prev_x + final->y) * sin(angle) - final->z;
}

void	ft_parallel(t_point *final)
{
	final->x = final->x + final->z * 0.5;
	final->y = final->y + final->z * 0.5;
}

void	ft_parallel_pure(t_point *final)
{
	final->x = final->x;
	final->y = final->y - final->z;
}

void	ft_conic(t_point *final, double d)
{
	double	prev_x;
	double	prev_y;
	double	scale;

	prev_x = final->x;
	prev_y = final->y;
	if (final->z != 0)
		scale = d / (d + final->z);
	else
		scale = 1;
	final->x = (prev_x - prev_y) * scale;
	final->y = ((prev_x + prev_y) * scale) - final->z;
}

void	ft_zoom(t_point *final, int zoom, t_map *map)
{
	final->x = (((WIDTH - 100) / map->width) * final->x / 2.5);
	final->z *= 10;
	final->y = (((HEIGHT - 100) / map->height) * final->y / 2.5);
	if (zoom > -10)
	{
		final->x = final->x * (10 + zoom) / 10;
		final->y = final->y * (10 + zoom) / 10;
		final->z = final->z * (10 + zoom) / 10;
	}
}
