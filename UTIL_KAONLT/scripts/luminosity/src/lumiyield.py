#! /usr/bin/python
# Description:
# ================================================================
# Time-stamp: "2020-12-21 12:01:21 trottar"
# ================================================================
#
# Author:  Richard L. Trotta III <trotta@cua.edu>
#
# Copyright (c) trottar
#
import uproot as up
import numpy as np
import pandas as pd
import scipy
import scipy.integrate as integrate
import matplotlib.pyplot as plt
import sys, math, os, subprocess

sys.path.insert(0, '../../../bin/python/')
import kaonlt as klt

runNum = sys.argv[1]
MaxEvent=sys.argv[2]

# Add this to all files for more dynamic pathing
USER = subprocess.getstatusoutput("whoami") # Grab user info for file finding
HOST = subprocess.getstatusoutput("hostname")

if ("farm" in HOST[1]):
    REPLAYPATH = "/group/c-kaonlt/USERS/%s/hallc_replay_lt" % USER[1]
elif ("lark" in HOST[1]):
    REPLAYPATH = "/home/%s/work/JLab/hallc_replay_lt" % USER[1]
elif ("trottar" in HOST[1]):
    REPLAYPATH = "/home/trottar/Analysis/hallc_replay_lt"

print("Running as %s on %s, hallc_replay_lt path assumed as %s" % (USER[1], HOST[1], REPLAYPATH))

filename = "%s/UTIL_KAONLT/scripts/luminosity/OUTPUTS/lumi_data.csv" % REPLAYPATH
rootName = "%s/UTIL_KAONLT/ROOTfiles/coin_replay_Full_Lumi_%s_%s.root" % (REPLAYPATH,runNum,MaxEvent)
# report = "/u/group/c-kaonlt/USERS/%s/kaonlt/REPORT_OUTPUT/coin_replay_Full_Lumi_%s_%s.report" % (USER[1],runNum,MaxEvent)
report = "%s/UTIL_KAONLT/REPORT_OUTPUT/replay_coin_Lumi_%s_%s.report" % (REPLAYPATH,runNum,MaxEvent)

thres_curr = 2.5
# thres_curr = 10.0

f = open(report)

psList = ['Ps1_factor','Ps3_factor','Ps5_factor']

psActual = [-1,1,2,3,5,9,17,33,65,129,257,513,1025,2049,4097,8193,16385,32769]
psValue = [-1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16]

for line in f:
    data = line.split('=')
    curr_data = line.split(':')
    if ('SHMS BCM4A Beam Cut Current' in curr_data[0]) :
        report_current_tmp = curr_data[1].split(" ")[1]
    for index, obj in enumerate(psList) :
        if (psList[index] in data[0]) : 
            if (index == 0) :  
                ps1_tmp = data[1].split(" ")
            if (index == 1) : 
                ps3_tmp = data[1].split(" ")
            if (index == 2) :
                ps5_tmp = data[1].split(" ")
ps1=int(ps1_tmp[1])
ps3=int(ps3_tmp[1])
ps5=int(ps5_tmp[1])
report_current = float(report_current_tmp)        

for i,index in enumerate(psActual):
    #psValue
    if (index == ps1) :
        if(index == -1):
            PS1 = 0
        else:
            PS1 = psActual[i]
    if (index == ps3) :
        if(index == -1):
            PS3 = 0
        else:
            PS3 = psActual[i]
    if (index == ps5) :
        if(index == -1):
            PS5 = 0
        else:
            PS5 = psActual[i]
f.close()

'''
SCALER TREE, TSH
'''

s_tree = up.open(rootName)["TSP"]
s_branch = klt.pyBranch(s_tree)

# s_evts = len(s_tree)
s_evts = s_tree.array("P.BCM4A.scaler")

P_BCM4A_scalerCharge = s_tree.array("P.BCM4A.scalerCharge")
P_BCM2_scalerCharge = s_tree.array("P.BCM2.scalerCharge")
P_BCM4B_scalerCharge = s_tree.array("P.BCM4B.scalerCharge")
P_BCM1_scalerCharge = s_tree.array("P.BCM1.scalerCharge")
P_BCM4C_scalerCharge = s_tree.array("P.BCM4C.scalerCharge")

P_BCM4A_scalerCurrent = s_tree.array("P.BCM4A.scalerCurrent")
P_BCM2_scalerCurrent = s_tree.array("P.BCM2.scalerCurrent")
P_BCM4B_scalerCurrent = s_tree.array("P.BCM4B.scalerCurrent")
P_BCM1_scalerCurrent = s_tree.array("P.BCM1.scalerCurrent")
P_BCM4C_scalerCurrent = s_tree.array("P.BCM4C.scalerCurrent")

P_1Mhz_scalerTime = s_tree.array("P.1MHz.scalerTime")

P_pTRIG1_scaler = s_tree.array("P.pTRIG1.scaler")
P_pTRIG2_scaler = s_tree.array("P.pTRIG2.scaler")
P_pTRIG3_scaler = s_tree.array("P.pTRIG3.scaler")
P_pTRIG4_scaler = s_tree.array("P.pTRIG4.scaler")
P_pTRIG5_scaler = s_tree.array("P.pTRIG5.scaler")
P_pTRIG6_scaler = s_tree.array("P.pTRIG6.scaler")

P_pL1ACCP_scaler = s_tree.array("P.pL1ACCP.scaler")
P_pPRE40_scaler = s_tree.array("P.pPRE40.scaler")
P_pPRE100_scaler = s_tree.array("P.pPRE100.scaler")
P_pPRE150_scaler = s_tree.array("P.pPRE150.scaler")
P_pPRE200_scaler = s_tree.array("P.pPRE200.scaler")
P_pPRE40_scaler = s_tree.array("P.pPRE40.scaler")
P_pPRE100_scaler = s_tree.array("P.pPRE100.scaler")
P_pPRE150_scaler = s_tree.array("P.pPRE150.scaler")
P_pPRE200_scaler = s_tree.array("P.pPRE200.scaler")

P_pEL_LO_LO_scaler = s_tree.array("P.pEL_LO_LO.scaler")
P_pEL_LO_scaler = s_tree.array("P.pEL_LO.scaler")
P_pEL_HI_scaler = s_tree.array("P.pEL_HI.scaler")
P_pEL_REAL_scaler = s_tree.array("P.pEL_REAL.scaler")
P_pEL_CLEAN_scaler = s_tree.array("P.pEL_CLEAN.scaler")
P_pSTOF_scaler = s_tree.array("P.pSTOF.scaler")

