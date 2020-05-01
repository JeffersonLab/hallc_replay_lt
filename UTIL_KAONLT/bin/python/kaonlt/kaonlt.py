#! /usr/bin/python

#
# Description:This will read in the array data file that contains all the leave histogram information
# include...
# ================================================================
# Time-stamp: "2020-05-01 19:28:54 trottar"
# ================================================================
#
# Author:  Richard L. Trotta III <trotta@cua.edu>
#
# Copyright (c) trottar
#


from __future__ import division
import logging

# Gets rid of matplot logging DEBUG messages
plt_logger = logging.getLogger('matplotlib')
plt_logger.setLevel(logging.WARNING)

# Suppresses unwanted numpy warning
import warnings
import numpy as np
warnings.simplefilter(action='ignore', category=FutureWarning)

from ROOT import TFile, TH1F
import matplotlib.pyplot as plt
from matplotlib import interactive
from matplotlib import colors
import uproot as up
import time, math, sys

# garbage collector
import gc
gc.collect()

class pyDict(dict):
    
    def __init__(self,inputTree):
        self.inputTree = inputTree

class pyBranch(pyDict):

    def findBranch(self,inputBranch, inputLeaf):
        tree = self.inputTree
        branch = tree.array(inputBranch)
        branch  = list(zip(*branch)) # Match elements to proper leaves
        leafList = tree[inputBranch].interpretation.fromdtype.descr
        i=0
        for name,typ in leafList:
            if name == inputLeaf:
                leaf = name
                leafVal = i
                break
            i+=1
        leafHist = branch[leafVal]

        return np.array(leafHist)
    
class pyRoot():

    # Save arrays,lists,etc. to root file as histograms
    def py2root(self,inputDict,rootName):
        try:
            tmp = ""
            hist_key = []*len(inputDict)
            hist_val = []*len(inputDict)
            for key,val in inputDict.items():
                tmp = "hist_%s" % key
                tmp = TH1F( tmp, '%s' % key, len(val), 0., max(val))
                hist_key.append(tmp)
                hist_val.append(val)

            f = TFile( rootName, 'recreate' )
            for i, evt in enumerate(hist_val):
                for j, hevt in enumerate(hist_val[i]):
                    print(hist_key[i], "-> ", hevt)
                    hist_key[i].Fill(hevt)
                hist_key[i].Write()
 
            f.Write()
            f.Close()
        except TypeError:
            print("\nERROR: Only current accepting 1D array/list values\n")

class pyEquation():

    def missmass():
        print("missmass")
            
