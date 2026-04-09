/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-pape <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:20:55 by tle-pape          #+#    #+#             */
/*   Updated: 2025/02/13 10:13:07 by tle-pape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_data	img_setup(t_data dat)
{
	dat.bgr.path = "./sprite/background.xpm";
	dat.plr_d.path = "./sprite/player_d.xpm";
	dat.plr_a.path = "./sprite/player_a.xpm";
	dat.wll.path = "./sprite/wall.xpm";
	dat.col.path = "./sprite/collectible.xpm";
	dat.ext.path = "./sprite/exit.xpm";
	dat.bgr.img = XPMIMG(dat.mlx, dat.bgr.path, &dat.bgr.w, &dat.bgr.h);
	dat.plr_d.img = XPMIMG(dat.mlx, dat.plr_d.path, &dat.plr_d.w, &dat.plr_d.h);
	dat.plr_a.img = XPMIMG(dat.mlx, dat.plr_a.path, &dat.plr_a.w, &dat.plr_a.h);
	dat.wll.img = XPMIMG(dat.mlx, dat.wll.path, &dat.wll.w, &dat.wll.h);
	dat.ext.img = XPMIMG(dat.mlx, dat.ext.path, &dat.ext.w, &dat.ext.h);
	dat.col.img = XPMIMG(dat.mlx, dat.col.path, &dat.col.w, &dat.col.h);
	return (dat);
}

t_data	player_init(t_data dat)
{
	int	i;
	int	j;

	i = 0;
	dat.last_dir = 'd';
	dat.moves = 0;
	while (dat.map[i])
	{
		j = 0;
		while (dat.map[i][j])
		{
			if (dat.map[i][j] == 'P')
			{
				dat.plr_x = j * 48;
				dat.plr_y = i * 48;
			}
			j++;
		}
		i++;
	}
	dat.plr_old_x = -1;
	dat.plr_old_y = -1;
	return (dat);
}

t_data	dat_setup(t_data dat, char *char_fd)
{
	dat = img_setup(dat);
	dat.fd = open(char_fd, O_RDONLY);
	if (dat.fd == -1)
	{
		dat.error = "Error\nFailed to open file.\n";
		return (dat);
	}
	dat.map = get_map(dat.fd);
	if (!dat.map)
	{
		dat.error = "Error\nFailed to get map, map is too big or empty file.\n";
		return (dat);
	}
	dat.map_l = get_map_len(dat.map);
	dat = player_init(dat);
	close(dat.fd);
	dat.fd = open(char_fd, O_RDONLY);
	dat.parse_map = get_map(dat.fd);
	if (dat.bgr.img == NULL || dat.plr_d.img == NULL || dat.ext.img == NULL || \
		dat.col.img == NULL || dat.wll.img == NULL || dat.plr_a.img == NULL)
		dat.error = "Error\nFailed IMG setup : Check sprites ressources.\n";
	else if (parsing(dat.parse_map) == 0)
		dat.error = "Error\nFailed Parsing.\n";
	free_arr(dat.parse_map, dat.map_l);
	return (dat);
}

int	get_map_len(char **map)
{
	int	len;

	len = 0;
	while (map[len])
		len++;
	return (len);
}

char	**get_map(int fd)
{
	char	**map;
	char	*buff;
	char	*tmp;
	char	*nl;

	buff = ft_strdup("");
	tmp = buff;
	nl = get_next_line(fd);
	if (!nl)
		return (free(buff), NULL);
	while (nl)
	{
		buff = ft_strjoin(buff, nl);
		free(tmp);
		free(nl);
		nl = get_next_line(fd);
		tmp = buff;
	}
	map = ft_split(buff, '\n');
	if (ft_strlen(map[0]) > 40 || get_map_len(map) > 21)
	{
		free_arr(map, get_map_len(map));
		return (free(buff), NULL);
	}
	return (free(buff), map);
}
