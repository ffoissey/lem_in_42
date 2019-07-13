#include "lemin.h"

static void	free_links_list(t_list *lst)
{
	if (lst == NULL)
		return ;
	free_links_list(lst->next);
	free(lst);
}

static void	free_room(t_room *room)
{
	ft_strdel(&room->name);
	free_links_list(room->links);
	free(room);
}

static void	free_main_list_room(t_list *lst)
{
	if (lst == NULL)
		return ;
	free_main_list_room(lst->next);
	free_room((t_room *)lst->content);
	free(lst);
}

void	exit_routine(t_lemin *lemin)
{
	free_main_list_room(lemin->main_list_room);
}
