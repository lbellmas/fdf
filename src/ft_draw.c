/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:26:54 by lbellmas          #+#    #+#             */
/*   Updated: 2025/02/11 16:38:02 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_fdf.h"
#include "../printf/header/ft_printf.h"

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		ft_printf("close window\n");
		mlx_close_window(param);
		mlx_terminate(param);
		exit(1);
		return ;
	}
}

void	ft_isometric(t_point *final, t_point *point)
{
	final->x = (point->x - point->y) * cos(0.785398);
	final->y = -(point->z) + (point->x + point->y) * sin(0.615472907);
}

void	ft_arrange_point(t_point *final, t_point *point)
{
	ft_zoom() // multi 2.5
	ft_isometric(final, point); // o otra perspectiva
	ft_rotacion()// multiplicr por rotacion
	final->x = 1800 + final->x;
	final->y = 180 + final->y;
}

void	ft_draw_line(t_point *a, t_point *b)
{
	t_point	a_final;
	t_point	b_final;
	ft_arrange_point(&a_final, a);
	ft_arrange_point(&b_final, b);
	while ()
}

void	ft_check_draw(t_map *map)
{
	int	p;
	int	p_width;

	p = 0;
	p_width = 1;
	while (p < (width * height))
	{
		if (p + 1 < (map->width * p_width))
			ft_draw_line(map->points[p], map->points[p + 1]);
		else
			p_width++;
		if ((p + width) < map->height)
			ft_draw_line(map->points[p], map->points[p + width]);
		p++;
	}
}

void	ft_draw(t_map *map)
{
	ft_printf("draw\n");
	ft_check_draw(map);
	ft_printf("image to window\n");
	mlx_image_to_window(map->mlx, map->img, 0, 0);
	mlx_key_hook(map->mlx, my_keyhook, map->mlx);
	mlx_loop(map->mlx);
	mlx_delete_image(map->mlx, map->img);
	mlx_terminate(map->mlx);
	return ;
}
