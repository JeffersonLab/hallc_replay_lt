#! /usr/bin/python

#
# Description:
# ================================================================
# Time-stamp: "2020-05-12 20:03:29 trottar"
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

filename = "%s/UTIL_KAONLT/scripts/pid/OUTPUTS/pid_data.csv" % (REPLAYPATH)
rootName = "%s/UTIL_KAONLT/ROOTfiles/pid_coin_offline_%s_%s.root" % (REPLAYPATH, runNum,MaxEvent)

'''
ANALYSIS TREE, T
'''

tree = up.open(rootName)["T"]
branch = klt.pyBranch(tree)

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

missmass = np.array(np.sqrt(abs(emiss*emiss-pmiss*pmiss)))

#
# Mp = 0.93828
# MPi = 0.13957018
# MK = 0.493677
# MMpi = np.array([math.sqrt(abs((em + math.sqrt(abs((MK*MK) + (gtrp*gtrp))) - math.sqrt(abs((MPi*MPi) + (gtrp*gtrp) - (pm*pm))) ))**2) for (em, pm, gtrp) in zip(emiss, pmiss, P_gtr_p)])
# MMK = np.array([math.sqrt(abs((em*em)-(pm*pm))) for (em, pm) in zip(emiss, pmiss)])
# MMp = np.array([math.sqrt(abs((em + math.sqrt(abs((MK*MK) + (gtrp*gtrp))) - math.sqrt(abs((Mp*Mp) + (gtrp*gtrp) - (pm*pm))) ))**2) for (em, pm, gtrp) in zip(emiss, pmiss, P_gtr_p)])


r = klt.pyRoot()

fout = REPLAYPATH+'/UTIL_KAONLT/DB/CUTS/run_type/pid_eff.cuts'

# read in cuts file and make dictionary
c = klt.pyPlot(None)
readDict = c.read_dict(fout,runNum)

# This method calls several methods in kaonlt package. It is required to create properly formated
# dictionaries. The evaluation must be in the analysis script because the analysis variables (i.e. the
# leaves of interest) are not defined in the kaonlt package. This makes the system more flexible
# overall, but a bit more cumbersome in the analysis script. Perhaps one day a better solution will be
# implimented.
def make_cutDict(cut,inputDict=None):

    global c

    c = klt.pyPlot(readDict)
    x = c.w_dict(cut)
    print("%s" % cut)
    print("x ", x)
    
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

cutDict = make_cutDict("h_ecut_eff")
cutDict = make_cutDict("h_ecut_eff_no_cer",cutDict)
cutDict = make_cutDict("h_ecut_eff_no_cal",cutDict)
cutDict = make_cutDict("p_kcut_eff",cutDict)
cutDict = make_cutDict("p_kcut_eff_no_hgcer",cutDict)
cutDict = make_cutDict("p_kcut_eff_no_aero",cutDict)
cutDict = make_cutDict("p_kcut_eff_no_cal",cutDict)
c = klt.pyPlot(cutDict)

def hms_cer():

    # coin_noID_electron
    coin_noID_electron = np.array(c.add_cut(CTime_eKCoinTime_ROC1,"h_ecut_eff_no_cer")-47.5)

    noID_electron_iterate = [CTime_eKCoinTime_ROC1, H_gtr_dp, P_gtr_dp, P_cal_etotnorm, H_gtr_beta, H_cal_etotnorm, emiss, pmiss]
    
    # mm_noID_electron
    mm_noID_electron = np.array(c.add_cut(missmass,"h_ecut_eff_no_cer"))
    
    # coin_PID_electron
    coin_PID_electron = np.array(c.add_cut(CTime_eKCoinTime_ROC1,"h_ecut_eff")-47.5)
    
    # mm_PID_electron
    mm_PID_electron = np.array(c.add_cut(missmass,"h_ecut_eff"))

    h_cer_data = {

        "h_cer_eff" : len(mm_noID_electron)/len(mm_PID_electron),
    }

    f = plt.figure(figsize=(11.69,8.27))
    plt.style.use('default')

    plt.hist(missmass,bins=c.setbin(missmass,800,0,2.0),label='no cuts',histtype='step', alpha=0.7, stacked=True, fill=True)
    plt.hist(mm_noID_electron,bins=c.setbin(mm_noID_electron,800,0,2.0),label='no ID',histtype='step', alpha=0.7, stacked=True, fill=True)
    plt.hist(mm_PID_electron,bins=c.setbin(mm_PID_electron,800,0,2.0),label='PID',histtype='step', alpha=0.7, stacked=True, fill=True)
    plt.legend(loc=1)
    plt.title('Missing Mass ($GeV^2$)', fontsize =20)

    f.savefig(REPLAYPATH+'/UTIL_KAONLT/scripts/pid/OUTPUTS/missmass_%s.png' % runNum)

    noID_plot = c.densityPlot(coin_noID_electron, mm_noID_electron, 'Electron Coincident Time vs Mass ($GeV^2$) for ROC1 (w/out HMS Cherenkov cuts)','Time (ns)','Mass (GeV/c^2)', 200, 800,  c,-10,10,0,2.0)
    # plt.ylim(-180.,180.)
    # plt.xlim(0.,50.)

    noID_plot[1].savefig(REPLAYPATH+'/UTIL_KAONLT/scripts/pid/OUTPUTS/noID_hms_cer_%s.png' % runNum)

    PID_plot = c.densityPlot(coin_PID_electron, mm_PID_electron, 'Electron Coincident Time vs Mass ($GeV^2$) for ROC1 (with HMS Cherenkov cuts)','Time (ns)','Mass (GeV/c^2)', 200, 800,  c,-10,10,0,2.0)
    # plt.ylim(-180.,180.)
    # plt.xlim(0.,50.)

    PID_plot[1].savefig(REPLAYPATH+'/UTIL_KAONLT/scripts/pid/OUTPUTS/PID_hms_cer_%s.png' % runNum)
    
    print("=====================")
    print("= %s HMS CER DONE =" % runNum)
    print("=====================\n\n")
          
    return h_cer_data

