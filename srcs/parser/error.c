#include "lemin.h"
#include <errno.h>
#include <stdio.h>

uint8_t			is_major_error(uint32_t error)
{
	if ((unsigned char)(error >> 24))
		return (TRUE);
	else if (error & ANTS_ERR)
		return (TRUE);
	else if (error & ROOMS_ERR)
		return (TRUE);
	return (FALSE);
}

static void		ants_error(uint32_t error)
{
	ft_putstr_fd("ants: ", 2);
	if (error & NO_ANT)
		ft_putendl_fd("There can not be 0 ant", 2);
	else if (error & TOO_MANY_ANTS)
		ft_putendl_fd("Too many ants", 2);
	else if (error & BAD_FORMAT)
		ft_putendl_fd("Bad format", 2);
	else
		ft_putendl_fd("Undefined error", 2);

}

static void		rooms_error(uint32_t error)
{
	ft_putstr_fd("room: ", 2);
	if (error & BAD_START_LETTER)
		ft_putendl_fd("The name of a room can't start with the 'L' letter", 2);
	else if (error & INVALID_COORD)
		ft_putendl_fd("Invalid coordinate", 2);
	else if (error & MISS_ROOMS)
		ft_putendl_fd("At least two rooms are required", 2);
	else if (error & SAME_NAME)
		ft_putendl_fd("Two rooms have the same name", 2);
	else if (error & SAME_COORD)
		ft_putendl_fd("Two rooms have the same coordinates", 2);
	else if (error & TOO_FEW)
		ft_putendl_fd("Start or end is not defined", 2);
	else if (error & BAD_FORMAT)
		ft_putendl_fd("Bad format", 2);
	else
		ft_putendl_fd("Undefined error", 2);
}

static void		links_error(uint32_t error)
{
	ft_putstr_fd("links: ", 2);
	if (error & BAD_FORMAT)
		ft_putendl_fd("Bad format", 2);

}

void			print_error(uint32_t error)
{
	ft_putstr_fd("Error: ", 2);
	if (error & READ_ERR)
		perror("read");
	else if (error & MALLOC_ERR)
		perror("malloc");
	else if (error & WRITE_ERR)
		perror("write");
	else if (error & ANTS_ERR)
		ants_error(error);
	else if (error & ROOMS_ERR)
		rooms_error(error);
	else if (error & LINKS_ERR)
		links_error(error);
}
