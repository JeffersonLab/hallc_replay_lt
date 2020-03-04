#include <iostream>

void PlotLumi()
{
  //Define structure for input                                                                        
  struct input_t                                                                                      
  {                                                                                                   
    Int_t   run_num;                                                                                    
    Float_t HMS_EVENTS;
    Float_t HMS_EVENTSun;
    Float_t SHMS_EVENTS;
    Float_t SHMS_EVENTSun;
    Float_t HMS_track;                                                                                    
    Float_t HMS_trackun;
    Float_t HMS_etrack;                                                                                    
    Float_t HMS_etrackun;
    Float_t SHMS_track;                                                                                    
    Float_t SHMS_trackun;
    Float_t SHMS_hadtrack;                                                                                    
    Float_t SHMS_hadtrackun;
    Float_t SHMS_pitrack;                                                                                    
    Float_t SHMS_pitrackun;
    Float_t SHMS_Ktrack;                                                                                    
    Float_t SHMS_Ktrackun;
    Float_t SHMS_ptrack;                                                                                    
    Float_t SHMS_ptrackun;
    Float_t ACC_EDTM;
    Float_t PS1;
    Float_t PS3;
    Float_t TIME;
    Float_t BCM4B;
    Float_t TRIG1;
    Float_t TRIG3;
    Float_t comp_time;                                                                                
    Float_t comp_uncer;                                                                               
    Float_t HMS_elec;                                                                                
    Float_t HMS_elecun;                                                                               
    Float_t SHMS_elec;                                                                                
    Float_t SHMS_elecun;
    Float_t SENT_EDTM;
  };                                                                                                  
                                                                                                        
  input_t input;
                                                                                                                                                                              
  //Read Yield Data                                                                                   
  FILE *fp = fopen("Yield_Data.dat","r");                                
  char line[400];                                                                                     
                                                                                                       
  // Create TGraph for data                                                                           
  TGraphErrors *HMS_Current_Old = new TGraphErrors();                                                            
  HMS_Current_Old->SetTitle("HMS Normalized Yield NOT Using EDTM");  

  TGraphErrors *HMS_Current_EDTM = new TGraphErrors();                                                            
  HMS_Current_EDTM->SetTitle("HMS Normalized Yield Using EDTM"); 

  TGraphErrors *SHMS_Current_Old = new TGraphErrors();                                                            
  SHMS_Current_Old->SetTitle("SHMS Normalized Yield NOT Using EDTM");  

  TGraphErrors *SHMS_Current_EDTM = new TGraphErrors();                                                            
  SHMS_Current_EDTM->SetTitle("SHMS Normalized Yield Using EDTM"); 

  TGraphErrors *HMS_Rate_Old = new TGraphErrors();                                                            
  HMS_Rate_Old->SetTitle("HMS Normalized Yield NOT Using EDTM");  

  TGraphErrors *HMS_Rate_EDTM = new TGraphErrors();                                                            
  HMS_Rate_EDTM->SetTitle("HMS Normalized Yield Using EDTM"); 

  TGraphErrors *SHMS_Rate_Old = new TGraphErrors();                                                            
  SHMS_Rate_Old->SetTitle("SHMS Normalized Yield NOT Using EDTM");  

  TGraphErrors *SHMS_Rate_EDTM = new TGraphErrors();                                                            
  SHMS_Rate_EDTM->SetTitle("SHMS Normalized Yield Using EDTM"); 

  TGraphErrors *HMS_Current_track = new TGraphErrors();
  HMS_Current_track->SetTitle("HMS Tracking Efficiency");

  TGraphErrors *HMS_Rate_track = new TGraphErrors();
  HMS_Rate_track->SetTitle("HMS Tracking Efficiency");

  TGraphErrors *HMS_Current_etrack = new TGraphErrors();
  HMS_Current_etrack->SetTitle("HMS E Tracking Efficiency");

  TGraphErrors *HMS_Rate_etrack = new TGraphErrors();
  HMS_Rate_etrack->SetTitle("HMS E Tracking Efficiency");

  TGraphErrors *SHMS_Current_track = new TGraphErrors();
  SHMS_Current_track->SetTitle("SHMS Tracking Efficiency");

  TGraphErrors *SHMS_Rate_track = new TGraphErrors();
  SHMS_Rate_track->SetTitle("SHMS Tracking Efficiency");

  TGraphErrors *SHMS_Current_hadtrack = new TGraphErrors();
  SHMS_Current_hadtrack->SetTitle("SHMS HAD Tracking Efficiency");

  TGraphErrors *SHMS_Rate_hadtrack = new TGraphErrors();
  SHMS_Rate_hadtrack->SetTitle("SHMS HAD Tracking Efficiency");

  TGraphErrors *SHMS_Current_pitrack = new TGraphErrors();
  SHMS_Current_pitrack->SetTitle("SHMS PI Tracking Efficiency");

  TGraphErrors *SHMS_Rate_pitrack = new TGraphErrors();
  SHMS_Rate_pitrack->SetTitle("SHMS PI Tracking Efficiency");

  TGraphErrors *SHMS_Current_Ktrack = new TGraphErrors();
  SHMS_Current_Ktrack->SetTitle("SHMS K Tracking Efficiency");

  TGraphErrors *SHMS_Rate_Ktrack = new TGraphErrors();
  SHMS_Rate_Ktrack->SetTitle("SHMS K Tracking Efficiency");

  TGraphErrors *SHMS_Current_ptrack = new TGraphErrors();
  SHMS_Current_ptrack->SetTitle("SHMS p Tracking Efficiency");

  TGraphErrors *SHMS_Rate_ptrack = new TGraphErrors();
  SHMS_Rate_ptrack->SetTitle("SHMS p Tracking Efficiency");

  // Fill graph from .dat file                                                                        
 
  while (fgets(&line[0],500,fp)) {
    if (line[0] == '#')
      {
	continue;
      }
    else
      {                                                                                             
	sscanf(&line[0],"%d %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f",
	       &input.run_num,
	       &input.HMS_EVENTS,
	       &input.HMS_EVENTSun,
	       &input.SHMS_EVENTS,
	       &input.SHMS_EVENTSun,
	       &input.HMS_track,
	       &input.HMS_trackun,
	       &input.HMS_etrack,
	       &input.HMS_etrackun,
	       &input.SHMS_track,
	       &input.SHMS_trackun,
	       &input.SHMS_hadtrack,
	       &input.SHMS_hadtrackun,
	       &input.SHMS_pitrack,
	       &input.SHMS_pitrackun,
	       &input.SHMS_Ktrack,
	       &input.SHMS_Ktrackun,
	       &input.SHMS_ptrack,
	       &input.SHMS_ptrackun,
	       &input.ACC_EDTM,
	       &input.PS1,
	       &input.PS3,
	       &input.TIME,
	       &input.BCM4B,
	       &input.TRIG1,
	       &input.TRIG3,
	       &input.comp_time,
	       &input.comp_uncer,
	       &input.HMS_elec,
	       &input.HMS_elecun,
	       &input.SHMS_elec,
	       &input.SHMS_elecun,
	       &input.SENT_EDTM);   
	//cout << input.HMS_track << "   " << input.SHMS_ptrackun << "   " << input.comp_uncer << endl;
 
	HMS_Current_Old->SetPoint(HMS_Current_Old->GetN(),(input.BCM4B / input.TIME),(input.HMS_EVENTS)/(input.BCM4B*(input.comp_time*input.HMS_elec)*input.HMS_etrack));  
	HMS_Current_Old->SetPointError(HMS_Current_Old->GetN()-1,0.0,((input.HMS_EVENTS)/(input.BCM4B*(input.comp_time*input.HMS_elec)*input.HMS_etrack))*sqrt(pow(input.HMS_EVENTSun/input.HMS_EVENTS,2)+pow(input.comp_uncer/input.comp_time,2) + pow(input.HMS_elecun/input.HMS_elec,2) + pow(input.HMS_etrackun/input.HMS_etrack,2)));

	HMS_Current_EDTM->SetPoint(HMS_Current_EDTM->GetN(),(input.BCM4B / input.TIME),input.HMS_EVENTS/(input.BCM4B*(input.ACC_EDTM/input.SENT_EDTM)*input.HMS_etrack));  
	HMS_Current_EDTM->SetPointError(HMS_Current_EDTM->GetN()-1,0.0,((input.HMS_EVENTS/(input.BCM4B*(input.ACC_EDTM/input.SENT_EDTM)*input.HMS_elec*input.HMS_etrack)))*sqrt(pow(input.HMS_EVENTSun/input.HMS_EVENTS,2)+(1.0/input.ACC_EDTM) + (1.0/input.SENT_EDTM) + pow(input.HMS_etrackun/input.HMS_etrack,2)));
 
	SHMS_Current_Old->SetPoint(SHMS_Current_Old->GetN(),(input.BCM4B / input.TIME),(input.SHMS_EVENTS)/(input.BCM4B*(input.comp_time*input.SHMS_elec)*input.SHMS_hadtrack)); 
        SHMS_Current_Old->SetPointError(SHMS_Current_Old->GetN()-1,0.0,((input.SHMS_EVENTS)/(input.BCM4B*(input.comp_time*input.SHMS_elec)*input.SHMS_hadtrack))*sqrt(pow(input.SHMS_EVENTSun/input.SHMS_EVENTS,2)+pow(input.comp_uncer/input.comp_time,2) + pow(input.SHMS_elecun/input.SHMS_elec,2) + pow(input.SHMS_hadtrackun/input.SHMS_hadtrack,2))); 

	SHMS_Current_EDTM->SetPoint(SHMS_Current_EDTM->GetN(),(input.BCM4B / input.TIME),input.SHMS_EVENTS/(input.BCM4B*(input.ACC_EDTM/input.SENT_EDTM)*input.SHMS_hadtrack)); 
        SHMS_Current_EDTM->SetPointError(SHMS_Current_EDTM->GetN()-1,0.0,(input.SHMS_EVENTS/(input.BCM4B*((input.ACC_EDTM/input.SENT_EDTM)*input.SHMS_elec)*input.SHMS_hadtrack))*sqrt(pow(input.SHMS_EVENTSun/input.SHMS_EVENTS,2)+(1.0/input.ACC_EDTM) + (1.0/input.SENT_EDTM) + pow(input.SHMS_hadtrackun/input.SHMS_hadtrack,2))); 

	HMS_Rate_Old->SetPoint(HMS_Rate_Old->GetN(),(input.TRIG3 / input.TIME) / 1000.0,(input.HMS_EVENTS)/(input.BCM4B*(input.comp_time*input.HMS_elec)*input.HMS_etrack)); 
	HMS_Rate_Old->SetPointError(HMS_Rate_Old->GetN()-1,0.0,((input.HMS_EVENTS)/(input.BCM4B*(input.comp_time*input.HMS_elec)*input.HMS_etrack))*sqrt(pow(input.HMS_EVENTSun/input.HMS_EVENTS,2)+pow(input.comp_uncer/input.comp_time,2) + pow(input.HMS_elecun/input.HMS_elec,2) + pow(input.HMS_etrackun/input.HMS_etrack,2)));

	HMS_Rate_EDTM->SetPoint(HMS_Rate_EDTM->GetN(),(input.TRIG3 / input.TIME) / 1000.0,input.HMS_EVENTS/(input.BCM4B*(input.ACC_EDTM/input.SENT_EDTM)*input.HMS_etrack)); 
        HMS_Rate_EDTM->SetPointError(HMS_Rate_EDTM->GetN()-1,0.0,(input.HMS_EVENTS/(input.BCM4B*((input.ACC_EDTM/input.SENT_EDTM)*input.HMS_elec)*input.HMS_etrack))*sqrt(pow(input.HMS_EVENTSun/input.HMS_EVENTS,2)+(1.0/input.ACC_EDTM) + (1.0/input.SENT_EDTM) + pow(input.HMS_etrackun/input.HMS_etrack,2))); 

	SHMS_Rate_Old->SetPoint(SHMS_Rate_Old->GetN(),(input.TRIG1 / input.TIME) / 1000.0,(input.SHMS_EVENTS)/(input.BCM4B*(input.comp_time*input.SHMS_elec)*input.SHMS_hadtrack)); 
        SHMS_Rate_Old->SetPointError(SHMS_Rate_Old->GetN()-1,0.0,((input.SHMS_EVENTS)/(input.BCM4B*(input.comp_time*input.SHMS_elec)*input.SHMS_hadtrack))*sqrt(pow(input.SHMS_EVENTSun/input.SHMS_EVENTS,2)+pow(input.comp_uncer/input.comp_time,2) + pow(input.SHMS_elecun/input.SHMS_elec,2) + pow(input.SHMS_hadtrackun/input.SHMS_hadtrack,2))); 

	SHMS_Rate_EDTM->SetPoint(SHMS_Rate_EDTM->GetN(),(input.TRIG1 / input.TIME) / 1000.0,input.SHMS_EVENTS/(input.BCM4B*(input.ACC_EDTM/input.SENT_EDTM)*input.SHMS_hadtrack)); 
        SHMS_Rate_EDTM->SetPointError(SHMS_Rate_EDTM->GetN()-1,0.0,((input.SHMS_EVENTS/(input.BCM4B*((input.ACC_EDTM/input.SENT_EDTM)*input.SHMS_elec)*input.SHMS_hadtrack)))*sqrt(pow(input.SHMS_EVENTSun/input.SHMS_EVENTS,2)+(1.0/input.ACC_EDTM) + (1.0/input.SENT_EDTM) + pow(input.SHMS_hadtrackun/input.SHMS_hadtrack,2)));

	HMS_Current_track->SetPoint(HMS_Current_track->GetN(),(input.BCM4B / input.TIME) , input.HMS_track);
	HMS_Current_track->SetPointError(HMS_Current_track->GetN()-1,0.0, input.HMS_trackun);

	HMS_Rate_track->SetPoint(HMS_Rate_track->GetN(), (input.TRIG3 / input.TIME) / 1000.0, input.HMS_track);
	HMS_Rate_track->SetPointError(HMS_Rate_track->GetN()-1,0.0, input.HMS_trackun);

	HMS_Current_etrack->SetPoint(HMS_Current_etrack->GetN(),(input.BCM4B / input.TIME) , input.HMS_etrack);
	HMS_Current_etrack->SetPointError(HMS_Current_etrack->GetN()-1,0.0, input.HMS_etrackun);

	HMS_Rate_etrack->SetPoint(HMS_Rate_etrack->GetN(), (input.TRIG3 / input.TIME) / 1000.0, input.HMS_etrack);
	HMS_Rate_etrack->SetPointError(HMS_Rate_etrack->GetN()-1,0.0, input.HMS_etrackun);

	SHMS_Current_track->SetPoint(SHMS_Current_track->GetN(),(input.BCM4B / input.TIME) , input.SHMS_track);
	SHMS_Current_track->SetPointError(SHMS_Current_track->GetN()-1,0.0, input.SHMS_trackun);

	SHMS_Rate_track->SetPoint(SHMS_Rate_track->GetN(), (input.TRIG1 / input.TIME) / 1000.0, input.SHMS_track);
	SHMS_Rate_track->SetPointError(SHMS_Rate_track->GetN()-1,0.0, input.SHMS_trackun);

	SHMS_Current_hadtrack->SetPoint(SHMS_Current_hadtrack->GetN(),(input.BCM4B / input.TIME) , input.SHMS_hadtrack);
	SHMS_Current_hadtrack->SetPointError(SHMS_Current_hadtrack->GetN()-1,0.0, input.SHMS_hadtrackun);

	SHMS_Rate_hadtrack->SetPoint(SHMS_Rate_hadtrack->GetN(), (input.TRIG1 / input.TIME) / 1000.0, input.SHMS_hadtrack);
	SHMS_Rate_hadtrack->SetPointError(SHMS_Rate_hadtrack->GetN()-1,0.0, input.SHMS_hadtrackun);

	SHMS_Current_pitrack->SetPoint(SHMS_Current_pitrack->GetN(),(input.BCM4B / input.TIME) , input.SHMS_pitrack);
	SHMS_Current_pitrack->SetPointError(SHMS_Current_pitrack->GetN()-1,0.0, input.SHMS_pitrackun);

	SHMS_Rate_pitrack->SetPoint(SHMS_Rate_pitrack->GetN(), (input.TRIG1 / input.TIME) / 1000.0, input.SHMS_pitrack);
	SHMS_Rate_pitrack->SetPointError(SHMS_Rate_pitrack->GetN()-1,0.0, input.SHMS_pitrackun);

	SHMS_Current_Ktrack->SetPoint(SHMS_Current_Ktrack->GetN(),(input.BCM4B / input.TIME) , input.SHMS_Ktrack);
	SHMS_Current_Ktrack->SetPointError(SHMS_Current_Ktrack->GetN()-1,0.0, input.SHMS_Ktrackun);

	SHMS_Rate_Ktrack->SetPoint(SHMS_Rate_Ktrack->GetN(), (input.TRIG1 / input.TIME) / 1000.0, input.SHMS_Ktrack);
	SHMS_Rate_Ktrack->SetPointError(SHMS_Rate_Ktrack->GetN()-1,0.0, input.SHMS_Ktrackun);

	SHMS_Current_ptrack->SetPoint(SHMS_Current_ptrack->GetN(),(input.BCM4B / input.TIME) , input.SHMS_ptrack);
	SHMS_Current_ptrack->SetPointError(SHMS_Current_ptrack->GetN()-1,0.0, input.SHMS_ptrackun);

	SHMS_Rate_ptrack->SetPoint(SHMS_Rate_ptrack->GetN(), (input.TRIG1 / input.TIME) / 1000.0, input.SHMS_ptrack);
	SHMS_Rate_ptrack->SetPointError(SHMS_Rate_ptrack->GetN()-1,0.0, input.SHMS_ptrackun);
      }
  }
  fclose(fp);
  
  //Normalize yield to first entry
  
  Double_t Normalization_Factor;
  Double_t X;
  Double_t Y;
  Double_t EY;

  HMS_Current_Old->GetPoint(3, X, Normalization_Factor);
  for (Int_t i = 0; i < HMS_Current_Old->GetN(); i++) {
    HMS_Current_Old->GetPoint(i,X,Y);
    HMS_Current_Old->SetPoint(i,X,Y/Normalization_Factor);
    HMS_Current_Old->SetPointError(i,0.0,HMS_Current_Old->GetEY()[i]/Normalization_Factor);

    HMS_Rate_Old->GetPoint(i,X,Y);
    HMS_Rate_Old->SetPoint(i,X,Y/Normalization_Factor);
    HMS_Rate_Old->SetPointError(i,0.0,HMS_Rate_Old->GetEY()[i]/Normalization_Factor);
  }
  
  HMS_Current_EDTM->GetPoint(3, X, Normalization_Factor); 
  for (Int_t i = 0; i < HMS_Current_EDTM->GetN(); i++) {
    HMS_Current_EDTM->GetPoint(i,X,Y);
    HMS_Current_EDTM->SetPoint(i,X,Y/Normalization_Factor);
    HMS_Current_EDTM->SetPointError(i,0.0,HMS_Current_EDTM->GetEY()[i]/Normalization_Factor);

    HMS_Rate_EDTM->GetPoint(i,X,Y);
    HMS_Rate_EDTM->SetPoint(i,X,Y/Normalization_Factor);
    HMS_Rate_EDTM->SetPointError(i,0.0,HMS_Rate_EDTM->GetEY()[i]/Normalization_Factor);
  }

  SHMS_Current_Old->GetPoint(3, X, Normalization_Factor); 
  for (Int_t i = 0; i < SHMS_Current_Old->GetN(); i++) {
    SHMS_Current_Old->GetPoint(i,X,Y);
    SHMS_Current_Old->SetPoint(i,X,Y/Normalization_Factor);
    SHMS_Current_Old->SetPointError(i,0.0,SHMS_Current_Old->GetEY()[i]/Normalization_Factor);

    SHMS_Rate_Old->GetPoint(i,X,Y);
    SHMS_Rate_Old->SetPoint(i,X,Y/Normalization_Factor);
    SHMS_Rate_Old->SetPointError(i,0.0,SHMS_Rate_Old->GetEY()[i]/Normalization_Factor);
  }
  
  SHMS_Current_EDTM->GetPoint(3, X, Normalization_Factor);
  for (Int_t i = 0; i < SHMS_Current_EDTM->GetN(); i++) {
    SHMS_Current_EDTM->GetPoint(i,X,Y);
    SHMS_Current_EDTM->SetPoint(i,X,Y/Normalization_Factor);
    SHMS_Current_EDTM->SetPointError(i,0.0,SHMS_Current_EDTM->GetEY()[i]/Normalization_Factor);

    SHMS_Rate_EDTM->GetPoint(i,X,Y);
    SHMS_Rate_EDTM->SetPoint(i,X,Y/Normalization_Factor);
    SHMS_Rate_EDTM->SetPointError(i,0.0,SHMS_Rate_EDTM->GetEY()[i]/Normalization_Factor);
  }

  //Make it look nice
  HMS_Current_Old->SetMarkerColor(1);
  HMS_Current_Old->SetMarkerStyle(20);
  HMS_Current_Old->SetMarkerSize(1);
  HMS_Current_Old->GetXaxis()->SetTitle("Current uA");
  HMS_Current_Old->GetYaxis()->SetTitle("Normalized Yield");

  HMS_Current_EDTM->SetMarkerColor(1);
  HMS_Current_EDTM->SetMarkerStyle(20);
  HMS_Current_EDTM->SetMarkerSize(1);
  HMS_Current_EDTM->GetXaxis()->SetTitle("Current uA");
  HMS_Current_EDTM->GetYaxis()->SetTitle("Normalized Yield");

  SHMS_Current_Old->SetMarkerColor(1);
  SHMS_Current_Old->SetMarkerStyle(20);
  SHMS_Current_Old->SetMarkerSize(1);
  SHMS_Current_Old->GetXaxis()->SetTitle("Current uA");
  SHMS_Current_Old->GetYaxis()->SetTitle("Normalized Yield");

  SHMS_Current_EDTM->SetMarkerColor(1);
  SHMS_Current_EDTM->SetMarkerStyle(20);
  SHMS_Current_EDTM->SetMarkerSize(1);
  SHMS_Current_EDTM->GetXaxis()->SetTitle("Current uA");
  SHMS_Current_EDTM->GetYaxis()->SetTitle("Normalized Yield");

  HMS_Rate_Old->SetMarkerColor(1);
  HMS_Rate_Old->SetMarkerStyle(20);
  HMS_Rate_Old->SetMarkerSize(1);
  HMS_Rate_Old->GetXaxis()->SetTitle("Rate kHz");
  HMS_Rate_Old->GetYaxis()->SetTitle("Normalized Yield");

  HMS_Rate_EDTM->SetMarkerColor(1);
  HMS_Rate_EDTM->SetMarkerStyle(20);
  HMS_Rate_EDTM->SetMarkerSize(1);
  HMS_Rate_EDTM->GetXaxis()->SetTitle("Rate kHz");
  HMS_Rate_EDTM->GetYaxis()->SetTitle("Normalized Yield");

  SHMS_Rate_Old->SetMarkerColor(1);
  SHMS_Rate_Old->SetMarkerStyle(20);
  SHMS_Rate_Old->SetMarkerSize(1);
  SHMS_Rate_Old->GetXaxis()->SetTitle("Rate kHz");
  SHMS_Rate_Old->GetYaxis()->SetTitle("Normalized Yield");

  SHMS_Rate_EDTM->SetMarkerColor(1);
  SHMS_Rate_EDTM->SetMarkerStyle(20);
  SHMS_Rate_EDTM->SetMarkerSize(1);
  SHMS_Rate_EDTM->GetXaxis()->SetTitle("Rate kHz");
  SHMS_Rate_EDTM->GetYaxis()->SetTitle("Normalized Yield");

  HMS_Current_track->SetMarkerColor(2);
  HMS_Current_track->SetMarkerStyle(20);
  HMS_Current_track->SetMarkerSize(1);
  HMS_Current_track->GetXaxis()->SetTitle("Current uA");
  HMS_Current_track->GetYaxis()->SetTitle("Normalized Yield");

  HMS_Current_etrack->SetMarkerColor(3);
  HMS_Current_etrack->SetMarkerStyle(20);
  HMS_Current_etrack->SetMarkerSize(1);
  HMS_Current_etrack->GetXaxis()->SetTitle("Current uA");
  HMS_Current_etrack->GetYaxis()->SetTitle("Normalized Yield");

  HMS_Rate_track->SetMarkerColor(2);
  HMS_Rate_track->SetMarkerStyle(20);
  HMS_Rate_track->SetMarkerSize(1);
  HMS_Rate_track->GetXaxis()->SetTitle("Rate kHz");
  HMS_Rate_track->GetYaxis()->SetTitle("Efficiency (%)");

  HMS_Rate_etrack->SetMarkerColor(3);
  HMS_Rate_etrack->SetMarkerStyle(20);
  HMS_Rate_etrack->SetMarkerSize(1);
  HMS_Rate_etrack->GetXaxis()->SetTitle("Rate kHz");
  HMS_Rate_etrack->GetYaxis()->SetTitle("Efficiency (%)");

  SHMS_Current_track->SetMarkerColor(6);
  SHMS_Current_track->SetMarkerStyle(20);
  SHMS_Current_track->SetMarkerSize(1);
  SHMS_Current_track->GetXaxis()->SetTitle("Current uA");
  SHMS_Current_track->GetYaxis()->SetTitle("Efficiency (%)");

  SHMS_Current_hadtrack->SetMarkerColor(2);
  SHMS_Current_hadtrack->SetMarkerStyle(20);
  SHMS_Current_hadtrack->SetMarkerSize(1);
  SHMS_Current_hadtrack->GetXaxis()->SetTitle("Current uA");
  SHMS_Current_hadtrack->GetYaxis()->SetTitle("Efficiency (%)");

  SHMS_Current_pitrack->SetMarkerColor(3);
  SHMS_Current_pitrack->SetMarkerStyle(20);
  SHMS_Current_pitrack->SetMarkerSize(1);
  SHMS_Current_pitrack->GetXaxis()->SetTitle("Current uA");
  SHMS_Current_pitrack->GetYaxis()->SetTitle("Efficiency (%)");

  SHMS_Current_Ktrack->SetMarkerColor(4);
  SHMS_Current_Ktrack->SetMarkerStyle(20);
  SHMS_Current_Ktrack->SetMarkerSize(1);
  SHMS_Current_Ktrack->GetXaxis()->SetTitle("Current uA");
  SHMS_Current_Ktrack->GetYaxis()->SetTitle("Efficiency (%)");

  SHMS_Current_ptrack->SetMarkerColor(5);
  SHMS_Current_ptrack->SetMarkerStyle(20);
  SHMS_Current_ptrack->SetMarkerSize(1);
  SHMS_Current_ptrack->GetXaxis()->SetTitle("Current uA");
  SHMS_Current_ptrack->GetYaxis()->SetTitle("Efficiency (%)");

  SHMS_Rate_track->SetMarkerColor(6);
  SHMS_Rate_track->SetMarkerStyle(20);
  SHMS_Rate_track->SetMarkerSize(1);
  SHMS_Rate_track->GetXaxis()->SetTitle("Rate kHz");
  SHMS_Rate_track->GetYaxis()->SetTitle("Efficiency (%)");

  SHMS_Rate_hadtrack->SetMarkerColor(2);
  SHMS_Rate_hadtrack->SetMarkerStyle(20);
  SHMS_Rate_hadtrack->SetMarkerSize(1);
  SHMS_Rate_hadtrack->GetXaxis()->SetTitle("Rate kHz");
  SHMS_Rate_hadtrack->GetYaxis()->SetTitle("Efficiency (%)");

  SHMS_Rate_pitrack->SetMarkerColor(3);
  SHMS_Rate_pitrack->SetMarkerStyle(20);
  SHMS_Rate_pitrack->SetMarkerSize(1);
  SHMS_Rate_pitrack->GetXaxis()->SetTitle("Rate kHz");
  SHMS_Rate_pitrack->GetYaxis()->SetTitle("Efficiency (%)");

  SHMS_Rate_Ktrack->SetMarkerColor(4);
  SHMS_Rate_Ktrack->SetMarkerStyle(20);
  SHMS_Rate_Ktrack->SetMarkerSize(1);
  SHMS_Rate_Ktrack->GetXaxis()->SetTitle("Rate kHz");
  SHMS_Rate_Ktrack->GetYaxis()->SetTitle("Efficiency (%)");

  SHMS_Rate_ptrack->SetMarkerColor(5);
  SHMS_Rate_ptrack->SetMarkerStyle(20);
  SHMS_Rate_ptrack->SetMarkerSize(1);
  SHMS_Rate_ptrack->GetXaxis()->SetTitle("Rate kHz");
  SHMS_Rate_ptrack->GetYaxis()->SetTitle("Efficiency (%)");
  
  
  //Draw everything
  TCanvas *HMS_old = new TCanvas("HMS_old","Normalized Yield for HMS using pTRIG and L1ACC");
  HMS_old->Divide(2,1);
  HMS_old->cd(1);
  HMS_Current_Old->Draw("AEP");
  //Reference Line
  HMS_old->Update();
  TLine *reference = new TLine(gPad->GetUxmin(),1,gPad->GetUxmax(),1);
  reference->SetLineColor(kRed);
  HMS_Current_Old->GetYaxis()->SetTitleOffset(1.5);
  reference->Draw();  
  HMS_old->cd(2);
  HMS_Rate_Old->Draw("AEP");
  //Reference Line
  HMS_old->Update();
  TLine *reference_rate = new TLine(gPad->GetUxmin(),1,gPad->GetUxmax(),1);
  reference_rate->SetLineColor(kRed);
  HMS_Rate_Old->GetYaxis()->SetTitleOffset(1.5);
  reference_rate->Draw();

  HMS_old->Print(Form("OUTPUT/Norm_yield_hms_ptrig_L1ACC_%d.png",input.run_num));
  
  TCanvas *HMS_EDTM = new TCanvas("HMS_EDTM","Normalized Yield for HMS using EDTM");
  HMS_EDTM->Divide(2,1);
  HMS_EDTM->cd(1);
  HMS_Current_EDTM->Draw("AEP");
  HMS_EDTM->Update();
  HMS_Current_EDTM->GetYaxis()->SetTitleOffset(1.5);
  reference->Draw();
  HMS_EDTM->cd(2);
  HMS_Rate_EDTM->Draw("AEP");
  HMS_EDTM->Update();
  HMS_Rate_EDTM->GetYaxis()->SetTitleOffset(1.5);
  reference_rate->Draw();

  HMS_EDTM->Print(Form("OUTPUT/Norm_yield_hms_EDTM_%d.png",input.run_num));
  
  TCanvas *SHMS_old = new TCanvas("SHMS_old","Normalized Yield for SHMS using pTRIG and L1ACC");
  SHMS_old->Divide(2,1);
  SHMS_old->cd(1);
  SHMS_Current_Old->Draw("AEP");
  SHMS_old->Update();
  SHMS_Current_Old->GetYaxis()->SetTitleOffset(1.5);
  reference->Draw();
  SHMS_old->cd(2);
  TLine *SHMS_reference_rate = new TLine(gPad->GetUxmin(),1,gPad->GetUxmax(),1);
  SHMS_reference_rate->SetLineColor(kRed);
  SHMS_Rate_Old->Draw("AEP");
  SHMS_old->Update();
  SHMS_Rate_Old->GetYaxis()->SetTitleOffset(1.5);
  SHMS_reference_rate->Draw();

  SHMS_old->Print(Form("OUTPUT/Norm_yield_shms_ptrig_L1ACC_%d.png",input.run_num));
  
  TCanvas *SHMS_EDTM = new TCanvas("SHMS_EDTM","Normalized Yield for SHMS using EDTM");
  SHMS_EDTM->Divide(2,1);
  SHMS_EDTM->cd(1);
  SHMS_Current_EDTM->Draw("AEP");
  SHMS_EDTM->Update();
  SHMS_Current_EDTM->GetYaxis()->SetTitleOffset(1.5);
  reference->Draw();
  SHMS_EDTM->cd(2);
  SHMS_Rate_EDTM->Draw("AEP");
  SHMS_EDTM->Update();
  SHMS_Rate_EDTM->GetYaxis()->SetTitleOffset(1.5);
  SHMS_reference_rate->Draw();

  SHMS_EDTM->Print(Form("OUTPUT/Norm_yield_shms_EDTM_%d.png",input.run_num));
  
  TF1 *linear = new TF1("linear","[0] + [1]*(x)",0,100);
  linear->SetParName(0,"Intercept");
  linear->SetParName(1,"Slope");
  linear->FixParameter(0,1);
  HMS_Current_Old->Fit("linear","R");
  HMS_Current_Old->GetFunction("linear")->SetLineColor(kBlue);
  gPad->Update();

  //Efficiency Information
  
  TCanvas *HMS_Track = new TCanvas("HMS Track", "HMS Tracking Efficiency Information");
  HMS_Track->Divide(2,1);
  HMS_Track->cd(1);
  HMS_Current_track->SetMinimum(0.0);
  HMS_Current_track->SetMaximum(1.0);
  HMS_Current_track->Draw("AEP");
  HMS_Current_etrack->Draw("LEP");
  HMS_Track->cd(2);
  HMS_Rate_track->SetMinimum(0.0);
  HMS_Rate_track->SetMaximum(1.0);
  HMS_Rate_track->Draw("AEP");
  HMS_Rate_etrack->Draw("LEP");

  HMS_Track->Print(Form("OUTPUT/hms_track_eff_%d.png",input.run_num));

  TCanvas *SHMS_Track = new TCanvas("SHMS Track", "SHMS Tracking Efficiency Information");
  SHMS_Track->Divide(2,1);
  SHMS_Track->cd(1);
  SHMS_Current_track->SetMinimum(0.0);
  SHMS_Current_track->SetMaximum(1.0);
  SHMS_Current_track->Draw("ALEP");
  SHMS_Current_hadtrack->Draw("LEP");
  SHMS_Current_pitrack->Draw("LEP");
  SHMS_Current_Ktrack->Draw("LEP");
  SHMS_Current_ptrack->Draw("LEP");
  SHMS_Track->cd(2);
  SHMS_Rate_track->SetMinimum(0.0);
  SHMS_Rate_track->SetMaximum(1.0);
  SHMS_Rate_track->Draw("AEP");
  SHMS_Rate_hadtrack->Draw("LEP");
  SHMS_Rate_pitrack->Draw("LEP");
  SHMS_Rate_Ktrack->Draw("LEP");
  SHMS_Rate_ptrack->Draw("LEP");

  SHMS_Track->Print(Form("OUTPUT/shms_track_eff_%d.png",input.run_num));
  
}
