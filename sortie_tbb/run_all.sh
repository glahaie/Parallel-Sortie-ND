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
  for NAME in test_densite NewABAL1100A2 NewABAL3100A2 NewABAL5100A2 PISY100A2O PISY500A2O
  do
    (time ./sortie ${NAME}.xml >> result_par_for_${VAR}.txt) 2>> result_par_for_${VAR}.txt
  done
  T="$(date)"
  echo ${T} >> result_par_for_${VAR}.txt
  for NAME in test_densite NewABAL1100A2 NewABAL3100A2 NewABAL5100A2 PISY100A2O PISY500A2O
  do
    mv -f ${NAME}.out ${NAME}_for_${VAR}.out
  done
  rm -f *.gz.tar
#
  export PARALLEL=PARALLEL_TASKS
  echo "execution de parallel task"
  T="$(date)"
  echo ${T} > result_par_task_${VAR}.txt
  for NAME in test_densite NewABAL1100A2 NewABAL3100A2 NewABAL5100A2 PISY100A2O PISY500A2O
  do
    (time ./sortie ${NAME}.xml >> result_par_task_${VAR}.txt) 2>> result_par_task_${VAR}.txt
  done
  T="$(date)"
  echo ${T} >> result_par_task_${VAR}.txt
  for NAME in test_densite NewABAL1100A2 NewABAL3100A2 NewABAL5100A2 PISY100A2O PISY500A2O
  do
    mv -f ${NAME}.out ${NAME}_task_${VAR}.out
  done
  rm -f *.gz.tar
#
  export PARALLEL=PARALLEL_PIPELINE
  echo "execution de parallel pipeline"
  T="$(date)"
  echo ${T} > result_par_pl_${VAR}.txt
  for NAME in test_densite NewABAL1100A2 NewABAL3100A2 NewABAL5100A2 PISY100A2O PISY500A2O
  do
    (time ./sortie ${NAME}.xml >> result_par_pl_${VAR}.txt) 2>> result_par_pl_${VAR}.txt
  done
  T="$(date)"
  echo ${T} >> result_par_pl_${VAR}.txt
  for NAME in test_densite NewABAL1100A2 NewABAL3100A2 NewABAL5100A2 PISY100A2O PISY500A2O
  do
    mv -f ${NAME}.out ${NAME}_pl_${VAR}.out
  done
  rm -f *.gz.tar
#
done
#
unset PARALLEL
unset PROCESSOR
echo "execution sequentiel"
T="$(date)"
echo ${T} > result_sequentiel.txt
  for NAME in test_densite NewABAL1100A2 NewABAL3100A2 NewABAL5100A2 PISY100A2O PISY500A2O
  do
    (time ./sortie ${NAME}.xml >> result_sequentiel.txt) 2>> result_sequentiel.txt
  done
T="$(date)"
echo ${T} >> result_sequentiel.txt
  for NAME in test_densite NewABAL1100A2 NewABAL3100A2 NewABAL5100A2 PISY100A2O PISY500A2O
  do
    mv -f ${NAME}.out ${NAME}_seq.out
  done
  rm -f *.gz.tar
#
HOSTNAME=$(hostname)
NOW=$(date +"%Y-%m-%d")
FILE="result_$HOSTNAME_$NOW.tar.gz"
tar cvfz ${FILE} *.txt *.out
rm *.out *.txt
echo "Fini 100%"