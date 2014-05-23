#!/bin/bash
HOSTNAME="$(hostname)"
NOW=$(date +"%Y-%m-%d")
FILE="result_$HOSTNAME_$NOW.tar.gz"
tar cvfz ${FILE} *.txt *.out
rm -f *.out *.txt
