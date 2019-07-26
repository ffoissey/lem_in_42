/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_divison.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpillot <tpillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 10:17:34 by tpillot           #+#    #+#             */
/*   Updated: 2019/07/26 10:36:57 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

uint8_t		ants_divison(t_lemin *lemin)
{
	t_list	*ways_list;
	t_way	*cur_way;
	size_t	total_ants;

	ways_list = lemin->ways_list;
	cur_way = (t_way *)ways_list->content;
	total_ants = lemin->total_ants;
	while (ways_list != NULL && lemin->total_ants != 0)
	{
		cur_way->ants = lemin->size - cur_way->size + 1;
		total_ants -= cur_way->ants
		ways_list = ways_list->next;
	}
	if (total_ants != 0)
		return (FAILURE);
	return (SUCCES);
}

void		creat_ants_list(t_lemin *lemin)
{
	size_t	id;
	t_ant	*ant;
	t_list	*new;

	id = 1;
	while (id <= lemin->total_ants)
	{
		ant = ft_memalloc(sizeof(t_ants));
		if (ant == NULL)
			return (NULL);
		ant->position = lemin->start_room;
		ant->id = id;
		new = ft_lstnew_nomalloc(ant, sizeof(t_ant));
		ft_lstadd_back(&(lemin->ants), new);
		id++;
	}
}

void		find_ant_room_and_move(t_ant *ant, t_lemin *lemin)
{
	t_list	*ways_list;
	t_list	*room_list;
	t_way	*cur_way;
	t_room	*cur_room;
	t_room	*next_room;

	ways_list = lemin->ways_list;
	while (ways_list != NULL)
	{
		cur_way = (t_way *)ways_list->content;
		room_list = cur_way->list;
		while (room_list != NULL)
		{
			cur_room = (t_room *)room_list->content;
			next_room = (t_room *)room_list->next->content;
			if (ant->position == cur_room)
			{
				ant->position = next_room;
				return ;
			}
			room_list = room_list->next;
		}
		ways_list = ways_list->next;
	}
}

void		sent_first_time(t_ant *ant, t_list *ways_list)
{
	t_way	*way;
	t_list	*room_list;

	way = ways_list->content;
	if (way->ants == 0)
		return ;
	room_list = way->list->next;
	ants->position = (t_room *)room_list->content;
	way->ants--;
}

void		print_result(t_lemin *lemin)
{
	t_list	*ants_list;
	t_ant	*cur_ant;

	ants_list = lemin->ants;
	while (ants_list != NULL)
	{
		cur_ant = (t_ant *)ants_list->content;
		if (cur_ant->position != lemin->start_room)
		{
			ft_prinf("L%zu-%s", cur_ant->id, cur_ant->position->name);
			if (ants_list->next != NULL)
				ft_prinf(" ");
		}
		if (cur_ant->position == lemin->end_room)
		{
			ft_lstdelnode(&ants_list, , &free_ant(cur_ant))
			ants_list = lemin->ants;
		}
		else
			ants_list = ants_list->next;
	}
}

void		move_ants(t_lemin *lemin)
{
	t_list	*way_list
	t_ant	*cur_ant;

	ants_list = lemin->ants;
	cur_ant = (t_ant *)ants_list->content;
	way_list = lemin->ways_list;
	while (ants_list != NULL && ants_list != NULL)
	{
		if (cur_ant->position == lemin->start_room)
		{
			if (way_list == NULL)
				return ;
			sent_first_time(cur_ant, ways_list);
		}
		find_ant_room_move_and_move(cur_ant, lemin);
	}
	print_result(lemin->ways_list)
}

void		completed_result(t_lemin *lemin)
{
	create_ants_list(lemin);
	if (ants_divison(lemin) == FAILURE)
		return (FAILURE);
	while (lemin->ants != NULL)
		move_ants(lemin);
}
