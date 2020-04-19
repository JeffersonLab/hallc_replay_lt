#! /usr/bin/python

#
# Description:
# ================================================================
# Time-stamp: "2020-04-19 12:31:57 trottar"
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

sys.path.insert(0, 'python/')
import root2py as r2p

runNum = sys.argv[1]
MaxEvent=sys.argv[2]
# MaxEvent=50000

b = r2p.pyBin()
c = r2p.pyPlot(None)

USER = subprocess.getstatusoutput("whoami")

# filename = "/home/trottar/Analysis/hallc_replay_lt/UTIL_KAONLT/scripts/pid/OUTPUTS/pid_data.csv" 
# rootName = "/home/trottar/Analysis/hallc_replay_lt/UTIL_KAONLT/ROOTfiles/pid_coin_offline_%s_%s.root" % (runNum,MaxEvent)

filename = "/u/group/c-kaonlt/USERS/%s/hallc_replay_lt/UTIL_KAONLT/scripts/pid/OUTPUTS/pid_data.csv" % USER[1]
rootName = "/u/group/c-kaonlt/USERS/%s/hallc_replay_lt/UTIL_KAONLT/ROOTfiles/pid_coin_offline_%s_%s.root" % (USER[1], runNum,MaxEvent)

'''
ANALYSIS TREE, T
'''

tree = up.open(rootName)["T"]
branch = r2p.pyBranch(tree)

CTime_ePositronCoinTime_ROC1  = tree.array("CTime.ePositronCoinTime_ROC1")
CTime_eKCoinTime_ROC1  = tree.array("CTime.eKCoinTime_ROC1")
CTime_ePiCoinTime_ROC1 = tree.array("CTime.ePiCoinTime_ROC1")
CTime_epCoinTime_ROC1  = tree.array("CTime.epCoinTime_ROC1")
P_gtr_beta         = tree.array("P.gtr.beta")
P_gtr_th           = tree.array("P.gtr.th")
P_gtr_ph           = tree.array("P.gtr.ph")
H_gtr_beta         = tree.array("H.gtr.beta")
H_gtr_th           = tree.array("H.gtr.th")
H_gtr_ph           = tree.array("H.gtr.ph")
H_cal_etotnorm     = tree.array("H.cal.etotnorm") 
H_cer_npeSum       = tree.array("H.cer.npeSum")
P_cal_etotnorm     = tree.array("P.cal.etotnorm")
P_aero_npeSum      = tree.array("P.aero.npeSum")
P_hgcer_npeSum     = tree.array("P.hgcer.npeSum")
P_hgcer_xAtCer     = tree.array("P.hgcer.xAtCer")
P_hgcer_yAtCer     = tree.array("P.hgcer.yAtCer")
H_gtr_dp           = tree.array("H.gtr.dp")
P_gtr_dp           = tree.array("P.gtr.dp")
P_gtr_p            = tree.array("P.gtr.p")
Q2                 = tree.array("H.kin.primary.Q2")
W                  = tree.array("H.kin.primary.W")
epsilon            = tree.array("H.kin.primary.epsilon")
ph_q               = tree.array("P.kin.secondary.ph_xq")
emiss              = tree.array("P.kin.secondary.emiss")
pmiss              = tree.array("P.kin.secondary.pmiss")
MandelT            = tree.array("P.kin.secondary.MandelT")
pEDTM              = tree.array("T.coin.pEDTM_tdcTime")
pTRIG5             = tree.array("T.coin.pTRIG5_ROC1_tdcTime")
EvtType            = tree.array("fEvtHdr.fEvtType")


