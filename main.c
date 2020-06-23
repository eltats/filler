/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkraig <wkraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:04:42 by wkraig            #+#    #+#             */
/*   Updated: 2020/06/23 21:24:57 by wkraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <stdio.h>
#define FILE fd

int		check_place(t_filler *data, int x, int y)
{
	if (x - data->token->height < 0 || x + data->token->height >= data->map->height)
		return (0);
	if (y - data->token->width < 0 || y + data->token->width >= data->map->width)
		return (0);
	return (1);
}

int		coords_sum(t_filler *data, int x, int y)
{
	int		i;
	int		j;
	int		sum;

	i = 0;
	sum = 0;
	while (data->token->figure[i])
	{
		j = 0;
		while (data->token->figure[i][j])
		{
			if (data->token->figure[i][j] == '*')
				sum += data->map->heatmap[x + i][j + y];
			j++;
		}
		i++;
	}
	return (sum);
}

void	place(t_filler *data)
{
	int		x;
	int		y;
	int		i;
	int		j;
	int		sum;
	int		min_sum;

	min_sum = 2147483647;
	x = 0;
	while (data->map->heatmap[x])
	{
		y = 0;
		while (y < data->map->width)
		{
			i = 0;
			while (data->token->figure[i])
			{
				j = 0;
				while (data->token->figure[i][j])
				{
					if (!check_place(data, x, y))
						break ;
					if (data->map->heatmap[x + i][y + j] == -1)
					{
						sum = coords_sum(data, x, y);
						if (sum < min_sum)
						{
							min_sum = sum;
							data->playa->x = x;
							data->playa->y = y;
						}
					}
					j++;
				}
				i++;
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
	// for (int i = 0; data->map->heatmap[i]; i++)
	// {
	// 	ft_printf("%2d   ", i);
	// 	for(int j = 0; j < data->map->width; j++)
	// 		ft_printf("%3d", data->map->heatmap[i][j]);
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
	i = 0;
	get_next_line(FILE, &line);
	while (i < data->map->height)
	{
		data->map->heatmap[i] = (int *)ft_memalloc(sizeof(int) * (data->map->width + 1));
		get_next_line(FILE, &line);
		j = 0;
		while (line[j])
		{
			if (line[j] == ft_tolower(data->playa->enemy) || line[j] == data->playa->enemy)
				data->map->heatmap[i][j - 4] = -2;
			else if (line[j] == ft_tolower(data->playa->player) || line[j] == data->playa->player)
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
		i++;
	}
}

int		main(void)
{
	char		*line;
	int			i;
	// int			FILE = open("test.txt", O_RDWR);
	int			FILE = 0;
	t_filler	*data;

	data = (t_filler *)ft_memalloc(sizeof(t_filler));
	data->map = (t_map *)ft_memalloc(sizeof(t_map));
	data->token = (t_token *)ft_memalloc(sizeof(t_token));
	data->playa = (t_players_info *)ft_memalloc(sizeof(t_players_info));
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
			// ft_printf("%d %d\n", data->playa->x, data->playa->y);
			ft_putnbr(5);
			ft_putchar(' ');
			ft_putnbr(5);
			ft_putchar('\n');
			
		}
	}
	close(fd);
	return (0);
}
