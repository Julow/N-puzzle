#!/bin/bash
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ocaml_depend.sh                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/02 13:29:23 by jaguillo          #+#    #+#              #
#    Updated: 2015/11/03 16:41:28 by jaguillo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OCAML_DIRS="srcs/solver batteries-included"

OCAML_SOURCES="`find $OCAML_DIRS -name '*.ml*' -type f`"
OCAML_FLAGS=""

for dir_name in `find $OCAML_DIRS -type d`; do
	OCAML_FLAGS="$OCAML_FLAGS -I $dir_name"
done

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
echo "OCAML_FLAGS +=$OCAML_FLAGS"
echo "ML_MAX_LEN = $ML_MAX_LEN"
echo

ocamldep -all -allow-approx $OCAML_DIRS $OCAML_SOURCES
