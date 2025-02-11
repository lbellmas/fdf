/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:31:44 by lbellmas          #+#    #+#             */
/*   Updated: 2025/02/10 17:01:04 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_H
# define FT_FDF_H
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include "../MLX42/include/MLX42/MLX42.h"
# define WIDTH 4480
# define HEIGHT 2520

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
} t_point;

typedef	struct s_map
{
	int		width;
	int		height;
	struct s_point	**points;
	mlx_t	*mlx;
	mlx_image_t	*img;
} t_map;

int	ft_parsing(char *argv);
int	ft_check_matrix(int **matrix);
void	ft_draw(t_map *map);
void	ft_draw_points(t_map *map);
t_map	*ft_mapping(int	**matrix, t_map *map);
int	ft_ycalculate(int **matrix);
int	ft_xcalculate(int *matrix);
int	**ft_matrix_join(int **matrix, int *add, t_map *map);
t_map	*ft_setup(int fd);
int	*ft_atoiloop(char *str, t_map *map);
void	ft_clear(int **matrix, int i);

#endif
