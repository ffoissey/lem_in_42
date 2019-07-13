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
		ft_printf("\033[31m\n%s\033[0m\n", room->name);
		ft_printf("|-----> ");
		print_room_links(room->links);
		run = run->next;
	}
}

void	print_graph(t_lemin *lemin)
{
	ft_printf("\033[33m\n####### DEBUG MODE ######\033[0m\n\n");
	ft_printf("------ START | END ------\n\n");
	ft_printf("Start: \033[36m%s\033[0m | End: \033[36m%s\033[0m\n\n",
				lemin->start_room->name, lemin->end_room->name);
	print_room_list(lemin->main_list_room);
	ft_printf("\033[33m\n#########################\033[0m\n");
}