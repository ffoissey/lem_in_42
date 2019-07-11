#include "lemin.h"

void		do_links(t_lemin *lemin, char *room_name1, char *room_name2)
{
	(void)lemin;
	(void)room_name1;
	(void)room_name2;
	// if: room_name1 or room_name2 is unknow: get error
	// else: connect room1 with room2
}

int8_t		get_links(t_lemin *lemin, char *line)
{
	char	*room_name1;
	char	*room_name2;
	char	*hyphen;

	if (is_comment(lemin, line) & COMMENT)
		return (SUCCESS);
	if (line == NULL || line == '\0' || (hyphen = ft_strchr(line, '-')) == NULL)
	{
		lemin->error = LINKS_ERR | BAD_FORMAT;
		return (FAILURE);
	}
	room_name1 = ft_strcdup(line, '-');
	room_name2 = ft_strdup(hyphen + 1);
	if (room_name1 == NULL || room_name2 == NULL)
		lemin->error = MALLOC_ERR;
	else
		do_links(lemin, room_name1, room_name2);
	ft_strdel(&room_name1);
	ft_strdel(&room_name2);
	return (SUCCESS);
}
