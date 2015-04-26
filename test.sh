#!/bin/sh

# ResolveSouinsuのテスト用shellscript
# author コウジ
# date	2015/04/26

PATH="./Debug/"

LIST="
3,10,3
6,-1,-15
12,-1,-6
3,-8,4
3,5,7
"

for i in $LIST
do
 $PATH/ResolveSoinsu $i
done
