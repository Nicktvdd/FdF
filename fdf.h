/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:35:05 by nvan-den          #+#    #+#             */
/*   Updated: 2023/02/21 15:41:12 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <mlx.h>
# include <fcntl.h>
# include "libft/libft.h"

# define WIDTH 1920
# define HEIGHT 1080
# define CELL_SIZE 30

typedef struct s_data
{
	void	*mlx;
	void	*window;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	//break it here
	int		x;
	int		y;
	int		i;
	int		j;
	int		nr;
	int		nxtnr;
	int		lownr;
}			t_data;

typedef struct s_plot
{
	int	delta_x;
	int	delta_y;
	int	current_x;
	int	current_y;
	int	error;
	int	step;
	int	x_iso;
	int	y_iso;
}			t_plot;

typedef	struct	s_arg
{
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;
}			t_arg;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	plot_line_high(t_data *data, int start_x, int start_y, int end_x, int end_y, int color);
void	plot_line_low(t_data *data, int start_x, int start_y, int end_x, int end_y, int color);
void	plot_line(t_data *data, int start_x, int start_y, int end_x, int end_y, int color);
int		key_press_exit(int key);
int		close_window(void);
int		main(int argc, char **argv);
int		count_lines(int fd);
char	***parse_map(int argc, char **argv);

#endif