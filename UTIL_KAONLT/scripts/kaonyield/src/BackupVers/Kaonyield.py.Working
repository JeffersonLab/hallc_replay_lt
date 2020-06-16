#! /usr/bin/python

# 07/05/20 - Stephen Kay, University of Regina

# Python version of the proton analysis script. Now utilises uproot to select event of each type and writes them to a root file
# Intention is to apply PID/selection cutting here and plot in a separate script
# Python should allow for easier reading of databases storing timing offsets e.t.c.

# Import relevant packages
import uproot as up
import numpy as np
import root_numpy as rnp
import pandas as pd
import root_pandas as rpd
import ROOT
import scipy
import scipy.integrate as integrate
import matplotlib.pyplot as plt
import sys, math, os, subprocess

sys.path.insert(0, 'python/')
if len(sys.argv)-1!=2:
    print("!!!!! ERROR !!!!!\n Expected 2 arguments\n Usage is with - RunNumber MaxEvents\n!!!!! ERROR !!!!!")
    sys.exit(1)
# Input params - run number and max number of events
runNum = sys.argv[1]
MaxEvent = sys.argv[2]

USER = subprocess.getstatusoutput("whoami") # Grab user info for file finding
HOST = subprocess.getstatusoutput("hostname")
if ("farm" in HOST[1]):
    REPLAYPATH = "/group/c-kaonlt/USERS/%s/hallc_replay_lt" % USER[1]
elif ("qcd" in HOST[1]):
    REPLAYPATH = "/group/c-kaonlt/USERS/%s/hallc_replay_lt" % USER[1]
elif ("lark.phys.uregina" in HOST[1]):
    REPLAYPATH = "/home/%s/work/JLab/hallc_replay_lt" % USER[1]

# Add more path setting as needed in a similar manner
OUTPATH = "%s/UTIL_KAONLT/scripts/kaonyield/OUTPUT" % REPLAYPATH
sys.path.insert(0, '%s/UTIL_KAONLT/bin/python/' % REPLAYPATH)
import kaonlt as klt

print("Running as %s on %s, hallc_replay_lt path assumed as %s" % (USER[1], HOST[1], REPLAYPATH))
rootName = "%s/UTIL_KAONLT/ROOTfiles/Proton_coin_replay_production_%s_%s.root" % (REPLAYPATH, runNum, MaxEvent)

TimingCutFile = "%s/UTIL_KAONLT/DB/PARAM/Timing_Parameters.csv" % REPLAYPATH
AcceptCutFile = "%s/UTIL_KAONLT/DB/PARAM/Acceptance_Parameters.csv" % REPLAYPATH
PIDCutFile = "%s/UTIL_KAONLT/DB/PARAM/PID_Parameters.csv" % REPLAYPATH

try:
    TimingCutFile
    AcceptCutFile
    PIDCutFile
except NameError:
    print("!!!!! ERRROR !!!!!\n One (or more) of the cut files not found!\n!!!!! ERRORR !!!!!")
    sys.exit(2)
print("Reading timing cuts from %s" % TimingCutFile)
print("Reading acceptance cuts from %s" % AcceptCutFile)
print("Reading PID cuts from %s" % PIDCutFile)

TimingCutf = open(TimingCutFile)
PromptPeak = [0, 0, 0]
linenum = 0 # Count line number we're on
TempPar = -1 # To check later
for line in TimingCutf: # Read all lines in the cut file
    linenum += 1 # Add one to line number at start of loop
    if(linenum > 1): # Skip first line
        line = line.partition('#')[0] # Treat anything after a # as a comment and ignore it
        line = line.rstrip()
        array = line.split(",") # Convert line into an array, anything after a comma is a new entry
        if(int(runNum) in range (int(array[0]), int(array[1])+1)): # Check if run number for file is within any of the ranges specified in the cut file
            TempPar += 2 # If run number is in range, set to non -1 value
            BunchSpacing = float(array[2]) # Bunch spacing in ns
            CT_Offset = float(array[3]) # Offset to add to width of prompt peak
            PromptPeak[0] = float(array[4]) # Pion CT prompt peak positon
            PromptPeak[1] = float(array[5]) # Kaon CT prompt peak positon
            PromptPeak[2] = float(array[6]) # Proton CT prompt peak positon
            RF_Offset = float(array[7]) # Offset for RF timing cut
TimingCutf.close() # After scanning all lines in file, close file

if(TempPar == -1): # If value is still -1, run number provided din't match any ranges specified so exit
    print("!!!!! ERROR !!!!!\n Run number specified does not fall within a set of runs for which cuts are defined in %s\n!!!!! ERROR !!!!!" % TimingCutFile)
    sys.exit(3)
elif(TempPar > 1):
    print("!!! WARNING!!! Run number was found within the range of two (or more) line entries of %s !!! WARNING !!!" % TimingCutFile)
    print("The last matching entry will be treated as the input, you should ensure this is what you want")

# Using parameteres read in from DB file, calculate relevant time windows
RandomWindows = np.zeros((2, 2, 3)) # Low/high, 1st/2nd value, particle
nWindows = 6 # Number of random windows (total, not per side!), should be an even number
nSkip = 2 # Number of random buckets to skip (per side left/right), should not be too high

