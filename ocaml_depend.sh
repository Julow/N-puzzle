#!/bin/bash
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ocaml_depend.sh                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/02 13:29:23 by jaguillo          #+#    #+#              #
#    Updated: 2015/11/03 16:15:56 by jaguillo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OCAML_DIR="srcs/solver"

OCAML_SOURCES="`find $OCAML_DIR -name '*.ml*' -type f`"

OCAML_OBJS=""
ML_MAX_LEN=0

for file_name in `ocamldep -sort $OCAML_SOURCES`; do
	if [ "${#file_name}" -gt "$ML_MAX_LEN" ]; then
		ML_MAX_LEN="${#file_name}"
	fi
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
echo "ML_MAX_LEN = $ML_MAX_LEN"
echo

ocamldep -all -I "$OCAML_DIR" $OCAML_SOURCES
