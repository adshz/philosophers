# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: szhong <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/30 14:21:37 by szhong            #+#    #+#              #
#    Updated: 2024/11/16 21:47:58 by szhong           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DF :=	\033[0m
R  :=	\033[1;31m
G  :=	\033[1;32m
Y  :=	\033[1;33m
B  :=	\033[1;34m
M  :=	\033[1;35m
C  :=	\033[1;36m
W  :=	\033[1;37m

NAME		:=	philo
SRC_DIR		:=	./src
OBJ_DIR		:=	./obj
SRCS		:=	\
				main.c \
				utils.c \
				parse.c \
				dinning.c \
				init.c \
				party_over.c \
				philo_actions.c \
				philo_monitor.c

OBJS		:= $(addprefix $(OBJ_DIR)/, $(patsubst %.c, %.o, $(SRCS)))
CC			:= cc
CFLAGS		:= -Wall -Werror -Wextra
INCLUDES	:=	-I ./inc -I ./libft/inc
MAKEFLAGS	:=	--no-print-directory
lDFLAGS		:=	-pthread

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(LDFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "${G}[Philosophers] Build Complete${DF}"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) $(LDFLAGS) -c $^ -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "${C}[Philosophers] Objects Removed${DF}"

fclean: clean
	@rm -rf $(NAME)
	@echo "${C}[Philosophers] $(NAME) Removed${DF}"
	@echo "${Y}====== Project Reset ======${DF}"

re: fclean all

.PHONY: all clean fclean re