for x in range (0,3):
    # Take prompt peak - Spacing/2 - Offset, this is the end point of the prompt window, next take nSkip*BunchSpacing-> skip n buckets,
    # window is then (nWindows/2)*BunchSpacing wide, so use the subtraction/addition of this to provide the lower/upper end of the random window
    RandomWindows[0][0][x] = PromptPeak[x]-(BunchSpacing/2)-CT_Offset-(nSkip*BunchSpacing)-((nWindows/2)*BunchSpacing) #Random Low 1
    RandomWindows[0][1][x] = PromptPeak[x]-(BunchSpacing/2)-CT_Offset-(nSkip*BunchSpacing) #Random low 2
    RandomWindows[1][0][x] = PromptPeak[x]+(BunchSpacing/2)+CT_Offset+(nSkip*BunchSpacing) #Random high 1
    RandomWindows[1][1][x] = PromptPeak[x]+(BunchSpacing/2)+CT_Offset+(nSkip*BunchSpacing)+((nWindows/2)*BunchSpacing) #Random high 2

AcceptCutf = open(AcceptCutFile)
linenum = 0 # Count line number we're on
TempPar = -1 # To check later
for line in AcceptCutf: # Read all lines in the cut file
    linenum += 1 # Add one to line number at start of loop
    if(linenum > 1): # Skip first line
        line = line.partition('#')[0] # Treat anything after a # as a comment and ignore it
        line = line.rstrip()
        array = line.split(",") # Convert line into an array, anything after a comma is a new entry
        if(int(runNum) in range (int(array[0]), int(array[1])+1)): # Check if run number for file is within any of the ranges specified in the cut file
            TempPar += 2 # If run number is in range, set to non -1 value
            AcceptCutArray=[0 for x in range (0, (len(array)-2))] # Hdelta low/high, Hxpfp low/high, Hypfp low/high, Pdelta low/high, Pxpfp low/high, Pypfp low/high
            for x in range (0, (len(array)-2)): # Loop over the 12 elements of the array that do NOT specify run number group
                AcceptCutArray[x] = float(array[x+2]) # Set values of cut array to be equal to values from cut file
AcceptCutf.close() # After scanning all lines in file, close file

if(TempPar == -1): # If value is still -1, run number provided din't match any ranges specified so exit
    print("!!!!! ERROR !!!!!\n Run number specified does not fall within a set of runs for which cuts are defined in %s\n!!!!! ERROR !!!!!" % AcceptCutFile)
    sys.exit(4)
elif(TempPar > 1):
    print("!!! WARNING!!! Run number was found within the range of two (or more) line entries of %s !!! WARNING !!!" % AcceptCutFile)
    print("The last matching entry will be treated as the input, you should ensure this is what you want")

PIDCutf = open(PIDCutFile)
linenum = 0 # Count line number we're on
TempPar = -1 # To check later
 # See README in param file
for line in PIDCutf: # Read all lines in the cut file
    linenum += 1 # Add one to line number at start of loop
    if(linenum > 1): # Skip first line
        line = line.partition('#')[0] # Treat anything after a # as a comment and ignore it
        line = line.rstrip()
        array = line.split(",") # Convert line into an array, anything after a comma is a new entry
        if(int(runNum) in range (int(array[0]), int(array[1])+1)): # Check if run number for file is within any of the ranges specified in the cut file
            PIDCutArray=[0 for x in range (0, (len(array)-2))]
            TempPar += 2 # If run number is in range, set to non -1 value
            for x in range (0, (len(array)-2)): # Loop over the 12 elements of the array that do NOT specify run number group
                PIDCutArray[x] = float(array[x+2]) # Set values of cut array to be equal to values from cut file
PIDCutf.close() # After scanning all lines in file, close file

# Read stuff from the main event tree
e_tree = up.open(rootName)["T"]

# Timing info
CTime_ePiCoinTime_ROC1 = e_tree.array("CTime.ePiCoinTime_ROC1")
CTime_eKCoinTime_ROC1 = e_tree.array("CTime.eKCoinTime_ROC1")
CTime_epCoinTime_ROC1 = e_tree.array("CTime.epCoinTime_ROC1")
P_RF_tdcTime = e_tree.array("T.coin.pRF_tdcTime")
P_hod_fpHitsTime = e_tree.array("P.hod.fpHitsTime")
# HMS info
H_gtr_beta = e_tree.array("H.gtr.beta")
H_gtr_xp = e_tree.array("H.gtr.th") # xpfp -> Theta
H_gtr_yp = e_tree.array("H.gtr.ph") # ypfp -> Phi
H_gtr_dp = e_tree.array("H.gtr.dp")
H_cal_etotnorm = e_tree.array("H.cal.etotnorm")
H_cer_npeSum = e_tree.array("H.cer.npeSum")
# SHMS info
P_gtr_beta = e_tree.array("P.gtr.beta")
P_gtr_xp = e_tree.array("P.gtr.th") # xpfp -> Theta
P_gtr_yp = e_tree.array("P.gtr.ph") # ypfp -> Phi
P_gtr_p = e_tree.array("P.gtr.p")
P_gtr_dp = e_tree.array("P.gtr.dp")
P_cal_etotnorm = e_tree.array("P.cal.etotnorm")
P_aero_npeSum = e_tree.array("P.aero.npeSum")
P_hgcer_npeSum = e_tree.array("P.hgcer.npeSum")
P_hgcer_xAtCer = e_tree.array("P.hgcer.xAtCer")
P_hgcer_yAtCer = e_tree.array("P.hgcer.yAtCer")
# Kinematic quantitites
Q2 = e_tree.array("H.kin.primary.Q2")
W = e_tree.array("H.kin.primary.W")
epsilon = e_tree.array("H.kin.primary.epsilon")
ph_q = e_tree.array("P.kin.secondary.ph_xq")
emiss = e_tree.array("P.kin.secondary.emiss")
pmiss = e_tree.array("P.kin.secondary.pmiss")
MandelT = e_tree.array("P.kin.secondary.MandelT")
MandelU = e_tree.array("P.kin.secondary.MandelU")
# Misc quantities
fEvtType = e_tree.array("fEvtHdr.fEvtType")
RFFreq = e_tree.array("MOFC1FREQ")
RFFreqDiff = e_tree.array("MOFC1DELTA")
pEDTM = e_tree.array("T.coin.pEDTM_tdcTime")
# Relevant branches now stored as NP arrays

