#!/bin/sh
i=1
while [ $i -le $1 ]
do
    echo "hello world"
    i=`expr $i + 1`
done

exit 0
