/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:19:08 by lbellmas          #+#    #+#             */
/*   Updated: 2025/02/27 12:01:57 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line/get_next_line_bonus.h"
#include "../header/ft_fdf.h"

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
		free(split[p]);
		p++;
	}
	free(str);
	free(split);
	return (nbrs);
}

long	ft_atohexa(char *str)
{
	int		p;
	int		sign;
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
	while ((str[p] >= '0' && str[p] <= '9') || (str[p] >= 'A' && str[p] <= 'F')
		|| (str[p] >= 'a' && str[p] <= 'f'))
	{
		if (str[p] >= '0' && str[p] <= '9')
			num = num * 16 + (str[p] - '0');
		else if (str[p] >= 'A' && str[p] <= 'F')
			num = num * 16 + (str[p] - 'A' + 10);
		else
			num = num * 16 + (str[p] - 'a' + 10);
		p++;
	}
	return (num * sign);
}

void	ft_putcolor(t_point *point, char *str)
{
	uint8_t	a;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	point->color = (uint32_t)ft_atohexa(str);
	if ((point->color & 0xFF000000) == 0)
		point->color |= 0xFF000000;
	a = (point->color >> 24) & 0xFF;
	r = (point->color >> 16) & 0xFF;
	g = (point->color >> 8) & 0xFF;
	b = point->color & 0xFF;
	point->color = (r << 24) | (g << 16) | (b << 8) | a;
}

void	ft_map_color(char **split, t_map *map, int p, int loop)
{
	if (ft_strchr(split[p], ','))
		ft_putcolor(map->points[p + loop],
			(ft_strchr(split[p], ',') + 3));
	else
		map->points[p + loop]->color = 0x808080FF;
	free(split[p]);
}

void	ft_colors(t_map *map, int fd, char *argv, char *str)
{
	char	**split;
	int		p;
	int		loop;
	char	*temp;

	fd = open(argv, O_RDONLY);
	loop = 0;
	str = get_next_line(fd);
	while (str)
	{
		temp = ft_strtrim(str, "\n");
		split = ft_split(temp, ' ');
		p = -1;
		while (split[++p])
			ft_map_color(split, map, p, loop);
		loop += p;
		free(temp);
		free(str);
		free(split);
		str = get_next_line(fd);
	}
	close (fd);
}
