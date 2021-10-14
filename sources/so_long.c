/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 10:31:47 by lfornio           #+#    #+#             */
/*   Updated: 2021/10/14 16:23:04 by lfornio          ###   ########.fr       */
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

int map_element_error(char **tab)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] != '1' && tab[i][j] != '0' && tab[i][j] != 'C' && tab[i][j] != 'P' && tab[i][j] != 'E')
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

int analysis_str(char *str, char c) //функция считает количество элементов и проверяет наличие других символов
{
	int i;

	i = 0;
	int count;
	count = 0;
	while (str[i])
	{
		// if (str[i] != '1' && str[i] != '0' && str[i] != 'C' && str[i] != 'P' && str[i] != 'E' && str[i] != 'F')
		// {
		// 	printf("Error: Map is error, other characters\n");
		// 	exit(0);
		// }
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int walls_perimeter(char **tab, int count) //функция проверяет закрыты ли все стены по периметру
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

void init_images(void *mlx_ptr, t_mlx *mlx) // инициализация картинок
{
	int width;
	int height;

	mlx->img_ptr_wall = mlx_xpm_file_to_image(mlx_ptr, "images/wall.xpm", &width, &height);
	mlx->img_ptr_player = mlx_xpm_file_to_image(mlx_ptr, "images/player.xpm", &width, &height);
	mlx->img_ptr_cake = mlx_xpm_file_to_image(mlx_ptr, "images/cake.xpm", &width, &height);
	mlx->img_ptr_exit = mlx_xpm_file_to_image(mlx_ptr, "images/exit.xpm", &width, &height);
	mlx->img_ptr_exit_f = mlx_xpm_file_to_image(mlx_ptr, "images/exit_final.xpm", &width, &height);
}

void map_print_img(void *mlx_ptr, void *win_ptr, t_mlx *mlx, char **tab) //печать карты в окне
{
	int i = 0;
	int j = 0;
	int x = 0;
	int y = 0;
	while (tab[i])
	{
		j = 0;
		x = 0;
		while (tab[i][j])
		{
			if (tab[i][j] == '1')
				mlx_put_image_to_window(mlx_ptr, win_ptr, mlx->img_ptr_wall, x, y);
			else if (tab[i][j] == 'P')
				mlx_put_image_to_window(mlx_ptr, win_ptr, mlx->img_ptr_player, x, y);
			else if (tab[i][j] == 'C')
				mlx_put_image_to_window(mlx_ptr, win_ptr, mlx->img_ptr_cake, x, y);
			else if (tab[i][j] == 'E')
				mlx_put_image_to_window(mlx_ptr, win_ptr, mlx->img_ptr_exit, x, y);
			else if (tab[i][j] == 'F')
				mlx_put_image_to_window(mlx_ptr, win_ptr, mlx->img_ptr_exit_f, x, y);
			x += 75;
			j++;
		}
		y += 75;
		i++;
	}
}

int error_elements(char **tab, int count, t_mlx *mlx)
{
	int i = 0;
	int player = 0;
	int ex = 0;
	int cake = 0;
	while (tab[i] && i < count)
	{
		player = player + analysis_str(tab[i], 'P');
		ex = ex + analysis_str(tab[i], 'E');
		cake = cake + analysis_str(tab[i], 'C');

		i++;
	}
	mlx->cake = cake;
	// printf("cake c = %d\n", mlx->cake);
	i = 0;
	if (player > 1)
	{
		write(1, "Error\n", 6);
		printf("Lots of player\n");
		i++;
	}
	if (ex > 1)
	{
		write(1, "Error\n", 6);
		printf("Lots of exit\n");
		i++;
	}
	if (cake == 0) //проверки на игрока, монеты, выход
	{
		write(1, "Error\n", 6);
		printf("No collectibles\n");
		i++;
	}
	if (player == 0)
	{
		write(1, "Error\n", 6);
		printf("No player\n");
		i++;
	}
	if (ex == 0)
	{
		write(1, "Error\n", 6);
		printf("No exit\n");
		i++;
	}
	return (i);
}

int pos_player(char *s, char c)
{
	int x;
	x = 0;
	while (s[x])
	{
		if (s[x] == c)
			break;
		x++;
	}
	return (x);
}

int pos_player_x(char **tab, char c)
{
	int i;
	int x;
	i = 0;

	while (tab[i])
	{
		x = pos_player(tab[i], c);
		if (x != (int)ft_strlen(tab[i]) && x != 0)
			break;
		i++;
	}
	return (x);
}

int pos_player_y(char **tab, char c)
{
	int i;
	int x;
	i = 0;
	while (tab[i])
	{
		x = pos_player(tab[i], c);
		if (x != (int)ft_strlen(tab[i]) && x != 0)
			break;
		i++;
	}
	return (i);
}

int element_count(t_mlx *mlx, char c)
{
	int i;
	int player;

	i = 0;
	player = 0;
	while (mlx->tab[i] && i < mlx->count) //смотрим есть ли игрок
	{
		player = player + analysis_str(mlx->tab[i], c);
		i++;
	}
	return (player);
}

int steps(int key, t_mlx *mlx)
{
	// printf("key = %d\n", key);
	int x;
	int y;
	int i = 0;
	int j = 0;
	static int steps = 0;
	static int cake = 0;
	if (key == 53)
	{
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		exit(0);
	}
	if (element_count(mlx, 'P') == 1)
	{
		x = pos_player_x(mlx->tab, 'P');
		y = pos_player_y(mlx->tab, 'P');

		if (key == 2)
		{
			if (element_count(mlx, 'E') == 1)
			{
				if (mlx->tab[y][x + 1] == '1' || (mlx->tab[y][x + 1] == 'E' && cake != mlx->cake))
					return (0);
				if (mlx->tab[y][x + 1] == 'C')
					cake++;
			}
			else
			{
				if (mlx->tab[y][x + 1] == '1')
					return (0);
				if (cake == mlx->cake && mlx->tab[y][x + 1] == 'F')
				{

					steps = steps + step_in_exit(y, x, mlx);
					printf("Steps: %d\n", steps);
					exit(0);
				}
			}
			mlx->tab[y][x] = '0';
			mlx->tab[y][x + 1] = 'P';
			steps++;
			printf("Steps: %d\n", steps);
		}
		if (key == 0)
		{
			if (element_count(mlx, 'E') == 1)
			{
				if (mlx->tab[y][x - 1] == '1' || (mlx->tab[y][x - 1] == 'E' && cake != mlx->cake))
					return (0);
				if (mlx->tab[y][x - 1] == 'C')
					cake++;
			}
			else
			{
				if (mlx->tab[y][x - 1] == '1')
					return (0);
				if (cake == mlx->cake && mlx->tab[y][x - 1] == 'F')
				{
					steps = steps + step_in_exit(y, x, mlx);
					printf("Steps: %d\n", steps);
					exit (0);
				}
			}
			mlx->tab[y][x] = '0';
			mlx->tab[y][x - 1] = 'P';
			steps++;
			printf("Steps: %d\n", steps);
		}
		if (key == 1)
		{
			if (element_count(mlx, 'E') == 1)
			{
				if (mlx->tab[y + 1][x] == '1' || (mlx->tab[y + 1][x] == 'E' && cake != mlx->cake))
					return (0);
				if (mlx->tab[y + 1][x] == 'C')
					cake++;
			}
			else
			{
				if (mlx->tab[y + 1][x] == '1')
					return (0);
				if (cake == mlx->cake && mlx->tab[y + 1][x] == 'F')
				{
					steps = steps + step_in_exit(y, x, mlx);
					printf("Steps: %d\n", steps);
					exit (0);
				}
			}

			mlx->tab[y][x] = '0';
			mlx->tab[y + 1][x] = 'P';
			steps++;
			printf("Steps: %d\n", steps);
		}
		if (key == 13)
		{
			if (element_count(mlx, 'E') == 1)
			{
				if (mlx->tab[y - 1][x] == '1' || (mlx->tab[y - 1][x] == 'E' && cake != mlx->cake))
					return (0);
				if (mlx->tab[y - 1][x] == 'C')
					cake++;
			}
			else
			{
				if (mlx->tab[y - 1][x] == '1')
					return (0);
				if (cake == mlx->cake && mlx->tab[y - 1][x] == 'F')
				{
					steps = steps + step_in_exit(y, x, mlx);
					printf("Steps: %d\n", steps);
					i = 0;
					// return (0);
					exit(0);
				}
			}
			mlx->tab[y][x] = '0';
			mlx->tab[y - 1][x] = 'P';
			steps++;
			printf("Steps: %d\n", steps);
		}
		if (cake == mlx->cake && element_count(mlx, 'E') == 1)
		{
			i = pos_player_x(mlx->tab, 'E');
			j = pos_player_y(mlx->tab, 'E');
			mlx->tab[j][i] = 'F';
		}
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr);
		print_background(mlx);
		map_print_img(mlx->mlx_ptr, mlx->win_ptr, mlx, mlx->tab);
	}
	else
		exit(0);
	return (0);
}

int step_exit(int key, t_mlx *mlx)
{
	(void)key;
	(void)mlx;
	exit(0);
}

int main(int argc, char **argv)
{
	t_mlx *mlx;
	mlx = (t_mlx *)malloc(sizeof(t_mlx));

	if (argc == 2)
	{
		error_ber(argv[1]);
		mlx->count = size_tab(argv[1]);
		mlx->tab = new_tab(argv[1], mlx->count);
		if (error_map(mlx->tab, mlx->count) != 0 || error_elements(mlx->tab, mlx->count, mlx) != 0 || map_element_error(mlx->tab) != 0)
			exit(0);
		init_size_window(mlx, mlx->tab[0], mlx->count);
		mlx->mlx_ptr = mlx_init();
		mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, mlx->width, mlx->height, "so_long");
		print_background(mlx);
		init_images(mlx->mlx_ptr, mlx);
		map_print_img(mlx->mlx_ptr, mlx->win_ptr, mlx, mlx->tab);
		mlx_hook(mlx->win_ptr, 2, 1L << 0, steps, mlx);
		mlx_hook(mlx->win_ptr, 17, 1L << 0, step_exit, mlx);
		mlx_loop(mlx->mlx_ptr);
	}
	else
	{
		write(1, "Error\n", 6);
		printf("Argument error\n");
	}
	free(mlx);
}
