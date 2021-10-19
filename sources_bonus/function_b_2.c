/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_b_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 13:32:38 by lfornio           #+#    #+#             */
/*   Updated: 2021/10/19 15:27:49 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

void	print_key(char c, t_mlx *mlx, int x, int y)
{
	if (c == '1')
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr,
			mlx->img_ptr_wall, x, y);
	else if (c == 'P')
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr,
			mlx->img_ptr_player, x, y);
	else if (c == 'C')
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr,
			mlx->img_ptr_cake, x, y);
	else if (c == 'E')
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr,
			mlx->img_ptr_exit, x, y);
	else if (c == 'F')
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr,
			mlx->img_ptr_exit_f, x, y);
	else if (c == 'Z')
	{
		// mlx->p.x_enemy =pos_player_x(mlx->tab, 'Z') * 75;
		// mlx->p.y_enemy =pos_player_y(mlx->tab, 'Z') * 75;


		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr_enemy, x, y);
}
}

int	step_in_exit(t_mlx *mlx)
{
	int	i;

	i = 0;
	mlx->tab[mlx->p.y][mlx->p.x] = '0';
	i++;
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr);
	print_background(mlx);
	map_print_img(mlx, mlx->tab);
	return (i);
}

void	last_step(t_mlx *mlx)
{
	mlx->p.steps = mlx->p.steps + step_in_exit(mlx);
	printf("YOU WON\n");
	exit(0);
}

void	change_element(t_mlx *mlx, int j, int i)
{
	mlx->tab[mlx->p.y][mlx->p.x] = '0';
	mlx->tab[j][i] = 'P';
	mlx->p.steps++;
}

void	count_cake(t_mlx *mlx, int j, int i)
{
	if (mlx->tab[j][i] == 'C')
		mlx->p.cake++;
}
