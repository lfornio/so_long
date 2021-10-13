/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 10:31:47 by lfornio           #+#    #+#             */
/*   Updated: 2021/10/13 13:26:57 by lfornio          ###   ########.fr       */
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

int analysis_str(char *str, char c) //функция считает количество элементов и проверяет наличие других символов
{
	int i;

	i = 0;
	int count;
	count = 0;
	while (str[i])
	{
		if (str[i] != '1' && str[i] != '0' && str[i] != 'C' && str[i] != 'P' && str[i] != 'E')
		{
			printf("Error: Map is error, other characters\n");
			exit(0);
		}
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

void init_images(void *mlx_ptr, t_images *img) // инициализация картинок
{
	int width;
	int height;

	img->img_ptr_wall = mlx_xpm_file_to_image(mlx_ptr, "images/wall.xpm", &width, &height);
	// img->img_ptr_zone = mlx_xpm_file_to_image(mlx_ptr, "images/free_zone.xpm", &width, &height);
	img->img_ptr_player = mlx_xpm_file_to_image(mlx_ptr, "images/player.xpm", &width, &height);
	img->img_ptr_cake = mlx_xpm_file_to_image(mlx_ptr, "images/cake.xpm", &width, &height);
	img->img_ptr_exit = mlx_xpm_file_to_image(mlx_ptr, "images/exit.xpm", &width, &height);
}

void map_print_img(void *mlx_ptr, void *win_ptr, t_images *img, char **tab) //печать карты в окне
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
				mlx_put_image_to_window(mlx_ptr, win_ptr, img->img_ptr_wall, x, y);
			// else
			// 	mlx_put_image_to_window(mlx_ptr, win_ptr, img->img_ptr_zone, x, y);
			x += 75;
			j++;
		}
		y += 75;
		i++;
	}
	i = 0;
	y = 0;
	while (tab[i])
	{
		j = 0;
		x = 0;
		while (tab[i][j])
		{
			if (tab[i][j] == 'P')
				mlx_put_image_to_window(mlx_ptr, win_ptr, img->img_ptr_player, x, y);
			if (tab[i][j] == 'C')
				mlx_put_image_to_window(mlx_ptr, win_ptr, img->img_ptr_cake, x, y);
			if (tab[i][j] == 'E')
				mlx_put_image_to_window(mlx_ptr, win_ptr, img->img_ptr_exit, x, y);

			x += 75;
			j++;
		}
		y += 75;
		i++;
	}
}

int error_elements(char **tab, int count)
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
	i = 0;
	if (player > 1)
	{
		printf("Error: Lots of cats\n");
		i++;
	}
	if (ex > 1)
	{
		printf("Error: Lots of exit\n");
		i++;
	}
	if (cake == 0) //проверки на игрока, монеты, выход
	{
		printf("Error: No collectibles\n");
		i++;
	}
	if (player == 0)
	{
		printf("Error: No player\n");
		i++;
	}
	if (ex == 0)
	{
		printf("Error: No exit\n");
		i++;
	}
	return (i);
}

int main(int argc, char **argv)
{
	t_mlx *mlx;
	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	t_size *win;
	win = (t_size *)malloc(sizeof(t_size));
	t_images *img;
	img = (t_images *)malloc(sizeof(t_images));
	char **tab;
	int count;

	if (argc == 2)
	{
		error_ber(argv[1]);
		count = size_tab(argv[1]);
		tab = new_tab(argv[1], count);
		if (error_map(tab, count) != 0 || error_elements(tab, count) != 0)
			exit(0);
		init_size_window(win, tab[0], count);
		mlx->mlx_ptr = mlx_init();
		mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, win->width, win->height, "so_long");
		print_background(img, mlx, win);
		init_images(mlx->mlx_ptr, img);
		map_print_img(mlx->mlx_ptr, mlx->win_ptr, img, tab);

		mlx_loop(mlx->mlx_ptr);
	}
	else
		printf("Error: Argument error\n");
}