# Define particle masses for missing mass calculation
Mp = 0.93828
MPi = 0.13957018 
MK = 0.493677
# Calculate missing mass under different particle assumptions
# NOTE, this should be modified for NON different particle assumptions in hcana, this assumes a "kaon" is specified in the kinematics file
MMpi = np.array([math.sqrt(abs((em + math.sqrt(abs((MK*MK) + (gtrp*gtrp))) - math.sqrt(abs((MPi*MPi) + (gtrp*gtrp) - (pm*pm))) ))**2) for (em, pm, gtrp) in zip(emiss, pmiss, P_gtr_p)]) 
MMK = np.array([math.sqrt(abs((em*em)-(pm*pm))) for (em, pm) in zip(emiss, pmiss)])
MMp = np.array([math.sqrt(abs((em + math.sqrt(abs((MK*MK) + (gtrp*gtrp))) - math.sqrt(abs((Mp*Mp) + (gtrp*gtrp) - (pm*pm))) ))**2) for (em, pm, gtrp) in zip(emiss, pmiss, P_gtr_p)])

# Create array of mod(BunchSpacing)(RFTime - StartTime + Offset) for all events. Offset is chosen to centre the pion peak in the distribution (need to test 2ns runs)
RF_CutDist = np.array([ ((RFTime-StartTime + RF_Offset)%(BunchSpacing)) for (RFTime, StartTime) in zip(P_RF_tdcTime, P_hod_fpHitsTime)]) # In python x % y is taking the modulo y of x

def hms_elec():
    # Define the array of arrays containing the relevant HMS info
    NoCut_HMS_Elec = [H_gtr_beta, H_gtr_xp, H_gtr_yp, H_gtr_dp, H_cal_etotnorm, H_cer_npeSum, RF_CutDist]
    Uncut_HMS_Elec = [(HBeta, Hxp, Hyp, Hdel, HCal, HCer, RFCutDist)
                      for (HBeta, Hxp, Hyp, Hdel, HCal, HCer, RFCutDist) in zip(*NoCut_HMS_Elec)]
    # Create array of arrays of variables after cuts
    Cut_HMS_Elec = [(HBeta, Hxp, Hyp, Hdel, HCal, HCer, RFCutDist)
                    for (HBeta, Hxp, Hyp, Hdel, HCal, HCer, RFCutDist) in zip(*NoCut_HMS_Elec)
                    if Hdel > AcceptCutArray[0] and Hdel < AcceptCutArray[1]
                    if Hxp > AcceptCutArray[2] and Hxp < AcceptCutArray[3]
                    if Hyp > AcceptCutArray[4] and Hyp < AcceptCutArray[5]
                    if HCal > 0.7 and HCal <1.5]
    HMS_Electrons = {
        "Uncut_HMSelec_Events" : Uncut_HMS_Elec,
        "Cut_HMSelec_Events" : Cut_HMS_Elec,
    }

    return HMS_Electrons

