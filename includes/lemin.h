/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 17:19:59 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/10 17:50:37 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "libft.h"

enum	e_state
{
	GET_NB_ANTS,
	GET_ROOM_DESCRIPTION,
	GET_LINKS,
	PRE_PROCESS,
	PROCESS,
	PRINT,
	ERROR
};

typedef struct	s_coord
{
	size_t		x;
	size_t		y;
}				t_coord;

typedef struct	s_room
{
	t_list		*ways;
	t_coord		coord;
	size_t		nb_ways;
	size_t		distance_to_end;
	size_t		ants;
	size_t		waiting;
	uint8_t		is_free;
}				t_room;

typedef struct	s_lemin
{
	t_list		*start_room;
	t_list		*end_room;
	size_t		total_ants;
	size_t		turn;
}				t_lemin;			

#endif
