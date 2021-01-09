#!/bin/sh
echo "생일을 입력해주세요."
read mypass
while [ $mypass != "0225" ]
do
	echo "틀렸습니다. 다시 입력해주세요."
	read mypass
done
echo "정답!"

exit 0
