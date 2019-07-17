
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

	mark_way(way->list, MARK);
	way->nb_links = 1;
	while (way_list != NULL)
	{
		cur_way = (t_way *)way_list->content;
		if (cur_way->size <= lemin->total_ants
				&& is_way_free(cur_way->list) == TRUE)
		{
			if (match_with_others(cur_way, way->link) == TRUE)
			{
				way_node = ft_lstnew_nomalloc(cur_way, sizeof(t_way *));
				ft_lstadd(&(way->link), way_node);
				way->nb_links++;
			}
		}
		way_list = way_list->next;
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
