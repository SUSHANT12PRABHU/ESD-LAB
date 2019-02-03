#!/bin/bash
echo "Enter number"
read x
f=1
while((x > 1)); do
  f=`echo "$f*$x" | bc`
  ((x--))
done

echo $f  
