/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_course.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 14:39:51 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/16 15:29:19 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	void	add_way(t_lemin *lemin, t_way *way)
{
	t_list	*new;

	new = ft_lstnew_nomalloc(way, sizeof(t_way));
	ft_lstadd_back(&(lemin->way_list), new);
	lemin->nb_ways++;
	//DEBUG
	print_way(way);
}

static	int8_t		save_the_way(t_lemin *lemin)
{
	t_room	*room;
	t_list	*new;
	t_way	*way;

	way = ft_memalloc(sizeof(t_way));
	if (way == NULL)
		return (FAILURE);
	room = lemin->end_room;
	while (room != lemin->start_room)
	{
		way->size++;
		new = ft_lstnew_nomalloc(room, sizeof(t_room));
		ft_lstadd(&(way->list), new);
		room = room->current_link;
	}
	way->size++;
	new = ft_lstnew_nomalloc(room, sizeof(t_room));
	ft_lstadd(&(way->list), new);
	add_way(lemin, way);
	return (SUCCESS);
}

int8_t				graph_course(t_room *room, t_lemin *lemin)
{
	t_list *links;
	t_room *cur_room;

	if (room == lemin->start_room)
	{
		if (save_the_way(lemin) == FAILURE)
			return (FAILURE);
		return (SUCCESS);
	}
	if (room->d_to_start > lemin->total_ants)
		return (FAILURE);
	room->mark = MARK;
	links = room->links;
	while (links != NULL)
	{
		cur_room = (t_room *)links->content;
		if (cur_room->mark == UNMARK)
		{
			room->current_link = cur_room;
			graph_course(cur_room, lemin);
		}
		links = links->next;
	}
	room->mark = UNMARK;
	room->current_link = NULL;
	return (SUCCESS);	
}
