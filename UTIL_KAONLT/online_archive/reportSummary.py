#!/usr/bin/env python

import sys

runNo  = sys.argv[1]
evenNo = sys.argv[2]

summaryfile='./REPORT_OUTPUT/COIN/PRODUCTION/summary_production_%s_%s.report' % (runNo, evenNo)

f    = open(summaryfile)
fout = open('output.txt','w')

sumList = ['Cut Summary for run %s' % (runNo)]

for line in f:
    data = line.split('completed')
    for index, obj in enumerate(sumList) :
        if (sumList[index] in data[0]) :
            if (index == 0) :
                fout.write('\n=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:\n\n')
                fout.write('Kaon-LT Report Summary')
                fout.write('\n\n=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:\n\n')
                fout.write("Most recent analysis for run %s was completed on" % (runNo) + data[1] + '\n')
f.close()

#filename = './REPORT_OUTPUT/COIN/PRODUCTION/KaonLT_replay_coin_production_%s_%s.report' % (runNo, evenNo)
filename = './REPORT_OUTPUT/COIN/PRODUCTION/replay_coin_production_%s_%s.report' % (runNo, evenNo)

f    = open(filename)
#fout = open('output.txt','w')

objList = ['Run #', 
           'SHMS Run Length',
           'SHMS BCM1 Beam Cut Current', 'SHMS BCM1 Beam Cut Charge',
           'SHMS BCM2 Beam Cut Current', 'SHMS BCM2 Beam Cut Charge',
           'SHMS BCM4A Beam Cut Current', 'SHMS BCM4A Beam Cut Charge',
           'SHMS BCM4B Beam Cut Current', 'SHMS BCM4B Beam Cut Charge',
           'SHMS BCM4C Beam Cut Current', 'SHMS BCM4C Beam Cut Charge',
           'SHMS Unser Beam Cut Current', 'SHMS Unser Beam Cut Charge',
           'SHMS_pTRIG1 Pre-triggers', 'SHMS_pTRIG3 Pre-triggers', 'SHMS_pTRIG5 Pre-triggers',
           'SHMS_pTRIG1 Pre-scaled Pre-triggers', 'SHMS_pTRIG3 Pre-scaled Pre-triggers', 'SHMS_pTRIG5 Pre-scaled Pre-triggers',
           'Coin ROC2 pTRIG1 Accepted Triggers', 'Coin ROC2 pTRIG3 Accepted Triggers', 'Coin ROC2 pTRIG5 Accepted Triggers', 'ROC2 OG 6 GeV Electronic Dead Time (100, 150) ']

for line in f:
    data = line.split(':')
    for index, obj in enumerate(objList) :
        if (objList[index] in data[0]) :
            #if (index == 0) :
             #   fout.write('\n=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:\n\n')
              #  fout.write('Kaon-LT Report Summary')
              #  fout.write('\n\n=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:\n\n')
            if (index == 19) :
                COIN_RAW = data[1].split("[")
            if (index == 22) :
                COIN_ACC = data[1].split("[")
            if (objList[index] == 'ROC2 OG 6 GeV Electronic Dead Time (100, 150) ') :
                elec_DT = data[1].split("%")
                elec_LT = 1-float(elec_DT[0])
                fout.write('\nROC2 OG 6 GeV Electronic Live Time (100, 150) (%): ')
                fout.write(str(elec_LT))
            else :
                fout.write(data[0] + ' : ' + data[1])
COIN_LT = 100-(float(COIN_ACC[0]) / float(COIN_RAW[0]))
fout.write('\nComputer Live Time for COIN Trigger (%): ')
fout.write(str(COIN_LT))
f.close()

#shms_file = '../REPORT_OUTPUT/SHMS/PRODUCTION/replay_shms_coin_production_%s_50000.report' % (runNo)
shms_file = '../MON_OUTPUT/REPORT/reportMonitor_shms_%s_50000.txt' % (runNo)
#print('./REPORT_OUTPUT/COIN/PRODUCTION/output_coin_production_%s_%s.report' % (runNo, evenNo))
f    = open(shms_file)
fout.write('\n\n')
shmsList = ['HADRON SING FID TRACK EFFIC', 'Overall AERO Efficiency']

for line in f:
    data = line.split(':')
    for index, obj in enumerate(shmsList) :
        if (shmsList[index] in data[0]) :
                        if(shmsList[index] == 'Overall AERO Efficiency') : 
                            line = data[0]
                            line = line.replace('Overall AERO Efficiency', 'Overall SHMS Aero Efficiency')
                            fout.write(line + ' : ' + data[1])
                        else : fout.write(data[0] + ' : ' + data[1])
f.close()

#hms_file = '../REPORT_OUTPUT/HMS/PRODUCTION/replay_hms_coin_production_%s_50000.report' % (runNo)
hms_file = '../MON_OUTPUT/REPORT/reportMonitor_hms_%s_50000.txt' % (runNo)
#print('./REPORT_OUTPUT/COIN/PRODUCTION/output_coin_production_%s_%s.report' % (runNo, evenNo))
f    = open(hms_file)
fout.write('\n')
hmsList = ['E SING FID TRACK EFFIC','Overall HGC Efficiency']

for line in f:
    data = line.split(':')
    for index, obj in enumerate(hmsList) :
        if (hmsList[index] in data[0]) :
            if(hmsList[index] == 'Overall HGC Efficiency') : 
                line = data[0]
                line = line.replace('Overall HGC Efficiency', 'Overall HMS Cer Efficiency')
                fout.write(line + ' : ' + data[1])
            else : fout.write(data[0] + ' : ' + data[1])
f.close()

replay_file = './REPORT_OUTPUT/COIN/PRODUCTION/output_coin_production_%s_%s.report' % (runNo, evenNo)
#print('./REPORT_OUTPUT/COIN/PRODUCTION/output_coin_production_%s_%s.report' % (runNo, evenNo))
f    = open(replay_file)
fout.write('\n\n')
replayList = ['Missing Ref times']

fout.write('\n=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:\n\n')
for line in f:
    data = line.split(':')
    for index, obj in enumerate(replayList) :
        if (replayList[index] in data[0]) :
            fout.write(data[0] + ' : ' + data[1])
fout.write('\n=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:\n\n')

f.close()
fout.close()
