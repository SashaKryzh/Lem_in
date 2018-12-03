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

NAME = libftprintf.a
FLAGS = -Wall -Wextra -Werror
CC = gcc
SRCS = ft_printf.c \
parser.c \
display_d.c \
display_c.c \
display_s.c \
display_o.c \
display_u.c \
display_x.c \
display_p.c \
display_f.c \
display_b.c \
get_value.c \
dtoa.c \
utils.c \
../ft_isdigit.c \
../ft_itoa.c \
../ft_strcpy.c \
../ft_strnew.c \
../ft_putstr.c \
../ft_strdup.c \
../ft_putchar.c \
../ft_itoa_base.c \
../ft_nbrlen.c \
../ft_abs.c \
../ft_strlen.c \
../ft_tolower.c \
../ft_strsub.c \
../ft_strncpy.c \
../ft_power.c \
../ft_strcat.c \
../ft_strrev.c \
../ft_strjoin.c \
../ft_putnstr.c \
../ft_print_bits.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -o $@ -c $< -I../includes

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re