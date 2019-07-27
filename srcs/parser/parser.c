/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 11:08:43 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/27 13:11:30 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	print_line(t_lemin *lemin, char *line)
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

int8_t		parser(t_lemin *lemin)
{
	static t_parsing	parsing[3] = {get_ants, get_rooms, get_links};
	char				*line;
	int					ret;

	line = NULL;
	lemin->state = GET_ANTS;
	while (lemin->error == NO_ERR)
	{
		if ((ret = get_next_line(STDIN_FILENO, &line)) > 0)
			parsing[lemin->state](lemin, line);
		else if (ret == FAILURE)
			lemin->error = READ_ERR;
		else
			break ;
		print_line(lemin, line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	get_next_line(CLEANUP, NULL);
	if (lemin->links_validation == FALSE)
		lemin->error = LINKS_ERR | BAD_FORMAT;
	if (lemin->main_list_room == NULL && lemin->error == NO_ERR)
		lemin->error = FILE_ERR;
	return (lemin->error == NO_ERR || (lemin->links_validation == TRUE
				&& (lemin->error & LINKS_ERR)) ? SUCCESS : FAILURE);
}
