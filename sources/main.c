/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-pape <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:06:09 by tle-pape          #+#    #+#             */
/*   Updated: 2025/02/13 13:43:37 by tle-pape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_arr(char **s, int max)
{
	int	i;

	i = 0;
	while (i < max)
	{
		free(s[i]);
		i++;
	}
	free(s);
}

void	kill_image(t_data dat)
{
	if (dat.bgr.img != NULL)
		mlx_destroy_image(dat.mlx, dat.bgr.img);
	if (dat.plr_d.img != NULL)
		mlx_destroy_image(dat.mlx, dat.plr_d.img);
	if (dat.plr_a.img != NULL)
		mlx_destroy_image(dat.mlx, dat.plr_a.img);
	if (dat.ext.img != NULL)
		mlx_destroy_image(dat.mlx, dat.ext.img);
	if (dat.wll.img != NULL)
		mlx_destroy_image(dat.mlx, dat.wll.img);
	if (dat.col.img != NULL)
		mlx_destroy_image(dat.mlx, dat.col.img);
}

int	kill_prog(t_data dat, int err, char *error)
{
	if (err != 3)
		write(2, error, ft_strlen(error));
	if (err >= 1)
	{
		if (dat.fd > 1)
		{
			close(dat.fd);
			free_arr(dat.map, dat.map_l);
		}
		kill_image(dat);
		if (err > 1)
			mlx_destroy_window(dat.mlx, dat.win);
	}
	if (dat.mlx)
	{
		mlx_destroy_display(dat.mlx);
		free(dat.mlx);
	}
	exit(1);
}

int	hook_kill_prog(t_data *dat)
{
	kill_prog(*dat, 3, dat->error);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		dat;
	char		*tmp;

	dat.error = NULL;
	dat.fd = -99;
	dat.map_l = 0;
	dat.won = 0;
	dat.mlx = mlx_init();
	if (dat.mlx == NULL)
		kill_prog(dat, 0, "Error\nFailed to mlx_init().\n");
	else if (argc != 2)
		kill_prog(dat, 0, "Error\nToo few/many arguments.\n");
	tmp = ft_substr(argv[argc - 1], ft_strlen(argv[argc - 1]) - 4, 4);
	if (ft_strncmp(tmp, ".ber", 4) != 0)
		dat.error = "Error\nWrong map format.\n";
	free(tmp);
	dat = dat_setup(dat, argv[argc - 1]);
	if (dat.fd < 1 || dat.error != NULL)
		kill_prog(dat, 1, dat.error);
	dat.win = NEW_WIN(dat.mlx, ft_strlen(*dat.map) * 48, dat.map_l * 48, NM);
	render(&dat);
	mlx_key_hook(dat.win, &input, &dat);
	mlx_hook(dat.win, 17, 1L << 17, &hook_kill_prog, &dat);
	mlx_loop(dat.mlx);
}
