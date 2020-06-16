#! /usr/bin/bash

#
# History:
# ================================================================
# Time-stamp: "2019-03-31 23:16:46 cdaq"
# ================================================================
#
# Author:  Richard L. Trotta III <trotta@cua.edu>
#
# Copyright (c) trottar
#


echo "##############################################################################"
echo "# HIGH #######################################################################"
echo "##############################################################################"



echo "# Center"
./run_chainQ2p115W2p95.sh high center
./run_chainQ3W2p32.sh high center
./run_chainQ3W3p14.sh high center
./run_chainQ4p4W2p74.sh high center
./run_chainQ5p5W3p02.sh high center
./run_chainQ05W2p40.sh high center

echo "# Left"
./run_chainQ2p115W2p95.sh high left
./run_chainQ3W2p32.sh high left
./run_chainQ3W3p14.sh high left
./run_chainQ4p4W2p74.sh high left
./run_chainQ5p5W3p02.sh high left
./run_chainQ05W2p40.sh high left

echo "# right"
./run_chainQ2p115W2p95.sh high right
./run_chainQ3W2p32.sh high right
./run_chainQ3W3p14.sh high right
./run_chainQ4p4W2p74.sh high right
./run_chainQ5p5W3p02.sh high right
./run_chainQ05W2p40.sh high right

echo "##############################################################################"
echo "# LOW ########################################################################"
echo "##############################################################################"

echo "# Center"
./run_chainQ2p115W2p95.sh low center
./run_chainQ3W2p32.sh low center
# ./run_chainQ3W3p14.sh low center
./run_chainQ4p4W2p74.sh low center
# ./run_chainQ5p5W3p02.sh low center
./run_chainQ05W2p40.sh low center

echo "# Left"
./run_chainQ2p115W2p95.sh low left
./run_chainQ3W2p32.sh low left
# ./run_chainQ3W3p14.sh low left
./run_chainQ4p4W2p74.sh low left
# ./run_chainQ5p5W3p02.sh low left
./run_chainQ05W2p40.sh low left

echo "# Right"
# ./run_chainQ2p115W2p95.sh low right
# ./run_chainQ3W2p32.sh low right
# ./run_chainQ3W3p14.sh low right
# ./run_chainQ4p4W2p74.sh low right
# ./run_chainQ5p5W3p02.sh low right
# ./run_chainQ05W2p40.sh low right
