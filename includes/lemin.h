/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 17:19:59 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/10 19:01:11 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "libft.h"
# include <stdint.h>
# include <limits.h>

# define NO_COMMENT			0x00
# define COMMENT			0x01
# define START_CMD			0x10
# define END_CMD			0x20
# define UNKNOW_CMD			0x40

/*
**** Generic error
*/

# define	NO_ERR			0x00000000
# define	BAD_FORMAT		0x00000001

/*
**** Ants error
*/

# define	NO_ANT			0x00000010
# define	TOO_MANY_ANTS	0x00000020

/*
**** Type of errors
*/

# define	ANTS_ERR		0x00010000
# define	ROOMS_ERR		0x00020000
# define	LINKS_ERR		0x00040000
# define	PRE_PROCESS_ERR	0x00080000
# define	PROCESS_ERR		0x00100000

/*
**** Critical errors
*/

# define	READ_ERR		0x10000000
# define	MALLOC_ERR		0x20000000
# define	WRITE_ERR		0x40000000

enum				e_state
{
	GET_ANTS,
	GET_ROOMS,
	GET_LINKS,
	PRINT,
	ERROR
};

typedef struct		s_coord
{
	size_t			x;
	size_t			y;
}					t_coord;

typedef struct		s_room
{
	t_list			*ways;
	t_coord			coord;
	size_t			nb_ways;
	size_t			distance_to_end;
	size_t			ants;
	size_t			waiting;
	uint8_t			is_free;
}					t_room;

typedef struct		s_lemin
{
	t_list			*start_room;
	t_list			*end_room;
	size_t			total_ants;
	size_t			turn;
	uint32_t		error;
	enum e_state	state;
}					t_lemin;			

typedef int8_t	(*t_parsing)(t_lemin *, char *);

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

uint8_t		is_comment(char *line);

/*
**** Error Management
*/

uint8_t	is_major_error(uint32_t error);
void	print_error(uint32_t error);

#endif
