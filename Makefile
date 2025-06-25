# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/17 18:10:20 by luinasci          #+#    #+#              #
#    Updated: 2025/06/25 17:35:26 by luinasci         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3d
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror

SRC_DIR		=	src
UTILS_DIR	=	utils
OBJ_DIR		=	obj
MLX_DIR		=	mlx
LIBFT_DIR	=	libft

MLX_LIB		=	$(MLX_DIR)/libmlx.a
LIBFT_LIB	=	$(LIBFT_DIR)/libft.a

MLX_FLAGS	=	-L$(MLX_DIR) -Imlx -Lmlx -lmlx -lXext -lX11 -lm
INCLUDES	=	-Iincludes -I$(MLX_DIR) -I/usr/include -I$(LIBFT_DIR)

# List all .c files with their paths
SRCS = \
	$(SRC_DIR)/controller.c \
	$(SRC_DIR)/error_handler.c \
	$(SRC_DIR)/events.c \
	$(SRC_DIR)/flood_fill.c \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/map_validator.c \
	$(SRC_DIR)/movement.c \
	$(SRC_DIR)/parser_cub.c \
	$(SRC_DIR)/parsers.c \
	$(SRC_DIR)/mlx_window.c \
	$(SRC_DIR)/init.c \
	$(SRC_DIR)/ray_cast.c \
	$(SRC_DIR)/drawing_utils.c \
	$(SRC_DIR)/texture_loader.c \
	$(SRC_DIR)/door.c \
	$(UTILS_DIR)/map_processing_utils.c \
	$(UTILS_DIR)/map_utils.c \
	$(UTILS_DIR)/utils.c \

# Convert to obj paths
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Colors (optional, remove if you want plain output)
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
RED		= \033[1;31m
RESET	= \033[0m

# Default rule
all: $(OBJ_DIR) $(NAME)

# Linking
$(NAME): $(OBJS) $(MLX_LIB) $(LIBFT_LIB)
	@echo "$(YELLOW)🔗 Linking:$(RESET) $@"
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -L$(LIBFT_DIR) -lft -o $(NAME)
	@echo "$(GREEN)✅ Build complete!$(RESET)"

# Compile rule (handles nested folders too)
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)🛠️  Compiling:$(RESET) $<"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Create obj folder
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# External libs
$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

$(MLX_LIB):
	@make -sC $(MLX_DIR) > /dev/null 2>/dev/null || true

# Cleanup
clean:
	@echo "$(RED)🧹 Cleaning objects$(RESET)"
	@find $(OBJ_DIR) -type f -name '*.o' -delete
	@$(RM) $(TERMINAL_TEST_OBJS) $(TERMINAL_EXTRA_OBJS) $(TERMINAL_TEST_NAME)
	@$(MAKE) -C $(LIBFT_DIR) clean --silent

fclean: clean
	@echo "$(RED)🔥 Full clean$(RESET)"
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --silent
	@$(RM) $(MLX_LIB)

re: fclean all

clone:
	git clone https://github.com/42paris/minilibx-linux.git mlx

.PHONY: all clean fclean re

#terminal tester

# Terminal Tester
TERMINAL_TEST_NAME = terminal_test
TERMINAL_TEST_SRC = $(SRC_DIR)/terminal_test.c
TERMINAL_TEST_OBJS = $(TERMINAL_TEST_SRC:%.c=$(OBJ_DIR)/%.o)

# Add all required sources used by the test
TERMINAL_EXTRA_SRCS = \
	$(SRC_DIR)/controller.c \
	$(SRC_DIR)/movement.c \
	$(SRC_DIR)/parser_cub.c \
	$(SRC_DIR)/error_handler.c \
	$(SRC_DIR)/flood_fill.c \
	$(SRC_DIR)/map_validator.c \
	$(UTILS_DIR)/utils.c \
	$(UTILS_DIR)/map_processing_utils.c \
	$(UTILS_DIR)/map_utils.c \
	$(SRC_DIR)/parsers.c \
	$(SRC_DIR)/events.c \


TERMINAL_EXTRA_OBJS = $(TERMINAL_EXTRA_SRCS:%.c=$(OBJ_DIR)/%.o)

terminal_test: $(TERMINAL_TEST_OBJS) $(TERMINAL_EXTRA_OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(INCLUDES) $(TERMINAL_TEST_OBJS) $(TERMINAL_EXTRA_OBJS) $(LIBFT_LIB) -lm -o $(TERMINAL_TEST_NAME)

# Optional cleanup rule for test binary
clean_test:
	$(RM) $(TERMINAL_TEST_OBJS) $(TERMINAL_EXTRA_OBJS) $(TERMINAL_TEST_NAME)


