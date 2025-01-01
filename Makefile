# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/24 17:14:00 by idakhlao          #+#    #+#              #
#    Updated: 2025/01/01 13:35:20 by idakhlao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRCS = src/prout.c src/raycasting.c src/raycasting_utils.c src/calc.c src/movement.c src/texture.c src/handle_keys.c

OBJS_DIR = .objects
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -lXext -lX11

MINILIB = minilibx-linux/libmlx_Linux.a

CC = cc
RM = rm -f

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR) $(OBJS_DIR)/src

all: $(NAME)

$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): start $(OBJS)
	$(CC) $(CFLAGS) $(MLX_FLAGS) $(OBJS) -o $(NAME) $(MINILIB) -lm

start :
	make -C minilibx-linux

clean:
	$(RM) $(OBJS)
	find $(OBJS_DIR) -type f -name "*.o" -delete

fclean: clean
	$(RM) $(NAME)


ac: all clean
	make clean

re: fclean all

.PHONY: all clean fclean re
