/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_to_start.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 14:39:46 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/16 17:14:05 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int8_t	set_distance_from_start(t_room *room, t_lemin *lemin, size_t distance)
{
	t_list *links;
	t_room *cur_room;

	if (room == lemin->end_room)
	{
		room->d_start = distance;
		return (SUCCESS);
	}
	else if (room == NULL || (distance != 0 && room == lemin->start_room)
			|| distance > lemin->total_ants)
		return (FAILURE);
	links = room->links;
	room->d_start = distance;
	room->mark = DEAD;
	while (links != NULL)
	{
		cur_room = (t_room *)links->content;
		if (cur_room->d_start == 0 || cur_room->d_start > distance)
		{
			if (set_distance_from_start(cur_room, lemin, distance + 1) == SUCCESS)
				room->mark = UNMARK;
		}
		links = links->next;
	}
	return (SUCCESS);
}

int8_t	set_distance_from_end(t_room *room, t_lemin *lemin, size_t distance)
{
	t_list *links;
	t_room *cur_room;

	if (room == lemin->start_room)
	{
		room->d_end = distance;
		return (SUCCESS);
	}
	else if (room == NULL || (distance != 0 && room == lemin->end_room)
			|| distance > lemin->total_ants)
		return (FAILURE);
	links = room->links;
	room->d_end = distance;
	room->mark = DEAD;
	while (links != NULL)
	{
		cur_room = (t_room *)links->content;
		if (cur_room->d_end == 0 || cur_room->d_end > distance)
		{
			if (set_distance_from_end(cur_room, lemin, distance + 1) == SUCCESS)
				room->mark = UNMARK;
		}
		links = links->next;
	}
	return (SUCCESS);
}
