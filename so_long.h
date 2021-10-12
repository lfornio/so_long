/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:46:08 by lfornio           #+#    #+#             */
/*   Updated: 2021/10/12 15:58:14 by lfornio          ###   ########.fr       */
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
	void *img_ptr_wall;
	void *img_ptr;
	void *img_ptr_cat;
	void *img_ptr_mouse;
	void *img_ptr_exit;
} t_images;

void error_ber(char *map);
int size_tab(char *file);
char **new_tab(char *file, int count);







#endif
