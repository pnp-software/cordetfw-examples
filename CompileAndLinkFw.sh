#!/bin/bash
# This script compiles the part of the FW Profile required for the C2 Implementation:
# - The State Machine Modules (excluding static creation component)
# - The Procedure Modules (excluding static creation component)
#
# The script takes the following parameters:
# 1. The path of the FW Profile source directory
# 2. The path to the directory where executables are created
#
# This script performs the following actions:
# 1. Compile the FW Profile files which are needed by the CORDET FW
#
#====================================================================================
# Assign variables 
#====================================================================================

FW_DIR=$1
EXE_DIR=$2

FW_SRC="$FW_DIR"
FW_OBJ="$EXE_DIR"

mkdir -p ${FW_OBJ}

#====================================================================================
# Set the compilation options
#====================================================================================
# Use the following definition for linker map
OPT="-Os -Wall -c -ansi -pedantic -fmessage-length=0" 
#OPT="-O0 -g3 -Wall -c -fmessage-length=0 -fprofile-arcs -ftest-coverage"  

echo "===================================================================================="
echo "- Compile the part of the FW Profile needed for the C2 Applications"
echo "===================================================================================="
gcc $OPT -o $FW_OBJ/FwPrConfig.o $FW_SRC/FwPrConfig.c 
gcc $OPT -o $FW_OBJ/FwPrCore.o $FW_SRC/FwPrCore.c
gcc $OPT -o $FW_OBJ/FwPrDCreate.o $FW_SRC/FwPrDCreate.c
gcc $OPT -o $FW_OBJ/FwSmAux.o $FW_SRC/FwSmAux.c
gcc $OPT -o $FW_OBJ/FwSmConfig.o $FW_SRC/FwSmConfig.c
gcc $OPT -o $FW_OBJ/FwSmCore.o $FW_SRC/FwSmCore.c
gcc $OPT -o $FW_OBJ/FwSmDCreate.o $FW_SRC/FwSmDCreate.c
gcc $OPT -o $FW_OBJ/FwSmSCreate.o $FW_SRC/FwSmSCreate.c
