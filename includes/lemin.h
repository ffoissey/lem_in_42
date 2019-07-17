/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 17:19:59 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/16 20:17:01 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "libft.h"
# include <stdint.h>
# include <limits.h>

/*
***** Comments and Commands
*/

# define NO_COMMENT			0x00
# define COMMENT			0x01
# define START_CMD			0x10
# define END_CMD			0x20
# define UNKNOW_CMD			0x40

/*
**** Node Mark
*/

# define UNMARK				0
# define MARK				1
# define DEAD				2

/*
**** Distance
*/

# define D_START			0
# define D_END				1

/*
*****************
***** ERROR *****
*****************
*/

/*
**** Generic error
*/

# define NO_ERR				0x00000000
# define BAD_FORMAT			0x00000001

/*
**** Ants error
*/

# define NO_ANT				0x00000010
# define TOO_MANY_ANTS		0x00000020

/*
**** Rooms error
*/

# define INVALID_COORD		0x00000040
# define BAD_START_LETTER	0x00000080
# define MISS_ROOMS			0x00000100
# define SAME_NAME			0x00000200
# define SAME_COORD			0x00000400
# define START_ROOM			0x00000800
# define END_ROOM			0x00001000
# define TOO_FEW			0x00002000
# define UNKNOW_ROOM		0x00004000

/*
**** Type of errors
*/

# define ANTS_ERR			0x00010000
# define ROOMS_ERR			0x00020000
# define LINKS_ERR			0x00040000
# define PRE_PROCESS_ERR	0x00100000
# define PROCESS_ERR		0x00200000

/*
**** Critical errors
*/

# define READ_ERR			0x10000000
# define MALLOC_ERR			0x20000000
# define WRITE_ERR			0x40000000
# define FILE_ERR			0x80000000

enum				e_state
{
	GET_ANTS,
	GET_ROOMS,
	GET_LINKS
};

typedef struct		s_coord
{
	size_t			x;
	size_t			y;
}					t_coord;

typedef struct		s_way
{
	t_list			*list;
	t_list			*link;
	size_t			size;
	size_t			nb_links;
	uint8_t			id;
}					t_way;

typedef struct		s_ant
{
	t_list			*position;
	size_t			id;
}					t_ant;

typedef struct		s_room
{
	t_list			*links;
	struct	s_room	*current_link;
	char			*name;
	size_t			d_start;
	size_t			d_end;
	size_t			nb_links;
	size_t			ants;
	t_coord			coord;
	uint8_t			mark;
}					t_room;

typedef struct		s_lemin
{
	t_list			*main_list_room;
	t_room			*start_room;
	t_room			*end_room;
	t_list			*possible_way_list;
	t_list			*way_list;
	size_t			nb_ways;
	size_t			nb_possible_ways;
	size_t			nb_max_ways;
	size_t			total_ants;
	enum e_state	state;
	uint32_t		error;
}					t_lemin;			

typedef int8_t	(*t_parsing)(t_lemin *, char *);

/*
**********************
**** --- MAIN --- ****
**********************
*/

void	get_way_links(t_lemin *lemin);
int8_t	save_the_way(t_lemin *lemin);
int8_t	graph_course(t_lemin *lemin);
void	ways_selection(t_lemin *lemin);
int8_t	set_distance_from_start(t_room *room, t_lemin *lemin, size_t distance);
int8_t	set_distance_from_end(t_room *room, t_lemin *lemin, size_t distance);

/*
**** Exit / Free
*/

void	exit_routine(t_lemin *lemin);

/*
**** Error Management
*/

uint8_t		is_major_error(uint32_t error);
void		print_error(uint32_t error);

/*
**** Tools
*/

void		delete_duplicate_ways(t_lemin *lemin);
void		mark_way(t_list *lst, uint8_t mark);
uint8_t		is_way_free(t_list *lst);
size_t		get_nb_max_ways(t_lemin *lemin);

/*
**********************
******* PARSER *******
**********************
*/

int8_t		parser(t_lemin *lemin);

/*
**** State Machine
*/

int8_t		get_ants(t_lemin *lemin, char *line);
int8_t		get_rooms(t_lemin *lemin, char *line);
int8_t		get_links(t_lemin *lemin, char *line);

/*
**** Parser Tools
*/

uint8_t		is_comment(t_lemin *lemin, char *line);
uint8_t		is_correct_numeric_format(char *line);


/*
**** Graph Tools
*/

int8_t		create_room_node(t_lemin *lemin, t_room *room, uint8_t cmd);

/*
**** Debug
*/

void	print_graph(t_lemin *lemin);
void	print_list_ways(t_lemin *lemin);

#endif