def coin_pions(): 
    # Define the array of arrays containing the relevant HMS and SHMS info
    NoCut_COIN_Pions = [H_gtr_beta, H_gtr_xp, H_gtr_yp, H_gtr_dp, H_cal_etotnorm, H_cer_npeSum, CTime_ePiCoinTime_ROC1, P_RF_tdcTime, P_hod_fpHitsTime, P_gtr_beta, P_gtr_xp, P_gtr_yp, P_gtr_p, P_gtr_dp, P_cal_etotnorm, P_aero_npeSum, P_hgcer_npeSum, P_hgcer_xAtCer, P_hgcer_yAtCer, MMpi, MMK, MMp, RF_CutDist, Q2, W, epsilon, MandelT, MandelU, ph_q]
    Uncut_COIN_Pions = [(HBeta, Hxp, Hyp, Hdel, HCal, HCer, CTPi, RF, HodStart, PiBeta, Pixp, Piyp, PiP, PiDel, PiCal, PiAero, PiHGC, PiHGCX, PiHGCY, mm1, mm2, mm3, RFCutDist, Kin_Q2, Kin_W, Kin_eps, Kin_t, Kin_u, phq) for (HBeta, Hxp, Hyp, Hdel, HCal, HCer, CTPi, RF, HodStart, PiBeta, Pixp, Piyp, PiP, PiDel, PiCal, PiAero, PiHGC, PiHGCX, PiHGCY, mm1, mm2, mm3, RFCutDist, Kin_Q2, Kin_W, Kin_eps, Kin_t, Kin_u, phq) in zip(*NoCut_COIN_Pions)]
    # Create array of arrays of pions after cuts, all events, prompt and random
    Cut_COIN_Pions_all = [(HBeta, Hxp, Hyp, Hdel, HCal, HCer, CTPi, RF, HodStart, PiBeta, Pixp, Piyp, PiP, PiDel, PiCal, PiAero, PiHGC, PiHGCX, PiHGCY, mm1, mm2, mm3, RFCutDist, Kin_Q2, Kin_W, Kin_eps, Kin_t, Kin_u, phq) for (HBeta, Hxp, Hyp, Hdel, HCal, HCer, CTPi, RF, HodStart, PiBeta, Pixp, Piyp, PiP, PiDel, PiCal, PiAero, PiHGC, PiHGCX, PiHGCY, mm1, mm2, mm3, RFCutDist, Kin_Q2, Kin_W, Kin_eps, Kin_t, Kin_u, phq) in zip(*NoCut_COIN_Pions)
                    if Hdel > AcceptCutArray[0] and Hdel < AcceptCutArray[1]
                    if Hxp > AcceptCutArray[2] and Hxp < AcceptCutArray[3]
                    if Hyp > AcceptCutArray[4] and Hyp < AcceptCutArray[5]
                    if HCal > PIDCutArray[0] and HCal < PIDCutArray[0]+0.8 # H_ecut.H_cal [0]
                    if PiDel > AcceptCutArray[6] and PiDel < AcceptCutArray[7]
                    if Pixp > AcceptCutArray[8] and Pixp < AcceptCutArray[9]
                    if Piyp > AcceptCutArray[10] and Piyp <  AcceptCutArray[11]
                    if abs(PiBeta -1.0) < PIDCutArray[21] # P_picut.P_Beta = [21]
                    if PiAero > PIDCutArray[23] # P_picut.P_aero = [23] 
                    if PiHGC > PIDCutArray[22] # P_picut.P_hgcer = [22]
                    if RFCutDist > 1.4 and RFCutDist < 3]

    # Create array of arrays of pions after cuts, prompt events
    # NOTE - Should just be able to feed all events array into this somehow? Should investigate
    Cut_COIN_Pions_prompt = [(HBeta, Hxp, Hyp, Hdel, HCal, HCer, CTPi, RF, HodStart, PiBeta, Pixp, Piyp, PiP, PiDel, PiCal, PiAero, PiHGC, PiHGCX, PiHGCY, mm1, mm2, mm3, RFCutDist, Kin_Q2, Kin_W, Kin_eps, Kin_t, Kin_u, phq) for (HBeta, Hxp, Hyp, Hdel, HCal, HCer, CTPi, RF, HodStart, PiBeta, Pixp, Piyp, PiP, PiDel, PiCal, PiAero, PiHGC, PiHGCX, PiHGCY, mm1, mm2, mm3, RFCutDist, Kin_Q2, Kin_W, Kin_eps, Kin_t, Kin_u, phq) in zip(*NoCut_COIN_Pions)
                    if Hdel > AcceptCutArray[0] and Hdel < AcceptCutArray[1]
                    if Hxp > AcceptCutArray[2] and Hxp < AcceptCutArray[3]
                    if Hyp > AcceptCutArray[4] and Hyp < AcceptCutArray[5]
                    if HCal > PIDCutArray[0] and HCal < PIDCutArray[0]+0.8 # H_ecut.H_cal [0]
                    if PiDel > AcceptCutArray[6] and PiDel < AcceptCutArray[7]
                    if Pixp > AcceptCutArray[8] and Pixp < AcceptCutArray[9]
                    if Piyp > AcceptCutArray[10] and Piyp <  AcceptCutArray[11]
                    if abs(PiBeta -1.0) < PIDCutArray[21] # P_picut.P_Beta = [21]
                    if PiAero > PIDCutArray[23] # P_picut.P_aero = [23] 
                    if PiHGC > PIDCutArray[22] # P_picut.P_hgcer = [22]
                    if CTPi > (PromptPeak[0]-((BunchSpacing/2)+CT_Offset)) and CTPi < (PromptPeak[0]+((BunchSpacing/2)+CT_Offset))
                    if RFCutDist > 1.4 and RFCutDist < 3]

    # Create array of arrays of pions after cuts, random events    
    Cut_COIN_Pions_random = [(HBeta, Hxp, Hyp, Hdel, HCal, HCer, CTPi, RF, HodStart, PiBeta, Pixp, Piyp, PiP, PiDel, PiCal, PiAero, PiHGC, PiHGCX, PiHGCY, mm1, mm2, mm3, RFCutDist, Kin_Q2, Kin_W, Kin_eps, Kin_t, Kin_u, phq) for (HBeta, Hxp, Hyp, Hdel, HCal, HCer, CTPi, RF, HodStart, PiBeta, Pixp, Piyp, PiP, PiDel, PiCal, PiAero, PiHGC, PiHGCX, PiHGCY, mm1, mm2, mm3, RFCutDist, Kin_Q2, Kin_W, Kin_eps, Kin_t, Kin_u, phq) in zip(*NoCut_COIN_Pions)
                    if Hdel > AcceptCutArray[0] and Hdel < AcceptCutArray[1]
                    if Hxp > AcceptCutArray[2] and Hxp < AcceptCutArray[3]
                    if Hyp > AcceptCutArray[4] and Hyp < AcceptCutArray[5]
                    if HCal > PIDCutArray[0] and HCal < PIDCutArray[0]+0.8 # H_ecut.H_cal [0]
                    if PiDel > AcceptCutArray[6] and PiDel < AcceptCutArray[7]
                    if Pixp > AcceptCutArray[8] and Pixp < AcceptCutArray[9]
                    if Piyp > AcceptCutArray[10] and Piyp <  AcceptCutArray[11]
                    if abs(PiBeta -1.0) < PIDCutArray[21] # P_picut.P_Beta = [21]
                    if PiAero > PIDCutArray[23] # P_picut.P_aero = [23] 
                    if PiHGC > PIDCutArray[22] # P_picut.P_hgcer = [22]
                    if (CTPi > RandomWindows[0][0][0] and CTPi < RandomWindows[0][1][0]) or (CTPi > RandomWindows[1][0][0] and CTPi < RandomWindows[1][1][0])
                    if RFCutDist > 1.4 and RFCutDist < 3]

    COIN_Pions = {
        "Uncut_Pion_Events" : Uncut_COIN_Pions,
        "Cut_Pion_Events_All" : Cut_COIN_Pions_all,
        "Cut_Pion_Events_Prompt" : Cut_COIN_Pions_prompt,
        "Cut_Pion_Events_Random" : Cut_COIN_Pions_random,
    }

    return COIN_Pions

