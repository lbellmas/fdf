/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_algoritm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:31:02 by lbellmas          #+#    #+#             */
/*   Updated: 2025/02/27 12:01:15 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_fdf.h"
#include <math.h>

void	ft_init_draw(int *variable, int *diferencial, int final, int inicial)
{
	*diferencial = abs(final - inicial);
	if (final > inicial)
		*variable = 1;
	else
		*variable = -1;
}

void	ft_check_points(t_point *inicial, t_point *final)
{
	if (inicial->x < 0)
		final->x = final->x + inicial->x;
	if (inicial->y < 0)
		final->y = final->y + inicial->y;
	ft_checkpoint(final);
	ft_checkpoint(inicial);
}

void	draw_line_low(mlx_image_t *img, t_point inicial, t_point final,
		uint32_t color)
{
	int	formula;
	int	dx;
	int	dy;
	int	step_x;
	int	step_y;

	ft_init_draw(&step_x, &dx, final.x, inicial.x);
	ft_init_draw(&step_y, &dy, final.y, inicial.y);
	ft_check_points(&inicial, &final);
	formula = (2 * dy) - dx;
	while (inicial.x != final.x)
	{
		ft_checkpoint(&inicial);
		mlx_put_pixel(img, inicial.x, inicial.y, color);
		if (abs(inicial.x - final.x) == (dx / 2))
			color = final.color;
		if (formula > 0)
		{
			inicial.y += step_y;
			formula -= (2 * dx);
		}
		formula += (2 * dy);
		inicial.x += step_x;
		ft_checkpoint(&inicial);
	}
}

void	draw_line_high(mlx_image_t *img, t_point inicial, t_point final,
		uint32_t color)
{
	int	formula;
	int	dx;
	int	dy;
	int	step_x;
	int	step_y;

	ft_init_draw(&step_x, &dx, final.x, inicial.x);
	ft_init_draw(&step_y, &dy, final.y, inicial.y);
	ft_check_points(&inicial, &final);
	formula = (2 * dx) - dy;
	while (inicial.y != final.y)
	{
		ft_checkpoint(&inicial);
		mlx_put_pixel(img, inicial.x, inicial.y, color);
		if (abs(inicial.y - final.y) == (dy / 2))
			color = final.color;
		if (formula > 0)
		{
			inicial.x += step_x;
			formula -= (2 * dy);
		}
		formula += (2 * dx);
		inicial.y += step_y;
		ft_checkpoint(&inicial);
	}
}
