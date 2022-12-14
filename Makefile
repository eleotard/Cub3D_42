# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/12 17:20:01 by eleotard          #+#    #+#              #
#    Updated: 2023/01/05 15:21:40 by eleotard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRCS_FILES =	main.c \
				utils.c \
				check_parsing.c \
				hook.c  \
				get_next_line.c \
				get_next_line_utils.c \
				error_destroy.c \
				moves.c \
				new_minimap.c \
				line.c \
				init_player.c \
				raycasting.c \
				rendering.c \

SRCS_DIR = srcs
OBJS_DIR = objs
OBJS_FILES = ${SRCS_FILES:%.c=%.o}
OBJS = ${addprefix ${OBJS_DIR}/, ${OBJS_FILES}}

INC_DIR = includes

CC = gcc

FLAGS = -I${INC_DIR}/ -Wall -Wextra -Werror -g3

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