def coin_kaons(): 
    # Define the array of arrays containing the relevant HMS and SHMS info
    NoCut_COIN_Kaons = [H_gtr_beta, H_gtr_xp, H_gtr_yp, H_gtr_dp, H_cal_etotnorm, H_cer_npeSum, CTime_eKCoinTime_ROC1, P_RF_tdcTime, P_hod_fpHitsTime, P_gtr_beta, P_gtr_xp, P_gtr_yp, P_gtr_p, P_gtr_dp, P_cal_etotnorm, P_aero_npeSum, P_hgcer_npeSum, P_hgcer_xAtCer, P_hgcer_yAtCer, MMpi, MMK, MMp, RF_CutDist, Q2, W, epsilon, MandelT, MandelU, ph_q]
    Uncut_COIN_Kaons = [(HBeta, Hxp, Hyp, Hdel, HCal, HCer, CTK, RF, HodStart, KBeta, Kxp, Kyp, KP, KDel, KCal, KAero, KHGC, KHGCX, KHGCY, mm1, mm2, mm3, RFCutDist, Kin_Q2, Kin_W, Kin_eps, Kin_t, Kin_u, phq) for (HBeta, Hxp, Hyp, Hdel, HCal, HCer, CTK, RF, HodStart, KBeta, Kxp, Kyp, KP, KDel, KCal, KAero, KHGC, KHGCX, KHGCY, mm1, mm2, mm3, RFCutDist, Kin_Q2, Kin_W, Kin_eps, Kin_t, Kin_u, phq) in zip(*NoCut_COIN_Kaons)]
    # Create array of arrays of pions after cuts, all events, prompt and random
    Cut_COIN_Kaons_all = [(HBeta, Hxp, Hyp, Hdel, HCal, HCer, CTK, RF, HodStart, KBeta, Kxp, Kyp, KP, KDel, KCal, KAero, KHGC, KHGCX, KHGCY, mm1, mm2, mm3, RFCutDist, Kin_Q2, Kin_W, Kin_eps, Kin_t, Kin_u, phq) for (HBeta, Hxp, Hyp, Hdel, HCal, HCer, CTK, RF, HodStart, KBeta, Kxp, Kyp, KP, KDel, KCal, KAero, KHGC, KHGCX, KHGCY, mm1, mm2, mm3, RFCutDist, Kin_Q2, Kin_W, Kin_eps, Kin_t, Kin_u, phq) in zip(*NoCut_COIN_Kaons)
                    if Hdel > AcceptCutArray[0] and Hdel < AcceptCutArray[1]
                    if Hxp > AcceptCutArray[2] and Hxp < AcceptCutArray[3]
                    if Hyp > AcceptCutArray[4] and Hyp < AcceptCutArray[5]
                    if HCal > PIDCutArray[0] and HCal < PIDCutArray[0]+0.8 # H_ecut.H_cal [0]
                    if KDel > AcceptCutArray[6] and KDel < AcceptCutArray[7]
                    if Kxp > AcceptCutArray[8] and Kxp < AcceptCutArray[9]
                    if Kyp > AcceptCutArray[10] and Kyp < AcceptCutArray[11]
                    if abs(KBeta -1.0) < PIDCutArray[27] # P_kcut.P_Beta = [27]
                    if KAero > PIDCutArray[29] # P_kcut.P_aero = [29]
                    if KHGC < PIDCutArray[28] # P_kcut.P_hgcer = [28]
                    if RFCutDist > 1.3 and RFCutDist < 3]
    # Create array of a/rrays of pions after cuts, prompt events
    # NOTE - Should just be able to feed all events array into this somehow? Should investigate
    Cut_COIN_Kaons_prompt = [(HBeta, Hxp, Hyp, Hdel, HCal, HCer, CTK, RF, HodStart, KBeta, Kxp, Kyp, KP, KDel, KCal, KAero, KHGC, KHGCX, KHGCY, mm1, mm2, mm3, RFCutDist, Kin_Q2, Kin_W, Kin_eps, Kin_t, Kin_u, phq) for (HBeta, Hxp, Hyp, Hdel, HCal, HCer, CTK, RF, HodStart, KBeta, Kxp, Kyp, KP, KDel, KCal, KAero, KHGC, KHGCX, KHGCY, mm1, mm2, mm3, RFCutDist, Kin_Q2, Kin_W, Kin_eps, Kin_t, Kin_u, phq) in zip(*NoCut_COIN_Kaons)
                    if Hdel > AcceptCutArray[0] and Hdel < AcceptCutArray[1]
                    if Hxp > AcceptCutArray[2] and Hxp < AcceptCutArray[3]
                    if Hyp > AcceptCutArray[4] and Hyp < AcceptCutArray[5]
                    if HCal > PIDCutArray[0] and HCal < PIDCutArray[0]+0.8 # H_ecut.H_cal [0]
                    if KDel > AcceptCutArray[6] and KDel < AcceptCutArray[7]
                    if Kxp > AcceptCutArray[8] and Kxp < AcceptCutArray[9]
                    if Kyp > AcceptCutArray[10] and Kyp < AcceptCutArray[11]
                    if abs(KBeta -1.0) < PIDCutArray[27] # P_kcut.P_Beta = [27]
                    if KAero > PIDCutArray[29] # P_kcut.P_aero = [29]
                    if KHGC < PIDCutArray[28] # P_kcut.P_hgcer = [28]
                    if CTK > (PromptPeak[1]-((BunchSpacing/2)+CT_Offset)) and CTK < (PromptPeak[1]+((BunchSpacing/2)+CT_Offset))
                    if RFCutDist > 1.3 and RFCutDist < 3]
    # Create array of arrays of pions after cuts, random events    
    Cut_COIN_Kaons_random = [(HBeta, Hxp, Hyp, Hdel, HCal, HCer, CTK, RF, HodStart, KBeta, Kxp, Kyp, KP, KDel, KCal, KAero, KHGC, KHGCX, KHGCY, mm1, mm2, mm3, RFCutDist, Kin_Q2, Kin_W, Kin_eps, Kin_t, Kin_u, phq) for (HBeta, Hxp, Hyp, Hdel, HCal, HCer, CTK, RF, HodStart, KBeta, Kxp, Kyp, KP, KDel, KCal, KAero, KHGC, KHGCX, KHGCY, mm1, mm2, mm3, RFCutDist, Kin_Q2, Kin_W, Kin_eps, Kin_t, Kin_u, phq) in zip(*NoCut_COIN_Kaons)
                    if Hdel > AcceptCutArray[0] and Hdel < AcceptCutArray[1]
                    if Hxp > AcceptCutArray[2] and Hxp < AcceptCutArray[3]
                    if Hyp > AcceptCutArray[4] and Hyp < AcceptCutArray[5]
                    if HCal > PIDCutArray[0] and HCal < PIDCutArray[0]+0.8 # H_ecut.H_cal [0]
                    if KDel > AcceptCutArray[6] and KDel < AcceptCutArray[7]
                    if Kxp > AcceptCutArray[8] and Kxp < AcceptCutArray[9]
                    if Kyp > AcceptCutArray[10] and Kyp < AcceptCutArray[11]
                    if abs(KBeta -1.0) < PIDCutArray[27] # P_kcut.P_Beta = [27]
                    if KAero > PIDCutArray[29] # P_kcut.P_aero = [29]
                    if KHGC < PIDCutArray[28] # P_kcut.P_hgcer = [28]
                    if (CTK > RandomWindows[0][0][1] and CTK < RandomWindows[0][1][1]) or (CTK > RandomWindows[1][0][1] and CTK < RandomWindows[1][1][1])
                    if RFCutDist > 1.3 and RFCutDist < 3]

    COIN_Kaons = {
        "Uncut_Kaon_Events" : Uncut_COIN_Kaons,
        "Cut_Kaon_Events_All" : Cut_COIN_Kaons_all,
        "Cut_Kaon_Events_Prompt" : Cut_COIN_Kaons_prompt,
        "Cut_Kaon_Events_Random" : Cut_COIN_Kaons_random,
    }

    return COIN_Kaons

