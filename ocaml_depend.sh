#!/bin/bash
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ocaml_depend.sh                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/02 13:29:23 by jaguillo          #+#    #+#              #
#    Updated: 2015/11/02 16:08:44 by jaguillo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OCAML_DIR="srcs/solver"

OCAML_SOURCES="`find $OCAML_DIR -name '*.ml*' -type f`"

OCAML_OBJS=""

for file_name in $OCAML_SOURCES; do
	file_name=${file_name/.mli/.cmi}
	file_name=${file_name/.ml/.cmx}
	OCAML_OBJS="$OCAML_OBJS $file_name"
done

printf "ML_OBJS ="
for obj in $OCAML_OBJS; do
	printf " \\\\\n\t%s" "$obj"
done
echo
echo
echo "OCAML_DIR = $OCAML_DIR"
echo

ocamldep $OCAML_SOURCES
