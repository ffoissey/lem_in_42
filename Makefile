# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/05 18:25:23 by ffoissey          #+#    #+#              #
#    Updated: 2019/07/26 10:43:51 by ffoissey         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
################################                ################################
################################ MAIN VARIABLES ################################
################################                ################################
################################################################################

# Name
NAME = lem-in
DEBUG_NAME = lem-in_db

# Compiler
CC = clang

# Lib
PATH_LIBFT = libft/
LIBFT = $(PATH_LIBFT)libft.a
DEBUG_LIBFT = $(PATH_LIBFT)db_libft.a

# Compiler Flags
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Werror

# Compiler Debug Flags
DBFLAGS += $(CFLAGS)
DBFLAGS += -fsanitize=address,undefined
DBFLAGS += -g3
DBFLAGS += -pedantic

# Debug Dir
DSYM += $(NAME).dSYM
DSYM += $(DBNAME).dSYM

################################################################################
################################                ################################
################################   PRINT VAR    ################################
################################                ################################
################################################################################

# Reset
NC = \033[0m

# Regular Colors
BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m

# One Line Output
ONELINE =\e[1A\r

################################################################################
#################################               ################################
#################################    INCLUDES   ################################
#################################               ################################
################################################################################

INCLUDES_LIBFT = libft/includes/
INCLUDES_LEMIN = includes/

I_INCLUDES += -I $(INCLUDES_LIBFT)
I_INCLUDES += -I $(INCLUDES_LEMIN)

################################################################################
#################################               ################################
#################################    HEADERS    ################################
#################################               ################################
################################################################################

vpath %.h $(INCLUDES_LIBFT)
vpath %.h $(INCLUDES_LEMIN)

# libft
HEADER += libft.h

# lemin
HEADER += lemin.h

################################################################################
#################################               ################################
#################################  PATH SOURCES ################################
#################################               ################################
################################################################################

PATH_SRCS += srcs
PATH_SRCS += srcs/parser
PATH_SRCS += srcs/get_best_ways
PATH_SRCS += srcs/complete_result

################################################################################
#################################               ################################
#################################    SOURCES    ################################
#################################               ################################
################################################################################

SRCS += lemin.c
SRCS += error.c
SRCS += exit_routine.c
SRCS += tools.c

# Complete Result
SRCS += ants_division.c
SRCS += ants_list_tool.c
SRCS += complete_result.c

# Get Best Ways
SRCS += set_distance.c
SRCS += graph_course.c
SRCS += save_way.c
SRCS += get_way_links.c
SRCS += ways_selection.c

# Parser
SRCS += parser.c
SRCS += get_ants.c
SRCS += get_rooms.c
SRCS += create_room_node.c
SRCS += get_links.c
SRCS += parser_tools.c

#Debug
SRCS += debug.c

################# ATTRIBUTION

vpath %.c $(PATH_SRCS)

################################################################################
#################################               ################################
#################################     OBJS      ################################
#################################               ################################
################################################################################

PATH_OBJS = objs/
OBJS = $(patsubst %.c, $(PATH_OBJS)%.o, $(SRCS))

DEBUG_PATH_OBJS = objs_debug/
DEBUG_OBJS = $(patsubst %.c, $(DEBUG_PATH_OBJS)%.o, $(SRCS))

################################################################################
#################################               ################################
#################################     RULES     ################################
#################################               ################################
################################################################################

#---------------------------------- STANDARD ----------------------------------#

all: $(PATH_OBJS) $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(I_INCLUDES) $(OBJS) $(LIBFT) -o $@
	printf "$(GREEN)$@ is ready.\n$(NC)"

$(OBJS): $(PATH_OBJS)%.o: %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) $(I_INCLUDES) -c $< -o $@
	printf "$(ONELINE)$(CYAN)Compiling $<"
	printf "                                                            \n$(NC)"

$(PATH_OBJS):
	mkdir $@

$(LIBFT): FORCE 
	$(MAKE) -C $(PATH_LIBFT)

#------------------------------------ DEBUG -----------------------------------#

debug: $(DEBUG_PATH_OBJS) $(DEBUG_NAME)

$(DEBUG_NAME): $(DEBUG_LIBFT) $(DEBUG_OBJS)
	$(CC) $(DBFLAGS) $(I_INCLUDES) $(DEBUG_OBJS) $(DEBUG_LIBFT) -o $@
	printf "$(GREEN)$@ is ready.\n$(NC)"

$(DEBUG_OBJS): $(DEBUG_PATH_OBJS)%.o: %.c $(HEADER) Makefile
	$(CC) $(DBFLAGS) $(I_INCLUDES) -c $< -o $@
	printf "$(ONELINE)$(PURPLE)Compiling for DEBUG $<"
	printf "                                                            \n$(NC)"

$(DEBUG_PATH_OBJS):
	mkdir $@

$(DEBUG_LIBFT): FORCE 
	$(MAKE) -C $(PATH_LIBFT) debug

#--------------------------------- Basic Rules --------------------------------#

clean:
	$(RM) $(OBJS)
	$(RM) $(DEBUG_OBJS)
	$(RM) -R $(PATH_OBJS)
	$(RM) -R $(DEBUG_PATH_OBJS)
	$(RM) -R $(DSYM)
	$(MAKE) -C $(PATH_LIBFT) clean
	printf "$(RED)Objs from lemin removed\n$(NC)"

fclean: clean
	$(RM) $(NAME)
	$(RM) $(DEBUG_NAME)
	$(MAKE) -C $(PATH_LIBFT) fclean
	printf "$(RED)$(NAME) removed\n$(NC)"

re: fclean all

FORCE:

#----------------------------------- Special ----------------------------------#

.PHONY: clean fclean re all debug
.SILENT:
