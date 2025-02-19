/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:54:34 by lbellmas          #+#    #+#             */
/*   Updated: 2025/02/19 12:40:53 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/ft_fdf.h"
#include "printf/header/ft_printf.h"

int	main(int argc, char **argv)
{
	int		fd;
	t_map	*map;

	if (argc != 2)
		return (ft_printf("INVALID ARG\n"));
	fd = ft_parsing(argv[1]);
	if (fd == -1)
		return (ft_printf("ERROR OPENING\n"));
	ft_printf("going to ft_setup\n");
	map = ft_setup(fd, argv[1]);
	map->mlx = mlx_init(WIDTH, HEIGHT, "FDF", true);
	map->img = mlx_new_image(map->mlx, WIDTH, HEIGHT);
//	ft_memset(map->img->pixels, 0, map->img->width * map->img->height
//			* sizeof(int32_t));
	if (map->mlx)
		ft_draw(map);
	return (0);
}
