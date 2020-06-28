/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkraig <wkraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:04:42 by wkraig            #+#    #+#             */
/*   Updated: 2020/06/28 20:34:50 by wkraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <stdio.h>
#define FILE fd

int		check_pos(t_filler *data, int x, int y)
{
	int i, coord_x, coord_y;

	coord_x = 0;
	i = 0;
	if (x + data->token->height >= data->map->height || y + data->token->width >= data->map->width)
		return (0);
	coord_x = 0;
	while (coord_x < data->token->height)
	{
		coord_y = 0;
		while (coord_y < data->token->width)
		{
			if (data->map->heatmap[x + coord_x][y + coord_y] == -1 && data->token->figure[coord_x][coord_y] == '*')
				i++;
			if (data->map->heatmap[x + coord_x][y + coord_y] == -2 || i > 1)
				return (0);
			coord_y++;
		}
		coord_x++;
	}
	if (i == 1)
		return (1);
	return (0);
}

int		coords_sum(t_filler *data, int x, int y)
{
	int		i;
	int		j;
	int		coord_x, coord_y;
	int		sum;
	int		tmp_y;

	sum = 0;
	tmp_y = y;
	coord_x = 0;
	while (coord_x < data->token->height)
	{
		coord_y = 0;
		y = tmp_y;
		while (coord_y < data->token->width)
		{
			if (data->token->figure[coord_x][coord_y] == '*')
				sum += data->map->heatmap[x][y];
			coord_y++;
			y++;
		}
		coord_x++;
		x++;
	}
	return (sum);
}

void	place(t_filler *data)
{
	int		x = 0;
	int		y = 0;
	int		i = 0;
	int		j = 0;
	int		sum = 100000;
	int		min_sum = 0;

	while (x < data->map->height)
	{
		y = 0;
		while (y < data->map->width)
		{
			if (check_pos(data, x, y))
				sum = coords_sum(data, x , y);
			if (sum < min_sum)
			{
				data->playa->x = x;
				data->playa->y = y;
				min_sum = sum;
			}
			y++;
		}
		x++;
	}
}

int		manhattan_distance(t_filler *data, int x, int y)
{
	int		i;
	int		j;
	int		min_dist;
	int		dist;

	min_dist = 2147483647;
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
	// for (int i = 0; i < data->map->height; i++){
	// 	for (int j = 0; j < data->map->width; j++){
	// 		ft_printf("%3d", data->map->heatmap[i][j]);
	// 	}
	// 	ft_printf("\n");
	// }
}

void	get_map(char *line, int FILE, t_filler *data)
{
	int		i;
	int		j;

	data->map->height = ft_atoi(ft_strchr(line, ' '));
	data->map->width = ft_atoi(ft_strchr(ft_strchr(line, ' ') + 1, ' '));
	data->map->heatmap = (int **)ft_memalloc(sizeof(int *) * (data->map->height + 1));
	get_next_line(FILE, &line);
	ft_strdel(&line);
	i = 0;
	while (i < data->map->height && (get_next_line(FILE, &line)) > 0)
	{
		data->map->heatmap[i] = (int *)ft_memalloc(sizeof(int) * (data->map->width + 1));
		j = 0;
		while (line[j])
		{
			if (line[j] == ft_tolower(data->playa->enemy) || line[j] == data->playa->enemy)
				data->map->heatmap[i][j - 4] = -2;
			else if (line[j] == ft_tolower(data->playa->player) || line[j] == data->playa->player)
				data->map->heatmap[i][j - 4] = -1;
			j++;
		}
		if (line)
			ft_strdel(&line);
		i++;
	}
}

void	get_token(char *line, int FILE, t_filler *data)
{
	int		i;
	int		j;

	data->token->height = ft_atoi(ft_strchr(line, ' '));
	data->token->width = ft_atoi(ft_strchr(ft_strchr(line, ' ') + 1, ' '));
	data->token->figure = (char **)ft_memalloc(sizeof(char *) * (data->token->height + 1));
	i = 0;
	while (i < data->token->height)
	{
		data->token->figure[i] = (char *)ft_memalloc(sizeof(char) * (data->token->width + 1));
		get_next_line(FILE, &line);
		j = 0;
		while (line[j])
		{
			data->token->figure[i][j] = line[j];
			j++;
		}
		ft_strdel(&line);
		i++;
	}
	// for (int i = 0; i < data->token->height; i++){
	// 	for (int j = 0; j < data->token->width; j++){
	// 		ft_printf("%3c", data->token->figure[i][j]);
	// 	}
	// 	ft_printf("\n");
	// }
}

int		main(void)
{
	char		*line;
	int			i;
	int			FILE = open("test.txt", O_RDWR);
	// int			FILE = 0;
	t_filler	*data;

	data = (t_filler *)ft_memalloc(sizeof(t_filler));
	data->map = (t_map *)ft_memalloc(sizeof(t_map));
	data->token = (t_token *)ft_memalloc(sizeof(t_token));
	data->playa = (t_players_info *)ft_memalloc(sizeof(t_players_info));
	data->playa->x = 2;
	data->playa->y = 3;
	data->playa->enemy = '\0';
	data->playa->player = '\0';
	data->token->height = 0;
	data->token->width = 0;
	data->token->figure = NULL;
	data->map->width = 0;
	data->map->height = 0;
	data->map->heatmap = NULL;
	line = NULL;
	while (get_next_line(FILE, &line) > 0)
	{
		if (line && !ft_strncmp(line, "$$$ exec p1", 11))
			init_players(data, line);
		if (line && !ft_strncmp(line, "Plateau", 7))
		{
			get_map(line, FILE, data);
			create_heatmap(data);
		}
		if (line && !ft_strncmp(line, "Piece", 5))
		{
			get_token(line, FILE, data);
			place(data);
			ft_putnbr(data->playa->x);
			ft_putchar(' ');
			ft_putnbr(data->playa->y);
			ft_putchar('\n');
			for (int i = 0; i < data->map->height; i++){
				free(data->map->heatmap[i]);
				data->map->heatmap[i] = NULL;
			}
			free(data->map->heatmap);
			data->map->heatmap = NULL;
			for (int i = 0; i < data->token->height; i++){
				free(data->token->figure[i]);
				data->token->figure[i] = NULL;
			}
			free(data->token->figure);
			data->token->figure = NULL;
		}
		if (line)
			ft_strdel(&line);
	}
	free(data->map);
	free(data->token);
	free(data->playa);
	free(data);
	return (0);
}
