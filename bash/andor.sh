#!/bin/sh
echo "파일명을 입력해주세요."
read fname
if [ -f $fname ] && [ -s $fname ]
then
	head -5 $fname
else
	echo "파일이 없거나, 크기가 0입니다."
fi

exit 0
