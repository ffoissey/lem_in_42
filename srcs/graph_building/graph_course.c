/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_course.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 14:39:51 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/16 20:48:39 by ffoissey         ###   ########.fr       */
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

int8_t		save_the_way(t_lemin *lemin)
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

int8_t				go_to_start(t_room *room, t_lemin *lemin)
{
	t_list *links;
	t_room *cur_room;
	t_room	*best_room;
	size_t	d_from_start;

	if (room == NULL)
		return (FAILURE);
	if (room == lemin->start_room)
	{
		if (save_the_way(lemin) == FAILURE)
			return (FAILURE);
		return (SUCCESS);
	}
	links = room->links;
	d_from_start = room->d_start;
	best_room = NULL;
	while (links != NULL)
	{
		cur_room = (t_room *)links->content;
		if (d_from_start > cur_room->d_start)
		{
			d_from_start = cur_room->d_start;
			best_room = cur_room;
		}
		links = links->next;
	}
	if (best_room != NULL)
	{
		room->current_link = best_room;
		best_room->mark = MARK;
		go_to_start(best_room, lemin);
		best_room->mark = UNMARK;
	}
	return (SUCCESS);	
}

void				trace_til_mark(t_room *room, t_lemin *lemin)
{
	t_list *links;
	t_room *cur_room;

	links = room->links;
	while (links != NULL)
	{
		cur_room = (t_room *)links->content;
		if (cur_room->mark == MARK && cur_room != room
			&& room->d_start > cur_room->d_start)
		{
			room->current_link = cur_room;
			trace_til_mark(cur_room, lemin);
			return ;
		}
		links = links->next;
	}
	go_to_start(room, lemin);
}

void				roll_back_to_end(t_room *room, t_lemin *lemin)
{
	t_room	*cur_room;
	t_list *links;
	t_room	*best_room;
	size_t	d_from_end;

	if (room == NULL)
		return ;
	if (room == lemin->end_room)
	{
		trace_til_mark(room, lemin);
		return ;
	}
	links = room->links;
	best_room = NULL;
	d_from_end = room->d_end;
	while (links != NULL)
	{
		cur_room = (t_room *)links->content;
		if (d_from_end > cur_room->d_end)
		{
			d_from_end = cur_room->d_end;
			best_room = cur_room;
		}
		links = links->next;
	}
	if (best_room != NULL)
	{
		best_room->mark = MARK;
		roll_back_to_end(best_room, lemin);
		best_room->mark = UNMARK;
	}
}

int8_t				graph_course(t_lemin *lemin)
{
	t_list	*run;
	t_room *cur_room;

	run = lemin->main_list_room;
	while (run != NULL)
	{
		cur_room = (t_room *)run->content;
		if (cur_room != lemin->start_room && cur_room != lemin->end_room
				&& cur_room->mark != DEAD)
				//&& cur_room->d_start < lemin->total_ants)
			roll_back_to_end(cur_room, lemin);
		run = run->next;
	}
	return (SUCCESS);	
}
