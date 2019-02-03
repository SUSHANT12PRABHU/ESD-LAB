#!/bin/sh
x=$(ls *.txt)
for i in $x
  do
    sed -i 's/^ex:/Example:/' $i
    sed -i 's/\.ex:/\.Example:/' $i  
  done
