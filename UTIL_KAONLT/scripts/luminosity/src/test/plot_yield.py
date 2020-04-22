#! /usr/bin/python

#
# Description:
# ================================================================
# Time-stamp: "2020-04-22 00:46:39 trottar"
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
from itertools import chain
import os, subprocess

USER = subprocess.getstatusoutput("whoami")

inp_f = "/home/trottar/Analysis/hallc_replay_lt/UTIL_KAONLT/scripts/luminosity/OUTPUTS/lumi_data.csv"
out_f = "/home/trottar/Analysis/hallc_replay_lt/UTIL_KAONLT/scripts/luminosity/src/test/OUTPUTS/yield_data.csv"

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
    rate_HMS = [lumi_data["HMS_evts"][i]/lumi_data["time"][i]
                for i,evts in enumerate(lumi_data["run number"])]
    rate_HMS = pd.Series(rate_HMS).fillna(0).tolist()
    rate_SHMS = [lumi_data["SHMS_evts"][i]/lumi_data["time"][i]
                for i,evts in enumerate(lumi_data["run number"])]
    rate_SHMS = pd.Series(rate_SHMS).fillna(0).tolist()
    cpuLT_HMS = [lumi_data["TRIG3_cut"][i]/((lumi_data["TRIG3_scaler"][i]-lumi_data["sent_edtm"][i])/lumi_data["ps3"][i])
                 for i,evt in enumerate(lumi_data["run number"])]
    cpuLT_HMS  = pd.Series(cpuLT_HMS).fillna(0).tolist()
    cpuLT_HMS_uncern = [np.sqrt(cpuLT_HMS[i])/cpuLT_HMS[i]
                 for i,evt in enumerate(lumi_data["run number"])]
    cpuLT_HMS_uncern = pd.Series(cpuLT_HMS_uncern).fillna(0).tolist()
    cpuLT_SHMS = [lumi_data["TRIG1_cut"][i]/((lumi_data["TRIG1_scaler"][i]-lumi_data["sent_edtm"][i])/lumi_data["ps1"][i])
                  for i,evt in enumerate(lumi_data["run number"])]
    cpuLT_SHMS = pd.Series(cpuLT_SHMS).fillna(0).tolist()
    cpuLT_SHMS_uncern = [np.sqrt(cpuLT_SHMS[i])/cpuLT_SHMS[i]
                         for i,evt in enumerate(lumi_data["run number"])]
    cpuLT_SHMS_uncern = pd.Series(cpuLT_SHMS_uncern).fillna(0).tolist()
    uncern_HMS_evts = [np.sqrt(lumi_data["HMS_evts"][i])/lumi_data["HMS_evts"][i]
                       for i,evt in enumerate(lumi_data["run number"])]
    uncern_HMS_evts  = pd.Series(uncern_HMS_evts).fillna(0).tolist()
    uncern_SHMS_evts = [np.sqrt(lumi_data["SHMS_evts"][i])/lumi_data["SHMS_evts"][i]
                        for i,evt in enumerate(lumi_data["run number"])]
    uncern_SHMS_evts = pd.Series(uncern_SHMS_evts).fillna(0).tolist()
    yield_HMS = [(lumi_data["HMS_evts"][i]*lumi_data["ps3"][i])/(lumi_data["charge"][i]*cpuLT_HMS[i]*lumi_data["HMS_track"][i])
                 for i,evt in enumerate(lumi_data["run number"])]
    yield_HMS = pd.Series(yield_HMS).fillna(0).tolist()
    yield_SHMS = [(lumi_data["SHMS_evts"][i]*lumi_data["ps1"][i])/(lumi_data["charge"][i]*cpuLT_SHMS[i]*lumi_data["SHMS_track"][i])
                  for i,evt in enumerate(lumi_data["run number"])]
    yield_SHMS = pd.Series(yield_SHMS).fillna(0).tolist()

    for i,curr in enumerate(current):
        if curr == min(current):
            if lumi_data["ps3"][i] !=0:
                min_yield_HMS = yield_HMS[i]
            else:
                min_yield_HMS = 1
            if lumi_data["ps1"][i] !=0:
                min_yield_SHMS = yield_SHMS[i]
            else:
                min_yield_SHMS = 1

    yieldRel_HMS = [yield_HMS[i]/min_yield_HMS for i,evt in enumerate(lumi_data["run number"])]
    # yieldRel_HMS = pd.Series(yieldRel_HMS).fillna(0).tolist()
    yieldRel_SHMS = [yield_SHMS[i]/min_yield_SHMS for i,evt in enumerate(lumi_data["run number"])]
    # yieldRel_SHMS = pd.Series(yieldRel_SHMS).fillna(0).tolist()

    return [current,rate_HMS,rate_SHMS,cpuLT_HMS,cpuLT_SHMS,yield_HMS,yield_SHMS,uncern_HMS_evts,uncern_SHMS_evts,yield_HMS,yield_SHMS,yieldRel_HMS,yieldRel_SHMS]

