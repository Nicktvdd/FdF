/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:17:36 by nvan-den          #+#    #+#             */
/*   Updated: 2023/03/03 14:42:13 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	plot_line(t_data *data, int start_x, int start_y, int end_x, int end_y)
{
	t_plot	plot;
	
	plot.delta_x = end_x - start_x;
	plot.delta_y = end_y - start_y;
	plot.end_x = end_x;
	plot.end_y = end_y;
	if (abs(end_y - start_y) > abs(end_x - start_x))
	{
		plot.delta_x = start_x - end_x;
		plot.delta_y = start_y - end_y;
		plot.end_y = start_y;
		plot_line_low(data, end_x, end_y, plot);
		plot.delta_x = end_x - start_x;
		plot.delta_y = end_y - start_y;
		plot.end_y = end_y;
		plot_line_low(data, start_x, start_y, plot);
	}
	else
	{
		plot.delta_x = start_x - end_x;
		plot.delta_y = start_y - end_y;
		plot.end_y = start_x;
		plot_line_high(data, end_x, end_y, plot);
		plot.delta_x = end_x - start_x;
		plot.delta_y = end_y - start_y;
		plot.end_y = end_y;
		plot_line_high(data, start_x, start_y, plot);
	}
}

void	plot_line_low(t_data *data, int start_x, int start_y, t_plot plot)
{
	plot.step = 1;
	if (plot.delta_x < 0)
	{
		plot.step = -1;
		plot.delta_x *= -1;
	}
	plot.error = 2 * plot.delta_x - plot.delta_y;
	plot.current_x = start_x;
	plot.current_y = start_y;
	while (plot.current_y++ < plot.end_y)
	{
		plot.x_iso = plot.current_x - plot.current_y;
		plot.y_iso = (plot.current_x + plot.current_y) / 2;
		if (data->nr > 0)
			my_mlx_pixel_put(data, plot.x_iso, plot.y_iso, 0xFF0000);
		else
			my_mlx_pixel_put(data, plot.x_iso, plot.y_iso, 0xFFFFFF);
		if (plot.error > 0)
		{
			plot.current_x += plot.step;
			plot.error += 2 * (plot.delta_x - plot.delta_y);
		}
		else
			plot.error += 2 * plot.delta_x;
	}
}

void	plot_line_high(t_data *data, int start_x, int start_y, t_plot plot)
{
	plot.step = 1;
	if (plot.delta_y < 0)
	{
		plot.step = -1;
		plot.delta_y *= -1;
	}
	plot.error = 2 * plot.delta_y - plot.delta_x;
	plot.current_x = start_x;
	plot.current_y = start_y;
	while (plot.current_x++ < plot.end_x)
	{
		plot.x_iso = plot.current_x - plot.current_y;
		plot.y_iso = (plot.current_x + plot.current_y) / 2;
		if (data->nr > 0)
			my_mlx_pixel_put(data, plot.x_iso, plot.y_iso, 0xFF0000);
		else
			my_mlx_pixel_put(data, plot.x_iso, plot.y_iso, 0xFFFFFF);
		if (plot.error > 0)
		{
			plot.current_y += plot.step;
			plot.error += 2 * (plot.delta_y - plot.delta_x);
		}
		else
			plot.error += 2 * plot.delta_y;
	}
}

void	draw_grid(t_data *data, char ***map)
{
	data->y = 0;
	while (map[++data->i])
	{
		data->x = WIDTH / 2;
		while (map[data->i][++data->j])
		{
			if (map[data->i][data->j][0] != '\n')
			data->nr = (ft_atoi(map[data->i][data->j]));
			if (map[data->i][data->j + 1])
				data->nxtnr = (ft_atoi(map[data->i][data->j + 1]));
			if (map[data->i + 1])
				data->lownr = (ft_atoi(map[data->i + 1][data->j]));
			if (map[data->i][data->j + 1] && map[data->i][data->j])
				plot_line(data, data->x - data->nr, data->y - data->nr, data->x
					+ CELL_SIZE - data->nxtnr, data->y - data->nxtnr); // plot high
			if (map[data->i + 1] && map[data->i])
				plot_line(data, data->x - data->nr, data->y - data->nr, data->x
					- data->lownr, data->y + CELL_SIZE - data->lownr); // plot low
			data->x += CELL_SIZE;
		}
		data->j = 0;
		data->y += CELL_SIZE;
	}
}

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	char	***map;

	map = parse_map(argc, argv);
	if (!map)
		return (1);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "Grid_FDF");
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	img.mlx = mlx;
	img.window = mlx_win;
	img.x = WIDTH / 2;
	img.y = HEIGHT / 2;
	draw_grid(&img, map);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_hook(mlx_win, 2, 1L << 0, key_press_exit, 0);
	mlx_hook(mlx_win, 17, 1L << 17, close_window, 0);
	mlx_loop(mlx);
	return (0);
}
