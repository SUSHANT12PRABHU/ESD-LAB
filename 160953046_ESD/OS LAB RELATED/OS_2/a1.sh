#!/bin/bash
echo $(ls -l $1 | cut -d " " -f 1)
