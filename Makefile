#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/23 10:11:34 by okryzhan          #+#    #+#              #
#    Updated: 2018/10/23 10:11:36 by okryzhan         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = ants

FLAGS = -Wall -Wextra -Werror
CC = gcc $(FLAGS)

SRCS = main.c \
tests.c

LIBFT = -L ./libft -lft
LIB_HEAD = ./libft/includes

OBJ_DIR = ./objs
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: $(OBJ_DIR)
	@$(MAKE) -C ./libft all
	@$(MAKE) $(NAME)

$(OBJ_DIR):
	@mkdir ./objs

$(NAME): $(OBJS) ./libft/libft.a
	@$(CC) -o $(NAME) $(SRCS) $(LIBFT) -I $(LIB_HEAD)

$(OBJ_DIR)/%.o: %.c $(LIB_HEAD)/*.h ./*.h
	$(CC) -o $@ -c $< -I $(LIB_HEAD) 

clean:
	@rm -rf $(OBJ_DIR)

cleanlib:
	@make clean -C ./libft

fclean: clean
	@rm -f $(NAME)

fcleanlib:
	@make fclean -C ./libft

re: relib fclean all

relib:
	@make re -C ./libft

.PHONY: all clean fclean re