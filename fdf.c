/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:17:36 by nvan-den          #+#    #+#             */
/*   Updated: 2023/03/08 10:25:55 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	plot_line(t_data *data, t_line line)
{
	t_plot	plot;

	plot.delta_x = line.start_x - line.end_x;
	plot.delta_y = line.start_y - line.end_y;
	plot.end_x = line.start_x;
	plot.end_y = line.start_y;
	if (abs(line.end_y - line.start_y) > abs(line.end_x - line.start_x))
	{
		plot_line_low(data, line.end_x, line.end_y, plot);
		plot.delta_x = line.end_x - line.start_x;
		plot.delta_y = line.end_y - line.start_y;
		plot.end_y = line.end_y;
		plot_line_low(data, line.start_x, line.start_y, plot);
	}
	else
	{
		plot_line_high(data, line.end_x, line.end_y, plot);
		plot.delta_x = line.end_x - line.start_x;
		plot.delta_y = line.end_y - line.start_y;
		plot.end_x = line.end_x;
		plot_line_high(data, line.start_x, line.start_y, plot);
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
	int	gridsize;

	gridsize = CELL_SIZE / count_map(map);
	data->y = 0;
	while (map[++data->i])
	{
		data->x = WIDTH / 2;
		while (map[data->i][++data->j])
		{
			if (map[data->i][data->j])
				data->nr = (ft_atoi(map[data->i][data->j]));
			if (map[data->i][data->j + 1])
				data->nxtnr = (ft_atoi(map[data->i][data->j + 1]));
			if (map[data->i + 1])
				data->lownr = (ft_atoi(map[data->i + 1][data->j]));
			if (map[data->i][data->j + 1] && map[data->i][data->j])
				plot_y(data, gridsize);
			if (map[data->i + 1] && map[data->i])
				plot_x(data, gridsize);
			data->x += gridsize;
		}
		data->j = 0;
		data->y += gridsize;
	}
}

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	char	***map;

	if (argc != 2)
		exit (2);
	map = parse_map(argv);
	if (!map)
		exit (1);
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
