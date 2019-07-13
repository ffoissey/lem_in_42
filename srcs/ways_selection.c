#include "lemin.h"

int				sort_by_size(void *content1, void *content2)
{
	t_way	*way1;
	t_way	*way2;

	way1 = (t_way *)content1;
	way2 = (t_way *)content2;
	if (way1 == NULL || way2 == NULL)
		return (0);
	return (way1->size < way2->size);
}

static size_t	get_nb_max_ways(t_lemin *lemin)
{
	if (lemin->start_room->nb_links > lemin->end_room->nb_links)
		return (lemin->end_room->nb_links);
	return (lemin->start_room->nb_links);
}

static size_t	try_to_match(t_lemin *lemin, t_list *way_list,
					size_t count, size_t nb_ways)
{
	t_way	*way;
	t_list	*new_way;

	while (way_list != NULL)
	{
		way = (t_way *)way_list->content;
		if (way->size > lemin->total_ants + 1)
			return (FAILURE);
		if (mark_way(way->list, MARK) == SUCCESS)
		{
			new_way = ft_lstnew_nomalloc(way, sizeof(t_way *));
			ft_lstadd(&lemin->way_list, new_way);
			if (try_to_match(lemin, way_list->next,
								count + 1, nb_ways) == nb_ways)
			{
				mark_way(way->list, UNMARK);
				return (SUCCESS);
			}
			ft_lstpop(&lemin->way_list);
		}
		mark_way(way->list, UNMARK);
		way_list = way_list->next;
	}
	return (count);
}


void			ways_selection(t_lemin *lemin)
{
	size_t	nb_max_ways;
	t_list	*new_way;

	ft_lst_mergesort(&lemin->possible_way_list, sort_by_size);
	lemin->nb_max_ways = get_nb_max_ways(lemin);
	nb_max_ways = lemin->nb_max_ways;
	while (nb_max_ways > 1 && lemin->way_list == NULL)
	{
		try_to_match(lemin, lemin->possible_way_list, 0, nb_max_ways);
		nb_max_ways--;
	}
	if (lemin->way_list == NULL)
	{
		if (lemin->possible_way_list != NULL)
		{
			new_way = ft_lstnew_nomalloc(lemin->possible_way_list->content,
					sizeof(t_way *));
			ft_lstadd(&lemin->way_list, new_way);
		}
	}	
	else
		ft_lst_mergesort(&lemin->way_list, sort_by_size);
}
