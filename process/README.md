CPU 사용 시간을 처리하는 프로세스 통계 정보 얻기

---

명령어 라인의 파라미터(n, total, resol)

n : 동시에 동작하는 프로세스 수

total : 프로그램이 동작하는 총 시간(ms 단위)

resol : 데이터 수집 간격(ms 단위)



```
gcc -o sched sched.c

taskset -c 0 ./sched 1 100 1 > 1core_1process.txt
taskset -c 0 ./sched 2 100 1 < 1core_2process.txt

cat 1core_1process.txt
cat 1core_2process.txt
```



결과

2개의 텍스트 파일을 비교해보면 CPU에서 동작되는 프로세스의 정보에 대해서 알 수 있다.

라운드로빈 방식으로 동작하고 있다.