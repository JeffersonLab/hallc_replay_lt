#! /usr/bin/python

#
# Description:
# ================================================================
# Time-stamp: "2020-04-24 17:41:28 trottar"
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
import sys, math, os, subprocess

sys.path.insert(0, 'python/')
import root2py as r2p

runNum = sys.argv[1]
MaxEvent=sys.argv[2]
# MaxEvent=50000

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
rootName = "%s/UTIL_KAONLT/ROOTfiles/lumi_coin_offline_%s_%s.root" % (REPLAYPATH,runNum,MaxEvent)
report = "/u/group/c-kaonlt/USERS/%s/kaonlt/REPORT_OUTPUT/lumi_coin_offline_%s_%s.report" % (USER[1],runNum,MaxEvent)

thres_curr = 2.5

f = open(report)

psList = ['Ps1_factor','Ps3_factor','Ps5_factor']

psActual = [-1,1,2,3,5,9,17,33,65,129,257,513,1025,2049,4097,8193,16385,32769]
psValue = [-1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16]


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
ps1=int(ps1_tmp[1])
ps3=int(ps3_tmp[1])
ps5=int(ps5_tmp[1])

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

s_tree = up.open(rootName)["TSH"]
s_branch = r2p.pyBranch(s_tree)

H_BCM4A_scalerCharge = s_tree.array("H.BCM4A.scalerCharge")
H_BCM2_scalerCharge = s_tree.array("H.BCM2.scalerCharge")
H_BCM4B_scalerCharge = s_tree.array("H.BCM4B.scalerCharge")
H_BCM1_scalerCharge = s_tree.array("H.BCM1.scalerCharge")
H_BCM4C_scalerCharge = s_tree.array("H.BCM4C.scalerCharge")

H_1Mhz_scalerTime = s_tree.array("H.1MHz.scalerTime")

H_hTRIG1_scaler = s_tree.array("H.pTRIG1.scaler")
H_hTRIG2_scaler = s_tree.array("H.pTRIG2.scaler")
H_hTRIG3_scaler = s_tree.array("H.pTRIG3.scaler")
H_hTRIG4_scaler = s_tree.array("H.pTRIG4.scaler")
H_hTRIG5_scaler = s_tree.array("H.pTRIG5.scaler")
H_hTRIG6_scaler = s_tree.array("H.pTRIG6.scaler")

H_hL1ACCP_scaler = s_tree.array("H.hL1ACCP.scaler")
H_hPRE40_scaler = s_tree.array("H.hPRE40.scaler")
H_hPRE100_scaler = s_tree.array("H.hPRE100.scaler")
H_hPRE150_scaler = s_tree.array("H.hPRE150.scaler")
H_hPRE200_scaler = s_tree.array("H.hPRE200.scaler")
H_pPRE40_scaler = s_tree.array("H.pPRE40.scaler")
H_pPRE100_scaler = s_tree.array("H.pPRE100.scaler")
H_pPRE150_scaler = s_tree.array("H.pPRE150.scaler")
H_pPRE200_scaler = s_tree.array("H.pPRE200.scaler")

H_hEL_LO_LO_scaler = s_tree.array("H.hEL_LO_LO.scaler")
H_hEL_LO_scaler = s_tree.array("H.hEL_LO.scaler")
H_hEL_HI_scaler = s_tree.array("H.hEL_HI.scaler")
H_hEL_REAL_scaler = s_tree.array("H.hEL_REAL.scaler")
H_hEL_CLEAN_scaler = s_tree.array("H.hEL_CLEAN.scaler")
H_hSTOF_scaler = s_tree.array("H.hSTOF.scaler")

H_pEL_LO_LO_scaler = s_tree.array("H.pEL_LO_LO.scaler")
H_pEL_LO_scaler = s_tree.array("H.pEL_LO.scaler")
H_pEL_HI_scaler = s_tree.array("H.pEL_HI.scaler")
H_pEL_REAL_scaler = s_tree.array("H.pEL_REAL.scaler")
H_pEL_CLEAN_scaler = s_tree.array("H.pEL_CLEAN.scaler")
H_pSTOF_scaler = s_tree.array("H.pSTOF.scaler")
H_pPRHI_scaler = s_tree.array("H.PRHI.scaler")
H_pPRLO_scaler = s_tree.array("H.PRLO.scaler")

