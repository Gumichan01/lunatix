#!/bin/sh

#
# This script will help you to launch some tests on the library
# It only works on the Linux systems.
#

VERSION="v0.8"
LOG_FILE="lunatix-"${VERSION}"-"$(date +%Y-%m-%d-%H:%M:%S)".log";
LOG_TMP_FILE=/tmp/"."${LOG_FILE}".lx.tmp";
LOG_RESULT_DIR="test/result/";
LOG_RESULT_FILE=${PWD}"/"${LOG_RESULT_DIR}${LOG_FILE};
SUCCESS_TAG="SUCCESS";
FAILURE_TAG="FAILURE";

touch ${LOG_TMP_FILE} && chmod 600 ${LOG_TMP_FILE}
echo "\n============================= Begin Report ============================\n\n" \
| tee -a ${LOG_TMP_FILE}
./test-init 2>&1     | tee -a ${LOG_TMP_FILE}
./test-config 2>&1   | tee -a ${LOG_TMP_FILE}
./test-system 2>&1   | tee -a ${LOG_TMP_FILE}
./test-device 2>&1   | tee -a ${LOG_TMP_FILE}
./test-file 2>&1     | tee -a ${LOG_TMP_FILE}
./test-window 2>&1   | tee -a ${LOG_TMP_FILE}
./test-ttf 2>&1      | tee -a ${LOG_TMP_FILE}
./test-particle 2>&1 | tee -a ${LOG_TMP_FILE}
./test-ime 2>&1      | tee -a ${LOG_TMP_FILE}
./test-physics 2>&1  | tee -a ${LOG_TMP_FILE}
./test-audio 2>&1    | tee -a ${LOG_TMP_FILE}
./test-thread 2>&1   | tee -a ${LOG_TMP_FILE}

# Rate of success
NB_OK=`grep ${SUCCESS_TAG} ${LOG_TMP_FILE} | wc -l | tr -s ' ' | cut -d ' ' -f1`
NB_KO=`grep ${FAILURE_TAG} ${LOG_TMP_FILE} | wc -l | tr -s ' ' | cut -d ' ' -f1`
NB_TESTS=`expr ${NB_OK} + ${NB_KO}`

echo "\n============================= Test report =============================" \
| tee -a ${LOG_TMP_FILE}
echo "Success: "${NB_OK}"/"${NB_TESTS} | tee -a ${LOG_TMP_FILE}
echo "============================= End report ==============================\n" \
| tee -a ${LOG_TMP_FILE}

# Get the log file
mkdir -p ${LOG_RESULT_DIR}
cp ${LOG_TMP_FILE} ${LOG_RESULT_FILE}
echo "'"${LOG_FILE}"' generated in '"$(dirname ${LOG_RESULT_FILE}) "'"

rm -f win-*.png
rm ${LOG_TMP_FILE}