def coin_protons(): 
    # Define the array of arrays containing the relevant HMS and SHMS info
    NoCut_COIN_Protons = [H_gtr_beta, H_gtr_xp, H_gtr_yp, H_gtr_dp, H_cal_etotnorm, H_cer_npeSum, CTime_epCoinTime_ROC1, P_RF_tdcTime, P_hod_fpHitsTime, P_gtr_beta, P_gtr_xp, P_gtr_yp, P_gtr_p, P_gtr_dp, P_cal_etotnorm, P_aero_npeSum, P_hgcer_npeSum, P_hgcer_xAtCer, P_hgcer_yAtCer, MMpi, MMK, MMp, RF_CutDist, Q2, W, epsilon, MandelT, MandelU, ph_q]
    Uncut_COIN_Protons = [(HBeta, Hxp, Hyp, Hdel, HCal, HCer, CTp, RF, HodStart, pBeta, pxp, pyp, pP, pDel, pCal, pAero, pHGC, pHGCX, pHGCY, mm1, mm2, mm3, RFCutDist, Kin_Q2, Kin_W, Kin_eps, Kin_t, Kin_u, phq) for (HBeta, Hxp, Hyp, Hdel, HCal, HCer, CTp, RF, HodStart, pBeta, pxp, pyp, pP, pDel, pCal, pAero, pHGC, pHGCX, pHGCY, mm1, mm2, mm3, RFCutDist, Kin_Q2, Kin_W, Kin_eps, Kin_t, Kin_u, phq) in zip(*NoCut_COIN_Protons)]
    # Create array of arrays of pions after cuts, all events, prompt and random
    Cut_COIN_Protons_all = [(HBeta, Hxp, Hyp, Hdel, HCal, HCer, CTp, RF, HodStart, pBeta, pxp, pyp, pP, pDel, pCal, pAero, pHGC, pHGCX, pHGCY, mm1, mm2, mm3, RFCutDist, Kin_Q2, Kin_W, Kin_eps, Kin_t, Kin_u, phq) for (HBeta, Hxp, Hyp, Hdel, HCal, HCer, CTp, RF, HodStart, pBeta, pxp, pyp, pP, pDel, pCal, pAero, pHGC, pHGCX, pHGCY, mm1, mm2, mm3, RFCutDist, Kin_Q2, Kin_W, Kin_eps, Kin_t, Kin_u, phq) in zip(*NoCut_COIN_Protons)
                    if Hdel > AcceptCutArray[0] and Hdel < AcceptCutArray[1]
                    if Hxp > AcceptCutArray[2] and Hxp < AcceptCutArray[3]
                    if Hyp > AcceptCutArray[4] and Hyp < AcceptCutArray[5]
                    if HCal > PIDCutArray[0] and HCal < PIDCutArray[0]+0.8 # H_ecut.H_cal [0]
                    if pDel > AcceptCutArray[6] and pDel < AcceptCutArray[7]
                    if pxp > AcceptCutArray[8] and pxp < AcceptCutArray[9]
                    if pyp > AcceptCutArray[10] and pyp < AcceptCutArray[11]
                    if abs(pBeta -1.0) < PIDCutArray[33] # P_pcut.P_Beta = [33]
                    if pAero < PIDCutArray[35] # P_pcut.P_Aero = [35]
                    if pHGC < PIDCutArray[34] # P_pcut.P_hgcer = [34]
                    if RFCutDist < 1.5]
    # Create array of a/rrays of pions after cuts, prompt events
    # NOTE - Should just be able to feed all events array into this somehow? Should investigate
    Cut_COIN_Protons_prompt = [(HBeta, Hxp, Hyp, Hdel, HCal, HCer, CTp, RF, HodStart, pBeta, pxp, pyp, pP, pDel, pCal, pAero, pHGC, pHGCX, pHGCY, mm1, mm2, mm3, RFCutDist, Kin_Q2, Kin_W, Kin_eps, Kin_t, Kin_u, phq) for (HBeta, Hxp, Hyp, Hdel, HCal, HCer, CTp, RF, HodStart, pBeta, pxp, pyp, pP, pDel, pCal, pAero, pHGC, pHGCX, pHGCY, mm1, mm2, mm3, RFCutDist, Kin_Q2, Kin_W, Kin_eps, Kin_t, Kin_u, phq) in zip(*NoCut_COIN_Protons)
                    if Hdel > AcceptCutArray[0] and Hdel < AcceptCutArray[1]
                    if Hxp > AcceptCutArray[2] and Hxp < AcceptCutArray[3]
                    if Hyp > AcceptCutArray[4] and Hyp < AcceptCutArray[5]
                    if HCal > PIDCutArray[0] and HCal < PIDCutArray[0]+0.8 # H_ecut.H_cal [0]
                    if pDel > AcceptCutArray[6] and pDel < AcceptCutArray[7]
                    if pxp > AcceptCutArray[8] and pxp < AcceptCutArray[9]
                    if pyp > AcceptCutArray[10] and pyp < AcceptCutArray[11]
                    if abs(pBeta -1.0) < PIDCutArray[33] # P_pcut.P_Beta = [33]
                    if pAero < PIDCutArray[35] # P_pcut.P_Aero = [35]
                    if pHGC < PIDCutArray[34] # P_pcut.P_hgcer = [34]
                    if CTp > (PromptPeak[2]-((BunchSpacing/2)+CT_Offset)) and CTp < (PromptPeak[2]+((BunchSpacing/2)+CT_Offset))
                    if RFCutDist < 1.5]
    # Create array of arrays of pions after cuts, random events    
    Cut_COIN_Protons_random = [(HBeta, Hxp, Hyp, Hdel, HCal, HCer, CTp, RF, HodStart, pBeta, pxp, pyp, pP, pDel, pCal, pAero, pHGC, pHGCX, pHGCY, mm1, mm2, mm3, RFCutDist, Kin_Q2, Kin_W, Kin_eps, Kin_t, Kin_u, phq) for (HBeta, Hxp, Hyp, Hdel, HCal, HCer, CTp, RF, HodStart, pBeta, pxp, pyp, pP, pDel, pCal, pAero, pHGC, pHGCX, pHGCY, mm1, mm2, mm3, RFCutDist, Kin_Q2, Kin_W, Kin_eps, Kin_t, Kin_u, phq) in zip(*NoCut_COIN_Protons)
                    if Hdel > AcceptCutArray[0] and Hdel < AcceptCutArray[1]
                    if Hxp > AcceptCutArray[2] and Hxp < AcceptCutArray[3]
                    if Hyp > AcceptCutArray[4] and Hyp < AcceptCutArray[5]
                    if HCal > PIDCutArray[0] and HCal < PIDCutArray[0]+0.8 # H_ecut.H_cal [0]
                    if pDel > AcceptCutArray[6] and pDel < AcceptCutArray[7]
                    if pxp > AcceptCutArray[8] and pxp < AcceptCutArray[9]
                    if pyp > AcceptCutArray[10] and pyp < AcceptCutArray[11]
                    if abs(pBeta -1.0) < PIDCutArray[33] # P_pcut.P_Beta = [33]
                    if pAero < PIDCutArray[35] # P_pcut.P_Aero = [35]
                    if pHGC < PIDCutArray[34] # P_pcut.P_hgcer = [34]
                    if (CTp > RandomWindows[0][0][2] and CTp < RandomWindows[0][1][2]) or (CTp > RandomWindows[1][0][2] and CTp < RandomWindows[1][1][2])
                    if RFCutDist < 1.5]

    COIN_Protons = {
        "Uncut_Proton_Events" : Uncut_COIN_Protons,
        "Cut_Proton_Events_All" : Cut_COIN_Protons_all,
        "Cut_Proton_Events_Prompt" : Cut_COIN_Protons_prompt,
        "Cut_Proton_Events_Random" : Cut_COIN_Protons_random,
    }

    return COIN_Protons



