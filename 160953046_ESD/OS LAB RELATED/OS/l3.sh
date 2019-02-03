#!/bin/bash
x=`find . -name "*.txt"`
for i in $x
  do
    j="$(echo $i | sed 's/\.txt$/\.text/')"
    mv $i $j
  done
