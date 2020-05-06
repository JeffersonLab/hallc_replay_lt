#! /usr/bin/python

#
# Description: This package will perform many tasks required for physics analysis in hall c
#              (although can also be expanded to any analysis using root files to varying success)
# Analysis script required format for applying cuts...

'''
import uproot as up
sys.path.insert(0, 'path_to/bin/python/')
import kaonlt as klt

# Convert root leaf to array with uproot
array  = tree.array("leaf")

# Not required for applying cuts, but required for converting back to root files
r = klt.pyRoot()

fout = "<path_to_run_type_cut>"
c = klt.pyPlot(None) # See below for pyPlot class definition
readDict = c.read_dict(fout) # read in run type cuts file and makes dictionary

# This method calls several methods in kaonlt package. It is required to create properly formated
# dictionaries. The evaluation must be in the analysis script because the analysis variables (i.e. the
# leaves of interest) are not defined in the kaonlt package. This makes the system more flexible
# overall, but a bit more cumbersome in the analysis script. Perhaps one day a better solution will be
# implimented.
def make_cutDict(cut,inputDict=None):

    global c

    c = klt.pyPlot(readDict)
    x = c.w_dict(cut)
    
    # Only for first key of dictionary
    if inputDict == None:
        inputDict = {}
        
    # Update dictionary with cuts (as strings) from readDict
    for key,val in readDict.items():
        if key == cut:
            inputDict.update({key : {}})

    # Evaluate strings to cut values. Creates a dictionary in a dictionary...dict-ception!
    for i,val in enumerate(x):
        tmp = x[i]
        inputDict[cut].update(eval(tmp))
        
    return inputDict

cutDict = make_cutDict("cut1")
cutDict = make_cutDict("cut2",cutDict)
# Continue this for all run type cuts required

# ---> If multple run type files are required then define a new run type file altogether. Do not try to 
# chain run type files. It can be done, but is computationally wasteful and pointless.

# To apply cuts to array...
c.add_cut(array,"cut#")

'''
# ================================================================
# Time-stamp: "2020-05-02 15:00:37 trottar"
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

'''
When calling kaonlt package, you may define a dictionary in the script. This dictionary will contain
the cuts of interest (defined in a CUTS directory).  These cuts are read in through the read_dict()
method of the pyPlot() class. The pyDict class is not explicitly called, but rather called implicitly
by other classes.
'''
class pyDict(dict):
    
    def __init__(self,inputTree):
        self.inputTree = inputTree
        
'''
This class, with its findBranch method, will grab the leaves in a branch using uproot package
'''
class pyBranch():

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

'''    
This class is for converting files into root files after the analysis steps
'''
class pyRoot():

    # Save arrays,lists,etc. from csv to root file as histograms
    def csv2root(self,inputDict,rootName):
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

'''            
This class stores a variety of equations often used in the KaonLT analysis procedure
'''
class pyEquation():

    # Define missing mass calculation
    def missmass():
        print("missmass")

