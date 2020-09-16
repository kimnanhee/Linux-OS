시스템 콜 호출의 동작 준서 확인하기

---

```c
gcc hello.c
strace -o hello.log ./a.out
```



hello.log

write() - 문자열을 화면에 출력

main() 함수 앞뒤로 실행되는 것들