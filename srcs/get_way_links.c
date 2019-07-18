
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

int8_t		get_way_setup(t_way *way, t_list *links, size_t size, size_t nb_ways, t_lemin *lemin)
{
	t_way	*cur_way;
	t_list	*way_node;
	t_list	*setup_node;
	t_setup	new_setup;

	if (nb_ways != 0 && lemin->better_setup != NULL)
	{
		if ((float)(lemin->total_ants + size) / nb_ways
				< (float)(lemin->total_ants + lemin->better_setup->size) / lemin->better_setup->nb_ways)
			return (FAILURE);
	}
	while (links != NULL)
	{
		cur_way = (t_way *)links->content;
		if (is_way_free(cur_way->list) == TRUE)
		{
			mark_way(cur_way->list, MARK);
			if (get_way_setup(way, links->next, size + cur_way->size, nb_ways + 1, lemin) == SUCCESS)
			{
				way_node = ft_lstnew_nomalloc(cur_way, sizeof(t_way *));
				ft_lstadd(&((t_setup *)(way->setup_list->content))->way_list, way_node);
			}
			mark_way(cur_way->list, UNMARK);
		}
		links = links->next;
	}
	if (nb_ways != 0)
	{
		ft_bzero(&new_setup, sizeof(new_setup));
		setup_node = ft_lstnew(&new_setup, sizeof(new_setup));
		ft_lstadd(&(way->setup_list), setup_node);
		way_node = ft_lstnew_nomalloc(way, sizeof(t_way *));
		ft_lstadd(&((t_setup *)(way->setup_list->content))->way_list, way_node);
		((t_setup *)(way->setup_list->content))->nb_ways = nb_ways + 1;
		((t_setup *)(way->setup_list->content))->size = size + way->size;
	}
	return (SUCCESS);
}

void		create_potential_links(t_way *way, t_list *way_list)
{
	t_way	*cur_way;
	t_list	*way_node;

	mark_way(way->list, MARK);
	while (way_list != NULL)
	{
		cur_way = (t_way *)way_list->content;
		if (is_way_free(cur_way->list) == TRUE)
		{
			way_node = ft_lstnew_nomalloc(cur_way, sizeof(t_way *));
			ft_lstadd(&(way->link), way_node);
			way->nb_links++;
		}
		way_list = way_list->next;
	}
	way->nb_links++;
	way_node = ft_lstnew_nomalloc(way, sizeof(t_way *));
	ft_lstadd(&(way->link), way_node);
	mark_way(way->list, UNMARK);
	ft_lst_mergesort(&way->link, sort_by_size);
}

void		get_way_links(t_lemin *lemin)
{
	t_list	*way_list;
	t_way	*way;
	t_list	*node;

	way_list = lemin->possible_way_list;
	while (way_list != NULL)
	{
		way = (t_way *)way_list->content;
		create_potential_links(way, lemin->possible_way_list);
		get_way_setup(way, way->link, 0, 0, lemin);
		node = ft_lstnew_nomalloc(get_better_setup(lemin, way->setup_list), sizeof(t_setup *));
		ft_lstadd(&lemin->setup_list, node);
		lemin->better_setup = get_better_setup(lemin, lemin->setup_list);
		way_list = way_list->next;
	}
}
