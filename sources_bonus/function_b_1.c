/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_b_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:02:01 by lfornio           #+#    #+#             */
/*   Updated: 2021/10/19 09:41:14 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

int	step_count(t_mlx *mlx, int j, int i)
{
	if (mlx->tab[j][i] == 'Z')
			{
				printf("YOU LOST\n");
				exit(0);
			}
	if (mlx->tab[j][i] == '1')
				return(0);
	if (element_count(mlx, 'E') == 1)
	{
		if (mlx->tab[j][i] == 'E'
			&& mlx->p.cake != mlx->cake)
			return (0);
		count_cake(mlx, j, i);
	}
	else
	{
		if (mlx->p.cake == mlx->cake && mlx->tab[j][i] == 'F')
			last_step(mlx);
	}
	change_element(mlx, j, i);
	return (0);
}

void	esc_exit(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	exit(0);
}

int	count_error(char *s, int i)
{
	int	k;

	k = i;
	printf("%s\n", s);
	k++;
	return (k);
}

void	error(char *s)
{
	write(1, "Error\n", 6);
	printf("%s\n", s);
}

int	error_key_in_map(int player, int ex, int cake)
{
	int	i;

	i = 0;
	write(1, "Error\n", 6);
	if (player > 1)
		i = count_error("Lots of player", i);
	if (ex > 1)
		i = count_error("Lots of exit", i);
	if (cake == 0)
		i = count_error("No collectibles", i);
	if (player == 0)
		i = count_error("No player", i);
	if (ex == 0)
		i = count_error("No exit", i);
	return (i);
}
