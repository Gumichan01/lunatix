#!/bin/sh

#
# This script will help you to launch some tests on the engine
# It only works on Linux system.
#

LOG_FILE="./result-test-lunatix-"$(date +%y-%m-%d-%H:%M:%S)".log";
LOG_TMP_FILE=/tmp/${LOG_FILE};
SUCCESS_TAG="SUCCESS";
FAILURE_TAG="FAILURE";

touch ${LOG_TMP_FILE}; chmod 600 ${LOG_TMP_FILE}
./test-init 2>&1 | tee -a ${LOG_TMP_FILE}
./test-config 2>&1 | tee -a ${LOG_TMP_FILE}
./test-system 2>&1 | tee -a ${LOG_TMP_FILE}
./test-device 2>&1 | tee -a ${LOG_TMP_FILE}
./test-file 2>&1 | tee -a ${LOG_TMP_FILE}
./test-physics 2>&1 | tee -a ${LOG_TMP_FILE}
./test-window 2>&1 | tee -a ${LOG_TMP_FILE}
./test-ttf 2>&1 | tee -a ${LOG_TMP_FILE}
./test-particle 2>&1 | tee -a ${LOG_TMP_FILE}

# Rate of success
NB_OK=`grep ${SUCCESS_TAG} ${LOG_TMP_FILE} | wc -l | tr -s ' ' | cut -d ' ' -f1`
NB_KO=`grep ${FAILURE_TAG} ${LOG_TMP_FILE} | wc -l | tr -s ' ' | cut -d ' ' -f1`
NB_TESTS=`expr ${NB_OK} + ${NB_KO}`

echo " = Test report = " | tee -a ${LOG_TMP_FILE}
echo "Success: "${NB_OK}"/"${NB_TESTS} | tee -a ${LOG_TMP_FILE}

if [ ${NB_KO} -ne 0 ]]
then
	cp ${LOG_TMP_FILE} ${LOG_FILE}
fi

rm -f win-*.png
rm ${LOG_TMP_FILE}

