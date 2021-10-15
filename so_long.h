/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:46:08 by lfornio           #+#    #+#             */
/*   Updated: 2021/10/15 14:10:42 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <unistd.h>
# include "get_next_line/get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include "libft/libft.h"

typedef struct s_pos
{
	int	x;
	int	y;
	int	x_ex;
	int	y_ex;
	int	cake;
	int	steps;
}	t_pos;

typedef struct s_mlx
{
	int		width;
	int		height;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	void	*img_ptr_wall;
	void	*img_ptr_player;
	void	*img_ptr_cake;
	void	*img_ptr_exit;
	void	*img_ptr_exit_f;
	int		count;
	int		cake;
	char	**tab;
	t_pos	p;
}	t_mlx;

typedef struct s_fon
{
	int	bpp;
	int	size_line;
	int	endian;
}	t_fon;

void	error_ber(char *map);
int		size_tab(char *map);
char	**new_tab(char *file, int count);
int		error_map(char **tab, int count);
int		box(char **tab);
int		walls_str(char *str);
int		walls_perimeter(char **tab, int count);
void	init_size_window(t_mlx *mlx, char *s, int count);
void	print_background(t_mlx *mlx);
int		step_in_exit(t_mlx *mlx);
void	map_print_img(t_mlx *mlx, char **tab);
void	last_step(t_mlx *mlx);
void	change_element(t_mlx *mlx, int j, int i);
void	count_cake(t_mlx *mlx, int j, int i);
int		step_count(t_mlx *mlx, int j, int i);
int		element_count(t_mlx *mlx, char c);
void	esc_exit(t_mlx *mlx);
int		count_error(char *s, int i);
int		step_exit(int key, t_mlx *mlx);
int		steps(int key, t_mlx *mlx);
void	game(t_mlx *mlx);
void	map(t_mlx *mlx, char *str);
int		error_elements(char **tab, int count, t_mlx *mlx);
int		map_element_error(char **tab);
void	error(char *s);
int		error_key_in_map(int player, int ex, int cake);
void	print_key(char c, t_mlx *mlx, int x, int y);
int		analysis_str(char *str, char c);
int		pos_player_x(char **tab, char c);
int		pos_player_y(char **tab, char c);

#endif