H_EDTM_scaler = s_tree.array("H.EDTM.scaler")


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

    bcm_value = [H_BCM1_scalerCharge, H_BCM2_scalerCharge,
                 H_BCM4A_scalerCharge, H_BCM4B_scalerCharge, H_BCM4C_scalerCharge]

    trig_value = [H_hTRIG1_scaler, H_hTRIG2_scaler, H_hTRIG3_scaler,
                  H_hTRIG4_scaler, H_hTRIG5_scaler, H_hTRIG6_scaler]

    acctrig_value = H_hL1ACCP_scaler

    PRE_value = [H_hPRE40_scaler, H_hPRE100_scaler,
                 H_hPRE150_scaler, H_hPRE200_scaler]

    SHMS_PRE_value = [H_pPRE40_scaler, H_pPRE100_scaler,
                      H_pPRE150_scaler, H_pPRE200_scaler]

    rate_value = [H_hEL_LO_LO_scaler, H_hEL_LO_scaler, H_hEL_HI_scaler,
                  H_hEL_REAL_scaler, H_hEL_CLEAN_scaler, H_hSTOF_scaler]

    SHMS_rate_value = [H_pEL_LO_LO_scaler, H_pEL_LO_scaler, H_pEL_HI_scaler,
                       H_pEL_REAL_scaler, H_pEL_CLEAN_scaler, H_pSTOF_scaler, H_pPRHI_scaler, H_pPRLO_scaler]

    EDTM_value = H_EDTM_scaler

    # Variables useful in Process
    # To find total charge
    name = [0]*NBCM
    charge_sum = [0]*NBCM
    time_sum = [0]*NBCM
    time_total = 0
    previous_charge = [0]*NBCM
    # previous_time = 0
    previous_time = [0]*NBCM
    current_I = 0
    current_time = 0
    Current = 0

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

    for ibcm in range(0, 5):
        current_I = 0
        for i, evt in enumerate(H_1Mhz_scalerTime):
            if (evt != previous_time[ibcm]):
                current_I = (
                    bcm_value[ibcm][i] - previous_charge[ibcm])/(evt - previous_time[ibcm])
            if (current_I > thres_curr):
                charge_sum[ibcm] += (bcm_value[ibcm][i] -
                                     previous_charge[ibcm])
                time_sum[ibcm] += (evt - previous_time[ibcm])
            if (ibcm == 3 and (current_I > thres_curr)):
                EDTM_current = (EDTM_value - previous_EDTM)
                EDTM_sum += EDTM_current
                acctrig_sum += ((acctrig_value - EDTM_current) -
                                previous_acctrig)
                for itrig in range(0, NTRIG):
                    trig_sum[itrig] += (trig_value[itrig] -
                                        previous_trig[itrig])
                for iPRE in range(0, NPRE):
                    PRE_sum[iPRE] += (PRE_value[iPRE] - previous_PRE[iPRE])
                    SHMS_PRE_sum[iPRE] += (SHMS_PRE_value[iPRE] -
                                           SHMS_previous_PRE[iPRE])
                for iRATE in range(0, NRATE):
                    rate_sum[iRATE] += (rate_value[iRATE] -
                                        previous_rate[iRATE])
                for iRATE in range(0, SHMSNRATE):
                    SHMS_rate_sum[iRATE] += (SHMS_rate_value[iRATE] -
                                             SHMS_previous_rate[iRATE])
                previous_acctrig = (acctrig_value - EDTM_current)
                previous_EDTM = EDTM_value
                for itrig in range(0, NTRIG):
                    previous_trig[itrig] = trig_value[itrig]
                for iPRE in range(0, NPRE):
                    previous_PRE[iPRE] = PRE_value[iPRE]
                    SHMS_previous_PRE[iPRE] = SHMS_PRE_value[iPRE]
                for iRATE in range(0, NRATE):
                    previous_rate[iRATE] = rate_value[iRATE]
                for iRATE in range(0, SHMSNRATE):
                    SHMS_previous_rate[iRATE] = SHMS_rate_value[iRATE]
        time_total += (evt - previous_time[ibcm])
        previous_time[ibcm] = evt
        previous_charge[ibcm] = bcm_value[ibcm][i]

    if PS1 == 0 :
        scalers = {
            "run number" : runNum,
            "ps1" : PS1,
            "ps3" : PS3,
            "time": time_sum[3],
            "charge": charge_sum[3],
            "TRIG1_scaler": sum(trig_sum[0]),
            "TRIG3_scaler": sum(trig_sum[2]),
            "CPULT_scaler": 1-sum(acctrig_sum)/(sum(trig_sum[2])/PS3),
            "CPULT_scaler_uncern": (sum(acctrig_sum)/((sum(trig_sum[2])/PS3)))*np.sqrt((1/(sum(trig_sum[2])/PS3))+(1/sum(acctrig_sum))),
            "HMS_eLT": 1 - ((6/5)*(sum(PRE_sum[1])-sum(PRE_sum[2]))/(sum(PRE_sum[1]))),
            "HMS_eLT_uncern": (sum(PRE_sum[1])-sum(PRE_sum[2]))/(sum(PRE_sum[1]))*np.sqrt((np.sqrt(sum(PRE_sum[1])) + np.sqrt(sum(PRE_sum[2])))/(sum(PRE_sum[1]) - sum(PRE_sum[2])) + (np.sqrt(sum(PRE_sum[1]))/sum(PRE_sum[1]))),
            "SHMS_eLT": 0,
            "SHMS_eLT_uncern": 0,
            "sent_edtm": sum(EDTM_sum)

        }
    elif PS3==0 :
        scalers = {
            "run number" : runNum,
            "ps1" : PS1,
            "ps3" : PS3,
            "time": time_sum[3],
            "charge": charge_sum[3],
            "TRIG1_scaler": sum(trig_sum[0]),
            "TRIG3_scaler": sum(trig_sum[2]),
            "CPULT_scaler": 1-sum(acctrig_sum)/((sum(trig_sum[0])/PS1)),
            "CPULT_scaler_uncern": (sum(acctrig_sum)/((sum(trig_sum[0])/PS1))*np.sqrt((1/(sum(trig_sum[0])/PS1)))+(1/sum(acctrig_sum))),
            "HMS_eLT": 0,
            "HMS_eLT_uncern": 0,
            "SHMS_eLT": 1 - ((6/5)*(sum(SHMS_PRE_sum[1])-sum(SHMS_PRE_sum[2]))/(sum(SHMS_PRE_sum[1]))),
            "SHMS_eLT_uncern": (sum(SHMS_PRE_sum[1])-sum(SHMS_PRE_sum[2]))/(sum(SHMS_PRE_sum[1]))*np.sqrt((np.sqrt(sum(SHMS_PRE_sum[1])) + np.sqrt(sum(SHMS_PRE_sum[2])))/(sum(SHMS_PRE_sum[1]) - sum(SHMS_PRE_sum[2])) + (np.sqrt(sum(SHMS_PRE_sum[1]))/sum(SHMS_PRE_sum[1]))),
            "sent_edtm": sum(EDTM_sum)

        }

    else:
        scalers = {
            "run number" : runNum,
            "ps1" : PS1,
            "ps3" : PS3,
            "time": time_sum[3],
            "charge": charge_sum[3],
            "TRIG1_scaler": sum(trig_sum[0]),
            "TRIG3_scaler": sum(trig_sum[2]),
            "CPULT_scaler": 1-sum(acctrig_sum)/((sum(trig_sum[0])/PS1) + (sum(trig_sum[2])/PS3)),
            "CPULT_scaler_uncern": (sum(acctrig_sum)/((sum(trig_sum[0])/PS1) + (sum(trig_sum[2])/PS3)))*np.sqrt((1/(sum(trig_sum[0])/PS1))+(1/(sum(trig_sum[2])/PS3))+(1/sum(acctrig_sum))),
            "HMS_eLT": 1 - ((6/5)*(sum(PRE_sum[1])-sum(PRE_sum[2]))/(sum(PRE_sum[1]))),
            "HMS_eLT_uncern": (sum(PRE_sum[1])-sum(PRE_sum[2]))/(sum(PRE_sum[1]))*np.sqrt((np.sqrt(sum(PRE_sum[1])) + np.sqrt(sum(PRE_sum[2])))/(sum(PRE_sum[1]) - sum(PRE_sum[2])) + (np.sqrt(sum(PRE_sum[1]))/sum(PRE_sum[1]))),
            "SHMS_eLT": 1 - ((6/5)*(sum(SHMS_PRE_sum[1])-sum(SHMS_PRE_sum[2]))/(sum(SHMS_PRE_sum[1]))),
            "SHMS_eLT_uncern": (sum(SHMS_PRE_sum[1])-sum(SHMS_PRE_sum[2]))/(sum(SHMS_PRE_sum[1]))*np.sqrt((np.sqrt(sum(SHMS_PRE_sum[1])) + np.sqrt(sum(SHMS_PRE_sum[2])))/(sum(SHMS_PRE_sum[1]) - sum(SHMS_PRE_sum[2])) + (np.sqrt(sum(SHMS_PRE_sum[1]))/sum(SHMS_PRE_sum[1]))),
            "sent_edtm": sum(EDTM_sum)
            
        }


    print("Using prescale factors: PS1 %.0f, PS3 %.0f\n" % (PS1, PS3))
    print("\n\nUsed current threshold value: %.2f uA" % thres_curr)

    for ibcm in range(0, NBCM):
        print("%s charge: %.3f uC, Beam over threshold for %.3f s" %
              (bcm_name[ibcm], charge_sum[ibcm], time_sum[ibcm]))

    print("\n\n")

    print("L1ACC counts: %.0f, \n%s Prescaled Pretrigger Counts: %.0f \n%s Prescaled Pretrigger Counts: %.0f \nComputer Livetime: %f +/- %f" %
          (sum(acctrig_sum), trig_name[0], scalers["TRIG1_scaler"], trig_name[2], scalers["TRIG3_scaler"], scalers["CPULT_scaler"], scalers["CPULT_scaler_uncern"]))

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
branch = r2p.pyBranch(tree)

