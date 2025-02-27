/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extras2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:52:17 by lbellmas          #+#    #+#             */
/*   Updated: 2025/02/27 12:00:43 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../header/ft_fdf.h"

static void	ft_rotation_ext(t_point *point, t_map *map)
{
	int	x;
	int	y;

	if (map->a_rotation != 0)
	{
		x = point->x;
		y = point->y;
		point->x = (x * cos(map->a_rotation * M_PI / 180))
			- (y * sin(map->a_rotation * M_PI / 180));
		point->y = (x * sin(map->a_rotation * M_PI / 180))
			+ (y * cos(map->a_rotation * M_PI / 180));
	}
}

void	ft_rotation(t_point *point, t_map *map)
{
	int	x;
	int	y;
	int	z;

	if (map->a_updown != 0)
	{
		x = point->x;
		y = point->y;
		z = point->z;
		point->y = (y * cos(map->a_updown * M_PI / 180))
			- (z * sin(map->a_updown * M_PI / 180));
		point->z = (y * sin(map->a_updown * M_PI / 180))
			+ (z * cos(map->a_updown * M_PI / 180));
	}
	if (map->a_rightleft != 0)
	{
		x = point->x;
		y = point->y;
		z = point->z;
		point->x = (x * cos(map->a_rightleft * M_PI / 180))
			+ (z * sin(map->a_rightleft * M_PI / 180));
		point->z = (-x * sin(map->a_rightleft * M_PI / 180))
			+ (z * cos(map->a_rightleft * M_PI / 180));
	}
	ft_rotation_ext(point, map);
}

static void	ft_selectcolor(t_point *point, char *original, int minus)
{
	uint8_t	a;
	uint8_t	b;
	uint8_t	r;
	uint8_t	g;

	point->color = (uint32_t)ft_atohexa(original);
	if ((point->color & 0xFF000000) == 0)
		point->color |= 0xFF000000;
	a = (point->color >> 24) & 0xFF;
	r = (point->color >> 16) & 0xFF;
	g = (point->color >> 8) & 0xFF;
	b = point->color & 0xFF;
	if (minus > 2)
		r = r + (255 - r) * (point->z / 255.0f);
	if (minus > 1)
		g = g + (255 - g) * (point->z / 255.0f);
	if (minus > 0)
		b = b + (255 - b) * (point->z / 255.0f);
	point->color = (r << 24) | (g << 16) | (b << 8) | a;
}

void	ft_control_color(t_point *final, t_point *point, t_map *map)
{
	if (map->select_color == 0)
		final->color = point->color;
	else if (map->select_color == 2)
		ft_selectcolor(final, "FFA500ff", 2);
	else if (map->select_color == 1)
		ft_selectcolor(final, "FFA500", 3);
	else if (map->select_color == 3)
		ft_selectcolor(final, "000000", 1);
	else
		ft_selectcolor(final, "FFFFFFFF", 0);
}

void	ft_arrange_point(t_point *final, t_point *point, t_map *map)
{
	int	temp;

	final->x = point->x;
	temp = point->y;
	final->y = point->z;
	final->z = temp;
	ft_control_color(final, point, map);
	ft_zoom(final, map->zoom, map);
	if (map->perspective == 1)
		ft_isometric(final);
	if (map->perspective == 2)
	{
		final->y = temp * 10;
		final->z = point->z;
	}
	if (map->perspective == 3)
		ft_parallel(final);
	if (map->perspective == 4)
		ft_conic(final, 500);
	if (map->perspective == 5)
		ft_parallel_pure(final);
	ft_rotation(final, map);
	final->x = final->x + 1000 + map->pluswidth;
	final->y = final->y + 450 + map->plusheight;
}
