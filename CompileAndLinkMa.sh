#!/bin/bash
# This script compiles and links the Master Application for the C2 Implementation.
# The script assumes that the FW Profile object files are available for linking
# in directory $FW_OBJ.
#
# The script takes the following parameters:
# 1. The path of the FW Profile source directory
# 2. The path of the CORDET FW source directory
# 3. The path of the CORDET FW examples directory
# 4. The path to the directory where executables are created
#
# This script performs the following actions:
# 1. Compile the CORDET FW files with the Master Demo #INCLUDE files
# 2. Compile the Master Application Files for the C2 Implementation
# 3. Build the executable to run the Master Application 
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

MA_SRC="$EXM_DIR/CrDemoMaster"
MA_CNF_SRC="$EXM_DIR/CrConfigDemoMaster" 
MA_OBJ="$EXE_DIR/master"

mkdir -p ${MA_OBJ}

#====================================================================================
# Set the compilation options
#====================================================================================
# Use the following definition for linker map
#OPT="-Os -Wall -c -fmessage-length=0" 
OPT="-O0 -g3 -Wall -c -fmessage-length=0 -fprofile-arcs -ftest-coverage"  

#====================================================================================
# Set the include path
#====================================================================================
INCLUDE="-I"$FW_DIR" -I"$MA_SRC" -I"$CR_SRC" -I"$MA_CNF_SRC"" 

echo "===================================================================================="
echo " Compile all the C2 Implementation Files "
echo "===================================================================================="
gcc $INCLUDE $OPT -o $MA_OBJ/CrFwAux.o $CR_SRC/Aux/CrFwAux.c
gcc $INCLUDE $OPT -o $MA_OBJ/CrFwBaseCmp.o $CR_SRC/BaseCmp/CrFwBaseCmp.c
gcc $INCLUDE $OPT -o $MA_OBJ/CrFwDummyExecProc.o $CR_SRC/BaseCmp/CrFwDummyExecProc.c
gcc $INCLUDE $OPT -o $MA_OBJ/CrFwInitProc.o $CR_SRC/BaseCmp/CrFwInitProc.c
gcc $INCLUDE $OPT -o $MA_OBJ/CrFwResetProc.o $CR_SRC/BaseCmp/CrFwResetProc.c
gcc $INCLUDE $OPT -o $MA_OBJ/CrFwInCmd.o $CR_SRC/InCmd/CrFwInCmd.c
gcc $INCLUDE $OPT -o $MA_OBJ/CrFwInFactory.o $CR_SRC/InFactory/CrFwInFactory.c
gcc $INCLUDE $OPT -o $MA_OBJ/CrFwInRegistry.o $CR_SRC/InRegistry/CrFwInRegistry.c
gcc $INCLUDE $OPT -o $MA_OBJ/CrFwInManager.o $CR_SRC/InManager/CrFwInManager.c
gcc $INCLUDE $OPT -o $MA_OBJ/CrFwInRep.o $CR_SRC/InRep/CrFwInRep.c
gcc $INCLUDE $OPT -o $MA_OBJ/CrFwInRepExecProc.o $CR_SRC/InRep/CrFwInRepExecProc.c
gcc $INCLUDE $OPT -o $MA_OBJ/CrFwInStream.o $CR_SRC/InStream/CrFwInStream.c
gcc $INCLUDE $OPT -o $MA_OBJ/CrFwInLoader.o $CR_SRC/InLoader/CrFwInLoader.c
gcc $INCLUDE $OPT -o $MA_OBJ/CrFwOutCmp.o $CR_SRC/OutCmp/CrFwOutCmp.c
gcc $INCLUDE $OPT -o $MA_OBJ/CrFwOutFactory.o $CR_SRC/OutFactory/CrFwOutFactory.c
gcc $INCLUDE $OPT -o $MA_OBJ/CrFwOutLoader.o $CR_SRC/OutLoader/CrFwOutLoader.c
gcc $INCLUDE $OPT -o $MA_OBJ/CrFwOutManager.o $CR_SRC/OutManager/CrFwOutManager.c
gcc $INCLUDE $OPT -o $MA_OBJ/CrFwOutRegistry.o $CR_SRC/OutRegistry/CrFwOutRegistry.c
gcc $INCLUDE $OPT -o $MA_OBJ/CrFwOutStream.o $CR_SRC/OutStream/CrFwOutStream.c
gcc $INCLUDE $OPT -o $MA_OBJ/CrFwPcktQueue.o $CR_SRC/Pckt/CrFwPcktQueue.c
gcc $INCLUDE $OPT -o $MA_OBJ/CrFwUtilityFunctions.o $CR_SRC/UtilityFunctions/CrFwUtilityFunctions.c
gcc $INCLUDE $OPT -o $MA_OBJ/CrFwAppSm.o $CR_SRC/AppStartUp/CrFwAppSm.c

