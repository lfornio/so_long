/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 13:41:31 by lfornio           #+#    #+#             */
/*   Updated: 2021/10/15 14:05:48 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	steps(int key, t_mlx *mlx)
{
	if (key == 53)
		esc_exit(mlx);
	if (element_count(mlx, 'P') == 1)
	{
		mlx->p.x = pos_player_x(mlx->tab, 'P');
		mlx->p.y = pos_player_y(mlx->tab, 'P');
		if (key == 2)
			step_count(mlx, mlx->p.y, mlx->p.x + 1);
		else if (key == 0)
			step_count(mlx, mlx->p.y, mlx->p.x - 1);
		else if (key == 1)
			step_count(mlx, mlx->p.y + 1, mlx->p.x);
		else if (key == 13)
			step_count(mlx, mlx->p.y - 1, mlx->p.x);
		if (mlx->p.cake == mlx->cake && element_count(mlx, 'E') == 1)
		{
			mlx->p.x_ex = pos_player_x(mlx->tab, 'E');
			mlx->p.y_ex = pos_player_y(mlx->tab, 'E');
			mlx->tab[mlx->p.y_ex][mlx->p.x_ex] = 'F';
		}
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr);
		print_background(mlx);
		map_print_img(mlx, mlx->tab);
	}
	return (0);
}

int	error_map(char **tab, int count)
{
	int	flag;

	flag = 0;
	if (box(tab) == 1)
	{
		write(1, "Error\n", 6);
		flag = count_error("The field is not rectangular", flag);
	}
	if (walls_perimeter(tab, count - 1) == 1)
	{
		write(1, "Error\n", 6);
		flag = count_error("The perimeter walls are open", flag);
	}
	if (ft_strlen(tab[0]) > 34 || count > 19)
	{
		write(1, "Error\n", 6);
		flag = count_error("Map is very big", flag);
	}
	if (ft_strlen(tab[0]) < 4 || count < 4)
	{
		write(1, "Error\n", 6);
		flag = count_error("Map is very small", flag);
	}
	return (flag);
}

void	print_background(t_mlx *mlx)
{
	t_fon	f;
	int		*img_data;
	int		i;
	int		j;

	i = 0;
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, mlx->width, mlx->height);
	img_data = (int *)mlx_get_data_addr(mlx->img_ptr, &f.bpp,
			&f.size_line, &f.endian);
	while (i < mlx->height)
	{
		j = 0;
		while (j < mlx->width)
		{
			img_data[i * mlx->width + j] = 0x90EE90;
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
}
