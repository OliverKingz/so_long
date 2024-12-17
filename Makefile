# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/25 20:01:56 by ozamora-          #+#    #+#              #
#    Updated: 2024/12/17 21:38:39 by ozamora-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# COMMANDS
MKDIR		:= mkdir -p
RM			:= rm -rf
PRINTF		:= printf "%b"
MAKE_LIB	:= make -sC
CP			:= cp -p

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

# **************************************************************************** #
# FILES
SRC_FILES := $(wildcard $(SRC_DIR)*.c)

# INCLUDE FILES
INC_FILES := so_long

# GENERAL FILES
SRCS    := $(SRC_FILES)
OBJS    := $(addprefix $(OBJ_DIR), $(notdir $(SRC_FILES:.c=.o)))
DEPS    := $(addprefix $(OBJ_DIR), $(notdir $(SRC_FILES:.c=.d)))
INCS    := $(addprefix $(INC_DIR), $(addsuffix .h, $(INC_FILES)))
INCS	+= $(LIBFT_INC_DIR)libft.h
INCS	+= $(LIBMLX_INC_DIR)

# **************************************************************************** #
# PROJECT
NAME  := so_long
LIBFT := $(LIBFT_DIR)libft.a
LIBMLX := $(LIBMLX_DIR)build/libmlx42.a

# **************************************************************************** #
# COMPILER
CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror
CFLAGS	+= -Wunreachable-code -Ofast
# CFLAGS	+= -g3 -fsanitize=address
# CFLAGS	+= -MMD -MP
IFLAGS	:= -I$(INC_DIR) -I$(LIBFT_INC_DIR) -I$(LIBMLX_INC_DIR)
LDFLAGS	:= $(LIBFT)
LDFLAGS	+= $(LIBMLX) -ldl -lglfw -pthread -lm

# **************************************************************************** #
# COLOURS

BOLD_RED   = \033[1;31m
BOLD_GREEN = \033[1;32m
BOLD_BLUE  = \033[1;34m

DEF_COLOR  = \033[0;39m
CLEAR_LINE = \033[2K

# **************************************************************************** #
# RULES
-include $(DEPS)

# Default rule to create the program
all: $(LIBFT) $(LIBMLX) $(NAME)

# Rule to compile object files from source files
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(MKDIR) $(dir $@)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

# Rule to create the program
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(IFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME) 
	@$(PRINTF) "$(CLEAR_LINE)$(BOLD_BLUE)\t[ozamora-'s so_long]:\t" \
		"$(DEF_COLOR)$(BOLD_GREEN)COMPILED$(DEF_COLOR)\n"

# Rule to make the library Libft
libft: $(LIBFT)
$(LIBFT):
	@$(MAKE_LIB) $(LIBFT_DIR)

# Rule to make the library Libmlx
libmlx: $(LIBMLX)
$(LIBMLX):
	@cmake $(LIBMLX_DIR) -B $(LIBMLX_DIR)/build > /dev/null && make -C $(LIBMLX_DIR)/build -j4 > /dev/null
	@$(PRINTF) "$(CLEAR_LINE)$(BOLD_BLUE)\t[Codam's LibMLX]:\t" \
		"$(DEF_COLOR)$(BOLD_GREEN)CREATED$(DEF_COLOR)\n"

# Rule to clean generated files
clean:
	@$(RM) $(OBJ_DIR)
	@make clean -sC $(LIBFT_DIR)
	@$(RM) $(LIBMLX_DIR)/build
	@$(PRINTF) "$(CLEAR_LINE)$(BOLD_BLUE)\t[ozamora-'s so_long]:\t" \
		"$(DEF_COLOR)$(BOLD_RED)OBJECTS CLEANED$(DEF_COLOR)\n"

# Rule to clean generated files and the executablle
fclean: 
	@make clean > /dev/null
	@make fclean -sC $(LIBFT_DIR)
	@$(PRINTF) "$(CLEAR_LINE)$(BOLD_BLUE)\t[ozamora-'s so_long]:\t" \
		"$(DEF_COLOR)$(BOLD_RED)FULLY CLEANED$(DEF_COLOR)\n"

# Rule to recompile from zero. 
re: fclean all

# Rule to check if the files pass norminette
norm:
	@norminette $(SRCS) $(INC_DIR)so_long.h $(LIBFT_INC_DIR)libft.h

show:
	@echo "Compilation command:\t"\
		"$(CC) $(CFLAGS) $(IFLAGS) -c $(SRC_DIR)so_long.c -o $(OBJ_DIR)so_long.o"
	@echo "Linking command:\t"\
		"$(CC) $(CFLAGS) $(IFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)"
	@echo "Cleaning command:\t $(RM) $(OBJ_DIR)" $(NAME)

info:
	@echo "NAME: $(NAME)"
	@echo "LIBFT: $(LIBFT)"
	@echo "LIBMLX: $(LIBMLX)"
	@echo "CC: $(CC)"
	@echo "CFLAGS: $(CFLAGS)"
	@echo "IFLAGS: $(IFLAGS)"
	@echo "LDFLAGS: $(LDFLAGS)"
	@echo "MKDIR: $(MKDIR)"
	@echo "RM: $(RM)"
	@echo "PRINTF: $(PRINTF)"
	@echo "MAKE_LIB: $(MAKE_LIB)"
	@echo "CP: $(CP)"
	@echo "SRC_DIR: $(SRC_DIR)"
	@echo "INC_DIR: $(INC_DIR)"
	@echo "OBJ_DIR: $(OBJ_DIR)"
	@echo "LIB_DIR: $(LIB_DIR)"
	@echo "LIBFT_DIR: $(LIBFT_DIR)"
	@echo "LIBFT_INC_DIR: $(LIBFT_INC_DIR)"
	@echo "LIBMLX_DIR: $(LIBMLX_DIR)"
	@echo "LIBMLX_INC_DIR: $(LIBMLX_INC_DIR)"
	@echo "SRC_FILES: $(SRC_FILES)"
	@echo "INC_FILES: $(INC_FILES)"
	@echo "SRCS: $(SRCS)"
	@echo "OBJS: $(OBJS)"
	@echo "DEPS: $(DEPS)"
	@echo "INCS: $(INCS)"

# valgrind: $(NAME)
# 	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

# Phony targets
.PHONY: all clean fclean re libmlx libft norm show info

# **************************************************************************** #