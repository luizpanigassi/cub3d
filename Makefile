# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/17 18:10:20 by luinasci          #+#    #+#              #
#    Updated: 2025/06/19 19:54:30 by luinasci         ###   ########.fr        #
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
	$(SRC_DIR)/error_handler.c \
	$(SRC_DIR)/flood_fill.c \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/map_validator.c \
	$(SRC_DIR)/parser_cub.c \
	$(SRC_DIR)/parsers.c \
	$(UTILS_DIR)/map_processing_utils.c \
	$(UTILS_DIR)/map_utils.c \
	$(UTILS_DIR)/utils.c \


# Convert to obj paths
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Default rule
all: $(OBJ_DIR) $(NAME)

# Linking
$(NAME): $(OBJS) $(MLX_LIB) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -L$(LIBFT_DIR) -lft -o $(NAME)

# Compile rule (handles nested folders too)
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

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
	$(RM) $(OBJS)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	@make -C $(LIBFT_DIR) fclean || true
	$(RM) $(MLX_LIB)

re: fclean all

.PHONY: all clean fclean re
