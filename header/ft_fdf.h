/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:31:44 by lbellmas          #+#    #+#             */
/*   Updated: 2025/02/26 12:38:33 by lbellmas         ###   ########.fr       */
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
	uint32_t	color;
} t_point;

typedef	struct s_map
{
	int	select_color;
	int	a_updown;
	int	a_rightleft;
	int	a_rotation;
	int	pluswidth;
	int	plusheight;
	int	zoom;
	int	perspective;
	int	rotation;
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
int	**ft_matrix_join(int **matrix, int *add, t_map *map);
t_map	*ft_setup(int fd, char *argv);
int	*ft_atoiloop(char *str, t_map *map);
void	ft_clear(int **matrix, int i);
void ft_checkpoint(t_point *point);
void	ft_colors(t_map *map, int fd, char *argv, char *str);
int	ft_lenght(char **split);
void	ft_black(t_map *map);
long	ft_atohexa(char *str);
void	ft_putcolor(t_point *point, char *str);
void	ft_errase_map(t_map *map);
// algoritm
void	draw_line_low(mlx_image_t	*img, t_point inicial, t_point final, uint32_t color);
void	draw_line_high(mlx_image_t	*img, t_point inicial, t_point final, uint32_t color);
//t_point	ft_right_up(t_point a_final, t_point b_final);
//t_point	ft_left_up(t_point a_final, t_point b_final);
//t_point	ft_right(t_point a_final, t_point b_final, t_map *map);
//t_point	ft_left(t_point a_final, t_point b_final, t_map *map);

#endif
