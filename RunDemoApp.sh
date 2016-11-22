#!/bin/bash
# This script runs the demo applications of the CORDET Framework.
#
# This script takes one parameter:
# 1. The path to the directory where the demo application executables are located
#
# This script performs the following actions:
# 1. It spawns three processes each of which runs one of the 3 demo applications
#
#====================================================================================
# Assign variables
#====================================================================================

EXE_DIR=$1
OUTFILE1="DemoAppOut_Master.txt"
OUTFILE2="DemoAppOut_Slave1.txt"
OUTFILE3="DemoAppOut_Slave2.txt"

rm -f $EXE_DIR/$OUTFILE1
rm -f $EXE_DIR/$OUTFILE2
rm -f $EXE_DIR/$OUTFILE3

echo " "
echo "Run Demo Applications -- this takes nearly 2 minutes"
echo "(Demo application outputs is in DemoAppOut_*.txt files)"
echo " "
$EXE_DIR/cr_slave1 > $EXE_DIR/$OUTFILE2 &
sleep 1
$EXE_DIR/cr_master > $EXE_DIR/$OUTFILE1 &
sleep 1
$EXE_DIR/cr_slave2 > $EXE_DIR/$OUTFILE3 &

# give time to the demo applications to terminate
sleep 105

