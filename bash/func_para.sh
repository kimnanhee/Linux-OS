#!/bin/sh
plus()
{
	echo "$1 + $2 = "`expr $1 + $2` 
}
echo "plue 함수 호출"
plus 10 20
plus 34 35

exit 0
