# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/17 18:10:20 by luinasci          #+#    #+#              #
#    Updated: 2025/06/17 18:31:02 by luinasci         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3d
LIB			=	ar rcs
RM			=	rm -f
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror

SRCS		=	parse_config.c \
				parse_file.c \
				build_map.c

UTILS		=	utils.c \

OBJS		=	$(SRCS:.c=.o) $(UTILS:.c=.o)

MLX_DIR		= mlx
MLX_LIB		= $(MLX_DIR)/libmlx.a
MLX_FLAGS	= -L$(MLX_DIR) -Imlx -Ilibft -Lmlx -lmlx -lXext -lX11 -lm
INCLUDES	= -I$(MLX_DIR) -I/usr/include -I. -Ilibft

LIBFT_DIR	= libft
LIBFT_LIB	= $(LIBFT_DIR)/libft.a

all:		$(NAME)

$(NAME):	$(OBJS) $(MLX_LIB) $(LIBFT_LIB)
			$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -L$(LIBFT_DIR) -lft -o $(NAME)

$(LIBFT_LIB):
			@make -C $(LIBFT_DIR)

$(MLX_LIB):
			@make -sC $(MLX_DIR) > /dev/null 2>/dev/null

%.o: %.c $(INCLUDES)
			$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
			$(RM) $(OBJS)
			@make -C $(MLX_DIR) clean
			@make -C $(LIBFT_DIR) clean

fclean:		clean
			$(RM) $(NAME)
			@make -C $(MLX_DIR) fclean || true
			@make -C $(LIBFT_DIR) fclean || true
			$(RM) $(MLX_LIB)
			$(RM) $(MLX_DIR)/libmlx_*.a

re:			fclean all

.PHONY:		all clean fclean re
