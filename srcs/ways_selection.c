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
		if (better_size == 0
			|| (float)((float)(lemin->total_ants + way->total_size) / (float)way->nb_links) < better_size)
		{
			better_size = (float)((float)(lemin->total_ants + way->total_size) / (float)way->nb_links);
			better_list = way->link;
			lemin->nb_ways = way->nb_links;
			lemin->size = better_size;
		}
		way_list = way_list->next;
	}
	lemin->way_list = better_list;
}

void			get_hits(t_lemin *lemin)
{
	t_list	*way_list;
	t_way	*way;
	t_list	*links;
	t_room	*room;

	way_list = lemin->possible_way_list;
	while (way_list != NULL)
	{
		way = (t_way *)way_list->content;
		links = way->link;
		while (links != NULL)
		{
			room = (t_room *)links->content;
			room->hit++;
			links = links->next;
		}
		way_list = way_list->next;
	}
	way_list = lemin->possible_way_list;
	while (way_list != NULL)
	{
		way = (t_way *)way_list->content;
		links = way->link;
		while (links != NULL)
		{
			room = (t_room *)links->content;
			way->moy_hit += room->hit;
			links = links->next;
		}
		if (way->size == 0)
			way->moy_hit = 0;
		else
			way->moy_hit = way->moy_hit / way->size + way->moy_hit % way->size;
		if (lemin->better_hits == 0 || way->moy_hit < lemin->better_hits)
			lemin->better_hits = way->moy_hit;
		if (lemin->max_hits == 0 || way->moy_hit > lemin->max_hits)
			lemin->max_hits = way->moy_hit;
		way_list = way_list->next;
	}
}

void			ways_selection(t_lemin *lemin)
{
	ft_lst_mergesort(&lemin->possible_way_list, sort_by_size);
	lemin->nb_max_ways = get_nb_max_ways(lemin);
	get_hits(lemin);
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
