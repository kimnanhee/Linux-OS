# 쉘 스크립트

#### bash

우분투의 기본 쉘은 bash 쉘
`bash(Bource Again SHell)`  



 #### 쉘 스크립트 프로그래밍

C언어와 유사하게 프로그래밍 가능
변수, 반복문, 제어문 등의 사용이 가능
텍스트 파일 형태로 바로 실행
리눅스의 많은 부분이 쉘 스크립트로 작성



#### 변수의 기본

변수에 처음 값이 할당되면서 자동으로 생성
모든 변수는 문자열 취급
변수 이름은 대소문자 구분
변수를 대입할 때 = 좌우에 공백 X																							



#### 변수의 입력과 출력

$ 문자가 들어간 글자를 출력하려면 ' ' 로 묶어주거나 앞에 \
" "로 변수를 묶어줘도 된다.

``` sh
#!/bin/sh
myvar="Hi"
echo $myvar
echo "$myvar"
echo \$myvar

echo 갑 입력:
read myvar
echo "$myvar" = $myvar

exit 0
```



#### 숫자 계산

변수에 대입된 값은 모두 문자열 취급|
+, -, *, / 연산을 하기 위해 expr 사용
수식 괄호와 곱하기 앞에 \

``` sh
#!/bin/sh
num1=100
num2=$num1 + 200
echo $num2

num3=`expr $num1 + 200`
echo $num3

num4=`expr \( $num1 + 200 \) / 10 \* 2`
echo $num4

exit 0
```



#### if문

참 or 거짓
[ 조건 ]의 각 단어 사이는 공백

| 문자열 비교 | 결과               | 산술 비교 | 결과                       |
| ----------- | ------------------ | --------- | -------------------------- |
| =           | 같으면 True        | -eq       | 두 수식이 같으면 True      |
| !=          | 같지 않으면 True   | -ne       | 두 수식이 같지 않으면 True |
| -n          | NULL이 아니면 True | -gt       | 수식1이 크면 True          |
| -z          | NULL이면 True      | -ge       | 수식1이 크거나 같으면 True |
|             |                    | -lt       | 수식1이 작으면 True        |
|             |                    | -le       | 수식1이 작거나 같으면 True |
|             |                    | !         | 거짓이면 True              |

``` sh
#!/bin/sh
if [ "woo" = "woo" ]
then
	echo "참입니다."
else
	echo "거짓입니다."
fi

exit 0
```



#### 파일

| 파일 조건 | 결과                                |
| --------- | ----------------------------------- |
| -d        | 파일이 디렉터리면 True              |
| -e        | 파일이 존재하면 True                |
| -f        | 파일이 일반 파일이면 True           |
| -g        | 파일에 set-group-id가 설정되면 True |
| -r        | 파일이 읽기 가능이면 True           |
| -s        | 파일 크기가 0이 아니면 True         |
| -u        | 파일에 set-user-id가 설정되면True   |
| -w        | 파일이 쓰기 가능이면 True           |
| -x        | 파일이 실행 가능이면 True           |



``` sh
#!/bin/sh
fname=/lib/systemd/system/cron.service
if [ -f $fname ]
then
	head -5 $fname
else
	echo "cron 서버가 설치되지 않았습니다."
fi

exit 0
```



#### case문

if문 - 참 or 거짓
case문 - 여러 가지 경우

``` sh
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
```



#### AND, OR 관계 연산자

and는 -a, &&
or는 -o, ||

``` sh
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
```



#### for문

``` sh
#!/bin/sh
hap=0
for i in 1 2 3 4 5 6 7 8 9 10
do
	hap=`expr $hap + $i`
done
echo "1부터 10까지의 합 : "$hap

exit 0
```

``` sh
#!/bin/sh
for fname in $(ls *.sh)
do
	echo ""
	echo "---- $fname ----"
	head -3 $fname
done

exit 0
```



#### while문

조건식이 참인 동안에 반복
[ 1 ], [ : ]은 무한루프

``` sh
#!/bin/sh
while [ 1 ]
do
	echo "우분투 16.04 LTS"
done

exit 0
```

``` sh
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
```



#### eval

문자열을 명령문으로 인식하고 실행

``` sh
#!/bin/sh
str="ls -al"
echo str
eval str

exit
```



#### export

외부 변수로 선언해서 다른 프로그램에서도 사용 가능

``` sh
exp1.sh
#!/bin/sh
echo $var1
echo $var2

exit 0
```

``` sh
exp2.sh
#!/bin/sh
var1="지역 변수"
export var2="외부 변수"
sh exp1.sh

exit 0
```



#### set

리눅스 명령어를 결과로 사용하기 위해서는 $(명령어)
결과를 파라미터로 사용할 때는 set과 함께 사용

``` sh
#!/bin/sh
echo "오늘 날짜는 $(date)입니다."
set $(date)
echo "지금은 $4(시:분:초)입니다."

exit 0
```



#### shift

파라미터 변수를 하나씩 쉬프트

``` sh
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
```

