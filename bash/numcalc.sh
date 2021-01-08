#!/bin/sh
num1=100
num2=$num1+200
echo $num2

num3=`expr $num1 + 200`
echo $num3

num4=`expr \( $num1 + 200 \) / 10 \* 2`
echo $num4

exit 0
