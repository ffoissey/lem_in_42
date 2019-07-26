/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 10:27:52 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/26 10:27:56 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

uint8_t			is_comment(char *line)
{
	uint8_t	comment;

	if (line == NULL || *line != '#')
		return (NO_COMMENT);
	if (ft_strnequ(line, "##", 2) == FALSE)
		comment = COMMENT;
	else if (ft_strequ(line, "##start") == TRUE)
		comment = START_CMD;
	else if (ft_strequ(line, "##end") == TRUE)
		comment = END_CMD;
	else
		comment = UNKNOW_CMD | COMMENT;
	return (comment);
}

uint8_t			is_correct_numeric_format(char *line)
{
	if (line == NULL || *line == '\0')
		return (FALSE);
	else if (ft_str_is_numeric(line) == FALSE)
		return (FALSE);
	return (TRUE);
}
