# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/25 20:01:56 by ozamora-          #+#    #+#              #
#    Updated: 2025/01/29 18:04:13 by ozamora-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# DIRECTORIES
SRC_DIR			:= src/
INC_DIR			:= inc/
OBJ_DIR			:= obj/

LIB_DIR			:= lib/
LIBMLX_DIR		:= $(LIB_DIR)MLX42/
LIBMLX_INC_DIR	:= $(LIBMLX_DIR)include/
LIBFT_DIR		:= $(LIB_DIR)libft/
LIBFT_INC_DIR	:= $(LIBFT_DIR)inc/

SRC_BONUS_DIR	:= src/bonus/
INC_BONUS_DIR	:= inc/bonus/
OBJ_BONUS_DIR	:= obj/bonus/

# **************************************************************************** #
# FILES
SRC_FILES		:= checks hook main map utils \
					display exit game init
INC_FILES		:= so_long

SRC_BONUS_FILES	:= checks_bonus hook_bonus main_bonus map_bonus utils_bonus \
					display_bonus exit_bonus game_bonus init_bonus
INC_BONUS_FILES		:= bonus/so_long_bonus

# GENERAL FILES
SRCS		:= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS		:= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
DEPS		:= $(addprefix $(OBJ_DIR), $(addsuffix .d, $(SRC_FILES)))
INCS		:= $(INC_DIR)so_long.h $(LIBFT_INC_DIR)libft.h $(LIBMLX_INC_DIR)MLX42.h

SRCS_BONUS	:= $(addprefix $(SRC_BONUS_DIR), $(addsuffix .c, $(SRC_BONUS_FILES)))
OBJS_BONUS	:= $(addprefix $(OBJ_BONUS_DIR), $(addsuffix .o, $(SRC_BONUS_FILES)))
DEPS_BONUS	:= $(addprefix $(OBJ_BONUS_DIR), $(addsuffix .d, $(SRC_BONUS_FILES)))
INCS_BONUS	:= $(INC_BONUS_DIR)so_long_bonus.h $(LIBFT_INC_DIR)libft.h $(LIBMLX_INC_DIR)MLX42.h

# **************************************************************************** #
# PROJECT
NAME	:= so_long
LIBFT	:= $(LIBFT_DIR)libft.a
LIBMLX	:= $(LIBMLX_DIR)build/libmlx42.a

# **************************************************************************** #
# COMPILER
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror
CFLAGS			+= -Wunreachable-code -Ofast
CFLAGS			+= -MMD -MP

IFLAGS			:= -I$(INC_DIR) -I$(LIBFT_INC_DIR) -I$(LIBMLX_INC_DIR)
IFLAGS_BONUS	:= -I$(INC_BONUS_DIR) -I$(LIBFT_INC_DIR) -I$(LIBMLX_INC_DIR)

LDFLAGS			:= $(LIBFT)
LDFLAGS			+= $(LIBMLX) -ldl -lglfw -pthread -lm

# **************************************************************************** #
# COLOURS

BOLD_RED	= \033[1;31m
BOLD_GREEN	= \033[1;32m
BOLD_BLUE	= \033[1;34m
BOLD_YELLOW	= \033[1;33m

DEF_COLOR	= \033[0;39m
CLEAR_LINE	= \033[2K

# **************************************************************************** #
# RULES
-include $(DEPS) $(DEPS_BONUS)

# Default rule to create the program
all: libmlx libft $(NAME)

# Rule to compile object files from source files
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@printf "%b" "$(CLEAR_LINE)$(BOLD_BLUE)[ozamora-'s so_long]:\t$(DEF_COLOR)$<\r"
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

# Rule to create the program
$(NAME): $(OBJS) $(LIBMLX) $(LIBFT)
	@$(CC) $(CFLAGS) $(IFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME) 
	@printf "%b" "$(CLEAR_LINE)$(BOLD_BLUE)[ozamora-'s so_long]:\t" \
		"$(DEF_COLOR)$(BOLD_GREEN)COMPILED$(DEF_COLOR)\n"

# Rule to make the library Libft
libft: $(LIBFT)
$(LIBFT):
	@$(MAKE) -sC $(LIBFT_DIR)

# Rule to make the library Libmlx
libmlx: $(LIBMLX)
$(LIBMLX):
	@cmake $(LIBMLX_DIR) -B $(LIBMLX_DIR)/build > /dev/null && make -C $(LIBMLX_DIR)/build -j4 > /dev/null
	@printf "%b" "$(CLEAR_LINE)$(BOLD_BLUE)[42-codam's LibMLX]:\t" \
		"$(DEF_COLOR)$(BOLD_GREEN)CREATED$(DEF_COLOR)\n"

# Rule to clean generated files
clean:
	@rm -rf $(OBJ_DIR) $(OBJ_BONUS_DIR)
	@$(MAKE) clean -sC $(LIBFT_DIR)
	@rm -rf $(LIBMLX_DIR)/build
	@printf "%b" "$(CLEAR_LINE)$(BOLD_BLUE)[ozamora-'s so_long]:\t" \
		"$(DEF_COLOR)$(BOLD_RED)OBJECTS CLEANED$(DEF_COLOR)\n"

# Rule to clean generated files and the executablle
fclean: 
	@$(MAKE) clean > /dev/null
	@$(MAKE) fclean -sC $(LIBFT_DIR)
	@rm -rf $(NAME) $(NAME)_bonus
	@printf "%b" "$(CLEAR_LINE)$(BOLD_BLUE)[ozamora-'s so_long]:\t" \
		"$(DEF_COLOR)$(BOLD_RED)FULLY CLEANED$(DEF_COLOR)\n"

# Rule to recompile from zero. 
re: fclean all

# Rule to compile the bonus portion
bonus: $(NAME)_bonus

$(OBJ_BONUS_DIR)%.o: $(SRC_BONUS_DIR)%.c
	@mkdir -p $(dir $@)
	@printf "%b" "$(CLEAR_LINE)$(BOLD_BLUE)[ozamora-'s so_long]:\t$(DEF_COLOR)$<\r"
	@$(CC) $(CFLAGS) $(IFLAGS_BONUS) -c $< -o $@

$(NAME)_bonus: $(OBJS_BONUS) $(LIBMLX) $(LIBFT)
	@$(CC) $(CFLAGS) $(IFLAGS_BONUS) $(OBJS_BONUS) $(LDFLAGS) -o $(NAME)_bonus
	@printf "%b" "$(CLEAR_LINE)$(BOLD_BLUE)[ozamora-'s bonus]:\t" \
		"$(DEF_COLOR)$(BOLD_GREEN)BONUS COMPILED$(DEF_COLOR)\n"

# Phony targets
.PHONY: all clean fclean re libmlx libft bonus

# **************************************************************************** #