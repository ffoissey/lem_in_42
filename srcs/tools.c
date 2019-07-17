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

static void	erase_same_way(t_list *way_list)
{
	t_way	*cur_way;
	t_way	*ref_way;
	t_list	*previous;

	ref_way = (t_way *)way_list->content;
	previous = way_list;
	way_list = way_list->next;
	while (way_list != NULL)
	{
		cur_way = (t_way *)way_list->content;
		if (cur_way->size > ref_way->size)
			return ;
		if (is_same_way(cur_way, ref_way) == TRUE)
		{
			//// FREE CUR_WAY
			previous->next = way_list->next;	
			way_list = previous->next;
		}
		else
		{
			previous = way_list;
			way_list = way_list->next;
		}
	}
}

void		delete_duplicate_ways(t_lemin *lemin)
{
	size_t	 i;
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