P_pEL_LO_LO_scaler = s_tree.array("P.pEL_LO_LO.scaler")
P_pEL_LO_scaler = s_tree.array("P.pEL_LO.scaler")
P_pEL_HI_scaler = s_tree.array("P.pEL_HI.scaler")
P_pEL_REAL_scaler = s_tree.array("P.pEL_REAL.scaler")
P_pEL_CLEAN_scaler = s_tree.array("P.pEL_CLEAN.scaler")
P_pSTOF_scaler = s_tree.array("P.pSTOF.scaler")
P_pPRHI_scaler = s_tree.array("P.PRHI.scaler")
P_pPRLO_scaler = s_tree.array("P.PRLO.scaler")

P_EDTM_scaler = s_tree.array("P.EDTM.scaler")


def scaler(runNum, PS1, PS3, thres_curr):

    NBCM = 5
    NTRIG = 6
    NPRE = 4
    NRATE = 6
    SHMSNRATE = 8

    bcm_name = ["BCM1 ", "BCM2 ", "BCM4A", "BCM4B", "BCM4C"]

    trig_name = ["TRIG1", "TRIG2", "TRIG3", "TRIG4", "TRIG5", "TRIG6"]

    PRE_name = ["40", "100", "150", "200"]

    rate_name = ["EL_LO_LO", "EL_LO", "EL_HI", "EL_REAL", "EL_CLEAN", "STOF"]

    SHMS_rate_name = ["EL_LO_LO", "EL_LO", "EL_HI",
                      "EL_REAL", "EL_CLEAN", "STOF", "PR_HI", "PR_LO"]

    bcm_value = [P_BCM1_scalerCharge, P_BCM2_scalerCharge,
                 P_BCM4A_scalerCharge, P_BCM4B_scalerCharge, P_BCM4C_scalerCharge]

    time_value = P_1Mhz_scalerTime

    current = [P_BCM1_scalerCurrent, P_BCM2_scalerCurrent,
                 P_BCM4A_scalerCurrent, P_BCM4B_scalerCurrent, P_BCM4C_scalerCurrent]

    trig_value = [P_pTRIG1_scaler, P_pTRIG2_scaler, P_pTRIG3_scaler,
                  P_pTRIG4_scaler, P_pTRIG5_scaler, P_pTRIG6_scaler]

    acctrig_value = P_pL1ACCP_scaler

    PRE_value = [P_pPRE40_scaler, P_pPRE100_scaler,
                 P_pPRE150_scaler, P_pPRE200_scaler]

    SHMS_PRE_value = [P_pPRE40_scaler, P_pPRE100_scaler,
                      P_pPRE150_scaler, P_pPRE200_scaler]

    rate_value = [P_pEL_LO_LO_scaler, P_pEL_LO_scaler, P_pEL_HI_scaler,
                  P_pEL_REAL_scaler, P_pEL_CLEAN_scaler, P_pSTOF_scaler]

    SHMS_rate_value = [P_pEL_LO_LO_scaler, P_pEL_LO_scaler, P_pEL_HI_scaler,
                       P_pEL_REAL_scaler, P_pEL_CLEAN_scaler, P_pSTOF_scaler, P_pPRHI_scaler, P_pPRLO_scaler]

    EDTM_value = P_EDTM_scaler

    # Variables useful in Process
    # To find total charge
    name = [0]*NBCM
    charge_sum = [0]*NBCM
    time_sum = [0]*NBCM
    previous_charge = [0]*NBCM
    previous_time = 0
    previous_time = [0]*NBCM
    current_I = 0
    current_time = 0

    # To determine computer livetime
    name = [0]*NTRIG
    trig_sum = [0]*NTRIG
    previous_trig = [0]*NTRIG
    pretrigger = 0
    previous_pretrigger = 0
    acctrig_sum = 0
    previous_acctrig = 0

    # To determine HMS electronic livetime
    name = [0]*NPRE
    PRE_sum = [0]*NPRE
    previous_PRE = [0]*NPRE

    # To determine SHMS electronic livetime
    SHMS_PRE_sum = [0]*NPRE
    SHMS_previous_PRE = [0]*NPRE

    # To determine HMS trigger rates
    name = [0]*NRATE
    rate_sum = [0]*NRATE
    previous_rate = [0]*NRATE

    # To determine SHMS trigger rates
    rate_name = [0]*SHMSNRATE
    SHMS_rate_sum = [0]*SHMSNRATE
    SHMS_previous_rate = [0]*SHMSNRATE

    # To determine number of EDTM events
    EDTM_sum = 0
    EDTM_current = 0
    previous_EDTM = 0
    
    # for itrig in range(0, NTRIG):
        # print("trig_value[%s] = " %(itrig),trig_value[itrig][:5])
        # print(len(trig_value[itrig]))
        
    for ibcm in range(0, 5):
        previous_acctrig = (acctrig_value[0] - EDTM_current)
        previous_EDTM = EDTM_value[0]
        for itrig in range(0, NTRIG):
            previous_trig[itrig] = trig_value[itrig][0]
        for iPRE in range(0, NPRE):
            previous_PRE[iPRE] = PRE_value[iPRE][0]
            SHMS_previous_PRE[iPRE] = SHMS_PRE_value[iPRE][0]
        for iRATE in range(0, NRATE):
            previous_rate[iRATE] = rate_value[iRATE][0]
        for iRATE in range(0, SHMSNRATE):
            SHMS_previous_rate[iRATE] = SHMS_rate_value[iRATE][0]
        previous_time[ibcm] = time_value[0]
        previous_charge[ibcm] = bcm_value[ibcm][0]
        for i, evt in enumerate(s_evts):
            if (time_value[i] != previous_time[ibcm]):
                current_I = (bcm_value[ibcm][i] -
                             previous_charge[ibcm])/(time_value[i] - previous_time[ibcm])
            if (abs( current[ibcm][i]-report_current) < thres_curr ):
                charge_sum[ibcm] += (bcm_value[ibcm][i] - previous_charge[ibcm])
                time_sum[ibcm] += (time_value[i] - previous_time[ibcm])
            if (ibcm == 2 and abs( current[ibcm][i]-report_current) < thres_curr):
                EDTM_current = (EDTM_value[i] - previous_EDTM)
                EDTM_sum += EDTM_current
                acctrig_sum += ((acctrig_value[i] - EDTM_current) - previous_acctrig)
                for itrig in range(0, NTRIG):
                    trig_sum[itrig] += (trig_value[itrig][i] - previous_trig[itrig])
                    # print("trig_value[%s] = " %(itrig),trig_value[itrig][i])
                for iPRE in range(0, NPRE):
                    PRE_sum[iPRE] += (PRE_value[iPRE][i] - previous_PRE[iPRE])
                    SHMS_PRE_sum[iPRE] += (SHMS_PRE_value[iPRE][i] - SHMS_previous_PRE[iPRE])
                for iRATE in range(0, NRATE):
                    rate_sum[iRATE] += (rate_value[iRATE][i] - previous_rate[iRATE])
                for iRATE in range(0, SHMSNRATE):
                    SHMS_rate_sum[iRATE] += (SHMS_rate_value[iRATE][i] - SHMS_previous_rate[iRATE])
            previous_acctrig = (acctrig_value[i] - EDTM_current)
            previous_EDTM = EDTM_value[i]
            for itrig in range(0, NTRIG):
                previous_trig[itrig] = trig_value[itrig][i]
            for iPRE in range(0, NPRE):
                previous_PRE[iPRE] = PRE_value[iPRE][i]
                SHMS_previous_PRE[iPRE] = SHMS_PRE_value[iPRE][i]
            for iRATE in range(0, NRATE):
                previous_rate[iRATE] = rate_value[iRATE][i]
            for iRATE in range(0, SHMSNRATE):
                SHMS_previous_rate[iRATE] = SHMS_rate_value[iRATE][i]
            previous_time[ibcm] = time_value[i]
            previous_charge[ibcm] = bcm_value[ibcm][i]

    if PS1 == 0 :
        scalers = {
            "run number" : runNum,
            "ps1" : PS1,
            "ps3" : PS3,
            "time": time_sum[1],
            "charge": charge_sum[1],
            "TRIG1_scaler": trig_sum[0],
            "TRIG3_scaler": trig_sum[2],
            "CPULT_scaler": acctrig_sum/(trig_sum[2]/PS3),
            "CPULT_scaler_uncern": (acctrig_sum/((trig_sum[2]/PS3)))*np.sqrt((1/(trig_sum[2]/PS3))+(1/acctrig_sum)),
            "HMS_eLT": 1 - ((6/5)*(PRE_sum[1]-PRE_sum[2])/(PRE_sum[1])),
            "HMS_eLT_uncern": (PRE_sum[1]-PRE_sum[2])/(PRE_sum[1])*np.sqrt((np.sqrt(PRE_sum[1]) + np.sqrt(PRE_sum[2]))/(PRE_sum[1] - PRE_sum[2]) + (np.sqrt(PRE_sum[1])/PRE_sum[1])),
            "SHMS_eLT": 0,
            "SHMS_eLT_uncern": 0,
            "sent_edtm": EDTM_sum

        }
    elif PS3==0 :
        scalers = {
            "run number" : runNum,
            "ps1" : PS1,
            "ps3" : PS3,
            "time": time_sum[1],
            "charge": charge_sum[1],
            "TRIG1_scaler": trig_sum[0],
            "TRIG3_scaler": trig_sum[2],
            "CPULT_scaler": acctrig_sum/((trig_sum[0]/PS1)),
            "CPULT_scaler_uncern": (acctrig_sum/((trig_sum[0]/PS1))*np.sqrt((1/(trig_sum[0]/PS1)))+(1/acctrig_sum)),
            "HMS_eLT": 0,
            "HMS_eLT_uncern": 0,
            "SHMS_eLT": 1 - ((6/5)*(SHMS_PRE_sum[1]-SHMS_PRE_sum[2])/(SHMS_PRE_sum[1])),
            "SHMS_eLT_uncern": (SHMS_PRE_sum[1]-SHMS_PRE_sum[2])/(SHMS_PRE_sum[1])*np.sqrt((np.sqrt(SHMS_PRE_sum[1]) + np.sqrt(SHMS_PRE_sum[2]))/(SHMS_PRE_sum[1] - SHMS_PRE_sum[2]) + (np.sqrt(SHMS_PRE_sum[1])/SHMS_PRE_sum[1])),
            "sent_edtm": EDTM_sum

        }

    else:
        scalers = {
            "run number" : runNum,
            "ps1" : PS1,
            "ps3" : PS3,
            "time": time_sum[1],
            "charge": charge_sum[1],
            "TRIG1_scaler": trig_sum[0],
            "TRIG3_scaler": trig_sum[2],
            "CPULT_scaler": acctrig_sum/((trig_sum[0]/PS1) + (trig_sum[2]/PS3)),
            "CPULT_scaler_uncern": (acctrig_sum/((trig_sum[0]/PS1) + (trig_sum[2]/PS3)))*np.sqrt((1/(trig_sum[0]/PS1))+(1/(trig_sum[2]/PS3))+(1/acctrig_sum)),
            "HMS_eLT": 1 - ((6/5)*(PRE_sum[1]-PRE_sum[2])/(PRE_sum[1])),
            "HMS_eLT_uncern": (PRE_sum[1]-PRE_sum[2])/(PRE_sum[1])*np.sqrt((np.sqrt(PRE_sum[1]) + np.sqrt(PRE_sum[2]))/(PRE_sum[1] - PRE_sum[2]) + (np.sqrt(PRE_sum[1])/PRE_sum[1])),
            "SHMS_eLT": 1 - ((6/5)*(SHMS_PRE_sum[1]-SHMS_PRE_sum[2])/(SHMS_PRE_sum[1])),
            "SHMS_eLT_uncern": (SHMS_PRE_sum[1]-SHMS_PRE_sum[2])/(SHMS_PRE_sum[1])*np.sqrt((np.sqrt(SHMS_PRE_sum[1]) + np.sqrt(SHMS_PRE_sum[2]))/(SHMS_PRE_sum[1] - SHMS_PRE_sum[2]) + (np.sqrt(SHMS_PRE_sum[1])/SHMS_PRE_sum[1])),
            "sent_edtm": EDTM_sum
            
        }


    print("Using prescale factors: PS1 %.0f, PS3 %.0f\n" % (PS1, PS3))
    print("\n\nUsed current threshold value: %.2f uA" % thres_curr)

    for ibcm in range(0, NBCM):
        print("%s charge: %.3f uC, Beam over threshold for %.3f s" %
              (bcm_name[ibcm], charge_sum[ibcm], time_sum[ibcm]))

    print("\n\n")

    print("L1ACC counts: %.0f, \n%s Prescaled Pretrigger Counts: %.0f \n%s Prescaled Pretrigger Counts: %.0f \nComputer Livetime: %f +/- %f" %
          (acctrig_sum, trig_name[0], scalers["TRIG1_scaler"], trig_name[2], scalers["TRIG3_scaler"], scalers["CPULT_scaler"], scalers["CPULT_scaler_uncern"]))

    print("HMS Electronic livetime: %f +/- %f" %
          (scalers["HMS_eLT"], scalers["HMS_eLT_uncern"]))

    print("SHMS Electronic livetime: %f +/- %f" %
          (scalers["SHMS_eLT"], scalers["SHMS_eLT_uncern"]))

    print("EDTM Events: %.0f" % scalers["sent_edtm"])

    return scalers


