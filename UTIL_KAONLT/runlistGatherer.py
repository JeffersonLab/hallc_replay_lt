#!/usr/bin/env python

import sys

runNum = sys.argv[1]
runType = sys.argv[2]
target = sys.argv[3]

#report_1="./REPORT_OUTPUT/COIN/PRODUCTION/KaonLT_replay_coin_production_%s_-1.report" % (runNum)
report_1="./REPORT_OUTPUT/COIN/PRODUCTION/replay_coin_production_%s_-1.report" % (runNum)
f    = open(report_1)
fout = open('tmp','wb')

curList = ['SHMS BCM4B Beam Cut Current']

for line in f:
    data = line.split(':')
    for index, obj in enumerate(curList) :
        if (curList[index] in data[0]) : 
            if(index == 0) :
                current_tmp = data[1].split(" ")
current=float(current_tmp[1])
fout.write(str(current) + "\n")
f.close()

#report_2="./REPORT_OUTPUT/COIN/PRODUCTION/KaonLT_replay_coin_production_%s_-1.report" % (runNum)
report_2="./REPORT_OUTPUT/COIN/PRODUCTION/replay_coin_production_%s_-1.report" % (runNum)
f    = open(report_2)

psList = ['Ps1_factor','Ps3_factor','Ps5_factor']

psActual = ['-1','1','2','3','5','9','17','33','65','129','257','513','1025','2049','4097','8193','16385','32769']

psValue = ['-1','0','1','2','3','4','5','6','7','8','9','10','11','12','13','14','15','16']

for line in f:
    data = line.split('=')
    for index, obj in enumerate(psList) :
        if (psList[index] in data[0]) : 
            if (index == 0) :  
                ps1_tmp = data[1].split(" ")
            if (index == 1) : 
                ps3_tmp = data[1].split(" ")
            if (index == 2) :
                ps5_tmp = data[1].split(" ")
ps1=float(ps1_tmp[1])
ps3=float(ps3_tmp[1])
ps5=float(ps5_tmp[1])
i=0
for index in psActual:
    if (float(index) == ps1) :
        PS1 = str(psValue[i])
    if (float(index) == ps3) :
        PS3 = str(psValue[i])
    if (float(index) == ps5) :
        PS5 = str(psValue[i])
    i=i+1
fout.write(str(PS1) + "\n")
fout.write(str(ps1) + "\n")
fout.write(str(PS3) + "\n")
fout.write(str(ps3) + "\n")
fout.write(str(PS5) + "\n")
fout.write(str(ps5) + "\n")
f.close()

#report_3="./REPORT_OUTPUT/COIN/PRODUCTION/KaonLT_replay_coin_production_%s_-1.report" % (runNum)
report_3="./REPORT_OUTPUT/COIN/PRODUCTION/replay_coin_production_%s_-1.report" % (runNum)
f    = open(report_3)

repList = ['SHMS_pTRIG3 Pre-triggers', 'SHMS_pTRIG1 Pre-triggers', 
           'SHMS_pTRIG5 Pre-scaled Pre-triggers', 'SHMS BCM4B Beam Cut Charge',
           'Coin ROC2 pTRIG5 Accepted Triggers']

for line in f:
    data = line.split(':')
    for index, obj in enumerate(repList) :
        if (repList[index] in data[0]) : 
            if (index == 0) : 
                HMSRATE_tmp = data[1].split(" ")
            if (index == 1) : 
                SHMSRATE_tmp = data[1].split(" ")
            if (index == 2) : 
                COINRATE_tmp = data[1].split(" ")
            if (index == 3) : 
                charge_tmp = data[1].split(" ")
            if (index == 4) : 
                RAWCOIN_tmp = data[1].split(" ")
HMSRATE=float(HMSRATE_tmp[6])
SHMSRATE=float(SHMSRATE_tmp[6])
COINRATE=float(COINRATE_tmp[6])
charge=float(charge_tmp[1])
RAWCOIN=float(RAWCOIN_tmp[1])
fout.write(str(HMSRATE) + "\n")
fout.write(str(SHMSRATE) + "\n")
fout.write(str(COINRATE) + "\n")
fout.write(str(charge) + "\n")
fout.write(str(RAWCOIN) + "\n")
f.close()

report_4="../MON_OUTPUT/REPORT/reportMonitor_shms_%s_50000.txt" % (runNum)
f    = open(report_4)

monList = ['HADRON SING FID TRACK EFFIC']

for line in f:
    data = line.split(':')
    for index, obj in enumerate(monList) :
        if (monList[index] in data[0]) :
            if(index == 0) :  
                hadtrack_tmp = data[1].split(" ")
hadtrack=float(hadtrack_tmp[4])
fout.write(str(hadtrack) + "\n")
f.close()

report_5="OUTPUT/scalers_Run%s.txt" % (runNum)
f    = open(report_5)

scalList = ['SHMS_pTRIG1 Pre-scaled Pre-triggers','SHMS_pTRIG3 Pre-scaled Pre-triggers', 'SHMS_pTRIG5 Pre-triggers']

for line in f:
    data = line.split(':')
    for index, obj in enumerate(scalList) :
        if (scalList[index] in data[0]) :
            if(index == 0) :  
                ptrig1_tmp = data[1].split(" ")
            if(index == 1) :  
                ptrig3_tmp = data[1].split(" ")
            if(index == 2) :  
                ptrig5_tmp = data[1].split(" ")
ptrig1=float(ptrig1_tmp[3])
ptrig3=float(ptrig3_tmp[3])
ptrig5=float(ptrig5_tmp[3])
fout.write(str(ptrig1) + "\n")
fout.write(str(ptrig3) + "\n")
fout.write(str(ptrig5))
f.close()
fout.close()
