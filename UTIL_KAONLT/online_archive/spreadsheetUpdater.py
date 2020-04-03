#!/usr/bin/env python
#-*- coding: utf-8 -*-

import xlsxwriter

from PIL import ImageFont

##########################################
#############6.2 GeV######################
##########################################
kin6p2_setting1 = 'Q2=3.0|W=2.32|x=0.40'
kin6p2_center1 = '13.28'
kin6p2_center1_Values = (
    # current
    [70,
     # tPAC
     6,
     # tPACPrime, same as tPAC just sheet 2
     6,
     # qPAC
     0,
     # lambda evnt
     1703,
     # lambda evntPAC
     1550]
)
kin6p2DUM_center1 = '13.28'
kin6p2DUM_center1_Values = (
    # current
    [40,
     # tPAC
     0.4,
     # tPACPrime, same as tPAC just sheet 2
     0.4,
     # qPAC
     0,
     # lambda evnt
     0,
     # lambda evntPAC
     0]
)
kin6p2_left1 = '16.28'
kin6p2_left1_Values = (
    # current
    [70,
     # tPAC
     6,
     # tPACPrime, same as tPAC just sheet 2
     6,
     # qPAC
     0,
     # lambda evnt
     1477,
     # lambda evntPAC
     1550]
)
kin6p2DUM_left1 = '16.28'
kin6p2DUM_left1_Values = (
    # current
    [40,
     # tPAC
     0.4,
     # tPACPrime, same as tPAC just sheet 2
     0.4,
     # qPAC
     0,
     # lambda evnt
     0,
     # lambda evntPAC
     0]
)
##########################################
kin6p2_setting2 = 'Q2=2.115|W=2.95|x=0.21'
kin6p2_center2 = '5.90'
kin6p2_center2_Values = (
    # current
    [55,
     # tPAC
     21,
     # tPACPrime, same as tPAC just sheet 2
     21,
     # qPAC
     0,
     # lambda evnt
     579,
     # lambda evntPAC
     1750]
)
kin6p2DUM_center2 = '5.90'
kin6p2DUM_center2_Values = (
    # current
    [40,
     # tPAC
     1.1,
     # tPACPrime, same as tPAC just sheet 2
     1.1,
     # qPAC
     0,
     # lambda evnt
     0,
     # lambda evntPAC
     0]
)
kin6p2_left2 = '8.48'
kin6p2_left2_Values = (
    # current
    [70,
     # tPAC
     15,
     # tPACPrime, same as tPAC just sheet 2
     15,
     # qPAC
     0,
     # lambda evnt
     723,
     # lambda evntPAC
     1165]
)
kin6p2DUM_left2 = '8.48'
kin6p2DUM_left2_Values = (
    # current
    [40,
     # tPAC
     1.5,
     # tPACPrime, same as tPAC just sheet 2
     1.5,
     # qPAC
     0,
     # lambda evnt
     0,
     # lambda evntPAC
     0]
)

##########################################
#############8.2 GeV######################
##########################################
kin8p2_setting1 = 'Q2=4.4|W=2.74|x=0.40'
kin8p2_center1 = '10.00'
kin8p2_center1_Values = (
    # current
    [70,
     # tPAC
     16.3,
     # tPACPrime, same as tPAC just sheet 2
     16.3,
     # qPAC
     0,
     # lambda evnt
     2728,
     # lambda evntPAC
     2500]
)
kin8p2DUM_center1 = '10.00'
kin8p2DUM_center1_Values = (
    # current
    [40,
     # tPAC
     1.1,
     # tPACPrime, same as tPAC just sheet 2
     1.1,
     # qPAC
     0,
     # lambda evnt
     0,
     # lambda evntPAC
     0]
)
kin8p2_left1 = '13.00'
kin8p2_left1_Values = (
    # current
    [70,
     # tPAC
     16.3,
     # tPACPrime, same as tPAC just sheet 2
     16.3,
     # qPAC
     0,
     # lambda evnt
     4046,
     # lambda evntPAC
     2250]
)
kin8p2DUM_left1 = '13.00'
kin8p2DUM_left1_Values = (
    # current
    [40,
     # tPAC
     1.1,
     # tPACPrime, same as tPAC just sheet 2
     1.1,
     # qPAC
     0,
     # lambda evnt
     0,
     # lambda evntPAC
     0]
)

##########################################
kin8p2_setting2 = 'Q2=3.0|W=3.14|x=0.25'
kin8p2_center2 = '6.89'
kin8p2_center2_Values = (
    # current
    [70,
     # tPAC
     40.2,
     # tPACPrime, same as tPAC just sheet 2
     40.2,
     # qPAC
     0,

     # lambda evnt
     11626,
     # lambda evntPAC
     8200]
)
kin8p2DUM_center2 = '6.89'
kin8p2DUM_center2_Values = (
    # current
    [40,
     # tPAC
     2.8,
     # tPACPrime, same as tPAC just sheet 2
     2.8,
     # qPAC
     0,

     # lambda evnt
     0,
     # lambda evntPAC
     0]
)
kin8p2_left2 = '9.89'
kin8p2_left2_Values = (
    # current
    [70,
     # tPAC
     40.2,
     # tPACPrime, same as tPAC just sheet 2
     40.2,
     # qPAC
     0,
     # lambda evnt
     8405,
     # lambda evntPAC
     6100]
)
kin8p2DUM_left2 = '9.89'
kin8p2DUM_left2_Values = (
    # current
    [40,
     # tPAC
     2.8,
     # tPACPrime, same as tPAC just sheet 2
     2.8,
     # qPAC
     0,
     # lambda evnt
     0,
     # lambda evntPAC
     0]
)

##########################################
kin8p2_setting3 = 'Q2=5.5|W=3.02|x=0.40'
kin8p2_center3 = '5.90'
kin8p2_center3_Values = (
    # current
    [70,
     # tPAC
     40.1,
     # tPACPrime, same as tPAC just sheet 2
     40.1,
     # qPAC
     0,
     # lambda evnt
     1164,
     # lambda evntPAC
     525]
)
kin8p2DUM_center3 = '5.90'
kin8p2DUM_center3_Values = (
    # current
    [40,
     # tPAC
     2.8,
     # tPACPrime, same as tPAC just sheet 2
     2.8,
     # qPAC
     0,
     # lambda evnt
     0,
     # lambda evntPAC
     0]
)
kin8p2_left3 = '8.48'
kin8p2_left3_Values = (
    # current
    [70,
     # tPAC
     40.1,
     # tPACPrime, same as tPAC just sheet 2
     40.1,
     # qPAC
     0,
     # lambda evnt
     835,
     # lambda evntPAC
     525]
)
kin8p2DUM_left3 = '8.48'
kin8p2DUM_left3_Values = (
    # current
    [40,
     # tPAC
     2.8,
     # tPACPrime, same as tPAC just sheet 2
     2.8,
     # qPAC
     0,
     # lambda evnt
     0,
     # lambda evntPAC
     0]
)

wb = xlsxwriter.Workbook('test.xls')

# Add first sheet in spreadsheet
s1 = wb.add_worksheet('6.2 GeV Summary')

# Specify formatting
bold = wb.add_format({'bold': True})

# Set row and column size
s1.set_default_row(30)
s1.set_column(0,14,15)

# Merging first row to fit title
s1.merge_range('A1:M1','6.2 GeV KAON-LT Physics Setting',bold)

# write(column[row],'Name of cell',formatting)
s1.write('A2', 'Setting',bold)
s1.write('B2', 'BCM4A \nCharge (mC)',bold)
s1.write('C2', 't_run (sec)',bold)
s1.write('D2', 't_setting (sec)',bold)
s1.write('E2', 't_PAC \n(hr @ 100% eff)',bold)
s1.write('F2', 't_setting/t_PAC',bold)
s1.write('G2', 'Q_PAC',bold)
s1.write('H2', 'Q_actual (mC)',bold)
s1.write('I2', 'Q_actual/Q_PAC',bold)
s1.write('J2', 'Effective \nEfficiency (J/H)',bold)
# Delta: u'\u0394' (UTF-8)
s1.write('K2', 'K+%s \nrun plan events' % (u'\u0394'),bold)
s1.write('L2', 'K+%s \nactual events' % (u'\u0394'),bold)
s1.write('M2', 'K+%s \nactual/proposed' % (u'\u0394'),bold)
s1.write('N2', 'K+%s \nY_obs/Y_expect' % (u'\u0394'),bold)

# Add first sheet in spreadsheet
s2 = wb.add_worksheet('6.2 Gev|%s' % kin6p2_setting1)

# Set row and column size
s2.set_default_row(30)
s2.set_column(0,14,15)

# Merging first row to fit title
s2.merge_range('A1:M1','6.2 GeV KAON-LT Physics Setting',bold)

s2.write('A2', 'SHMS Angle',bold)
s2.write('B2', 'Run Number',bold)
s2.write('C2', 'BCM4A \nCharge (mC)',bold)
s2.write('D2', 't_run (sec)',bold)
s2.write('E2', 'Current (uA)',bold)
s2.write('F2', 't_setting (sec)',bold)
s2.write('G2', 't_PAC \n(hr @ 100% eff)',bold)
s2.write('H2', 't_setting/t_PAC',bold)
s2.write('I2', 'Q_PAC',bold)
s2.write('J2', 'Q_actual/Q_PAC',bold)
s2.write('K2', 'Effective \nEfficiency (J/H)',bold)

###############################################################################
# 6.2 GeV, Setting 1 ##########################################################
###############################################################################

s1.merge_range('A3:B3','%s' % kin6p2_setting1 ,bold)
s2.merge_range('A3:B3','%s' % kin6p2_setting1 ,bold)

l1 = 0
l2 = 0
curNum = 5
newData = ()

current = kin6p2_center1_Values[0]
tPAC= kin6p2_center1_Values[1]
tPACPrime = kin6p2_center1_Values[2]
qPAC = kin6p2_center1_Values[3]
evnt= kin6p2_center1_Values[4]
evntPAC = kin6p2_center1_Values[5]

s1.write('A4', '%s deg LH2' % kin6p2_center1)
s2.write('A4', '%s deg LH2' % kin6p2_center1)

print("Looking at current %s uA" % (current))
# [RunNum,charge]
newData = (
    [7871, 241.648],
    [7872, 234.072],
    [7873, 222.282],
    [7874, 276.079],
    [7875, 221.651],
    [7876, 231.678],
    [7877, 222.27],
)
tmpCurr = [current]
for value in (tmpCurr):
    s2.write('A%s' % (curNum+l2), '@ %suA (mC)' % (value))
    # Starts at 0 for rows and columns
    row = l2+curNum-1
    col = 1
    for runNum, BCM4A in (newData):
        s2.write(row,col, runNum)
        s2.write(row,col+1, BCM4A)
        row += 1
    end = row+1
    # Going back to sheet one so we can 'link' second sheet values
    s2.write('B%s' % (end), 'Total',bold)
    s2.write_formula('C%s' % (end), '=SUM(C%s:C%s)' % (curNum+l2,end-1) ,bold)
    s2.write('E%s' % (end), current,bold)
    s2.write('G%s' % (end), tPAC,bold)
    s2.write_formula('I%s' % (end),'=G%s*3600*0.000070*1000' % (end) ,bold)
    s2.write_formula('J%s' % (end), '=C%s/I%s' % (end,end),bold)
    l2 = end+1
    curNum = 5+l1
    print("%s" % curNum)
    s1.write('A%s' % (curNum), '@ %suA (mC)' % (value))
    s1.write_formula('B%s' % (curNum), '=\'6.2 Gev|%s\'!C%s' % (kin6p2_setting1,end))
    s1.write_formula('C%s' % (curNum), '=\'6.2 Gev|%s\'!D%s' % (kin6p2_setting1,end))
    s1.write_formula('D%s' % (curNum), '=\'6.2 Gev|%s\'!F%s' % (kin6p2_setting1,end))
    s1.write_formula('H%s' % (curNum), '=\'6.2 Gev|%s\'!C%s' % (kin6p2_setting1,end))
    s1.write('L%s' % (curNum), evnt)
    curNum += 1
endCur =  curNum
l1 = endCur+1

s1.write_formula('F%s' % (curNum), '=D%s/3600/E%s' % (curNum-1,endCur-1))
s1.write_formula('I%s' % (curNum), '=B%s/G%s' % (curNum,qPAC))
s1.write_formula('M%s' % (curNum), '=L%s/K%s' % (curNum,evntPAC))

