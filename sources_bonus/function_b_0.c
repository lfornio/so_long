/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_b_0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:17:47 by lfornio           #+#    #+#             */
/*   Updated: 2021/10/20 07:38:14 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

void	error_ber(char *map)
{
	int		i;
	int		a;
	char	*str;

	i = 0;
	a = ft_strlen(map) - 4;
	str = (char *)malloc(sizeof(char *) * 5);
	if (!str)
		return ;
	while (map[a])
	{
		str[i] = map[a];
		a++;
		i++;
	}
	str[i] = '\0';
	if (ft_strncmp(str, ".ber", 4) != 0)
	{
		write(1, "Error\n", 6);
		printf("The map is not .ber\n");
		free(str);
		exit(0);
	}
	free(str);
}

int	size_tab(char *map)
{
	int		fd;
	int		count;
	char	*line;

	line = NULL;
	count = 0;
	fd = open(map, O_RDONLY);
	if (fd == -1)
	{
		perror("Error");
		exit(0);
	}
	while ((get_next_line(fd, &line)) > 0)
	{
		if (ft_strlen(line) == 0)
		{
			printf("Error: Map is error, empty lines\n");
			exit(0);
		}
		free(line);
		count++;
	}
	free(line);
	close(fd);
	return (count);
}

char	**new_tab(char *map, int count)
{
	char	**tab;
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open(map, O_RDONLY);
	tab = (char **)malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	while ((get_next_line(fd, &line)) > 0)
	{
		tab[i] = ft_substr(line, 0, ft_strlen(line));
		free(line);
		i++;
	}
	free(line);
	tab[i] = NULL;
	close(fd);
	return (tab);
}

void	init_size_window(t_mlx *mlx, char *s, int count)
{
	mlx->height = 75 * count + 25;
	mlx->width = 75 * ft_strlen(s);
}

int	walls_str(char *str)
{
	while (*str)
	{
		if (*str != '1')
			return (1);
		str++;
	}
	return (0);
}
