# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/31 14:55:54 by lbellmas          #+#    #+#              #
#    Updated: 2025/02/26 14:39:16 by lbellmas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME     = fdf
CHECKER	= checker
AR       = ar
ARFLAGS  = -rcs
CC       = cc
CFLAGS   = -Wall -Wextra -Werror -g
OFLAGS   = -MMD -MF $(@:.o=.d)
MLX_FLAGS = -g -ldl -lglfw -lm -pthread #-Ofast -fsanitize=address

SRCDIR	= src
UTILSDIR	= utils
OBJDIR	= obj
DEPSDIR	= deps
MLXDIR	= MLX42
PRINTFDIR	= printf
BUILD	= $(MLXDIR)/build
GETNEXTDIR	= get_next_line
OGETNEXTDIR	= get_next_line_objects
OUTILSDIR	= utils_objects

HEAD	= header/ft_fdf.h
PRINTF	= $(PRINTFDIR)/libftprintf.a
MLX = $(BUILD)/libmlx42.a
GETNEXT	= get_next_line_bonus.c get_next_line_utils_bonus.c
MAIN	= ft_fdf.c
SRC	= ft_draw.c ft_mapping.c ft_parsing_args.c ft_setup.c ft_algoritm.c
UTILS	= ft_utils.c ft_utils2.c
OBJ	= $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
OUTILS	= $(addprefix $(OUTILSDIR)/, $(UTILS:.c=.o))
OGETNEXT	= $(addprefix $(OGETNEXTDIR)/, $(GETNEXT:.c=.o))

RED      = \033[0;31m
GREEN    = \033[0;32m
YELLOW   = \033[0;33m
BLUE     = \033[0;34m
PURPLE   = \033[0;35m
CYAN     = \033[0;36m
RESET    = \033[m

all: $(PRINTF) $(NAME) $(HEAD) Makefile

-include $(DEPS)

$(NAME): $(MAIN) $(OBJ) $(OUTILS) $(MLX) $(OGETNEXT)
	@printf "%-42b%b" "$(PURPLE)$<:" "$(BLUE)$(@F)$(RESET)\n"
	@$(CC) $(CFLAGS) $(MAIN) $(OUTILS) $(OGETNEXT) $(OBJ) $(PRINTF) $(MLX) $(MLX_FLAGS) -o $(NAME)
	

$(OBJ): $(OBJDIR)/%.o : $(SRCDIR)/%.c Makefile | $(OBJDIR) $(DEPSDIR)
	@printf "%-42b%b" "$(PURPLE)$<:" "$(BLUE)$(@F)$(RESET)\n"
	@$(CC) $(CFLAGS) $(OFLAGS) -c $< -o $@
	@mv $(OBJDIR)/*.d deps/

$(OUTILS): $(OUTILSDIR)/%.o : $(UTILSDIR)/%.c Makefile | $(OUTILSDIR) $(DEPSDIR)
	@printf "%-42b%b" "$(PURPLE)$<:" "$(BLUE)$(@F)$(RESET)\n"
	@$(CC) $(CFLAGS) $(OFLAGS) -c $< -o $@
	@mv $(OUTILSDIR)/*.d deps/

$(OGETNEXT): $(OGETNEXTDIR)/%.o : $(GETNEXTDIR)/%.c Makefile | $(OGETNEXTDIR) $(DEPSDIR)
	@printf "%-42b%b" "$(PURPLE)$<:" "$(BLUE)$(@F)$(RESET)\n"
	@$(CC) $(CFLAGS) $(OFLAGS) -c $< -o $@
	@mv $(OGETNEXTDIR)/*.d deps/

$(MLX): $(BUILD)
	@$(MAKE) -C $(BUILD)

$(BUILD):
	@if [ ! -d "$(MLX_\DIR)/build" ]; then \
        cmake $(MLXDIR) -B $(MLXDIR)/build > /dev/null 2>&1 && \
        make -C $(MLXDIR)/build -j4 > /dev/null 2>&1; \
	fi

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OGETNEXTDIR):
	@mkdir -p $(OGETNEXTDIR)

$(OUTILSDIR):
	@mkdir -p $(OUTILSDIR)

$(DEPSDIR):
	@mkdir -p $(DEPSDIR) 

$(PRINTF):
	@printf "%b" "$(BLUE)$(@F)$(RESET)\n"
	@$(MAKE) --silent -C $(PRINTFDIR)

clean:
	@printf "%b" "$(BLUE)Cleaning objects...$(RESET)\n"
	@rm -rf $(OBJDIR)
	@rm -rf $(DEPSDIR)
	@rm -rf $(BUILD)
	@rm -rf $(OUTILSDIR)
	@rm -rf $(OGETNEXTDIR)
	@$(MAKE) -C $(PRINTFDIR) clean --silent
#	@$(MAKE) -C $(MLXDIR) fclean --silent

fclean:
	@printf "%b" "$(BLUE)Cleaning all files...$(RESET)\n"
	@rm -f $(NAME)
	@$(MAKE) clean --silent
	@$(MAKE) -C $(PRINTFDIR) fclean --silent

re: fclean all

.PHONY: all clean fclean re $(PRINTF)
