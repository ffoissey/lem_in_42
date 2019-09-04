/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 17:50:47 by ffoissey          #+#    #+#             */
/*   Updated: 2019/09/04 17:03:51 by ffoissey         ###   ########.fr       */
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
		else if (ft_strequ(*arg, "--verbose") == TRUE)
			lemin->option |= V_OPT;
		else
		{
			ft_dprintf(2, "lem-in: %s: Invalid option\n", *arg);
			ft_dprintf(2, "usage: ./lem-in [--option]\n");
			ft_dprintf(2, "options: --nomap\n\t --onlycom\n\t");
			ft_dprintf(2, " --count\n\t --ways\n\t --graph\n\t --verbose\n");
			return (FAILURE);
		}
		arg++;
	}
	return (SUCCESS);
}

static void			print_line(t_lemin *lemin, char *line)
{
	if ((lemin->option & NOMAP_OPT) == FALSE)
	{
		if (lemin->option & ONLYCOM_OPT)
		{
			if (line != NULL && *line == '#' && *(line + 1) != '#')
			{
				if (ft_putendl(line) == FAILURE)
					lemin->error = WRITE_ERR;
			}
		}
		else if (ft_putendl(line) == FAILURE)
			lemin->error = WRITE_ERR;
	}
}

static void			print_map(t_lemin *lemin, t_list *map)
{
	static size_t	err = 0;

	if (map != NULL)
	{
		print_map(lemin, map->next);
		if ((lemin->error & WRITE_ERR) == FALSE)
			print_line(lemin, (char *)map->content);
		else if (err == FALSE && (lemin->error & WRITE_ERR))
		{
			err++;
			ft_putstr_fd("lemin: error: ", 2);
			perror("write");
		}
	}
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
		print_error(lemin.option & V_OPT ? lemin.error | V_ERR : lemin.error);
		exit_routine(&lemin);
		return (EXIT_FAILURE);
	}
	if (get_best_way_set(&lemin) == FAILURE)
	{
		ft_putendl_fd(lemin.option & V_OPT ? STR_ERR_NOWAY : "ERROR", 2);
		exit_routine(&lemin);
		return (EXIT_FAILURE);
	}
	print_map(&lemin, lemin.map);
	complete_result(&lemin);
	if (lemin.option & COUNT_OPT)
		ft_printf("Count: \033[32m%zu\033[0m\n", lemin.count);
	exit_routine(&lemin);
	return (EXIT_SUCCESS);
}
