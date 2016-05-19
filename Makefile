# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/27 14:53:18 by tdieumeg          #+#    #+#              #
#    Updated: 2014/03/15 16:27:16 by tdieumeg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# binaries
CC		= /usr/bin/clang
RM		= /bin/rm
MAKE	= /usr/bin/make
MKDIR	= /bin/mkdir

# app name
NAME	= minishell

# dir
ROOT	= $(shell pwd)
OBJDIR	= $(ROOT)/objs
SRCDIR	= $(ROOT)/srcs
INCDIR	= $(ROOT)/includes
LIBDIR	= $(ROOT)/libft
LFTINC	= $(LIBDIR)/includes

# compil flags
CFLAGS	= -I $(INCDIR) -I $(LFTINC) -Wall -Wextra -Werror -g
LIBS	= -L $(LIBDIR) -lft

SRC		= main.c \
		  environment.c \
		  arr_of_arr.c \
		  env_list.c \
		  env_list_copy.c \
		  commands.c \
		  lexer.c \
		  builtin.c \
		  builtin_env.c \
		  builtin_env_parse.c \
		  builtin_cd.c \
		  builtin_cd_test.c \
		  display.c \
		  utility.c \
		  execution.c \
		  signals.c \
		  sh_error.c 

# obj
OBJS	= $(patsubst %.c, $(OBJDIR)/%.o, $(SRC))

.PHONY: all clean fclean re

all: $(OBJDIR) $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBDIR)
	@echo "Compiling minishell..."
	@$(CC) $(OBJS) -o $@ $(LIBS) $(CFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $< -o $@ -c $(CFLAGS)

$(OBJDIR):
	@$(MKDIR) $@

clean:
	$(RM) -rf $(OBJDIR)

fclean: clean
	$(RM) -f $(NAME)

lib.fclean:
	$(MAKE) -C $(LIBDIR) fclean

re: fclean all