s1.write('B%s' % (endCur), 'Total',bold)
s1.write_formula('D%s' % (endCur), '=SUM(D%s:D%s)' % (curNum-1,endCur-1),bold)
s1.write('E%s' % (endCur), tPACPrime,bold)
s1.write_formula('F%s' % (endCur), 'D%s/3600/E%s' % (endCur,endCur),bold)
s1.write_formula('G%s' % (endCur), '=\'6.2 Gev|%s\'!I%s' % (kin6p2_setting1,end),bold)
s1.write_formula('H%s' % (endCur), '=SUM(H%s:H%s)' % (curNum-1,endCur-1),bold)
s1.write_formula('I%s' % (endCur), '=H%s/G%s' % (endCur,endCur),bold)
s1.write('K%s' % (endCur), evntPAC,bold)
s1.write_formula('L%s' % (endCur), '=SUM(L%s:L%s)' % (curNum-1,endCur-1),bold)
s1.write_formula('M%s' % (endCur), '=L%s/K%s' % (endCur,endCur),bold)
s1.write_formula('N%s' % (endCur), '=M%s/I%s' % (endCur,endCur),bold)

######################################################################################################

curNum =0

current = kin6p2DUM_left1_Values[0]
tPAC= kin6p2DUM_left1_Values[1]
tPACPrime = kin6p2DUM_left1_Values[2]
qPAC = kin6p2DUM_left1_Values[3]
evnt= kin6p2DUM_left1_Values[4]
evntPAC = kin6p2DUM_left1_Values[5]

print("Looking at current %s uA" % (current))
# [RunNum,charge]
newData = (
    [7878, 10.921],
    [7879, 31.699],
    [7880, 31.699],
)
tmpCurr = [current]
for value in (tmpCurr):
    s2.write('A%s' % (curNum+l2), 'DUMMY (%suA)' % (value))
    # Starts at 0 for rows and columns
    row = l2+curNum-1
    col = 1
    for runNum, BCM4A in (newData):
        s2.write(row,col, runNum)
        s2.write(row,col+1, BCM4A)
        row += 1
    end = row+1
    # Going back to sheet one so we can 'link' second sheet values
    s2.write('B%s' % (end), 'Total',bold)
    s2.write_formula('C%s' % (end), '=SUM(C%s:C%s)' % (curNum+l2,end-1) ,bold)
    s2.write('E%s' % (end), current,bold)
    s2.write('G%s' % (end), tPAC,bold)
    s2.write_formula('I%s' % (end),'=G%s*3600*0.000004*1000' % (end) ,bold)
    s2.write_formula('J%s' % (end), '=C%s/I%s' % (end,end),bold)
    l2 = end+1
    curNum = l1
    print("%s" % curNum)
    s1.write('A%s' % (curNum), 'DUMMY (%suA)' % (value))
    s1.write_formula('B%s' % (curNum), '=\'6.2 Gev|%s\'!C%s' % (kin6p2_setting1,end))
    s1.write_formula('C%s' % (curNum), '=\'6.2 Gev|%s\'!D%s' % (kin6p2_setting1,end))
    s1.write_formula('D%s' % (curNum), '=\'6.2 Gev|%s\'!F%s' % (kin6p2_setting1,end))
    s1.write_formula('H%s' % (curNum), '=\'6.2 Gev|%s\'!C%s' % (kin6p2_setting1,end))
    s1.write('L%s' % (curNum), evnt)
    curNum += 1
endCur =  curNum
l1 = endCur+1

s1.write_formula('F%s' % (curNum), '=D%s/3600/E%s' % (curNum-1,endCur-1))
s1.write_formula('I%s' % (curNum), '=B%s/G%s' % (curNum,qPAC))
s1.write_formula('M%s' % (curNum), '=L%s/K%s' % (curNum,evntPAC))

s1.write('B%s' % (endCur), 'Total',bold)
s1.write_formula('D%s' % (endCur), '=SUM(D%s:D%s)' % (curNum-1,endCur-1),bold)
s1.write('E%s' % (endCur), tPACPrime,bold)
s1.write_formula('F%s' % (endCur), 'D%s/3600/E%s' % (endCur,endCur),bold)
s1.write('G%s' % (endCur), '=\'6.2 Gev|%s\'!I%s' % (kin6p2_setting1,end),bold)
s1.write_formula('H%s' % (endCur), '=SUM(H%s:H%s)' % (curNum-1,endCur-1),bold)
s1.write_formula('I%s' % (endCur), '=H%s/G%s' % (endCur,endCur),bold)
s1.write('K%s' % (endCur), evntPAC,bold)
s1.write_formula('L%s' % (endCur), '=SUM(L%s:L%s)' % (curNum-1,endCur-1),bold)
s1.write_formula('M%s' % (endCur), '=L%s/K%s' % (endCur,endCur),bold)
s1.write_formula('N%s' % (endCur), '=M%s/I%s' % (endCur,endCur),bold)

####################################################################################################
# Next angle #############
##########################

curNum =1

current = kin6p2_left1_Values[0]
tPAC= kin6p2_left1_Values[1]
tPACPrime = kin6p2_left1_Values[2]
qPAC = kin6p2_left1_Values[3]
evnt= kin6p2_left1_Values[4]
evntPAC = kin6p2_left1_Values[5]

s1.write('A%s' % (l1), '%s deg LH2' % kin6p2_left1)
s2.write('A%s' % (l2), '%s deg LH2' % kin6p2_left1)


print("Looking at current %s uA" % (current))
# [RunNum,charge]
newData = (
    [7882,209.19],
    [7883,257.17],
    [7884,243.51],
    [7885,267.2],
    [7886,266.44],
    [7887,301.65],
)
tmpCurr = [current]
for value in (tmpCurr):
    s2.write('A%s' % (curNum+l2), '@ %suA (mC)' % (value))
    # Starts at 0 for rows and columns
    row = l2+curNum-1
    col = 1
    for runNum, BCM4A in (newData):
        s2.write(row,col, runNum)
        s2.write(row,col+1, BCM4A)
        row += 1
    end = row+1
    # Going back to sheet one so we can 'link' second sheet values
    s2.write('B%s' % (end), 'Total',bold)
    s2.write_formula('C%s' % (end), '=SUM(C%s:C%s)' % (curNum+l2,end-1) ,bold)
    s2.write('E%s' % (end), current,bold)
    s2.write('G%s' % (end), tPAC,bold)
    s2.write_formula('I%s' % (end),'=G%s*3600*0.000070*1000' % (end) ,bold)
    s2.write_formula('J%s' % (end), '=C%s/I%s' % (end,end),bold)
    l2 = end+1
    curNum = 1+l1
    print("%s" % curNum)
    s1.write('A%s' % (curNum), '@ %suA (mC)' % (value))
    s1.write_formula('B%s' % (curNum), '=\'6.2 Gev|%s\'!C%s' % (kin6p2_setting1,end))
    s1.write_formula('C%s' % (curNum), '=\'6.2 Gev|%s\'!D%s' % (kin6p2_setting1,end))
    s1.write_formula('D%s' % (curNum), '=\'6.2 Gev|%s\'!F%s' % (kin6p2_setting1,end))
    # s1.write_formula('F%s' % (curNum), '=D%s/3600/E%s' % (curNum,curNum+1)) Need work
    s1.write_formula('H%s' % (curNum), '=\'6.2 Gev|%s\'!C%s' % (kin6p2_setting1,end))
    # s1.write_formula('I%s' % (curNum), '=B%s/G%s' % (curNum,curNum+1))
    s1.write('L%s' % (curNum), evnt)
    # s1.write_formula('M%s' % (curNum), '=L%s/K%s' % (curNum,curNum+1))
    curNum += 1
endCur =  curNum
l1 = endCur+1
s1.write('B%s' % (endCur), 'Total',bold)
s1.write_formula('D%s' % (endCur), '=SUM(D%s:D%s)' % (curNum-1,endCur-1),bold)
s1.write('E%s' % (endCur), tPACPrime,bold)
s1.write_formula('F%s' % (endCur), 'D%s/3600/E%s' % (endCur,endCur),bold)
s1.write('G%s' % (endCur), '=\'6.2 Gev|%s\'!I%s' % (kin6p2_setting1,end),bold)
s1.write_formula('H%s' % (endCur), '=SUM(H%s:H%s)' % (curNum-1,endCur-1),bold)
s1.write_formula('I%s' % (endCur), '=H%s/G%s' % (endCur,endCur),bold)
s1.write('K%s' % (endCur), evntPAC,bold)
s1.write_formula('L%s' % (endCur), '=SUM(L%s:L%s)' % (curNum-1,endCur-1),bold)
s1.write_formula('M%s' % (endCur), '=L%s/K%s' % (endCur,endCur),bold)
s1.write_formula('N%s' % (endCur), '=M%s/I%s' % (endCur,endCur),bold)

######################################################################################################

curNum =0

current = kin6p2DUM_center1_Values[0]
tPAC= kin6p2DUM_center1_Values[1]
tPACPrime = kin6p2DUM_center1_Values[2]
qPAC = kin6p2DUM_center1_Values[3]
evnt= kin6p2DUM_center1_Values[4]
evntPAC = kin6p2DUM_center1_Values[5]

print("Looking at current %s uA" % (current))
# [RunNum,charge]
newData = (
    [7881,55.62],
    [7888,71.48],
)
tmpCurr = [current]
for value in (tmpCurr):
    s2.write('A%s' % (curNum+l2), 'DUMMY (%suA)' % (value))
    # Starts at 0 for rows and columns
    row = l2+curNum-1
    col = 1
    for runNum, BCM4A in (newData):
        s2.write(row,col, runNum)
        s2.write(row,col+1, BCM4A)
        row += 1
    end = row+1
    # Going back to sheet one so we can 'link' second sheet values
    s2.write('B%s' % (end), 'Total',bold)
    s2.write_formula('C%s' % (end), '=SUM(C%s:C%s)' % (curNum+l2,end-1) ,bold)
    s2.write('E%s' % (end), current,bold)
    s2.write('G%s' % (end), tPAC,bold)
    s2.write_formula('I%s' % (end),'=G%s*3600*0.000040*1000' % (end) ,bold)
    s2.write_formula('J%s' % (end), '=C%s/I%s' % (end,end),bold)
    l2 = end+1
    curNum = l1
    print("%s" % curNum)
    s1.write('A%s' % (curNum), 'DUMMY (%suA)' % (value))
    s1.write_formula('B%s' % (curNum), '=\'6.2 Gev|%s\'!C%s' % (kin6p2_setting1,end))
    s1.write_formula('C%s' % (curNum), '=\'6.2 Gev|%s\'!D%s' % (kin6p2_setting1,end))
    s1.write_formula('D%s' % (curNum), '=\'6.2 Gev|%s\'!F%s' % (kin6p2_setting1,end))
    s1.write_formula('H%s' % (curNum), '=\'6.2 Gev|%s\'!C%s' % (kin6p2_setting1,end))
    s1.write('L%s' % (curNum), evnt)
    curNum += 1
endCur =  curNum
l1 = endCur+1

s1.write_formula('F%s' % (curNum), '=D%s/3600/E%s' % (curNum-1,endCur-1))
s1.write_formula('I%s' % (curNum), '=B%s/G%s' % (curNum,qPAC))
s1.write_formula('M%s' % (curNum), '=L%s/K%s' % (curNum,evntPAC))

s1.write('B%s' % (endCur), 'Total',bold)
s1.write_formula('D%s' % (endCur), '=SUM(D%s:D%s)' % (curNum-1,endCur-1),bold)
s1.write('E%s' % (endCur), tPACPrime,bold)
s1.write_formula('F%s' % (endCur), 'D%s/3600/E%s' % (endCur,endCur),bold)
s1.write('G%s' % (endCur), '=\'6.2 Gev|%s\'!I%s' % (kin6p2_setting1,end),bold)
s1.write_formula('H%s' % (endCur), '=SUM(H%s:H%s)' % (curNum-1,endCur-1),bold)
s1.write_formula('I%s' % (endCur), '=H%s/G%s' % (endCur,endCur),bold)
s1.write('K%s' % (endCur), evntPAC,bold)
s1.write_formula('L%s' % (endCur), '=SUM(L%s:L%s)' % (curNum-1,endCur-1),bold)
s1.write_formula('M%s' % (endCur), '=L%s/K%s' % (endCur,endCur),bold)
s1.write_formula('N%s' % (endCur), '=M%s/I%s' % (endCur,endCur),bold)

####################################################################################################

###############################################################################
# 6.2 GeV, Setting 2 ##########################################################
###############################################################################

s2a = wb.add_worksheet('6.2 Gev|%s' % kin6p2_setting2)

# Set row and column size
s2a.set_default_row(30)
s2a.set_column(0,14,15)

# Merging first row to fit title
s2a.merge_range('A1:M1','6.2 GeV KAON-LT Physics Setting',bold)

