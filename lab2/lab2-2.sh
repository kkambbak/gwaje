#1/bin/sh
if [ $2 = "-" ]
then
    echo `expr $1 - $3`
elif [ $2 = "+" ]
then
    echo `expr $1 + $3`
fi
exit 0
