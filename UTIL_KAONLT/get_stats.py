#!/usr/bin/env python

import time,sys,os,argparse,atexit,subprocess,math

ANGLE = sys.argv[1]    
# CURRENT = sys.argv[2]
# Q2 = sys.argv[2]
CURRENT = 40
BEAM = 8.200
target = "LH2"

ANGLE_low = float(ANGLE)-0.05
ANGLE_high = float(ANGLE)+0.05

CURRENT_low = float(CURRENT)-7
CURRENT_high = float(CURRENT)+7

BEAM_low = float(BEAM)-0.1
BEAM_high = float(BEAM)+0.1



def getRunInfo():

    Run = []
    Type = [] 
    Target = [] 
    lamb = []
    KAONLTLIST="kaonlt_runlist_8p2-6p2.csv"

    f = open(KAONLTLIST)
    
    for line in f:
        linespace = line.strip()
        if "Prod" in linespace or "PROD" in linespace :
            if target in linespace :
                data = linespace.split("!")
                # print(str(data))
                runtmp = [int(s) for s in data[0].split() if s.isdigit()]
                lamtmp = [int(s) for s in data[1].split() if s.isdigit()]
                if len(lamtmp) != 0:
                    run_tmp = runtmp[0]
                    lambda_tmp = lamtmp[0]
                    #print("Run %s, lambda %s" % (run_tmp,lambda_tmp))
                    Run.append(run_tmp)
                    lamb.append(lambda_tmp)
                
    f.close()
    

    return[Run, Type, Target, lamb]