def hms_cer():

    missmass = np.array([math.sqrt(abs(emm*emm-pmm*pmm)) for (emm, pmm) in zip(emiss, pmiss)])
    
    noID_electron_iterate = [CTime_eKCoinTime_ROC1, H_gtr_dp, P_gtr_dp, P_cal_etotnorm, H_gtr_beta, H_cal_etotnorm, emiss, pmiss]
    
    # coin_noID_electron
    coin_noID_electron = np.array([coin-47.5
                                   for (coin, h_dp, p_dp, p_cal, h_beta, h_cal, emm, pmm)
                                   in zip(*noID_electron_iterate)
                                   if abs(h_dp) < 10.0
                                   if p_dp >-10.0 or p_dp < 20.0
                                   if p_cal <0.6
                                   if (abs(h_beta)-1.00) < 0.1
                                   if (coin-47.5) > -0.5 and (coin-47.5) < 0.5
                                   if h_cal > 0.995 and h_cal < 1.015])

    # mm_noID_electron
    mm_noID_electron = np.array([math.sqrt(abs(emm*emm-pmm*pmm))
                                 for (coin, h_dp, p_dp, p_cal, h_beta, h_cal, emm, pmm)
                                 in zip(*noID_electron_iterate)
                                 if abs(h_dp) < 10.0
                                 if p_dp >-10.0 or p_dp < 20.0
                                 if p_cal <0.6
                                 if (abs(h_beta)-1.00) < 0.1
                                 if (coin-47.5) > -0.5 and (coin-47.5) < 0.5
                                 if h_cal > 0.995 and h_cal < 1.015])

    PID_electron_iterate = [CTime_eKCoinTime_ROC1, H_gtr_dp, P_gtr_dp, P_cal_etotnorm, H_gtr_beta, H_cal_etotnorm, H_cer_npeSum, emiss, pmiss]
    
    # coin_PID_electron
    coin_PID_electron = np.array([coin-47.5
                                  for (coin, h_dp, p_dp, p_cal, h_beta, h_cal, h_cer, emm, pmm)
                                  in zip(*PID_electron_iterate)
                                  if abs(h_dp) < 10.0
                                  if p_dp >-10.0 or p_dp < 20.0
                                  if p_cal <0.6
                                  if (abs(h_beta)-1.00) < 0.1
                                  if (coin-47.5) > -0.5 and (coin-47.5) < 0.5
                                  if h_cal > 0.995 and h_cal < 1.015
                                  if h_cer > 3.0])

    # mm_PID_electron
    mm_PID_electron = np.array([math.sqrt(emm*emm-pmm*pmm)
                                for (coin, h_dp, p_dp, p_cal, h_beta, h_cal, h_cer, emm, pmm)
                                in zip(*PID_electron_iterate)
                                if abs(h_dp) < 10.0
                                if p_dp >-10.0 or p_dp < 20.0
                                if p_cal <0.6
                                if (abs(h_beta)-1.00) < 0.1
                                if (coin-47.5) > -0.5 and (coin-47.5) < 0.5
                                if h_cal > 0.995 and h_cal < 1.015
                                if h_cer > 3.0])

    h_cer_data = {

        "h_cer_eff" : len(mm_noID_electron)/len(mm_PID_electron),
    }

    f = plt.figure(figsize=(11.69,8.27))
    plt.style.use('default')

    plt.hist(missmass,bins=b.setbin(missmass,800,0,2.0),label='no cuts',histtype='step', alpha=0.7, stacked=True, fill=True)
    plt.hist(mm_noID_electron,bins=b.setbin(mm_noID_electron,800,0,2.0),label='no ID',histtype='step', alpha=0.7, stacked=True, fill=True)
    plt.hist(mm_PID_electron,bins=b.setbin(mm_PID_electron,800,0,2.0),label='PID',histtype='step', alpha=0.7, stacked=True, fill=True)
    plt.legend(loc=1)
    plt.title('Missing Mass ($GeV^2$)', fontsize =20)

    f.savefig('../OUTPUTS/missmass_%s.png' % runNum)

    noID_plot = c.densityPlot(coin_noID_electron, mm_noID_electron, 'Electron Coincident Time vs Mass ($GeV^2$) for ROC1 (w/out HMS Cherenkov cuts)','Time (ns)','Mass (GeV/c^2)', 200, 800,  b,-10,10,0,2.0)
    # plt.ylim(-180.,180.)
    # plt.xlim(0.,50.)

    noID_plot[1].savefig('../OUTPUTS/noID_hms_cer_%s.png' % runNum)

    PID_plot = c.densityPlot(coin_PID_electron, mm_PID_electron, 'Electron Coincident Time vs Mass ($GeV^2$) for ROC1 (with HMS Cherenkov cuts)','Time (ns)','Mass (GeV/c^2)', 200, 800,  b,-10,10,0,2.0)
    # plt.ylim(-180.,180.)
    # plt.xlim(0.,50.)

    PID_plot[1].savefig('../OUTPUTS/PID_hms_cer_%s.png' % runNum)
    
    print("=====================")
    print("= %s HMS CER DONE =" % runNum)
    print("=====================\n\n")
          
    return [h_cer_data,f]

