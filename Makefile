# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/25 20:01:56 by ozamora-          #+#    #+#              #
#    Updated: 2025/01/25 15:25:36 by ozamora-         ###   ########.fr        #
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
# -Wall: Enable all compiler's warning messages
# -Wextra: Enable additional warning messages not covered by -Wall
# -Werror: Treat all warnings as errors
# -Wunreachable-code: Warn about code that will never be executed
# -Ofast: Optimize code for maximum speed, disregarding strict standards compliance
# -MMD: Generate dependency files for make, excluding system headers
# -MP: Add phony targets for each dependency, preventing errors if files are deleted
# -g3: Generate debugging information
# -fsanitize=address: Enable AddressSanitizer, a memory error detector

IFLAGS			:= -I$(INC_DIR) -I$(LIBFT_INC_DIR) -I$(LIBMLX_INC_DIR)
IFLAGS_BONUS	:= -I$(INC_BONUS_DIR) -I$(LIBFT_INC_DIR) -I$(LIBMLX_INC_DIR)

LDFLAGS			:= $(LIBFT)
LDFLAGS			+= $(LIBMLX) -ldl -lglfw -pthread -lm
# -ldl: Link with the dynamic linking library
# -lglfw: Link with the GLFW library for OpenGL
# -pthread: Link with the POSIX threads library
# -lm: Link with the math library

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
-include $(DEPS)

# Default rule to create the program
all: $(LIBMLX) $(LIBFT) $(NAME)

# Rule to compile object files from source files
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

# Rule to create the program
$(NAME): $(OBJS)
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
	@rm -rf $(OBJ_DIR)
	@$(MAKE) clean -sC $(LIBFT_DIR)
	@rm -rf $(LIBMLX_DIR)/build
	@printf "%b" "$(CLEAR_LINE)$(BOLD_BLUE)[ozamora-'s so_long]:\t" \
		"$(DEF_COLOR)$(BOLD_RED)OBJECTS CLEANED$(DEF_COLOR)\n"

# Rule to clean generated files and the executablle
fclean: 
	@$(MAKE) clean > /dev/null
	@$(MAKE) fclean -sC $(LIBFT_DIR)
	@printf "%b" "$(CLEAR_LINE)$(BOLD_BLUE)[ozamora-'s so_long]:\t" \
		"$(DEF_COLOR)$(BOLD_RED)FULLY CLEANED$(DEF_COLOR)\n"

# Rule to recompile from zero. 
re: fclean all

# Rule to check if the files pass norminette
norm:
	@norminette $(SRCS) $(SRCS_BONUS) $(INC_DIR)so_long.h $(INC_BONUS_DIR)so_long_bonus.h

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

debug: CFLAGS += -g3 -fsanitize=address
debug: clean all
	@echo "\t\t\t$(BOLD_YELLOW)[DEBUG MODE]$(DEF_COLOR)"

valgrind: CFLAGS += -g3
valgrind: clean all
	@echo "\t\t\t$(BOLD_YELLOW)[DEBUG MODE WITH VALGRIND]$(DEF_COLOR)"
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) "assets/maps/example.ber"
# Valgrind leak types:
# "definitely lost": memory leak, fix these.
# "indirectly lost": memory leak in a pointer-based structure.
# "possibly lost": potential memory leak, check unusual pointer usage.
# "still reachable": program ok, memory not freed, common and often reasonable.
# "suppressed": leak error suppressed, can be ignored.

$(OBJ_BONUS_DIR)%.o: $(SRC_BONUS_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(IFLAGS_BONUS) -c $< -o $@

bonus: $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $(IFLAGS_BONUS) $(OBJS_BONUS) $(LDFLAGS) -o $(NAME) 
	@printf "%b" "$(CLEAR_LINE)$(BOLD_BLUE)[ozamora-'s so_long]:\t" \
		"$(DEF_COLOR)$(BOLD_GREEN)BONUS COMPILED$(DEF_COLOR)\n"

# Phony targets
.PHONY: all clean fclean re libmlx libft norm show info debug valgrind bonus

# **************************************************************************** #