H_cal_etotnorm = tree.array("H.cal.etotnorm")
H_cer_npeSum = tree.array("H.cer.npeSum")
H_gtr_dp = tree.array("H.gtr.dp")
H_tr_tg_th = tree.array("H.gtr.th")
H_tr_tg_ph = tree.array("H.gtr.ph")
H_tr_beta = tree.array("H.tr.beta")
H_tr_chi2 = tree.array("H.tr.chi2")
H_tr_ndof = tree.array("H.tr.ndof")
H_hod_goodscinhit = tree.array("H.hod.goodscinhit")
H_hod_betanotrack = tree.array("H.hod.betanotrack")
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

P_cal_etotnorm = tree.array("P.cal.etotnorm")
P_hgcer_npeSum = tree.array("P.hgcer.npeSum")
P_aero_npeSum = tree.array("P.aero.npeSum")
P_gtr_dp = tree.array("P.gtr.dp")
P_gtr_th = tree.array("P.gtr.th")
P_gtr_ph = tree.array("P.gtr.ph")
P_tr_beta = tree.array("P.tr.beta")
P_tr_chi2 = tree.array("P.tr.chi2")
P_tr_ndof = tree.array("P.tr.ndof")
P_hod_goodscinhit = tree.array("P.hod.goodscinhit")
P_hod_betanotrack = tree.array("P.hod.betanotrack")
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

H_bcm_bcm4b_AvgCurrent = tree.array("H.bcm.bcm4b.AvgCurrent")

T_coin_pTRIG1_ROC1_tdcTime = tree.array("T.coin.pTRIG1_ROC1_tdcTime")
T_coin_pTRIG3_ROC1_tdcTime = tree.array("T.coin.pTRIG3_ROC1_tdcTime")
T_coin_pTRIG5_ROC1_tdcTime = tree.array("T.coin.pTRIG5_ROC1_tdcTime")
T_coin_pTRIG1_ROC2_tdcTime = tree.array("T.coin.pTRIG1_ROC2_tdcTime")
T_coin_pTRIG3_ROC2_tdcTime = tree.array("T.coin.pTRIG3_ROC2_tdcTime")
T_coin_pTRIG5_ROC2_tdcTime = tree.array("T.coin.pTRIG5_ROC2_tdcTime")

T_coin_pEDTM_tdcTime = tree.array("T.coin.pEDTM_tdcTime")

EvtType = tree.array("fEvtHdr.fEvtType")