def hms_cal():

    missmass = np.array([math.sqrt(abs(emm*emm-pmm*pmm)) for (emm, pmm) in zip(emiss, pmiss)])
    
    noID_electron_iterate = [CTime_eKCoinTime_ROC1, H_gtr_dp, P_gtr_dp, P_cal_etotnorm, H_gtr_beta, H_cer_npeSum, emiss, pmiss]
    
    # coin_noID_electron
    coin_noID_electron = np.array([coin-47.5
                                   for (coin, h_dp, p_dp, p_cal, h_beta, h_cer, emm, pmm)
                                   in zip(*noID_electron_iterate)
                                   if abs(h_dp) < 10.0
                                   if p_dp >-10.0 or p_dp < 20.0
                                   if p_cal <0.6
                                   if (abs(h_beta)-1.00) < 0.1
                                   if (coin-47.5) > -0.5 and (coin-47.5) < 0.5
                                   if h_cer > 1.5])

    # mm_noID_electron
    mm_noID_electron = np.array([math.sqrt(abs(emm*emm-pmm*pmm))
                                 for (coin, h_dp, p_dp, p_cal, h_beta, h_cer, emm, pmm)
                                 in zip(*noID_electron_iterate)
                                 if abs(h_dp) < 10.0
                                 if p_dp >-10.0 or p_dp < 20.0
                                 if p_cal <0.6
                                 if (abs(h_beta)-1.00) < 0.1
                                 if (coin-47.5) > -0.5 and (coin-47.5) < 0.5
                                 if h_cer > 1.5])

    PID_electron_iterate = [CTime_eKCoinTime_ROC1, H_gtr_dp, P_gtr_dp, P_cal_etotnorm, H_gtr_beta, H_cer_npeSum, H_cal_etotnorm, emiss, pmiss]
    
    # coin_PID_electron
    coin_PID_electron = np.array([coin-47.5
                                  for (coin, h_dp, p_dp, p_cal, h_beta, h_cer, h_cal, emm, pmm)
                                  in zip(*PID_electron_iterate)
                                  if abs(h_dp) < 10.0
                                  if p_dp >-10.0 or p_dp < 20.0
                                  if p_cal <0.6
                                  if (abs(h_beta)-1.00) < 0.1
                                  if (coin-47.5) > -0.5 and (coin-47.5) < 0.5
                                  if h_cer > 1.5
                                  if h_cal > 1.1])

    # mm_PID_electron
    mm_PID_electron = np.array([math.sqrt(emm*emm-pmm*pmm)
                                for (coin, h_dp, p_dp, p_cal, h_beta, h_cer, h_cal, emm, pmm)
                                in zip(*PID_electron_iterate)
                                if abs(h_dp) < 10.0
                                if p_dp >-10.0 or p_dp < 20.0
                                if p_cal <0.6
                                if (abs(h_beta)-1.00) < 0.1
                                if (coin-47.5) > -0.5 and (coin-47.5) < 0.5
                                if h_cer > 1.5
                                if h_cal > 1.1])

    h_cal_data = {

        "h_cal_eff" : len(mm_noID_electron)/len(mm_PID_electron),
    }

    f = plt.figure(figsize=(11.69,8.27))
    plt.style.use('default')

    plt.hist(missmass,bins=b.setbin(missmass,800,0,2.0),label='no cuts',histtype='step', alpha=0.7, stacked=True, fill=True)
    plt.hist(mm_noID_electron,bins=b.setbin(mm_noID_electron,800,0,2.0),label='no ID',histtype='step', alpha=0.7, stacked=True, fill=True)
    plt.hist(mm_PID_electron,bins=b.setbin(mm_PID_electron,800,0,2.0),label='PID',histtype='step', alpha=0.7, stacked=True, fill=True)
    plt.legend(loc=1)
    plt.title('Missing Mass ($GeV^2$)', fontsize =20)

    f.savefig('../OUTPUTS/missmass_%s.png' % runNum)

    noID_plot = c.densityPlot(coin_noID_electron, mm_noID_electron, 'Electron Coincident Time vs Mass ($GeV^2$) for ROC1 (w/out HMS Calorimeter cuts)','Time (ns)','Mass (GeV/c^2)', 200, 800,  b,-10,10,0,2.0)
    # plt.ylim(-180.,180.)
    # plt.xlim(0.,50.)

    noID_plot[1].savefig('../OUTPUTS/noID_hms_cal_%s.png' % runNum)

    PID_plot = c.densityPlot(coin_PID_electron, mm_PID_electron, 'Electron Coincident Time vs Mass ($GeV^2$) for ROC1 (with HMS Calorimeter cuts)','Time (ns)','Mass (GeV/c^2)', 200, 800,  b,-10,10,0,2.0)
    # plt.ylim(-180.,180.)
    # plt.xlim(0.,50.)

    PID_plot[1].savefig('../OUTPUTS/PID_hms_cal_%s.png' % runNum)
    
    print("=====================")
    print("= %s HMS CAL DONE =" % runNum)
    print("=====================\n\n")
          
    return [h_cal_data, f]

