/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkraig <wkraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 20:39:40 by wkraig            #+#    #+#             */
/*   Updated: 2020/03/13 20:39:59 by wkraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	init_players(t_filler *data, char *line)
{
	int		i;

	line = ft_strchr(line, ']');
	while (*line != '/')
		line--;
	if (!ft_strncmp(line, "wkraig", 6))
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
