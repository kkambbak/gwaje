#!/bin/sh
mkdir $1
cd $1
touch file0.txt
touch file1.txt
touch file2.txt
touch file3.txt
touch file4.txt
ls
mkdir $1
tar -cvf files.tar file0.txt file1.txt file2.txt file3.txt file4.txt
mv files.tar files/
cd $1
tar -xf files.tar
