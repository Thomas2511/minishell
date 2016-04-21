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
CFLAGS	= -I $(INCDIR) -I $(LFTINC) -Wall -Wextra -Werror
LIBS	= -L $(LIBDIR) -lft -ltermcap

SRC		= main.c \
		  ft_analyser.c \
		  ft_lexer.c \
		  ft_lexer_fun.c \
		  ft_parser.c \
		  ft_parse_fun.c \
		  ft_token.c \
		  ft_node.c \
		  ft_builtin.c \
		  ft_is_builtin.c \
		  ft_cd.c \
		  ft_cd_fun.c \
		  ft_echo.c \
		  ft_echo_utf.c \
		  ft_checkpath.c \
		  ft_envman.c \
		  ft_notfnd.c \
		  ft_sighandler.c \
		  ft_token_handler.c \
		  ft_pfd_manage.c \
		  ft_cmd_handler.c \
		  ft_red_handler.c \
		  ft_get_bquote.c \
		  ft_red_open.c \
		  ft_term_fun.c \
		  ft_read_keys.c \
		  ft_keys_fun.c \
		  ft_keys_fun2.c \
		  ft_keys_fun3.c \
		  ft_keys_fun4.c \
		  ft_putchar_tc.c \
		  ft_log.c \
		  ft_error.c \
		  ft_utility_fun.c \
		  ft_autocomp.c \
		  ft_autocomp_fun.c \
		  ft_select.c \
		  ft_slct_dep.c \
		  ft_slct_dep2.c \
		  draw_list.c \
		  key_down.c \
		  key_up.c \
		  key_escape.c \
		  key_return.c \
		  key_right.c \
		  key_left.c \
		  keys.c \
		  list.c \
		  move.c \
		  signals.c \
		  write.c \
		  get_next_line.c

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
