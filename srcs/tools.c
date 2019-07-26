/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 10:06:13 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/26 10:10:54 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

uint8_t		is_way_free(t_list *lst)
{
	t_room *room;

	while (lst != NULL)
	{
		room = (t_room *)lst->content;
		if (room->mark == MARK)
			return (FALSE);
		lst = lst->next;
	}
	return (TRUE);
}

void		mark_way(t_list *lst, uint8_t mark)
{
	t_room *room;

	if (lst != NULL)
		lst = lst->next;
	while (lst != NULL && lst->next != NULL)
	{
		room = (t_room *)lst->content;
		room->mark = mark;
		lst = lst->next;
	}
}

size_t		get_nb_max_ways(t_lemin *lemin)
{
	if (lemin->start_room->nb_links > lemin->end_room->nb_links)
		return (lemin->end_room->nb_links);
	return (lemin->start_room->nb_links);
}

int			sort_by_size(void *content1, void *content2)
{
	t_way	*way1;
	t_way	*way2;

	way1 = (t_way *)content1;
	way2 = (t_way *)content2;
	if (way1 == NULL || way2 == NULL)
		return (0);
	return (way1->size < way2->size);
}

uint8_t		is_oneshot(t_lemin *lemin, t_way *way)
{
	if (way->size == 1)
		lemin->oneshot = TRUE;
	return (lemin->oneshot);
}
