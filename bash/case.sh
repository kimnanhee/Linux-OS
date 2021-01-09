#!/bin/sh
echo "리눅스가 좋나요? (y/n)"
read answer
case $answer in
	yes | y | Y | Yes | YES)
		echo "좋습니다!";;
	[nN]*)
		echo "슬퍼요ㅠ";;
	*)
		echo "잘못된 입력입니다."
		exit 1;;
esac

exit 0
