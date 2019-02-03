#!/bin/bash
x=`find * -maxdepth 0 -name "*.txt"`
for i in $x
  do
    j="$(echo $i | sed 's/\.txt$/\.text/')"
    mv $i $j
  done
