#!/bin/bash
arr=($(ls -l --full-time | tr ' ' ':'))
echo ${arr[@]}
for i in $arr
  do
    y=$(echo $i | cut -d ':' -f 1)
    echo $y
  done