'''
ANALYSIS TREE, T
'''

tree = up.open(rootName)["T"]
branch = klt.pyBranch(tree)

H_cal_etotnorm = tree.array("H.cal.etotnorm")
H_cer_npeSum = tree.array("H.cer.npeSum")
H_gtr_dp = tree.array("H.gtr.dp")
H_tr_tg_th = tree.array("H.gtr.th")
H_tr_tg_ph = tree.array("H.gtr.ph")
H_gtr_beta = tree.array("H.gtr.beta")
H_tr_chi2 = tree.array("H.tr.chi2")
H_tr_ndof = tree.array("H.tr.ndof")
H_hod_goodscinhit = tree.array("H.hod.goodscinhit")
H_hod_betanotrack = tree.array("H.hod.betanotrack")
H_hod_goodstarttime = tree.array("H.hod.goodstarttime")
H_dc_ntrack = tree.array("H.dc.ntrack")

H_dc_1x1_nhit = tree.array("H.dc.1x1.nhit")
H_dc_1u2_nhit = tree.array("H.dc.1u2.nhit")
H_dc_1u1_nhit = tree.array("H.dc.1u1.nhit")
H_dc_1v1_nhit = tree.array("H.dc.1v1.nhit")
H_dc_1x2_nhit = tree.array("H.dc.1x2.nhit")
H_dc_1v2_nhit = tree.array("H.dc.1v2.nhit")
H_dc_2x1_nhit = tree.array("H.dc.2x1.nhit")
H_dc_2u2_nhit = tree.array("H.dc.2u2.nhit")
H_dc_2u1_nhit = tree.array("H.dc.2u1.nhit")
H_dc_2v1_nhit = tree.array("H.dc.2v1.nhit")
H_dc_2x2_nhit = tree.array("H.dc.2x2.nhit")
H_dc_2v2_nhit = tree.array("H.dc.2v2.nhit")

