/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:46:08 by lfornio           #+#    #+#             */
/*   Updated: 2021/10/13 13:20:47 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include <mlx.h>
#include <unistd.h>
#include "get_next_line/get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include "libft/libft.h"

typedef struct s_size
{
	int width;
	int height;
} t_size;

typedef struct s_mlx
{
	void *mlx_ptr;
	void *win_ptr;
} t_mlx;

typedef struct s_images
{
	void *img_ptr;
	void *img_ptr_wall;
	void *img_ptr_player;
	void *img_ptr_cake;
	void *img_ptr_exit;
} t_images;

void error_ber(char *map);
int size_tab(char *map);
char **new_tab(char *file, int count);
int error_map(char **tab, int count);
int box(char **tab);
int walls_str(char *str);
int walls_perimeter(char **tab, int count);
void init_size_window(t_size *win, char *s, int count);
void print_background(t_images *img, t_mlx *mlx, t_size *win);









#endif
