/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyhook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:56:24 by lbellmas          #+#    #+#             */
/*   Updated: 2025/02/27 11:57:26 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_fdf.h"

static void	my_keyhook_ext2(mlx_key_data_t keydata, t_map *map)
{
	if (keydata.key == MLX_KEY_ENTER && keydata.action == MLX_PRESS)
	{
		map->a_rotation = 0;
		map->a_updown = 0;
		map->a_rightleft = 0;
		map->zoom = 0;
		map->pluswidth = 0;
		map->plusheight = 0;
	}
	else if (keydata.key == MLX_KEY_I && keydata.action == MLX_PRESS)
		map->perspective = 1;
	else if (keydata.key == MLX_KEY_0 && keydata.action == MLX_PRESS)
		map->select_color = 0;
	else if (keydata.key == MLX_KEY_1 && keydata.action == MLX_PRESS)
		map->select_color = 1;
	else if (keydata.key == MLX_KEY_2 && keydata.action == MLX_PRESS)
		map->select_color = 2;
	else if (keydata.key == MLX_KEY_3 && keydata.action == MLX_PRESS)
		map->select_color = 3;
	else if (keydata.key == MLX_KEY_4 && keydata.action == MLX_PRESS)
		map->select_color = 4;
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		map->plusheight += 50;
}

static void	my_keyhook_ext(mlx_key_data_t keydata, t_map *map)
{
	if (keydata.key == MLX_KEY_O && keydata.action == MLX_PRESS)
		map->perspective = 0;
	else if (keydata.key == MLX_KEY_P && keydata.action == MLX_PRESS)
		map->perspective = 2;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		map->a_rightleft += 1;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		map->a_rightleft -= 1;
	else if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		map->a_updown += 1;
	else if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		map->a_updown -= 1;
	else if (keydata.key == MLX_KEY_Z && keydata.action == MLX_PRESS)
		map->a_rotation += 1;
	else if (keydata.key == MLX_KEY_X && keydata.action == MLX_PRESS)
		map->a_rotation -= 1;
	else if (keydata.key == MLX_KEY_U && keydata.action == MLX_PRESS)
		map->perspective = 3;
	else if (keydata.key == MLX_KEY_Y && keydata.action == MLX_PRESS)
		map->perspective = 4;
	else if (keydata.key == MLX_KEY_T && keydata.action == MLX_PRESS)
		map->perspective = 5;
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_map	*map;

	map = (t_map *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(((t_map *)param)->mlx);
		mlx_terminate(((t_map *)param)->mlx);
		ft_errase_map(map);
		exit(1);
	}
	else if (keydata.key == MLX_KEY_KP_ADD && keydata.action == MLX_PRESS)
		(*map).zoom += 1;
	else if (keydata.key == MLX_KEY_KP_SUBTRACT && keydata.action
		== MLX_PRESS && (*map).zoom > -9)
		(*map).zoom -= 1;
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		map->pluswidth -= 50;
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		map->pluswidth += 50;
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		map->plusheight -= 50;
	my_keyhook_ext(keydata, map);
	my_keyhook_ext2(keydata, map);
	ft_check_draw(map);
}
