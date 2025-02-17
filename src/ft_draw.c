/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:26:54 by lbellmas          #+#    #+#             */
/*   Updated: 2025/02/17 16:37:34 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../header/ft_fdf.h"
#include "../printf/header/ft_printf.h"

void	ft_check_draw(t_map *map);

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_map *map = (t_map *)param;
	param = (t_map *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(((t_map *)param)->mlx);
		mlx_terminate(((t_map *)param)->mlx);
		exit(1);
	}
	if (keydata.key == MLX_KEY_KP_ADD && keydata.action == MLX_PRESS)
		(*map).zoom += 1;
	if (keydata.key == MLX_KEY_KP_SUBTRACT && keydata.action == MLX_PRESS)
		(*map).zoom -= 1;
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		map->pluswidth -= 50;
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		map->pluswidth += 50;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		map->plusheight -= 50;
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		map->plusheight += 50;
	if (keydata.key == MLX_KEY_I && keydata.action == MLX_PRESS)
		map->perspective = 1;
	if (keydata.key == MLX_KEY_O && keydata.action == MLX_PRESS)
		map->perspective = 0;
	if (keydata.key == MLX_KEY_P && keydata.action == MLX_PRESS)
		map->perspective = 2;
	ft_check_draw(map);
}

void	ft_isometric(t_point *final)
{
	int	prev_x;
	int	prev_y;

	prev_y = final->y;
	prev_x = final->x;
	final->x = (final->x + final->y) * cos(0.785398);
	final->y = ((prev_y * sin(0.615472907)) - final->z);
}

void	ft_zoom(t_point *final, int	zoom, t_map *map)
{
	final->x = (((WIDTH - 100)/map->width) * final->x/2.5);
	final->z *= 10;
	final->y = (((HEIGHT - 100)/map->height) * final->y/2.5);
	zoom = zoom + 0;
	if (zoom > 1)
	{
		final->x = final->x * (zoom);
		final->y = final->y * (zoom);
		final->z = final->z * (zoom);
	}
}

void	ft_arrange_point(t_point *final, t_point *point, t_map *map)
{
	int temp;
	ft_printf("Y:%i\n", final->y);
	final->x = point->x;
	temp = point->y;
	final->y = point->z;
	final->z = temp;
	final->color = point->color;
	ft_zoom(final, map->zoom, map); // multi 2.5
	if (map->perspective == 1)
		ft_isometric(final); // o otra perspectiva
	if (map->perspective == 2)
		final->y = temp * 10;
//	ft_rotacion()// multiplicr por rotacion
	final->x = final->x + 1000 + map->pluswidth;
	final->y = final->y + 450 + map->plusheight;
}

void	ft_draw_line(t_point *a, t_point *b, t_map *map)
{
	t_point	a_final;
	t_point	b_final;

	ft_arrange_point(&a_final, a, map);
	ft_arrange_point(&b_final, b, map);
	mlx_put_pixel(map->img, a_final.x, a_final.y, 0x00000);
	if (abs(b_final.y - a_final.y) < abs(b_final.x - a_final.x))
	{
		if (a_final.x > b_final.x)
			draw_line_low(map->img, b_final, a_final);
		else
			draw_line_low(map->img, a_final, b_final);
	}
	else
	{
		if (a_final.y > b_final.y)
			draw_line_high(map->img, b_final, a_final);
		else
			draw_line_high(map->img, a_final, b_final);
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
	map->perspective = 1;
	map->plusheight = 0;
	map->plusheight = 0;
	ft_printf("draw\n");
	ft_check_draw(map);
	ft_printf("image to window\n");
	mlx_image_to_window(map->mlx, map->img, 0, 0);
	mlx_key_hook(map->mlx, my_keyhook, map);
	mlx_loop(map->mlx);
	mlx_delete_image(map->mlx, map->img);
	mlx_terminate(map->mlx);
	return ;
}
