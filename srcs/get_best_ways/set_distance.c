/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_distance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 14:39:46 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/27 13:09:55 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		out_node(t_list *room_list, t_lemin *lemin)
{
	t_room	*room;
	t_room	*cur_room;
	t_list	*link;

	while (room_list != NULL)
	{
		room = (t_room *)room_list->content;
		if (room != lemin->start_room)
		{
			link = room->links;
			while (link != NULL)
			{
				cur_room = (t_room *)link->content;
				if (cur_room->score > lemin->max_score)
				{
					ft_lstdelnode(&room->links, cur_room, NULL);
					link = room->links;
				}
				else
					link = link->next;
			}
		}
		room_list = room_list->next;
	}
}

static size_t	get_worst_score(t_lemin *lemin)
{
	t_list	*link;
	t_room	*room;
	size_t	score;

	score = 0;
	if (lemin->end_room->nb_links > lemin->start_room->nb_links)
		link = lemin->start_room->links;
	else
		link = lemin->end_room->links;
	while (link != NULL)
	{
		room = (t_room *)link->content;
		if (room->mark != DEAD && (score == 0 || score < room->score))
			score = room->score;
		link = link->next;
	}
	return (score);
}

static void		set_distance_from_start(t_room *room,
					t_lemin *lemin, size_t distance)
{
	t_list *links;
	t_room *cur_room;

	if (distance != 0 && room == lemin->start_room)
		return ;
	room->d_start = distance;
	if (room == lemin->end_room)
		return ;
	links = room->links;
	while (links != NULL)
	{
		cur_room = (t_room *)links->content;
		if (cur_room->mark != DEAD
			&& (cur_room->d_start == 0 || cur_room->d_start > distance))
			set_distance_from_start(cur_room, lemin, distance + 1);
		links = links->next;
	}
	if (room->nb_links < 2 && room != lemin->start_room)
		room->mark = DEAD;
}

static void		set_distance_from_end(t_room *room,
					t_lemin *lemin, size_t distance)
{
	t_list *links;
	t_room *cur_room;

	if (distance != 0 && room == lemin->end_room)
		return ;
	room->d_end = distance;
	room->score = room->d_end + room->d_start;
	if (room == lemin->start_room)
		return ;
	links = room->links;
	while (links != NULL)
	{
		cur_room = (t_room *)links->content;
		if (cur_room->mark != DEAD
			&& (cur_room->d_end == 0 || cur_room->d_end > distance))
			set_distance_from_end(cur_room, lemin, distance + 1);
		links = links->next;
	}
	if (room->nb_links < 2 && room != lemin->end_room)
		room->mark = DEAD;
}

void			set_distance(t_lemin *lemin)
{
	set_distance_from_start(lemin->start_room, lemin, 0);
	set_distance_from_end(lemin->end_room, lemin, 0);
	lemin->nb_max_ways = get_nb_max_ways(lemin);
	lemin->max_score = get_worst_score(lemin);
	out_node(lemin->main_list_room, lemin);
}
