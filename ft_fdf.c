/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:54:34 by lbellmas          #+#    #+#             */
/*   Updated: 2025/02/03 15:30:22 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/ft_fdf.h"

int	main(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		return (-1);
	fd = ft_parsing(argc, argv[1]);
	if (fd == -1)
		return (0);
	ft_setup(fd);
	
	return (0);
}
