#!/bin/bash

for VAR in 2 3 4
do
  export PROCESSOR=$VAR
  echo "processor ${VAR}"
  export > result_${VAR}.txt
#  
  export PARALLEL=PARALLEL_FOR
  echo "execution de parallel for"
  T="$(date)"
  echo ${T} > result_par_for_${VAR}.txt
  for NAME in testDensite200 testDensite400 testDensite600 testDensite800 testDensite1000
  do
    (time ./sortie ${NAME}.xml >> result_densite_for_${VAR}.txt) 2>> result_densite_for_${VAR}.txt
  done
  T="$(date)"
  echo ${T} >> result_densite_for_${VAR}.txt
#
  export PARALLEL=PARALLEL_TASKS
  echo "execution de parallel task"
  T="$(date)"
  echo ${T} > result_densite_task_${VAR}.txt
  for NAME in testDensite200 testDensite400 testDensite600 testDensite800 testDensite1000
  do
    (time ./sortie ${NAME}.xml >> result_densite_task_${VAR}.txt) 2>> result_densite_task_${VAR}.txt
  done
  T="$(date)"
  echo ${T} >> result_densite_task_${VAR}.txt
#
  export PARALLEL=PARALLEL_PIPELINE
  echo "execution de parallel pipeline"
  T="$(date)"
  echo ${T} > result_densite_pl_${VAR}.txt
  for NAME in testDensite200 testDensite400 testDensite600 testDensite800 testDensite1000
  do
    echo $NAME
    (time ./sortie ${NAME}.xml >> result_densite_pl_${VAR}.txt) 2>> result_densite_pl_${VAR}.txt
  done
  T="$(date)"
  echo ${T} >> result_densite_pl_${VAR}.txt
#
done
#
unset PARALLEL
unset PROCESSOR
echo "execution sequentiel"
T="$(date)"
echo ${T} > result_densite_sequentiel.txt
  for NAME in testDensite200 testDensite400 testDensite600 testDensite800 testDensite1000
  do
    (time ./sortie ${NAME}.xml >> result_densite_sequentiel.txt) 2>> result_densite_sequentiel.txt
  done
T="$(date)"
echo ${T} >> result_sequentiel.txt
#
HOSTNAME=$(hostname)
NOW=$(date +"%Y-%m-%d")
FILE="result_$HOSTNAME_$NOW.tar.gz"
tar cvfz ${FILE} *.txt *.out
rm *.out *.txt
echo "Fini 100%"