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

void		reset_ways(t_lemin *lemin)
{
	t_way	*way;
	t_list	*way_list;

	way_list = lemin->possible_way_list;
	while (way_list != NULL)
	{
		way = (t_way *)way_list->content;
		mark_way(way->list->next, UNMARK);
		way_list = way_list->next;
	}
}

static size_t	try_to_match(t_lemin *lemin, t_list *way_list,
					size_t count, size_t nb_ways)
{
	t_way	*way;
	t_list	*new_way;

	if (count == nb_ways)
		return (SUCCESS);
	while (way_list != NULL)
	{
		way = (t_way *)way_list->content;
		if ((nb_ways == 1 || way->size < lemin->total_ants + 1)
			 && is_way_free(way->list) == TRUE)
		{
			mark_way(way->list, MARK);
			if (try_to_match(lemin, way_list->next, count + 1,
						nb_ways) == SUCCESS)
			{
				new_way = ft_lstnew_nomalloc(way, sizeof(t_way *));
				ft_lstadd(&lemin->way_list, new_way);
				return (SUCCESS);
			}
			mark_way(way->list, UNMARK);
		}
		way_list = way_list->next;
	}
	return (FAILURE);
	reset_ways(lemin);
}

void			ways_selection(t_lemin *lemin)
{
	size_t	nb_max_ways;

	ft_lst_mergesort(&lemin->possible_way_list, sort_by_size);
	print_list_ways(lemin); /// POSSIBLE WAY LIST DEBUG
	lemin->nb_max_ways = get_nb_max_ways(lemin);
	nb_max_ways = lemin->nb_max_ways;
	while (nb_max_ways > 0 && lemin->way_list == NULL)
	{
		try_to_match(lemin, lemin->possible_way_list, 0, nb_max_ways);
		nb_max_ways--;
	}
}