def plot_yield():

    [current,rate_HMS,rate_SHMS,cpuLT_HMS,cpuLT_SHMS,yield_HMS,yield_SHMS,uncern_HMS_evts,uncern_SHMS_evts,yield_HMS,yield_SHMS,yieldRel_HMS,yieldRel_SHMS] = calc_yield()

    for i, val in enumerate(lumi_data["run number"]):
        print("Run numbers:",lumi_data["run number"][i],"Current Values:",current[i])
    
    relYieldPlot = plt.figure()

    #HMS plot
    plt.subplot(1,2,1)    
    plt.grid(zorder=1)
    plt.xlim(0,60)
    #plt.ylim(0.98,1.02)
    plt.plot([0,60], [1,1], 'r-',zorder=2)
    plt.errorbar(current,yieldRel_HMS,yerr=uncern_HMS_evts,color='black',linestyle='None',zorder=3)
    plt.scatter(current,yieldRel_HMS,color='blue',zorder=4)
    plt.ylabel('Rel. Yield', fontsize=16)
    if target == 'LD2' :
        plt.title('HMS LD2 %s-%s' % (lumi_data["run number"][0],lumi_data["run number"][numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)
    elif target == 'LH2' :
        plt.title('HMS LH2 %s-%s' % (lumi_data["run number"][0],lumi_data["run number"][numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)
    else :
        plt.title('HMS Carbon %s-%s' % (lumi_data["run number"][0],lumi_data["run number"][numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)
    
    #SHMS plot
    plt.subplot(1,2,2)
    plt.grid(zorder=1)
    plt.xlim(0,60)
    #plt.ylim(0.94,1.06)
    plt.plot([0,60], [1,1], 'r-',zorder=2)
    plt.errorbar(current,yieldRel_SHMS,yerr=uncern_SHMS_evts,color='black',linestyle='None',zorder=3)
    plt.scatter(current,yieldRel_SHMS,color='blue',zorder=4)
    plt.ylabel('Rel. Yield', fontsize=16)
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
        "HMS rate" :rate_HMS,
        "SHMS rate" :rate_SHMS,
        "HMScpuLT" : cpuLT_HMS,
        "SHMScpuLT" : cpuLT_SHMS,
        "HMS yield" : yield_HMS,
        "SHMS yield" : yield_SHMS,
        "HMS event uncertainty" : uncern_HMS_evts,
        "SHMS event uncertainty" : uncern_SHMS_evts,
        "HMS yield" : yield_HMS,
        "SHMS yield" : yield_SHMS,
        "HMS relative yield" : yieldRel_HMS,
        "SHMS relative yield" : yieldRel_SHMS,
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
    
    table  = pd.DataFrame([data], columns=data.keys())
    table = table.reindex(sorted(table.columns), axis=1)
    
    file_exists = os.path.isfile(out_f)

    if file_exists:
        table.to_csv(out_f, index = True, header=False, mode='a',)
    else:
        table.to_csv(out_f, index = True, header=True, mode='a',)

if __name__ == '__main__':
    main()
