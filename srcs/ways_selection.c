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


static int8_t	try_to_match(t_lemin *lemin, t_list *way_list,
					size_t count, size_t nb_ways)
{
	t_way	*way;
	t_list	*new_way;

	if (count == nb_ways)
		return (SUCCESS);
	while (way_list != NULL)
	{
		way = (t_way *)way_list->content;
		if (way->size > lemin->total_ants)
			return (FAILURE);
		if (is_way_free(way->list) == TRUE)
		{
			mark_way(way->list, MARK);
			if (try_to_match(lemin, way_list->next, count + 1,
						nb_ways) == SUCCESS)
			{
				new_way = ft_lstnew_nomalloc(way, sizeof(t_way *));
				ft_lstadd(&lemin->way_list, new_way);
				lemin->nb_ways++;
				return (SUCCESS);
			}
			mark_way(way->list, UNMARK);
		}
		way_list = way_list->next;
	}
	return (FAILURE);
}

void			just_one_way(t_lemin *lemin)
{
	t_list	*new_way;
	t_way	*way;

	way = (t_way *)lemin->possible_way_list->content;
	new_way = ft_lstnew_nomalloc(way, sizeof(t_way *));
	ft_lstadd(&lemin->way_list, new_way);
}

void			ways_selection(t_lemin *lemin)
{
	size_t	nb_max_ways;
	t_list	*way_list;
	size_t	nb_ways;

	ft_lst_mergesort(&lemin->possible_way_list, sort_by_size);
	lemin->nb_max_ways = get_nb_max_ways(lemin);
	if (lemin->nb_ways == 0 || lemin->nb_max_ways == 0)
	{
		ft_printf("No way is possible\n");
		return ;
	}
	delete_duplicate_ways(lemin);
	way_list = NULL;
	nb_ways = 0;
	nb_max_ways = 2;
	while (nb_max_ways <= lemin->nb_max_ways)
	{
		lemin->nb_ways = 0;
		lemin->way_list = NULL;
		if (try_to_match(lemin, lemin->possible_way_list, 0, nb_max_ways) == FAILURE)
		{
			lemin->way_list = way_list;
			lemin->nb_ways = nb_ways;
			break ;
		}
		nb_ways = lemin->nb_ways;
		//////// free way_list
		///// keep reference nb
		way_list = lemin->way_list;
		nb_max_ways++;
	}
	if (lemin->way_list == NULL)
	{
		lemin->nb_ways = 1;
		just_one_way(lemin);
	}
}