def hms_cal():
    
    # coin_noID_electron
    coin_noID_electron = np.array(c.add_cut(CTime_eKCoinTime_ROC1,"h_ecut_eff_no_cal")-47.5)

    # mm_noID_electron
    mm_noID_electron = np.array(c.add_cut(missmass,"h_ecut_eff_no_cal"))
    
    # coin_PID_electron
    coin_PID_electron = np.array(c.add_cut(CTime_eKCoinTime_ROC1,"h_ecut_eff")-47.5)
    
    # mm_PID_electron
    mm_PID_electron = np.array(c.add_cut(missmass,"h_ecut_eff"))
    
    h_cal_data = {

        "h_cal_eff" : len(mm_noID_electron)/len(mm_PID_electron),
    }

    f = plt.figure(figsize=(11.69,8.27))
    plt.style.use('default')

    plt.hist(missmass,bins=c.setbin(missmass,800,0,2.0),label='no cuts',histtype='step', alpha=0.7, stacked=True, fill=True)
    plt.hist(mm_noID_electron,bins=c.setbin(mm_noID_electron,800,0,2.0),label='no ID',histtype='step', alpha=0.7, stacked=True, fill=True)
    plt.hist(mm_PID_electron,bins=c.setbin(mm_PID_electron,800,0,2.0),label='PID',histtype='step', alpha=0.7, stacked=True, fill=True)
    plt.legend(loc=1)
    plt.title('Missing Mass ($GeV^2$)', fontsize =20)

    f.savefig(REPLAYPATH+'/UTIL_KAONLT/scripts/pid/OUTPUTS/missmass_%s.png' % runNum)

    noID_plot = c.densityPlot(coin_noID_electron, mm_noID_electron, 'Electron Coincident Time vs Mass ($GeV^2$) for ROC1 (w/out HMS Calorimeter cuts)','Time (ns)','Mass (GeV/c^2)', 200, 800,  c,-10,10,0,2.0)
    # plt.ylim(-180.,180.)
    # plt.xlim(0.,50.)

    noID_plot[1].savefig(REPLAYPATH+'/UTIL_KAONLT/scripts/pid/OUTPUTS/noID_hms_cal_%s.png' % runNum)

    PID_plot = c.densityPlot(coin_PID_electron, mm_PID_electron, 'Electron Coincident Time vs Mass ($GeV^2$) for ROC1 (with HMS Calorimeter cuts)','Time (ns)','Mass (GeV/c^2)', 200, 800,  c,-10,10,0,2.0)
    # plt.ylim(-180.,180.)
    # plt.xlim(0.,50.)

    PID_plot[1].savefig(REPLAYPATH+'/UTIL_KAONLT/scripts/pid/OUTPUTS/PID_hms_cal_%s.png' % runNum)
    
    print("=====================")
    print("= %s HMS CAL DONE =" % runNum)
    print("=====================\n\n")
          
    return h_cal_data

