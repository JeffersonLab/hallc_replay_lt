#! /usr/bin/python

#
# Description:
# ================================================================
# Time-stamp: "2020-12-09 12:25:17 trottar"
# ================================================================
#
# Author:  Richard L. Trotta III <trotta@cua.edu>
#
# Copyright (c) trottar
#
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from csv import DictReader
import sys, os, subprocess

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

inp_f = "%s/UTIL_KAONLT/scripts/luminosity/OUTPUTS/lumi_data.csv" % str(REPLAYPATH)
out_f = "%s/UTIL_KAONLT/scripts/luminosity/OUTPUTS/yield_data.csv" % str(REPLAYPATH)

try:
    lumi_data = dict(pd.read_csv(inp_f))
except IOError:
    print("Error: %s does not appear to exist." % inp_f)
print(lumi_data.keys())
    
# prints first instance of run number-> print(lumi_data["run number"][0])
target = "carbon"

numRuns = len(lumi_data["run number"])
    
def calc_yield():
    current = [lumi_data["charge"][i]/lumi_data["time"][i]
               for i,evts in enumerate(lumi_data["run number"])]
    rate_HMS = [lumi_data["HMS_evts_scalar"][i]/lumi_data["time"][i]
                for i,evts in enumerate(lumi_data["run number"])]
    rate_HMS = pd.Series(rate_HMS).fillna(0).tolist()
    rate_SHMS = [lumi_data["SHMS_evts_scalar"][i]/lumi_data["time"][i]
                for i,evts in enumerate(lumi_data["run number"])]
    rate_SHMS = pd.Series(rate_SHMS).fillna(0).tolist()
    # cpuLT_HMS = [abs(lumi_data["TRIG3_cut"][i]/(((lumi_data["TRIG3_scaler"][i]/lumi_data["ps3"][i])-lumi_data["accp_edtm"][i])))
                 # for i,evt in enumerate(lumi_data["run number"])]
    cpuLT_HMS = [lumi_data["CPULT_scaler"][i]
                 for i,evt in enumerate(lumi_data["run number"])]                 
    cpuLT_HMS  = pd.Series(cpuLT_HMS).fillna(0).tolist()
    cpuLT_HMS_uncern = [np.sqrt(abs(cpuLT_HMS[i]))/cpuLT_HMS[i]
                        for i,evt in enumerate(lumi_data["run number"])]
    cpuLT_HMS_uncern = pd.Series(cpuLT_HMS_uncern).fillna(0).tolist()
    # cpuLT_SHMS = [abs(lumi_data["TRIG1_cut"][i]/(((lumi_data["TRIG1_scaler"][i]/lumi_data["ps1"][i])-lumi_data["accp_edtm"][i])))
    #               for i,evt in enumerate(lumi_data["run number"])]
    cpuLT_SHMS = [lumi_data["CPULT_scaler"][i]
                 for i,evt in enumerate(lumi_data["run number"])]    
    cpuLT_SHMS = pd.Series(cpuLT_SHMS).fillna(0).tolist()
    cpuLT_SHMS_uncern = [np.sqrt(abs(cpuLT_SHMS[i]))/cpuLT_SHMS[i]
                         for i,evt in enumerate(lumi_data["run number"])]
    cpuLT_SHMS_uncern = pd.Series(cpuLT_SHMS_uncern).fillna(0).tolist()
    uncern_HMS_evts_scalar = [np.sqrt(lumi_data["TRIG3_scaler"][i])/lumi_data["TRIG3_scaler"][i]
                       for i,evt in enumerate(lumi_data["run number"])]
    uncern_HMS_evts_scalar  = pd.Series(uncern_HMS_evts_scalar).fillna(0).tolist()
    uncern_SHMS_evts_scalar = [np.sqrt(lumi_data["TRIG1_scaler"][i])/lumi_data["TRIG1_scaler"][i]
                        for i,evt in enumerate(lumi_data["run number"])]
    uncern_SHMS_evts_scalar = pd.Series(uncern_SHMS_evts_scalar).fillna(0).tolist()
    uncern_HMS_evts_notrack = [np.sqrt(lumi_data["h_int_goodscin_evts"][i])/lumi_data["h_int_goodscin_evts"][i]
                       for i,evt in enumerate(lumi_data["run number"])]
    uncern_HMS_evts_notrack  = pd.Series(uncern_HMS_evts_notrack).fillna(0).tolist()
    uncern_SHMS_evts_notrack = [np.sqrt(lumi_data["p_int_goodscin_evts"][i])/lumi_data["p_int_goodscin_evts"][i]
                        for i,evt in enumerate(lumi_data["run number"])]
    uncern_SHMS_evts_notrack = pd.Series(uncern_SHMS_evts_notrack).fillna(0).tolist()
    uncern_HMS_evts_track = [np.sqrt(lumi_data["h_int_goodscin_evts"][i])/lumi_data["h_int_goodscin_evts"][i]
                       for i,evt in enumerate(lumi_data["run number"])]
    uncern_HMS_evts_track  = pd.Series(uncern_HMS_evts_track).fillna(0).tolist()
    uncern_SHMS_evts_track = [np.sqrt(lumi_data["p_int_goodscin_evts"][i])/lumi_data["p_int_goodscin_evts"][i]
                        for i,evt in enumerate(lumi_data["run number"])]
    uncern_SHMS_evts_track = pd.Series(uncern_SHMS_evts_track).fillna(0).tolist()
    yield_HMS_notrack = [(lumi_data["h_int_goodscin_evts"][i])/(lumi_data["charge"][i]*cpuLT_HMS[i])
    for i,evt in enumerate(lumi_data["run number"])]
    yield_HMS_track = [(lumi_data["h_int_goodscin_evts"][i])/(lumi_data["charge"][i]*cpuLT_HMS[i]*(1-lumi_data["etrack"][i]))
    for i,evt in enumerate(lumi_data["run number"])]
    yield_HMS_scalar = [(lumi_data["TRIG3_scaler"][i])/(lumi_data["charge"][i])
                 for i,evt in enumerate(lumi_data["run number"])]
    yield_HMS_scalar = pd.Series(yield_HMS_scalar).fillna(0).tolist()
    yield_HMS_notrack = pd.Series(yield_HMS_notrack).fillna(0).tolist()
    yield_HMS_track = pd.Series(yield_HMS_track).fillna(0).tolist()
    yield_SHMS_notrack = [(lumi_data["p_int_goodscin_evts"][i])/(lumi_data["charge"][i]*cpuLT_SHMS[i])
    for i,evt in enumerate(lumi_data["run number"])]
    yield_SHMS_track = [(lumi_data["h_int_goodscin_evts"][i])/(lumi_data["charge"][i]*cpuLT_SHMS[i]*(lumi_data["ptrack"][i]))
    for i,evt in enumerate(lumi_data["run number"])]
    yield_SHMS_scalar = [(lumi_data["TRIG1_scaler"][i])/(lumi_data["charge"][i])
                  for i,evt in enumerate(lumi_data["run number"])]
    yield_SHMS_scalar = pd.Series(yield_SHMS_scalar).fillna(0).tolist()
    yield_SHMS_notrack = pd.Series(yield_SHMS_notrack).fillna(0).tolist()
    yield_SHMS_track = pd.Series(yield_SHMS_track).fillna(0).tolist()
    
    count_HMS = [(lumi_data["h_int_goodscin_evts"][i])
                  for i,evt in enumerate(lumi_data["run number"])]
    count_HMS = pd.Series(count_HMS).fillna(0).tolist()    
    count_SHMS = [(lumi_data["p_int_goodscin_evts"][i])
                  for i,evt in enumerate(lumi_data["run number"])]
    count_SHMS = pd.Series(count_SHMS).fillna(0).tolist()

    etrack_HMS = [(1-lumi_data["etrack"][i])
                  for i,evt in enumerate(lumi_data["run number"])]
    etrack_HMS = pd.Series(etrack_HMS).fillna(0).tolist()            
    ptrack_SHMS = [(lumi_data["ptrack"][i])
                  for i,evt in enumerate(lumi_data["run number"])]
    ptrack_SHMS = pd.Series(ptrack_SHMS).fillna(0).tolist()


    for i,curr in enumerate(current):
        if curr == min(current):
            if lumi_data["ps3"][i] !=0:
                min_yield_HMS_scalar = yield_HMS_scalar[i]
            else:
                min_yield_HMS_scalar = 1
            if lumi_data["ps1"][i] !=0:
                min_yield_SHMS_scalar = yield_SHMS_scalar[i]
            else:
                min_yield_SHMS_scalar = 1
                
    for i,curr in enumerate(current):
        if curr == min(current):
            if lumi_data["ps3"][i] !=0:
                min_yield_HMS_notrack = yield_HMS_notrack[i]
            else:
                min_yield_HMS_notrack = 1
            if lumi_data["ps1"][i] !=0:
                min_yield_SHMS_notrack = yield_SHMS_notrack[i]
            else:
                min_yield_SHMS_notrack = 1

    for i,curr in enumerate(current):
        if curr == min(current):
            if lumi_data["ps3"][i] !=0:
                min_yield_HMS_track = yield_HMS_track[i]
            else:
                min_yield_HMS_track = 1
            if lumi_data["ps1"][i] !=0:
                min_yield_SHMS_track = yield_SHMS_track[i]
            else:
                min_yield_SHMS_track = 1

    yieldRel_HMS_scalar = [yield_HMS_scalar[i]/min_yield_HMS_scalar for i,evt in enumerate(lumi_data["run number"])]
    # yieldRel_HMS_scalar = pd.Series(yieldRel_HMS_scalar).fillna(0).tolist()
    yieldRel_SHMS_scalar = [yield_SHMS_scalar[i]/min_yield_SHMS_scalar for i,evt in enumerate(lumi_data["run number"])]
    # yieldRel_SHMS_scalar = pd.Series(yieldRel_SHMS_scalar).fillna(0).tolist()

    yieldRel_HMS_notrack = [yield_HMS_notrack[i]/min_yield_HMS_notrack for i,evt in enumerate(lumi_data["run number"])]
    # yieldRel_HMS_notrack = pd.Series(yieldRel_HMS_notrack).fillna(0).tolist()
    yieldRel_SHMS_notrack = [yield_SHMS_notrack[i]/min_yield_SHMS_notrack for i,evt in enumerate(lumi_data["run number"])]
    # yieldRel_SHMS_notrack = pd.Series(yieldRel_SHMS_notrack).fillna(0).tolist()

    yieldRel_HMS_track = [yield_HMS_track[i]/min_yield_HMS_track for i,evt in enumerate(lumi_data["run number"])]
    # yieldRel_HMS_track = pd.Series(yieldRel_HMS_track).fillna(0).tolist()
    yieldRel_SHMS_track = [yield_SHMS_track[i]/min_yield_SHMS_track for i,evt in enumerate(lumi_data["run number"])]
    # yieldRel_SHMS_track = pd.Series(yieldRel_SHMS_track).fillna(0).tolist()

    return [current,rate_HMS,rate_SHMS,cpuLT_HMS,cpuLT_SHMS,uncern_HMS_evts_scalar,uncern_SHMS_evts_scalar,yield_HMS_scalar,yield_SHMS_scalar,yieldRel_HMS_scalar,yieldRel_SHMS_scalar,uncern_HMS_evts_notrack,uncern_SHMS_evts_notrack,yield_HMS_notrack,yield_SHMS_notrack,yieldRel_HMS_notrack,yieldRel_SHMS_notrack,uncern_HMS_evts_track,uncern_SHMS_evts_track,yield_HMS_track,yield_SHMS_track,yieldRel_HMS_track,yieldRel_SHMS_track,count_HMS,count_SHMS,etrack_HMS,ptrack_SHMS]

