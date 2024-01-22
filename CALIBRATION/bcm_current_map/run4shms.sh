#!/bin/bash

list=$1

while read line
do

fname=/groupc-pionlt/hallc_replay_lt/ROOTfiles/shms_replay_production_${line}_-1.root

root -b<<EOF
.x run.C("${fname}", "P")
EOF

[ ! -d "shms" ] && `mkdir shms`

mv bcmcurrent* ./shms/

done < ${list}