def shms_hgcer():

    missmass = np.array([math.sqrt(abs(emm*emm-pmm*pmm)) for (emm, pmm) in zip(emiss, pmiss)])
    
    noID_electron_iterate = [CTime_eKCoinTime_ROC1, H_gtr_dp, P_gtr_dp, H_cal_etotnorm, H_cer_npeSum, P_gtr_beta, P_cal_etotnorm, P_aero_npeSum, emiss, pmiss]
    
    # coin_noID_electron
    coin_noID_electron = np.array([coin-47.5
                                   for (coin, h_dp, p_dp, h_cal, h_cer, p_beta, p_cal, p_aero, emm, pmm)
                                   in zip(*noID_electron_iterate)
                                   if abs(h_dp) < 10.0
                                   if p_dp >-10.0 or p_dp < 20.0
                                   if h_cal > 0.7 or h_cer > 1.5
                                   if (abs(p_beta)-1.00) < 0.1
                                   if (coin-47.5) > -0.5 and (coin-47.5) < 0.5
                                   if p_cal > 0.7 or p_aero > 1.5])

    # mm_noID_electron
    mm_noID_electron = np.array([math.sqrt(abs(emm*emm-pmm*pmm))
                                 for (coin, h_dp, p_dp, h_cal, h_cer, p_beta, p_cal, p_aero, emm, pmm)
                                 in zip(*noID_electron_iterate)
                                 if abs(h_dp) < 10.0
                                 if abs(h_dp) < 10.0
                                 if p_dp >-10.0 or p_dp < 20.0
                                 if h_cal > 0.7 or h_cer > 1.5
                                 if (abs(p_beta)-1.00) < 0.1
                                 if (coin-47.5) > -0.5 and (coin-47.5) < 0.5
                                 if p_cal > 0.7 or p_aero > 1.5])
    
    PID_electron_iterate = [CTime_eKCoinTime_ROC1, H_gtr_dp, P_gtr_dp, H_cal_etotnorm, H_cer_npeSum, P_gtr_beta, P_cal_etotnorm, P_aero_npeSum, P_hgcer_npeSum, emiss, pmiss]
    
    # coin_PID_electron
    coin_PID_electron = np.array([coin-47.5
                                  for (coin, h_dp, p_dp, h_cal, h_cer, p_beta, p_cal, p_aero, p_hgcer, emm, pmm)
                                  in zip(*PID_electron_iterate)
                                  if abs(h_dp) < 10.0
                                  if abs(h_dp) < 10.0
                                  if p_dp >-10.0 or p_dp < 20.0
                                  if h_cal > 0.7 or h_cer > 1.5
                                  if (abs(p_beta)-1.00) < 0.1
                                  if (coin-47.5) > -0.5 and (coin-47.5) < 0.5
                                  if p_cal > 0.7 or p_aero > 1.5
                                  if p_hgcer >1.5])
    

    # mm_PID_electron
    mm_PID_electron = np.array([math.sqrt(emm*emm-pmm*pmm)
                                for (coin, h_dp, p_dp, h_cal, h_cer, p_beta, p_cal, p_aero, p_hgcer, emm, pmm)
                                in zip(*PID_electron_iterate)
                                if abs(h_dp) < 10.0
                                if abs(h_dp) < 10.0
                                if p_dp >-10.0 or p_dp < 20.0
                                if h_cal > 0.7 or h_cer > 1.5
                                if (abs(p_beta)-1.00) < 0.1
                                if (coin-47.5) > -0.5 and (coin-47.5) < 0.5
                                if p_cal > 0.7 or p_aero > 1.5
                                if p_hgcer >1.5])
    

    p_hgcer_data = {

        "p_hgcer_eff" : len(mm_noID_electron)/len(mm_PID_electron),
    }

    f = plt.figure(figsize=(11.69,8.27))
    plt.style.use('default')

    plt.hist(missmass,bins=b.setbin(missmass,800,0,2.0),label='no cuts',histtype='step', alpha=0.7, stacked=True, fill=True)
    plt.hist(mm_noID_electron,bins=b.setbin(mm_noID_electron,800,0,2.0),label='no ID',histtype='step', alpha=0.7, stacked=True, fill=True)
    plt.hist(mm_PID_electron,bins=b.setbin(mm_PID_electron,800,0,2.0),label='PID',histtype='step', alpha=0.7, stacked=True, fill=True)
    plt.legend(loc=1)
    plt.title('Missing Mass ($GeV^2$)', fontsize =20)

    f.savefig('../OUTPUTS/missmass_%s.png' % runNum)

    noID_plot = c.densityPlot(coin_noID_electron, mm_noID_electron, 'Pion Coincident Time vs Mass ($GeV^2$) for ROC1 (w/out SHMS HGCer cuts)','Time (ns)','Mass (GeV/c^2)', 200, 800,  b,-10,10,0,2.0)
    # plt.ylim(-180.,180.)
    # plt.xlim(0.,50.)

    noID_plot[1].savefig('../OUTPUTS/noID_shms_hgcer_%s.png' % runNum)

    PID_plot = c.densityPlot(coin_PID_electron, mm_PID_electron, 'Pion Coincident Time vs Mass ($GeV^2$) for ROC1 (with SHMS HGCer cuts)','Time (ns)','Mass (GeV/c^2)', 200, 800,  b,-10,10,0,2.0)
    # plt.ylim(-180.,180.)
    # plt.xlim(0.,50.)

    PID_plot[1].savefig('../OUTPUTS/PID_shms_hgcer_%s.png' % runNum)
    
    print("========================")
    print("= %s SHMS HGCER DONE =" % runNum)
    print("========================\n\n")
          
    return [p_hgcer_data, f]

