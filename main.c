/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 08:07:19 by lfornio           #+#    #+#             */
/*   Updated: 2021/10/05 14:26:06 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>

int main(void)
{
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
	int width;
	int height;
	// int *img_data;
	int i = 0;
	int     bpp;
int     size_line;
int     endian;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "so_long");
	// mlx_pixel_put(mlx_ptr, win_ptr, 250, 250, 0xFF0000);
	// mlx_string_put(mlx_ptr, win_ptr, 250, 270, 0xFF00FF, "hello");
	// img_ptr = mlx_new_image(mlx_ptr, 200, 200);
	// img_data = (int *)mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
	// while(i < 200)
	// {
	// 	int j = 0;
	// 	while (j < 200)
	// 	{
	// 		if(j % 2)
	// 			img_data[i * 200 + j] = 0xFFFFFF;
	// 		else
	// 			img_data[i * 200 + j] = 0xFF0000;
	// 		j++;
	// 	}
	// 	i++;
	// }
	// mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 100, 100);
	img_ptr = mlx_xpm_file_to_image(mlx_ptr, "free_zone.xpm", &width, &height);
	while (i < 500)
	{
		mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, i, 0);
		i += 50;
	}


	mlx_loop(mlx_ptr);
	return (0);


}
