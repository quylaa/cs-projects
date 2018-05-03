#!/bin/bash
for i in $(seq 1 4); do
	s="s$i"
	a="a$i"
	o="o$i"
	# O="$(./out $s)"
	./out $s > $o
	vimdiff $a $o
	rm $o
done
