/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:46:08 by lfornio           #+#    #+#             */
/*   Updated: 2021/10/13 15:11:29 by lfornio          ###   ########.fr       */
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

typedef struct s_mlx
{
	int width;
	int height;
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
	void *img_ptr_wall;
	void *img_ptr_player;
	void *img_ptr_cake;
	void *img_ptr_exit;
	int count;
	char **tab;
} t_mlx;

void error_ber(char *map);
int size_tab(char *map);
char **new_tab(char *file, int count);
int error_map(char **tab, int count);
int box(char **tab);
int walls_str(char *str);
int walls_perimeter(char **tab, int count);
void init_size_window(t_mlx *mlx, char *s, int count);
void print_background(t_mlx *mlx);









#endif