echo "===================================================================================="
echo "- Compile the Master Application"
echo "===================================================================================="
function compileMasterFile {
gcc $INCLUDE $OPT -o $MA_OBJ/"$1.o" $MA_SRC/"$1.c"
}
compileMasterFile "CrMaInRepTempViolation"
compileMasterFile "CrMaOutCmpEnableDisable"
compileMasterFile "CrMaOutCmpSetTempLimit"
compileMasterFile "CrMaMain"
compileMasterFile "CrDaClientSocket"
compileMasterFile "CrDaOutCmpTempViolation"
compileMasterFile "CrDaServerSocket"
compileMasterFile "CrDaTempMonitor"

echo "===================================================================================="
echo " Compile the C2 Configuration Files for the Master Application "
echo "===================================================================================="
function compileConfigFile {
gcc $INCLUDE $OPT -o $MA_OBJ/"$1.o" $MA_CNF_SRC/"$1.c"
}
compileConfigFile "CrFwRepErr"
compileConfigFile "CrFwPckt"
compileConfigFile "CrFwRepInCmdOutcome"
compileConfigFile "CrFwTime"
compileConfigFile "CrFwAppStartUpProc"
compileConfigFile "CrFwAppResetProc"
compileConfigFile "CrFwAppShutdownProc"

echo "===================================================================================="
echo " Build the executable to run the Master Application "
echo "===================================================================================="
# Use following definition for linker map (and remove -fprofile-arcs option)
#LNKMAP="-Wl,-Map,$EXE_DIR/cr_master.map" 
LNKMAP=""
#gcc -o $EXE_DIR/cr_master \
gcc -fprofile-arcs -o $EXE_DIR/cr_master \
$FW_OBJ/FwPrConfig.o $FW_OBJ/FwPrCore.o $FW_OBJ/FwPrDCreate.o $FW_OBJ/FwSmAux.o \
$FW_OBJ/FwSmConfig.o $FW_OBJ/FwSmCore.o $FW_OBJ/FwSmDCreate.o $FW_OBJ/FwSmSCreate.o \
$MA_OBJ/CrFwAux.o $MA_OBJ/CrFwBaseCmp.o $MA_OBJ/CrFwDummyExecProc.o \
$MA_OBJ/CrFwInitProc.o $MA_OBJ/CrFwResetProc.o $MA_OBJ/CrFwInCmd.o $MA_OBJ/CrFwInRegistry.o \
$MA_OBJ/CrFwInManager.o $MA_OBJ/CrFwInRep.o $MA_OBJ/CrFwInRepExecProc.o $MA_OBJ/CrFwInLoader.o \
$MA_OBJ/CrFwInFactory.o $MA_OBJ/CrFwInStream.o $MA_OBJ/CrFwOutCmp.o $MA_OBJ/CrFwOutFactory.o \
$MA_OBJ/CrFwOutLoader.o $MA_OBJ/CrFwOutManager.o $MA_OBJ/CrFwOutRegistry.o $MA_OBJ/CrFwOutStream.o $MA_OBJ/CrFwPcktQueue.o \
$MA_OBJ/CrFwUtilityFunctions.o $MA_OBJ/CrFwPckt.o $MA_OBJ/CrFwRepErr.o $MA_OBJ/CrFwTime.o \
$MA_OBJ/CrFwAppSm.o $MA_OBJ/CrFwAppStartUpProc.o $MA_OBJ/CrFwAppResetProc.o $MA_OBJ/CrFwAppShutdownProc.o \
$MA_OBJ/CrFwRepInCmdOutcome.o \
$MA_OBJ/CrMaInRepTempViolation.o $MA_OBJ/CrMaOutCmpEnableDisable.o $MA_OBJ/CrMaOutCmpSetTempLimit.o \
$MA_OBJ/CrMaMain.o $MA_OBJ/CrDaClientSocket.o $MA_OBJ/CrDaServerSocket.o \
$MA_OBJ/CrDaOutCmpTempViolation.o $MA_OBJ/CrDaTempMonitor.o \
-lpthread $LNKMAP
