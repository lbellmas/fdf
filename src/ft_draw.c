/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:26:54 by lbellmas          #+#    #+#             */
/*   Updated: 2025/02/12 16:55:44 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
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

void	ft_isometric(t_point *final)
{
	int	prev_x;

	prev_x = final->x;
	final->x = (final->x - final->y) * cos(0.785398);
	final->y = -(final->z) + (prev_x + final->y) * sin(0.615472907);
}

void	ft_zoom(t_point *final, int	zoom, t_map *map)
{
	final->x = (((WIDTH - 100)/map->width) * final->x)/2.5;
	final->z *= (zoom * 2);
	final->y = (((HEIGHT - 100)/map->height) * final->y)/2.5;
}

void	ft_arrange_point(t_point *final, t_point *point, t_map *map)
{
	int temp;
	map->zoom = 2.5;
	final->x = point->x;
	temp = point->y;
	final->y = point->z;
	final->z = temp;
	final->color = point->color;
	ft_zoom(final, map->zoom, map); // multi 2.5
	ft_isometric(final); // o otra perspectiva
//	ft_rotacion()// multiplicr por rotacion
	final->x = 1800 + final->x;
	final->y = 180 + final->y;
}

void	ft_draw_line(t_point *a, t_point *b, t_map *map)
{
	t_point	a_final;
	t_point	b_final;

	ft_arrange_point(&a_final, a, map);
	ft_arrange_point(&b_final, b, map);
	if ((b_final.x - a_final.x) < 0 && (b_final.y - a_final.y) <= 0)
	{
		while (a_final.x != b_final.x && a_final.y != b_final.y)
		{
			a_final = ft_left_up(a_final, b_final);
			mlx_put_pixel(map->img, a_final.x, a_final.y, 0x808080FF);
		}
	}
	else if ((b_final.x - a_final.x) < 0 && (b_final.y - a_final.y) >= 0)
	{
		while (a_final.x != b_final.x && a_final.y != b_final.y)
		{
			a_final = ft_left(a_final, b_final);
			mlx_put_pixel(map->img, a_final.x, a_final.y, 0xFF0000FF);
		}
	}
	else if ((b_final.y - a_final.y) <= 0)
	{
		while (a_final.x != b_final.x && a_final.y != b_final.y)
		{
			a_final = ft_right_up(a_final, b_final);
			mlx_put_pixel(map->img, a_final.x, a_final.y, 0x00FF00FF);
		}
	}
	else
	{
		while (a_final.x != b_final.x && a_final.y != b_final.y)
		{
			a_final = ft_right(a_final, b_final);
			mlx_put_pixel(map->img, a_final.x, a_final.y, 0xA020F0FF);
		}	
	}
}

void	ft_check_draw(t_map *map)
{
	int	p;
	int	p_width;

	p = 0;
	p_width = 1;
	ft_memset(map->img->pixels, 255, map->img->width * map->img->height
			* sizeof(int32_t));
	while (p < (map->width * map->height))
	{
		if (p + 1 < (map->width * p_width))
		{
			ft_draw_line(map->points[p], map->points[p + 1], map);
			ft_printf("horizontal\n");
		}
		else
			p_width++;
		if ((p + map->width) < ((map->height * map->width)))
		{
			ft_draw_line(map->points[p], map->points[p + map->width], map);
			ft_printf("vertical\n");
		}
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