cutDict = {
    "p_track_before" :
    {
        '{"H_bcm_bcm4b_AvgCurrent" : (H_bcm_bcm4b_AvgCurrent > thres_curr)}',        
        '{"P_hod_goodscinhit" : (P_hod_goodscinhit == 0)}',
        '{"P_hod_betanotrack" : ((P_hod_betanotrack > 0.5) & (P_hod_betanotrack < 1.4))}',
        '{"P_dc_1*_nhit" : ((P_dc_1x1_nhit + P_dc_1u2_nhit + P_dc_1u1_nhit + P_dc_1v1_nhit + P_dc_1x2_nhit + P_dc_1v2_nhit) <  20)}',        
        '{"P_dc_2*_nhit" : ((P_dc_2x1_nhit + P_dc_2u2_nhit + P_dc_2u1_nhit + P_dc_2v1_nhit + P_dc_2x2_nhit + P_dc_2v2_nhit) < 20)}',
    },
    "p_hadtrack_before" :
    {
        '{"H_bcm_bcm4b_AvgCurrent" : (H_bcm_bcm4b_AvgCurrent > thres_curr)}',        
        '{"P_hod_goodscinhit" : (P_hod_goodscinhit == 0)}',
        '{"P_hod_betanotrack" : ((P_hod_betanotrack > 0.5) & (P_hod_betanotrack < 1.4))}',
        '{"P_dc_1*_nhit" : ((P_dc_1x1_nhit + P_dc_1u2_nhit + P_dc_1u1_nhit + P_dc_1v1_nhit + P_dc_1x2_nhit + P_dc_1v2_nhit) <  20)}',        
        '{"P_dc_2*_nhit" : ((P_dc_2x1_nhit + P_dc_2u2_nhit + P_dc_2u1_nhit + P_dc_2v1_nhit + P_dc_2x2_nhit + P_dc_2v2_nhit) < 20)}',
        '{"P_cal_etotnorm" : (P_cal_etotnorm > 0.05)}',        
    },
    "p_pitrack_before" :
    {
        '{"H_bcm_bcm4b_AvgCurrent" : (H_bcm_bcm4b_AvgCurrent > thres_curr)}',        
        '{"P_hod_goodscinhit" : (P_hod_goodscinhit == 0)}',
        '{"P_hod_betanotrack" : ((P_hod_betanotrack > 0.5) & (P_hod_betanotrack < 1.4))}',
        '{"P_dc_1*_nhit" : ((P_dc_1x1_nhit + P_dc_1u2_nhit + P_dc_1u1_nhit + P_dc_1v1_nhit + P_dc_1x2_nhit + P_dc_1v2_nhit) <  20)}',        
        '{"P_dc_2*_nhit" : ((P_dc_2x1_nhit + P_dc_2u2_nhit + P_dc_2u1_nhit + P_dc_2v1_nhit + P_dc_2x2_nhit + P_dc_2v2_nhit) < 20)}',
        '{"P_cal_etotnorm" : (P_cal_etotnorm > 0.05)}',
        '{"P_hgcer_npeSum" : (P_hgcer_npeSum > 1.5)}',        
    },
    "p_Ktrack_before" :
    {
        '{"H_bcm_bcm4b_AvgCurrent" : (H_bcm_bcm4b_AvgCurrent > thres_curr)}',        
        '{"P_hod_goodscinhit" : (P_hod_goodscinhit == 0)}',
        '{"P_hod_betanotrack" : ((P_hod_betanotrack > 0.5) & (P_hod_betanotrack < 1.4))}',
        '{"P_dc_1*_nhit" : ((P_dc_1x1_nhit + P_dc_1u2_nhit + P_dc_1u1_nhit + P_dc_1v1_nhit + P_dc_1x2_nhit + P_dc_1v2_nhit) <  20)}',        
        '{"P_dc_2*_nhit" : ((P_dc_2x1_nhit + P_dc_2u2_nhit + P_dc_2u1_nhit + P_dc_2v1_nhit + P_dc_2x2_nhit + P_dc_2v2_nhit) < 20)}',
        '{"P_cal_etotnorm" : (P_cal_etotnorm > 0.05)}',
        '{"P_hgcer_npeSum" : (P_hgcer_npeSum > 1.5)}',
        '{"P_aero_npeSum" : (P_aero_npeSum > 1.5)}',        
    },
    "p_Ktrack_before" :
    {
        '{"H_bcm_bcm4b_AvgCurrent" : (H_bcm_bcm4b_AvgCurrent > thres_curr)}',        
        '{"P_hod_goodscinhit" : (P_hod_goodscinhit == 0)}',
        '{"P_hod_betanotrack" : ((P_hod_betanotrack > 0.5) & (P_hod_betanotrack < 1.4))}',
        '{"P_dc_1*_nhit" : ((P_dc_1x1_nhit + P_dc_1u2_nhit + P_dc_1u1_nhit + P_dc_1v1_nhit + P_dc_1x2_nhit + P_dc_1v2_nhit) <  20)}',        
        '{"P_dc_2*_nhit" : ((P_dc_2x1_nhit + P_dc_2u2_nhit + P_dc_2u1_nhit + P_dc_2v1_nhit + P_dc_2x2_nhit + P_dc_2v2_nhit) < 20)}',
        '{"P_cal_etotnorm" : (P_cal_etotnorm > 0.05)}',
        '{"P_hgcer_npeSum" : (P_hgcer_npeSum > 1.5)}',
        '{"P_aero_npeSum" : (P_aero_npeSum < 1.5)}',        
    },
    "p_track_after" :
    {
        '{"H_bcm_bcm4b_AvgCurrent" : (H_bcm_bcm4b_AvgCurrent > thres_curr)}',        
        '{"P_hod_goodscinhit" : (P_hod_goodscinhit == 0)}',
        '{"P_hod_betanotrack" : ((P_hod_betanotrack > 0.5) & (P_hod_betanotrack < 1.4))}',
        '{"P_dc_1*_nhit" : ((P_dc_1x1_nhit + P_dc_1u2_nhit + P_dc_1u1_nhit + P_dc_1v1_nhit + P_dc_1x2_nhit + P_dc_1v2_nhit) <  20)}',        
        '{"P_dc_2*_nhit" : ((P_dc_2x1_nhit + P_dc_2u2_nhit + P_dc_2u1_nhit + P_dc_2v1_nhit + P_dc_2x2_nhit + P_dc_2v2_nhit) < 20)}',
        '{"P_dc_ntrack" : (P_dc_ntrack > 0.0)}',        
    },
    "p_hadtrack_after" :
    {
        '{"H_bcm_bcm4b_AvgCurrent" : (H_bcm_bcm4b_AvgCurrent > thres_curr)}',        
        '{"P_hod_goodscinhit" : (P_hod_goodscinhit == 0)}',
        '{"P_hod_betanotrack" : ((P_hod_betanotrack > 0.5) & (P_hod_betanotrack < 1.4))}',
        '{"P_dc_1*_nhit" : ((P_dc_1x1_nhit + P_dc_1u2_nhit + P_dc_1u1_nhit + P_dc_1v1_nhit + P_dc_1x2_nhit + P_dc_1v2_nhit) <  20)}',        
        '{"P_dc_2*_nhit" : ((P_dc_2x1_nhit + P_dc_2u2_nhit + P_dc_2u1_nhit + P_dc_2v1_nhit + P_dc_2x2_nhit + P_dc_2v2_nhit) < 20)}',
        '{"P_dc_ntrack" : (P_dc_ntrack > 0.0)}',        
        '{"P_cal_etotnorm" : (P_cal_etotnorm > 0.05)}',        
    },
    "p_pitrack_after" :
    {
        '{"H_bcm_bcm4b_AvgCurrent" : (H_bcm_bcm4b_AvgCurrent > thres_curr)}',        
        '{"P_hod_goodscinhit" : (P_hod_goodscinhit == 0)}',
        '{"P_hod_betanotrack" : ((P_hod_betanotrack > 0.5) & (P_hod_betanotrack < 1.4))}',
        '{"P_dc_1*_nhit" : ((P_dc_1x1_nhit + P_dc_1u2_nhit + P_dc_1u1_nhit + P_dc_1v1_nhit + P_dc_1x2_nhit + P_dc_1v2_nhit) <  20)}',        
        '{"P_dc_2*_nhit" : ((P_dc_2x1_nhit + P_dc_2u2_nhit + P_dc_2u1_nhit + P_dc_2v1_nhit + P_dc_2x2_nhit + P_dc_2v2_nhit) < 20)}',
        '{"P_dc_ntrack" : (P_dc_ntrack > 0.0)}',        
        '{"P_cal_etotnorm" : (P_cal_etotnorm > 0.05)}',
        '{"P_hgcer_npeSum" : (P_hgcer_npeSum > 1.5)}',        
    },
    "p_Ktrack_after" :
    {
        '{"H_bcm_bcm4b_AvgCurrent" : (H_bcm_bcm4b_AvgCurrent > thres_curr)}',        
        '{"P_hod_goodscinhit" : (P_hod_goodscinhit == 0)}',
        '{"P_hod_betanotrack" : ((P_hod_betanotrack > 0.5) & (P_hod_betanotrack < 1.4))}',
        '{"P_dc_1*_nhit" : ((P_dc_1x1_nhit + P_dc_1u2_nhit + P_dc_1u1_nhit + P_dc_1v1_nhit + P_dc_1x2_nhit + P_dc_1v2_nhit) <  20)}',        
        '{"P_dc_2*_nhit" : ((P_dc_2x1_nhit + P_dc_2u2_nhit + P_dc_2u1_nhit + P_dc_2v1_nhit + P_dc_2x2_nhit + P_dc_2v2_nhit) < 20)}',
        '{"P_dc_ntrack" : (P_dc_ntrack > 0.0)}',        
        '{"P_cal_etotnorm" : (P_cal_etotnorm > 0.05)}',
        '{"P_hgcer_npeSum" : (P_hgcer_npeSum > 1.5)}',
        '{"P_aero_npeSum" : (P_aero_npeSum > 1.5)}',        
    },
    "p_Ktrack_after" :
    {
        '{"H_bcm_bcm4b_AvgCurrent" : (H_bcm_bcm4b_AvgCurrent > thres_curr)}',        
        '{"P_hod_goodscinhit" : (P_hod_goodscinhit == 0)}',
        '{"P_hod_betanotrack" : ((P_hod_betanotrack > 0.5) & (P_hod_betanotrack < 1.4))}',
        '{"P_dc_1*_nhit" : ((P_dc_1x1_nhit + P_dc_1u2_nhit + P_dc_1u1_nhit + P_dc_1v1_nhit + P_dc_1x2_nhit + P_dc_1v2_nhit) <  20)}',        
        '{"P_dc_2*_nhit" : ((P_dc_2x1_nhit + P_dc_2u2_nhit + P_dc_2u1_nhit + P_dc_2v1_nhit + P_dc_2x2_nhit + P_dc_2v2_nhit) < 20)}',
        '{"P_dc_ntrack" : (P_dc_ntrack > 0.0)}',        
        '{"P_cal_etotnorm" : (P_cal_etotnorm > 0.05)}',
        '{"P_hgcer_npeSum" : (P_hgcer_npeSum > 1.5)}',
        '{"P_aero_npeSum" : (P_aero_npeSum < 1.5)}',        
    },
    "p_ecut_before" :
    {
        '{"H_bcm_bcm4b_AvgCurrent" : (H_bcm_bcm4b_AvgCurrent > thres_curr)}',        
        '{"P_hod_goodscinhit" : (P_hod_goodscinhit == 0)}',
        '{"P_hod_betanotrack" : ((P_hod_betanotrack > 0.5) & (P_hod_betanotrack < 1.4))}',
    },
    "p_ecut_after" :
    {
        '{"H_bcm_bcm4b_AvgCurrent" : (H_bcm_bcm4b_AvgCurrent > thres_curr)}',        
        '{"P_hod_goodscinhit" : (P_hod_goodscinhit == 0)}',
        '{"P_hod_betanotrack" : ((P_hod_betanotrack > 0.5) & (P_hod_betanotrack < 1.4))}',
        '{"P_cal_etotnorm" : (P_cal_etotnorm < 0.7)}',
    },
    "p_ecut_eff" :
    {
        '{"H_bcm_bcm4b_AvgCurrent" : (H_bcm_bcm4b_AvgCurrent > thres_curr)}',        
        '{"P_hod_goodscinhit" : (P_hod_goodscinhit == 0)}',
        '{"P_hod_betanotrack" : ((P_hod_betanotrack > 0.5) & (P_hod_betanotrack < 1.4))}',
        '{"P_cal_etotnorm" : (P_cal_etotnorm < 0.7)}',
        '{"P_aero_npeSum" : (P_aero_npeSum < 1.5)}',
        '{"P_gtr_dp" : ((P_gtr_dp > -10.0) | (P_gtr_dp < 20.0))}',
        '{"P_gtr_th" : (abs(P_gtr_th) < 0.080)}',
        '{"P_gtr_ph" : (abs(P_gtr_ph) < 0.035)}',
    },
    "h_track_before" :
    {
        '{"H_bcm_bcm4b_AvgCurrent" : (H_bcm_bcm4b_AvgCurrent > thres_curr)}',        
        '{"H_hod_goodscinhit" : (H_hod_goodscinhit == 0)}',
        '{"H_hod_betanotrack" : ((H_hod_betanotrack > 0.8) & (H_hod_betanotrack < 1.3))}',
        '{"H_dc_1*_nhit" : ((H_dc_1x1_nhit + H_dc_1u2_nhit + H_dc_1u1_nhit + H_dc_1v1_nhit + H_dc_1x2_nhit + H_dc_1v2_nhit) <  20)}',        
        '{"H_dc_2*_nhit" : ((H_dc_2x1_nhit + H_dc_2u2_nhit + H_dc_2u1_nhit + H_dc_2v1_nhit + H_dc_2x2_nhit + H_dc_2v2_nhit) < 20)}',
    },
    "h_etrack_before" :
    {
        '{"H_bcm_bcm4b_AvgCurrent" : (H_bcm_bcm4b_AvgCurrent > thres_curr)}',        
        '{"H_hod_goodscinhit" : (H_hod_goodscinhit == 0)}',
        '{"H_hod_betanotrack" : ((H_hod_betanotrack > 0.8) & (H_hod_betanotrack < 1.3))}',
        '{"H_dc_1*_nhit" : ((H_dc_1x1_nhit + H_dc_1u2_nhit + H_dc_1u1_nhit + H_dc_1v1_nhit + H_dc_1x2_nhit + H_dc_1v2_nhit) <  20)}',        
        '{"H_dc_2*_nhit" : ((H_dc_2x1_nhit + H_dc_2u2_nhit + H_dc_2u1_nhit + H_dc_2v1_nhit + H_dc_2x2_nhit + H_dc_2v2_nhit) < 20)}',
        '{"H_cer_npeSum" : (H_cer_npeSum > 0.5)}', 
        '{"H_cal_etotnorm" : ((H_cal_etotnorm > 0.6) & (H_cal_etotnorm < 2.0))}',
    },
    "h_track_after" :
    {
        '{"H_bcm_bcm4b_AvgCurrent" : (H_bcm_bcm4b_AvgCurrent > thres_curr)}',        
        '{"H_hod_goodscinhit" : (H_hod_goodscinhit == 0)}',
        '{"H_hod_betanotrack" : ((H_hod_betanotrack > 0.8) & (H_hod_betanotrack < 1.3))}',
        '{"H_dc_1*_nhit" : ((H_dc_1x1_nhit + H_dc_1u2_nhit + H_dc_1u1_nhit + H_dc_1v1_nhit + H_dc_1x2_nhit + H_dc_1v2_nhit) <  20)}',        
        '{"H_dc_2*_nhit" : ((H_dc_2x1_nhit + H_dc_2u2_nhit + H_dc_2u1_nhit + H_dc_2v1_nhit + H_dc_2x2_nhit + H_dc_2v2_nhit) < 20)}',
        '{"H_dc_ntrack" : (H_dc_ntrack > 0.0)}',        
    },
    "h_etrack_after" :
    {
        '{"H_bcm_bcm4b_AvgCurrent" : (H_bcm_bcm4b_AvgCurrent > thres_curr)}',        
        '{"H_hod_goodscinhit" : (H_hod_goodscinhit == 0)}',
        '{"H_hod_betanotrack" : ((H_hod_betanotrack > 0.8) & (H_hod_betanotrack < 1.3))}',
        '{"H_dc_1*_nhit" : ((H_dc_1x1_nhit + H_dc_1u2_nhit + H_dc_1u1_nhit + H_dc_1v1_nhit + H_dc_1x2_nhit + H_dc_1v2_nhit) <  20)}',        
        '{"H_dc_2*_nhit" : ((H_dc_2x1_nhit + H_dc_2u2_nhit + H_dc_2u1_nhit + H_dc_2v1_nhit + H_dc_2x2_nhit + H_dc_2v2_nhit) < 20)}',
        '{"H_dc_ntrack" : (H_dc_ntrack > 0.0)}',        
        '{"H_cer_npeSum" : (H_cer_npeSum > 0.5)}', 
        '{"H_cal_etotnorm" : ((H_cal_etotnorm > 0.6) & (H_cal_etotnorm < 2.0))}',
    },
    "h_ecut_after" :
    {
        '{"H_bcm_bcm4b_AvgCurrent" : (H_bcm_bcm4b_AvgCurrent > thres_curr)}',        
        '{"H_cal_etotnorm" : ((H_cal_etotnorm > 0.6) & (H_cal_etotnorm < 2.0))}',
        '{"H_cer_npeSum" : (H_cer_npeSum > 1.5)}', 
        '{"H_gtr_dp" : (abs(H_gtr_dp) < 8.0)}',
        '{"H_gtr_th" : (abs(H_gtr_th) < 0.080)}',
        '{"H_gtr_ph" : (abs(H_gtr_ph) < 0.035)}',
    },
    "h_ecut_eff" :
    {
        '{"H_bcm_bcm4b_AvgCurrent" : (H_bcm_bcm4b_AvgCurrent > thres_curr)}',        
        '{"H_cal_etotnorm" : ((H_cal_etotnorm > 0.6) & (H_cal_etotnorm < 2.0))}',
        '{"H_cer_npeSum" : (H_cer_npeSum > 1.5)}', 
        '{"H_gtr_dp" : (abs(H_gtr_dp) < 8.0)}',
        '{"H_gtr_th" : (abs(H_gtr_th) < 0.080)}',
        '{"H_gtr_ph" : (abs(H_gtr_ph) < 0.035)}',
        '{"H_cer_npeSum" : (H_cer_npeSum > 1.5)}',
    },
}

