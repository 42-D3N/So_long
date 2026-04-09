/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-pape <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 08:53:22 by tle-pape          #+#    #+#             */
/*   Updated: 2025/02/13 08:42:44 by tle-pape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_ffdata	ff(char **map, int x, int y, t_ffdata *count)
{
	if (map[x][y] != '1' && map[x][y] != '2')
	{
		if (map[x][y] == 'P')
			(*count).p -= 1;
		if (map[x][y] == 'E')
			(*count).e -= 1;
		if (map[x][y] == 'C')
			(*count).c -= 1;
		map[x][y] = '2';
		*count = ff(map, x + 1, y, count);
		*count = ff(map, x - 1, y, count);
		*count = ff(map, x, y + 1, count);
		*count = ff(map, x, y - 1, count);
	}
	return (*count);
}

t_ffdata	counting(char **map, t_ffdata count)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
				count.p += 1;
			else if (map[i][j] == 'E')
				count.e += 1;
			else if (map[i][j] == 'C')
				count.c += 1;
			j++;
		}
		i++;
	}
	return (count);
}

int	flood_fill(char **map, int x, int y)
{
	t_ffdata	count;

	count.p = 0;
	count.e = 0;
	count.c = 0;
	count = counting(map, count);
	ff(map, x, y, &count);
	if (count.p == 0 && count.e == 0 && count.c == 0)
		return (1);
	return (0);
}
