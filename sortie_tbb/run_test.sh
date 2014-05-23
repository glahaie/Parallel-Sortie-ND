#!/bin/bash

for VAR in 2 3 4
do
  export PROCESSOR=$VAR
  echo "processor ${VAR}"
#  
  export PARALLEL=PARALLEL_FOR
  echo "execution de parallel for"
  T="$(date)"
  echo ${T} > result_unittest_${VAR}.txt
  for VAR2 in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
  do
    (time ./../test/Main ${VAR2} >> result_unittest_${VAR}.txt) 2>> result_unittest_${VAR}.txt
  done
  T="$(date)"
#
  export PARALLEL=PARALLEL_TASKS
  echo "execution de parallel task"
  T="$(date)"
  echo ${T} > result_unittest_${VAR}.txt
  for VAR2 in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
  do
    (time ./../test/Main ${VAR2} >> result_unittest_${VAR}.txt) 2>> result_unittest_${VAR}.txt
  done
  T="$(date)"
#
  export PARALLEL=PARALLEL_PIPELINE
  echo "execution de parallel pipeline"
  T="$(date)"
  echo ${T} > result_unittest_${VAR}.txt
  for VAR2 in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
  do
    (time ./../test/Main ${VAR2} >> result_unittest_${VAR}.txt) 2>> result_unittest_${VAR}.txt
  done
  T="$(date)"
done
unset PARALLEL
unset PROCESSOR