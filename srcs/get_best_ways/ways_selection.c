/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ways_selection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 10:06:09 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/26 10:36:04 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static uint8_t	is_same_way(t_way *cur_way, t_way *ref_way)
{
	t_list	*current;
	t_list	*ref;

	current = cur_way->list;
	ref = ref_way->list;
	while (current != NULL && ref != NULL)
	{
		if (ref->content != current->content)
			return (FALSE);
		current = current->next;
		ref = ref->next;
	}
	return (TRUE);
}

static void		erase_same_way(t_list *way_list)
{
	t_way	*ref_way;
	t_list	*tmp;
	t_list	*previous;

	ref_way = (t_way *)way_list->content;
	previous = way_list;
	way_list = way_list->next;
	while (way_list && ((t_way *)(way_list->content))->size <= ref_way->size)
	{
		if (is_same_way((t_way *)way_list->content, ref_way) == TRUE)
		{
			tmp = way_list;
			previous->next = way_list->next;
			free_links_list(((t_way *)(tmp->content))->list);
			((t_way *)(tmp->content))->list = NULL;
			free(tmp->content);
			free(tmp);
			way_list = previous->next;
		}
		else
		{
			previous = way_list;
			way_list = way_list->next;
		}
	}
}

static void		delete_duplicate_ways(t_lemin *lemin)
{
	size_t	i;
	t_list	*way_list;

	i = 0;
	way_list = lemin->possible_way_list;
	while (way_list != NULL && way_list->next != NULL)
	{
		erase_same_way(way_list);
		way_list = way_list->next;
		i++;
	}
	lemin->nb_ways = i + 1;
}

static void		get_better_ways_set(t_lemin *lemin)
{
	t_list	*way_list;
	t_way	*way;
	float	cur_size;
	float	better_size;

	way_list = lemin->possible_way_list;
	lemin->nb_ways = 0;
	better_size = 0;
	while (way_list != NULL)
	{
		way = (t_way *)way_list->content;
		cur_size = (float)((float)(lemin->total_ants + way->total_size)
				/ (float)way->nb_links);
		if (better_size == 0 || cur_size <= better_size || way->size == 1)
		{
			lemin->nb_ways = way->nb_links;
			lemin->size = (size_t)cur_size;
			better_size = cur_size;
			lemin->way_list = way->link;
			if (is_oneshot(lemin, way) == TRUE)
				return ;
		}
		way_list = way_list->next;
	}
}

int8_t			ways_selection(t_lemin *lemin)
{
	ft_lst_mergesort(&lemin->possible_way_list, sort_by_size);
	if (lemin->nb_ways == 0 || lemin->nb_max_ways == 0)
		return (FAILURE);
	delete_duplicate_ways(lemin);
	get_way_links(lemin);
	get_better_ways_set(lemin);
	return (SUCCESS);
}
