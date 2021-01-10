#!/bin/sh
myfunc()
{
	str=""
	while [ "$1" != "" ]
	do
		str="$str $1"
		shift
	done
	echo $str
}
myfunc AA BB CC DD EE FF GG HH

exit 0
