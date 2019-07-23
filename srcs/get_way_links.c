
#include "lemin.h"

uint8_t		match_with_others(t_way *way, t_list *way_list)
{
	t_way	*cur_way;

	mark_way(way->list, MARK);
	while (way_list != NULL)
	{
		cur_way = (t_way *)way_list->content;
		if (is_way_free(cur_way->list) == FALSE)
		{
			mark_way(way->list, UNMARK);
			return (FALSE);
		}
		way_list = way_list->next;
	}
	mark_way(way->list, UNMARK);
	return (TRUE);
}

void		create_way_link(t_way *way, t_list *way_list, t_lemin *lemin)
{
	t_way	*cur_way;
	t_list	*way_node;
	float	better_size;
	size_t	hits;


	hits = lemin->better_hits;
	better_size = 0;
	mark_way(way->list, MARK);
	way->nb_links = 1;
	way->total_size = way->size - (way->size <= lemin->total_ants ? 1 : 0);
	while (hits <= lemin->max_hits)
	{
		if (way->nb_links == lemin->total_ants)
			break ;
		cur_way = (t_way *)way_list->content;
		if (way->moy_hit <= hits
			&& is_way_free(cur_way->list) == TRUE
			&& (better_size == 0
			|| (float)((float)(lemin->total_ants + way->total_size + cur_way->size)
				/ (float)(way->nb_links + 1)) < better_size))
		{
			if (match_with_others(cur_way, way->link) == TRUE)
			{
				way_node = ft_lstnew_nomalloc(cur_way, sizeof(t_way *));
				ft_lstadd(&(way->link), way_node);
				way->nb_links++;
				way->total_size += cur_way->size - (cur_way->size <= lemin->total_ants ? 1 : 0);
				better_size = (float)((float)(lemin->total_ants + way->total_size) / (float)way->nb_links);
				way_list = lemin->possible_way_list;
			}
			else
				way_list = way_list->next;
		}
		else
			way_list = way_list->next;
		if (way_list == NULL)
		{
			way_list = lemin->possible_way_list;
			hits++;
		}
	}
	way_node = ft_lstnew_nomalloc(way, sizeof(t_way *));
	ft_lstadd(&(way->link), way_node);
	mark_way(way->list, UNMARK);
}

void		get_way_links(t_lemin *lemin)
{
	t_list	*way_list;

	way_list = lemin->possible_way_list;
	while (way_list != NULL)
	{
		create_way_link(way_list->content, lemin->possible_way_list, lemin);
		way_list = way_list->next;
	}
}
