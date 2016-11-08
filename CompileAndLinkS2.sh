#!/bin/bash
# This script compiles and links the Slave 2 Application for the C2 Implementation.
# The script assumes that the FW Profile object files are available for linking
# in directory $FW_OBJ.
#
# The script takes the following parameters:
# 1. The path of the FW Profile source directory
# 2. The path of the CORDET FW source directory
# 3. The path to the directory where executables are created
#
# This script performs the following actions:
# 1. Compile the CORDET FW files with the Slave 2 Demo #INCLUDE files
# 2. Compile the Slave 2 Demo Files for the C2 Implementation
# 3. Build the executables to run the Test Suite 
#
# In all cases, compilation and linking is done with the gcov options.
#
#====================================================================================
# Assign variables 
#====================================================================================

FW_DIR=$1
CR_DIR=$2
EXM_DIR=$3
EXE_DIR=$4

CR_SRC="$CR_DIR"

FW_OBJ="$EXE_DIR"

S2_SRC="$EXM_DIR/CrDemoSlave2"
S2_CNF_SRC="$EXM_DIR/CrConfigDemoSlave2" 
S1_CNF_SRC="$EXM_DIR/CrConfigDemoSlave1" 
S2_OBJ="$EXE_DIR/S2"

mkdir -p ${S2_OBJ}

#====================================================================================
# Set the compilation options
#====================================================================================
# Use the following definition for linker map
#OPT="-Os -Wall -c -fmessage-length=0" 
OPT="-O0 -g3 -Wall -c -fmessage-length=0 -fprofile-arcs -ftest-coverage"  

#====================================================================================
# Set the include path
#====================================================================================
INCLUDE="-I"$FW_DIR" -I"$S2_SRC" -I"$CR_SRC" -I"$S2_CNF_SRC"" 

echo "===================================================================================="
echo " Compile all the C2 Implementation Files "
echo "===================================================================================="
gcc $INCLUDE $OPT -o $S2_OBJ/CrFwAux.o $CR_SRC/Aux/CrFwAux.c
gcc $INCLUDE $OPT -o $S2_OBJ/CrFwBaseCmp.o $CR_SRC/BaseCmp/CrFwBaseCmp.c
gcc $INCLUDE $OPT -o $S2_OBJ/CrFwDummyExecProc.o $CR_SRC/BaseCmp/CrFwDummyExecProc.c
gcc $INCLUDE $OPT -o $S2_OBJ/CrFwInitProc.o $CR_SRC/BaseCmp/CrFwInitProc.c
gcc $INCLUDE $OPT -o $S2_OBJ/CrFwResetProc.o $CR_SRC/BaseCmp/CrFwResetProc.c
gcc $INCLUDE $OPT -o $S2_OBJ/CrFwInCmd.o $CR_SRC/InCmd/CrFwInCmd.c
gcc $INCLUDE $OPT -o $S2_OBJ/CrFwInFactory.o $CR_SRC/InFactory/CrFwInFactory.c
gcc $INCLUDE $OPT -o $S2_OBJ/CrFwInRegistry.o $CR_SRC/InRegistry/CrFwInRegistry.c
gcc $INCLUDE $OPT -o $S2_OBJ/CrFwInManager.o $CR_SRC/InManager/CrFwInManager.c
gcc $INCLUDE $OPT -o $S2_OBJ/CrFwInRep.o $CR_SRC/InRep/CrFwInRep.c
gcc $INCLUDE $OPT -o $S2_OBJ/CrFwInRepExecProc.o $CR_SRC/InRep/CrFwInRepExecProc.c
gcc $INCLUDE $OPT -o $S2_OBJ/CrFwInStream.o $CR_SRC/InStream/CrFwInStream.c
gcc $INCLUDE $OPT -o $S2_OBJ/CrFwInLoader.o $CR_SRC/InLoader/CrFwInLoader.c
gcc $INCLUDE $OPT -o $S2_OBJ/CrFwOutCmp.o $CR_SRC/OutCmp/CrFwOutCmp.c
gcc $INCLUDE $OPT -o $S2_OBJ/CrFwOutFactory.o $CR_SRC/OutFactory/CrFwOutFactory.c
gcc $INCLUDE $OPT -o $S2_OBJ/CrFwOutLoader.o $CR_SRC/OutLoader/CrFwOutLoader.c
gcc $INCLUDE $OPT -o $S2_OBJ/CrFwOutManager.o $CR_SRC/OutManager/CrFwOutManager.c
gcc $INCLUDE $OPT -o $S2_OBJ/CrFwOutRegistry.o $CR_SRC/OutRegistry/CrFwOutRegistry.c
gcc $INCLUDE $OPT -o $S2_OBJ/CrFwOutStream.o $CR_SRC/OutStream/CrFwOutStream.c
gcc $INCLUDE $OPT -o $S2_OBJ/CrFwPcktQueue.o $CR_SRC/Pckt/CrFwPcktQueue.c
gcc $INCLUDE $OPT -o $S2_OBJ/CrFwUtilityFunctions.o $CR_SRC/UtilityFunctions/CrFwUtilityFunctions.c
gcc $INCLUDE $OPT -o $S2_OBJ/CrFwAppSm.o $CR_SRC/AppStartUp/CrFwAppSm.c

