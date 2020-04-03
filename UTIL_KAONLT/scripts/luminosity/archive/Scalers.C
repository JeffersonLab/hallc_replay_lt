#define Scalers_cxx
// The class definition in Scalers.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.


// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// root> T->Process("Scalers.C")
// root> T->Process("Scalers.C","some options")
// root> T->Process("Scalers.C+")
//


#include "Scalers.h"
#include <TH2.h>
#include <TStyle.h>


void Scalers::Begin(TTree * /*tree*/)
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).

  /*TString option = GetOption();
    Current = option.Atoi();*/
  Info("Begin", "Starting scalar corrections");
  //Info("Begin", Form("Threshold current is taken as: %s",option.Data()));
}

void Scalers::SlaveBegin(TTree * /*tree*/)
{
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).

  

  TString option = GetOption();
  TString PS1_temp = option(0,option.Index("."));
  TString PS3_temp = option(option.Index(".")+1,option.Length());
  PS1 = PS1_temp.Atof();
  PS3 = PS3_temp.Atof();

  bcm_name[0] = "BCM1 ";
  bcm_name[1] = "BCM2 ";
  bcm_name[2] = "BCM4A";
  bcm_name[3] = "BCM4B";
  bcm_name[4] = "BCM4C";

  trig_name[0] = "TRIG1";
  trig_name[1] = "TRIG2";
  trig_name[2] = "TRIG3";
  trig_name[3] = "TRIG4";
  trig_name[4] = "TRIG5";
  trig_name[5] = "TRIG6";

  PRE_name[0] = "40";
  PRE_name[1] = "100";
  PRE_name[2] = "150";
  PRE_name[3] = "200";

  rate_name[0] = "EL_LO_LO";
  rate_name[1] = "EL_LO";
  rate_name[2] = "EL_HI";
  rate_name[3] = "EL_REAL";
  rate_name[4] = "EL_CLEAN";
  rate_name[5] = "STOF";

  SHMS_rate_name[0] = "EL_LO_LO";
  SHMS_rate_name[1] = "EL_LO";
  SHMS_rate_name[2] = "EL_HI";
  SHMS_rate_name[3] = "EL_REAL";
  SHMS_rate_name[4] = "EL_CLEAN";
  SHMS_rate_name[5] = "STOF";
  SHMS_rate_name[6] = "PR_HI";
  SHMS_rate_name[7] = "PR_LO";
}

