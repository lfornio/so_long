/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 10:31:47 by lfornio           #+#    #+#             */
/*   Updated: 2021/10/20 10:04:49 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

void	map(t_mlx *mlx, char *str)
{
	error_ber(str);
	mlx->count = size_tab(str);
	mlx->tab = new_tab(str, mlx->count);
	if (error_map(mlx->tab, mlx->count) != 0
		|| error_elements(mlx->tab, mlx->count, mlx) != 0
		|| map_element_error(mlx->tab) != 0)
		exit(0);
	init_size_window(mlx, mlx->tab[0], mlx->count);
}

void	init_images(void *mlx_ptr, t_mlx *mlx)
{
	int	width;
	int	height;

	mlx->img_ptr_wall = mlx_xpm_file_to_image(mlx_ptr, "images/wall.xpm",
			&width, &height);
	mlx->img_ptr_player = mlx_xpm_file_to_image(mlx_ptr, "images/player.xpm",
			&width, &height);
	mlx->img_ptr_cake = mlx_xpm_file_to_image(mlx_ptr, "images/cake.xpm",
			&width, &height);
	mlx->img_ptr_exit = mlx_xpm_file_to_image(mlx_ptr, "images/exit.xpm",
			&width, &height);
	mlx->img_ptr_exit_f = mlx_xpm_file_to_image(mlx_ptr,
			"images/exit_final.xpm", &width, &height);
	mlx->img_ptr_enemy = mlx_xpm_file_to_image(mlx_ptr,
			"images/enemy.xpm", &width, &height);
	mlx->img_ptr_enemy_1 = mlx_xpm_file_to_image(mlx_ptr,
			"images/enemy_1.xpm", &width, &height);
}

void	map_print_img(t_mlx *mlx, char **tab)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	y = 0;
	while (tab[i])
	{
		j = 0;
		x = 0;
		while (tab[i][j])
		{
			print_key(tab[i][j], mlx, x, y);
			x += 75;
			j++;
		}
		y += 75;
		i++;
	}
}

void	game(t_mlx *mlx)
{
	mlx_loop_hook(mlx->mlx_ptr, animation, mlx);
	mlx_hook(mlx->win_ptr, 2, 1L << 0, steps, mlx);
	mlx_hook(mlx->win_ptr, 17, 1L << 0, step_exit, mlx);
	mlx_loop(mlx->mlx_ptr);
}

int	main(int argc, char **argv)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	if (!mlx)
		return (-1);
	mlx = init_struct(mlx);
	if (argc == 2)
	{
		map(mlx, argv[1]);
		mlx->mlx_ptr = mlx_init();
		mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, mlx->width,
				mlx->height, "so_long_bonus");
		print_background(mlx);
		init_images(mlx->mlx_ptr, mlx);
		map_print_img(mlx, mlx->tab);
		game(mlx);
	}
	else
		error("Argument error");
	free(mlx);
}