echo "===================================================================================="
echo " Compile the Demo Application Common Files "
echo "===================================================================================="
gcc $INCLUDE $OPT -o $S2_OBJ/CrS2Main.o $S2_SRC/CrS2Main.c
gcc $INCLUDE $OPT -o $S2_OBJ/CrDaClientSocket.o $S2_SRC/CrDaClientSocket.c
gcc $INCLUDE $OPT -o $S2_OBJ/CrDaOutCmpTempViolation.o $S2_SRC/CrDaOutCmpTempViolation.c
gcc $INCLUDE $OPT -o $S2_OBJ/CrDaServerSocket.o $S2_SRC/CrDaServerSocket.c
gcc $INCLUDE $OPT -o $S2_OBJ/CrDaTempMonitor.o $S2_SRC/CrDaTempMonitor.c

echo "===================================================================================="
echo " Compile the C2 Configuration Files for the Slave 2 Application "
echo "===================================================================================="
function compileConfigFile {
  gcc $INCLUDE $OPT -o $S2_OBJ/"$1.o" $S2_CNF_SRC/"$1.c"
}
compileConfigFile "CrFwRepErr"
compileConfigFile "CrFwPckt"
compileConfigFile "CrFwRepInCmdOutcome"
compileConfigFile "CrFwTime"
compileConfigFile "CrFwAppStartUpProc"
compileConfigFile "CrFwAppResetProc"
compileConfigFile "CrFwAppShutdownProc"

echo "===================================================================================="
echo " Build the executable to run the Slave 2 Application "
echo "===================================================================================="
# Use following definition for linker map (and remove -fprofile-arcs option)
#LNKMAP="-Wl,-Map,$EXE_DIR/cr_Slave2.map" 
LNKMAP=""
#gcc -o $EXE_DIR/cr_Slave2 \
gcc -fprofile-arcs -o $EXE_DIR/cr_slave2 \
$FW_OBJ/FwPrConfig.o $FW_OBJ/FwPrCore.o $FW_OBJ/FwPrDCreate.o $FW_OBJ/FwSmAux.o \
$FW_OBJ/FwSmConfig.o $FW_OBJ/FwSmCore.o $FW_OBJ/FwSmDCreate.o $FW_OBJ/FwSmSCreate.o \
$S2_OBJ/CrFwAux.o $S2_OBJ/CrFwBaseCmp.o $S2_OBJ/CrFwDummyExecProc.o \
$S2_OBJ/CrFwInitProc.o $S2_OBJ/CrFwResetProc.o $S2_OBJ/CrFwInCmd.o $S2_OBJ/CrFwInRegistry.o \
$S2_OBJ/CrFwInManager.o $S2_OBJ/CrFwInRep.o $S2_OBJ/CrFwInRepExecProc.o $S2_OBJ/CrFwInLoader.o \
$S2_OBJ/CrFwInFactory.o $S2_OBJ/CrFwInStream.o $S2_OBJ/CrFwOutCmp.o $S2_OBJ/CrFwOutFactory.o \
$S2_OBJ/CrFwOutLoader.o $S2_OBJ/CrFwOutManager.o $S2_OBJ/CrFwOutRegistry.o $S2_OBJ/CrFwOutStream.o $S2_OBJ/CrFwPcktQueue.o \
$S2_OBJ/CrFwUtilityFunctions.o $S2_OBJ/CrFwPckt.o $S2_OBJ/CrFwRepErr.o $S2_OBJ/CrFwTime.o \
$S2_OBJ/CrFwAppSm.o $S2_OBJ/CrFwAppStartUpProc.o $S2_OBJ/CrFwAppResetProc.o $S2_OBJ/CrFwAppShutdownProc.o \
$S2_OBJ/CrFwRepInCmdOutcome.o \
$S2_OBJ/CrS2Main.o $S2_OBJ/CrDaClientSocket.o $S2_OBJ/CrDaServerSocket.o \
$S2_OBJ/CrDaOutCmpTempViolation.o $S2_OBJ/CrDaTempMonitor.o \
-lpthread $LNKMAP
