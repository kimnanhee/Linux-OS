#!/bin/sh
echo "무한반복 입력을 시작합니다(b-break, c-continue, e-exit)"
while [ 1 ]
do
	read input
	case $input in
		b | B )
			break ;;
		c | C )
			echo "while 조건으로 continue"
			continue ;;
		e | E )
			echo "exit으로 프로그램 종료"
			exit 1 ;;
	esac;
done
echo "프로그램 종료"

exit 0

