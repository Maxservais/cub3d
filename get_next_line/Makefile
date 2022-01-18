# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mservais <mservais@student.s19.be >        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/14 11:19:20 by mservais          #+#    #+#              #
#    Updated: 2021/09/14 11:21:49 by mservais         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_FILES		= get_next_line.c \
				get_next_line_utils.c

OBJ_FILES		= $(SRC_FILES:.c=.o)

NAME			= libgnl.a

CC				= gcc

CFLAGS			= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ_FILES)
	ar -rcs $@ $^

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re