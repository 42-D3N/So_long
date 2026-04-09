/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-pape <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:19:34 by tle-pape          #+#    #+#             */
/*   Updated: 2025/02/10 14:47:46 by tle-pape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <mlx.h>
# include "../sources/libft/includes/libft.h"

# define NM "So Long"
# define ESC 65307								// Ascii Code of ESC key
# define NEW_WIN mlx_new_window					// Reduce Function name len
# define XPMIMG mlx_xpm_file_to_image			// Reduce function name len
# define DIS mlx_put_image_to_window			// Reduce function name len

typedef struct img_data
{
	int		w;
	int		h;
	char	*path;
	void	*img;
}			t_img_data;

typedef struct s_data
{
	char		**map;
	char		**parse_map;
	char		*error;
	void		*win;
	void		*mlx;
	int			moves;
	int			fd;
	int			won;
	int			map_l;
	int			plr_x;
	int			plr_y;
	int			plr_old_x;
	int			plr_old_y;
	int			last_dir;
	t_img_data	bgr;
	t_img_data	plr_d;
	t_img_data	plr_a;
	t_img_data	wll;
	t_img_data	ext;
	t_img_data	col;
}			t_data;

typedef struct parse_data
{
	int	player;
	int	exit;
	int	collectible;
	int	valid;
}			t_pdata;

typedef struct ff_data
{
	int	p;
	int	e;
	int	c;
}			t_ffdata;

int		render(t_data *dat);
int		input(int key, t_data *dat);
int		parsing(char **map);
int		flood_fill(char **map, int x, int y);
int		kill_prog(t_data dat, int err, char *error);
int		get_map_len(char **map);
char	**get_map(int fd);
void	free_arr(char **s, int max);
t_data	dat_setup(t_data dat, char *char_fd);

#endif
