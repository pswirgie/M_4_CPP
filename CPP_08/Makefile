# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pswirgie <pswirgie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/08 15:59:21 by pswirgie          #+#    #+#              #
#    Updated: 2026/07/08 16:03:50 by pswirgie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += --no-print-directory

DIRS = $(dir $(wildcard */Makefile))
TARGETS = all clean fclean re

.PHONY: $(TARGETS)

$(TARGETS):
	@for d in $(DIRS); do \
		$(MAKE) -C $$d $@; \
	done