s2a.write('A2', 'SHMS Angle',bold)
s2a.write('B2', 'Run Number',bold)
s2a.write('C2', 'BCM4A \nCharge (mC)',bold)
s2a.write('D2', 't_run (sec)',bold)
s2a.write('E2', 'Current (uA)',bold)
s2a.write('F2', 't_setting (sec)',bold)
s2a.write('G2', 't_PAC \n(hr @ 100% eff)',bold)
s2a.write('H2', 't_setting/t_PAC',bold)
s2a.write('I2', 'Q_PAC',bold)
s2a.write('J2', 'Q_actual/Q_PAC',bold)
s2a.write('K2', 'Effective \nEfficiency (J/H)',bold)


l2=3
 
s1.merge_range('A%s:B%s' % (l1,l1),'%s' % kin6p2_setting2 ,bold)
s2a.merge_range('A%s:B%s' % (l2,l2),'%s' % kin6p2_setting2 ,bold)

curNum = 2
newData = ()

current = kin6p2_center2_Values[0]
tPAC= kin6p2_center2_Values[1]
tPACPrime = kin6p2_center2_Values[2]
qPAC = kin6p2_center2_Values[3]
evnt= kin6p2_center2_Values[4]
evntPAC = kin6p2_center2_Values[5]

s1.write('A%s' % (l1+1), '%s deg LH2' % kin6p2_center2)
s2a.write('A%s' % (l2+1), '%s deg LH2' % kin6p2_center2)

print("Looking at current %s uA" % (current))
# [RunNum,charge]
newData = (
    [7891,252.502],
    [7891,232.9],
    [7892,226.93],
    [7893,195.38],
    [7894,214.42],
    [7895,362.67],
    [7896,234.96],
    [7899,260.56],
    [7900,242.66],
    [7901,240.04],
    [7902,239.04],
    [7903,253.33],
    [7904,181.34],
    [7905,238.33],
    [7906,219.53],
    [7907,219.53],
    [7908,141.28],
)
tmpCurr = [current]
for value in (tmpCurr):
    s2a.write('A%s' % (curNum+l2), '@ %suA (mC)' % (value))
    # Starts at 0 for rows and columns
    row = l2+curNum-1
    col = 1
    for runNum, BCM4A in (newData):
        s2a.write(row,col, runNum)
        s2a.write(row,col+1, BCM4A)
        row += 1
    end = row+1
    # Going back to sheet one so we can 'link' second sheet values
    s2a.write('B%s' % (end), 'Total',bold)
    s2a.write_formula('C%s' % (end), '=SUM(C%s:C%s)' % (curNum+l2,end-1) ,bold)
    s2a.write('E%s' % (end), current,bold)
    s2a.write('G%s' % (end), tPAC,bold)
    s2a.write_formula('I%s' % (end),'=G%s*3600*0.000055*1000' % (end) ,bold)
    s2a.write_formula('J%s' % (end), '=C%s/I%s' % (end,end),bold)
    l2 = end+1
    curNum = 2+l1
    print("%s" % curNum)
    s1.write('A%s' % (curNum), '@ %suA (mC)' % (value))
    s1.write_formula('B%s' % (curNum), '=\'6.2 Gev|%s\'!C%s' % (kin6p2_setting2,end))
    s1.write_formula('C%s' % (curNum), '=\'6.2 Gev|%s\'!D%s' % (kin6p2_setting2,end))
    s1.write_formula('D%s' % (curNum), '=\'6.2 Gev|%s\'!F%s' % (kin6p2_setting2,end))
    s1.write_formula('H%s' % (curNum), '=\'6.2 Gev|%s\'!C%s' % (kin6p2_setting2,end))
    s1.write('L%s' % (curNum), evnt)
    curNum += 1
endCur =  curNum
l1 = endCur+1

s1.write_formula('F%s' % (curNum), '=D%s/3600/E%s' % (curNum-1,endCur-1))
s1.write_formula('I%s' % (curNum), '=B%s/G%s' % (curNum,qPAC))
s1.write_formula('M%s' % (curNum), '=L%s/K%s' % (curNum,evntPAC))

s1.write('B%s' % (endCur), 'Total',bold)
s1.write_formula('D%s' % (endCur), '=SUM(D%s:D%s)' % (curNum-1,endCur-1),bold)
s1.write('E%s' % (endCur), tPACPrime,bold)
s1.write_formula('F%s' % (endCur), 'D%s/3600/E%s' % (endCur,endCur),bold)
s1.write('G%s' % (endCur), '=\'6.2 Gev|%s\'!I%s' % (kin6p2_setting2,end),bold)
s1.write_formula('H%s' % (endCur), '=SUM(H%s:H%s)' % (curNum-1,endCur-1),bold)
s1.write_formula('I%s' % (endCur), '=H%s/G%s' % (endCur,endCur),bold)
s1.write('K%s' % (endCur), evntPAC,bold)
s1.write_formula('L%s' % (endCur), '=SUM(L%s:L%s)' % (curNum-1,endCur-1),bold)
s1.write_formula('M%s' % (endCur), '=L%s/K%s' % (endCur,endCur),bold)
s1.write_formula('N%s' % (endCur), '=M%s/I%s' % (endCur,endCur),bold)

######################################################################################################

curNum =0

current = kin6p2DUM_left1_Values[0]
tPAC= kin6p2DUM_left1_Values[1]
tPACPrime = kin6p2DUM_left1_Values[2]
qPAC = kin6p2DUM_left1_Values[3]
evnt= kin6p2DUM_left1_Values[4]
evntPAC = kin6p2DUM_left1_Values[5]

print("Looking at current %s uA" % (current))
# [RunNum,charge]
newData = (
    [7897,41.31],
    [7898,87.38],
)
tmpCurr = [current]
for value in (tmpCurr):
    s2a.write('A%s' % (curNum+l2), 'DUMMY (%suA)' % (value))
    # Starts at 0 for rows and columns
    row = l2+curNum-1
    col = 1
    for runNum, BCM4A in (newData):
        s2a.write(row,col, runNum)
        s2a.write(row,col+1, BCM4A)
        row += 1
    end = row+1
    # Going back to sheet one so we can 'link' second sheet values
    s2a.write('B%s' % (end), 'Total',bold)
    s2a.write_formula('C%s' % (end), '=SUM(C%s:C%s)' % (curNum+l2,end-1) ,bold)
    s2a.write('E%s' % (end), current,bold)
    s2a.write('G%s' % (end), tPAC,bold)
    s2a.write_formula('I%s' % (end),'=G%s*3600*0.000040*1000' % (end) ,bold)
    s2a.write_formula('J%s' % (end), '=C%s/I%s' % (end,end),bold)
    l2 = end+1
    curNum = l1
    print("%s" % curNum)
    s1.write('A%s' % (curNum), 'DUMMY (%suA)' % (value))
    s1.write_formula('B%s' % (curNum), '=\'6.2 Gev|%s\'!C%s' % (kin6p2_setting2,end))
    s1.write_formula('C%s' % (curNum), '=\'6.2 Gev|%s\'!D%s' % (kin6p2_setting2,end))
    s1.write_formula('D%s' % (curNum), '=\'6.2 Gev|%s\'!F%s' % (kin6p2_setting2,end))
    s1.write_formula('H%s' % (curNum), '=\'6.2 Gev|%s\'!C%s' % (kin6p2_setting2,end))
    s1.write('L%s' % (curNum), evnt)
    curNum += 1
endCur =  curNum
l1 = endCur+1

s1.write_formula('F%s' % (curNum), '=D%s/3600/E%s' % (curNum-1,endCur-1))
s1.write_formula('I%s' % (curNum), '=B%s/G%s' % (curNum,qPAC))
s1.write_formula('M%s' % (curNum), '=L%s/K%s' % (curNum,evntPAC))

s1.write('B%s' % (endCur), 'Total',bold)
s1.write_formula('D%s' % (endCur), '=SUM(D%s:D%s)' % (curNum-1,endCur-1),bold)
s1.write('E%s' % (endCur), tPACPrime,bold)
s1.write_formula('F%s' % (endCur), 'D%s/3600/E%s' % (endCur,endCur),bold)
s1.write('G%s' % (endCur), '=\'6.2 Gev|%s\'!I%s' % (kin6p2_setting2,end),bold)
s1.write_formula('H%s' % (endCur), '=SUM(H%s:H%s)' % (curNum-1,endCur-1),bold)
s1.write_formula('I%s' % (endCur), '=H%s/G%s' % (endCur,endCur),bold)
s1.write('K%s' % (endCur), evntPAC,bold)
s1.write_formula('L%s' % (endCur), '=SUM(L%s:L%s)' % (curNum-1,endCur-1),bold)
s1.write_formula('M%s' % (endCur), '=L%s/K%s' % (endCur,endCur),bold)
s1.write_formula('N%s' % (endCur), '=M%s/I%s' % (endCur,endCur),bold)

####################################################################################################
# Next angle #############
##########################

curNum =1
current = kin6p2_left2_Values[0]
tPAC= kin6p2_left2_Values[1]
tPACPrime = kin6p2_left2_Values[2]
qPAC = kin6p2_left2_Values[3]
evnt= kin6p2_left2_Values[4]
evntPAC = kin6p2_left2_Values[5]

s1.write('A%s' % (l1), '%s deg LH2' % kin6p2_left2)
s2a.write('A%s' % (l2), '%s deg LH2' % kin6p2_left2)


print("Looking at current %s uA" % (current))
# [RunNum,charge]
newData = (
    [7909, 131.014],
    [7910, 55.047],
    [7911, 77.354],
    [7912, 28.683],
    [7913, 76.601],
    [7914, 117.79],
    [7915, 118.783],
    [7916, 135.726],
    [7917, 146.517],
    [7918, 27.966],
    [7919, 142.475],
    [7920, 116.507],
    [7921, 182.834],
    [7925, 170.95],
    [7926, 183.094],
    [7927, 143.944],
    [7928, 72.459],
    [7930, 13.966],
    [7931, 175.929],
    [7932, 171.455],
    [7933, 168.158],
    [7934, 176.0],
    [7935, 158.969],
    [7936, 151.628],
    [7937, 164.136],
    [7938, 143.332],

)
tmpCurr = [current]
for value in (tmpCurr):
    s2a.write('A%s' % (curNum+l2), '@ %suA (mC)' % (value))
    # Starts at 0 for rows and columns
    row = l2+curNum-1
    col = 1
    for runNum, BCM4A in (newData):
        s2a.write(row,col, runNum)
        s2a.write(row,col+1, BCM4A)
        row += 1
    end = row+1
    # Going back to sheet one so we can 'link' second sheet values
    s2a.write('B%s' % (end), 'Total',bold)
    s2a.write_formula('C%s' % (end), '=SUM(C%s:C%s)' % (curNum+l2,end-1) ,bold)
    s2a.write('E%s' % (end), current,bold)
    s2a.write('G%s' % (end), tPAC,bold)
    s2a.write_formula('I%s' % (end),'=G%s*3600*0.000055*1000' % (end) ,bold)
    s2a.write_formula('J%s' % (end), '=C%s/I%s' % (end,end),bold)
    l2 = end+1
    curNum = 1+l1
    print("%s" % curNum)
    s1.write('A%s' % (curNum), '@ %suA (mC)' % (value))
    s1.write_formula('B%s' % (curNum), '=\'6.2 Gev|%s\'!C%s' % (kin6p2_setting2,end))
    s1.write_formula('C%s' % (curNum), '=\'6.2 Gev|%s\'!D%s' % (kin6p2_setting2,end))
    s1.write_formula('D%s' % (curNum), '=\'6.2 Gev|%s\'!F%s' % (kin6p2_setting2,end))
    # s1.write_formula('F%s' % (curNum), '=D%s/3600/E%s' % (curNum,curNum+1)) Need work
    s1.write_formula('H%s' % (curNum), '=\'6.2 Gev|%s\'!C%s' % (kin6p2_setting2,end))
    # s1.write_formula('I%s' % (curNum), '=B%s/G%s' % (curNum,curNum+1))
    s1.write('L%s' % (curNum), evnt)
    # s1.write_formula('M%s' % (curNum), '=L%s/K%s' % (curNum,curNum+1))
    curNum += 1
endCur =  curNum
l1 = endCur+1
s1.write('B%s' % (endCur), 'Total',bold)
s1.write_formula('D%s' % (endCur), '=SUM(D%s:D%s)' % (curNum-1,endCur-1),bold)
s1.write('E%s' % (endCur), tPACPrime,bold)
s1.write_formula('F%s' % (endCur), 'D%s/3600/E%s' % (endCur,endCur),bold)
s1.write('G%s' % (endCur), '=\'6.2 Gev|%s\'!I%s' % (kin6p2_setting2,end),bold)
s1.write_formula('H%s' % (endCur), '=SUM(H%s:H%s)' % (curNum-1,endCur-1),bold)
s1.write_formula('I%s' % (endCur), '=H%s/G%s' % (endCur,endCur),bold)
s1.write('K%s' % (endCur), evntPAC,bold)
s1.write_formula('L%s' % (endCur), '=SUM(L%s:L%s)' % (curNum-1,endCur-1),bold)
s1.write_formula('M%s' % (endCur), '=L%s/K%s' % (endCur,endCur),bold)
s1.write_formula('N%s' % (endCur), '=M%s/I%s' % (endCur,endCur),bold)

