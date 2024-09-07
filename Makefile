# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: szhong <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/30 14:21:37 by szhong            #+#    #+#              #
#    Updated: 2024/09/04 13:00:19 by szhong           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	philo
SRC_DIR		:=	./src
OBJ_DIR		:=	./obj
SRCS		:=	\
				main.c
OBJS		:= $(addprefix $(OBJ_DIR)/, $(patsubst %.c, %.o, $(SRCS)))
CC			:= cc
CFLAGS		:= -Wall -Werror -Wextra
INCLUDES	:=	-I ./inc -I ./libft/inc
MAKEFLAGS	:=	--no-print-directory
lDFLAGS		:=	-pthread

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(LDFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "[Philosophers] Build Complete"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) $(LDFLAGS) -c $^ -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "[Philosophers] Objects Removed"

fclean: clean
	@rm -rf $(NAME)
	@echo "[Philosophers] $(NAME) Removed"

re: fclean all

.PHONY: all clean fclean re
