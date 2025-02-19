/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:19:08 by lbellmas          #+#    #+#             */
/*   Updated: 2025/02/19 16:09:28 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../printf/header/ft_printf.h"
#include "../get_next_line/get_next_line_bonus.h"
#include "../header/ft_fdf.h"

void	ft_black(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(map->img, x, y, 0x000000FF);
			x++;
		}
		y++;
	}
}

void ft_checkpoint(t_point *point)
{
	if (point->y >= HEIGHT)
		point->y = HEIGHT - 1;
	else if (point->y < 0)
		point->y = 0;
	if (point->x >= WIDTH)
		point->x = WIDTH - 1;
	else if (point->x < 0)
		point->x = 0;
}

int	ft_lenght(char **split)
{
	int	p;

	p = 0;
	while (split[p])
		p++;
	return (p);
}

int	*ft_atoiloop(char *str, t_map *map)
{
	int		*nbrs;
	int		p;
	char	**split;
	

	str = ft_strtrim(str, "\n");
	split = ft_split(str, ' ');
	p = 0;
	nbrs = (int *)malloc(ft_lenght(split) * sizeof(int));
	map->width = ft_lenght(split);
	map = NULL;
	while (split[p])
	{
		nbrs[p] = ft_atoi(split[p]);
		if (!nbrs && str[p] != '0')
			return (NULL);
		p++;
	}
	return (nbrs);
}

long	ft_atohexa(char *str)
{
	int	p;
	int	sign;
	long	num;

	sign = 1;
	p = 0;
	num = 0;
	if (str[p] == '-' || str[p] == '+')
	{
		if (str[p] == '-')
			sign = -sign;
		p++;
	}
	while ((str[p] >= '0' && str[p] <= '9') || (str[p] >= 'A' && str[p] <= 'F') || (str[p] >= 'a' && str[p] <= 'f'))
	{
		if (str[p] >= '0' && str[p] <= '9')
			num = num * 16 + (str[p] - '0');
		else if(str[p] >= 'A' && str[p] <= 'F')
			num = num * 16 + (str[p] - 'A' + 10);
		else
			num = num * 16 + (str[p] - 'a' + 10);
		p++;
	}
	return (num * sign);
}

void	ft_putcolor(t_point *point, char *str)
{
	uint32_t temp = (uint32_t)ft_atohexa(str);
	if ((temp & 0xFF000000) == 0)
		temp |= 0xFF000000;
	uint8_t A = (temp >> 24) & 0xFF;
	uint8_t R = (temp >> 16) & 0xFF;
	uint8_t G = (temp >> 8) & 0xFF;
	uint8_t B = temp & 0xFF;
	point->color = (R << 24) | (G << 16) | (B << 8) | A;
}

void	ft_colors(t_map *map, int fd, char *argv, char *str)
{
	char **split;
	int	p;
	int	loop;

	fd = open(argv, O_RDONLY);
	loop = 0;
	str = get_next_line(fd);
	while (str)
	{
		str = ft_strtrim(str, "\n");
		split = ft_split(str, ' ');
		p = 0;
		while (split[p])
		{
			if (ft_strchr(split[p], ','))
				ft_putcolor(map->points[p + loop], (ft_strchr(split[p], ',') + 3));
			else
				map->points[p + loop]->color = 0x808080FF;
			p++;
		}
		loop += p;
		str = get_next_line(fd);
	}
	close (fd);
}

void	ft_clear(int **matrix, int i)
{
	while (i)
	{
		free ((matrix[i - 1]));
		i--;
	}
	free (matrix);
}