######################################################################################################

curNum =0

current = kin6p2DUM_center1_Values[0]
tPAC= kin6p2DUM_center1_Values[1]
tPACPrime = kin6p2DUM_center1_Values[2]
qPAC = kin6p2DUM_center1_Values[3]
evnt= kin6p2DUM_center1_Values[4]
evntPAC = kin6p2DUM_center1_Values[5]

print("Looking at current %s uA" % (current))
# [RunNum,charge]
newData = (
    [7922, 23.781],
    [7923, 198.331],
    [7924, 100.607],
    
)
tmpCurr = [current]
for value in (tmpCurr):
    s2a.write('A%s' % (curNum+l2), 'DUMMY (%suA)' % (value))
    # Starts at 0 for rows and columns
    row = l2+curNum-1
    col = 1
    for runNum, BCM4A in (newData):
        s2a.write(row,col, runNum)
        s2a.write(row,col+1, BCM4A)
        row += 1
    end = row+1
    # Going back to sheet one so we can 'link' second sheet values
    s2a.write('B%s' % (end), 'Total',bold)
    s2a.write_formula('C%s' % (end), '=SUM(C%s:C%s)' % (curNum+l2,end-1) ,bold)
    s2a.write('E%s' % (end), current,bold)
    s2a.write('G%s' % (end), tPAC,bold)
    s2a.write_formula('I%s' % (end),'=G%s*3600*0.000040*1000' % (end) ,bold)
    s2a.write_formula('J%s' % (end), '=C%s/I%s' % (end,end),bold)
    l2 = end+1
    curNum = l1
    print("%s" % curNum)
    s1.write('A%s' % (curNum), 'DUMMY (%suA)' % (value))
    s1.write_formula('B%s' % (curNum), '=\'6.2 Gev|%s\'!C%s' % (kin6p2_setting2,end))
    s1.write_formula('C%s' % (curNum), '=\'6.2 Gev|%s\'!D%s' % (kin6p2_setting2,end))
    s1.write_formula('D%s' % (curNum), '=\'6.2 Gev|%s\'!F%s' % (kin6p2_setting2,end))
    s1.write_formula('H%s' % (curNum), '=\'6.2 Gev|%s\'!C%s' % (kin6p2_setting2,end))
    s1.write('L%s' % (curNum), evnt)
    curNum += 1
endCur =  curNum
l1 = endCur+1

s1.write_formula('F%s' % (curNum), '=D%s/3600/E%s' % (curNum-1,endCur-1))
s1.write_formula('I%s' % (curNum), '=B%s/G%s' % (curNum,qPAC))
s1.write_formula('M%s' % (curNum), '=L%s/K%s' % (curNum,evntPAC))

s1.write('B%s' % (endCur), 'Total',bold)
s1.write_formula('D%s' % (endCur), '=SUM(D%s:D%s)' % (curNum-1,endCur-1),bold)
s1.write('E%s' % (endCur), tPACPrime,bold)
s1.write_formula('F%s' % (endCur), 'D%s/3600/E%s' % (endCur,endCur),bold)
s1.write('G%s' % (endCur), '=\'6.2 Gev|%s\'!I%s' % (kin6p2_setting2,end),bold)
s1.write_formula('H%s' % (endCur), '=SUM(H%s:H%s)' % (curNum-1,endCur-1),bold)
s1.write_formula('I%s' % (endCur), '=H%s/G%s' % (endCur,endCur),bold)
s1.write('K%s' % (endCur), evntPAC,bold)
s1.write_formula('L%s' % (endCur), '=SUM(L%s:L%s)' % (curNum-1,endCur-1),bold)
s1.write_formula('M%s' % (endCur), '=L%s/K%s' % (endCur,endCur),bold)
s1.write_formula('N%s' % (endCur), '=M%s/I%s' % (endCur,endCur),bold)

####################################################################################################

################################################################################################################################################################################################################################################################################################

# Add first sheet in spreadsheet
s3 = wb.add_worksheet('8.2 GeV Summary')

# Specify formatting
bold = wb.add_format({'bold': True})

# Set row and column size
s3.set_default_row(30)
s3.set_column(0,14,15)

# Merging first row to fit title
s3.merge_range('A1:M1','8.2 GeV KAON-LT Physics Setting',bold)

# write(column[row],'Name of cell',formatting)
s3.write('A2', 'Setting',bold)
s3.write('B2', 'BCM4A \nCharge (mC)',bold)
s3.write('C2', 't_run (sec)',bold)
s3.write('D2', 't_setting (sec)',bold)
s3.write('E2', 't_PAC \n(hr @ 100% eff)',bold)
s3.write('F2', 't_setting/t_PAC',bold)
s3.write('G2', 'Q_PAC',bold)
s3.write('H2', 'Q_actual (mC)',bold)
s3.write('I2', 'Q_actual/Q_PAC',bold)
s3.write('J2', 'Effective \nEfficiency (J/H)',bold)
# Delta: u'\u0394' (UTF-8)
s3.write('K2', 'K+%s \nrun plan events' % (u'\u0394'),bold)
s3.write('L2', 'K+%s \nactual events' % (u'\u0394'),bold)
s3.write('M2', 'K+%s \nactual/proposed' % (u'\u0394'),bold)
s3.write('N2', 'K+%s \nY_obs/Y_expect' % (u'\u0394'),bold)

# Add first sheet in spreadsheet
s4 = wb.add_worksheet('8.2 Gev|%s' % kin8p2_setting1)

# Set row and column size
s4.set_default_row(30)
s4.set_column(0,14,15)

# Merging first row to fit title
s4.merge_range('A1:M1','8.2 GeV KAON-LT Physics Setting',bold)

s4.write('A2', 'SHMS Angle',bold)
s4.write('B2', 'Run Number',bold)
s4.write('C2', 'BCM4A \nCharge (mC)',bold)
s4.write('D2', 't_run (sec)',bold)
s4.write('E2', 'Current (uA)',bold)
s4.write('F2', 't_setting (sec)',bold)
s4.write('G2', 't_PAC \n(hr @ 100% eff)',bold)
s4.write('H2', 't_setting/t_PAC',bold)
s4.write('I2', 'Q_PAC',bold)
s4.write('J2', 'Q_actual/Q_PAC',bold)
s4.write('K2', 'Effective \nEfficiency (J/H)',bold)

###############################################################################
# 8.2 GeV, Setting 1 ##########################################################
###############################################################################

s3.merge_range('A3:B3','%s' % kin8p2_setting1 ,bold)
s4.merge_range('A3:B3','%s' % kin8p2_setting1 ,bold)

l1 = 0
l2 = 0
curNum = 5
newData = ()

current = kin8p2_center1_Values[0]
tPAC= kin8p2_center1_Values[1]
tPACPrime = kin8p2_center1_Values[2]
qPAC = kin8p2_center1_Values[3]
evnt= kin8p2_center1_Values[4]
evntPAC = kin8p2_center1_Values[5]

s3.write('A4', '%s deg LH2' % kin8p2_center1)
s4.write('A4', '%s deg LH2' % kin8p2_center1)

print("Looking at current %s uA" % (current))
# [RunNum,charge]
newData = (
    [7978, 214.524],
    [7979, 240.132],
    [7980, 214.37],
    [7981, 161.841],
    [7982, 169.908],
    [7983, 187.538],
    [7984, 143.949],
    [7985, 162.07],
    [7986, 163.603],
    [7987, 158.75],
    [7988, 76.21],
    [7989, 135.083],
    [7994, 98.43],
    [7995, 192.309],
    [7996, 60.322],
    [7997, 208.632],
    [7999, 183.021],
    [8000, 233.727],
    [8001, 352.742],
    [8002, 253.60],

)
tmpCurr = [current]
for value in (tmpCurr):
    s4.write('A%s' % (curNum+l2), '@ %suA (mC)' % (value))
    # Starts at 0 for rows and columns
    row = l2+curNum-1
    col = 1
    for runNum, BCM4A in (newData):
        s4.write(row,col, runNum)
        s4.write(row,col+1, BCM4A)
        row += 1
    end = row+1
    # Going back to sheet one so we can 'link' second sheet values
    s4.write('B%s' % (end), 'Total',bold)
    s4.write_formula('C%s' % (end), '=SUM(C%s:C%s)' % (curNum+l2,end-1) ,bold)
    s4.write('E%s' % (end), current,bold)
    s4.write('G%s' % (end), tPAC,bold)
    s4.write_formula('I%s' % (end),'=G%s*3600*0.000070*1000' % (end) ,bold)
    s4.write_formula('J%s' % (end), '=C%s/I%s' % (end,end),bold)
    l2 = end+1
    curNum = 5+l1
    print("%s" % curNum)
    s3.write('A%s' % (curNum), '@ %suA (mC)' % (value))
    s3.write_formula('B%s' % (curNum), '=\'8.2 Gev|%s\'!C%s' % (kin8p2_setting1,end))
    s3.write_formula('C%s' % (curNum), '=\'8.2 Gev|%s\'!D%s' % (kin8p2_setting1,end))
    s3.write_formula('D%s' % (curNum), '=\'8.2 Gev|%s\'!F%s' % (kin8p2_setting1,end))
    s3.write_formula('H%s' % (curNum), '=\'8.2 Gev|%s\'!C%s' % (kin8p2_setting1,end))
    s3.write('L%s' % (curNum), evnt)
    curNum += 1
endCur =  curNum
l1 = endCur+1

s3.write_formula('F%s' % (curNum), '=D%s/3600/E%s' % (curNum-1,endCur-1))
s3.write_formula('I%s' % (curNum), '=B%s/G%s' % (curNum,qPAC))
s3.write_formula('M%s' % (curNum), '=L%s/K%s' % (curNum,evntPAC))

s3.write('B%s' % (endCur), 'Total',bold)
s3.write_formula('D%s' % (endCur), '=SUM(D%s:D%s)' % (curNum-1,endCur-1),bold)
s3.write('E%s' % (endCur), tPACPrime,bold)
s3.write_formula('F%s' % (endCur), 'D%s/3600/E%s' % (endCur,endCur),bold)
s3.write('G%s' % (endCur), '=\'8.2 Gev|%s\'!I%s' % (kin8p2_setting1,end),bold)
s3.write_formula('H%s' % (endCur), '=SUM(H%s:H%s)' % (curNum-1,endCur-1),bold)
s3.write_formula('I%s' % (endCur), '=H%s/G%s' % (endCur,endCur),bold)
s3.write('K%s' % (endCur), evntPAC,bold)
s3.write_formula('L%s' % (endCur), '=SUM(L%s:L%s)' % (curNum-1,endCur-1),bold)
s3.write_formula('M%s' % (endCur), '=L%s/K%s' % (endCur,endCur),bold)
s3.write_formula('N%s' % (endCur), '=M%s/I%s' % (endCur,endCur),bold)

######################################################################################################

curNum =0

current = kin8p2DUM_left1_Values[0]
tPAC= kin8p2DUM_left1_Values[1]
tPACPrime = kin8p2DUM_left1_Values[2]
qPAC = kin8p2DUM_left1_Values[3]
evnt= kin8p2DUM_left1_Values[4]
evntPAC = kin8p2DUM_left1_Values[5]

print("Looking at current %s uA" % (current))
# [RunNum,charge]
newData = (
    [7990, 50.669],
    [7991, 11.696],
    [7992, 52.025],
    [7993, 34.495],
    
)
tmpCurr = [current]
for value in (tmpCurr):
    s4.write('A%s' % (curNum+l2), 'DUMMY (%suA)' % (value))
    # Starts at 0 for rows and columns
    row = l2+curNum-1
    col = 1
    for runNum, BCM4A in (newData):
        s4.write(row,col, runNum)
        s4.write(row,col+1, BCM4A)
        row += 1
    end = row+1
    # Going back to sheet one so we can 'link' second sheet values
    s4.write('B%s' % (end), 'Total',bold)
    s4.write_formula('C%s' % (end), '=SUM(C%s:C%s)' % (curNum+l2,end-1) ,bold)
    s4.write('E%s' % (end), current,bold)
    s4.write('G%s' % (end), tPAC,bold)
    s4.write_formula('I%s' % (end),'=G%s*3600*0.000040*1000' % (end) ,bold)
    s4.write_formula('J%s' % (end), '=C%s/I%s' % (end,end),bold)
    l2 = end+1
    curNum = l1
    print("%s" % curNum)
    s3.write('A%s' % (curNum), 'DUMMY (%suA)' % (value))
    s3.write_formula('B%s' % (curNum), '=\'8.2 Gev|%s\'!C%s' % (kin8p2_setting1,end))
    s3.write_formula('C%s' % (curNum), '=\'8.2 Gev|%s\'!D%s' % (kin8p2_setting1,end))
    s3.write_formula('D%s' % (curNum), '=\'8.2 Gev|%s\'!F%s' % (kin8p2_setting1,end))
    s3.write_formula('H%s' % (curNum), '=\'8.2 Gev|%s\'!C%s' % (kin8p2_setting1,end))
    s3.write('L%s' % (curNum), evnt)
    curNum += 1
