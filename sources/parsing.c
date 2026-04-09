/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-pape <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 08:33:22 by tle-pape          #+#    #+#             */
/*   Updated: 2025/02/10 14:01:43 by tle-pape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	check_map_format(char **map, int last)
{
	int		i;
	size_t	ref;

	i = 0;
	ref = ft_strlen(map[i]);
	while (i < last + 1)
	{
		if (ft_strlen(map[i]) != ref)
			return (0);
		i++;
	}
	return (1);
}

int	check_border(char **map, int last)
{
	int	i;
	int	len;

	i = 0;
	if (check_map_format(map, last) == 0)
		return (0);
	while (map[0][i])
	{
		if (map[0][i] != '1' || map[last][i] != '1')
			return (0);
		i++;
	}
	len = i - 1;
	i = 0;
	while (i != last)
	{
		if (map[i][0] != '1' || map[i][len] != '1')
			return (0);
		i++;
	}
	return (1);
}

t_pdata	check_set(char c, t_pdata data)
{
	if (c == 'P' && data.player == 0)
		data.player += 1;
	else if (c == 'E')
		data.exit += 1;
	else if (c == 'C')
		data.collectible += 1;
	else if (c == '1')
		data.valid = 0;
	else if (c == '0')
		data.valid = 0;
	else
		data.valid = -1;
	return (data);
}

int	check_tiles(char **map, int last)
{
	int		i;
	t_pdata	data;

	data.player = 0;
	data.exit = 0;
	data.collectible = 0;
	data.valid = 0;
	while (last >= 0)
	{
		i = 0;
		while (map[last][i])
		{
			data = check_set(map[last][i], data);
			if (data.valid == -1)
				return (0);
			i++;
		}
		last--;
	}
	if (data.player != 1 || data.exit != 1 || data.collectible < 1)
		return (0);
	return (1);
}

int	parsing(char **map)
{
	int		i;
	int		x;
	int		y;

	i = 0;
	x = 1;
	y = 1;
	if (map == NULL)
		return (0);
	while (map[i])
		i++;
	if (check_border(map, i - 1) == 0 || \
		check_tiles(map, i - 1) == 0 || \
		flood_fill(map, x, y) == 0)
		return (0);
	return (1);
}
