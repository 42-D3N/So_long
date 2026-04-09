/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-pape <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:25:41 by tle-pape          #+#    #+#             */
/*   Updated: 2025/02/10 14:09:24 by tle-pape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	check_collectible(char **map)
{
	int	i;
	int	j;
	int	c;

	i = 0;
	c = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				c++;
			j++;
		}
		i++;
	}
	if (c == 0)
		return (0);
	return (1);
}

int	check_collision(t_data dat, int x, int y)
{
	x /= 48;
	y /= 48;
	if (dat.map[y][x] == '1')
		return (0);
	else if (dat.map[y][x] == 'C')
		dat.map[y][x] = '0';
	else if (dat.map[y][x] == 'E')
		return (2);
	return (1);
}

t_data	moves(int key, t_data dat)
{
	if (key == 'w' && check_collision(dat, dat.plr_x, dat.plr_y - 48) != 0)
		dat.plr_y -= 48;
	if (key == 'a' && check_collision(dat, dat.plr_x - 48, dat.plr_y) != 0)
		dat.plr_x -= 48;
	if (key == 's' && check_collision(dat, dat.plr_x, dat.plr_y + 48) != 0)
		dat.plr_y += 48;
	if (key == 'd' && check_collision(dat, dat.plr_x + 48, dat.plr_y) != 0)
		dat.plr_x += 48;
	if (dat.plr_old_x != dat.plr_x || dat.plr_old_y != dat.plr_y)
	{
		dat.moves += 1;
		ft_printf("Steps : %d\n", dat.moves);
	}
	else
		ft_printf("*bonk*\n");
	if (check_collision(dat, dat.plr_x, dat.plr_y) == 2)
	{
		if (check_collectible(dat.map) == 0)
		{
			render(&dat);
			ft_printf("You won in %d steps !\nPress ESC to quit.\n", dat.moves);
			dat.won = 1;
		}
	}
	return (dat);
}

int	input(int key, t_data *dat)
{
	if (key == ESC)
		kill_prog(*dat, 3, NULL);
	else if (dat->won == 1)
		return (0);
	else if (key == 'w' || key == 'a' || key == 's' || key == 'd')
	{
		if (key == 'd')
			dat->last_dir = key;
		else if (key == 'a')
			dat->last_dir = key;
		dat->plr_old_x = dat->plr_x;
		dat->plr_old_y = dat->plr_y;
		*dat = moves(key, *dat);
	}
	if (dat->won == 0)
		render(dat);
	return (0);
}

int	render(t_data *dat)
{
	int	i;
	int	j;

	i = 1;
	DIS(dat->mlx, dat->win, dat->bgr.img, 0, 0);
	while (dat->map[i - 1])
	{
		j = 1;
		while (dat->map[i - 1][j - 1])
		{
			if (dat->map[i - 1][j - 1] == '1')
				DIS(dat->mlx, dat->win, dat->wll.img, j * 48 - 48, i * 48 - 48);
			if (dat->map[i - 1][j - 1] == 'E')
				DIS(dat->mlx, dat->win, dat->ext.img, j * 48 - 48, i * 48 - 48);
			if (dat->map[i - 1][j - 1] == 'C')
				DIS(dat->mlx, dat->win, dat->col.img, j * 48 - 48, i * 48 - 48);
			j++;
		}
		i++;
	}
	if (dat->last_dir == 'd')
		DIS(dat->mlx, dat->win, dat->plr_d.img, dat->plr_x, dat->plr_y);
	else if (dat->last_dir == 'a')
		DIS(dat->mlx, dat->win, dat->plr_a.img, dat->plr_x, dat->plr_y);
	return (0);
}
