/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 11:08:43 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/12 11:58:54 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int8_t		parser(t_lemin *lemin)
{
	static t_parsing	parsing[] = {get_ants, get_rooms, get_links};
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
			return (SUCCESS);
		ft_strdel(&line);
	}
	if (lemin->error) //is_major_error(lemin->error) == TRUE)
	{
		print_error(lemin->error);
		// FREE ROUTINE
		return (FAILURE);
	}
	return (SUCCESS);
}
