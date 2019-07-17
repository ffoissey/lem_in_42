#include "lemin.h"

uint8_t		is_way_free(t_list *lst)
{
	t_room *room;

	while (lst != NULL)
	{
		room = (t_room *)lst->content;
		if (room->mark == MARK)
			return (FALSE);
		lst = lst->next;
	}
	return (TRUE);
}

void		mark_way(t_list *lst, uint8_t mark)
{
	t_room *room;

	if (lst != NULL)
		lst = lst->next;
	while (lst != NULL && lst->next != NULL)
	{
		room = (t_room *)lst->content;
		room->mark = mark;
		lst = lst->next;
	}
}

size_t		get_nb_max_ways(t_lemin *lemin)
{
	if (lemin->start_room->nb_links > lemin->end_room->nb_links)
		return (lemin->end_room->nb_links);
	return (lemin->start_room->nb_links);
}
