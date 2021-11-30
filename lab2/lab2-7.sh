#!/bin/sh
mkdir $1
cd $1
touch file0.txt
mkdir file0
ln -s file0.txt file0
touch file1.txt
mkdir file1
ln -s file1.txt file1
touch file2.txt
mkdir file2
ln -s file2.txt file2
touch file3.txt
mkdir file3
ln -s file3.txt file3
touch file4.txt
mkdir file4
ln -s file4.txt file4
exit 0
