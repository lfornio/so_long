/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:17:47 by lfornio           #+#    #+#             */
/*   Updated: 2021/10/13 15:05:27 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void error_ber(char *map) //функция пррверяет расширение .ber
{
	int i;
	int a;
	char *str;

	a = ft_strlen(map) - 4;
	str = (char *)malloc(sizeof(char *) * 5);
	if (!str)
		return;
	i = 0;
	while (map[a])
	{
		str[i] = map[a];
		a++;
		i++;
	}
	str[i] = '\0';
	if (ft_strncmp(str, ".ber", 4) != 0)
	{
		printf("Error: The map is not .ber\n");
		free(str);
		exit(0);
	}
	free(str);
}

int size_tab(char *map)
{
	int fd;
	int count;
	char *line;

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
			printf("Error : Map is error, empty lines\n");
			exit(0);
		}

		free(line);
		count++;
	}
	free(line);
	close(fd);
	// printf("size = %d\n", count);
	return (count);
}

char **new_tab(char *map, int count)
{
	char **tab;
	char *line;
	int fd;
	int i;

	i = 0;
	fd = open(map, O_RDONLY);
	tab = (char **)malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	while ((get_next_line(fd, &line)) > 0)
	{
		tab[i] = ft_substr(line, 0, ft_strlen(line));
		// printf("%s\n", tab[i]);
		free(line);
		i++;
	}
	free(line);
	tab[i] = NULL;
	close(fd);
	// printf("aaaa\n");
	return (tab);
}

int error_map(char **tab, int count)
{
	int flag;

	flag = 0;
	if (box(tab) == 1) //проверка на прямоугольник
	{
		printf("Error: The field is not rectangular\n");
		flag++;
	}
	if (walls_perimeter(tab, count - 1) == 1) //проверка на периметр
	{
		printf("Error: The perimeter walls are open\n");
		flag++;
	}
	if (ft_strlen(tab[0]) > 34 || count > 19)
	{
		printf("Error: Map is very big\n");
		flag++;
	}
	return (flag);
}

void init_size_window(t_mlx *mlx, char *s, int count)
{
	mlx->height = 75 * count;
	mlx->width = 75 * ft_strlen(s);
}

void print_background(t_mlx *mlx)
{
	int *img_data;
	int bpp;
	int size_line;
	int endian;
	int i;

	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, mlx->width, mlx->height);
	img_data = (int *)mlx_get_data_addr(mlx->img_ptr, &bpp, &size_line, &endian);
	i = 0;
	while (i < mlx->height)
	{
		int j = 0;
		while (j < mlx->width)
		{

			img_data[i * mlx->width + j] = 0x90EE90;

			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
}
