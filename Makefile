# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/31 14:55:54 by lbellmas          #+#    #+#              #
#    Updated: 2025/02/01 17:54:16 by lbellmas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME     = fdf
CHECKER	= checker
AR       = ar
ARFLAGS  = -rcs
CC       = cc
CFLAGS   = -Wall -Wextra -Werror -g
OFLAGS   = -MMD -MF $(@:.o=.d)
MLX_FLAGS = -L$(MLXDIR) -lmlx -L/usr/lib -lX11 -lXext -lm

SRCDIR	= src 
UTILSDIR	= utils 
OBJDIR	= obj 
DEPSDIR	= deps 
MLXDIR	= minilibx-linux
PRINTFDIR	= printf

HEAD	= header/ft_fdf.h
PRINTF	= $(PRINTFDIR)/libftprintf.a 
MLX = $(MLXDIR)libmlx.a
GETNEXT	= get_next_line_bonus.c get_next_line_utils_bonus.c
MAIN	= ft_fdf.c 
SRC	= 
UTILS	= 
OBJ	= $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
OUTILS	= $(addprefix $(OBJDIR)/, $(UTILS:.c=.o))

RED      = \033[0;31m
GREEN    = \033[0;32m
YELLOW   = \033[0;33m
BLUE     = \033[0;34m
PURPLE   = \033[0;35m
CYAN     = \033[0;36m
RESET    = \033[m

all: $(PRINTF) $(NAME) $(HEAD) Makefile

-include $(DEPS)

$(NAME): $(MAIN) $(OBJ) $(OUTILS) $(MLX)
	@printf "%-42b%b" "$(PURPLE)$<:" "$(BLUE)$(@F)$(RESET)\n"
	@$(CC) $(CFLAGS) $(MAIN) $(PRINTF) $(MLX) $(OBJ) $(OUTILS) $(GETNEXT) -o $(NAME)
	

$(OBJ): $(OBJDIR)/%.o : $(SRCDIR)/%.c Makefile | $(OBJDIR) $(DEPSDIR)
	@printf "%-42b%b" "$(PURPLE)$<:" "$(BLUE)$(@F)$(RESET)\n"
	@$(CC) $(CFLAGS) $(OFLAGS) -c $< -o $@
	@mv objs/*.d deps/

$(OUTILS): $(OBJDIR)/%.o : $(UTILSDIR)/%.c Makefile | $(OBJDIR) $(DEPSDIR)
	@printf "%-42b%b" "$(PURPLE)$<:" "$(BLUE)$(@F)$(RESET)\n"
	@$(CC) $(CFLAGS) $(OFLAGS) -c $< -o $@
	@mv $(OUTILS)/*.d deps/

$(MLX):
	@$(MAKE) --silent -C $(MLXDIR)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(DEPSDIR):
	@mkdir -p $(DEPS) 

$(PRINTF):
	@printf "%b" "$(BLUE)$(@F)$(RESET)\n"
	@$(MAKE) --silent -C $(PRINTFDIR)

clean:
	@printf "%b" "$(BLUE)Cleaning objects...$(RESET)\n"
	@rm -rf $(OBJDIR)
	@rm -rf $(DEPSDIR)
	@$(MAKE) -C $(PRINTFDIR) clean --silent
	@$(MAKE) -C $(MLXDIR) clean --silent

fclean:
	@printf "%b" "$(BLUE)Cleaning all files...$(RESET)\n"
	@rm -f $(NAME)
	@$(MAKE) -C $(MLXDIR) fclean --silent
	@$(MAKE) -C $(PRINTFDIR) fclean --silent

re: fclean all

.PHONY: all clean fclean re $(PRINTF)
