#include "lemin.h"

static void	print_room_links(t_list *run)
{
	t_room	*room;

	while (run != NULL)
	{
		room = (t_room *)run->content;
		ft_printf("\033[32m%s\033[0m", room->name);
		run = run->next;
		if (run != NULL)
			ft_printf(" | ");
	}
	ft_putchar('\n');
}

static void	print_room_list(t_list *run)
{
	t_room *room;

	ft_printf("------- ALL ROOMS -------\n");
	while (run != NULL)
	{
		room = (t_room *)run->content;
		ft_printf("\033[31m%s\033[0m\n", room->name);
		ft_printf("|--> linked to: ");
		print_room_links(room->links);
		run = run->next;
	}
	ft_printf("-------------------------\n");
}

void	print_graph(t_lemin *lemin)
{
	print_room_list(lemin->main_list_room);
}