Bool_t Scalers::Process(Long64_t entry)
{
  // The Process() function is called for each entry in the tree (or possibly
  // keyed object in the case of PROOF) to be processed. The entry argument
  // specifies which entry in the currently loaded tree is to be processed.
  // When processing keyed objects with PROOF, the object is already loaded
  // and is available via the fObject pointer.
  //
  // This function should contain the \"body\" of the analysis. It can contain
  // simple or elaborate selection criteria, run algorithms on the data
  // of the event and typically fill histograms.
  //
  // The processing can be stopped by calling Abort().
  //
  // Use fStatus to set the return value of TTree::Process().
  //
  // The return value is currently not used.

  fReader.SetEntry(entry);
  //if (entry % 100000 == 0) printf("Processing Entry number %lld\n",entry);

  bcm_value[0] = *H_BCM1_scalerCharge;
  bcm_value[1] = *H_BCM2_scalerCharge;
  bcm_value[2] = *H_BCM4A_scalerCharge;
  bcm_value[3] = *H_BCM4B_scalerCharge;
  bcm_value[4] = *H_BCM4C_scalerCharge;

  trig_value[0] = *H_hTRIG1_scaler;
  trig_value[1] = *H_hTRIG2_scaler;
  trig_value[2] = *H_hTRIG3_scaler;
  trig_value[3] = *H_hTRIG4_scaler;
  trig_value[4] = *H_hTRIG5_scaler;
  trig_value[5] = *H_hTRIG6_scaler;

  acctrig_value = *H_hL1ACCP_scaler;

  PRE_value[0] = *H_hPRE40_scaler;
  PRE_value[1] = *H_hPRE100_scaler;
  PRE_value[2] = *H_hPRE150_scaler;
  PRE_value[3] = *H_hPRE200_scaler;

  SHMS_PRE_value[0] = *H_pPRE40_scaler;
  SHMS_PRE_value[1] = *H_pPRE100_scaler;
  SHMS_PRE_value[2] = *H_pPRE150_scaler;
  SHMS_PRE_value[3] = *H_pPRE200_scaler;

  rate_value[0] = *H_hEL_LO_LO_scaler;
  rate_value[1] = *H_hEL_LO_scaler;
  rate_value[2] = *H_hEL_HI_scaler;
  rate_value[3] = *H_hEL_REAL_scaler;
  rate_value[4] = *H_hEL_CLEAN_scaler;
  rate_value[5] = *H_hSTOF_scaler;

  SHMS_rate_value[0] = *H_pEL_LO_LO_scaler;
  SHMS_rate_value[1] = *H_pEL_LO_scaler;
  SHMS_rate_value[2] = *H_pEL_HI_scaler;
  SHMS_rate_value[3] = *H_pEL_REAL_scaler;
  SHMS_rate_value[4] = *H_pEL_CLEAN_scaler;
  SHMS_rate_value[5] = *H_pSTOF_scaler;
  SHMS_rate_value[6] = *H_pPRHI_scaler;
  SHMS_rate_value[7] = *H_pPRLO_scaler;

  EDTM_value = *H_EDTM_scaler;

  for (Int_t ibcm = 0; ibcm < NBCM; ibcm++) {
    current_I = 0;
    if (*H_1Mhz_scalerTime != previous_time) {
      current_I = (bcm_value[ibcm] - previous_charge[ibcm])/(*H_1Mhz_scalerTime - previous_time);
    }
    if (current_I > 2.5) {
      charge_sum[ibcm] += (bcm_value[ibcm] - previous_charge[ibcm]);
      time_sum[ibcm] += (*H_1Mhz_scalerTime - previous_time);
    }
    if (ibcm == 3 && (current_I > 2.5)) {
      EDTM_current = (EDTM_value - previous_EDTM);
      EDTM_sum += EDTM_current;
      acctrig_sum += ((acctrig_value - EDTM_current) - previous_acctrig);
      for (Int_t itrig = 0; itrig < NTRIG; itrig++) {
	trig_sum[itrig] += (trig_value[itrig] - previous_trig[itrig]);
      }
      for (Int_t iPRE = 0; iPRE < NPRE; iPRE++) {
	PRE_sum[iPRE] += (PRE_value[iPRE] - previous_PRE[iPRE]);
	SHMS_PRE_sum[iPRE] += (SHMS_PRE_value[iPRE] - SHMS_previous_PRE[iPRE]);
      }
      for (Int_t iRATE = 0; iRATE < NRATE; iRATE++) {
	rate_sum[iRATE] += (rate_value[iRATE] - previous_rate[iRATE]);
      }
      for (Int_t iRATE = 0; iRATE < SHMSNRATE; iRATE++) {
	SHMS_rate_sum[iRATE] += (SHMS_rate_value[iRATE] - SHMS_previous_rate[iRATE]);
      }
      
      previous_acctrig = (acctrig_value - EDTM_current);
      previous_EDTM = EDTM_value;
      for (Int_t itrig = 0; itrig < NTRIG; itrig++) {
	previous_trig[itrig] = trig_value[itrig];
      }
      for (Int_t iPRE = 0; iPRE < NPRE; iPRE++) {
	previous_PRE[iPRE] = PRE_value[iPRE];
	SHMS_previous_PRE[iPRE] = SHMS_PRE_value[iPRE];
      }
      for (Int_t iRATE = 0; iRATE < NRATE; iRATE++) {
	previous_rate[iRATE] = rate_value[iRATE];
      }
      for (Int_t iRATE = 0; iRATE < SHMSNRATE; iRATE++) {
	SHMS_previous_rate[iRATE] = SHMS_rate_value[iRATE];
      }
    } 
    previous_charge[ibcm] = bcm_value[ibcm];
  }
   
  time_total += (*H_1Mhz_scalerTime - previous_time);
  previous_time = *H_1Mhz_scalerTime;
   
  return kTRUE;
}

void Scalers::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.

}

