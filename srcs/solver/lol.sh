#!/bin/bash

for f in $(ocamldep -sort `find . -name '*\.ml'`); do
	echo "${f}..."
	if [[ ! -f "${f}i" ]]; then
		ocamlc -thread -I Algorithms/ -I Heuristics/ -I ../../batteries-included/src/ -i "$f" > "${f}i" || rm "${f}i";
		echo "Gen ${f}i";
	fi
done
