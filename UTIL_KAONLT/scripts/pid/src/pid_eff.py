#! /usr/bin/python

#
# Description:
# ================================================================
# Time-stamp: "2020-04-17 15:02:06 trottar"
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
import matplotlib.backends.backend_pdf
import sys, math, os, subprocess

sys.path.insert(0, 'python/')
import root2py as r2p

runNum = sys.argv[1]
MaxEvent=sys.argv[2]
# MaxEvent=50000

b = r2p.pyBin()
c = r2p.pyPlot(None)

USER = subprocess.getstatusoutput("whoami")

# pdf = matplotlib.backends.backend_pdf.PdfPages("/u/group/c-kaonlt/USERS/%s/hallc_replay_lt/UTIL_KAONLT/scripts/pid/OUTPUTS/pid_plots.pdf"  % USER[1]) 

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

    noID_electron_iterate = [CTime_eKCoinTime_ROC1, H_gtr_dp, P_gtr_dp, P_cal_etotnorm, P_gtr_beta, H_cal_etotnorm, emiss, pmiss]
    # coin_noID_electron
    coin_noID_electron = [coin
                          for coin, h_dp, p_dp, p_cal, p_beta, h_cal, emm, pmm
                          in zip(*noID_electron_iterate)
                          if abs(h_dp) < 10.0
                          if p_dp >-10.0 or p_dp < 20.0
                          if p_cal <0.6
                          if (abs(p_beta)-1) < 0.1
                          if (coin-47.5) > -0.5 and (coin-47.5) < 0.5
                          if h_cal > 0.995 and h_cal < 1.015]

    # mm_noID_electron
    mm_noID_electron = [np.sqrt(emm*emm-pmm*pmm)
                          for coin, h_dp, p_dp, p_cal, p_beta, h_cal, emm, pmm
                          in zip(*noID_electron_iterate)
                          if abs(h_dp) < 10.0
                          if p_dp >-10.0 or p_dp < 20.0
                          if p_cal <0.6
                          if (abs(p_beta)-1) < 0.1
                          if (coin-47.5) > -0.5 and (coin-47.5) < 0.5
                          if h_cal > 0.995 and h_cal < 1.015]

    PID_electron_iterate = [CTime_eKCoinTime_ROC1, H_gtr_dp, P_gtr_dp, P_cal_etotnorm, P_gtr_beta, H_cal_etotnorm, H_cer_npeSum, emiss, pmiss]
    # coin_PID_electron
    coin_PID_electron = [coin
                         for coin, h_dp, p_dp, p_cal, p_beta, h_cal, h_cer, emm, pmm
                         in zip(*PID_electron_iterate)
                         if abs(h_dp) < 10.0
                         if p_dp >-10.0 or p_dp < 20.0
                         if p_cal <0.6
                         if (abs(p_beta)-1) < 0.1
                         if (coin-47.5) > -0.5 and (coin-47.5) < 0.5
                         if h_cal > 0.995 and h_cal < 1.015
                         if h_cer > 3.0]

    # mm_PID_electron
    mm_PID_electron = [np.sqrt(emm*emm-pmm*pmm)
                       for coin, h_dp, p_dp, p_cal, p_beta, h_cal, h_cer, emm, pmm
                       in zip(*PID_electron_iterate)
                       if abs(h_dp) < 10.0
                       if p_dp >-10.0 or p_dp < 20.0
                       if p_cal <0.6
                       if (abs(p_beta)-1) < 0.1
                       if (coin-47.5) > -0.5 and (coin-47.5) < 0.5
                       if h_cal > 0.995 and h_cal < 1.015
                       if h_cer > 3.0]

    h_cer_data = {
        
        "e coin ratio" : np.average(coin_noID_electron)/np.average(coin_PID_electron),
        "e missing mass ratio" : np.average(mm_noID_electron)/np.average(mm_PID_electron),
    }

    print(h_cer_data)

    f = plt.figure(figsize=(11.69,8.27))
    plt.style.use('default')

    ax = f.add_subplot(211)
    ax.hist(mm_noID_electron,bins=b.setbin(mm_noID_electron,200),label='no ID',histtype='step', alpha=0.5, stacked=True, fill=True)
    ax.hist(mm_PID_electron,bins=b.setbin(mm_PID_electron,200),label='PID',histtype='step', alpha=0.5, stacked=True, fill=True)
    ax.legend(loc=1)
    plt.title('Missing Mass ($GeV^2$)', fontsize =20)#

    noID_plot = c.densityPlot(coin_noID_electron, mm_noID_electron, 'Electron Coincident Time vs Mass ($GeV^{2}$) for ROC1 (w/out Cherenkov cuts)','Time (ns)','Mass (GeV/c^{2})', 200, 200,  b)
    # plt.ylim(-180.,180.)
    # plt.xlim(0.,50.)

    PID_plot = c.densityPlot(coin_PID_electron, mm_PID_electron, 'Electron Coincident Time vs Mass ($GeV^{2}$) for ROC1 (with Cherenkov cuts)','Time (ns)','Mass (GeV/c^{2})', 200, 200,  b)
    # plt.ylim(-180.,180.)
    # plt.xlim(0.,50.)

    # for f in range(1, plt.figure().number):
    #     pdf.savefig(f)
    # pdf.close()
    
    print("============================================================================\n\n")
          
    return h_cer_data

def main():

    h_cer_data = hms_cer()

    plt.show()

    table  = pd.DataFrame([pid_data], columns=pid_data.keys())

    table = table.reindex(sorted(table.columns), axis=1)
    
    file_exists = os.path.isfile(filename)

    if file_exists:
        table.to_csv(filename, index = False, header=False, mode='a',)
    else:
        table.to_csv(filename, index = False, header=True, mode='a',)

if __name__ == '__main__':
    main()