void Scalers::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.
  
  TString option = GetOption();
  TString PS1_temp = option(0,option.Index("."));
  TString PS3_temp = option(option.Index(".")+1,option.Length());
  PS1 = PS1_temp.Atof();
  PS3 = PS3_temp.Atof();
  cout << Form("Using prescale factors: PS1 %.0f, PS3 %.0f\n",PS1,PS3);
  cout << "\n\nUsed current threshold value: 5 uA" << endl;

  for (Int_t ibcm = 0; ibcm < NBCM; ibcm++) {
    cout << Form("%s charge: %.3f uC, Beam over threshold for %.3f s", bcm_name[ibcm].c_str(), charge_sum[ibcm], time_sum[ibcm]) << endl;
  }

  cout <<"\n\n";

  
  cout << Form("L1ACC counts: %.0f, %s Prescaled Pretrigger Counts: %.0f, %s Prescaled Pretrigger Counts: %.0f\nComputer Livetime: %f +/- %f", acctrig_sum, trig_name[0].c_str(), trig_sum[0]/PS1, trig_name[2].c_str(), trig_sum[2]/PS3, acctrig_sum/((trig_sum[0]/PS1) + (trig_sum[2]/PS3)), (acctrig_sum/((trig_sum[0]/PS1) + (trig_sum[2]/PS3)))*sqrt((1/(trig_sum[0]/PS1))+(1/(trig_sum[2]/PS3))+(1/acctrig_sum))) << endl;
  

  //cout <<"\n\n";

  /*for (Int_t iPRE = 0; iPRE < NPRE; iPRE++) {
    cout << Form("HMS PRE%s counts: %.0f", PRE_name[iPRE].c_str(), PRE_sum[iPRE]) << endl;
    }*/
  cout << Form("HMS Electronic livetime: %f +/- %f",1 - ((6/5)*(PRE_sum[1]-PRE_sum[2])/(PRE_sum[1])), (PRE_sum[1]-PRE_sum[2])/(PRE_sum[1]) * sqrt( (sqrt(PRE_sum[1]) + sqrt(PRE_sum[2]))/(PRE_sum[1] - PRE_sum[2]) + (sqrt(PRE_sum[1])/PRE_sum[1]) )) << endl;

  //cout <<"\n\n";

  /*for (Int_t iPRE = 0; iPRE < NPRE; iPRE++) {
    cout << Form("SHMS PRE%s counts: %.0f", PRE_name[iPRE].c_str(), SHMS_PRE_sum[iPRE]) << endl;
    }*/
  cout << Form("SHMS Electronic livetime: %f +/- %f",1 - ((6/5)*(SHMS_PRE_sum[1]-SHMS_PRE_sum[2])/(SHMS_PRE_sum[1])), (SHMS_PRE_sum[1]-SHMS_PRE_sum[2])/(SHMS_PRE_sum[1]) * sqrt( (sqrt(SHMS_PRE_sum[1]) + sqrt(SHMS_PRE_sum[2]))/(SHMS_PRE_sum[1] - SHMS_PRE_sum[2]) + (sqrt(SHMS_PRE_sum[1])/SHMS_PRE_sum[1]) )) << endl;

  //cout << "\n\n";
  /*
  for (Int_t iRATE = 0; iRATE < NRATE; iRATE++) {
    cout << Form("HMS %s counts: %.0f, rate: %f +/- %f Hz", rate_name[iRATE].c_str(), rate_sum[iRATE], rate_sum[iRATE]/time_sum[2], sqrt(rate_sum[iRATE])/time_sum[2]) << endl;
  }

  cout << "\n\n";

  for (Int_t iRATE = 0; iRATE < SHMSNRATE; iRATE++) {
    cout << Form("SHMS %s counts: %.0f, rate: %f +/- %f Hz", SHMS_rate_name[iRATE].c_str(), SHMS_rate_sum[iRATE], SHMS_rate_sum[iRATE]/time_sum[2], sqrt(SHMS_rate_sum[iRATE])/time_sum[2]) << endl;
  }
  */
  cout << Form("EDTM Events: %.0f", EDTM_sum) << endl;

  ofstream myfile1;
  myfile1.open ("Yield_Data.dat", fstream::app);
  myfile1 << Form("%.3f %.3f %.0f %.0f %.4f %.4f %.4f %.4f %.4f %.4f %.0f\n",
		  //Time
		  time_sum[3],
		  //Charge
		  charge_sum[3],
		  //
		  trig_sum[0],
		  //
		  trig_sum[2],
		  //CPU LT
		  acctrig_sum/((trig_sum[0]/PS1) + (trig_sum[2]/PS3)),
		  (acctrig_sum/((trig_sum[0]/PS1) + (trig_sum[2]/PS3)))*sqrt((1/(trig_sum[0]/PS1))+(1/(trig_sum[2]/PS3))+(1/acctrig_sum)),
		  //HMS elec LT
		  1 - ((6/5)*(PRE_sum[1]-PRE_sum[2])/(PRE_sum[1])),
		  (PRE_sum[1]-PRE_sum[2])/(PRE_sum[1]) * sqrt( (sqrt(PRE_sum[1]) + sqrt(PRE_sum[2]))/(PRE_sum[1] - PRE_sum[2]) + (sqrt(PRE_sum[1])/PRE_sum[1]) ),
		  //SHMS elec LT
		  1 - ((6/5)*(SHMS_PRE_sum[1]-SHMS_PRE_sum[2])/(SHMS_PRE_sum[1])),
		  (SHMS_PRE_sum[1]-SHMS_PRE_sum[2])/(SHMS_PRE_sum[1]) * sqrt( (sqrt(SHMS_PRE_sum[1]) + sqrt(SHMS_PRE_sum[2]))/(SHMS_PRE_sum[1] - SHMS_PRE_sum[2]) + (sqrt(SHMS_PRE_sum[1])/SHMS_PRE_sum[1]) ),
		  //Sent EDTM
		  EDTM_sum);
  myfile1.close();
}
