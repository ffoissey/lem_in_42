#include "lemin.h"

int		sort_by_size(void *content1, void *content2)
{
	t_way	*way1;
	t_way	*way2;

	way1 = (t_way *)content1;
	way2 = (t_way *)content2;
	if (way1 == NULL || way2 == NULL)
		return (0);
	return (way1->size < way2->size);
}

void	ways_selection(t_lemin *lemin)
{
	///SORT WAYS
	ft_lst_mergesort(&lemin->way_list, sort_by_size);
}
