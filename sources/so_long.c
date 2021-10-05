/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 10:31:47 by lfornio           #+#    #+#             */
/*   Updated: 2021/10/05 15:36:16 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"


int box(char **tab) // функция проверяет прямоугольник ли поле
{
	int i;

	i = 0;
	while (tab[i] && tab[i + 1])
	{
		// printf("tab = %s\n", tab[i]);
		if (ft_strlen(tab[i]) != ft_strlen(tab[i + 1]))
			return (1);
		i++;
	}
	return (0);
}

int walls_str(char *str) //функция которая проверяет верхнюю и нижнюю стену
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '1')
			return (1);
		i++;
	}
	return (0);
}

int analysis_str(char *str, char c) //функция которая проверяет верхнюю и нижнюю стену
{
	int i;

	i = 0;
	int count;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int walls_perimeter(char **tab, int count)   //функция проверяет закрыты ли все стены по периметру
{
	int i;

	i = 1;
	if (walls_str(tab[0]) == 1 || walls_str(tab[count]) == 1)
	{
		return (1);
	}
	while (tab[i] && i < count)
	{
		int len;
		len = ft_strlen(tab[i]) - 1;
		if (tab[i][0] != '1' || tab[i][len] != '1')
			return (1);
		i++;
	}
	return (0);
}

// void input_image_from_map(char *str)
// {
// 	int i = 0;

// 	while (str[i])
// 	{
// 		if (str[i] == '1')


// 	}
// }



int main(int argc, char **argv)
{
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
	char *line;
	int res;
	// int i;
	char **tab;
	int count;
	int width;
	int height;
	// int *img_data;
	int i = 0;
// 	int     bpp;
// int     size_line;
// int     endian;

	i = 0;


	if (argc == 2)
	{
		int fd;
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			perror("Error");
		// write(1, "No file\n", 8);
		else
			printf("%d\n", fd);
		while ((res = get_next_line(fd, &line)) > 0)
		{

			// printf("res = %d fd = %d str%d = %s\n", res, fd, i, line);
			free(line);
			i++;
		}
		free(line);
		printf("i = %d\n", i);
		close(fd);
		count = i - 1;
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			perror("Error");
		// write(1, "No file\n", 8);
		else
			printf("%d\n", fd);
		tab = (char **)malloc(sizeof(char *) * (count + 1));
		if (!tab)
			return (0);
		i = 0;
		while ((res = get_next_line(fd, &line)) > 0)
		{

			// printf("res = %d fd = %d str%d = %s\n", res, fd, i, line);
			tab[i] = ft_substr(line, 0, ft_strlen(line));
			// line;
			printf("%s\n", tab[i]);
			free(line);
			i++;
		}
		free(line);
		tab[i] = NULL;
		close(fd);
		printf("i = %d\n", i);
		if (box(tab) == 1)                    //проверка на прямоугольник
		{
			write(1, "Error\n", 6);
			printf("The field is not rectangular\n");
			exit(0);
		}
		if (walls_perimeter(tab, count) == 1)         //проверка на периметр
		{
			write(1, "Error\n", 6);
			printf("The perimeter walls are open\n");
			exit(0);
		}
		i = 1;
		int c = 0;
		int p = 0;
		int e = 0;
		while (tab[i] && i < count)
		{
			if (analysis_str(tab[i], 'C') > 0)
				c++;
			if (analysis_str(tab[i], 'P') > 0)
				p++;
			if (analysis_str(tab[i], 'E') > 0)
				e++;
			i++;
		}
		if (c == 0)           //проверки на игрока, монеты, выход
		{
			write(1, "Error\n", 6);
			printf("No collectibles\n");

		}
		if (p == 0)
		{
			write(1, "Error\n", 6);
			printf("No player\n");

		}
		if (e == 0)
		{
			write(1, "Error\n", 6);
			printf("No exit\n");
			exit(0);
		}
	}
	else
		write(1, "Error\n", 6);

		// i = 0;
		// while(tab[i])
		// {
		// 	input_image_from_map(tab[i]);
		// }

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "so_long");
	img_ptr = mlx_xpm_file_to_image(mlx_ptr, "free_zone.xpm", &width, &height);
	i = 0;
	while (i < 500)
	{
		mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, i, 0);
		i += 50;
	}

	mlx_loop(mlx_ptr);

}