W = tree.array("H.kin.primary.W")
P_cal_etotnorm = tree.array("P.cal.etotnorm")
P_hgcer_npeSum = tree.array("P.hgcer.npeSum")
P_aero_npeSum = tree.array("P.aero.npeSum")
P_gtr_dp = tree.array("P.gtr.dp")
P_gtr_th = tree.array("P.gtr.th")
P_gtr_ph = tree.array("P.gtr.ph")
P_gtr_beta = tree.array("P.gtr.beta")
P_tr_chi2 = tree.array("P.tr.chi2")
P_tr_ndof = tree.array("P.tr.ndof")
P_hod_goodscinhit = tree.array("P.hod.goodscinhit")
P_hod_betanotrack = tree.array("P.hod.betanotrack")
P_hod_goodstarttime = tree.array("P.hod.goodstarttime")
P_dc_ntrack = tree.array("P.dc.ntrack")

P_dc_1x1_nhit = tree.array("P.dc.1x1.nhit")
P_dc_1u2_nhit = tree.array("P.dc.1u2.nhit")
P_dc_1u1_nhit = tree.array("P.dc.1u1.nhit")
P_dc_1v1_nhit = tree.array("P.dc.1v1.nhit")
P_dc_1x2_nhit = tree.array("P.dc.1x2.nhit")
P_dc_1v2_nhit = tree.array("P.dc.1v2.nhit")
P_dc_2x1_nhit = tree.array("P.dc.2x1.nhit")
P_dc_2u2_nhit = tree.array("P.dc.2u2.nhit")
P_dc_2u1_nhit = tree.array("P.dc.2u1.nhit")
P_dc_2v1_nhit = tree.array("P.dc.2v1.nhit")
P_dc_2x2_nhit = tree.array("P.dc.2x2.nhit")
P_dc_2v2_nhit = tree.array("P.dc.2v2.nhit")

# H_bcm_bcm4a_AvgCurrent = tree.array("H.bcm.bcm4b.AvgCurrent")
H_bcm_bcm4a_AvgCurrent = np.full(len(W),np.average(P_BCM4A_scalerCharge))

T_coin_pTRIG1_ROC1_tdcTime = tree.array("T.coin.pTRIG1_ROC1_tdcTime")
T_coin_pTRIG3_ROC1_tdcTime = tree.array("T.coin.pTRIG3_ROC1_tdcTime")
T_coin_pTRIG5_ROC1_tdcTime = tree.array("T.coin.pTRIG5_ROC1_tdcTime")
T_coin_pTRIG1_ROC2_tdcTime = tree.array("T.coin.pTRIG1_ROC2_tdcTime")
T_coin_pTRIG3_ROC2_tdcTime = tree.array("T.coin.pTRIG3_ROC2_tdcTime")
T_coin_pTRIG5_ROC2_tdcTime = tree.array("T.coin.pTRIG5_ROC2_tdcTime")

T_coin_pEDTM_tdcTime = tree.array("T.coin.pEDTM_tdcTime")

EvtType = tree.array("fEvtHdr.fEvtType")

fout = REPLAYPATH+'/UTIL_KAONLT/DB/CUTS/run_type/lumi.cuts'

