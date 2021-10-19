/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_b_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 13:35:24 by lfornio           #+#    #+#             */
/*   Updated: 2021/10/19 08:20:03 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

int	box(char **tab)
{
	int	i;

	i = 0;
	while (*tab && *(tab + 1))
	{
		if (ft_strlen(*tab) != ft_strlen(*(tab + 1)))
			return (1);
		tab++;
	}
	return (0);
}

int	map_element_error(char **tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] != '1' && tab[i][j] != '0' && tab[i][j] != 'C'
				&& tab[i][j] != 'P' && tab[i][j] != 'E' && tab[i][j] != 'Z')
			{
				write(1, "Error\n", 6);
				printf("Map is error, unknown key\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	analysis_str(char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count);
}

int	walls_perimeter(char **tab, int count)
{
	int	i;
	int	len;

	i = 1;
	if (walls_str(tab[0]) == 1 || walls_str(tab[count]) == 1)
	{
		return (1);
	}
	while (tab[i] && i < count)
	{
		len = ft_strlen(tab[i]) - 1;
		if (tab[i][0] != '1' || tab[i][len] != '1')
			return (1);
		i++;
	}
	return (0);
}

int	error_elements(char **tab, int count, t_mlx *mlx)
{
	int	i;
	int	player;
	int	ex;
	int	cake;

	i = 0;
	player = 0;
	ex = 0;
	cake = 0;
	while (tab[i] && i < count)
	{
		player = player + analysis_str(tab[i], 'P');
		ex = ex + analysis_str(tab[i], 'E');
		cake = cake + analysis_str(tab[i], 'C');
		i++;
	}
	mlx->cake = cake;
	i = 0;
	if (player != 1 || ex != 1 || cake == 0)
		i = error_key_in_map(player, ex, cake);
	return (i);
}
