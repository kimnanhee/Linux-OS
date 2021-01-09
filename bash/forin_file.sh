#!/bin/sh
for fname in $(ls *.sh)
do
	echo ""
	echo "---- $fname ----"
	head -3 $fname
done

exit 0
