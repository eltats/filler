/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkraig <wkraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 16:05:54 by wkraig            #+#    #+#             */
/*   Updated: 2020/03/13 18:19:01 by wkraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"

typedef struct	s_map{
	int			**heatmap;
	int			height;
	int			width;
}				t_map;

typedef struct	s_filler{
	char		**figure;
	t_map		*map;
	int			height;
	int			width;
}				t_filler;