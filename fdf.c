/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:17:36 by nvan-den          #+#    #+#             */
/*   Updated: 2023/02/14 13:45:24 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

void	plot_line(t_data *data, int start_x, int start_y, int end_x, int end_y, int color)
{
	if (abs(end_y - start_y) > abs(end_x - start_x))
	{
			plot_line_low(data, end_x, end_y, start_x, start_y, color);
			plot_line_low(data, start_x, start_y, end_x, end_y, color);
	}
	else 
	{
			plot_line_high(data, end_x, end_y, start_x, start_y, color);
			plot_line_high(data, start_x, start_y, end_x, end_y, color);
	}
}

void	plot_line_high(t_data *display_data, int start_x, int start_y, int end_x, int end_y, int color)
{
	int delta_x = end_x - start_x;
    int delta_y = end_y - start_y;
    int current_x, current_y, error, x_step, y_step;

	y_step = 1;
	x_step = 0;
	if (delta_y < 0)
	{
		y_step = -1;
		delta_y *= -1;
	}
	error = 2 * delta_y - delta_x;
	current_x = start_x;
	current_y = start_y;
	while (current_x++ < end_x)
	{
		int x_iso = current_x - current_y;
        int y_iso = (current_x + current_y) / 2;
		if (color > 0)
			my_mlx_pixel_put(display_data, x_iso, y_iso, 0xFF0000);
		else
        	my_mlx_pixel_put(display_data, x_iso, y_iso, 0xFFFFFF);          
		if (error > 0)
        {
        	current_y += y_step;
            error += 2 * (delta_y - delta_x);
        }
		else
        	error += 2 * delta_y;
	}
}

void	plot_line_low(t_data *display_data, int start_x, int start_y, int end_x, int end_y, int color)
{
    int delta_x = end_x - start_x;
    int delta_y = end_y - start_y;
    int current_x, current_y, error, x_step, y_step;

	x_step = 1;
	y_step = 0;
	if (delta_x < 0)
	{
		x_step = -1;
		delta_x *= -1;
	}
    error = 2 * delta_x - delta_y;
	current_x = start_x;
	current_y = start_y;
	while (current_y++ < end_y)
	{
		int x_iso = current_x - current_y;
        int y_iso = (current_x + current_y) / 2;
		if (color > 0)
			my_mlx_pixel_put(display_data, x_iso, y_iso, 0xFF0000);
		else
        	my_mlx_pixel_put(display_data, x_iso, y_iso, 0xFFFFFF);          
		if (error > 0)
        {
        	current_x += x_step;
            error += 2 * (delta_x - delta_y);
        }
		else
        	error += 2 * delta_x;
	}
}


void    draw_grid(t_data *data, char ***map)
{
    int x_iso;
    int y_iso;
    int i;
    int j;
	int number;
	int nextnumber;
	int lownumber;

    data->x = WIDTH / 2;
    data->y = 0;
    i = 0;
    j = 0;
    if (!map)
        return;
    while (map[i + 1])
    {
		i++;
        while (map[i][j + 1])
        {
			j++;
			if (map[i][j][0] != '\n')
            	number = (ft_atoi(map[i][j]));
			if (map[i][j + 1])
				nextnumber = (ft_atoi(map[i][j + 1]));
			else
				nextnumber = number;
			if (map[i + 1])
				lownumber = (ft_atoi(map[i + 1][j]));
			else
				lownumber = number;
			x_iso = data->x;
			y_iso = data->y;
			if (map[i][j + 1] && map[i][j])
            	plot_line(data, x_iso - number, y_iso - number, x_iso + CELL_SIZE - nextnumber, y_iso - nextnumber, number);
			if (map[i + 1] && map[i])
				plot_line(data, x_iso - number, y_iso - number, x_iso - lownumber, y_iso + CELL_SIZE - lownumber, number);
            data->x += CELL_SIZE;
        }
        j = 0;
        data->x = WIDTH / 2;
        data->y += CELL_SIZE;
    }
}


int	key_press_exit(int key)
{
	if (key == 53 || key == 17)
		exit(0);
	return(0);
}

int	close_window()
{
	exit(0);
}

int		main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	char	***map;

	map = parse_map(argc, argv);
	if (!map)
		return(1);
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