def shms_hgcer():
    
    # coin_noID_electron
    coin_noID_electron = np.array(c.add_cut(CTime_eKCoinTime_ROC1,"p_kcut_eff_no_hgcer")-47.5)

    # mm_noID_electron
    mm_noID_electron = np.array(c.add_cut(missmass,"p_kcut_eff_no_hgcer"))
    
    # coin_PID_electron
    coin_PID_electron = np.array(c.add_cut(CTime_eKCoinTime_ROC1,"p_kcut_eff")-47.5)
    
    # mm_PID_electron
    mm_PID_electron = np.array(c.add_cut(missmass,"p_kcut_eff"))    

    p_hgcer_data = {

        "p_hgcer_eff" : len(mm_noID_electron)/len(mm_PID_electron),
    }

    f = plt.figure(figsize=(11.69,8.27))
    plt.style.use('default')

    plt.hist(missmass,bins=c.setbin(missmass,800,0,2.0),label='no cuts',histtype='step', alpha=0.7, stacked=True, fill=True)
    plt.hist(mm_noID_electron,bins=c.setbin(mm_noID_electron,800,0,2.0),label='no ID',histtype='step', alpha=0.7, stacked=True, fill=True)
    plt.hist(mm_PID_electron,bins=c.setbin(mm_PID_electron,800,0,2.0),label='PID',histtype='step', alpha=0.7, stacked=True, fill=True)
    plt.legend(loc=1)
    plt.title('Missing Mass ($GeV^2$)', fontsize =20)

    f.savefig(REPLAYPATH+'/UTIL_KAONLT/scripts/pid/OUTPUTS/missmass_%s.png' % runNum)

    noID_plot = c.densityPlot(coin_noID_electron, mm_noID_electron, 'Pion Coincident Time vs Mass ($GeV^2$) for ROC1 (w/out SHMS HGCer cuts)','Time (ns)','Mass (GeV/c^2)', 200, 800,  c,-10,10,0,2.0)
    # plt.ylim(-180.,180.)
    # plt.xlim(0.,50.)

    noID_plot[1].savefig(REPLAYPATH+'/UTIL_KAONLT/scripts/pid/OUTPUTS/noID_shms_hgcer_%s.png' % runNum)

    PID_plot = c.densityPlot(coin_PID_electron, mm_PID_electron, 'Pion Coincident Time vs Mass ($GeV^2$) for ROC1 (with SHMS HGCer cuts)','Time (ns)','Mass (GeV/c^2)', 200, 800,  c,-10,10,0,2.0)
    # plt.ylim(-180.,180.)
    # plt.xlim(0.,50.)

    PID_plot[1].savefig(REPLAYPATH+'/UTIL_KAONLT/scripts/pid/OUTPUTS/PID_shms_hgcer_%s.png' % runNum)
    
    print("========================")
    print("= %s SHMS HGCER DONE =" % runNum)
    print("========================\n\n")
          
    return p_hgcer_data

def shms_aero():
    
    # coin_noID_electron
    coin_noID_electron = np.array(c.add_cut(CTime_eKCoinTime_ROC1,"p_kcut_eff_no_aero")-47.5)

    # mm_noID_electron
    mm_noID_electron = np.array(c.add_cut(missmass,"p_kcut_eff_no_aero"))
    
    # coin_PID_electron
    coin_PID_electron = np.array(c.add_cut(CTime_eKCoinTime_ROC1,"p_kcut_eff")-47.5)
    
    # mm_PID_electron
    mm_PID_electron = np.array(c.add_cut(missmass,"p_kcut_eff"))        

    p_aero_data = {

        "p_aero_eff" : len(mm_noID_electron)/len(mm_PID_electron),
    }

    f = plt.figure(figsize=(11.69,8.27))
    plt.style.use('default')

    plt.hist(missmass,bins=c.setbin(missmass,800,0,2.0),label='no cuts',histtype='step', alpha=0.7, stacked=True, fill=True)
    plt.hist(mm_noID_electron,bins=c.setbin(mm_noID_electron,800,0,2.0),label='no ID',histtype='step', alpha=0.7, stacked=True, fill=True)
    plt.hist(mm_PID_electron,bins=c.setbin(mm_PID_electron,800,0,2.0),label='PID',histtype='step', alpha=0.7, stacked=True, fill=True)
    plt.legend(loc=1)
    plt.title('Missing Mass ($GeV^2$)', fontsize =20)

    f.savefig(REPLAYPATH+'/UTIL_KAONLT/scripts/pid/OUTPUTS/missmass_%s.png' % runNum)

    noID_plot = c.densityPlot(coin_noID_electron, mm_noID_electron, 'Pion Coincident Time vs Mass ($GeV^2$) for ROC1 (w/out SHMS Aerogel cuts)','Time (ns)','Mass (GeV/c^2)', 200, 800,  c,-10,10,0,2.0)
    # plt.ylim(-180.,180.)
    # plt.xlim(0.,50.)

    noID_plot[1].savefig(REPLAYPATH+'/UTIL_KAONLT/scripts/pid/OUTPUTS/noID_shms_aero_%s.png' % runNum)

    PID_plot = c.densityPlot(coin_PID_electron, mm_PID_electron, 'Pion Coincident Time vs Mass ($GeV^2$) for ROC1 (with SHMS Aerogel cuts)','Time (ns)','Mass (GeV/c^2)', 200, 800,  c,-10,10,0,2.0)
    # plt.ylim(-180.,180.)
    # plt.xlim(0.,50.)

    PID_plot[1].savefig(REPLAYPATH+'/UTIL_KAONLT/scripts/pid/OUTPUTS/PID_shms_aero_%s.png' % runNum)
    
    print("=======================")
    print("= %s SHMS AERO DONE =" % runNum)
    print("=======================\n\n")
          
    return p_aero_data