def getValues():
    

    P_SHMS=[] 
    Theta_SHMS=[] 
    P_HMS=[] 
    Theta_HMS=[] 
    Ebeam=[] 
    Current=[] 
    PS1=[] 
    PS3=[] 
    PS5=[] 
    HMS_Rate=[] 
    SHMS_Rate=[] 
    COIN_Rate=[]
    Charge=[] 
    Raw_coin=[] 

    [Run, Type, Target, lamb] = getRunInfo()
    #print("Run list %s" % (Run))
    i=0
    while True :        
        #print("Run %s" % (Run[i]))        
        report_1="./REPORT_OUTPUT/COIN/PRODUCTION/replay_coin_production_%s_-1.report" % (Run[i])
        report_2="./REPORT_OUTPUT/COIN/PRODUCTION/replay_coin_production_%s_-1.report" % (Run[i])
        report_4="../MON_OUTPUT/REPORT/reportMonitor_shms_%s_50000.txt" % (Run[i])
        report_5="OUTPUT/scalers_Run%s.txt" % (Run[i])

        f    = open(report_1)
        curList = ['SHMS P Central', 'SHMS Angle', 'HMS P Central', 'HMS Angle','Beam energy',
                   'SHMS BCM4B Beam Cut Current','SHMS_pTRIG3 Pre-triggers', 'SHMS_pTRIG1 Pre-triggers', 
                   'SHMS_pTRIG5 Pre-scaled Pre-triggers', 'SHMS BCM4B Beam Cut Charge',
                   'Coin ROC2 pTRIG5 Accepted Triggers']        
        for line in f:
            data = line.split(':')
            for index, obj in enumerate(curList) :
                if (curList[index] in data[0]) : 
                    if(index == 0) :
                       moment_shms_tmp = data[1].split(" ")
                    if(index == 1) :
                       angle_shms_tmp = data[1].split(" ")
                    if(index == 2) :
                       moment_hms_tmp = data[1].split(" ")
                    if(index == 3) :
                       angle_hms_tmp = data[1].split(" ")
                    if(index == 4) :
                        beam_tmp = data[1].split(" ")
                    if(index == 5) :
                        current_tmp = data[1].split(" ")
                    if (index == 6) : 
                        HMSRATE_tmp = data[1].split(" ")
                    if (index == 7) : 
                        SHMSRATE_tmp = data[1].split(" ")
                    if (index == 8) : 
                        COINRATE_tmp = data[1].split(" ")
                    if (index == 9) : 
                        charge_tmp = data[1].split(" ")
                    if (index == 10) : 
                        RAWCOIN_tmp = data[1].split(" ")
        moment_shms = float(moment_shms_tmp[1])
        angle_shms = float(angle_shms_tmp[1])
        moment_hms = float(moment_hms_tmp[1])
        angle_hms = float(angle_hms_tmp[1])
        beam = float(beam_tmp[1])
        current=float(current_tmp[1])
        HMSRATE=float(HMSRATE_tmp[6])
        SHMSRATE=float(SHMSRATE_tmp[6])
        COINRATE=float(COINRATE_tmp[6])
        charge=float(charge_tmp[1])
        RAWCOIN=float(RAWCOIN_tmp[1])
        #print(str(moment_shms) + "-momentum_shms\n")
        #print(str(angle_shms) + "-angle_shms\n")
        #print(str(moment_hms) + "-momentum_hms\n")
        #print(str(angle_hms) + "-angle_hms\n")
        #print(str(beam) + "-beam\n")
        #print(str(current) + "-current\n")
        #print(str(HMSRATE) + "-HMSRATE\n")
        #print(str(SHMSRATE) + "-SHMSRATE\n")
        #print(str(COINRATE) + "-COINRATE\n")
        #print(str(charge) + "-charge\n")
        #print(str(RAWCOIN) + "-RAWCOIN\n")
        P_SHMS.append(moment_shms)
        Theta_SHMS.append(angle_shms)
        P_HMS.append(moment_hms)
        Theta_HMS.append(angle_hms)
        Ebeam.append(beam)
        Current.append(current)
        HMS_Rate.append(HMSRATE)
        SHMS_Rate.append(SHMSRATE)
        COIN_Rate.append(COINRATE)
        Charge.append(charge)
        Raw_coin.append(RAWCOIN)
        f.close()
                    
        f    = open(report_2)   
     
        psList = ['Ps1_factor','Ps3_factor','Ps5_factor']        
        psActual = ['1','2','3','5','9','17','33','65','129','257','513','1025','2049','4097','8193','16385','32769']        
        psValue = ['0','1','2','3','4','5','6','7','8','9','10','11','12','13','14','15','16']    
    
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
        ps1=float(ps1_tmp[1])
        ps3=float(ps3_tmp[1])
        ps5=float(ps5_tmp[1])
        j=0
        for index in psActual:
            if (float(index) == ps1) :
                psv1 = str(psValue[j])
            if (float(index) == ps3) :
                psv3 = str(psValue[j])
            if (float(index) == ps5) :
                psv5 = str(psValue[j])
            j=j+1
        #print(str(psv1) + "-PS1\n")
        ##print(str(ps1) + "\n")
        #print(str(psv3) + "-PS3\n")
        ##print(str(ps3) + "\n")
        #print(str(psv5) + "-PS5\n")
        ##print(str(ps5) + "\n")
        PS1.append(psv1)
        PS3.append(psv3)
        PS5.append(psv5)
        f.close()
     
        i=i+1

        if i == len(Run) :
            break

    return[P_SHMS, Theta_SHMS, P_HMS, Theta_HMS, Ebeam, Current, PS1, PS3, PS5, HMS_Rate, SHMS_Rate, COIN_Rate, Charge, Raw_coin]


