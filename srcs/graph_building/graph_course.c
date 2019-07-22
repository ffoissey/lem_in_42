/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_course.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 14:39:51 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/18 18:52:57 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
static uint8_t	is_better_distance(size_t *d_start, size_t *d_end, t_room *room, uint8_t opt)
{
	if (room->mark == DEAD)
		return (FALSE);
	if (opt == D_START)
	{
		if (*d_start > room->d_start)
		{
			*d_start = room->d_start;
			*d_end = room->d_end;
			return (TRUE);
		}
	}
	else
	{
		if (*d_end > room->d_end)
		{
			*d_start = room->d_start;
			*d_end = room->d_end;
			return (TRUE);
		}
	}
	return (FALSE);
}

static t_room	*get_best_room(t_room *room, t_lemin *lemin, uint8_t opt)
{
	t_list *links;
	t_room	*best_room;
	t_room	*cur_room;
	size_t	d_start;
	size_t	d_end;

	d_start = room->d_start;
	d_end = room->d_end;
	best_room = NULL;
	links = room->links;
	while (links != NULL)
	{
		cur_room = (t_room *)links->content;
		if (cur_room->score <= lemin->max_score
			&& is_better_distance(&d_start, &d_end, cur_room, opt) == TRUE)
			best_room = cur_room;
		links = links->next;
	}
	(void)lemin;
	return (best_room);
}

static int8_t	go_to_start(t_room *room, t_lemin *lemin)
{
	t_room	*best_room;

	if (room == lemin->start_room)
	{
		if (save_the_way(lemin) == FAILURE)
			return (FAILURE);
		return (SUCCESS);
	}
	if ((best_room = get_best_room(room, lemin, D_START)) != NULL)
	{
		room->current_link = best_room;
		return (go_to_start(best_room, lemin));
	}
	return (FAILURE);
}

static int8_t	roll_back_to_end(t_room *room, t_lemin *lemin)
{
	t_room	*best_room;

	if (room == lemin->end_room)
		return (SUCCESS);
	if ((best_room = get_best_room(room, lemin, D_END)) != NULL)
	{
		best_room->current_link = room;
		return (roll_back_to_end(best_room, lemin));
	}
	return (FAILURE);
}

int8_t			graph_course(t_lemin *lemin)
{
	t_list	*run;
	t_room *cur_room;

	run = lemin->main_list_room;
	while (run != NULL)
	{
		cur_room = (t_room *)run->content;
		if (cur_room->mark != DEAD && cur_room != lemin->start_room)
		{
			if (roll_back_to_end(cur_room, lemin) == SUCCESS)
				go_to_start(cur_room, lemin);
		}
		run = run->next;
	}
	return (SUCCESS);	
}
*/

int				graph_course(t_room *room, t_lemin *lemin)
{
	t_list *links;
	t_room	*cur_room;

	if (room == lemin->start_room)
	{
		if (save_the_way(lemin) == FAILURE)
			return (FAILURE);
		return (SUCCESS);
	}
	links = room->links;
	if (room->mark != DEAD)
		room->mark = MARK;
	while (links != NULL)
	{
		cur_room = (t_room*)links->content;
		if (cur_room->mark == UNMARK)
		{
			room->current_link = cur_room;
			graph_course(cur_room, lemin);
		}
		links = links->next;
	}
	if (room->mark != DEAD)
		room->mark = UNMARK;
	return (SUCCESS);	
}
