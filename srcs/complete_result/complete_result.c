/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_result.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpillot <tpillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 10:25:08 by tpillot           #+#    #+#             */
/*   Updated: 2019/07/27 13:09:52 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		find_ant_room_and_move(t_ant *ant, t_lemin *lemin)
{
	t_list	*ways_list;
	t_list	*room_list;
	t_way	*cur_way;
	t_room	*cur_room;
	t_room	*next_room;

	ways_list = lemin->way_list;
	while (ways_list != NULL)
	{
		cur_way = (t_way *)ways_list->content;
		room_list = cur_way->list;
		while (room_list->next != NULL)
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

static void		sent_first_time(t_ant *ant, t_list *ways_list)
{
	t_way	*way;
	t_room	*room;

	way = (t_way *)ways_list->content;
	if (way->ants == 0)
		return ;
	room = (t_room *)way->list->next->content;
	ant->position = room;
	way->ants--;
}

static void		print_move(t_lemin *lemin)
{
	t_list	*ants_list;
	t_ant	*cur_ant;

	ants_list = lemin->ants;
	while (ants_list != NULL)
	{
		cur_ant = (t_ant *)ants_list->content;
		if (cur_ant->position != lemin->start_room)
		{
			ft_printf("L%zu-%s", cur_ant->id, cur_ant->position->name);
			if (ants_list->next != NULL)
				ft_putchar(' ');
		}
		ants_list = ants_list->next;
		if (cur_ant->position == lemin->end_room)
			ft_lstdelnode(&lemin->ants, cur_ant, &free_ant);
	}
	if (lemin->option & COUNT_OPT)
		lemin->count++;
	ft_putchar('\n');
}

static void		move_ants(t_lemin *lemin)
{
	t_list	*way_list;
	t_list	*ants_list;
	t_ant	*cur_ant;

	ants_list = lemin->ants;
	way_list = lemin->way_list;
	while (ants_list != NULL)
	{
		cur_ant = (t_ant *)ants_list->content;
		if (cur_ant->position == lemin->start_room)
		{
			if (way_list == NULL)
				break ;
			sent_first_time(cur_ant, way_list);
			if (lemin->oneshot == FALSE)
				way_list = way_list->next;
		}
		else
			find_ant_room_and_move(cur_ant, lemin);
		ants_list = ants_list->next;
	}
	print_move(lemin);
}

int8_t			complete_result(t_lemin *lemin)
{
	if (create_ants_list(lemin) == FAILURE)
		return (FAILURE);
	ants_divison(lemin);
	ft_putchar('\n');
	while (lemin->ants != NULL)
		move_ants(lemin);
	return (SUCCESS);
}