def shms_aero():

    missmass = np.array([math.sqrt(abs(emm*emm-pmm*pmm)) for (emm, pmm) in zip(emiss, pmiss)])
    
    noID_electron_iterate = [CTime_eKCoinTime_ROC1, H_gtr_dp, P_gtr_dp, H_cal_etotnorm, H_cer_npeSum, P_gtr_beta, P_cal_etotnorm, P_hgcer_npeSum, emiss, pmiss]
    
    # coin_noID_electron
    coin_noID_electron = np.array([coin-47.5
                                   for (coin, h_dp, p_dp, h_cal, h_cer, p_beta, p_cal, p_hgcer, emm, pmm)
                                   in zip(*noID_electron_iterate)
                                   if abs(h_dp) < 10.0
                                   if p_dp >-10.0 or p_dp < 20.0
                                   if h_cal > 0.7 or h_cer > 1.5
                                   if (abs(p_beta)-1.00) < 0.1
                                   if (coin-47.5) > -0.5 and (coin-47.5) < 0.5
                                   if p_cal > 0.7 or p_hgcer > 1.5])

    # mm_noID_electron
    mm_noID_electron = np.array([math.sqrt(abs(emm*emm-pmm*pmm))
                                 for (coin, h_dp, p_dp, h_cal, h_cer, p_beta, p_cal, p_hgcer, emm, pmm)
                                 in zip(*noID_electron_iterate)
                                 if abs(h_dp) < 10.0
                                 if abs(h_dp) < 10.0
                                 if p_dp >-10.0 or p_dp < 20.0
                                 if h_cal > 0.7 or h_cer > 1.5
                                 if (abs(p_beta)-1.00) < 0.1
                                 if (coin-47.5) > -0.5 and (coin-47.5) < 0.5
                                 if p_cal > 0.7 or p_hgcer > 1.5])
    
    PID_electron_iterate = [CTime_eKCoinTime_ROC1, H_gtr_dp, P_gtr_dp, H_cal_etotnorm, H_cer_npeSum, P_gtr_beta, P_cal_etotnorm, P_hgcer_npeSum, P_aero_npeSum, emiss, pmiss]
    
    # coin_PID_electron
    coin_PID_electron = np.array([coin-47.5
                                  for (coin, h_dp, p_dp, h_cal, h_cer, p_beta, p_cal, p_hgcer, p_aero, emm, pmm)
                                  in zip(*PID_electron_iterate)
                                  if abs(h_dp) < 10.0
                                  if abs(h_dp) < 10.0
                                  if p_dp >-10.0 or p_dp < 20.0
                                  if h_cal > 0.7 or h_cer > 1.5
                                  if (abs(p_beta)-1.00) < 0.1
                                  if (coin-47.5) > -0.5 and (coin-47.5) < 0.5
                                  if p_cal > 0.7 or p_hgcer > 1.5
                                  if p_aero > 1.5])
    

    # mm_PID_electron
    mm_PID_electron = np.array([math.sqrt(emm*emm-pmm*pmm)
                                for (coin, h_dp, p_dp, h_cal, h_cer, p_beta, p_cal, p_hgcer, p_aero, emm, pmm)
                                in zip(*PID_electron_iterate)
                                if abs(h_dp) < 10.0
                                if abs(h_dp) < 10.0
                                if p_dp >-10.0 or p_dp < 20.0
                                if h_cal > 0.7 or h_cer > 1.5
                                if (abs(p_beta)-1.00) < 0.1
                                if (coin-47.5) > -0.5 and (coin-47.5) < 0.5
                                if p_cal > 0.7 or p_hgcer > 1.5
                                if p_aero > 1.5])
    

    p_aero_data = {

        "p_aero_eff" : len(mm_noID_electron)/len(mm_PID_electron),
    }

    f = plt.figure(figsize=(11.69,8.27))
    plt.style.use('default')

    plt.hist(missmass,bins=b.setbin(missmass,800,0,2.0),label='no cuts',histtype='step', alpha=0.7, stacked=True, fill=True)
    plt.hist(mm_noID_electron,bins=b.setbin(mm_noID_electron,800,0,2.0),label='no ID',histtype='step', alpha=0.7, stacked=True, fill=True)
    plt.hist(mm_PID_electron,bins=b.setbin(mm_PID_electron,800,0,2.0),label='PID',histtype='step', alpha=0.7, stacked=True, fill=True)
    plt.legend(loc=1)
    plt.title('Missing Mass ($GeV^2$)', fontsize =20)

    f.savefig('../OUTPUTS/missmass_%s.png' % runNum)

    noID_plot = c.densityPlot(coin_noID_electron, mm_noID_electron, 'Pion Coincident Time vs Mass ($GeV^2$) for ROC1 (w/out SHMS Aerogel cuts)','Time (ns)','Mass (GeV/c^2)', 200, 800,  b,-10,10,0,2.0)
    # plt.ylim(-180.,180.)
    # plt.xlim(0.,50.)

    noID_plot[1].savefig('../OUTPUTS/noID_shms_aero_%s.png' % runNum)

    PID_plot = c.densityPlot(coin_PID_electron, mm_PID_electron, 'Pion Coincident Time vs Mass ($GeV^2$) for ROC1 (with SHMS Aerogel cuts)','Time (ns)','Mass (GeV/c^2)', 200, 800,  b,-10,10,0,2.0)
    # plt.ylim(-180.,180.)
    # plt.xlim(0.,50.)

    PID_plot[1].savefig('../OUTPUTS/PID_shms_aero_%s.png' % runNum)
    
    print("=======================")
    print("= %s SHMS AERO DONE =" % runNum)
    print("=======================\n\n")
          
    return [p_aero_data, f]