r = r2p.pyRoot()

def make_cutDict(inputDict,cut):

    global c
    c = r2p.pyPlot(inputDict)
    
    x = c.w_dict(cut)
    inputDict[cut] = {}
    for i,val in enumerate(x):
        tmp = x[i]
        inputDict[cut].update(eval(tmp))

    return inputDict

cutDict = make_cutDict(cutDict,"h_ecut_no_cer")

def analysis(PS1, PS3, thres_curr):
    
    bcm_before = H_bcm_bcm4b_AvgCurrent
    bcm_after = [x for x in H_bcm_bcm4b_AvgCurrent if x > thres_curr ]

    EDTM = [x
            for x,bcm in zip(T_coin_pEDTM_tdcTime,bcm_after)
            if bcm > thres_curr
            if x != 0.0]
    
    TRIG1 = [x
             for x,bcm in zip(T_coin_pTRIG1_ROC2_tdcTime,bcm_after)
             if bcm > thres_curr             
             if x != 0.0]
    TRIG3 = [x
             for x,bcm in zip(T_coin_pTRIG3_ROC2_tdcTime,bcm_after)
             if bcm > thres_curr
             if x !=0.0]
    TRIG5 = [x
             for x,bcm in zip(T_coin_pTRIG5_ROC2_tdcTime,bcm_after)
             if bcm > thres_curr
             if x !=0.0]
    
    EventType = [x
             for x,bcm in zip(EvtType,bcm_after)
             if bcm > thres_curr]
    
    SHMS_EDTM = [edtm
                 for (edtm,evt,bcm) in zip(T_coin_pEDTM_tdcTime,EvtType,bcm_after)
                 if bcm > thres_curr
                 if (evt == 1)]
                     # and edtm > 140.0
                     # and edtm < 144.0)]

    TRIG1_cut = [trig1
                 for (trig1,evt,bcm) in zip(T_coin_pTRIG1_ROC2_tdcTime,EvtType,bcm_after)
                 if bcm > thres_curr
                 if evt == 1]
    
    # p_track_before
    p_track_before = c.add_cut(P_dc_ntrack,"p_track_before")
    # p_hadtrack_before
    p_hadtrack_before = c.add_cut(P_dc_ntrack,"p_hadtrack_before")

    # p_pitrack_before
    p_pitrack_before = c.add_cut(P_dc_ntrack,"p_pitrack_before")

    # p_Ktrack_before
    p_Ktrack_before = c.add_cut(P_dc_ntrack,"p_Ktrack_before")

    # p_ptrack_before
    p_ptrack_before = c.add_cut(P_dc_ntrack,"p_ptrack_before")

    # p_track_after
    p_track_after = c.add_cut(P_dc_ntrack,"p_track_after")

    # p_hadtrack_after
    p_hadtrack_after = c.add_cut(P_dc_ntrack,"p_hadtrack_after")

    # p_pitrack_after
    p_pitrack_after = c.add_cut(P_dc_ntrack,"p_pitrack_after")

    # p_Ktrack_after
    p_Ktrack_after = c.add_cut(P_dc_ntrack,"p_Ktrack_after")

    # p_ptrack_after
    p_ptrack_after = c.add_cut(P_dc_ntrack,"p_ptrack_after")

    # p_ecut_before
    p_ecut_before = c.add_cut(P_hgcer_npeSum,"p_ecut_before")

    # p_show_before
    p_show_before = c.add_cut(P_cal_etotnorm,"p_ecut_before")

    # p_ecut_after
    p_ecut_after  = c.add_cut(P_hgcer_npeSum,"p_ecut_after")

    # p_ecut_eff
    p_ecut_eff  = c.add_cut(P_hgcer_npeSum,"p_ecut_eff")

    # p_show_after
    p_show_after  = c.add_cut(P_cal_etotnorm,"p_ecut_eff")
    
    HMS_EDTM = [x
                for (x, evt, bcm) in zip(T_coin_pEDTM_tdcTime, EvtType, bcm_after)
                if bcm > thres_curr
                if (evt == 2)]

    TRIG3_cut = [ x
                  for (x, evt, bcm ) in zip(T_coin_pTRIG3_ROC2_tdcTime, EvtType, bcm_after)
                  if bcm > thres_curr
                  if evt == 2]

    # h_track_before
    h_track_before = c.add_cut(H_dc_ntrack,"h_track_before")

    # h_etrack_before
    h_etrack_before = c.add_cut(H_dc_ntrack,"h_etrack_before")
    
    # h_track_after
    h_track_after = c.add_cut(H_dc_ntrack,"h_track_after")


    # h_etrack_after
    h_etrack_after = c.add_cut(H_dc_ntrack,"h_etrack_after")    

    # h_ecut_before
    h_ecut_before_iterate = [H_cer_npeSum, bcm_after]
    h_ecut_before = [cer
                      for (cer, bcm) in zip(*h_ecut_before_iterate)
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
    # h_ecut_after
    h_ecut_after = c.add_cut(H_cer_npeSum,"h_ecut_after")
    
    # h_dp_after
    h_dp_after = c.add_cut(H_gtr_dp,"h_ecut_after")
    
    # h_th_after
    h_th_after = c.add_cut(H_tr_tg_th,"h_ecut_after")
    
    # h_ph_after
    h_ph_after = c.add_cut(H_tr_tg_ph,"h_ecut_after")
    
    # h_show_after
    h_show_after = c.add_cut(H_cal_etotnorm,"h_ecut_after")
    
    # h_ecut_eff
    h_ecut_eff = c.add_cut(H_cal_etotnorm,"h_ecut_eff")
                                                        
    if PS1 == 0:
        track_info = {
            
            "HMS_evts" : len(h_ecut_eff),
            "HMS_evts_uncern" : math.sqrt(len(h_ecut_eff)),
            "SHMS_evts" : 0,
            "SHMS_evts_uncern" : 0,
            "TRIG1_cut" : len(TRIG1_cut),
            "TRIG3_cut" : len(TRIG3_cut),
            "HMS_track" : len(h_track_after)/len(h_track_before),
            "HMS_track_uncern" : (len(h_track_after)/len(h_track_before))*math.sqrt((1/len(h_track_after)) + (1/len(h_track_before))),
            "etrack" : len(h_etrack_after)/len(h_etrack_before),
            "etrack_uncern" : (len(h_etrack_after)/len(h_etrack_before))*math.sqrt((1/len(h_etrack_after)) + (1/len(h_etrack_before))),
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
            "accp_edtm" : (scipy.integrate.simps(SHMS_EDTM) + scipy.integrate.simps(HMS_EDTM)),
            
        }
    elif PS3 == 0:
        track_info = {
            
            "HMS_evts" : 0,
            "HMS_evts_uncern" : 0,
            "SHMS_evts" : len(p_ecut_eff),
            "SHMS_evts_uncern" : math.sqrt(len(p_ecut_eff)),
            "TRIG1_cut" : len(TRIG1_cut),
            "TRIG3_cut" : len(TRIG3_cut),
            "HMS_track" : 0,
            "HMS_track_uncern" : 0,
            "etrack" : 0,
            "etrack_uncern" : 0,
            "SHMS_track" : len(p_track_after)/len(p_track_before),
            "SHMS_track_uncern" : (len(p_track_after)/len(p_track_before))*math.sqrt((1/len(p_track_after)) + (1/len(p_track_before))),
            "hadtrack" : len(p_hadtrack_after)/len(p_hadtrack_before),
            "hadtrack_uncern" : (len(p_hadtrack_after)/len(p_hadtrack_before))*math.sqrt((1/len(p_hadtrack_after)) + (1/len(p_hadtrack_before))),
            "pitrack" : len(p_pitrack_after)/len(p_pitrack_before),
            "pitrack_uncern" : (len(p_pitrack_after)/len(p_pitrack_before))*math.sqrt((1/len(p_pitrack_after)) + (1/len(p_pitrack_before))),
            "Ktrack" : len(p_Ktrack_after)/len(p_Ktrack_before),
            "Ktrack_uncern" : (len(p_Ktrack_after)/len(p_Ktrack_before))*math.sqrt((1/len(p_Ktrack_after)) + (1/len(p_Ktrack_before))),
            "ptrack" : len(p_ptrack_after)/len(p_ptrack_before),
            "ptrack_uncern" : (len(p_ptrack_after)/len(p_ptrack_before))*math.sqrt((1/len(p_ptrack_after)) + (1/len(p_ptrack_before))),
            "accp_edtm" : (scipy.integrate.simps(SHMS_EDTM) + scipy.integrate.simps(HMS_EDTM)),

        }
    else:
        track_info = {
            
            "HMS_evts" : len(h_ecut_eff),
            "HMS_evts_uncern" : math.sqrt(len(h_ecut_eff)),
            "SHMS_evts" : len(p_ecut_eff),
            "SHMS_evts_uncern" : math.sqrt(len(p_ecut_eff)),
            "TRIG1_cut" : len(TRIG1_cut),
            "TRIG3_cut" : len(TRIG3_cut),
            "HMS_track" : len(h_track_after)/len(h_track_before),
            "HMS_track_uncern" : (len(h_track_after)/len(h_track_before))*math.sqrt((1/len(h_track_after)) + (1/len(h_track_before))),
            "etrack" : len(h_etrack_after)/len(h_etrack_before),
            "etrack_uncern" : (len(h_etrack_after)/len(h_etrack_before))*math.sqrt((1/len(h_etrack_after)) + (1/len(h_etrack_before))),
            "SHMS_track" : len(p_track_after)/len(p_track_before),
            "SHMS_track_uncern" : (len(p_track_after)/len(p_track_before))*math.sqrt((1/len(p_track_after)) + (1/len(p_track_before))),
            "hadtrack" : len(p_hadtrack_after)/len(p_hadtrack_before),
            "hadtrack_uncern" : (len(p_hadtrack_after)/len(p_hadtrack_before))*math.sqrt((1/len(p_hadtrack_after)) + (1/len(p_hadtrack_before))),
            "pitrack" : len(p_pitrack_after)/len(p_pitrack_before),
            "pitrack_uncern" : (len(p_pitrack_after)/len(p_pitrack_before))*math.sqrt((1/len(p_pitrack_after)) + (1/len(p_pitrack_before))),
            "Ktrack" : len(p_Ktrack_after)/len(p_Ktrack_before),
            "Ktrack_uncern" : (len(p_Ktrack_after)/len(p_Ktrack_before))*math.sqrt((1/len(p_Ktrack_after)) + (1/len(p_Ktrack_before))),
            "ptrack" : len(p_ptrack_after)/len(p_ptrack_before),
            "ptrack_uncern" : (len(p_ptrack_after)/len(p_ptrack_before))*math.sqrt((1/len(p_ptrack_after)) + (1/len(p_ptrack_before))),
            "accp_edtm" : (scipy.integrate.simps(SHMS_EDTM) + scipy.integrate.simps(HMS_EDTM)),
            
        }

    print("Terminate","Selection rules have been applied, plotting results")
    print("Using prescale factors: PS1 %.0f, PS3 %.0f\n" % (PS1,PS3))
    print("Total number of events: %.0f\n" % (len(EventType)))
    print("Number of EDTM  Events: %.0f\n" % (PS1*scipy.integrate.simps(SHMS_EDTM)
                                              + PS3*scipy.integrate.simps(HMS_EDTM)))
    print("Number of TRIG1 Events: %.0f\n" % (PS1*scipy.integrate.simps(TRIG1_cut)))
    print("Number of TRIG3 Events: %.0f\n" % (PS3*scipy.integrate.simps(TRIG3_cut)))
    print("Number of TRIG5 Events: %.0f\n\n" % scipy.integrate.simps(TRIG5))

    print("Number of HMS good events: %.0f +/- %.0f " % ((PS3*len(h_ecut_eff))
                                                         ,math.sqrt(PS3*len(h_ecut_eff))))
    print("Calculated tracking efficiency: %f +/- %f\n" %
          (len(h_track_after)/len(h_track_before),
           (len(h_track_after)/len(h_track_before))*math.sqrt((1/len(h_track_after))
                                                         + (1/len(h_track_before)))))
    print("Calculated electron tracking efficiency: %f +/- %f\n" %
          (len(h_etrack_after)/len(h_etrack_before),
           (len(h_etrack_after)/len(h_etrack_before))*math.sqrt((1/len(h_etrack_after))
                                                           + (1/len(h_etrack_before)))))
    print("Calculated HMS Cherenkov efficiency: %f +/- %f\n\n" %
          (len(h_ecut_eff)/len(h_ecut_after),
           (len(h_ecut_eff)/len(h_ecut_after))*math.sqrt((1/len(h_ecut_eff))
                                                    + (1/len(h_ecut_after)))))
    print("Number of SHMS good events: %.0f +/- %.0f" % ((PS1*len(p_ecut_eff)),
                                                         math.sqrt(PS1*len(p_ecut_eff))))
    print("Calculated tracking efficiency: %f +/- %f\n" %
          (len(p_track_after)/len(p_track_before),
           (len(p_track_after)/len(p_track_before))*math.sqrt((1/len(p_track_after))
                                                         + (1/len(p_track_before)))))
    print("Calculated hadron tracking efficiency: %f +/- %f\n" %
          (len(p_hadtrack_after)/len(p_hadtrack_before),
           (len(p_hadtrack_after)/len(p_hadtrack_before))*math.sqrt((1/len(p_hadtrack_after))
                                                               + (1/len(p_hadtrack_before)))))
    print("Calculated pion tracking efficiency: %f +/- %f\n" %
          (len(p_pitrack_after)/len(p_pitrack_before),
           (len(p_pitrack_after)/len(p_pitrack_before))*math.sqrt((1/len(p_pitrack_after))
                                                             + (1/len(p_pitrack_before)))))
    print("Calculated kaon tracking efficiency: %f +/- %f\n" %
          (len(p_Ktrack_after)/len(p_Ktrack_before),
           (len(p_Ktrack_after)/len(p_Ktrack_before))*math.sqrt((1/len(p_Ktrack_after))
                                                           + (1/len(p_Ktrack_before)))))
    print("Calculated proton tracking efficiency: %f +/- %f\n" %
          (len(p_ptrack_after)/len(p_ptrack_before),
           (len(p_ptrack_after)/len(p_ptrack_before))*math.sqrt((1/len(p_ptrack_after))
                                                           + (1/len(p_ptrack_before)))))
    print("Calculated SHMS Cherenkov efficiency: %f +/- %f\n\n" %
          (len(p_ecut_eff)/len(p_ecut_after),
           (len(p_ecut_eff)/len(p_ecut_after))*math.sqrt((1/len(p_ecut_eff))
                                                + (1/len(p_ecut_after)))))
    print("============================================================================\n\n")
          
    return track_info

def main():

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