endCur =  curNum
l1 = endCur+1

s3.write_formula('F%s' % (curNum), '=D%s/3600/E%s' % (curNum-1,endCur-1))
s3.write_formula('I%s' % (curNum), '=B%s/G%s' % (curNum,qPAC))
s3.write_formula('M%s' % (curNum), '=L%s/K%s' % (curNum,evntPAC))

s3.write('B%s' % (endCur), 'Total',bold)
s3.write_formula('D%s' % (endCur), '=SUM(D%s:D%s)' % (curNum-1,endCur-1),bold)
s3.write('E%s' % (endCur), tPACPrime,bold)
s3.write_formula('F%s' % (endCur), 'D%s/3600/E%s' % (endCur,endCur),bold)
s3.write('G%s' % (endCur), '=\'8.2 Gev|%s\'!I%s' % (kin8p2_setting1,end),bold)
s3.write_formula('H%s' % (endCur), '=SUM(H%s:H%s)' % (curNum-1,endCur-1),bold)
s3.write_formula('I%s' % (endCur), '=H%s/G%s' % (endCur,endCur),bold)
s3.write('K%s' % (endCur), evntPAC,bold)
s3.write_formula('L%s' % (endCur), '=SUM(L%s:L%s)' % (curNum-1,endCur-1),bold)
s3.write_formula('M%s' % (endCur), '=L%s/K%s' % (endCur,endCur),bold)
s3.write_formula('N%s' % (endCur), '=M%s/I%s' % (endCur,endCur),bold)

####################################################################################################
# Next angle #############
##########################

curNum =1
current = kin8p2_left1_Values[0]
tPAC= kin8p2_left1_Values[1]
tPACPrime = kin8p2_left1_Values[2]
qPAC = kin8p2_left1_Values[3]
evnt= kin8p2_left1_Values[4]
evntPAC = kin8p2_left1_Values[5]

s3.write('A%s' % (l1), '%s deg LH2' % kin8p2_left1)
s4.write('A%s' % (l2), '%s deg LH2' % kin8p2_left1)


print("Looking at current %s uA" % (current))
# [RunNum,charge]
newData = (
    [8003, 180.185],
    [8004, 159.999],
    [8005, 235.155],
    [8006, 228.774],
    [8007, 218.061],
    [8008, 225.288],
    [8009, 228.907],
    [8010, 243.926],
    [8011, 217.279],
    [8012, 220.949],
    [8013, 241.701],
    [8014, 193.19],
    [8015, 193.07],
    [8016, 172.213],
    [8018, 111.1],
    [8020, 223.047],
    [8021, 176.946],
    [8022, 235.45],
    [8023, 235.158],
    [8024, 233.889],
    [8025, 218.253],
    [8026, 79.13],
    [8027, 157.283],
    [8028, 211.372],
    [8029, 240.039],
    [8030, 235.859],
    [8031, 187.966],
    [8032, 210.45],
    [8033, 219.095],
    [8034, 231.974],
    [8035, 189.29],
    [8036, 215.511],
    [8037, 140.592],
    
)
tmpCurr = [current]
for value in (tmpCurr):
    s4.write('A%s' % (curNum+l2), '@ %suA (mC)' % (value))
    # Starts at 0 for rows and columns
    row = l2+curNum-1
    col = 1
    for runNum, BCM4A in (newData):
        s4.write(row,col, runNum)
        s4.write(row,col+1, BCM4A)
        row += 1
    end = row+1
    # Going back to sheet one so we can 'link' second sheet values
    s4.write('B%s' % (end), 'Total',bold)
    s4.write_formula('C%s' % (end), '=SUM(C%s:C%s)' % (curNum+l2,end-1) ,bold)
    s4.write('E%s' % (end), current,bold)
    s4.write('G%s' % (end), tPAC,bold)
    s4.write_formula('I%s' % (end),'=G%s*3600*0.000070*1000' % (end) ,bold)
    s4.write_formula('J%s' % (end), '=C%s/I%s' % (end,end),bold)
    l2 = end+1
    curNum = 1+l1
    print("%s" % curNum)
    s3.write('A%s' % (curNum), '@ %suA (mC)' % (value))
    s3.write_formula('B%s' % (curNum), '=\'8.2 Gev|%s\'!C%s' % (kin8p2_setting1,end))
    s3.write_formula('C%s' % (curNum), '=\'8.2 Gev|%s\'!D%s' % (kin8p2_setting1,end))
    s3.write_formula('D%s' % (curNum), '=\'8.2 Gev|%s\'!F%s' % (kin8p2_setting1,end))
    # s3.write_formula('F%s' % (curNum), '=D%s/3600/E%s' % (curNum,curNum+1)) Need work
    s3.write_formula('H%s' % (curNum), '=\'8.2 Gev|%s\'!C%s' % (kin8p2_setting1,end))
    # s3.write_formula('I%s' % (curNum), '=B%s/G%s' % (curNum,curNum+1))
    s3.write('L%s' % (curNum), evnt)
    # s3.write_formula('M%s' % (curNum), '=L%s/K%s' % (curNum,curNum+1))
    curNum += 1
endCur =  curNum
l1 = endCur+1
s3.write('B%s' % (endCur), 'Total',bold)
s3.write_formula('D%s' % (endCur), '=SUM(D%s:D%s)' % (curNum-1,endCur-1),bold)
s3.write('E%s' % (endCur), tPACPrime,bold)
s3.write_formula('F%s' % (endCur), 'D%s/3600/E%s' % (endCur,endCur),bold)
s3.write('G%s' % (endCur), '=\'8.2 Gev|%s\'!I%s' % (kin8p2_setting1,end),bold)
s3.write_formula('H%s' % (endCur), '=SUM(H%s:H%s)' % (curNum-1,endCur-1),bold)
s3.write_formula('I%s' % (endCur), '=H%s/G%s' % (endCur,endCur),bold)
s3.write('K%s' % (endCur), evntPAC,bold)
s3.write_formula('L%s' % (endCur), '=SUM(L%s:L%s)' % (curNum-1,endCur-1),bold)
s3.write_formula('M%s' % (endCur), '=L%s/K%s' % (endCur,endCur),bold)
s3.write_formula('N%s' % (endCur), '=M%s/I%s' % (endCur,endCur),bold)

######################################################################################################

curNum =0

current = kin8p2DUM_center1_Values[0]
tPAC= kin8p2DUM_center1_Values[1]
tPACPrime = kin8p2DUM_center1_Values[2]
qPAC = kin8p2DUM_center1_Values[3]
evnt= kin8p2DUM_center1_Values[4]
evntPAC = kin8p2DUM_center1_Values[5]

print("Looking at current %s uA" % (current))
# [RunNum,charge]
newData = (
    [8017, 136.855],
    
)
tmpCurr = [current]
for value in (tmpCurr):
    s4.write('A%s' % (curNum+l2), 'DUMMY (%suA)' % (value))
    # Starts at 0 for rows and columns
    row = l2+curNum-1
    col = 1
    for runNum, BCM4A in (newData):
        s4.write(row,col, runNum)
        s4.write(row,col+1, BCM4A)
        row += 1
    end = row+1
    # Going back to sheet one so we can 'link' second sheet values
    s4.write('B%s' % (end), 'Total',bold)
    s4.write_formula('C%s' % (end), '=SUM(C%s:C%s)' % (curNum+l2,end-1) ,bold)
    s4.write('E%s' % (end), current,bold)
    s4.write('G%s' % (end), tPAC,bold)
    s4.write_formula('I%s' % (end),'=G%s*3600*0.000040*1000' % (end) ,bold)
    s4.write_formula('J%s' % (end), '=C%s/I%s' % (end,end),bold)
    l2 = end+1
    curNum = l1
    print("%s" % curNum)
    s3.write('A%s' % (curNum), 'DUMMY (%suA)' % (value))
    s3.write_formula('B%s' % (curNum), '=\'8.2 Gev|%s\'!C%s' % (kin8p2_setting1,end))
    s3.write_formula('C%s' % (curNum), '=\'8.2 Gev|%s\'!D%s' % (kin8p2_setting1,end))
    s3.write_formula('D%s' % (curNum), '=\'8.2 Gev|%s\'!F%s' % (kin8p2_setting1,end))
    s3.write_formula('H%s' % (curNum), '=\'8.2 Gev|%s\'!C%s' % (kin8p2_setting1,end))
    s3.write('L%s' % (curNum), evnt)
    curNum += 1
endCur =  curNum
l1 = endCur+1

s3.write_formula('F%s' % (curNum), '=D%s/3600/E%s' % (curNum-1,endCur-1))
s3.write_formula('I%s' % (curNum), '=B%s/G%s' % (curNum,qPAC))
s3.write_formula('M%s' % (curNum), '=L%s/K%s' % (curNum,evntPAC))

s3.write('B%s' % (endCur), 'Total',bold)
s3.write_formula('D%s' % (endCur), '=SUM(D%s:D%s)' % (curNum-1,endCur-1),bold)
s3.write('E%s' % (endCur), tPACPrime,bold)
s3.write_formula('F%s' % (endCur), 'D%s/3600/E%s' % (endCur,endCur),bold)
s3.write('G%s' % (endCur), '=\'8.2 Gev|%s\'!I%s' % (kin8p2_setting1,end),bold)
s3.write_formula('H%s' % (endCur), '=SUM(H%s:H%s)' % (curNum-1,endCur-1),bold)
s3.write_formula('I%s' % (endCur), '=H%s/G%s' % (endCur,endCur),bold)
s3.write('K%s' % (endCur), evntPAC,bold)
s3.write_formula('L%s' % (endCur), '=SUM(L%s:L%s)' % (curNum-1,endCur-1),bold)
s3.write_formula('M%s' % (endCur), '=L%s/K%s' % (endCur,endCur),bold)
s3.write_formula('N%s' % (endCur), '=M%s/I%s' % (endCur,endCur),bold)

####################################################################################################

###############################################################################
# 8.2 GeV, Setting 2 ##########################################################
###############################################################################

s4a = wb.add_worksheet('8.2 Gev|%s' % kin8p2_setting2)

# Set row and column size
s4a.set_default_row(30)
s4a.set_column(0,14,15)

# Merging first row to fit title
s4a.merge_range('A1:M1','8.2 GeV KAON-LT Physics Setting',bold)

s4a.write('A2', 'SHMS Angle',bold)
s4a.write('B2', 'Run Number',bold)
s4a.write('C2', 'BCM4A \nCharge (mC)',bold)
s4a.write('D2', 't_run (sec)',bold)
s4a.write('E2', 'Current (uA)',bold)
s4a.write('F2', 't_setting (sec)',bold)
s4a.write('G2', 't_PAC \n(hr @ 100% eff)',bold)
s4a.write('H2', 't_setting/t_PAC',bold)
s4a.write('I2', 'Q_PAC',bold)
s4a.write('J2', 'Q_actual/Q_PAC',bold)
s4a.write('K2', 'Effective \nEfficiency (J/H)',bold)

l2=3

s3.merge_range('A%s:B%s' % (l1,l1),'%s' % kin8p2_setting2 ,bold)
s4a.merge_range('A%s:B%s' % (l2,l2),'%s' % kin8p2_setting2 ,bold)

curNum = 2
newData = ()

current = kin8p2_center2_Values[0]
tPAC= kin8p2_center2_Values[1]
tPACPrime = kin8p2_center2_Values[2]
qPAC = kin8p2_center2_Values[3]
evnt= kin8p2_center2_Values[4]
evntPAC = kin8p2_center2_Values[5]

s3.write('A%s' % (l1+1), '%s deg LH2' % kin8p2_center2)
s4a.write('A%s' % (l2+1), '%s deg LH2' % kin8p2_center2)

