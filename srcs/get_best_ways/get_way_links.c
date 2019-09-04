/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_way_links.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 10:29:44 by ffoissey          #+#    #+#             */
/*   Updated: 2019/09/04 13:39:10 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void				hit_way_rooms(t_list *lst, int64_t inc)
{
	t_room *room;

	if (lst != NULL)
		lst = lst->next;
	while (lst != NULL && lst->next != NULL)
	{
		room = (t_room *)lst->content;
		if (inc == INCREMENT || room->hit != 1)
			room->hit += inc;
		lst = lst->next;
	}
}

static float		match_try(t_lemin *lemin, t_way *way, t_way *cur_way,
		float better_size)
{
	t_list	*way_node;
	float	cur_size;

	if (is_way_free(cur_way->list) == TRUE)
	{
		hit_way_rooms(cur_way->list, INCREMENT);
		cur_size = (float)((float)(lemin->total_ants + way->total_size
					+ cur_way->size) / (float)(way->nb_links + 1));
		way_node = ft_lstnew_nomalloc(cur_way, sizeof(t_way *));
		ft_lstadd(&(way->link), way_node);
		way->nb_links++;
		way->total_size += cur_way->size
			- (cur_way->size <= lemin->total_ants ? 1 : 0);
		better_size = cur_size;
	}
	return (better_size);
}

static void			create_way_link(t_way *way, t_list *way_list,
		t_lemin *lemin)
{
	t_way	*cur_way;
	t_list	*way_node;
	float	better_size;

	better_size = 0;
	mark_way(way->list, MARK);
	way->nb_links = 1;
	way->total_size = way->size - (way->size <= lemin->total_ants ? 1 : 0);
	while (way_list != NULL)
	{
		if (way->nb_links == lemin->total_ants)
			break ;
		cur_way = (t_way *)way_list->content;
		if (cur_way != way)
			better_size = match_try(lemin, way, cur_way, better_size);
		way_list = way_list->next;
	}
	way_node = ft_lstnew_nomalloc(way, sizeof(t_way *));
	ft_lstadd(&(way->link), way_node);
	mark_way(way->list, UNMARK);
	ft_lst_mergesort(&(way->link), sort_by_size);
}

uint8_t				is_unique(t_way *way)
{
	t_room *room;
	t_list *lst;

	lst =  way->list;
	if (lst != NULL)
		lst = lst->next;
	while (lst != NULL && lst->next != NULL)
	{
		room = (t_room *)lst->content;
		if (room->hit > 1)
			return (FALSE);
		lst = lst->next;
	}
	return (TRUE);
}

uint8_t				is_only_unique_ways(t_list *lst)
{
	t_way *way;

	while (lst != NULL)
	{
		way = (t_way *)lst->content;
		if (is_unique(way) == FALSE)
			return (FALSE);
		lst = lst->next;
	}
	return (TRUE);
}

void				select_ways(t_way *way, t_lemin *lemin)
{
	t_list	*lst;
	t_way	*cur_way;
	t_way	*bad_way;
	int64_t	delta;
	int64_t	cur_delta;
	int64_t	potential_size;
	int64_t	new_size;
	int64_t	size;
	uint8_t	set;

	while (is_only_unique_ways(way->link) == FALSE)
	{
		lst = way->link;
		delta = 0;
		size = (int64_t)((float)(lemin->total_ants + way->total_size / (float)(way->nb_links)));
		new_size = size;
		bad_way = NULL;
		set = FALSE;
		while (lst != NULL)
		{
			cur_way = (t_way *)lst->content;
			if (is_unique(cur_way) == TRUE || cur_way == way)
			{
				lst = lst->next;
				continue ;
			}
			potential_size = (int64_t)((float)(lemin->total_ants + way->total_size
						- cur_way->size) / (float)(way->nb_links - 1));
			cur_delta = size - potential_size;
			if (cur_delta <= delta || set == FALSE)
			{
				//ft_printf("size  : %3d, delta    : %3d\np_size: %3d, cur_delta: %3d\n\n", size, delta, potential_size, cur_delta);
				delta = cur_delta;
				set = TRUE;
				bad_way = cur_way;
				new_size = potential_size;
			}
			lst = lst->next;
		}
		if (bad_way != NULL)
		{
			hit_way_rooms(bad_way->list, DECREMENT);
			way->nb_links--;
			way->total_size -= bad_way->size;
			way->total_size = new_size;
			ft_lstdelnode(&way->link, bad_way, NULL);
		}
	}
}

void				decrement_all_rooms(t_way *way)
{
	t_list	*lst;
	t_way	*cur_way;

	lst = way->link;
	while (lst != NULL)
	{
		cur_way = (t_way *)lst->content;
		hit_way_rooms(cur_way->list, DECREMENT);
		lst = lst->next;
	}
}

void				get_way_links(t_lemin *lemin)
{
	t_list	*way_list;

	way_list = lemin->possible_way_list;
	while (way_list != NULL)
	{
		create_way_link(way_list->content, lemin->possible_way_list, lemin);
		select_ways(way_list->content, lemin);
		decrement_all_rooms(way_list->content);
		way_list = way_list->next;
	}
	way_list = lemin->possible_way_list;
}
