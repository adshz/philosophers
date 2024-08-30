# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: szhong <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/30 14:21:37 by szhong            #+#    #+#              #
#    Updated: 2024/08/30 19:06:17 by szhong           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	philo
SRC_DIR	:=	./src
OBJ_DIR	:=	./obj
SRCS	:=	\
			main.c
OBJS	:= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
CC		:= cc
CFLAGS	:= -Wall -Werror -Wextra
INCLUDES	:=	-I ./inc -I ./libft/inc
MAKEFLAGS	:=	--no-print-directory
LIBS		:=	-L./libft -lft
LIBFT		:=	./libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(OBJS) $(LIBS) -o $(NAME)

$(OBJS):$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@make $(MAKEFLAGS) -C ./libft all

clean:
	@make $(MAKEFLAGS) -C ./libft clean
	@rm -rf $(OBJ_DIR)
	@echo "[Philosophers] Objects Removed"

fclean: clean
	@make $(MAKEFLAGS) -C ./libft fclean
	@rm -rf $(NAME)
	@echo "[Philosophers] $(NAME) Removed"

re: fclean all

.PHONY: all clean fclean re