def shms_cal():

    missmass = np.array([math.sqrt(abs(emm*emm-pmm*pmm)) for (emm, pmm) in zip(emiss, pmiss)])
    
    noID_electron_iterate = [CTime_eKCoinTime_ROC1, H_gtr_dp, P_gtr_dp, H_cal_etotnorm, H_cer_npeSum, P_gtr_beta, P_aero_npeSum, P_hgcer_npeSum, emiss, pmiss]
    
    # coin_noID_electron
    coin_noID_electron = np.array([coin-47.5
                                   for (coin, h_dp, p_dp, h_cal, h_cer, p_beta, p_aero, p_hgcer, emm, pmm)
                                   in zip(*noID_electron_iterate)
                                   if abs(h_dp) < 10.0
                                   if p_dp >-10.0 or p_dp < 20.0
                                   if h_cal > 0.7 or h_cer > 1.5
                                   if (abs(p_beta)-1.00) < 0.1
                                   if (coin-47.5) > -0.5 and (coin-47.5) < 0.5
                                   if p_aero > 1.5 or p_hgcer > 1.5])

    # mm_noID_electron
    mm_noID_electron = np.array([math.sqrt(abs(emm*emm-pmm*pmm))
                                 for (coin, h_dp, p_dp, h_cal, h_cer, p_beta, p_aero, p_hgcer, emm, pmm)
                                 in zip(*noID_electron_iterate)
                                 if abs(h_dp) < 10.0
                                 if abs(h_dp) < 10.0
                                 if p_dp >-10.0 or p_dp < 20.0
                                 if h_cal > 0.7 or h_cer > 1.5
                                 if (abs(p_beta)-1.00) < 0.1
                                 if (coin-47.5) > -0.5 and (coin-47.5) < 0.5
                                 if p_aero > 1.5 or p_hgcer > 1.5])
    
    PID_electron_iterate = [CTime_eKCoinTime_ROC1, H_gtr_dp, P_gtr_dp, H_cal_etotnorm, H_cer_npeSum, P_gtr_beta, P_aero_npeSum, P_hgcer_npeSum, P_cal_etotnorm, emiss, pmiss]
    
    # coin_PID_electron
    coin_PID_electron = np.array([coin-47.5
                                 for (coin, h_dp, p_dp, h_cal, h_cer, p_beta, p_aero, p_hgcer, p_cal, emm, pmm)
                                  in zip(*PID_electron_iterate)
                                  if abs(h_dp) < 10.0
                                  if abs(h_dp) < 10.0
                                  if p_dp >-10.0 or p_dp < 20.0
                                  if h_cal > 0.7 or h_cer > 1.5
                                  if (abs(p_beta)-1.00) < 0.1
                                  if (coin-47.5) > -0.5 and (coin-47.5) < 0.5
                                  if p_aero > 1.5 or p_hgcer > 1.5
                                  if p_cal > 0.7])
    

    # mm_PID_electron
    mm_PID_electron = np.array([math.sqrt(emm*emm-pmm*pmm)
                                for (coin, h_dp, p_dp, h_cal, h_cer, p_beta, p_aero, p_hgcer, p_cal, emm, pmm)
                                in zip(*PID_electron_iterate)
                                if abs(h_dp) < 10.0
                                if abs(h_dp) < 10.0
                                if p_dp >-10.0 or p_dp < 20.0
                                if h_cal > 0.7 or h_cer > 1.5
                                if (abs(p_beta)-1.00) < 0.1
                                if (coin-47.5) > -0.5 and (coin-47.5) < 0.5
                                if p_aero > 1.5 or p_hgcer > 1.5
                                if p_cal > 0.7])
    

    p_cal_data = {

        "p_cal_eff" : len(mm_noID_electron)/len(mm_PID_electron),
    }

    f = plt.figure(tight_layout=True, figsize=(11.69,8.27))
    plt.style.use('default')

    plt.hist(missmass,bins=b.setbin(missmass,800,0,2.0),label='no cuts',histtype='step', alpha=0.7, stacked=True, fill=True)
    plt.hist(mm_noID_electron,bins=b.setbin(mm_noID_electron,800,0,2.0),label='no ID',histtype='step', alpha=0.7, stacked=True, fill=True)
    plt.hist(mm_PID_electron,bins=b.setbin(mm_PID_electron,800,0,2.0),label='PID',histtype='step', alpha=0.7, stacked=True, fill=True)
    plt.legend(loc=1)
    plt.title('Missing Mass ($GeV^2$)', fontsize =20)

    f.savefig('../OUTPUTS/missmass_%s.png' % runNum)

    noID_plot = c.densityPlot(coin_noID_electron, mm_noID_electron, 'Pion Coincident Time vs Mass ($GeV^2$) for ROC1 (w/out SHMS Calorimeter cuts)','Time (ns)','Mass (GeV/c^2)', 200, 800,  b,-10,10,0,2.0)
    # plt.ylim(-180.,180.)
    # plt.xlim(0.,50.)

    noID_plot[1].savefig('../OUTPUTS/noID_shms_cal_%s.png' % runNum)

    PID_plot = c.densityPlot(coin_PID_electron, mm_PID_electron, 'Pion Coincident Time vs Mass ($GeV^2$) for ROC1 (with SHMS Calorimeter cuts)','Time (ns)','Mass (GeV/c^2)', 200, 800,  b,-10,10,0,2.0)
    # plt.ylim(-180.,180.)
    # plt.xlim(0.,50.)

    PID_plot[1].savefig('../OUTPUTS/PID_shms_cal_%s.png' % runNum)
    
    print("======================")
    print("= %s SHMS CAL DONE =" % runNum)
    print("======================\n\n")
          
    return [p_cal_data, f]

def main():

    h_cer_data = hms_cer()
    h_cal_data = hms_cal()
    p_hgcer_data = shms_hgcer()
    p_aero_data = shms_aero()
    p_cal_data = shms_cal()

    runNum_dict = {
        "run_number" : runNum
    }

    datadict = {}
    for d in (runNum_dict, h_cer_data[0], h_cal_data[0], p_hgcer_data[0], p_aero_data[0], p_cal_data[0]): 
        datadict.update(d)
    data = {i : datadict[i] for i in sorted(datadict.keys())}

    # plt.show()

    table  = pd.DataFrame([data], columns=data.keys())

    table = table.reindex(sorted(table.columns), axis=1)
    
    file_exists = os.path.isfile(filename)

    if file_exists:
        table.to_csv(filename, index = False, header=False, mode='a',)
    else:
        table.to_csv(filename, index = False, header=True, mode='a',)

if __name__ == '__main__':
    main()
