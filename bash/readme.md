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
echp $num3

num4=`expr \( $num1 + 200 \) / 10 \* 2`
echp $num4

exit 0
```



#### if문

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

