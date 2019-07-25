/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 17:50:47 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/23 17:57:53 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int8_t		get_best_way_set(t_lemin *lemin)
{
	set_distance(lemin);
//	print_graph(lemin);	/// GRAPH DEBUG
	graph_course(lemin);
	if (ways_selection(lemin) == FAILURE)
		return (FAILURE);
//	print_list_ways(lemin); /// WAY LIST DEBUG
	return (SUCCESS);
}

int					main(void)
{
	t_lemin lemin;

	ft_bzero(&lemin, sizeof(lemin));
	if (parser(&lemin) == FAILURE)
	{
		print_error(lemin.error);
		exit_routine(&lemin);
		return (EXIT_FAILURE);
	}
	if (get_best_way_set(&lemin) == FAILURE)
	{
		ft_putendl_fd("No way is possible", 2);
		exit_routine(&lemin);
		return (EXIT_FAILURE);
	}
	complete_result(&lemin);
	exit_routine(&lemin);
	return (EXIT_SUCCESS);
}
