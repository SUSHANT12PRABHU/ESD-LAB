#!/bin/sh
echo "Enter filename"
read s
if [ -f $s ]; then
  echo "File"
elif [ -d $s ]; then
  echo "Directory"
fi