# read in cuts file and make dictionary
c = klt.pyPlot(REPLAYPATH)
# apply RF cuts to timing cuts file
c.cut_RF(runNum,MaxEvent)
readDict = c.read_dict(fout,runNum)

# This method calls several methods in kaonlt package. It is required to create properly formated
# dictionaries. The evaluation must be in the analysis script because the analysis variables (i.e. the
# leaves of interest) are not defined in the kaonlt package. This makes the system more flexible
# overall, but a bit more cumbersome in the analysis script. Perhaps one day a better solution will be
# implimented.
def make_cutDict(cut,inputDict=None):

    global c

    c = klt.pyPlot(REPLAYPATH,readDict)
    x = c.w_dict(cut)
    # print("%s" % cut)
    # print("x ", x)
    
    if inputDict == None:
        inputDict = {}
        
    for key,val in readDict.items():
        if key == cut:
            inputDict.update({key : {}})

    for i,val in enumerate(x):
        tmp = x[i]
        if tmp == "":
            continue
        else:
            inputDict[cut].update(eval(tmp))
        
    return inputDict

cutDict = make_cutDict("p_track_lumi_before")
cutDict = make_cutDict("p_hadtrack_lumi_before",cutDict)
cutDict = make_cutDict("p_pitrack_lumi_before",cutDict)
cutDict = make_cutDict("p_ktrack_lumi_before",cutDict)
cutDict = make_cutDict("p_ptrack_lumi_before",cutDict)
cutDict = make_cutDict("p_track_lumi_after",cutDict)
cutDict = make_cutDict("p_hadtrack_lumi_after",cutDict)
cutDict = make_cutDict("p_pitrack_lumi_after",cutDict)
cutDict = make_cutDict("p_ktrack_lumi_after",cutDict)
cutDict = make_cutDict("p_ptrack_lumi_after",cutDict)
cutDict = make_cutDict("p_etrack_lumi_before",cutDict)
cutDict = make_cutDict("p_etrack_lumi_after",cutDict)
cutDict = make_cutDict("p_pcut_lumi_eff",cutDict)
cutDict = make_cutDict("h_track_lumi_before",cutDict)
cutDict = make_cutDict("h_etrack_lumi_before",cutDict)
cutDict = make_cutDict("h_track_lumi_after",cutDict)
cutDict = make_cutDict("h_etrack_lumi_after",cutDict)
cutDict = make_cutDict("h_etrack_lumi_after",cutDict)
cutDict = make_cutDict("h_ecut_lumi_eff",cutDict)
cutDict = make_cutDict("h_cal",cutDict)
cutDict = make_cutDict("h_cer",cutDict)
cutDict = make_cutDict("p_cal",cutDict)
cutDict = make_cutDict("p_hgcer",cutDict)
cutDict = make_cutDict("p_aero",cutDict)
cutDict = make_cutDict("c_noedtm",cutDict)
cutDict = make_cutDict("c_edtm",cutDict)
c = klt.pyPlot(REPLAYPATH,cutDict)

def pid_cuts():

    f = plt.figure(figsize=(11.69,8.27))
    ax = f.add_subplot(231)
    ax.hist(H_cal_etotnorm,bins=c.setbin(H_cal_etotnorm,200),label='no cut',histtype='step',
            alpha=0.5, stacked=True, fill=True)
    ax.hist(c.add_cut(H_cal_etotnorm,"h_cal"),
             bins=c.setbin(c.add_cut(H_cal_etotnorm,"h_cal"),200),label='no cut',histtype='step', alpha=0.5, stacked=True, fill=True)
    plt.yscale('log')
    plt.xlabel('H_cal_etotnorm')
    plt.ylabel('Count')

    ax = f.add_subplot(232)
    ax.hist(H_cer_npeSum,bins=c.setbin(H_cer_npeSum,200),label='no cut',histtype='step', alpha=0.5,
            stacked=True, fill=True)
    ax.hist(c.add_cut(H_cer_npeSum,"h_cer"),
            bins=c.setbin(c.add_cut(H_cer_npeSum,"h_cer"),200),label='no cut',histtype='step', alpha=0.5, stacked=True, fill=True)
    plt.yscale('log')
    plt.xlabel('H_cer_npeSum')
    plt.ylabel('Count')

    ax = f.add_subplot(233)
    ax.hist(P_cal_etotnorm,bins=c.setbin(P_cal_etotnorm,200),label='no cut',histtype='step',
            alpha=0.5, stacked=True, fill=True)
    ax.hist(c.add_cut(P_cal_etotnorm,"p_cal"),
             bins=c.setbin(c.add_cut(P_cal_etotnorm,"p_cal"),200),label='no cut',histtype='step', alpha=0.5, stacked=True, fill=True)
    plt.yscale('log')
    plt.xlabel('P_cal_etotnorm')
    plt.ylabel('Count')

    ax = f.add_subplot(234)
    ax.hist(P_hgcer_npeSum,bins=c.setbin(P_hgcer_npeSum,200),label='no cut',histtype='step',
            alpha=0.5, stacked=True, fill=True)
    ax.hist(c.add_cut(P_hgcer_npeSum,"p_hgcer"),
             bins=c.setbin(c.add_cut(P_hgcer_npeSum,"p_hgcer"),200),label='no cut',histtype='step', alpha=0.5, stacked=True, fill=True)
    plt.yscale('log')
    plt.xlabel('P_hgcer_npeSum')
    plt.ylabel('Count')

    ax = f.add_subplot(235)
    ax.hist(P_aero_npeSum,bins=c.setbin(P_aero_npeSum,200),label='no cut',histtype='step',
            alpha=0.5, stacked=True, fill=True)
    ax.hist(c.add_cut(P_aero_npeSum,"p_aero"),
             bins=c.setbin(c.add_cut(P_aero_npeSum,"p_aero"),200),label='no cut',histtype='step', alpha=0.5, stacked=True, fill=True)
    plt.yscale('log')
    plt.xlabel('P_aero_npeSum')
    plt.ylabel('Count')    
    
