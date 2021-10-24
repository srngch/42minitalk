# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/16 23:19:34 by sarchoi           #+#    #+#              #
#    Updated: 2021/10/24 14:49:17 by sarchoi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk
SERVER = server
CLIENT = client

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS = src/util.c
SRCS_SERVER = src/$(SERVER).c
SRCS_CLIENT = src/$(CLIENT).c
OBJS = $(SRCS:.c=.o)
OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

LIBFT = libft
LIBFT_FLAGS = -L $(LIBFT) -lft
INC_FLAGS = -I includes -I $(LIBFT)

green:=$(shell tput setaf 2)
reset:=$(shell tput sgr0)

all: $(LIBFT) $(SERVER) $(CLIENT)
	$(info $(green)<MAKE> all$(reset))

$(LIBFT):
	@make all --silent --directory=$(LIBFT)
	$(info $(green)<MAKE> Libft - make$(reset))

$(NAME): all

$(SERVER): $(OBJS_SERVER) $(OBJS)
	$(info $(green)<MAKE> SERVER$(reset))
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT_FLAGS)

$(CLIENT): $(OBJS_CLIENT) $(OBJS)
	$(info $(green)<MAKE> CLIENT$(reset))
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT_FLAGS)

%.o: %.c
	$(info $(green)******** $(@) $(<) ********$(reset))
	$(CC) $(CFLAGS) -c $< -o $@ $(INC_FLAGS)

clean:
	$(info $(green)******** clean ********$(reset))
	@make clean --directory=$(LIBFT)
	$(info $(green)*** Libft - clean ***$(reset))
	rm -f $(OBJS) $(OBJS_SERVER) $(OBJS_CLIENT)

fclean: clean
	$(info $(green)******** fclean ********$(reset))
	@make fclean --directory=$(LIBFT)
	$(info $(green)*** Libft - fclean $(reset))
	rm -f $(SERVER) $(CLIENT)

re: fclean all
	$(info $(red)******** re ********$(reset))

.PHONY: all clean fclean re $(LIBFT) $(SERVER) $(CLIENT)
