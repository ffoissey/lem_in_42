/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 17:50:47 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/26 09:55:41 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int8_t		get_best_way_set(t_lemin *lemin)
{
	set_distance(lemin);
	if (lemin->option & GRAPH_OPT)
		print_graph(lemin);
	graph_course(lemin);
	if (ways_selection(lemin) == FAILURE)
		return (FAILURE);
	if (lemin->option & WAYS_OPT)
		print_list_ways(lemin);
	return (SUCCESS);
}

static int8_t		parse_arg(t_lemin *lemin, char **arg)
{
	while (*arg != NULL)
	{
		if (ft_strequ(*arg, "--count") == TRUE)
			lemin->option |= COUNT_OPT;
		else if (ft_strequ(*arg, "--nomap") == TRUE)
			lemin->option |= NOMAP_OPT;
		else if (ft_strequ(*arg, "--onlycom") == TRUE)
			lemin->option |= ONLYCOM_OPT;
		else if (ft_strequ(*arg, "--graph") == TRUE)
			lemin->option |= GRAPH_OPT;
		else if (ft_strequ(*arg, "--ways") == TRUE)
			lemin->option |= WAYS_OPT;
		else
		{
			ft_dprintf(2, "lem-in: %s: Invalid option\n", *arg);
			ft_dprintf(2, "usage: ./lem-in [--option]\n");
			ft_dprintf(2, "options: --nomap\n\t --onlycom\n\t");
			ft_dprintf(2, " --count\n\t --ways\n\t --graph\n");
			return (FAILURE);
		}
		arg++;
	}
	return (SUCCESS);
}

int					main(int ac, char **av)
{
	t_lemin lemin;

	(void)ac;
	ft_bzero(&lemin, sizeof(lemin));
	if (parse_arg(&lemin, av + 1) == FAILURE)
		return (EXIT_FAILURE);
	if (parser(&lemin) == FAILURE)
	{
		print_error(lemin.error);
		exit_routine(&lemin);
		return (EXIT_FAILURE);
	}
	if (get_best_way_set(&lemin) == FAILURE)
	{
		ft_putendl_fd("lem-in: error: No way is possible", 2);
		exit_routine(&lemin);
		return (EXIT_FAILURE);
	}
	complete_result(&lemin);
	if (lemin.option & COUNT_OPT)
		ft_printf("Count : %zu\n", lemin.count);
	exit_routine(&lemin);
	return (EXIT_SUCCESS);
}
