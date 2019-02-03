#!/bin/bash
bs=1000
ta=100
gs=`echo "$bs+$ta+$bs/100" | bc -l`
echo $gs
