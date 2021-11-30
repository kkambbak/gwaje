#!/bin/sh
myfunction () {
echo "함수안으로 들어왔음"
ls $1
return
}
echo "프로그램을 시작합니다"
myfunction $1
echo "프로그램을 종료합니다."
exit 0
