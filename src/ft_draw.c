/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:26:54 by lbellmas          #+#    #+#             */
/*   Updated: 2025/02/27 12:00:09 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../header/ft_fdf.h"

void	ft_draw_line(t_point *a, t_point *b, t_map *map)
{
	t_point	a_final;
	t_point	b_final;

	ft_arrange_point(&a_final, a, map);
	ft_arrange_point(&b_final, b, map);
	ft_checkpoint(&a_final);
	ft_checkpoint(&b_final);
	if (abs(b_final.y - a_final.y) < abs(b_final.x - a_final.x))
	{
		if (a_final.x > b_final.x)
			draw_line_low(map->img, b_final, a_final, b_final.color);
		else
			draw_line_low(map->img, a_final, b_final, a_final.color);
	}
	else
	{
		if (a_final.y > b_final.y)
			draw_line_high(map->img, b_final, a_final, b_final.color);
		else
			draw_line_high(map->img, a_final, b_final, a_final.color);
	}
}

void	ft_check_draw(t_map *map)
{
	int	p;
	int	p_width;

	p = 0;
	p_width = 1;
	ft_black(map);
	while (p < (map->width * map->height))
	{
		if (p + 1 < (map->width * p_width))
			ft_draw_line(map->points[p], map->points[p + 1], map);
		else
			p_width++;
		if ((p + map->width) < ((map->height * map->width)))
			ft_draw_line(map->points[p], map->points[p + map->width], map);
		p++;
	}
}

void	ft_draw(t_map *map)
{
	map->perspective = 1;
	map->plusheight = 0;
	map->plusheight = 0;
	map->a_updown = 0;
	map->a_rightleft = 0;
	map->a_rotation = 0;
	map->select_color = 0;
	ft_check_draw(map);
	mlx_image_to_window(map->mlx, map->img, 0, 0);
	mlx_key_hook(map->mlx, my_keyhook, map);
	mlx_loop(map->mlx);
	mlx_delete_image(map->mlx, map->img);
	mlx_terminate(map->mlx);
	return ;
}