def analysis(PS1, PS3, thres_curr):
    
    bcm_before = H_bcm_bcm4a_AvgCurrent
    bcm_after = [x for x in H_bcm_bcm4a_AvgCurrent if x > thres_curr ]

    # EDTM = [x
    #         for x,bcm in zip(T_coin_pEDTM_tdcTime,bcm_after)
    #         if bcm > thres_curr
    #         if x != 0.0]

    EDTM = c.add_cut(T_coin_pEDTM_tdcTime,"c_edtm")
    
    TRIG1 = [x
             for x,bcm in zip(T_coin_pTRIG1_ROC2_tdcTime,bcm_after)
             if bcm > thres_curr             
             if x != 0.0]
    TRIG3 = [x
             for x,bcm in zip(T_coin_pTRIG3_ROC1_tdcTime,bcm_after)
             if bcm > thres_curr
             if x !=0.0]
    TRIG5 = [x
             for x,bcm in zip(T_coin_pTRIG5_ROC2_tdcTime,bcm_after)
             if bcm > thres_curr
             if x !=0.0]
    
    EventType = [x
             for x,bcm in zip(EvtType,bcm_after)
             if bcm > thres_curr]

    TRIG1_cut = [trig1
                 for (trig1,evt,bcm) in zip(T_coin_pTRIG1_ROC2_tdcTime,EvtType,bcm_after)
                 if bcm > thres_curr
                 if evt == 1]
    
    # p_track_lumi_before
    p_track_lumi_before = c.add_cut(P_dc_ntrack,"p_track_lumi_before")
    
    # p_hadtrack_lumi_before
    p_hadtrack_lumi_before = c.add_cut(P_dc_ntrack,"p_hadtrack_lumi_before")

    # p_pitrack_lumi_before
    p_pitrack_lumi_before = c.add_cut(P_dc_ntrack,"p_pitrack_lumi_before")

    # p_ktrack_lumi_before
    p_ktrack_lumi_before = c.add_cut(P_dc_ntrack,"p_ktrack_lumi_before")

    # p_ptrack_lumi_before
    p_ptrack_lumi_before = c.add_cut(P_dc_ntrack,"p_ptrack_lumi_before")

    # p_track_lumi_after
    p_track_lumi_after = c.add_cut(P_dc_ntrack,"p_track_lumi_after")

    # p_hadtrack_lumi_after
    p_hadtrack_lumi_after = c.add_cut(P_dc_ntrack,"p_hadtrack_lumi_after")

    # p_pitrack_lumi_after
    p_pitrack_lumi_after = c.add_cut(P_dc_ntrack,"p_pitrack_lumi_after")

    # p_ktrack_lumi_after
    p_ktrack_lumi_after = c.add_cut(P_dc_ntrack,"p_ktrack_lumi_after")

    # p_ptrack_lumi_after
    p_ptrack_lumi_after = c.add_cut(P_dc_ntrack,"p_ptrack_lumi_after")

    # p_etrack_lumi_before
    p_etrack_lumi_before = c.add_cut(P_hgcer_npeSum,"p_etrack_lumi_before")

    # p_show_before
    p_show_before = c.add_cut(P_cal_etotnorm,"p_etrack_lumi_before")

    # p_etrack_lumi_after
    p_etrack_lumi_after  = c.add_cut(P_hgcer_npeSum,"p_etrack_lumi_after")

    # p_pcut_lumi_eff
    p_pcut_lumi_eff  = c.add_cut(P_hgcer_npeSum,"p_pcut_lumi_eff")

    # p_show_after
    p_show_after  = c.add_cut(P_cal_etotnorm,"p_pcut_lumi_eff")

    TRIG3_cut = [ x
                  for (x, evt, bcm ) in zip(T_coin_pTRIG3_ROC1_tdcTime, EvtType, bcm_after)
                  if bcm > thres_curr
                  if evt == 2]

    # h_track_lumi_before
    h_track_lumi_before = c.add_cut(H_dc_ntrack,"h_track_lumi_before")

    # h_etrack_lumi_before
    h_etrack_lumi_before = c.add_cut(H_dc_ntrack,"h_etrack_lumi_before")
    
    # h_track_lumi_after
    h_track_lumi_after = c.add_cut(H_dc_ntrack,"h_track_lumi_after")


    # h_etrack_lumi_after
    h_etrack_lumi_after = c.add_cut(H_dc_ntrack,"h_etrack_lumi_after")    

    # h_etrack_lumi_before
    h_etrack_lumi_before_iterate = [H_cer_npeSum, bcm_after]
    h_etrack_lumi_before = [cer
                      for (cer, bcm) in zip(*h_etrack_lumi_before_iterate)
                      if bcm > thres_curr]

    # h_dp_before
    h_dp_before_iterate = [H_gtr_dp, bcm_after]
    h_dp_before = [h_dp
                      for (h_dp, bcm) in zip(*h_dp_before_iterate)
                      if bcm > thres_curr]

    # h_th_before
    h_th_before_iterate = [H_tr_tg_th, bcm_after]
    h_th_before = [h_th
                      for (h_th, bcm) in zip(*h_th_before_iterate)
                      if bcm > thres_curr]

    # h_ph_before
    h_ph_before_iterate = [H_tr_tg_ph, bcm_after]
    h_ph_before = [h_ph
                      for (h_ph, bcm) in zip(*h_ph_before_iterate)
                      if bcm > thres_curr]

    # h_show_before
    h_show_before_iterate = [H_tr_tg_th, bcm_after]
    h_show_before = [h_caletot
                      for (h_caletot, bcm) in zip(*h_show_before_iterate)
                      if bcm > thres_curr]
    
    # h_etrack_lumi_after
    h_etrack_lumi_after = c.add_cut(H_cer_npeSum,"h_etrack_lumi_after")
    
    # h_dp_after
    h_dp_after = c.add_cut(H_gtr_dp,"h_etrack_lumi_after")
    
    # h_th_after
    h_th_after = c.add_cut(H_tr_tg_th,"h_etrack_lumi_after")
    
    # h_ph_after
    h_ph_after = c.add_cut(H_tr_tg_ph,"h_etrack_lumi_after")
    
    # h_show_after
    h_show_after = c.add_cut(H_cal_etotnorm,"h_etrack_lumi_after")
    
    # h_ecut_lumi_eff
    h_ecut_lumi_eff = c.add_cut(H_cal_etotnorm,"h_ecut_lumi_eff")

    # goodscinhit cut
    h_ecuts_goodscinhit = c.add_cut(H_hod_goodscinhit,"h_ecut_lumi_eff")
    p_pcuts_goodscinhit = c.add_cut(P_hod_goodscinhit,"p_pcut_lumi_eff")
                                                        
    if PS1 == -1 or PS1 == 0:
        track_info = {
            
            "HMS_evts_scalar" : len(h_ecut_lumi_eff),
            "HMS_evts_scalar_uncern" : math.sqrt(len(h_ecut_lumi_eff)),
            "SHMS_evts_scalar" : 0,
            "SHMS_evts_scalar_uncern" : 0,
            "h_int_goodscin_evts" : scipy.integrate.simps(h_ecuts_goodscinhit),
            "p_int_goodscin_evts" : scipy.integrate.simps(p_pcuts_goodscinhit),
            "TRIG1_cut" : len(TRIG1_cut),
            "TRIG3_cut" : len(TRIG3_cut),
            "HMS_track" : len(h_track_lumi_after)/len(h_track_lumi_before),
            "HMS_track_uncern" : (len(h_track_lumi_after)/len(h_track_lumi_before))*math.sqrt((1/len(h_track_lumi_after)) + (1/len(h_track_lumi_before))),
            "etrack" : len(h_etrack_lumi_after)/len(h_etrack_lumi_before),
            "etrack_uncern" : (len(h_etrack_lumi_after)/len(h_etrack_lumi_before))*math.sqrt((1/len(h_etrack_lumi_after)) + (1/len(h_etrack_lumi_before))),
            "SHMS_track" : 0,
            "SHMS_track_uncern" : 0,
            "hadtrack" : 0,
            "hadtrack_uncern" : 0,
            "pitrack" : 0,
            "pitrack_uncern" : 0,
            "Ktrack" : 0,
            "Ktrack_uncern" : 0,
            "ptrack" : 0,
            "ptrack_uncern" : 0,
            "accp_edtm" : (len(EDTM)),
            
        }
    elif PS3 == -1 or PS3 == 0:
        track_info = {
            
            "HMS_evts_scalar" : 0,
            "HMS_evts_scalar_uncern" : 0,
            "SHMS_evts_scalar" : len(p_pcut_lumi_eff),
            "SHMS_evts_scalar_uncern" : math.sqrt(len(p_pcut_lumi_eff)),
            "intW_evts" : scipy.integrate.simps(h_ecut_W),
            "h_int_goodscin_evts" : scipy.integrate.simps(h_ecuts_goodscinhit),
            "p_int_goodscin_evts" : scipy.integrate.simps(p_pcuts_goodscinhit),
            "TRIG1_cut" : len(TRIG1_cut),
            "TRIG3_cut" : len(TRIG3_cut),
            "HMS_track" : 0,
            "HMS_track_uncern" : 0,
            "etrack" : 0,
            "etrack_uncern" : 0,
            "SHMS_track" : len(p_track_lumi_after)/len(p_track_lumi_before),
            "SHMS_track_uncern" : (len(p_track_lumi_after)/len(p_track_lumi_before))*math.sqrt((1/len(p_track_lumi_after)) + (1/len(p_track_lumi_before))),
            "hadtrack" : len(p_hadtrack_lumi_after)/len(p_hadtrack_lumi_before),
            "hadtrack_uncern" : (len(p_hadtrack_lumi_after)/len(p_hadtrack_lumi_before))*math.sqrt((1/len(p_hadtrack_lumi_after)) + (1/len(p_hadtrack_lumi_before))),
            "pitrack" : len(p_pitrack_lumi_after)/len(p_pitrack_lumi_before),
            "pitrack_uncern" : (len(p_pitrack_lumi_after)/len(p_pitrack_lumi_before))*math.sqrt((1/len(p_pitrack_lumi_after)) + (1/len(p_pitrack_lumi_before))),
            "Ktrack" : len(p_ktrack_lumi_after)/len(p_ktrack_lumi_before),
            "Ktrack_uncern" : (len(p_ktrack_lumi_after)/len(p_ktrack_lumi_before))*math.sqrt((1/len(p_ktrack_lumi_after)) + (1/len(p_ktrack_lumi_before))),
            "ptrack" : len(p_ptrack_lumi_after)/len(p_ptrack_lumi_before),
            "ptrack_uncern" : (len(p_ptrack_lumi_after)/len(p_ptrack_lumi_before))*math.sqrt((1/len(p_ptrack_lumi_after)) + (1/len(p_ptrack_lumi_before))),
            "accp_edtm" : (len(EDTM)),

        }
    else:
        track_info = {
            
            "HMS_evts_scalar" : len(h_ecut_lumi_eff),
            "HMS_evts_scalar_uncern" : math.sqrt(len(h_ecut_lumi_eff)),
            "SHMS_evts_scalar" : len(p_pcut_lumi_eff),
            "SHMS_evts_scalar_uncern" : math.sqrt(len(p_pcut_lumi_eff)),
            "h_int_goodscin_evts" : scipy.integrate.simps(h_ecuts_goodscinhit),
            "p_int_goodscin_evts" : scipy.integrate.simps(p_pcuts_goodscinhit),
            "TRIG1_cut" : len(TRIG1_cut),
            "TRIG3_cut" : len(TRIG3_cut),
            "HMS_track" : len(h_track_lumi_after)/len(h_track_lumi_before),
            "HMS_track_uncern" : (len(h_track_lumi_after)/len(h_track_lumi_before))*math.sqrt((1/len(h_track_lumi_after)) + (1/len(h_track_lumi_before))),
            "etrack" : len(h_etrack_lumi_after)/len(h_etrack_lumi_before),
            "etrack_uncern" : (len(h_etrack_lumi_after)/len(h_etrack_lumi_before))*math.sqrt((1/len(h_etrack_lumi_after)) + (1/len(h_etrack_lumi_before))),
            "SHMS_track" : len(p_track_lumi_after)/len(p_track_lumi_before),
            "SHMS_track_uncern" : (len(p_track_lumi_after)/len(p_track_lumi_before))*math.sqrt((1/len(p_track_lumi_after)) + (1/len(p_track_lumi_before))),
            "hadtrack" : len(p_hadtrack_lumi_after)/len(p_hadtrack_lumi_before),
            "hadtrack_uncern" : (len(p_hadtrack_lumi_after)/len(p_hadtrack_lumi_before))*math.sqrt((1/len(p_hadtrack_lumi_after)) + (1/len(p_hadtrack_lumi_before))),
            "pitrack" : len(p_pitrack_lumi_after)/len(p_pitrack_lumi_before),
            "pitrack_uncern" : (len(p_pitrack_lumi_after)/len(p_pitrack_lumi_before))*math.sqrt((1/len(p_pitrack_lumi_after)) + (1/len(p_pitrack_lumi_before))),
            "Ktrack" : len(p_ktrack_lumi_after)/len(p_ktrack_lumi_before),
            "Ktrack_uncern" : (len(p_ktrack_lumi_after)/len(p_ktrack_lumi_before))*math.sqrt((1/len(p_ktrack_lumi_after)) + (1/len(p_ktrack_lumi_before))),
            "ptrack" : len(p_ptrack_lumi_after)/len(p_ptrack_lumi_before),
            "ptrack_uncern" : (len(p_ptrack_lumi_after)/len(p_ptrack_lumi_before))*math.sqrt((1/len(p_ptrack_lumi_after)) + (1/len(p_ptrack_lumi_before))),
            "accp_edtm" : (len(EDTM)),
            
        }

    print("Terminate","Selection rules have been applied, plotting results")
    print("Using prescale factors: PS1 %.0f, PS3 %.0f\n" % (PS1,PS3))
    print("Total number of events: %.0f\n" % (len(EventType)))
    print("Number of EDTM  Events: %.0f\n" % (len(EDTM)))
    print("Number of TRIG1 Events: %.0f\n" % (PS1*scipy.integrate.simps(TRIG1_cut)))
    print("Number of TRIG3 Events: %.0f\n" % (PS3*scipy.integrate.simps(TRIG3_cut)))
    print("Number of TRIG5 Events: %.0f\n\n" % scipy.integrate.simps(TRIG5))

    print("Number of HMS good events: %.0f +/- %.0f " % ((PS3*len(h_ecut_lumi_eff))
                                                         ,math.sqrt(PS3*len(h_ecut_lumi_eff))))
    print("Calculated tracking efficiency: %f +/- %f\n" %
          (len(h_track_lumi_after)/len(h_track_lumi_before),
           (len(h_track_lumi_after)/len(h_track_lumi_before))*math.sqrt((1/len(h_track_lumi_after))
                                                         + (1/len(h_track_lumi_before)))))
    print("Calculated electron tracking efficiency: %f +/- %f\n" %
          (len(h_etrack_lumi_after)/len(h_etrack_lumi_before),
           (len(h_etrack_lumi_after)/len(h_etrack_lumi_before))*math.sqrt((1/len(h_etrack_lumi_after))
                                                           + (1/len(h_etrack_lumi_before)))))
    print("Calculated HMS Cherenkov efficiency: %f +/- %f\n\n" %
          (len(h_ecut_lumi_eff)/len(h_etrack_lumi_after),
           (len(h_ecut_lumi_eff)/len(h_etrack_lumi_after))*math.sqrt((1/len(h_ecut_lumi_eff))
                                                    + (1/len(h_etrack_lumi_after)))))
    print("Number of SHMS good events: %.0f +/- %.0f" % ((PS1*len(p_pcut_lumi_eff)),
                                                         math.sqrt(PS1*len(p_pcut_lumi_eff))))
    print("Calculated tracking efficiency: %f +/- %f\n" %
          (len(p_track_lumi_after)/len(p_track_lumi_before),
           (len(p_track_lumi_after)/len(p_track_lumi_before))*math.sqrt((1/len(p_track_lumi_after))
                                                         + (1/len(p_track_lumi_before)))))
    print("Calculated hadron tracking efficiency: %f +/- %f\n" %
          (len(p_hadtrack_lumi_after)/len(p_hadtrack_lumi_before),
           (len(p_hadtrack_lumi_after)/len(p_hadtrack_lumi_before))*math.sqrt((1/len(p_hadtrack_lumi_after))
                                                               + (1/len(p_hadtrack_lumi_before)))))
    print("Calculated pion tracking efficiency: %f +/- %f\n" %
          (len(p_pitrack_lumi_after)/len(p_pitrack_lumi_before),
           (len(p_pitrack_lumi_after)/len(p_pitrack_lumi_before))*math.sqrt((1/len(p_pitrack_lumi_after))
                                                             + (1/len(p_pitrack_lumi_before)))))
    print("Calculated kaon tracking efficiency: %f +/- %f\n" %
          (len(p_ktrack_lumi_after)/len(p_ktrack_lumi_before),
           (len(p_ktrack_lumi_after)/len(p_ktrack_lumi_before))*math.sqrt((1/len(p_ktrack_lumi_after))
                                                           + (1/len(p_ktrack_lumi_before)))))
    print("Calculated proton tracking efficiency: %f +/- %f\n" %
          (len(p_ptrack_lumi_after)/len(p_ptrack_lumi_before),
           (len(p_ptrack_lumi_after)/len(p_ptrack_lumi_before))*math.sqrt((1/len(p_ptrack_lumi_after))
                                                           + (1/len(p_ptrack_lumi_before)))))
    print("Calculated SHMS Cherenkov efficiency: %f +/- %f\n\n" %
          (len(p_pcut_lumi_eff)/len(p_etrack_lumi_after),
           (len(p_pcut_lumi_eff)/len(p_etrack_lumi_after))*math.sqrt((1/len(p_pcut_lumi_eff))
                                                + (1/len(p_etrack_lumi_after)))))
    print("============================================================================\n\n")
          
    return track_info

def main():

    pid_cuts()
    plt.show()
    
    # combine dictionaries
    scalers = scaler(runNum, PS1, PS3, thres_curr)
    track_info = analysis(PS1, PS3, thres_curr)
    # lumi_data = {**scalers , **track_info} # only python 3.5+

    data = {}
    for d in (scalers, track_info): 
        data.update(d)
    lumi_data = {i : data[i] for i in sorted(data.keys())}

    table  = pd.DataFrame([lumi_data], columns=lumi_data.keys())
    table = table.reindex(sorted(table.columns), axis=1)
    
    file_exists = os.path.isfile(filename)

    if file_exists:
        table.to_csv(filename, index = False, header=False, mode='a',)
    else:
        table.to_csv(filename, index = False, header=True, mode='a',)

if __name__ == '__main__':
    main()
