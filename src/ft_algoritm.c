/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_algoritm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:31:02 by lbellmas          #+#    #+#             */
/*   Updated: 2025/02/19 12:18:22 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_fdf.h"
#include "../printf/header/ft_printf.h"
#include <math.h>


void	draw_line_low(mlx_image_t *img, t_point inicial, t_point final)
{
	int formula;
	int dx;
	int dy;
	int step_x;
	int step_y;
	uint32_t color;
	int distance;
	int midpoint;

	dx = abs(final.x - inicial.x);
	dy = abs(final.y - inicial.y);
	step_x = (final.x > inicial.x) ? 1 : -1;
	step_y = (final.y > inicial.y) ? 1 : -1;

	ft_checkpoint(&final);
	ft_checkpoint(&inicial);
	color = inicial.color;

	// Calcular la distancia total de la línea
	distance = (dx > dy) ? dx : dy;
	midpoint = distance / 2;

	formula = (2 * dy) - dx;
	for (int i = 0; i <= distance; i++)
	{
		ft_checkpoint(&inicial);
		mlx_put_pixel(img, inicial.x, inicial.y, color);

		// Cambio de color en el punto medio
		if (i == midpoint)
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

/*void	draw_line_low(mlx_image_t *img, t_point inicial, t_point final)
{
	int formula;
	int dx;
	int dy;
	int step_x;
	int step_y;
	uint32_t	color;

	dx = abs(final.x - inicial.x);
	dy = abs(final.y - inicial.y);
	step_x = (final.x > inicial.x) ? 1 : -1;
	step_y = (final.y > inicial.y) ? 1 : -1;

	ft_checkpoint(&final);
	ft_checkpoint(&inicial);
	color = inicial.color;
	formula = (2 * dy) - dx;
	while (inicial.x != final.x)
	{
		ft_checkpoint(&inicial);
		mlx_put_pixel(img, inicial.x, inicial.y, color);
		if (formula > 0)
		{
			inicial.y += step_y;
			formula -= (2 * dx);
		}
		formula += (2 * dy);
		inicial.x += step_x;
		if (inicial.x > step_x + ((final.x - step_x) / 2))
			color = final.color;
		ft_checkpoint(&inicial);
	}
}*/

/*void	draw_line_low(mlx_image_t	*img, t_point inicial, t_point final)
{
	int	formula;
	int	y;
	int	dy;
	int	dx;

	dy = abs(final.y - inicial.y);
	dx = final.x - inicial.x;
	y = 1;
	if ((final.y - inicial.y) < 0)
		y = -1;
	formula = 2 * (final.y - inicial.y) - (final.x - inicial.x);
	while (inicial.x < final.x)
	{
		mlx_put_pixel(img, inicial.x, inicial.y, inicial.color);
		if (formula > 0)
		{
			inicial.y = inicial.y + y;
			formula = formula + (2 * (dy - dx));
		}
		else
			formula = formula + 2 * dy;
		inicial.x += 1;
	}
}*/

void	draw_line_high(mlx_image_t *img, t_point inicial, t_point final)
{
	int formula;
	int dx;
	int dy;
	int step_x;
	int step_y;
	uint32_t color;
	int distance;
	int midpoint;

	dx = abs(final.x - inicial.x);
	dy = abs(final.y - inicial.y);
	step_x = (final.x > inicial.x) ? 1 : -1;
	step_y = (final.y > inicial.y) ? 1 : -1;

	ft_checkpoint(&final);
	ft_checkpoint(&inicial);
	color = inicial.color;

	// Calcular la distancia total de la línea
	distance = (dx > dy) ? dx : dy;
	midpoint = distance / 2;

	formula = (2 * dx) - dy;
	for (int i = 0; i <= distance; i++)
	{
		ft_checkpoint(&inicial);
		mlx_put_pixel(img, inicial.x, inicial.y, color);

		// Cambio de color en el punto medio
		if (i == midpoint)
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

/*void	draw_line_high(mlx_image_t *img, t_point inicial, t_point final)
{
	int formula;
	int dx;
	int dy;
	int step_x;
	int step_y;
	uint32_t	color;

	dx = abs(final.x - inicial.x);
	dy = abs(final.y - inicial.y); // Asegurar valores absolutos
	step_x = (final.x > inicial.x) ? 1 : -1; // Dirección en X
	step_y = (final.y > inicial.y) ? 1 : -1; // Dirección en Y

	ft_checkpoint(&final);
	ft_checkpoint(&inicial);
	color = inicial.color;
	formula = (2 * dx) - dy;
	while (inicial.y != final.y) // Corrección: recorrer correctamente en Y
	{
		ft_checkpoint(&inicial);
		mlx_put_pixel(img, inicial.x, inicial.y, color);
		if (formula > 0)
		{
			inicial.x += step_x;
			formula -= (2 * dy);
		}
		formula += (2 * dx);
		inicial.y += step_y;
		if (step_y < 0)
		{
			if (abs(inicial.y) >= abs(final.y / 2))
				color = final.color;
		}
		else
		{
			if (abs(inicial.y) <= abs(final.y / 2))
				color = final.color;
		}
		ft_checkpoint(&inicial);
	}

}*/


/*void	draw_line_high(mlx_image_t	*img, t_point inicial, t_point final)
{
	int	formula;
	int	x;
	int	dy;
	int	dx;

	dx = abs(final.x - inicial.x);
	dy = final.y - inicial.y;
	x = 1;
	if ((final.x - inicial.x) < 0)
		x = -1;
	formula = 2 * (final.y - inicial.y) - (final.x - inicial.x);
	while (inicial.y < final.y)
	{
		ft_printf("X: inicial %i, final %i \n", inicial.x, final.x);
		ft_printf("Y: inicial %i, final %i \n", inicial.y, final.y);
		mlx_put_pixel(img, inicial.x, inicial.y, inicial.color);
		if (formula > 0)
		{
			inicial.x = inicial.x + x;
			formula = formula + (2 * dx - dy);
		}
		else
			formula = formula + (2 * dx);
		inicial.y += 1;
	}
}*/
