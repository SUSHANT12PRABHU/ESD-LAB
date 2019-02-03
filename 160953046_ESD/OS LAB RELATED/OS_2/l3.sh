#!/bin/bash

sort_fn() {
  arr=$(printf '%s\n' "$@" | sort -n)
  echo $arr
}
sort_fn "$@"  
