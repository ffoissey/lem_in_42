#include "lemin.h"

// static	t_room	*find_mark_room(t_list *links)
// {
// 	while (links)
// 	{
// 		if (((t_room*)links->content)->mark == MARK)
// 			return ((t_room*)(links->content));
// 		links = links->next;
// 	}
// 	return (NULL);
// }

static	void	add_way(t_lemin *lemin, t_way *way)
{
	t_list	*new;

	new = ft_lstnew_nomalloc(way, sizeof(t_way));
	ft_lstadd_back(&(lemin->way_list), new);
	lemin->nb_ways++;
	//DEBUG
	print_way(way);
}

static	int		save_the_way(t_lemin *lemin)
{
	t_room	*room;
	t_list	*new;
	t_way	*way;

	way = ft_memalloc(sizeof(t_way));
	if (way == NULL)
		return (FAILURE);
	room = lemin->end_room;
	while (room != lemin->start_room)
	{
		way->size++;
		new = ft_lstnew_nomalloc(room, sizeof(t_room));
		ft_lstadd(&(way->list), new);
		room = room->current_link;
	}
	way->size++;
	new = ft_lstnew_nomalloc(room, sizeof(t_room));
	ft_lstadd(&(way->list), new);
	add_way(lemin, way);
	return (SUCCESS);
}

int				graph_course(t_room *room, t_lemin *lemin)
{
	t_list *links;

	if (room == lemin->start_room)
	{
		if (save_the_way(lemin) == FAILURE)
			return (FAILURE);
		return (SUCCESS);
	}
	room->mark = MARK;
	links = room->links;
	while (links != NULL)
	{
		if (((t_room*)links->content)->mark == UNMARK)
		{
			room->current_link = ((t_room*)links->content);
			graph_course((t_room*)(links->content), lemin);
		}
		links = links->next;
	}
	room->mark = UNMARK;
	return (SUCCESS);	
}