print("Looking at current %s uA" % (current))
# [RunNum,charge]
newData = (
    [8039, 155.804],
    [8040, 191.976],
    [8041, 202.001],
    [8042, 96.63],
    [8044, 194.738],
    [8045, 223.798],
    [8046, 214.824],
    [8047, 194.687],
    [8048, 94.077],
    [8050, 175.587],
    [8051, 199.966],
    [8052, 146.862],
    [8053, 125.793],
    [8055, 113.889],
    [8056, 126.542],
    [8057, 125.178],
    [8058, 129.321],
    [8059, 130.933],
    [8060, 140.512],
    [8061, 138.577],
    [8063, 85.809],
    [8064, 147.373],
    [8065, 59.271],
    [8067, 180.147],
    [8068, 177.385],
    [8069, 83.98],
    [8070, 94.503],
    [8071, 284.747],
    [8073, 58.465],
    [8074, 99.723],
    [8075, 147.195],
    [8076, 170.587],
    [8077, 80.611],
    [8078, 149.917],
    [8079, 154.711],
    [8080, 220.534],
    [8081, 254.68],
    [8082, 206.891],
    [8083, 191.653],
    [8084, 177.094],
    [8088, 137.815],
    [8089, 113.382],
    [8090, 211.722],
    [8091, 222.139],
    [8092, 158.727],
    [8093, 168.769],
    [8094, 220.165],
    [8095, 193.911],
    [8096, 222.749],
    [8097, 210.592],
    [8098, 202.41],
    [8099, 188.346],
    [8101, 214.803],
    [8100, 200.664],
    [8102, 218.965],
    [8103, 154.992],
    [8104, 164.39],
    [8105, 131.937],
    [8106, 139.146],
    [8107, 189.923],
    [8108, 170.793],
    [8109, 167.665],
    [8110, 78.048],
    
)
tmpCurr = [current]
for value in (tmpCurr):
    s4a.write('A%s' % (curNum+l2), '@ %suA (mC)' % (value))
    # Starts at 0 for rows and columns
    row = l2+curNum-1
    col = 1
    for runNum, BCM4A in (newData):
        s4a.write(row,col, runNum)
        s4a.write(row,col+1, BCM4A)
        row += 1
    end = row+1
    # Going back to sheet one so we can 'link' second sheet values
    s4a.write('B%s' % (end), 'Total',bold)
    s4a.write_formula('C%s' % (end), '=SUM(C%s:C%s)' % (curNum+l2,end-1) ,bold)
    s4a.write('E%s' % (end), current,bold)
    s4a.write('G%s' % (end), tPAC,bold)
    s4a.write_formula('I%s' % (end),'=G%s*3600*0.000070*1000' % (end) ,bold)
    s4a.write_formula('J%s' % (end), '=C%s/I%s' % (end,end),bold)
    l2 = end+1
    curNum = 2+l1
    print("%s" % curNum)
    s3.write('A%s' % (curNum), '@ %suA (mC)' % (value))
    s3.write_formula('B%s' % (curNum), '=\'8.2 Gev|%s\'!C%s' % (kin8p2_setting2,end))
    s3.write_formula('C%s' % (curNum), '=\'8.2 Gev|%s\'!D%s' % (kin8p2_setting2,end))
    s3.write_formula('D%s' % (curNum), '=\'8.2 Gev|%s\'!F%s' % (kin8p2_setting2,end))
    s3.write_formula('H%s' % (curNum), '=\'8.2 Gev|%s\'!C%s' % (kin8p2_setting2,end))
    s3.write('L%s' % (curNum), evnt)
    curNum += 1
endCur =  curNum
l1 = endCur+1

s3.write_formula('F%s' % (curNum), '=D%s/3600/E%s' % (curNum-1,endCur-1))
s3.write_formula('I%s' % (curNum), '=B%s/G%s' % (curNum,qPAC))
s3.write_formula('M%s' % (curNum), '=L%s/K%s' % (curNum,evntPAC))

s3.write('B%s' % (endCur), 'Total',bold)
s3.write_formula('D%s' % (endCur), '=SUM(D%s:D%s)' % (curNum-1,endCur-1),bold)
s3.write('E%s' % (endCur), tPACPrime,bold)
s3.write_formula('F%s' % (endCur), 'D%s/3600/E%s' % (endCur,endCur),bold)
s3.write('G%s' % (endCur), '=\'8.2 Gev|%s\'!I%s' % (kin8p2_setting2,end),bold)
s3.write_formula('H%s' % (endCur), '=SUM(H%s:H%s)' % (curNum-1,endCur-1),bold)
s3.write_formula('I%s' % (endCur), '=H%s/G%s' % (endCur,endCur),bold)
s3.write('K%s' % (endCur), evntPAC,bold)
s3.write_formula('L%s' % (endCur), '=SUM(L%s:L%s)' % (curNum-1,endCur-1),bold)
s3.write_formula('M%s' % (endCur), '=L%s/K%s' % (endCur,endCur),bold)
s3.write_formula('N%s' % (endCur), '=M%s/I%s' % (endCur,endCur),bold)

######################################################################################################

curNum =0

current = kin8p2DUM_left1_Values[0]
tPAC= kin8p2DUM_left1_Values[1]
tPACPrime = kin8p2DUM_left1_Values[2]
qPAC = kin8p2DUM_left1_Values[3]
evnt= kin8p2DUM_left1_Values[4]
evntPAC = kin8p2DUM_left1_Values[5]

print("Looking at current %s uA" % (current))
# [RunNum,charge]
newData = (
    [8085, 134.753],
    [8086, 123.302],
    [8087, 180.56],
    
)
tmpCurr = [current]
for value in (tmpCurr):
    s4a.write('A%s' % (curNum+l2), 'DUMMY (%suA)' % (value))
    # Starts at 0 for rows and columns
    row = l2+curNum-1
    col = 1
    for runNum, BCM4A in (newData):
        s4a.write(row,col, runNum)
        s4a.write(row,col+1, BCM4A)
        row += 1
    end = row+1
    # Going back to sheet one so we can 'link' second sheet values
    s4a.write('B%s' % (end), 'Total',bold)
    s4a.write_formula('C%s' % (end), '=SUM(C%s:C%s)' % (curNum+l2,end-1) ,bold)
    s4a.write('E%s' % (end), current,bold)
    s4a.write('G%s' % (end), tPAC,bold)
    s4a.write_formula('I%s' % (end),'=G%s*3600*0.000040*1000' % (end) ,bold)
    s4a.write_formula('J%s' % (end), '=C%s/I%s' % (end,end),bold)
    l2 = end+1
    curNum = l1
    print("%s" % curNum)
    s3.write('A%s' % (curNum), 'DUMMY (%suA)' % (value))
    s3.write_formula('B%s' % (curNum), '=\'8.2 Gev|%s\'!C%s' % (kin8p2_setting2,end))
    s3.write_formula('C%s' % (curNum), '=\'8.2 Gev|%s\'!D%s' % (kin8p2_setting2,end))
    s3.write_formula('D%s' % (curNum), '=\'8.2 Gev|%s\'!F%s' % (kin8p2_setting2,end))
    s3.write_formula('H%s' % (curNum), '=\'8.2 Gev|%s\'!C%s' % (kin8p2_setting2,end))
    s3.write('L%s' % (curNum), evnt)
    curNum += 1
endCur =  curNum
l1 = endCur+1

s3.write_formula('F%s' % (curNum), '=D%s/3600/E%s' % (curNum-1,endCur-1))
s3.write_formula('I%s' % (curNum), '=B%s/G%s' % (curNum,qPAC))
s3.write_formula('M%s' % (curNum), '=L%s/K%s' % (curNum,evntPAC))

s3.write('B%s' % (endCur), 'Total',bold)
s3.write_formula('D%s' % (endCur), '=SUM(D%s:D%s)' % (curNum-1,endCur-1),bold)
s3.write('E%s' % (endCur), tPACPrime,bold)
s3.write_formula('F%s' % (endCur), 'D%s/3600/E%s' % (endCur,endCur),bold)
s3.write('G%s' % (endCur), '=\'8.2 Gev|%s\'!I%s' % (kin8p2_setting2,end),bold)
s3.write_formula('H%s' % (endCur), '=SUM(H%s:H%s)' % (curNum-1,endCur-1),bold)
s3.write_formula('I%s' % (endCur), '=H%s/G%s' % (endCur,endCur),bold)
s3.write('K%s' % (endCur), evntPAC,bold)
s3.write_formula('L%s' % (endCur), '=SUM(L%s:L%s)' % (curNum-1,endCur-1),bold)
s3.write_formula('M%s' % (endCur), '=L%s/K%s' % (endCur,endCur),bold)
s3.write_formula('N%s' % (endCur), '=M%s/I%s' % (endCur,endCur),bold)

####################################################################################################
# Next angle #############
##########################

curNum =1
current = kin8p2_left2_Values[0]
tPAC= kin8p2_left2_Values[1]
tPACPrime = kin8p2_left2_Values[2]
qPAC = kin8p2_left2_Values[3]
evnt= kin8p2_left2_Values[4]
evntPAC = kin8p2_left2_Values[5]

s3.write('A%s' % (l1), '%s deg LH2' % kin8p2_left2)
s4a.write('A%s' % (l2), '%s deg LH2' % kin8p2_left2)


print("Looking at current %s uA" % (current))
# [RunNum,charge]
newData = (
    [8111, 57.184],
    [8112, 239.403],
    [8113, 200.727],
    [8116, 123.848],
    [8117, 236.933],
    [8117, 236.933],
    [8118, 221.954],
    [8119, 250.694],
    [8120, 102.964],
    [8121, 211.515],
    [8122, 199.208],
    [8123, 239.905],
    [8124, 61.443],
    [8123, 239.905],
    [8125, 217.712],
    [8126, 206.077],
    [8127, 242.506],
    [8128, 210.99],
    [8129, 216.664],
    [8135, 159.917],
    [8136, 213.122],
    [8137, 261.28],
    [8138, 249.514],
    [8140, 214.463],
    [8141, 0.124],
    [8142, 197.087],
    [8143, 227.237],
    [8144, 222.642],
    [8145, 234.368],
    [8146, 179.844],
    [8147, 46.432],
    [8148, 225.214],
    [8149, 200.469],
    [8150, 229.707],
    [8152, 231.469],
    [8153, 268.191],
    [8154, 39.697],
    [8156, 230.832],
    [8157, 105.103],
    [8158, 202.273],
    [8159, 201.394],
    [8160, 202.934],
    [8165, 191.372],
    [8166, 245.014],
    [8167, 253.833],
    [8168, 228.823],
    [8169, 242.773],
    [8170, 251.596],
    [8171, 213.688],
    [8172, 213.264],
    [8173, 234.223],
    [8174, 243.526],
    [8175, 220.115],
    [8176, 238.045],
    [8177, 222.797],
    [8178, 241.381],
    [8179, 182.724],
    [8180, 233.195],
    [8181, 34.058],
    [8182, 251.456],
    [8183, 191.398],
    [8184, 189.827],
    [8185, 57.218],
    
)
tmpCurr = [current]
for value in (tmpCurr):
    s4a.write('A%s' % (curNum+l2), '@ %suA (mC)' % (value))
    # Starts at 0 for rows and columns
    row = l2+curNum-1
    col = 1
    for runNum, BCM4A in (newData):
        s4a.write(row,col, runNum)
        s4a.write(row,col+1, BCM4A)
        row += 1
    end = row+1
    # Going back to sheet one so we can 'link' second sheet values
    s4a.write('B%s' % (end), 'Total',bold)
    s4a.write_formula('C%s' % (end), '=SUM(C%s:C%s)' % (curNum+l2,end-1) ,bold)
    s4a.write('E%s' % (end), current,bold)
    s4a.write('G%s' % (end), tPAC,bold)
    s4a.write_formula('I%s' % (end),'=G%s*3600*0.000070*1000' % (end) ,bold)
    s4a.write_formula('J%s' % (end), '=C%s/I%s' % (end,end),bold)
    l2 = end+1
    curNum = 1+l1
    print("%s" % curNum)
    s3.write('A%s' % (curNum), '@ %suA (mC)' % (value))
    s3.write_formula('B%s' % (curNum), '=\'8.2 Gev|%s\'!C%s' % (kin8p2_setting2,end))
    s3.write_formula('C%s' % (curNum), '=\'8.2 Gev|%s\'!D%s' % (kin8p2_setting2,end))
    s3.write_formula('D%s' % (curNum), '=\'8.2 Gev|%s\'!F%s' % (kin8p2_setting2,end))
    # s3.write_formula('F%s' % (curNum), '=D%s/3600/E%s' % (curNum,curNum+1)) Need work
    s3.write_formula('H%s' % (curNum), '=\'8.2 Gev|%s\'!C%s' % (kin8p2_setting2,end))
    # s3.write_formula('I%s' % (curNum), '=B%s/G%s' % (curNum,curNum+1))
    s3.write('L%s' % (curNum), evnt)
    # s3.write_formula('M%s' % (curNum), '=L%s/K%s' % (curNum,curNum+1))
    curNum += 1
