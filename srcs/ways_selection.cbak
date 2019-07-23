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

t_setup		*get_better_setup(t_lemin *lemin, t_list *setup_list)
{
	t_setup	*setup;
	t_setup	*better_setup;
	float	better_size;

	better_setup = NULL;
	better_size = 0;
	while (setup_list != NULL)
	{
		setup = (t_setup *)setup_list->content;
		if (setup->nb_ways > 0)
		{
			if (better_size == 0
				|| (float)((float)((float)lemin->total_ants + (float)setup->size) / (float)setup->nb_ways) < better_size)
			{
				better_size = (float)((float)((float)lemin->total_ants + (float)setup->size) / (float)setup->nb_ways);
				better_setup = setup; 
			}
		}
		setup_list = setup_list->next;
	}
	return (better_setup);
}

void			ways_selection(t_lemin *lemin)
{
	ft_lst_mergesort(&lemin->possible_way_list, sort_by_size);
	if (lemin->nb_ways == 0 || lemin->nb_max_ways == 0)
	{
		ft_printf("No way is possible\n");
		return ;
	}
	delete_duplicate_ways(lemin);
	get_way_links(lemin);
	lemin->better_setup = get_better_setup(lemin, lemin->setup_list);
	lemin->way_list = lemin->better_setup->way_list;
	lemin->nb_ways = lemin->better_setup->nb_ways;
	ft_lst_mergesort(&lemin->way_list, sort_by_size);
}
