/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_b_6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 10:07:20 by lfornio           #+#    #+#             */
/*   Updated: 2021/10/20 10:36:16 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

void	for_animation(t_mlx *mlx, void *p, int x, int y)
{
	int		i;
	int		j;
	int		*img_data;
	t_fon	f;

	i = 0;
	j = 0;
	img_data = (int *)mlx_get_data_addr(p, &f.bpp, &f.size_line, &f.endian);
	while (i < 75)
	{
		j = 0;
		while (j < 75)
		{
			img_data[i * 75 + j] = 0x90EE90;
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, p, x, y);
}

void	for_animation_3(t_mlx *mlx, int count, int x, int y)
{
	if (count <= 6)
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr,
			mlx->img_ptr_enemy_1, x, y);
	else
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr,
			mlx->img_ptr_enemy, x, y);
}

void	for_animation_2(t_mlx *mlx, void *p, int count)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	y = 0;
	while (mlx->tab[i])
	{
		j = 0;
		x = 0;
		while (mlx->tab[i][j])
		{
			if (mlx->tab[i][j] == 'Z')
			{
				for_animation(mlx, p, x, y);
				for_animation_3(mlx, count, x, y);
			}
			x += 75;
			j++;
		}
		y += 75;
		i++;
	}
}

int	animation(t_mlx *mlx)
{
	static int	count = 0;
	void		*p;

	p = mlx_new_image(mlx->mlx_ptr, 75, 75);
	for_animation_2(mlx, p, count);
	count++;
	if (count == 12)
		count = 0;
	mlx_destroy_image(mlx->mlx_ptr, p);
	return (0);
}
