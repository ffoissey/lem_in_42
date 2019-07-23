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

static void		get_better_ways_set(t_lemin *lemin)
{
	t_list	*way_list;
	t_way	*way;
	t_list	*better_list;
	size_t	better_size;

	way_list = lemin->possible_way_list;
	better_size = 0;
	while (way_list != NULL)
	{
		way = (t_way *)way_list->content;
//		if (better_size == 0
//			|| (float)((float)((float)lemin->total_ants + (float)way_nb_links) / (float)setup->nb_ways) < better_size)
		if (way->nb_links > better_size)
		{
			better_size = way->nb_links;
			better_list = way->link;
		}
		way_list = way_list->next;
	}
	lemin->way_list = better_list;
	lemin->nb_ways = better_size;
}

void			ways_selection(t_lemin *lemin)
{
	ft_lst_mergesort(&lemin->possible_way_list, sort_by_size);
	lemin->nb_max_ways = get_nb_max_ways(lemin);
	if (lemin->nb_ways == 0 || lemin->nb_max_ways == 0)
	{
		ft_printf("No way is possible\n");
		return ;
	}
	delete_duplicate_ways(lemin);
	get_way_links(lemin);
	get_better_ways_set(lemin);
	ft_lst_mergesort(&lemin->way_list, sort_by_size);
}
