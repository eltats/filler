/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 20:39:40 by wkraig            #+#    #+#             */
/*   Updated: 2020/06/28 22:06:21 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		ft_abs(int a)
{
	return (a < 0 ? -a : a);
}

void	init_players(t_filler *data, char *line)
{
	int		i;

	line = ft_strchr(line, '[');
	if (ft_strstr(line, "a.out") > 0)
	{
		data->playa->player = 'O';
		data->playa->enemy = 'X';
	}
	else
	{
		data->playa->player = 'X';
		data->playa->enemy = 'O';
	}
}
