/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:17:36 by nvan-den          #+#    #+#             */
/*   Updated: 2023/02/10 13:24:15 by nvan-den         ###   ########.fr       */
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

void draw_line(t_data *display_data, int start_x, int start_y, int end_x, int end_y, int color)
{
    int delta_x = end_x - start_x;
    int delta_y = end_y - start_y;
    int current_x, current_y, error, x_step, y_step;

    if (start_x < end_x)
        x_step = 1;
    else
        x_step = -1;
    if (start_y < end_y)
        y_step = 1;
    else
        y_step = -1;
    if (delta_x > delta_y)
    {
        error = 0;//2 * delta_y - delta_x;
        for (current_x = start_x, current_y = start_y; current_x != end_x; current_x += x_step) // does this continue until next point?
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
                error -= 2 * delta_x;
            }
            error += 2 * delta_y;
        }
    }
    else
    {
        error = 2 * delta_x - delta_y;
        for (current_x = start_x, current_y = start_y; current_y != end_y; current_y += y_step) // does this continue until next point?
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
                error -= 2 * delta_y;
            }
            error += 2 * delta_x;
        }
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
	int lastnumber;
	int lownumber;
	int highnumber;

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
			//ft_printf("%s ", map[i][j]);
			if (map[i][j][0] != '\n')
            	number = (ft_atoi(map[i][j]));
			ft_printf("%i ", number);
			if (map[i][j + 1])
				nextnumber = (ft_atoi(map[i][j + 1]));
			else
				nextnumber = number;
			if (map[i + 1])
				lownumber = (ft_atoi(map[i + 1][j]));
			else
				lownumber = number;
			if (map[i][j - 1])
				lastnumber = (ft_atoi(map[i][j - 1]));
			else
				lastnumber = number;
			if (map[i - 1])
				highnumber = (ft_atoi(map[i - 1][j]));
			else
				highnumber = number;
			x_iso = data->x;
			y_iso = data->y;
			//if (map[i][j + 1] && map[i][j])
            	//draw_line(data, x_iso - number, y_iso - number, x_iso + CELL_SIZE - nextnumber, y_iso - nextnumber, number); // passing argument incorrect?
			//if (map[i + 1] && map[i])
				draw_line(data, x_iso - number, y_iso - number, x_iso - lownumber, y_iso + CELL_SIZE - lownumber, number);
            data->x += CELL_SIZE;
        }
        j = 0;
        data->x = WIDTH / 2;
        data->y += CELL_SIZE;
		ft_printf("\n\n");
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
	mlx_hook(mlx_win, 2, 1L<<0, key_press_exit, 0);
	mlx_hook(mlx_win, 17, 1L<<17, close_window, 0);
	mlx_loop(mlx);
	return (0);
}
