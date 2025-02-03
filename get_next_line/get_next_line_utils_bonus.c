/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:32:40 by lbellmas          #+#    #+#             */
/*   Updated: 2024/11/22 14:28:27 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strdup(char *s)
{
	char	*p;
	size_t	len;

	len = ft_strlen(s);
	p = (char *)malloc((len + 1) * sizeof(char));
	if (!p)
		return (NULL);
	ft_strlcpy(p, s, (len + 1));
	return (p);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	char		*str;
	size_t		len;
	size_t		p;

	p = 0;
	if (!s1 && !s2)
		return (ft_strdup(""));
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *)malloc(len * sizeof(char));
	if (!str)
		return (NULL);
	if (len <= 0)
		return (NULL);
	while (s1[p] != '\0')
	{
		str[p] = s1[p];
		p++;
	}
	free(s1);
	ft_strlcpy((str + p), s2, (len - p + 1));
	return (str);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = 0;
		i++;
	}
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	s;

	s = 0;
	if (size > 0)
	{
		while (src[s] != '\0' && s < (size - 1))
		{
			dst[s] = src[s];
			s++;
		}
		dst[s] = '\0';
	}
	return (ft_strlen(src));
}

size_t	ft_strlen(const char *str)
{
	size_t	p;

	p = 0;
	while (str[p] != '\0')
		p++;
	return (p);
}