endCur =  curNum
l1 = endCur+1
s3.write('B%s' % (endCur), 'Total',bold)
s3.write_formula('D%s' % (endCur), '=SUM(D%s:D%s)' % (curNum-1,endCur-1),bold)
s3.write('E%s' % (endCur), tPACPrime,bold)
s3.write_formula('F%s' % (endCur), 'D%s/3600/E%s' % (endCur,endCur),bold)
s3.write('G%s' % (endCur), '=\'8.2 Gev|%s\'!I%s' % (kin8p2_setting2,end),bold)
s3.write_formula('H%s' % (endCur), '=SUM(H%s:H%s)' % (curNum-1,endCur-1),bold)
s3.write_formula('I%s' % (endCur), '=H%s/G%s' % (endCur,endCur),bold)
s3.write('K%s' % (endCur), evntPAC,bold)
s3.write_formula('L%s' % (endCur), '=SUM(L%s:L%s)' % (curNum-1,endCur-1),bold)
s3.write_formula('M%s' % (endCur), '=L%s/K%s' % (endCur,endCur),bold)
s3.write_formula('N%s' % (endCur), '=M%s/I%s' % (endCur,endCur),bold)

######################################################################################################

curNum =0

current = kin8p2DUM_center1_Values[0]
tPAC= kin8p2DUM_center1_Values[1]
tPACPrime = kin8p2DUM_center1_Values[2]
qPAC = kin8p2DUM_center1_Values[3]
evnt= kin8p2DUM_center1_Values[4]
evntPAC = kin8p2DUM_center1_Values[5]

print("Looking at current %s uA" % (current))
# [RunNum,charge]
newData = (
    [8161, 6.207],
    [8162, 157.241],
    [8163, 146.309],
    [8164, 126.29],

)
tmpCurr = [current]
for value in (tmpCurr):
    s4a.write('A%s' % (curNum+l2), 'DUMMY (%suA)' % (value))
    # Starts at 0 for rows and columns
    row = l2+curNum-1
    col = 1
    for runNum, BCM4A in (newData):
        s4a.write(row,col, runNum)
        s4a.write(row,col+1, BCM4A)
        row += 1
    end = row+1
    # Going back to sheet one so we can 'link' second sheet values
    s4a.write('B%s' % (end), 'Total',bold)
    s4a.write_formula('C%s' % (end), '=SUM(C%s:C%s)' % (curNum+l2,end-1) ,bold)
    s4a.write('E%s' % (end), current,bold)
    s4a.write('G%s' % (end), tPAC,bold)
    s4a.write_formula('I%s' % (end),'=G%s*3600*0.000040*1000' % (end) ,bold)
    s4a.write_formula('J%s' % (end), '=C%s/I%s' % (end,end),bold)
    l2 = end+1
    curNum = l1
    print("%s" % curNum)
    s3.write('A%s' % (curNum), 'DUMMY (%suA)' % (value))
    s3.write_formula('B%s' % (curNum), '=\'8.2 Gev|%s\'!C%s' % (kin8p2_setting2,end))
    s3.write_formula('C%s' % (curNum), '=\'8.2 Gev|%s\'!D%s' % (kin8p2_setting2,end))
    s3.write_formula('D%s' % (curNum), '=\'8.2 Gev|%s\'!F%s' % (kin8p2_setting2,end))
    s3.write_formula('H%s' % (curNum), '=\'8.2 Gev|%s\'!C%s' % (kin8p2_setting2,end))
    s3.write('L%s' % (curNum), evnt)
    curNum += 1
endCur =  curNum
l1 = endCur+1

s3.write_formula('F%s' % (curNum), '=D%s/3600/E%s' % (curNum-1,endCur-1))
s3.write_formula('I%s' % (curNum), '=B%s/G%s' % (curNum,qPAC))
s3.write_formula('M%s' % (curNum), '=L%s/K%s' % (curNum,evntPAC))

s3.write('B%s' % (endCur), 'Total',bold)
s3.write_formula('D%s' % (endCur), '=SUM(D%s:D%s)' % (curNum-1,endCur-1),bold)
s3.write('E%s' % (endCur), tPACPrime,bold)
s3.write_formula('F%s' % (endCur), 'D%s/3600/E%s' % (endCur,endCur),bold)
s3.write('G%s' % (endCur), '=\'8.2 Gev|%s\'!I%s' % (kin8p2_setting2,end),bold)
s3.write_formula('H%s' % (endCur), '=SUM(H%s:H%s)' % (curNum-1,endCur-1),bold)
s3.write_formula('I%s' % (endCur), '=H%s/G%s' % (endCur,endCur),bold)
s3.write('K%s' % (endCur), evntPAC,bold)
s3.write_formula('L%s' % (endCur), '=SUM(L%s:L%s)' % (curNum-1,endCur-1),bold)
s3.write_formula('M%s' % (endCur), '=L%s/K%s' % (endCur,endCur),bold)
s3.write_formula('N%s' % (endCur), '=M%s/I%s' % (endCur,endCur),bold)

####################################################################################################

###############################################################################
# 8.2 GeV, Setting 3 ##########################################################
###############################################################################

s4b = wb.add_worksheet('8.2 Gev|%s' % kin8p2_setting3)

# Set row and column size
s4b.set_default_row(30)
s4b.set_column(0,14,15)

# Merging first row to fit title
s4b.merge_range('A1:M1','8.2 GeV KAON-LT Physics Setting',bold)

s4b.write('A2', 'SHMS Angle',bold)
s4b.write('B2', 'Run Number',bold)
s4b.write('C2', 'BCM4A \nCharge (mC)',bold)
s4b.write('D2', 't_run (sec)',bold)
s4b.write('E2', 'Current (uA)',bold)
s4b.write('F2', 't_setting (sec)',bold)
s4b.write('G2', 't_PAC \n(hr @ 100% eff)',bold)
s4b.write('H2', 't_setting/t_PAC',bold)
s4b.write('I2', 'Q_PAC',bold)
s4b.write('J2', 'Q_actual/Q_PAC',bold)
s4b.write('K2', 'Effective \nEfficiency (J/H)',bold)

l2=3

s3.merge_range('A%s:B%s' % (l1,l1),'%s' % kin8p2_setting3 ,bold)
s4b.merge_range('A%s:B%s' % (l2,l2),'%s' % kin8p2_setting3 ,bold)

curNum = 2
newData = ()

current = kin8p2_center3_Values[0]
tPAC= kin8p2_center3_Values[1]
tPACPrime = kin8p2_center3_Values[2]
qPAC = kin8p2_center3_Values[3]
evnt= kin8p2_center3_Values[4]
evntPAC = kin8p2_center3_Values[5]

s3.write('A%s' % (l1+1), '%s deg LH2' % kin8p2_center3)
s4b.write('A%s' % (l2+1), '%s deg LH2' % kin8p2_center3)

print("Looking at current %s uA" % (current))
# [RunNum,charge]
newData = (
    [8252, 174.921],
    [8253, 158.495],
    [8254, 186.138],
    [8255, 162.428],
    [8256, 168.357],
    [8267, 150.633],
    [8268, 169.596],
    [8269, 142.786],
    [8270, 183.734],
    [8271, 178.488],
    [8272, 178.246],
    [8273, 158.595],
    [8274, 187.363],
    [8275, 154.267],
    [8276, 146.109],
    [8277, 150.714],
    [8278, 180.497],
    [8279, 148.192],
    [8280, 158.683],
    [8281, 158.826],
    [8282, 120.795],
    [8284, 88.626],
    [8285, 54.976],
    [8286, 175.963],
    [8287, 131.325],
    [8288, 143.752],
    [8289, 144.387],
    [8290, 160.042],
    [8291, 137.271],
    [8292, 130.46],
    [8293, 133.334],
    [8294, 167.13],
    [8295, 148.41],
    [8296, 152.111],
    [8297, 120.725],
    [8298, 94.02],
    [8304, 122.112],
    [8305, 180.192],
    [8306, 184.324],
    [8307, 178.28],
    [8308, 79.788],
    [8309, 139.631],
    [8310, 157.7],
    [8311, 136.314],
    [8312, 169.287],
    [8313, 148.87],
    [8318, 150.27],
    [8319, 137.01],
    [8320, 178.435],
    [8321, 174.838],
    [8322, 158.808],
    [8323, 130.801],
    [8324, 178.05],
    [8325, 189.774],
    [8326, 143.812],
    [8327, 169.827],
    [8328, 161.832],
    [8329, 168.672],
    [8330, 158.787],
    [8331, 171.727],
    [8332, 166.483],
    [8333, 156.04],
    [8334, 6.5],
    [8335, 160.933],
    [8336, 154.868],
    [8337, 161.88],
    [8338, 123.14],
    [8339, 113.895],
    [8340, 158.57],
    [8341, 153.428],
    [8342, 170.942],
    [8343, 149.72],
    [8344, 63.634],
    [8345, 166.929],
    [8346, 150.131],
    [8347, 134.198],
    [8348, 174.784],
    [8349, 139.499],
    [8350, 180.568],
    [8351, 162.813],
    [8352, 194.949],
    [8353, 102.648],
    [8354, 47.947],
    [8356, 76.733],

)
tmpCurr = [current]
for value in (tmpCurr):
    s4b.write('A%s' % (curNum+l2), '@ %suA (mC)' % (value))
    # Starts at 0 for rows and columns
    row = l2+curNum-1
    col = 1
    for runNum, BCM4A in (newData):
        s4b.write(row,col, runNum)
        s4b.write(row,col+1, BCM4A)
        row += 1
    end = row+1
    # Going back to sheet one so we can 'link' second sheet values
    s4b.write('B%s' % (end), 'Total',bold)
    s4b.write_formula('C%s' % (end), '=SUM(C%s:C%s)' % (curNum+l2,end-1) ,bold)
    s4b.write('E%s' % (end), current,bold)
    s4b.write('G%s' % (end), tPAC,bold)
    s4b.write_formula('I%s' % (end),'=G%s*3600*0.000070*1000' % (end) ,bold)
    s4b.write_formula('J%s' % (end), '=C%s/I%s' % (end,end),bold)
    l2 = end+1
    curNum = 2+l1
    print("%s" % curNum)
    s3.write('A%s' % (curNum), '@ %suA (mC)' % (value))
    s3.write_formula('B%s' % (curNum), '=\'8.2 Gev|%s\'!C%s' % (kin8p2_setting3,end))
    s3.write_formula('C%s' % (curNum), '=\'8.2 Gev|%s\'!D%s' % (kin8p2_setting3,end))
    s3.write_formula('D%s' % (curNum), '=\'8.2 Gev|%s\'!F%s' % (kin8p2_setting3,end))
    s3.write_formula('H%s' % (curNum), '=\'8.2 Gev|%s\'!C%s' % (kin8p2_setting3,end))
    s3.write('L%s' % (curNum), evnt)
    curNum += 1
endCur =  curNum
l1 = endCur+1

s3.write_formula('F%s' % (curNum), '=D%s/3600/E%s' % (curNum-1,endCur-1))
s3.write_formula('I%s' % (curNum), '=B%s/G%s' % (curNum,qPAC))
s3.write_formula('M%s' % (curNum), '=L%s/K%s' % (curNum,evntPAC))

s3.write('B%s' % (endCur), 'Total',bold)
s3.write_formula('D%s' % (endCur), '=SUM(D%s:D%s)' % (curNum-1,endCur-1),bold)
s3.write('E%s' % (endCur), tPACPrime,bold)
s3.write_formula('F%s' % (endCur), 'D%s/3600/E%s' % (endCur,endCur),bold)
s3.write('G%s' % (endCur), '=\'8.2 Gev|%s\'!I%s' % (kin8p2_setting3,end),bold)
s3.write_formula('H%s' % (endCur), '=SUM(H%s:H%s)' % (curNum-1,endCur-1),bold)
s3.write_formula('I%s' % (endCur), '=H%s/G%s' % (endCur,endCur),bold)
s3.write('K%s' % (endCur), evntPAC,bold)
s3.write_formula('L%s' % (endCur), '=SUM(L%s:L%s)' % (curNum-1,endCur-1),bold)
s3.write_formula('M%s' % (endCur), '=L%s/K%s' % (endCur,endCur),bold)
s3.write_formula('N%s' % (endCur), '=M%s/I%s' % (endCur,endCur),bold)

######################################################################################################

curNum =0

