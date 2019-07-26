/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 10:26:31 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/26 10:47:36 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static uint8_t	is_valid_cmd(uint8_t comment)
{
	if (comment == START_CMD || comment == END_CMD)
		return (comment);
	return (FALSE);
}

static char		*get_room_name(t_lemin *lemin, char *line)
{
	char	*name;

	name = NULL;
	if (line == NULL || *line == '\0')
		lemin->error = ROOMS_ERR | BAD_FORMAT;
	else if (*line == 'L')
		lemin->error = ROOMS_ERR | BAD_START_LETTER;
	else if ((name = ft_strcdup(line, ' ')) == NULL)
		lemin->error = MALLOC_ERR;
	return (name);
}

static	size_t	get_room_coord(t_lemin *lemin, char **line)
{
	char	*coord_str;
	size_t	coord;

	if (*line == NULL || **line == '\0')
	{
		lemin->error = ROOMS_ERR | BAD_FORMAT;
		return (0);
	}
	(*line)++;
	coord_str = ft_strcdup(*line, ' ');
	if (coord_str == NULL)
	{
		lemin->error = MALLOC_ERR;
		return (0);
	}
	else if (is_correct_numeric_format(coord_str) == FALSE)
		lemin->error = ROOMS_ERR | BAD_FORMAT;
	*line += ft_strlen(coord_str);
	coord = ft_atol(coord_str);
	if (coord > INT_MAX || ft_strlen(coord_str) > 10)
		lemin->error = ROOMS_ERR | INVALID_COORD;
	ft_strdel(&coord_str);
	return (coord);
}

static int8_t	room_acquisition(t_lemin *lemin, char *line, t_room *room)
{
	ft_bzero(room, sizeof(t_room));
	room->mark = UNMARK;
	room->name = get_room_name(lemin, line);
	if (lemin->error)
		return (FAILURE);
	line = ft_strchr(line, ' ');
	room->coord.x = get_room_coord(lemin, &line);
	room->coord.y = get_room_coord(lemin, &line);
	if (lemin->error || line == NULL || *line != '\0')
	{
		if (lemin->error == NO_ERR)
			lemin->error = ROOMS_ERR | BAD_FORMAT;
		ft_strdel(&room->name);
		return (FAILURE);
	}
	return (SUCCESS);
}

int8_t			get_rooms(t_lemin *lemin, char *line)
{
	uint8_t			comment;
	static uint8_t	cmd = FALSE;
	t_room			room;

	if ((comment = is_comment(line)) & COMMENT)
		return (SUCCESS);
	if (cmd == FALSE && (cmd = is_valid_cmd(comment)))
		return (SUCCESS);
	if (cmd == FALSE && ft_strchr(line, ' ') == NULL)
	{
		if (lemin->start_room == NULL || lemin->end_room == NULL)
		{
			lemin->error = ROOMS_ERR | TOO_FEW;
			return (FAILURE);
		}
		lemin->start_room->ants = lemin->total_ants;
		lemin->state = GET_LINKS;
		return (get_links(lemin, line));
	}
	else if (room_acquisition(lemin, line, &room) == FAILURE)
		return (FAILURE);
	else if (create_room_node(lemin, &room, cmd) == FAILURE)
		return (FAILURE);
	cmd = FALSE;
	return (SUCCESS);
}
