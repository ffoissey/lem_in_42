/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 17:50:47 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/23 19:13:54 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static uint8_t		is_completed(t_lemin *lemin)
{
	if (lemin->end_room == NULL)
		return (FALSE);
	if (lemin->end_room->ants == lemin->total_ants)
		return (TRUE);
	return (FALSE);
}

size_t		get_worst_score(t_lemin *lemin)
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

void				mark_dead_rooms(t_lemin *lemin)
{
	t_room *room;
	t_list	*list;

	list = lemin->main_list_room;
	while (list != NULL)
	{
		room = (t_room *)list->content;
		if (room->score > lemin->max_score)
			room->mark = DEAD;
		list = list->next;
	}
}

void				out_node(t_list *room_list, t_lemin *lemin)
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
				if (cur_room->mark == DEAD ||
					cur_room->score > lemin->max_score
					|| cur_room->nb_links == 0
					|| (cur_room->score > room->score && cur_room->d_end < room->d_end))
				{
					room->nb_links--;
					if (room->nb_links == 0)
						room->mark = DEAD;
					ft_lstdelnode(&room->links, cur_room);
					link = room->links;
				}
				else
					link = link->next;
			}
		}
		room_list = room_list->next;
	}
}

int					main(void)
{
	t_lemin lemin;
	char	*result;

	ft_bzero(&lemin, sizeof(lemin));
	if (parser(&lemin) == FAILURE)
	{
		print_error(lemin.error);
		exit_routine(&lemin);
		return (EXIT_FAILURE);
	}
	lemin.nb_max_ways = get_nb_max_ways(&lemin);
	set_distance_from_start(lemin.start_room, &lemin, 0);
	set_distance_from_end(lemin.end_room, &lemin, 0);
	lemin.max_score = get_worst_score(&lemin);
	out_node(lemin.main_list_room, &lemin);
	mark_dead_rooms(&lemin);
//	print_graph(&lemin);	/// GRAPH DEBUG
	graph_course(&lemin);
//	return (EXIT_FAILURE);
	ft_putendl("OK");
	ways_selection(&lemin); // WAYS SELECTION
	print_list_ways(&lemin); /// POSSIBLE WAY LIST DEBUG
	return (EXIT_SUCCESS);
	result = NULL;
	while (is_completed(&lemin) == FALSE)
	{
		//result = process(lemin->start_room, lemin->turn);
		ft_putendl(result);
		ft_strdel(&result);
	}
	exit_routine(&lemin);
	return (EXIT_SUCCESS);
}