current = kin8p2DUM_left1_Values[0]
tPAC= kin8p2DUM_left1_Values[1]
tPACPrime = kin8p2DUM_left1_Values[2]
qPAC = kin8p2DUM_left1_Values[3]
evnt= kin8p2DUM_left1_Values[4]
evntPAC = kin8p2DUM_left1_Values[5]

print("Looking at current %s uA" % (current))
# [RunNum,charge]
newData = (
    [8314, 73.553],
    [8315, 125.951],
    [8316, 135.039],
    [8317, 137.554],

)
tmpCurr = [current]
for value in (tmpCurr):
    s4b.write('A%s' % (curNum+l2), 'DUMMY (%suA)' % (value))
    # Starts at 0 for rows and columns
    row = l2+curNum-1
    col = 1
    for runNum, BCM4A in (newData):
        s4b.write(row,col, runNum)
        s4b.write(row,col+1, BCM4A)
        row += 1
    end = row+1
    # Going back to sheet one so we can 'link' second sheet values
    s4b.write('B%s' % (end), 'Total',bold)
    s4b.write_formula('C%s' % (end), '=SUM(C%s:C%s)' % (curNum+l2,end-1) ,bold)
    s4b.write('E%s' % (end), current,bold)
    s4b.write('G%s' % (end), tPAC,bold)
    s4b.write_formula('I%s' % (end),'=G%s*3600*0.000040*1000' % (end) ,bold)
    s4b.write_formula('J%s' % (end), '=C%s/I%s' % (end,end),bold)
    l2 = end+1
    curNum = l1
    print("%s" % curNum)
    s3.write('A%s' % (curNum), 'DUMMY (%suA)' % (value))
    s3.write_formula('B%s' % (curNum), '=\'8.2 Gev|%s\'!C%s' % (kin8p2_setting3,end))
    s3.write_formula('C%s' % (curNum), '=\'8.2 Gev|%s\'!D%s' % (kin8p2_setting3,end))
    s3.write_formula('D%s' % (curNum), '=\'8.2 Gev|%s\'!F%s' % (kin8p2_setting3,end))
    s3.write_formula('H%s' % (curNum), '=\'8.2 Gev|%s\'!C%s' % (kin8p2_setting3,end))
    s3.write('L%s' % (curNum), evnt)
    curNum += 1
endCur =  curNum
l1 = endCur+1

s3.write_formula('F%s' % (curNum), '=D%s/3600/E%s' % (curNum-1,endCur-1))
s3.write_formula('I%s' % (curNum), '=B%s/G%s' % (curNum,qPAC))
s3.write_formula('M%s' % (curNum), '=L%s/K%s' % (curNum,evntPAC))

s3.write('B%s' % (endCur), 'Total',bold)
s3.write_formula('D%s' % (endCur), '=SUM(D%s:D%s)' % (curNum-1,endCur-1),bold)
s3.write('E%s' % (endCur), tPACPrime,bold)
s3.write_formula('F%s' % (endCur), 'D%s/3600/E%s' % (endCur,endCur),bold)
s3.write('G%s' % (endCur), '=\'8.2 Gev|%s\'!I%s' % (kin8p2_setting3,end),bold)
s3.write_formula('H%s' % (endCur), '=SUM(H%s:H%s)' % (curNum-1,endCur-1),bold)
s3.write_formula('I%s' % (endCur), '=H%s/G%s' % (endCur,endCur),bold)
s3.write('K%s' % (endCur), evntPAC,bold)
s3.write_formula('L%s' % (endCur), '=SUM(L%s:L%s)' % (curNum-1,endCur-1),bold)
s3.write_formula('M%s' % (endCur), '=L%s/K%s' % (endCur,endCur),bold)
s3.write_formula('N%s' % (endCur), '=M%s/I%s' % (endCur,endCur),bold)

####################################################################################################
# Next angle #############
##########################

curNum =1
current = kin8p2_left3_Values[0]
tPAC= kin8p2_left3_Values[1]
tPACPrime = kin8p2_left3_Values[2]
qPAC = kin8p2_left3_Values[3]
evnt= kin8p2_left3_Values[4]
evntPAC = kin8p2_left3_Values[5]

s3.write('A%s' % (l1), '%s deg LH2' % kin8p2_left3)
s4b.write('A%s' % (l2), '%s deg LH2' % kin8p2_left3)


print("Looking at current %s uA" % (current))
# [RunNum,charge]
newData = (
    [8186, 130.736],
    [8187, 237.769],
    [8188, 225.298],
    [8189, 212.305],
    [8190, 228.331],
    [8191, 242.026],
    [8192, 229.37],
    [8193, 221.139],
    [8194, 225.426],
    [8195, 237.951],
    [8196, 225.127],
    [8197, 233.28],
    [8198, 228.909],
    [8199, 228.348],
    [8200, 211.308],
    [8201, 199.924],
    [8202, 110.813],
    [8203, 214.391],
    [8204, 111.292],
    [8205, 132.979],
    [8206, 235.786],
    [8207, 151.301],
    [8212, 206.137],
    [8213, 210.943],
    [8214, 259.246],
    [8215, 264.208],
    [8216, 223.263],
    [8217, 35.142],
    [8218, 134.189],
    [8219, 51.275],
    [8220, 135.232],
    [8221, 176.068],
    [8222, 265.22],
    [8223, 257.788],
    [8224, 204.388],
    [8225, 226.71],
    [8226, 228.738],
    [8227, 210.347],
    [8228, 248.232],
    [8229, 231.277],
    [8230, 238.423],
    [8231, 277.524],
    [8232, 294.295],
    [8233, 211.225],
    [8234, 170.231],
    [8235, 248.228],
    [8236, 260.883],
    [8237, 231.814],
    [8238, 265.791],
    [8239, 241.444],
    [8240, 188.966],
    [8241, 213.552],
    [8242, 336.619],
    [8243, 211.894],
    [8244, 210.954],
    [8245, 203.536],
    [8246, 161.978],
    
)
tmpCurr = [current]
for value in (tmpCurr):
    s4b.write('A%s' % (curNum+l2), '@ %suA (mC)' % (value))
    # Starts at 0 for rows and columns
    row = l2+curNum-1
    col = 1
    for runNum, BCM4A in (newData):
        s4b.write(row,col, runNum)
        s4b.write(row,col+1, BCM4A)
        row += 1
    end = row+1
    # Going back to sheet one so we can 'link' second sheet values
    s4b.write('B%s' % (end), 'Total',bold)
    s4b.write_formula('C%s' % (end), '=SUM(C%s:C%s)' % (curNum+l2,end-1) ,bold)
    s4b.write('E%s' % (end), current,bold)
    s4b.write('G%s' % (end), tPAC,bold)
    s4b.write_formula('I%s' % (end),'=G%s*3600*0.000070*1000' % (end) ,bold)
    s4b.write_formula('J%s' % (end), '=C%s/I%s' % (end,end),bold)
    l2 = end+1
    curNum = 1+l1
    print("%s" % curNum)
    s3.write('A%s' % (curNum), '@ %suA (mC)' % (value))
    s3.write_formula('B%s' % (curNum), '=\'8.2 Gev|%s\'!C%s' % (kin8p2_setting3,end))
    s3.write_formula('C%s' % (curNum), '=\'8.2 Gev|%s\'!D%s' % (kin8p2_setting3,end))
    s3.write_formula('D%s' % (curNum), '=\'8.2 Gev|%s\'!F%s' % (kin8p2_setting3,end))
    # s3.write_formula('F%s' % (curNum), '=D%s/3600/E%s' % (curNum,curNum+1)) Need work
    s3.write_formula('H%s' % (curNum), '=\'8.2 Gev|%s\'!C%s' % (kin8p2_setting3,end))
    # s3.write_formula('I%s' % (curNum), '=B%s/G%s' % (curNum,curNum+1))
    s3.write('L%s' % (curNum), evnt)
    # s3.write_formula('M%s' % (curNum), '=L%s/K%s' % (curNum,curNum+1))
    curNum += 1
endCur =  curNum
l1 = endCur+1
s3.write('B%s' % (endCur), 'Total',bold)
s3.write_formula('D%s' % (endCur), '=SUM(D%s:D%s)' % (curNum-1,endCur-1),bold)
s3.write('E%s' % (endCur), tPACPrime,bold)
s3.write_formula('F%s' % (endCur), 'D%s/3600/E%s' % (endCur,endCur),bold)
s3.write('G%s' % (endCur), '=\'8.2 Gev|%s\'!I%s' % (kin8p2_setting3,end),bold)
s3.write_formula('H%s' % (endCur), '=SUM(H%s:H%s)' % (curNum-1,endCur-1),bold)
s3.write_formula('I%s' % (endCur), '=H%s/G%s' % (endCur,endCur),bold)
s3.write('K%s' % (endCur), evntPAC,bold)
s3.write_formula('L%s' % (endCur), '=SUM(L%s:L%s)' % (curNum-1,endCur-1),bold)
s3.write_formula('M%s' % (endCur), '=L%s/K%s' % (endCur,endCur),bold)
s3.write_formula('N%s' % (endCur), '=M%s/I%s' % (endCur,endCur),bold)

######################################################################################################

curNum =0

current = kin8p2DUM_center1_Values[0]
tPAC= kin8p2DUM_center1_Values[1]
tPACPrime = kin8p2DUM_center1_Values[2]
qPAC = kin8p2DUM_center1_Values[3]
evnt= kin8p2DUM_center1_Values[4]
evntPAC = kin8p2DUM_center1_Values[5]

print("Looking at current %s uA" % (current))
# [RunNum,charge]
newData = (
    [8209, 108.125],
    [8210, 138.341],
    [8211, 176.443],
)
tmpCurr = [current]
for value in (tmpCurr):
    s4b.write('A%s' % (curNum+l2), 'DUMMY (%suA)' % (value))
    # Starts at 0 for rows and columns
    row = l2+curNum-1
    col = 1
    for runNum, BCM4A in (newData):
        s4b.write(row,col, runNum)
        s4b.write(row,col+1, BCM4A)
        row += 1
    end = row+1
    # Going back to sheet one so we can 'link' second sheet values
    s4b.write('B%s' % (end), 'Total',bold)
    s4b.write_formula('C%s' % (end), '=SUM(C%s:C%s)' % (curNum+l2,end-1) ,bold)
    s4b.write('E%s' % (end), current,bold)
    s4b.write('G%s' % (end), tPAC,bold)
    s4b.write_formula('I%s' % (end),'=G%s*3600*0.000040*1000' % (end) ,bold)
    s4b.write_formula('J%s' % (end), '=C%s/I%s' % (end,end),bold)
    l2 = end+1
    curNum = l1
    print("%s" % curNum)
    s3.write('A%s' % (curNum), 'DUMMY (%suA)' % (value))
    s3.write_formula('B%s' % (curNum), '=\'8.2 Gev|%s\'!C%s' % (kin8p2_setting3,end))
    s3.write_formula('C%s' % (curNum), '=\'8.2 Gev|%s\'!D%s' % (kin8p2_setting3,end))
    s3.write_formula('D%s' % (curNum), '=\'8.2 Gev|%s\'!F%s' % (kin8p2_setting3,end))
    s3.write_formula('H%s' % (curNum), '=\'8.2 Gev|%s\'!C%s' % (kin8p2_setting3,end))
    s3.write('L%s' % (curNum), evnt)
    curNum += 1
endCur =  curNum
l1 = endCur+1

s3.write_formula('F%s' % (curNum), '=D%s/3600/E%s' % (curNum-1,endCur-1))
s3.write_formula('I%s' % (curNum), '=B%s/G%s' % (curNum,qPAC))
s3.write_formula('M%s' % (curNum), '=L%s/K%s' % (curNum,evntPAC))

s3.write('B%s' % (endCur), 'Total',bold)
s3.write_formula('D%s' % (endCur), '=SUM(D%s:D%s)' % (curNum-1,endCur-1),bold)
s3.write('E%s' % (endCur), tPACPrime,bold)
s3.write_formula('F%s' % (endCur), 'D%s/3600/E%s' % (endCur,endCur),bold)
s3.write('G%s' % (endCur), '=\'8.2 Gev|%s\'!I%s' % (kin8p2_setting3,end),bold)
s3.write_formula('H%s' % (endCur), '=SUM(H%s:H%s)' % (curNum-1,endCur-1),bold)
s3.write_formula('I%s' % (endCur), '=H%s/G%s' % (endCur,endCur),bold)
s3.write('K%s' % (endCur), evntPAC,bold)
s3.write_formula('L%s' % (endCur), '=SUM(L%s:L%s)' % (curNum-1,endCur-1),bold)
s3.write_formula('M%s' % (endCur), '=L%s/K%s' % (endCur,endCur),bold)
s3.write_formula('N%s' % (endCur), '=M%s/I%s' % (endCur,endCur),bold)

####################################################################################################

wb.close()
