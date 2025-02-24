/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:26:54 by lbellmas          #+#    #+#             */
/*   Updated: 2025/02/24 12:35:43 by lbellmas         ###   ########.fr       */
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
	if (keydata.key == MLX_KEY_KP_SUBTRACT && keydata.action == MLX_PRESS && (*map).zoom > -9)
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
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		map->a_rightleft += 1;
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		map->a_rightleft -= 1;
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		map->a_updown += 1;
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		map->a_updown -= 1;
	if (keydata.key == MLX_KEY_Z && keydata.action == MLX_PRESS)
		map->a_rotation += 1;
	if (keydata.key == MLX_KEY_X && keydata.action == MLX_PRESS)
		map->a_rotation -= 1;
	if (keydata.key == MLX_KEY_U && keydata.action == MLX_PRESS)
		map->perspective = 3;
	if (keydata.key == MLX_KEY_Y && keydata.action == MLX_PRESS)
		map->perspective = 4;
	if (keydata.key == MLX_KEY_T && keydata.action == MLX_PRESS)
		map->perspective = 5;
	if (keydata.key == MLX_KEY_ENTER && keydata.action == MLX_PRESS)
	{
		map->a_rotation = 0;
		map->a_updown = 0;
		map->a_rightleft = 0;
		map->zoom = 0;
		map->pluswidth = 0;
		map->plusheight = 0;
	}
	if (keydata.key == MLX_KEY_0 && keydata.action == MLX_PRESS)
		map->select_color = 0;
	if (keydata.key == MLX_KEY_1 && keydata.action == MLX_PRESS)
		map->select_color = 1;
	if (keydata.key == MLX_KEY_2 && keydata.action == MLX_PRESS)
		map->select_color = 2;
	if (keydata.key == MLX_KEY_3 && keydata.action == MLX_PRESS)
		map->select_color = 3;
	if (keydata.key == MLX_KEY_4 && keydata.action == MLX_PRESS)
		map->select_color = 4;
	ft_check_draw(map);
}

/*void	ft_isometric(t_point *final)
{
	int	prev_y;

	prev_y = final->y;
	final->x = (final->x + final->y) * cos(0.785398);
	final->y = ((prev_y * sin(0.615472907)) - final->z);
}*/

void	ft_isometric(t_point *final)
{
	double	angle = 0.523599; // 30° en radianes
	double	prev_x = final->x;

	final->x = (prev_x - final->y) * cos(angle);
	final->y = (prev_x + final->y) * sin(angle) - final->z;
}

/*void	ft_parallel(t_point *final)
{
	double angle = 0.523599; // 30° en radianes

	double prev_x = final->x;
	double prev_y = final->y;

	final->x = (prev_x - prev_y) * cos(angle);
	final->y = (prev_x + prev_y) * sin(angle) - final->z; // Aplica la altura sobre el eje vertical
}*/

void	ft_parallel(t_point *final)
{
	final->x = final->x + final->z * 0.5;  // Controla cuánto influye la profundidad en X
	final->y = final->y + final->z * 0.5;  // Controla la inclinación sobre Y
}

void	ft_parallel_pure(t_point *final)
{
	final->x = final->x;  // No cambia
	final->y = final->y - final->z;  // Z controla la elevación vertical
}

void	ft_conic(t_point *final, double d)
{
	double prev_x = final->x;
	double prev_y = final->y;
	double scale;

	// d es la distancia al punto de fuga
	if (final->z != 0)
		scale = d / (d + final->z);
	else
		scale = 1;

	// Ajuste para que la figura esté "acostada"
	final->x = (prev_x - prev_y) * scale;
	final->y = ((prev_x + prev_y) * scale) - final->z;
}

/*void	ft_parallel(t_point *final)
{
	double	angle = 0.523599; // 30° en radianes (puedes ajustar)

	double	prev_x = final->x;
	double	prev_y = final->y;

	final->x = prev_x + final->z * cos(angle);
	final->y = prev_y + final->z * sin(angle);
}

void	ft_conic(t_point *final, double d)
{
	double	prev_x = final->x;
	double	prev_y = final->y;
	double	scale;

	// d es la distancia del punto de fuga (ajustable)
	if (final->z != 0)
		scale = d / (d + final->z);
	else
		scale = 1;

	final->x = prev_x * scale;
	final->y = prev_y * scale;
}*/

void	ft_zoom(t_point *final, int	zoom, t_map *map)
{
	final->x = (((WIDTH - 100)/map->width) * final->x/2.5);
	final->z *= 10;
	final->y = (((HEIGHT - 100)/map->height) * final->y/2.5);
	if (zoom > -10)
	{
		final->x = final->x * (10 + zoom) / 10;
		final->y = final->y * (10 + zoom) / 10;
		final->z = final->z * (10 + zoom) / 10;
	}
}

void ft_rotation(t_point *point, t_map *map)
{
    double x, y, z;

    if (map->a_updown != 0)
    {
        x = point->x;
        y = point->y;
        z = point->z;
        
        point->y = (y * cos(map->a_updown * M_PI / 180)) - (z * sin(map->a_updown * M_PI / 180));
        point->z = (y * sin(map->a_updown * M_PI / 180)) + (z * cos(map->a_updown * M_PI / 180));
    }
    if (map->a_rightleft != 0)
    {
        x = point->x;
        y = point->y;
        z = point->z;
        
        point->x = (x * cos(map->a_rightleft * M_PI / 180)) + (z * sin(map->a_rightleft * M_PI / 180));
        point->z = (-x * sin(map->a_rightleft * M_PI / 180)) + (z * cos(map->a_rightleft * M_PI / 180));
    }
    if (map->a_rotation != 0)
    {
        x = point->x;
        y = point->y;
        z = point->z;
        
        point->x = (x * cos(map->a_rotation * M_PI / 180)) - (y * sin(map->a_rotation * M_PI / 180));
        point->y = (x * sin(map->a_rotation * M_PI / 180)) + (y * cos(map->a_rotation * M_PI / 180));
    }
}
//0xFFA500ff
void	ft_selectcolor(t_point *point, char *original, int minus)
{
	uint32_t temp = (uint32_t)ft_atohexa(original);
	if ((temp & 0xFF000000) == 0)
		temp |= 0xFF000000;
	uint8_t A = (temp >> 24) & 0xFF;
	uint8_t R = (temp >> 16) & 0xFF;
	uint8_t G = (temp >> 8) & 0xFF;
	uint8_t B = temp & 0xFF;
	float factor = (float)point->z / 255.0f;
	if (factor > 1.0f)
		factor = 1.0f;
	if (minus > 2)
	R = R + (255 - R) * factor;
	if (minus > 1)
	G = G + (255 - G) * factor;
	if (minus > 0)
	B = B + (255 - B) * factor;

	point->color = (R << 24) | (G << 16) | (B << 8) | A;
}

void	ft_arrange_point(t_point *final, t_point *point, t_map *map)
{
	int temp;
	final->x = point->x;
	temp = point->y;
	final->y = point->z;
	final->z = temp;
	if (map->select_color == 0)
		final->color = point->color;
	else if (map->select_color == 2)
		ft_selectcolor(final, "FFA500ff", 2);
	else if (map->select_color == 1)
		ft_selectcolor(final, "FFA500", 3);
	else if (map->select_color == 3)
		ft_selectcolor(final, "000000", 1);
	else
		ft_selectcolor(final, "0F000000", 0);
	ft_zoom(final, map->zoom, map);
	if (map->perspective == 1)
		ft_isometric(final); // o otra perspectiva
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
