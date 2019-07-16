/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_to_start.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 14:39:46 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/16 15:06:16 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int8_t	set_distance_to_start(t_room *room, t_lemin *lemin, size_t distance)
{
	t_list *links;
	t_room *cur_room;

	if (room == lemin->end_room)
	{
		room->d_to_start = distance;
		return (SUCCESS);
	}
	else if (room == NULL || (distance != 0 && room == lemin->start_room))
		return (FAILURE);
	links = room->links;
	room->d_to_start = distance;
	room->mark = DEAD;
	while (links != NULL)
	{
		cur_room = (t_room *)links->content;
		if (cur_room->d_to_start == 0 || cur_room->d_to_start > distance)
		{
			if (set_distance_to_start(cur_room, lemin, distance + 1) == SUCCESS)
				room->mark = UNMARK;
		}
		links = links->next;
	}
	return (SUCCESS);
}
