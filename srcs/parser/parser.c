/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 11:08:43 by ffoissey          #+#    #+#             */
/*   Updated: 2019/08/02 12:09:49 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int8_t	post_parsing(t_lemin *lemin)
{
	if (lemin->main_list_room == NULL && lemin->error == NO_ERR)
		lemin->error = FILE_ERR;
	else if (lemin->error == FALSE && lemin->links_validation == FALSE)
		lemin->error = LINKS_ERR | BAD_FORMAT;
	return (lemin->error == NO_ERR || (lemin->links_validation == TRUE
				&& (lemin->error & LINKS_ERR)) ? SUCCESS : FAILURE);
}

int8_t		parser(t_lemin *lemin)
{
	static t_parsing	parsing[3] = {get_ants, get_rooms, get_links};
	char				*line;
	t_list				*map_line;
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
		map_line = ft_lstnew(line, ft_strlen(line) + 1);
		ft_lstadd(&lemin->map, map_line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	get_next_line(CLEANUP, NULL);
	return (post_parsing(lemin));
}