def main():
    HMS_Elec_Data = hms_elec()
    COIN_Pion_Data = coin_pions()
    COIN_Kaon_Data = coin_kaons()
    COIN_Proton_Data = coin_protons()
    
    # This is just the list of branches we use from the initial root file for each dict
    # I don't like re-defining this here as it's very prone to errors if you included (or removed something) earlier but didn't modify it here
    # Should base the branches to include based on some list and just repeat the list here (or call it again directly below)
    HMS_Data_Header = list(["H_gtr_beta","H_gtr_xp","H_gtr_yp","H_gtr_dp","H_cal_etotnorm","H_cer_npeSum", "RF_CutDist"])
    COIN_Pion_Data_Header = ["H_gtr_beta","H_gtr_xp","H_gtr_yp","H_gtr_dp","H_cal_etotnorm","H_cer_npeSum","CTime_ePiCoinTime_ROC1","P_RF_tdcTime","P_hod_fpHitsTime","P_gtr_beta","P_gtr_xp","P_gtr_yp","P_gtr_p","P_gtr_dp","P_cal_etotnorm","P_aero_npeSum","P_hgcer_npeSum","P_hgcer_xAtCer","P_hgcer_yAtCer","MMpi","MMK","MMp","RF_CutDist", "Q2", "W", "epsilon", "MandelT", "MandelU", "ph_q"]
    COIN_Kaon_Data_Header = ["H_gtr_beta","H_gtr_xp","H_gtr_yp","H_gtr_dp","H_cal_etotnorm","H_cer_npeSum","CTime_eKCoinTime_ROC1","P_RF_tdcTime","P_hod_fpHitsTime","P_gtr_beta","P_gtr_xp","P_gtr_yp","P_gtr_p","P_gtr_dp","P_cal_etotnorm","P_aero_npeSum","P_hgcer_npeSum","P_hgcer_xAtCer","P_hgcer_yAtCer","MMpi","MMK","MMp","RF_CutDist", "Q2", "W", "epsilon", "MandelT", "MandelU", "ph_q"]
    COIN_Proton_Data_Header = ["H_gtr_beta","H_gtr_xp","H_gtr_yp","H_gtr_dp","H_cal_etotnorm","H_cer_npeSum","CTime_epCoinTime_ROC1","P_RF_tdcTime","P_hod_fpHitsTime","P_gtr_beta","P_gtr_xp","P_gtr_yp","P_gtr_p","P_gtr_dp","P_cal_etotnorm","P_aero_npeSum","P_hgcer_npeSum","P_hgcer_xAtCer","P_hgcer_yAtCer","MMpi","MMK","MMp","RF_CutDist", "Q2", "W", "epsilon", "MandelT", "MandelU", "ph_q"]

    # Need to create a dict for all the branches we grab
    data = {}
    for d in (HMS_Elec_Data, COIN_Pion_Data, COIN_Kaon_Data, COIN_Proton_Data): # Convert individual dictionaries into a "dict of dicts"
        data.update(d)
    data_keys = list(data.keys()) # Create a list of all the keys in all dicts added above, each is an array of data
    for i in range (0, len(data_keys)):
        if("HMSelec" in data_keys[i]):
            DFHeader=list(HMS_Data_Header)
        elif("Pion" in data_keys[i]):
            DFHeader=list(COIN_Pion_Data_Header)
        elif("Kaon" in data_keys[i]):
            DFHeader=list(COIN_Kaon_Data_Header)
        elif("Proton" in data_keys[i]):
            DFHeader=list(COIN_Proton_Data_Header)
        else:
            continue
        # Uncomment the line below if you want .csv file output, WARNING the files can be very large and take a long time to process!
        #pd.DataFrame(data.get(data_keys[i])).to_csv("%s/%s_%s.csv" % (OUTPATH, data_keys[i], runNum), header=DFHeader, index=False) # Convert array to panda dataframe and write to csv with correct header
        if (i == 0):
            pd.DataFrame(data.get(data_keys[i]), columns = DFHeader, index = None).to_root("%s/%s_%s_Analysed_Data.root" % (OUTPATH, runNum, MaxEvent), key ="%s" % data_keys[i])
        elif (i != 0):
            pd.DataFrame(data.get(data_keys[i]), columns = DFHeader, index = None).to_root("%s/%s_%s_Analysed_Data.root" % (OUTPATH, runNum, MaxEvent), key ="%s" % data_keys[i], mode ='a') 

if __name__ == '__main__':
    main()    
