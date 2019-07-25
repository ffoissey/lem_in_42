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

static uint8_t	is_oneshot(t_lemin *lemin, t_way *way)
{
	if (way->size == 1)
		lemin->oneshot = TRUE;
	return (lemin->oneshot);
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
			if (is_oneshot(lemin, way) == TRUE)
				return ;
			better_size = cur_size;
			lemin->way_list = way->link;
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
