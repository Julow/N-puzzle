# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/09/24 16:50:26 by jaguillo          #+#    #+#              #
#    Updated: 2015/09/26 12:27:48 by juloo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TESTS := xml

FLAGS := -Wall -Wextra -O2 -g -std=c++14
HEADS := -I ../include
LINKS := -L .. -lftui

SHELL := /bin/bash

all:
	echo "Available tests: $(TESTS)"

$(TESTS): %: libftui out_%
%: libftui out_%
	./out_$@

out_%: test_%.cpp ../libftui.a
	clang++ $(FLAGS) $(HEADS) $< -o $@ $(LINKS)
	printf "\033[32m$@\033[0m\n"

libftui:
	make -C ..

clean:
	rm -rf $(addprefix out_,$(TESTS))

fclean: clean

.PHONY: all clean fclean libft
.SILENT:

xml:
	cat test.xml | ./out_xml