def main() :

    [Run, Type, Target, lamb] = getRunInfo()
    
    [P_SHMS, Theta_SHMS, P_HMS, Theta_HMS, Ebeam, Current, PS1, PS3, PS5, HMS_Rate, SHMS_Rate, COIN_Rate, Charge, Raw_coin] = getValues()
    
    acc_charge = []
    tot_charge = []
    tot_lambda = []
    lambda_fort = []
    charge_fort = []

    if ANGLE_low < float(6.91) < ANGLE_high :
        charge_goal = 10130
        lambda_goal = 8200
        # lambda_goal = 2550

    if ANGLE_low < float(9.91) < ANGLE_high :
        charge_goal = 10130
        lambda_goal = 6100
        # lambda_goal = 2550

    if ANGLE_low < float(8.50) < ANGLE_high :
        charge_goal = 10105
        lambda_goal = 525
        # lambda_goal = 2550

    if ANGLE_low < float(6.20) < ANGLE_high :
        charge_goal = 10105
        lambda_goal = 525
        # lambda_goal = 2550

    # if Q2 == "3":        
    #     charge_goal = 1512
    #     lambda_goal = 1550
    #     # charge_goalPAC = 3162
    #     # lambda_goalPAC = 60800
    # elif Q2 == "2.115":        
    #     charge_goal = 3780
    #     lambda_goal = 1165
    #     # charge_goalPAC = 3162
    #     # lambda_goalPAC = 60800

    i=0

    print("\nBeam must be between %0.3f GeV and %0.3f GeV" % (BEAM_low,BEAM_high))    
    print("Angle must be between %0.3f and %0.3f\n" % (ANGLE_low,ANGLE_high))
    # print("Current must be between %0.1f and %0.1f\n" % (CURRENT_low,CURRENT_high))
    
    while True :
        if BEAM_low < float(Ebeam[i]) < BEAM_high :
            if ANGLE_low < float(Theta_SHMS[i]) < ANGLE_high : 
                acc_charge.append(float(Charge[i]))
                #print("Theta_SHMS for run %s is %s" % (Run,Theta_SHMS))
                #print("Current for run %s is %s" % (Run,Current))
                tot_charge.append(float(Charge[i]))
                tot_lambda.append(float(lamb[i]))
                print("Run %s meets requirements [SHMS Angle is %s, Current is %s, Charge is %s, Lambda events are %s]" % (Run[i],Theta_SHMS[i],Current[i],Charge[i],lamb[i]))
                if CURRENT_low < float(Current[i]) < CURRENT_high :
                    lambda_fort.append(float(lamb[i]))
                    charge_fort.append(float(Charge[i]))
                    # print("->Run %s meets requirements [SHMS Angle is %s, Current is %s, Charge is %s, Lambda events are %s]" % (Run[i],Theta_SHMS[i],Current[i],Charge[i],lamb[i]))
        i=i+1
        if i == len(Run) :
            break
        
    #print("Total Charge is  %s, Total lambdas are %s" % (sum(tot_charge),sum(tot_lambda)))
    # print("\nCharge for this setting is  %0.2f, %0.1f%% of charge stat goal" % (sum(tot_charge),(sum(tot_charge)/charge_goal)*100))
    # print("Charge for this setting is  %0.2f, %0.1f%% of PAC charge stat goal\n" % (sum(tot_charge),(sum(tot_charge)/charge_goalPAC)*100))

    print("\n\nTotal Charge for %s degrees is %0.2f, %0.1f%% of charge goal" % (ANGLE, sum(acc_charge), (sum(acc_charge)/charge_goal)*100))
    # print("Charge at 40 uA are  %0.2f, %0.1f%% of charge goal" % ((sum(charge_fort)),(sum(charge_fort)/charge_goal)*100)) # At 40 uA
    # print("Total Charge for %s degrees is %0.2f, %0.1f%% of PAC charge stat goal\n" % (ANGLE, sum(acc_charge), (sum(acc_charge)/charge_goalPAC)*100))

    #print("%0.1f hours to complete setting at this current (100%% efficiency)" % (charge_goal/(float(CURRENT)*(10e-3)*60*60)))
    #print("%0.1f hours to complete setting at this current (75%% efficiency)\n" % ((charge_goal)/(float(CURRENT)*.75*(10e-3)*60*60)))

    # print("Lambda events were hand written in runlist, may be subject to change...")
    print("Total Lambda Events are  %0.2f, %0.1f%% of stat goal" % (sum(tot_lambda),(sum(tot_lambda)/lambda_goal)*100))
    # print("Lambda Events at 40 uA are  %0.2f, %0.1f%% of 40 uA stat goal" % (sum(lambda_fort),(sum(lambda_fort)/1000)*100)) # At 40 uA
    print("---->[Lambdas per Coulomb: %0.2f]<----\n\n" % ((sum(tot_lambda)/sum(acc_charge))*100))
    # print("Total Lambda Events are  %0.2f, %0.1f%% of PAC stat goal\n" % (sum(tot_lambda),(sum(tot_lambda)/lambda_goalPAC)*100))

    print("This is a rough estimate based on the runlist so make sure the runlist is up to date and correct\n\n")
    print("This is only for LH2 runs, not for target charge of dummy!!!\n\n")

if __name__=='__main__': main()
