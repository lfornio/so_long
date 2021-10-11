/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 10:31:47 by lfornio           #+#    #+#             */
/*   Updated: 2021/10/11 16:13:59 by lfornio          ###   ########.fr       */
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

// void input_image_from_map(char *str)
// {
// 	int i = 0;

// 	while (str[i])
// 	{
// 		if (str[i] == '1')

// 	}
// }

void init_images(void *mlx_ptr, t_images *img)
{
	int width;
	int height;

	img->img_ptr_wall = mlx_xpm_file_to_image(mlx_ptr, "images/wall.xpm", &width, &height);
	img->img_ptr_zone = mlx_xpm_file_to_image(mlx_ptr, "images/free_zone.xpm", &width, &height);
	img->img_ptr_cat = mlx_xpm_file_to_image(mlx_ptr, "images/cat.xpm", &width, &height);
	img->img_ptr_mouse = mlx_xpm_file_to_image(mlx_ptr, "images/mouse.xpm", &width, &height);
	img->img_ptr_exit = mlx_xpm_file_to_image(mlx_ptr, "images/exit.xpm", &width, &height);
}

void map_print_img(void *mlx_ptr, void *win_ptr, t_images *img, char **tab)
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
			else
				mlx_put_image_to_window(mlx_ptr, win_ptr, img->img_ptr_zone, x, y);
			x += 50;
			j++;
		}
		y += 50;
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
				mlx_put_image_to_window(mlx_ptr, win_ptr, img->img_ptr_cat, x, y);
			if (tab[i][j] == 'C')
				mlx_put_image_to_window(mlx_ptr, win_ptr, img->img_ptr_mouse, x, y);
			if (tab[i][j] == 'E')
				mlx_put_image_to_window(mlx_ptr, win_ptr, img->img_ptr_exit, x, y);

			x += 50;
			j++;
		}
		y += 50;
		i++;
	}
}

int error_str(char **tab, int count)
{
	int i = 0;
	int cat = 0;
	int ex = 0;
	int mouse = 0;
	while (tab[i] && i < count)
	{
		cat = cat + analysis_str(tab[i], 'P');
		ex = ex + analysis_str(tab[i], 'E');
		mouse = mouse + analysis_str(tab[i], 'C');
		i++;
	}
	i = 0;
	if (cat > 1)
		{
			printf("Error: Lots of cats\n");
			i++;
		}
	if (ex > 1)
		{
			printf("Error: Lots of exit\n");
			i++;
		}
	if (mouse == 0) //проверки на игрока, монеты, выход
		{
			printf("Error: No collectibles\n");
			i++;
		}
	if (cat == 0)
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

	void *mlx_ptr;
	void *win_ptr;
	char *line;
	int res;
	char **tab = NULL;
	int count;
	t_size *win;
	win = (t_size *)malloc(sizeof(t_size));
	int i = 0;

	if (argc == 2)
	{
		int fd;
		int a;
		a = ft_strlen(argv[1]) - 1 - 3;
		char *s;
		s = argv[1];
		char *str;
		str = (char *)malloc(sizeof(char *) * 5);
		if (!str)
			return (0);
		i = 0;
		while (s[a])
		{
			str[i] = s[a];
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
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			perror("Error");
			exit(0);
		}
		i = 0;
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

		if (box(tab) == 1) //проверка на прямоугольник
		{
			write(1, "Error\n", 6);
			printf("The field is not rectangular\n");
			exit(0);
		}
		if (walls_perimeter(tab, count) == 1) //проверка на периметр
		{
			write(1, "Error\n", 6);
			printf("The perimeter walls are open\n");
			exit(0);
		}
		win->height = 50 * i;
		win->width = 50 * ft_strlen(tab[0]);
		printf("hei = %d\n", win->height);
		printf("wid = %d\n", win->width);
		if (error_str(tab, count) != 0)
			exit(0);
	}
	else
		write(1, "Error\n", 6);

	mlx_ptr = mlx_init();

	win_ptr = mlx_new_window(mlx_ptr, win->width, win->height, "so_long");
	t_images *img;
	img = (t_images *)malloc(sizeof(t_images));
	init_images(mlx_ptr, img);
	map_print_img(mlx_ptr, win_ptr, img, tab);

	mlx_loop(mlx_ptr);
}
