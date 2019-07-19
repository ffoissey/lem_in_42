/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_to_start.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 14:39:46 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/18 18:52:57 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int8_t	set_distance_from_start(t_room *room, t_lemin *lemin, size_t distance)
{
	t_list *links;
	t_room *cur_room;

	if (distance != 0 && room == lemin->start_room)
		return (SUCCESS);
	room->d_start = distance;
	if (room == lemin->end_room)
		return (SUCCESS);
	links = room->links;
	while (links != NULL)
	{
		cur_room = (t_room *)links->content;
		if (cur_room->d_start == 0 || cur_room->d_start > distance)
		{
			if (set_distance_from_start(cur_room, lemin, distance + 1) == FAILURE
					&& room->nb_links > 0)
				room->nb_links--;
		}
		links = links->next;
	}
	if (room->nb_links == 1 && room != lemin->start_room)
	{
		room->mark = DEAD;
		return (FAILURE);
	}
	return (SUCCESS);
}

int8_t	set_distance_from_end(t_room *room, t_lemin *lemin, size_t distance)
{
	t_list *links;
	t_room *cur_room;

	if (distance != 0 && room == lemin->end_room)
		return (SUCCESS);
	room->d_end = distance;
	if (room == lemin->start_room)
		return (SUCCESS);
	links = room->links;
	while (links != NULL)
	{
		cur_room = (t_room *)links->content;
		if (cur_room->d_end == 0 || cur_room->d_end > distance)
		{
			if (set_distance_from_end(cur_room, lemin, distance + 1) == FAILURE
					&& room->nb_links > 0)
				room->nb_links--;
		}
		links = links->next;
	}
	if (room->nb_links == 1 && room != lemin->end_room)
	{
		room->mark = DEAD;
		return (FAILURE);
	}
	return (SUCCESS);
}