def plot_yield():

    [current,rate_HMS,rate_SHMS,cpuLT_HMS,cpuLT_SHMS,uncern_HMS_evts_scalar,uncern_SHMS_evts_scalar,yield_HMS_scalar,yield_SHMS_scalar,yieldRel_HMS_scalar,yieldRel_SHMS_scalar,uncern_HMS_evts_notrack,uncern_SHMS_evts_notrack,yield_HMS_notrack,yield_SHMS_notrack,yieldRel_HMS_notrack,yieldRel_SHMS_notrack,uncern_HMS_evts_track,uncern_SHMS_evts_track,yield_HMS_track,yield_SHMS_track,yieldRel_HMS_track,yieldRel_SHMS_track,count_HMS,count_SHMS,etrack_HMS,ptrack_SHMS] = calc_yield()

    for i, val in enumerate(lumi_data["run number"]):
        print("Run numbers:",lumi_data["run number"][i],"Current Values:",current[i])
    
    relYieldPlot = plt.figure(figsize=(12,8))

    #HMS plot scalar
    plt.subplot(2,3,1)    
    plt.grid(zorder=1)
    plt.xlim(0,60)
    #plt.ylim(0.98,1.02)
    plt.plot([0,60], [1,1], 'r-',zorder=2)
    plt.errorbar(current,yieldRel_HMS_scalar,yerr=uncern_HMS_evts_scalar,color='black',linestyle='None',zorder=3)
    plt.scatter(current,yieldRel_HMS_scalar,color='blue',zorder=4)
    plt.ylabel('Rel. Yield Scalar', fontsize=16)
    if target == 'LD2' :
        plt.title('HMS LD2 %s-%s' % (lumi_data["run number"][0],lumi_data["run number"][numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)
    elif target == 'LH2' :
        plt.title('HMS LH2 %s-%s' % (lumi_data["run number"][0],lumi_data["run number"][numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)
    else :
        plt.title('HMS Carbon %s-%s' % (lumi_data["run number"][0],lumi_data["run number"][numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)

    #HMS plot no track
    plt.subplot(2,3,2)    
    plt.grid(zorder=1)
    plt.xlim(0,60)
    #plt.ylim(0.98,1.02)
    plt.plot([0,60], [1,1], 'r-',zorder=2)
    plt.errorbar(current,yieldRel_HMS_notrack,yerr=uncern_HMS_evts_notrack,color='black',linestyle='None',zorder=3)
    plt.scatter(current,yieldRel_HMS_notrack,color='blue',zorder=4)
    plt.ylabel('Rel. Yield no track', fontsize=16)
    if target == 'LD2' :
        plt.title('HMS LD2 %s-%s' % (lumi_data["run number"][0],lumi_data["run number"][numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)
    elif target == 'LH2' :
        plt.title('HMS LH2 %s-%s' % (lumi_data["run number"][0],lumi_data["run number"][numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)
    else :
        plt.title('HMS Carbon %s-%s' % (lumi_data["run number"][0],lumi_data["run number"][numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)

    #HMS plot track
    plt.subplot(2,3,3)    
    plt.grid(zorder=1)
    plt.xlim(0,60)
    #plt.ylim(0.98,1.02)
    plt.plot([0,60], [1,1], 'r-',zorder=2)
    plt.errorbar(current,yieldRel_HMS_track,yerr=uncern_HMS_evts_track,color='black',linestyle='None',zorder=3)
    plt.scatter(current,yieldRel_HMS_track,color='blue',zorder=4)
    plt.ylabel('Rel. Yield track', fontsize=16)
    if target == 'LD2' :
        plt.title('HMS LD2 %s-%s' % (lumi_data["run number"][0],lumi_data["run number"][numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)
    elif target == 'LH2' :
        plt.title('HMS LH2 %s-%s' % (lumi_data["run number"][0],lumi_data["run number"][numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)
    else :
        plt.title('HMS Carbon %s-%s' % (lumi_data["run number"][0],lumi_data["run number"][numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)

        
    #SHMS plot scalar
    plt.subplot(2,3,4)    
    plt.grid(zorder=1)
    plt.xlim(0,60)
    #plt.ylim(0.98,1.02)
    plt.plot([0,60], [1,1], 'r-',zorder=2)
    plt.errorbar(current,yieldRel_SHMS_scalar,yerr=uncern_SHMS_evts_scalar,color='black',linestyle='None',zorder=3)
    plt.scatter(current,yieldRel_SHMS_scalar,color='blue',zorder=4)
    plt.ylabel('Rel. Yield Scalar', fontsize=16)
    if target == 'LD2' :
        plt.title('SHMS LD2 %s-%s' % (lumi_data["run number"][0],lumi_data["run number"][numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)
    elif target == 'LH2' :
        plt.title('SHMS LH2 %s-%s' % (lumi_data["run number"][0],lumi_data["run number"][numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)
    else :
        plt.title('SHMS Carbon %s-%s' % (lumi_data["run number"][0],lumi_data["run number"][numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)

    #SHMS plot no track
    plt.subplot(2,3,5)    
    plt.grid(zorder=1)
    plt.xlim(0,60)
    #plt.ylim(0.98,1.02)
    plt.plot([0,60], [1,1], 'r-',zorder=2)
    plt.errorbar(current,yieldRel_SHMS_notrack,yerr=uncern_SHMS_evts_notrack,color='black',linestyle='None',zorder=3)
    plt.scatter(current,yieldRel_SHMS_notrack,color='blue',zorder=4)
    plt.ylabel('Rel. Yield no track', fontsize=16)
    if target == 'LD2' :
        plt.title('SHMS LD2 %s-%s' % (lumi_data["run number"][0],lumi_data["run number"][numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)
    elif target == 'LH2' :
        plt.title('SHMS LH2 %s-%s' % (lumi_data["run number"][0],lumi_data["run number"][numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)
    else :
        plt.title('SHMS Carbon %s-%s' % (lumi_data["run number"][0],lumi_data["run number"][numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)

    #SHMS plot track
    plt.subplot(2,3,6)    
    plt.grid(zorder=1)
    plt.xlim(0,60)
    #plt.ylim(0.98,1.02)
    plt.plot([0,60], [1,1], 'r-',zorder=2)
    plt.errorbar(current,yieldRel_SHMS_track,yerr=uncern_SHMS_evts_track,color='black',linestyle='None',zorder=3)
    plt.scatter(current,yieldRel_SHMS_track,color='blue',zorder=4)
    plt.ylabel('Rel. Yield track', fontsize=16)
    if target == 'LD2' :
        plt.title('SHMS LD2 %s-%s' % (lumi_data["run number"][0],lumi_data["run number"][numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)
    elif target == 'LH2' :
        plt.title('SHMS LH2 %s-%s' % (lumi_data["run number"][0],lumi_data["run number"][numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)
    else :
        plt.title('SHMS Carbon %s-%s' % (lumi_data["run number"][0],lumi_data["run number"][numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)        

    plt.tight_layout()        

    cpuPlot = plt.figure(figsize=(12,8))

    #HMS plot cpu
    plt.subplot(2,1,1)    
    plt.grid(zorder=1)
    plt.xlim(0,60)
    #plt.ylim(0.98,1.02)
    plt.plot([0,60], [1,1], 'r-',zorder=2)
    plt.scatter(current,cpuLT_HMS,color='blue',zorder=4)
    plt.ylabel('CPU LT', fontsize=16)
    if target == 'LD2' :
        plt.title('HMS LD2 %s-%s' % (lumi_data["run number"][0],lumi_data["run number"][numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)
    elif target == 'LH2' :
        plt.title('HMS LH2 %s-%s' % (lumi_data["run number"][0],lumi_data["run number"][numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)
    else :
        plt.title('HMS Carbon %s-%s' % (lumi_data["run number"][0],lumi_data["run number"][numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)

    #SHMS plot cpu
    plt.subplot(2,1,2)    
    plt.grid(zorder=1)
    plt.xlim(0,60)
    #plt.ylim(0.98,1.02)
    plt.plot([0,60], [1,1], 'r-',zorder=2)
    plt.scatter(current,cpuLT_SHMS,color='blue',zorder=4)
    plt.ylabel('CPU LT', fontsize=16)
    if target == 'LD2' :
        plt.title('SHMS LD2 %s-%s' % (lumi_data["run number"][0],lumi_data["run number"][numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)
    elif target == 'LH2' :
        plt.title('SHMS LH2 %s-%s' % (lumi_data["run number"][0],lumi_data["run number"][numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)
    else :
        plt.title('SHMS Carbon %s-%s' % (lumi_data["run number"][0],lumi_data["run number"][numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)        

    plt.tight_layout()
        
    countPlot = plt.figure(figsize=(12,8))

    #HMS plot count
    plt.subplot(2,1,1)    
    plt.grid(zorder=1)
    plt.xlim(0,60)
    #plt.ylim(0.98,1.02)
    plt.plot([0,60], [1,1], 'r-',zorder=2)
    plt.scatter(current,count_HMS,color='blue',zorder=4)
    plt.ylabel('Count', fontsize=16)
    if target == 'LD2' :
        plt.title('HMS LD2 %s-%s' % (lumi_data["run number"][0],lumi_data["run number"][numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)
    elif target == 'LH2' :
        plt.title('HMS LH2 %s-%s' % (lumi_data["run number"][0],lumi_data["run number"][numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)
    else :
        plt.title('HMS Carbon %s-%s' % (lumi_data["run number"][0],lumi_data["run number"][numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)

    #SHMS plot count
    plt.subplot(2,1,2)    
    plt.grid(zorder=1)
    plt.xlim(0,60)
    #plt.ylim(0.98,1.02)
    plt.plot([0,60], [1,1], 'r-',zorder=2)
    plt.scatter(current,count_SHMS,color='blue',zorder=4)
    plt.ylabel('Count', fontsize=16)
    if target == 'LD2' :
        plt.title('SHMS LD2 %s-%s' % (lumi_data["run number"][0],lumi_data["run number"][numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)
    elif target == 'LH2' :
        plt.title('SHMS LH2 %s-%s' % (lumi_data["run number"][0],lumi_data["run number"][numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)
    else :
        plt.title('SHMS Carbon %s-%s' % (lumi_data["run number"][0],lumi_data["run number"][numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)        

        
    plt.tight_layout()

    trackPlot = plt.figure(figsize=(12,8))

    #HMS plot etrack
    plt.subplot(2,1,1)    
    plt.grid(zorder=1)
    plt.xlim(0,60)
    #plt.ylim(0.98,1.02)
    plt.plot([0,60], [1,1], 'r-',zorder=2)
    plt.scatter(current,etrack_HMS,color='blue',zorder=4)
    plt.ylabel('etrack', fontsize=16)
    if target == 'LD2' :
        plt.title('HMS LD2 %s-%s' % (lumi_data["run number"][0],lumi_data["run number"][numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)
    elif target == 'LH2' :
        plt.title('HMS LH2 %s-%s' % (lumi_data["run number"][0],lumi_data["run number"][numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)
    else :
        plt.title('HMS Carbon %s-%s' % (lumi_data["run number"][0],lumi_data["run number"][numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)

    #SHMS plot ptrack
    plt.subplot(2,1,2)    
    plt.grid(zorder=1)
    plt.xlim(0,60)
    #plt.ylim(0.98,1.02)
    plt.plot([0,60], [1,1], 'r-',zorder=2)
    plt.scatter(current,ptrack_SHMS,color='blue',zorder=4)
    plt.ylabel('ptrack', fontsize=16)
    if target == 'LD2' :
        plt.title('SHMS LD2 %s-%s' % (lumi_data["run number"][0],lumi_data["run number"][numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)
    elif target == 'LH2' :
        plt.title('SHMS LH2 %s-%s' % (lumi_data["run number"][0],lumi_data["run number"][numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)
    else :
        plt.title('SHMS Carbon %s-%s' % (lumi_data["run number"][0],lumi_data["run number"][numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)

    plt.tight_layout()
        
    plt.show()

    yield_data = {
        "current" : current,
        "HMS scalar rate" :rate_HMS,
        "SHMS scalar rate" :rate_SHMS,
        "HMScpuLT" : cpuLT_HMS,
        "SHMScpuLT" : cpuLT_SHMS,
        "HMS yield scalar" : yield_HMS_scalar,
        "SHMS yield scalar" : yield_SHMS_scalar,
        "HMS event scalar uncertainty" : uncern_HMS_evts_scalar,
        "SHMS event scalar uncertainty" : uncern_SHMS_evts_scalar,
        "HMS yield no track" : yield_HMS_notrack,
        "SHMS yield no track" : yield_SHMS_notrack,
        "HMS relative yield no track" : yieldRel_HMS_notrack,
        "SHMS relative yield no track" : yieldRel_SHMS_notrack,
        "HMS yield track" : yield_HMS_track,
        "SHMS yield track" : yield_SHMS_track,
        "HMS relative yield track" : yieldRel_HMS_track,
        "SHMS relative yield track" : yieldRel_SHMS_track,
    }

    return yield_data

def main():
    
    yield_data = plot_yield()
    # data = {**lumi_data, **yield_data} # only python 3.5+
    
    for key, val in lumi_data.items():
        lumi_data[key] = val.tolist()

    datadict = {}
    for d in (lumi_data, yield_data): 
        datadict.update(d)
    data = {i : datadict[i] for i in sorted(datadict.keys())}
    
    # table  = pd.DataFrame([data], columns=data.keys(), index=False)
    table  = pd.DataFrame([data], columns=data.keys())
    table = table.reindex(sorted(table.columns), axis=1)
    
    file_exists = os.path.isfile(out_f)

    if file_exists:
        table.to_csv(out_f, index = True, header=False, mode='a',)
    else:
        table.to_csv(out_f, index = True, header=True, mode='a',)

if __name__ == '__main__':
    main()
