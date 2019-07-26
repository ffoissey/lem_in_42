/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 09:47:42 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/26 10:25:14 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	print_room_list(t_list *run, t_lemin *lemin)
{
	t_room *room;

	ft_printf("------- ALL ROOMS -------\n");
	while (run != NULL)
	{
		room = (t_room *)run->content;
		ft_printf("\033[31m\n%s\033[0m\n", room->name);
		ft_printf("\033[35mnb links: %d\033[0m\n",
					(int)room->nb_links);
		ft_printf("\033[35mdistance from start: %d\033[0m\n",
					(int)room->d_start);
		ft_printf("\033[35mdistance from end: %d\033[0m\n",
					(int)room->d_end);
		ft_printf("\033[35mSCORE: %d\033[0m\n",
					(int)room->score);
		ft_printf("\033[35mstate: %s\033[0m\n",
					room->mark == DEAD ? "DEAD" : "OK");
		if (room == lemin->start_room)
			ft_printf("START\n");
		else if (room == lemin->end_room)
			ft_printf("END\n");
		ft_printf("|-----> ");
		print_room_links(room->links);
		run = run->next;
	}
}

void		print_graph(t_lemin *lemin)
{
	ft_printf("\033[33m\n###### GRAPH DEBUG ######\033[0m\n\n");
	ft_printf("------ START | END ------\n\n");
	ft_printf("Start: \033[36m%s\033[0m | End: \033[36m%s\033[0m\n\n",
				lemin->start_room->name, lemin->end_room->name);
	print_room_list(lemin->main_list_room, lemin);
	ft_printf("Total ants: \033[36m%d\033[0m\n", (int)lemin->total_ants);
	ft_printf("Max ways: \033[36m%d\033[0m\n", (int)lemin->nb_max_ways);
	ft_printf("\033[33m\n#########################\033[0m\n\n");
}

static void	print_way(t_way *way)
{
	t_list	*list;

	list = way->list;
	while (list != NULL)
	{
		ft_printf("%s", ((t_room*)list->content)->name);
		if (list->next != NULL)
			ft_printf("-->");
		list = list->next;
	}
	ft_printf("\nSIZE: %d\n", (int)way->size);
}

void		print_list_ways(t_lemin *lemin)
{
	t_way	*way;
	t_list	*lst;

	ft_printf("\033[33m\n####### WAYS DEBUG ######\033[0m\n\n");
	lst = lemin->way_list;
	while (lst != NULL)
	{
		way = (t_way *)lst->content;
		print_way(way);
		lst = lst->next;
	}
	ft_printf("\n\nSET: (size: %d | nb_links: %d)\n", (int)lemin->size,
				(int)lemin->nb_ways);
	ft_printf("count ways: %d\n", (int)lemin->nb_ways);
	ft_printf("nb ants: %d\n", (int)lemin->total_ants);
	ft_printf("\033[33m\n#########################\033[0m\n\n");
}
