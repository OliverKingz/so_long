# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/25 20:01:56 by ozamora-          #+#    #+#              #
#    Updated: 2025/02/07 13:33:00 by ozamora-         ###   ########.fr        #
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

# DEBUG MODE
BUILD_MODE_FILE := .build_mode

ifeq ($(DEBUG),1)
	CFLAGS += -g3 -fsanitize=address
	LDFLAGS += -fsanitize=address
endif

# VALGRIND MODE
ifeq ($(VALGRIND),1)
	CFLAGS += -g3
endif

# **************************************************************************** #
# COLOURS

BR	= \033[1;31m
BG	= \033[1;32m
BB	= \033[1;34m
BY	= \033[1;33m

NC	= \033[0;39m
CL	= \033[2K

# **************************************************************************** #
# RULES

# Default rule to create the program
all: libmlx libft $(NAME)

# Rule to create the program
$(NAME): $(OBJS) $(LIBMLX) $(LIBFT)
	@$(CC) $(CFLAGS) $(IFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME) 
	@printf "%b" "$(CL) -> $(BB)[so_long]:\t\t$(BG)Compilation success\t✅$(NC)\n"

# Rule to compile object files from source files
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@printf "%b" "$(CL) -> $(BB)[so_long]:\t\t$(NC)$<\r"
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

# Rule to create the program
$(NAME): $(OBJS) $(LIBMLX) $(LIBFT)
	@$(CC) $(CFLAGS) $(IFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME) 
	@printf "%b" "$(CLEAR_LINE)$(BOLD_BLUE)[ozamora-'s so_long]:\t" \
		"$(DEF_COLOR)$(BOLD_GREEN)COMPILED$(DEF_COLOR)\n"
	@echo " ▗▄▄▖ ▗▄▖   ▗▖    ▗▄▖ ▗▖  ▗▖ ▗▄▄▖";
	@echo "▐▌   ▐▌ ▐▌  ▐▌   ▐▌ ▐▌▐▛▚▖▐▌▐▌   ";
	@echo " ▝▀▚▖▐▌ ▐▌  ▐▌   ▐▌ ▐▌▐▌ ▝▜▌▐▌▝▜▌";
	@echo "▗▄▄▞▘▝▚▄▞▘  ▐▙▄▄▖▝▚▄▞▘▐▌  ▐▌▝▚▄▞▘ by ozamora-";
	@echo "                                   $(DEF_COLOR)";

# Rule to make the library Libft
libft: $(LIBFT)
$(LIBFT):
	@$(MAKE) -sC $(LIBFT_DIR)

# Rule to make the library Libmlx
libmlx: $(LIBMLX)
$(LIBMLX):
	-@cmake $(LIBMLX_DIR) -B $(LIBMLX_DIR)/build > /dev/null && make -C $(LIBMLX_DIR)/build -j4 > /dev/null
	@printf "%b" "$(CL) -> $(BB)[LibMLX]:\t\t$(NC)$(BG)Compilation success\t✅$(NC)\n"

# Rule to clean generated files
clean:
	@rm -rf $(OBJ_DIR) $(OBJ_BONUS_DIR)
	@$(MAKE) clean -sC $(LIBFT_DIR)
	@rm -rf $(LIBMLX_DIR)/build
	@printf "%b" "$(CL) -> $(BB)[so_long]:\t\t$(BG)Object files cleaned\t❎$(NC)\n"
	@rm -f $(BUILD_MODE_FILE)

# Rule to clean generated files and the executablle
fclean: 
	@$(MAKE) clean > /dev/null
	@$(MAKE) fclean -sC $(LIBFT_DIR)
	@rm -rf $(NAME) $(NAME)_bonus
	@printf "%b" "$(CL) -> $(BB)[so_long]:\t\t$(BG)Executable cleaned\t❎$(NC)\n"

# Rule to recompile from zero. 
re: fclean all

# **************************************************************************** #
# BONUS RULES
# Rule to compile the bonus portion
bonus: $(NAME)_bonus

$(OBJ_BONUS_DIR)%.o: $(SRC_BONUS_DIR)%.c
	@mkdir -p $(dir $@)
	@printf "%b" "$(CL)$(BB)[so_long]:\t\t$(NC)$<\r"
	@$(CC) $(CFLAGS) $(IFLAGS_BONUS) -c $< -o $@

$(NAME)_bonus: $(OBJS_BONUS) $(LIBMLX) $(LIBFT)
	@$(CC) $(CFLAGS) $(IFLAGS_BONUS) $(OBJS_BONUS) $(LDFLAGS) -o $(NAME)_bonus
	@printf "%b" "$(CL)$(BB)[bonus]:\t\t$(NC)$(BG)Compilation success\t✅$(NC)\n"

# **************************************************************************** #
# NORM AND DEBUG RULES

# Rule to check if the files pass norminette
norm:
	@norminette $(SRCS) $(SRCS_BONUS) $(INC_DIR)so_long.h $(INC_BONUS_DIR)so_long_bonus.h

debug: 
	@if [ ! -f $(BUILD_MODE_FILE) ] || ! grep -q "DEBUG=1" $(BUILD_MODE_FILE); then \
		$(MAKE) clean -s; \
	fi
	@echo "DEBUG=1" > $(BUILD_MODE_FILE)
	@$(MAKE) -s DEBUG=1
	@echo " -> $(BB)[Debug]:\t\t$(BG)Debug mode enabled\t🟦$(NC)"
	-@if [ ! -z "$(ARGS)" ]; then ./$(NAME) $(ARGS); fi

valgrind:
	@if [ ! -f $(BUILD_MODE_FILE) ] || ! grep -q "VALGRIND=1" $(BUILD_MODE_FILE); then \
		$(MAKE) clean -s; \
	fi
	@echo "VALGRIND=1" > $(BUILD_MODE_FILE)
	@$(MAKE) -s VALGRIND=1
	@echo " -> $(BB)[Valgrind]:\t\t$(BG)Valgrind mode enabled\t🟦$(NC)"
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) $(ARGS)

# Valgrind flags
# --leak-check=full: Enables detailed memory leak checking.
# --show-leak-kinds=all: Shows all possible leak types (definitely lost, indirectly lost, possibly lost, still reachable, suppressed).
# --track-origins=yes: Tracks the origin of uninitialized values.

# Valgrind leak types:
# "definitely lost": memory leak, fix these.
# "indirectly lost": memory leak in a pointer-based structure.
# "possibly lost": potential memory leak, check unusual pointer usage.
# "still reachable": program ok, memory not freed, common and often reasonable.
# "suppressed": leak error suppressed, can be ignored.

# **************************************************************************** #
# ADDITIONAL RULES
show:
	@echo "Compilation command:\t"\
		"$(CC) $(CFLAGS) $(IFLAGS) -c $(SRC_DIR)so_long.c -o $(OBJ_DIR)so_long.o"
	@echo "Linking command:\t"\
		"$(CC) $(CFLAGS) $(IFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)"
	@echo "Cleaning command:\t rm -rf $(OBJ_DIR)" $(NAME)

info:
	@echo "\nozamora's so_long:"
	@echo "NAME: $(NAME)"
	@echo "LIBFT: $(LIBFT)"
	@echo "LIBMLX: $(LIBMLX)"
	@echo "\nCompiler:"
	@echo "CC: $(CC)"
	@echo "CFLAGS: $(CFLAGS)"
	@echo "IFLAGS: $(IFLAGS)"
	@echo "LDFLAGS: $(LDFLAGS)"
	@echo "\nDirectories:"
	@echo "SRC_DIR: $(SRC_DIR)"
	@echo "INC_DIR: $(INC_DIR)"
	@echo "OBJ_DIR: $(OBJ_DIR)"
	@echo "LIB_DIR: $(LIB_DIR)"
	@echo "LIBFT_DIR: $(LIBFT_DIR)"
	@echo "LIBFT_INC_DIR: $(LIBFT_INC_DIR)"
	@echo "LIBMLX_DIR: $(LIBMLX_DIR)"
	@echo "LIBMLX_INC_DIR: $(LIBMLX_INC_DIR)"
	@echo "\nFiles:"
	@echo "SRC_FILES: $(SRC_FILES)"
	@echo "INC_FILES: $(INC_FILES)"
	@echo "SRCS: $(SRCS)"
	@echo "OBJS: $(OBJS)"
	@echo "DEPS: $(DEPS)"
	@echo "INCS: $(INCS)"
	@echo "\nBonus:"
	@echo "SRC_BONUS_DIR: $(SRC_BONUS_DIR)"
	@echo "INC_BONUS_DIR: $(INC_BONUS_DIR)"
	@echo "OBJ_BONUS_DIR: $(OBJ_BONUS_DIR)"
	@echo "SRC_BONUS_FILES: $(SRC_BONUS_FILES)"
	@echo "INC_BONUS_FILES: $(INC_BONUS_FILES)"
	@echo "SRCS_BONUS: $(SRCS_BONUS)"
	@echo "OBJS_BONUS: $(OBJS_BONUS)"
	@echo "DEPS_BONUS: $(DEPS_BONUS)"
	@echo "INCS_BONUS: $(INCS_BONUS)"
	@echo "IFLAGS_BONUS: $(IFLAGS_BONUS)"

-include $(DEPS) $(DEPS_BONUS)
.PHONY: all clean fclean re libmlx libft norm show info debug valgrind bonus
.DEFAULT_GOAL := all

# **************************************************************************** #