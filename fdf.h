/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:35:05 by nvan-den          #+#    #+#             */
/*   Updated: 2023/03/07 12:59:59 by nvan-den         ###   ########.fr       */
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

typedef struct s_data
{
	void	*mlx;
	void	*window;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		x;
	int		y;
	int		i;
	int		j;
	int		nr;
	int		nxtnr;
	int		lownr;
	int		cell_size;
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
	int	end_x;
	int	end_y;
}			t_plot;

typedef struct s_line {
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;
}				t_line;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	plot_line_high(t_data *data, int start_x, int start_y, t_plot plot);
void	plot_line_low(t_data *data, int start_x, int start_y, t_plot plot);
void	plot_line(t_data *data, t_line line);
int		key_press_exit(int key);
int		close_window(void);
int		main(int argc, char **argv);
int		count_lines(int fd);
char	***parse_map(int argc, char **argv);

#endif