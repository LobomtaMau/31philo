# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbaptist <mbaptist@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/23 14:07:10 by mbaptist          #+#    #+#              #
#    Updated: 2023/10/23 17:19:59 by mbaptist         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ./philo 1 800 200 200 
# ./philo 5 800 200 200 
# ./philo 5 800 200 200 7
# ./philo 4 410 200 200		/2
# ./philo 4 310 200 100		/2

NAME = philo

SRC =	philo.c\
		philo_setup.c\
		utils.c\

SRC_DIR = src
OBJ_DIR = obj

OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -fr

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lpthread

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean reNAME = philo