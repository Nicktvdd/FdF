/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:17:36 by nvan-den          #+#    #+#             */
/*   Updated: 2023/02/02 14:11:07 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_line(t_data *data, int x1, int y1, int x2, int y2, int number)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int x, y, d, s1, s2;
	
    if (x1 < x2)
        s1 = 1;
    else
        s1 = -1;
    if (y1 < y2)
        s2 = 1;
    else
        s2 = -1;
    if (dx > dy)
    {
        d = 2 * dy - dx;
        for (x = x1, y = y1; x != x2; x += s1)
        {
            int x_iso = x - y;
            int y_iso = (x + y) / 2;
			if (number > 0)
				my_mlx_pixel_put(data, x_iso, y_iso, 0xFF0000);
			else
        		my_mlx_pixel_put(data, x_iso, y_iso, 0xFFFFFF);            
				if (d > 0)
            {
                y += s2;
                d -= 2 * dx;
            }
            d += 2 * dy;
        }
    }
    else
    {
        d = (2 * dx - dy);
        for (x = x1, y = y1; y != y2; y += s2)
        {
            int x_iso = x - y;
            int y_iso = (x + y) / 2;
			if (number > 0)
				my_mlx_pixel_put(data, x_iso, y_iso, 0xFF0000);
			else
        		my_mlx_pixel_put(data, x_iso, y_iso, 0xFFFFFF);
            if (d > 0)
            {
                x += s1;
                d -= 2 * dy;
            }
            d += 2 * dx;
        }
    }
	number = 0;
}

/* 		if (map[i][j + 1])
			nextnumber = ft_atoi(map[i][j + 1]);
		else
			nextnumber = 0; */
			
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
    while (map[i] != NULL)
    {
        while (map[i][j] != NULL)
        {
			ft_printf("%i ", j);
            number = (ft_atoi(map[i][j]));
			if (map[i][j + 1])
				nextnumber = (ft_atoi(map[i][j + 1]));
			else
				nextnumber = 0;
			if (map[i + 1])
				lownumber = (ft_atoi(map[i + 1][j]));
			else
				lownumber = 0;
			x_iso = data->x /* - number */;
			y_iso = data->y /* - number */;
			if (map[i][j + 1] != NULL)
            	draw_line(data, x_iso - number, y_iso - number, x_iso + CELL_SIZE - nextnumber, y_iso - nextnumber, number);
			if (map[i + 1] != NULL)
				draw_line(data, x_iso - number, y_iso - number, x_iso - lownumber, y_iso + CELL_SIZE - lownumber, number);
            data->x += CELL_SIZE;
            j++;
        }
        j = 0;
        data->x = WIDTH / 2;
        data->y += CELL_SIZE;
        i++;
		ft_printf("\n");
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

/* int		key_press(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == 65362)
		data->y -= 10;
	else if (keycode == 65364)
		data->y += 10;
	else if (keycode == 65361)
		data->x -= 10;
	else if (keycode == 65363)
		data->x += 10;
	return (0);
} */


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
	//mlx_hook(mlx_win, 2, 1L<<0, key_press, &img);
	mlx_loop(mlx);
	return (0);
}
