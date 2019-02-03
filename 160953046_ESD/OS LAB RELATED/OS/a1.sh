#!/bin/bash
echo "Enter a number"
read a
l=$(expr $a / 2)

if [ $a == 2  -o  $a == 3  ]; then
  echo "Prime"
  exit
fi
  
for((i=2; i<=l; i++)); do
  if [ $((a % i)) == 0 ]; then
    echo "Not prime"
    exit
  fi
done

echo "Prime"    
