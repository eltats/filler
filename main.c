/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkraig <wkraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:04:42 by wkraig            #+#    #+#             */
/*   Updated: 2020/03/13 19:21:02 by wkraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <stdio.h>
#define FILE fd

int		manhattan_distance(t_filler *data, int x, int y)
{
	int		i;
	int		j;
	int		min_dist;
	int		dist;

	min_dist = 2147483647;
	dist = 0;
	i = 0;
	while (data->map->heatmap[i])
	{
		j = 0;
		while (j < data->map->width)
		{
			if (data->map->heatmap[i][j] == -2)
			{
				dist = ft_abs(x - i) + ft_abs(y - j);
				if (dist < min_dist)
					min_dist = dist;
			}
			j++;
		}
		i++;
	}
	return (min_dist);
}

void	create_heatmap(t_filler *data)
{
	int		x;
	int		y;
	
	x = 0;
	while (data->map->heatmap[x])
	{
		y = 0;
		while (y < data->map->width)
		{
			if (data->map->heatmap[x][y] == 0)
				data->map->heatmap[x][y] = manhattan_distance(data, x, y);
			y++;
		}
		x++;
	}
}

void	get_map(char *line, int FILE, t_filler *data)
{
	int		i;
	int		j;

	data->map->height = ft_atoi(ft_strchr(line, ' '));
	data->map->width = ft_atoi(ft_strchr(ft_strchr(line, ' ') + 1, ' '));
	data->map->heatmap = (int **)ft_memalloc(sizeof(int *) * (data->map->height + 1));
	i = 0;
	get_next_line(FILE, &line);
	while (i < data->map->height)
	{
		data->map->heatmap[i] = (int *)ft_memalloc(sizeof(int) * (data->map->width + 1));
		get_next_line(FILE, &line);
		j = 0;
		while (line[j])
		{
			if (line[j] == 'o' || line[j] == 'O')
				data->map->heatmap[i][j - 4] = -2;
			if (line[j] == 'x' || line[j] == 'X')
				data->map->heatmap[i][j - 4] = -1;
			j++;
		}
		i++;
	}
}

void	get_token(char *line, int FILE, t_filler *data)
{
	int		i;
	int		j;

	data->height = ft_atoi(ft_strchr(line, ' '));
	data->width = ft_atoi(ft_strchr(ft_strchr(line, ' ') + 1, ' '));
	data->figure = (char **)ft_memalloc(sizeof(char *) * (data->height + 1));
	i = 0;
	while (i < data->height)
	{
		data->figure[i] = (char *)ft_memalloc(sizeof(char) * (data->width + 1));
		get_next_line(FILE, &line);
		j = 0;
		while (line[j])
		{
			data->figure[i][j] = line[j];
			j++;
		}
		i++;
	}
}

int		main(void)
{
	char		*line;
	int			i;
	int			FILE = open("test.txt", O_RDWR);
	t_filler	*data;

	data = (t_filler *)ft_memalloc(sizeof(t_filler));
	data->map = (t_map *)ft_memalloc(sizeof(t_map));
	while (get_next_line(FILE, &line) > 0)
	{
		if (line && !ft_strncmp(line, "Plateau", 7))
		{
			get_map(line, FILE, data);
			create_heatmap(data);
			for(int i = 0; data->map->heatmap[i]; i++)
			{
				for (int j = 0; j < data->map->width; j++)
				{
					ft_printf("%3d", data->map->heatmap[i][j]);
				}
				ft_printf("\n");
			}
		}
		if (line && !ft_strncmp(line, "Piece", 5))
			get_token(line, FILE, data);
	}
	close (FILE);
	return (0);
}
