HMS Carbon Optics Replay Instructions
----------------------------------------------------------------------------------------------------------------------------------
Loading replay into root
----------------------------------------------------------------------------------------------------------------------------------
When running carbon optics, use the 50k replays to determine event rate.

For the HMS, these are saved into ROOTfiles/Analysis/50k/hms_coin_replay_production_####_50000.root, where #### is the run number.

From the hallc_replay_lt directory, enter:

root -l ROOTfiles/Analysis/50k/hms_coin_replay_production_####_50000.root

to load the 50k replay file.

----------------------------------------------------------------------------------------------------------------------------------
Selecting Carbon Foil
----------------------------------------------------------------------------------------------------------------------------------
From here, we want to determine the rate of events into the individual sieve holes FOR EACH FOIL.

In root, reconstruct the carbon foils by enter the following:

T->Draw("H.gtr.dp:H.gtr.y>>(300,-15,15,200,-10,10)","","colz")

To select one foil, apply cuts along H.gtr.y depending on your target.

For the 0.5% Carbon target, this requires no cut.

For the Optics #2 +/- 8 cm, select the first foil using:

T->Draw("H.gtr.dp:H.gtr.y>>(300,-15,15,200,-10,10)","H.gtr.y<0","colz")

and select the second foil using:

T->Draw("H.gtr.dp:H.gtr.y>>(300,-15,15,200,-10,10)","H.gtr.y>0","colz")

Ensure only one foil is visible after these cuts before proceeding. The cuts on H.gtr.y will be used for selecting the sieve hole.

----------------------------------------------------------------------------------------------------------------------------------
Selecting Sieve Hole
----------------------------------------------------------------------------------------------------------------------------------
Now reconstruct the sieve collimator plane by entering the following:

T->Draw("H.gtr.x+H.gtr.th*166.032:H.gtr.y+H.gtr.ph*166.032>>(200,-10,10,400,-20,20)","","colz")

And apply your H.gtr.y cut you used to select ONE carbon foil (if any cut was needed). 
For the Optics #2 target, this step will need to be completed twice for the two cuts.

Now you should apply cuts along H.gtr.x+H.gtr.th*166.032 and H.gtr.y+H.gtr.ph*166.032 to select a singular hole.
Try and select a hole with lower number of events. Not on the edge of acceptance, but not where events are hitting the most.

Root will tell you the count of events within this cut. Combined with the time of the run, you can get an estimate of the 
rate of events into the sieve holes. Our goal is 200 counts per hole.

Once this is complete, the cuts to the sieve plane should be repeated for the other foil(s).
The lowest rate should be used to determine how long to run.
















OLD SHMS instructions
------------------------------------------------------------------------------------------------------------------------------------


Alternatively, for the SHMS:

SCRIPTS/SHMS/PRODUCTION/replay_production_shms_coin.C

(this is just the 50k replay script, but it should have all variables needed)

which saves into  ROOTfiles/Analysis/50k/shms_coin_replay_production_####_##.root



From the hallc_replay_lt directory, enter:

root -l ROOTfiles/Analysis/50k/shms_coin_replay_production_####_##.root

to load the file of the 10-15 minute optics run.


From here, we want to determine the rate of events into the individual sieve holes FOR EACH FOIL.

For the 0.5% Carbon target, this requires no extra effort.

For the Optics #2 +/- 8 cm, we need to apply some cuts.

In root, reconstruct the sieve collimator enterance by enter the following:

T->Draw("P.gtr.dp:P.gtr.y>>(100,-15,15,100,-20,20)","","colz")


and determine cuts along H.gtr.y to select one of the foils.

If unfamiliar, the format is:

T->Draw("P.gtr.dp:P.gtr.y>>(100,-15,15,100,-20,20)","P.gtr.y<HIGHCUT&&P.gtr.y>LOWCUT","colz")


ALSO make a delta cut. +/- should be ok

Now reconstruct the siev collimator plane by entering the following:

T->Draw("P.gtr.x+P.gtr.th*253.0:(-0.019*P.gtr.dp+0.00019*P.gtr.dp*P.gtr.dp+(138.0+75.0)*P.gtr.ph+P.gtr.y) + 40.0*(-0.00052*P.gtr.dp+0.0000052*pow(P.gtr.dp,2)+P.gtr.ph)>>(100,-10,10,100,-20,20)","","colz")

And apply your H.gtr.y cut.


ALTERATIVELY:

T->Draw("P.gtr.ph:P.gtr.th>>(100,-0.05,0.05,100,-0.05,0.05)","","colz")

Now you should apply cuts along P.gtr.x+P.gtr.th*253.0 and (-0.019*P.gtr.dp+0.00019*P.gtr.dp*P.gtr.dp+(138.0+75.0)*P.gtr.ph+P.gtr.y) + 40.0*(-0.00052*P.gtr.dp+0.0000052*pow(P.gtr.dp,2)+P.gtr.ph) to select a singular hole.
Try and select a hole with lower number of events. Not on the edge of acceptance, but not where events are hitting the most.

Root will tell you the count of events within this cut. Combined with the time of the run, you can get an estimate of the 
rate of events into the sieve holes. Our goal is 200 counts per hole.

Once this is complete, the cuts to the sieve plane should be repeated for the other foil(s).
The lowest rate should be used to determine how long to run.

TL;DR:

Call Jacob Murphy and make him do this