class pyPlot(pyDict):
    
    def __init__(self, cutDict=None):
        self.cutDict = cutDict

    def setbin(self,plot,numbin,xmin=None,xmax=None):
        
        if (xmin or xmax):
            leaf = self.fixBin(plot,plot,xmin,xmax)
        else:
            leaf = plot
            
        binwidth = (abs(leaf).max()-abs(leaf).min())/numbin
        
        bins = np.arange(min(leaf), max(leaf) + binwidth, binwidth)

        return bins

    def fixBin(self,cut,plot,low,high):
            
        arrCut = cut
        arrPlot = plot
        arrPlot = arrPlot[(arrCut > low) & (arrCut < high)]

        return arrPlot

    def read_dict(self,fout):
        
        f = open(fout)
        cutDict = {}
        for line in f:
            if "#" in line:
                continue
            else:
                line = line.split("=")
                typName = line[0].rstrip()
                typName = typName.lstrip()
                typCuts = line[1].split("+")
                print("Type ", typName)
                print("Cuts ", typCuts)
                for evt in typCuts:
                    minusCuts = evt.split("-")
                    cutplus = minusCuts[0].rstrip()
                    cutplus = cutplus.lstrip()
                    if len(minusCuts) == 2:
                        cutminus = minusCuts[1].lstrip()
                    elif len(minusCuts) > 2:
                        for minus in cutminus:
                            cutminus = minus.lstrip()
                    else:
                        cutminus = "none"
                    print("+ ",cutplus)
                    print("- ",cutminus)
                    if "pid" in cutplus:
                        plusfout = "../../../../DB/CUTS/general/pid.cuts"
                    elif "track" in cutplus:
                        plusfout = "../../../../DB/CUTS/general/track.cuts"
                    elif "accept" in cutplus:
                        plusfout = "../../../../DB/CUTS/general/accept.cuts"
                    elif "coin_time" in cutplus:
                        plusfout = "../../../../DB/CUTS/general/coin_time.cuts"
                    elif "current" in cutplus:
                        plusfout = "../../../../DB/CUTS/general/current.cuts"
                    else:
                        print("ERROR: Cut %s not found" % cutplus)
                        continue
                    if "pid" in cutminus:
                        minusfout = "../../../../DB/CUTS/general/pid.cuts"
                    elif "track" in cutminus:
                        minusfout = "../../../../DB/CUTS/general/track.cuts"
                    elif "accept" in cutminus:
                        minusfout = "../../../../DB/CUTS/general/accept.cuts"
                    elif "coin_time" in cutminus:
                        minusfout = "../../../../DB/CUTS/general/coin_time.cuts"
                    elif "current" in cutminus:
                        minusfout = "../../../../DB/CUTS/general/current.cuts"
                    elif "none" in cutminus:
                        minusfout = "none"
                    else:
                        print("ERROR: Cut %s not found" % cutminus)
                        continue
                    
                    minuscut = cutminus.split(".")
                    if len(minuscut) == 3:
                        cutminus = minuscut[1]
                        leafminus = minuscut[2].rstrip()
                    elif minuscut == ['none']:
                        cutminus = "none"
                    else:
                        print("ERROR: Invalid syntax for removing cut %s " % (minuscut))
                        continue
                    cutplus = cutplus.split(".")
                    if len(cutplus) == 2:
                        cutplus = str(cutplus[1])
                        print("cutplus ", cutplus)
                    elif len(cutplus) > 2:
                        cutplus = str(cutplus[2])
                        print("cutplus ", cutplus)
                    else:
                        print("ERROR: %s cut not found in %s" % (cutplus,plusfout))
                        continue
                    
                    fplus = open(plusfout)
                    if minusfout == "none":
                        fminus = fplus             
                    else:
                        fminus = open(minusfout)
                    for lplus in fplus:
                        if "#" in lplus:
                            continue
                        else:
                            lplus  = lplus.split("=")
                            cuts = lplus[1]
                            print(cutplus, " ++ ", lplus[0])
                            if cutplus in lplus[0]:
                                if typName in cutDict.keys():
                                    if cuts not in cutDict.items():
                                        print(typName, " already found!!!!")
                                        cutDict[typName] += ","+cuts
                                else:
                                    cutName = {typName : cuts}
                                    cutDict.update(cutName)
                                print(lplus[0],"++>",cutDict[typName])
                            else:
                                print("ERROR: %s cut does not match %s" % (cutplus,lplus[0]))
                                continue
                    for lminus in fminus:
                        if "#" in lminus:
                            continue
                        else:
                            lminus  = lminus.split("=")
                            cuts = lminus[1]
                            arr_cuts = cuts.split(",")
                            print(leafminus,": ",cutminus, " -- ", lminus[0])
                            if cutminus in lminus[0]:
                                for remove in arr_cuts:
                                    if leafminus in remove:
                                        print("```````````````",remove)
                                        cutDict[typName] = cutDict[typName].replace(remove,"")
                                print(lminus[0],"-->",cutDict[typName])
                            else:
                                print("ERROR: %s cut does not match %s" % (cutminus,lminus[0]))
                                continue
                print("\n\n")
        fplus.close()
        f.close()
        print(cutDict.keys())
        return cutDict

    # Create a working dictionary for cuts
    def w_dict(self,cuts):

        inputDict = self.cutDict
        subDict = inputDict[cuts]
        subDict = subDict.split(",")
        cut_arr = [evt for evt in subDict]
        return cut_arr
            
    def cut(self,key,cuts=None):

        if cuts:
            inputDict = self.cutDict
            subDict = inputDict[cuts]
            value = subDict.get(key,"Leaf name not found")
            return value
        else:
            return self.cutDict.get(key,"Leaf name not found")

    # Old version of apply cuts
    def applyCuts(self,leaf,cuts=None):
        
        if cuts:
            tmp = leaf
            applycut = 'tmp['
            i=0
            while i < (len(cuts)-1):
                applycut += 'self.cut("%s") & ' % cuts[i]
                i+=1
            applycut += 'self.cut("%s")]' % cuts[len(cuts)-1]
            tmp = eval(applycut)
        else:
            print('No cuts applied to %s' % leaf)
            tmp = leaf
        
        return tmp

    # New version of applying cuts
    def add_cut(self,arr, cuts):
        
        arr_cut = arr  
        applycut = "arr_cut["
        inputDict = self.cutDict
        subDict = inputDict[cuts]
        for i,(key,val) in enumerate(subDict.items()):
            if i == len(subDict)-1:
                applycut += 'self.cut("%s","%s")]' % (key,cuts)
            else:
                applycut += 'self.cut("%s","%s") & ' % (key,cuts)
        arr_cut = eval(applycut)        
        return arr_cut


    def progressBar(self,value, endvalue, bar_length):

        percent = float(value) / endvalue
        arrow = '=' * int(round(percent * bar_length)-1) + '>'
        spaces = ' ' * (bar_length - len(arrow))
        
        sys.stdout.write(" \r[{0}] {1}%".format(arrow + spaces, int(round(percent * 100))))
        sys.stdout.flush()

    # Recreates the histograms of the root file
    def recreateLeaves(self):
                
        binwidth = 1.0
    
        i=1
        print("Looing at TTree %s" % self.tree1)
        print("Enter n to see next plot and q to exit program\n")
        # for key,arr in self.T1_leafdict.dictionary().items():
        for key,arr in self.T1_leafdict.items():
            # print key, -
            if (np.all(arr == 0.)):
                print("Histogram %s: Empty array" % key)
            elif ( 2. > len(arr)) :
                print("Histogram %s: Only one element" % key)
            else:
                binwidth = (abs(arr).max())/100
                plt.figure()
                plt.hist(arr,bins=np.arange(min(arr), max(arr) + binwidth, binwidth),histtype='step', stacked=True, fill=False )
                plt.title(key, fontsize =16)
                foutname = 'fig_'+key+'.png'
                i+=1

        print("\nTTree %s completed" % self.tree1)

    def densityPlot(self,x,y,title,xlabel,ylabel,binx,biny,pyMisc,
                    xmin=None,xmax=None,ymin=None,ymax=None,cuts=None,figure=None,ax=None,layered=True):
        if cuts:
            xcut  = self.applyCuts(x,cuts)
            ycut = self.applyCuts(y,cuts)
        else:
            xcut = x
            ycut = y
        if ax or figure:
            print("")
        else:
            fig, ax = plt.subplots(tight_layout=True,figsize=(11.69,8.27))
        if (xmin or xmax or ymin or ymax):
            # norm=colors.LogNorm() makes colorbar normed and logarithmic
            hist = ax.hist2d(xcut, ycut,bins=(pyMisc.setbin(x,binx,xmin,xmax),pyMisc.setbin(y,biny,ymin,ymax)), norm=colors.LogNorm())
        else:
            # norm=colors.LogNorm() makes colorbar normed and logarithmic
            hist = ax.hist2d(xcut, ycut,bins=(pyMisc.setbin(x,binx),pyMisc.setbin(y,biny)), norm=colors.LogNorm())
        if layered is True :
            plt.colorbar(hist[3], ax=ax, spacing='proportional', label='Number of Events')

        plt.title(title)
        plt.xlabel(xlabel)
        plt.ylabel(ylabel)

        inputVal = [x,y]
        
        if (xmin or xmax or ymin or ymax):
            binVal = [pyMisc.setbin(x,binx,xmin,xmax),pyMisc.setbin(y,biny,ymin,ymax)]
        else:
            binVal = [pyMisc.setbin(x,binx),pyMisc.setbin(y,biny)]
        return [binVal, fig]


    def polarPlot(self,theta,r,title,thetalabel,rlabel,bintheta,binr,pyMisc,
                  thetamin=None,thetamax=None,rmin=None,rmax=None,cuts=None,figure=None,ax=None):

        if cuts:
            thetacut  = self.applyCuts(theta,cuts)
            rcut = self.applyCuts(r,cuts)
        else:
            thetacut = theta
            rcut = r
        xy = np.vstack([thetacut, rcut])
        z = stats.gaussian_kde(xy)(xy)
        idx = z.argsort()
        x, y, z = np.array(thetacut)[idx], np.array(rcut)[idx], z[idx]
        if ax or figure:
            # ax = figure.add_subplot(sub,polar=True)
            print("")
        else:
            fig,ax = plt.subplot(111,polar=True)
        if (thetamin or thetamax or rmin or rmax):
            hist = ax.scatter(thetacut, rcut, c=z, edgecolor='', alpha = 0.75)
        else:
            hist = ax.scatter(thetacut, rcut, c=z, edgecolor='', alpha = 0.75)
        ax.grid(True)
        plt.title(title)
        plt.xlabel(thetalabel)
        plt.ylabel(rlabel)
        # plt.colorbar()

        return fig
