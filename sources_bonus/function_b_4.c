/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_b_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 13:38:24 by lfornio           #+#    #+#             */
/*   Updated: 2021/10/19 08:14:28 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

int	pos_player(char *s, char c)
{
	int	x;

	x = 0;
	while (s[x])
	{
		if (s[x] == c)
			break ;
		x++;
	}
	return (x);
}

int	pos_player_x(char **tab, char c)
{
	int	i;
	int	x;

	i = 0;
	while (tab[i])
	{
		x = pos_player(tab[i], c);
		if (x != (int)ft_strlen(tab[i]) && x != 0)
			break ;
		i++;
	}
	return (x);
}

int	pos_player_y(char **tab, char c)
{
	int	i;
	int	x;

	i = 0;
	while (tab[i])
	{
		x = pos_player(tab[i], c);
		if (x != (int)ft_strlen(tab[i]) && x != 0)
			break ;
		i++;
	}
	return (i);
}

int	element_count(t_mlx *mlx, char c)
{
	int	i;
	int	player;

	i = 0;
	player = 0;
	while (mlx->tab[i] && i < mlx->count)
	{
		player = player + analysis_str(mlx->tab[i], c);
		i++;
	}
	return (player);
}

int	step_exit(int key, t_mlx *mlx)
{
	(void)key;
	(void)mlx;
	exit(0);
}
