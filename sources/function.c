/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:17:47 by lfornio           #+#    #+#             */
/*   Updated: 2021/10/12 16:15:39 by lfornio          ###   ########.fr       */
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

int size_tab(char *file)
{
	int fd;
	int count;
	char *line;

	count = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("Error");
		exit(0);
	}
	while ((get_next_line(fd, &line)) > 0)
	{
		free(line);
		count++;
	}
	free(line);
	close(fd);
	printf("count2 = %d\n", count);
	return (count);
}

// char **new_tab(char *file, int count)
// {
// 	char **tab;
// 	char *line;
// 	int fd;
// 	int i;

// 	i = 0;
// 	fd = open(file, O_RDONLY);
// 	tab = (char **)malloc(sizeof(char *) * (count + 1));
// 	if (!tab)
// 		return (NULL);
// 	while ((get_next_line(fd, &line)) > 0)
// 	{
// 		tab[i] = ft_substr(line, 0, ft_strlen(line));
// 		printf("%s\n", tab[i]);
// 		free(line);
// 		i++;
// 	}
// 	free(line);
// 	tab[i] = NULL;
// 	close(fd);
// 	// printf("aaaa\n");
// 	return (tab);
// }
