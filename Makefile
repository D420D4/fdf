# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plefevre <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/26 22:24:33 by plefevre          #+#    #+#              #
#    Updated: 2022/01/08 13:26:51 by plefevre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fdf
SRC		= main.c\
			bonus_data.c\
			parse.c\
			linemap.c\
			maths.c\
			draw_utils.c\
			basic_drawer.c\
			line.c\
			color.c\
			xpm.c\
			window_utils.c\
			camera.c\
			get_next_line/get_next_line.c\
			get_next_line/get_next_line_utils.c\
			ft3d.c\
			ft3d/ft3d_perspective.c\
			ft3d/ft3d_resize.c\
			ft3d/ft3d_rotate.c\
			ft3d/ft3d_set.c\
			ft3d/ft3d_setrot.c\
			ft3d/ft3d_translate.c

SRCBONUS = bonus.c\
			bonus_functions.c\
			bonus_data.c\
			bonus_key.c\
			simulateur.c\
			parse.c\
			linemap.c\
			maths.c\
			draw_utils.c\
			basic_drawer.c\
			line.c\
			color.c\
			stars.c\
			xpm.c\
			window_utils.c\
			camera.c\
			get_next_line/get_next_line.c\
			get_next_line/get_next_line_utils.c\
			ft3d.c\
			ft3d/ft3d_perspective.c\
			ft3d/ft3d_resize.c\
			ft3d/ft3d_rotate.c\
			ft3d/ft3d_set.c\
			ft3d/ft3d_setrot.c\
			ft3d/ft3d_translate.c

OBJ		= $(patsubst %.c, %.o, $(SRC))
OBJBONUS= $(patsubst %.c, %.o, $(SRCBONUS))
SRCDIR	= src/
OBJDIR	= obj/
LIBDIR	= includes/
INC		= /usr/include
INCLIB	= $(INC)/../lib

OBJS		=$(addprefix ${OBJDIR},${OBJ})
OBJSBONUS	=$(addprefix ${OBJDIR},${OBJBONUS})

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror -g
LFLAGS	= -Lminilibx -lmlx -L$(INCLIB) -lXext -lX11 -lm
IFLAGS	= -I $(INC) -I minilibx -I libft

all: $(NAME)

bonus: $(OBJSBONUS) libft
	$(CC) -o $(NAME) $(OBJSBONUS) ./libft/libft.a $(LFLAGS)

$(NAME): $(OBJS) libft
	$(CC) -o $(NAME) $(OBJS) ./libft/libft.a $(LFLAGS)

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) $(LFLAGS) $(IFLAGS) -c -I $(LIBDIR) -o $@ $<

libft:
	make bonus -C ./libft
	cp ./libft/libft.a $(NAME)

clean:
	/bin/rm -f $(OBJS)
	/bin/rm -f $(OBJSBONUS)
	make clean -C ./libft

fclean: clean
	/bin/rm -f $(NAME)
	make fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re libft bonus
