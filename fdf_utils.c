/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:22:23 by nvan-den          #+#    #+#             */
/*   Updated: 2023/03/07 15:26:21 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		dst = data->addr + (y * data->line_length + x
				* (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

int	key_press_exit(int key)
{
	if (key == 53 || key == 17)
		exit(0);
	return (0);
}

int	close_window(void)
{
	exit(0);
}

void	plot_x(t_data *data, int gridsize)
{
	t_line	line;

	line.start_x = data->x - data->nr;
	line.start_y = data->y - data->nr;
	line.end_x = data->x - data->lownr;
	line.end_y = data->y + (gridsize) - data->lownr;
	plot_line(data, line);
}

void	plot_y(t_data *data, int gridsize)
{
	t_line	line;

	line.start_x = data->x - data->nr;
	line.start_y = data->y - data->nr;
	line.end_x = data->x + (gridsize) - data->nxtnr;
	line.end_y = data->y - data->nxtnr;
	plot_line(data, line);
}
