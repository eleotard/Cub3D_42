# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/12 17:20:01 by eleotard          #+#    #+#              #
#    Updated: 2023/01/21 23:51:37 by eleotard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRCS_FILES =	main.c \
				utils.c \
				hook.c  \
				get_next_line.c \
				get_next_line_utils.c \
				error_destroy.c \
				destroy_tabs.c \
				moves.c \
				watch.c \
				new_minimap.c \
				pixelize_minimap.c    \
				line.c \
				init_player.c \
				raycasting.c \
				rays_material.c \
				vertical_collision_raycasting.c \
				rendering.c \
				rendering_material.c \
				parse.c \
				parse_color_textures.c \
				parse_map.c \
				parse_map_utils.c \

SRCS_DIR = srcs
OBJS_DIR = objs
OBJS_FILES = ${SRCS_FILES:%.c=%.o}
OBJS = ${addprefix ${OBJS_DIR}/, ${OBJS_FILES}}

INC_DIR = includes

CC = gcc

FLAGS = -I${INC_DIR}/ -O3 -Wall -Wextra -Werror -g3 #-fsanitize=address

LIBFT = -Llibft -lft

MLX	= -Lminilibx-linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm  

RM = rm -rf

DEP = $(OBJS_FILES:%.o=%.d)

all: ${NAME}

-include ${DEP}
${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c | ${OBJS_DIR}
	${CC} ${FLAGS} -MMD -c $< -o $@

${OBJS_DIR}:
	mkdir -p $@

libft/libft.a:
	make -C libft --silent

minilibx-linux/libmlx_Linux.a:
	make -C minilibx-linux --silent

${NAME}: ${OBJS} libft/libft.a minilibx-linux/libmlx_Linux.a
	${CC} -o ${NAME} ${FLAGS} ${OBJS} ${LIBFT} ${MLX}

clean:
	make -C libft clean
	make -C minilibx-linux clean
	${RM} ${OBJS_FILES}
	${RM} ${OBJS_DIR}

fclean: clean
	make -C libft fclean
	${RM} ${NAME}

re: fclean all
	
.PHONY: all clean fclean re
