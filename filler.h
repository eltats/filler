/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 16:05:54 by wkraig            #+#    #+#             */
/*   Updated: 2020/06/28 22:06:35 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

typedef struct		s_map{
	int				**heatmap;
	int				height;
	int				width;
}					t_map;

typedef struct		s_token{
	char			**figure;
	int				height;
	int				width;
}					t_token;

typedef struct		s_players_info{
	char			enemy;
	char			player;
	int				x;
	int				y;
}					t_players_info;

typedef struct		s_filler{
	t_map			*map;
	t_token			*token;
	t_players_info	*playa;
}					t_filler;

void	init_players(t_filler *data, char *line);
int		ft_abs(int a);