def shms_cal():
    
    # coin_noID_electron
    coin_noID_electron = np.array(c.add_cut(CTime_eKCoinTime_ROC1,"p_kcut_eff_no_cal")-47.5)

    # mm_noID_electron
    mm_noID_electron = np.array(c.add_cut(missmass,"p_kcut_eff_no_cal"))
    
    # coin_PID_electron
    coin_PID_electron = np.array(c.add_cut(CTime_eKCoinTime_ROC1,"p_kcut_eff")-47.5)
    
    # mm_PID_electron
    mm_PID_electron = np.array(c.add_cut(missmass,"p_kcut_eff"))        

    p_cal_data = {

        "p_cal_eff" : len(mm_noID_electron)/len(mm_PID_electron),
    }

    f = plt.figure(tight_layout=True, figsize=(11.69,8.27))
    plt.style.use('default')

    plt.hist(missmass,bins=c.setbin(missmass,800,0,2.0),label='no cuts',histtype='step', alpha=0.7, stacked=True, fill=True)
    plt.hist(mm_noID_electron,bins=c.setbin(mm_noID_electron,800,0,2.0),label='no ID',histtype='step', alpha=0.7, stacked=True, fill=True)
    plt.hist(mm_PID_electron,bins=c.setbin(mm_PID_electron,800,0,2.0),label='PID',histtype='step', alpha=0.7, stacked=True, fill=True)
    plt.legend(loc=1)
    plt.title('Missing Mass ($GeV^2$)', fontsize =20)

    f.savefig(REPLAYPATH+'/UTIL_KAONLT/scripts/pid/OUTPUTS/missmass_%s.png' % runNum)

    noID_plot = c.densityPlot(coin_noID_electron, mm_noID_electron, 'Pion Coincident Time vs Mass ($GeV^2$) for ROC1 (w/out SHMS Calorimeter cuts)','Time (ns)','Mass (GeV/c^2)', 200, 800,  c,-10,10,0,2.0)
    # plt.ylim(-180.,180.)
    # plt.xlim(0.,50.)

    noID_plot[1].savefig(REPLAYPATH+'/UTIL_KAONLT/scripts/pid/OUTPUTS/noID_shms_cal_%s.png' % runNum)

    PID_plot = c.densityPlot(coin_PID_electron, mm_PID_electron, 'Pion Coincident Time vs Mass ($GeV^2$) for ROC1 (with SHMS Calorimeter cuts)','Time (ns)','Mass (GeV/c^2)', 200, 800,  c,-10,10,0,2.0)
    # plt.ylim(-180.,180.)
    # plt.xlim(0.,50.)

    PID_plot[1].savefig(REPLAYPATH+'/UTIL_KAONLT/scripts/pid/OUTPUTS/PID_shms_cal_%s.png' % runNum)
    
    print("======================")
    print("= %s SHMS CAL DONE =" % runNum)
    print("======================\n\n")
          
    return p_cal_data

def main():

    h_cer_data = hms_cer()
    h_cal_data = hms_cal()
    p_hgcer_data = shms_hgcer()
    p_aero_data = shms_aero()
    p_cal_data = shms_cal()

    runNum_dict = {
        "run_number" : int(runNum)
    }

    datadict = {}
    for d in (runNum_dict, h_cer_data, h_cal_data, p_hgcer_data, p_aero_data, p_cal_data): 
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
