/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:19:08 by lbellmas          #+#    #+#             */
/*   Updated: 2025/02/14 16:36:45 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../printf/header/ft_printf.h"
#include "../header/ft_fdf.h"

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

void	ft_clear(int **matrix, int i)
{
	while (i)
	{
		free ((matrix[i - 1]));
		i--;
	}
	free (matrix);
}
