/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_algoritm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:31:02 by lbellmas          #+#    #+#             */
/*   Updated: 2025/02/12 16:53:16 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_fdf.h"
#include "../printf/header/ft_printf.h"

t_point	ft_right_up(t_point a_final, t_point b_final)
{
	if ((((b_final.x - a_final.x) * 2) - (b_final.y - a_final.y)) > 0)
	{
		a_final.x += 1;
		a_final.y -= 1;
	}
	else
		a_final.x += 1;
	ft_printf("b_finalx %i, a_final %i \n", b_final.x, a_final.x);
	ft_printf("b_finaly %i, a_final %i \n", b_final.y, a_final.y);
	ft_printf("rightup");
	return (a_final);
}

t_point	ft_left_up(t_point a_final, t_point b_final)
{
	if ((((a_final.x - b_final.x) * 2) - (a_final.y - b_final.y)) > 0)
	{
		a_final.x -= 1;
		a_final.y -= 1;
	}
	else
		a_final.x -= 1;
	ft_printf("b_finalx %i, a_final %i \n", b_final.x, a_final.x);
	ft_printf("b_finaly %i, a_final %i \n", b_final.y, a_final.y);
	ft_printf("leftup");
	return (a_final);
}

t_point	ft_right(t_point a_final, t_point b_final)
{
	if ((((b_final.y - a_final.y) * 2) - (b_final.x - a_final.x)) > 0)
	{
		a_final.x += 1;
		a_final.y += 1;
	}
	else
		a_final.x += 1;
	ft_printf("a_finalx %i, b_final %i \n", b_final.x, a_final.x);
	ft_printf("a_finaly %i, b_final %i \n", b_final.y, a_final.y);
	ft_printf("right");
	return (a_final);
}

t_point	ft_left(t_point a_final, t_point b_final)
{
	if ((((a_final.x - b_final.x) * 2) - (a_final.y - b_final.y)) > 0)
	{
		a_final.x -= 1;
		a_final.y += 1;
	}
	else
		a_final.x -= 1;
	ft_printf("a_finalx %i, b_final %i \n", b_final.x, a_final.x);
	ft_printf("a_finaly %i, b_final %i \n", b_final.y, a_final.y);
	ft_printf("left");
	return (a_final);
}