'''
This is the most extensive class of the kaonlt package. This class will perform many required tasks
for doing in depth analysis in python. This class does not require, but will use the pyDict class to
apply cuts. Set the dictionary to None if no cuts are required.
'''
class pyPlot(pyDict):
    
    def __init__(self, cutDict=None):
        self.cutDict = cutDict

    # A method for defining a bin. This may be called in any matplotlib package plots.
    # This will calculate a suitable bin width and use that to equally distribute the bin size
    def setbin(self,plot,numbin,xmin=None,xmax=None):
        
        if (xmin or xmax):
            leaf = self.fixBin(plot,plot,xmin,xmax)
        else:
            leaf = plot
            
        binwidth = (abs(leaf).max()-abs(leaf).min())/numbin
        
        bins = np.arange(min(leaf), max(leaf) + binwidth, binwidth)

        return bins

    # This method is complimentary to setbin(). This will cut the distribution based off the min and max
    # array values
    def fixBin(self,cut,plot,low,high):
            
        arrCut = cut
        arrPlot = plot
        arrPlot = arrPlot[(arrCut > low) & (arrCut < high)]

        return arrPlot

    # This method reads in the CUTS and converts them to a dictionary. 
    def read_dict(self,fout):

        # Open run type cuts of interest
        f = open(fout)
        cutDict = {}
        for line in f:
            if "#" in line:
                continue
            else:
                line = line.split("=")
                # Grab run type cut name
                typName = line[0].rstrip()
                typName = typName.lstrip()
                # Grab run type cuts required, note at this stage the cuts to be removed are bunched
                # together still
                typCuts = line[1].split("+")
                print("Type ", typName)
                print("Cuts ", typCuts)
                # Loop over run type cuts
                for evt in typCuts:
                    # Split any cuts to be removed
                    minusCuts = evt.split("-")
                    # Define first cut to be added, any other cuts to be added will be done in future
                    # iteration over run type cuts
                    cutplus = minusCuts[0].rstrip()
                    cutplus = cutplus.lstrip()
                    # Checks if there are multiple cuts to be removed
                    if len(minusCuts) == 2:
                        cutminus = minusCuts[1].lstrip()
                    elif len(minusCuts) > 2:
                        for minus in cutminus:
                            cutminus = minus.lstrip()
                    else:
                        cutminus = "none"
                    print("+ ",cutplus)
                    print("- ",cutminus)
                    # Matches run type cuts with the general cuts (e.g pid, track, etc.)
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
                    # Break down the cut to be removed to find specific leaf to be subtracted from
                    # dictionary
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

                    # Open general cuts file of interest to be added to dictionary
                    fplus = open(plusfout)
                    # Open general cuts file of interest to be removed from dictionary. If there are no
                    # cuts to be removed then this step is skipped
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
                            # Check if cut is in file
                            if cutplus in lplus[0]:
                                # Check if run type is already defined in dictionary
                                if typName in cutDict.keys():
                                    if cuts not in cutDict.items():
                                        # If run type already defined, then append dictionary key
                                        print(typName, " already found!!!!")
                                        cutDict[typName] += ","+cuts
                                else:
                                    # If run type not defined, then add key to dictionary
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
                            # Split cuts to check for the one to be removed.
                            arr_cuts = cuts.split(",")
                            print(leafminus,": ",cutminus, " -- ", lminus[0])
                            # Check if cut is in file
                            if cutminus in lminus[0]:
                                for remove in arr_cuts:
                                    # Check which cut matches the one wanted to be removed
                                    if leafminus in remove:
                                        print("```````````````",remove)
                                        # Replace unwanted cut with blank string
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

    # Create a working dictionary for cuts by converting string to array of cuts.
    def w_dict(self,cuts):

        inputDict = self.cutDict
        subDict = inputDict[cuts]
        subDict = subDict.split(",")
        cut_arr = [evt for evt in subDict]
        return cut_arr

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

    # New version of applying cuts. The general idea is to apply cuts without sacrificing computation
    # time. Array indexing is much faster than most methods in python. This method formats a string with
    # the cuts required. This string is evaluated and the array index calls the cut() method.See
    # description above for how the analysis script should be formatted. 
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

    # The array index that was evaluated in the add_cut() method calls this method. This method then
    # grabs the properly formated dictionary (from class pyDict) and outputs arrays with cuts.
    def cut(self,key,cuts=None):

        if cuts:
            inputDict = self.cutDict
            subDict = inputDict[cuts]
            value = subDict.get(key,"Leaf name not found")
            return value
        # Just for old version for applying cuts (i.e. applyCuts() method)
        else:
            return self.cutDict.get(key,"Leaf name not found")

    # A simple progress bar to use in loops
    def progressBar(self,value, endvalue, bar_length):

        percent = float(value) / endvalue
        arrow = '=' * int(round(percent * bar_length)-1) + '>'
        spaces = ' ' * (bar_length - len(arrow))
        
        sys.stdout.write(" \r[{0}] {1}%".format(arrow + spaces, int(round(percent * 100))))
        sys.stdout.flush()

    # Creates nice density plots using matplotlib
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

    # Creates polar plots (useful for kaonlt analysis). Old script, has not been checked in a while.
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
