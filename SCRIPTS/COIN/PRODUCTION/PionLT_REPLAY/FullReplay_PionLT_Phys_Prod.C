void FullReplay_PionLT_Phys_Prod (Int_t RunNumber = 0, Int_t MaxEvent = 0) {

  // Get RunNumber and MaxEvent if not provided.
  if(RunNumber == 0) {
    cout << "Enter a Run Number (-1 to exit): ";
    cin >> RunNumber;
    if( RunNumber<=0 ) return;
  }
  if(MaxEvent == 0) {
    cout << "\nNumber of Events to analyze: ";
    cin >> MaxEvent;
    if(MaxEvent == 0) {
      cerr << "...Invalid entry\n";
      exit;
    }
  }

  // Create file name patterns. Base this upon run number
  const char* RunFileNamePattern;
  if (RunNumber >= 10000){                        // PionLT 2021/2022 Data
    RunFileNamePattern = "shms_all_%05d.dat";
  }
  else if (RunNumber < 10000){                    // PionLT 2019 and KaonLT Data
    RunFileNamePattern = "coin_all_%05d.dat";
  }
  vector<TString> pathList;
  pathList.push_back(".");
  pathList.push_back("./raw");
  pathList.push_back("./raw1");
  pathList.push_back("./raw2");
  pathList.push_back("./raw_volatile");
  pathList.push_back("./raw_PionLT");
  pathList.push_back("./raw_KaonLT");
  pathList.push_back("./raw/../raw.copiedtotape");
  pathList.push_back("./cache");
//  pathList.push_back("./cache_kaonlt");
//  pathList.push_back("./cache_pionlt");

  const char* ROOTFileNamePattern = "ROOTfiles/Analysis/General/PionLT_Coin_replay_production_%d_%d.root";

  // Load global parameters
  gHcParms->Define("gen_run_number", "Run Number", RunNumber);
  gHcParms->AddString("g_ctp_database_filename", "DBASE/COIN/standard_PionLT.database");
  gHcParms->Load(gHcParms->GetString("g_ctp_database_filename"), RunNumber);
  gHcParms->Load(gHcParms->GetString("g_ctp_parm_filename"));
  gHcParms->Load(gHcParms->GetString("g_ctp_kinematics_filename"), RunNumber);
  // Load params for COIN trigger configuration
  //  gHcParms->Load("PARAM/TRIG/KaonLT_Trig/tcoin_Spring19_Offline.param");
  gHcParms->Load("PARAM/TRIG/tcoin.param");
  // Load fadc debug parameters
  gHcParms->Load("PARAM/HMS/GEN/h_fadc_debug.param");
  gHcParms->Load("PARAM/SHMS/GEN/p_fadc_debug.param");

  // Load the Hall C detector map
  gHcDetectorMap = new THcDetectorMap();
  gHcDetectorMap->Load("MAPS/COIN/DETEC/coin.map");

  // Load the BCM current params
  //  const char* CurrentFileNamePattern = "PARAM/HMS/BCM/CALIB/bcmcurrent_%d.param";
  //  gHcParms->Load(Form(CurrentFileNamePattern, RunNumber));

  // Dec data
  //  gHaApps->Add(new Podd::DecData("D","Decoder raw data"));

  //=:=:=:=
  // SHMS 
  //=:=:=:=

  // Set up the equipment to be analyzed.
  THcHallCSpectrometer* SHMS = new THcHallCSpectrometer("P", "SHMS");
  SHMS->SetEvtType(1);
  SHMS->AddEvtType(4);
  SHMS->AddEvtType(5);
  SHMS->AddEvtType(6);
  SHMS->AddEvtType(7);
  gHaApps->Add(SHMS);
  // Add Noble Gas Cherenkov to SHMS apparatus
  THcCherenkov* pngcer = new THcCherenkov("ngcer", "Noble Gas Cherenkov");
  SHMS->AddDetector(pngcer);
  // Add drift chambers to SHMS apparatus
  THcDC* pdc = new THcDC("dc", "Drift Chambers");
  SHMS->AddDetector(pdc);
  // Add hodoscope to SHMS apparatus
  THcHodoscope* phod = new THcHodoscope("hod", "Hodoscope");
  SHMS->AddDetector(phod);
  // Add Heavy Gas Cherenkov to SHMS apparatus
  THcCherenkov* phgcer = new THcCherenkov("hgcer", "Heavy Gas Cherenkov");
  SHMS->AddDetector(phgcer);
  // Add Aerogel Cherenkov to SHMS apparatus
  THcAerogel* paero = new THcAerogel("aero", "Aerogel");
  SHMS->AddDetector(paero);
  // Add calorimeter to SHMS apparatus
  THcShower* pcal = new THcShower("cal", "Calorimeter");
  SHMS->AddDetector(pcal);
  
  // THcBCMCurrent* hbc = new THcBCMCurrent("H.bcm", "BCM current check");
  // gHaPhysics->Add(hbc);

  // Add rastered beam apparatus
  THaApparatus* pbeam = new THcRasteredBeam("P.rb", "Rastered Beamline");
  gHaApps->Add(pbeam);
  // Add physics modules
  // Calculate reaction point
  THcReactionPoint* prp = new THcReactionPoint("P.react", "SHMS reaction point", "P", "P.rb");
  gHaPhysics->Add(prp);
  // Calculate extended target corrections
  THcExtTarCor* pext = new THcExtTarCor("P.extcor", "HMS extended target corrections", "P", "P.react");
  gHaPhysics->Add(pext);
  // Calculate golden track quantites
  THaGoldenTrack* pgtr = new THaGoldenTrack("P.gtr", "SHMS Golden Track", "P");
  gHaPhysics->Add(pgtr);
  // Calculate the hodoscope efficiencies
  THcHodoEff* peff = new THcHodoEff("phodeff", "SHMS hodo efficiency", "P.hod");
  gHaPhysics->Add(peff);   

  // Add event handler for scaler events
  THcScalerEvtHandler* pscaler = new THcScalerEvtHandler("P", "Hall C scaler event type 1");
  pscaler->AddEvtType(1);
  pscaler->AddEvtType(4);
  pscaler->AddEvtType(5);
  pscaler->AddEvtType(6);
  pscaler->AddEvtType(7);
  pscaler->AddEvtType(129);
  pscaler->SetDelayedType(129);
  pscaler->SetUseFirstEvent(kTRUE);
  gHaEvtHandlers->Add(pscaler);

  //Add SHMS event handler for helicity scalers
//  THcHelicityScaler *phelscaler = new THcHelicityScaler("P", "Hall C helicity scaler");
  //phelscaler->SetDebugFile("PHelScaler.txt");
//  phelscaler->SetROC(8);
//  phelscaler->SetUseFirstEvent(kTRUE);
//  gHaEvtHandlers->Add(phelscaler);

  //=:=:=
  // HMS 
  //=:=:=

  // Set up the equipment to be analyzed.
  THcHallCSpectrometer* HMS = new THcHallCSpectrometer("H", "HMS");
  HMS->SetEvtType(2);
  HMS->AddEvtType(4);
  HMS->AddEvtType(5);
  HMS->AddEvtType(6);
  HMS->AddEvtType(7);
  gHaApps->Add(HMS);
  // Add drift chambers to HMS apparatus
  THcDC* hdc = new THcDC("dc", "Drift Chambers");
  HMS->AddDetector(hdc);
  // Add hodoscope to HMS apparatus
  THcHodoscope* hhod = new THcHodoscope("hod", "Hodoscope");
  HMS->AddDetector(hhod);
  // Add Cherenkov to HMS apparatus
  THcCherenkov* hcer = new THcCherenkov("cer", "Heavy Gas Cherenkov");
  HMS->AddDetector(hcer);
  // Add Aerogel Cherenkov to HMS apparatus
  // THcAerogel* haero = new THcAerogel("aero", "Aerogel");
  // HMS->AddDetector(haero);
  // Add calorimeter to HMS apparatus
  THcShower* hcal = new THcShower("cal", "Calorimeter");
  HMS->AddDetector(hcal);

  // Add rastered beam apparatus
  THaApparatus* hbeam = new THcRasteredBeam("H.rb", "Rastered Beamline");
  gHaApps->Add(hbeam);  
  // Add physics modules
  // Calculate reaction point
  THcReactionPoint* hrp = new THcReactionPoint("H.react", "HMS reaction point", "H", "H.rb");
  gHaPhysics->Add(hrp);
  // Calculate extended target corrections
  THcExtTarCor* hext = new THcExtTarCor("H.extcor", "HMS extended target corrections", "H", "H.react");
  gHaPhysics->Add(hext);
  // Calculate golden track quantities
  THaGoldenTrack* hgtr = new THaGoldenTrack("H.gtr", "HMS Golden Track", "H");
  gHaPhysics->Add(hgtr);
  // Calculate the hodoscope efficiencies
  THcHodoEff* heff = new THcHodoEff("hhodeff", "HMS hodo efficiency", "H.hod");
  gHaPhysics->Add(heff);

  // Add BCM Current check
  // THcBCMCurrent* hbc = new THcBCMCurrent("H.bcm", "BCM current check");
  // gHaPhysics->Add(hbc);       

  // Add event handler for scaler events
  THcScalerEvtHandler *hscaler = new THcScalerEvtHandler("H", "Hall C scaler event type 4");  
  hscaler->AddEvtType(2);
  hscaler->AddEvtType(4);
  hscaler->AddEvtType(5);
  hscaler->AddEvtType(6);
  hscaler->AddEvtType(7);
  hscaler->AddEvtType(129);
  hscaler->SetDelayedType(129);
  hscaler->SetUseFirstEvent(kTRUE);
  gHaEvtHandlers->Add(hscaler);

  // Add event handler for helicity scalers
//  THcHelicityScaler *hhelscaler = new THcHelicityScaler("H", "Hall C helicity scaler");
  //hhelscaler->SetDebugFile("HHelScaler.txt");
//  hhelscaler->SetROC(5);
//  hhelscaler->SetUseFirstEvent(kTRUE);
//  gHaEvtHandlers->Add(hhelscaler);

  //=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=
  // Kinematics Modules
  //=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=

  // Add Physics Module to calculate primary (scattered electrons) beam kinematics
  THcPrimaryKine* hkin_primary = new THcPrimaryKine("H.kin.primary", "HMS Single Arm Kinematics", "H", "H.rb");
  gHaPhysics->Add(hkin_primary);
  // Add Physics Module to calculate secondary (scattered hadrons) beam kinematics
  THcSecondaryKine* pkin_secondary = new THcSecondaryKine("P.kin.secondary", "SHMS Single Arm Kinematics", "P", "H.kin.primary");
  gHaPhysics->Add(pkin_secondary);
  
  //=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=
  // Global Objects & Event Handlers
  //=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=

  // Add trigger apparatus
  THaApparatus* TRG = new THcTrigApp("T", "TRG");
  gHaApps->Add(TRG);
  // Add trigger detector to trigger apparatus
  THcTrigDet* coin = new THcTrigDet("coin", "Coincidence Trigger Information");
  // Suppress missing reference time warnings for these event types
  coin->SetEvtType(1);
  coin->AddEvtType(2);
  TRG->AddDetector(coin); 
 
  // THcHelicityScaler *helscaler = new THcHelicityScaler("HS", "Hall C helicity scalers"); 
  // helscaler->SetROC(8);
  // helscaler->SetUseFirstEvent(kTRUE);
  // gHaEvtHandlers->Add(helscaler);
  // Add helicity detector to trigger apparatus
  // THcHelicity* helicity = new THcHelicity("helicity","Helicity Detector");
  // TRG->AddDetector(helicity);
  // helicity->SetHelicityScaler(helscaler);


  //Add coin physics module THcCoinTime::THcCoinTime (const char *name, const char* description, const char* hadArmName, 
  // const char* elecArmName, const char* coinname) :
  THcCoinTime* coinTime = new THcCoinTime("CTime", "Coincidende Time Determination", "P", "H", "T.coin");
  gHaPhysics->Add(coinTime);
  //Add RF physics module THcRFTime::THcRFTime (const char *name, const char* description, const char* hadArmName, 
  // const char* elecArmName, const char* RFname) :
  THcRFTime* RFTime = new THcRFTime("RFTime", "RF Time Determination", "P", "H", "T.coin");
  gHaPhysics->Add(RFTime);

  // Add event handler for prestart event 125.
  THcConfigEvtHandler* ev125 = new THcConfigEvtHandler("HC", "Config Event type 125");
  gHaEvtHandlers->Add(ev125);
  // Add event handler for EPICS events
  THaEpicsEvtHandler* hcepics = new THaEpicsEvtHandler("epics", "HC EPICS event type 180");
  gHaEvtHandlers->Add(hcepics);
 
  // Set up the analyzer - we use the standard one,
  // but this could be an experiment-specific one as well.
  // The Analyzer controls the reading of the data, executes
  // tests/cuts, loops over Apparatus's and PhysicsModules,
  // and executes the output routines.
  THcAnalyzer* analyzer = new THcAnalyzer;

  // A simple event class to be output to the resulting tree.
  // Creating your own descendant of THaEvent is one way of
  // defining and controlling the output.
  THaEvent* event = new THaEvent;

  // Define the run(s) that we want to analyze.
  // We just set up one, but this could be many.
  THcRun* run = new THcRun( pathList, Form(RunFileNamePattern, RunNumber) );

  // Set to read in Hall C run database parameters
  run->SetRunParamClass("THcRunParameters");
  
  // Eventually need to learn to skip over, or properly analyze the pedestal events
  run->SetEventRange(1, MaxEvent); // Physics Event number, does not include scaler or control events.
  run->SetNscan(1);
  run->SetDataRequired(0x7);
  run->Print();

  // Define the analysis parameters
  TString ROOTFileName = Form(ROOTFileNamePattern, RunNumber, MaxEvent);
  analyzer->SetCountMode(2);  // 0 = counter is # of physics triggers
                              // 1 = counter is # of all decode reads
                              // 2 = counter is event number

  analyzer->SetEvent(event);
  // Set EPICS event type
  analyzer->SetEpicsEvtType(181);
  // Define crate map
  analyzer->SetCrateMapFileName("MAPS/db_cratemap.dat");
  // Define output ROOT file
  analyzer->SetOutFile(ROOTFileName.Data());
  // Define DEF-file+
  analyzer->SetOdefFile("DEF-files/PRODUCTION/Full_Replay_Pass2_Coin_v2.def"); // New version, slimmed down
  // Define cuts file with different Aerogel trays
  //analyzer->SetCutFile("DEF-files/PRODUCTION/CUTS/coin_production_cuts.def");  // optional
  //  analyzer->SetCutFile("DEF-files/PRODUCTION/CUTS/coin_tracking_cuts.def");  // optional

  if (RunNumber >= 11700 && RunNumber <= 13042){
   analyzer->SetCutFile("DEF-files/PRODUCTION/PionLT_DEF/Aero_1p011/Offline_Physics_Coin_Cuts.def");
  }
  else if (RunNumber >= 13043 && RunNumber <= 13130){
   analyzer->SetCutFile("DEF-files/PRODUCTION/PionLT_DEF/Aero_1p030/Offline_Physics_Coin_Cuts.def");
  }
  else if (RunNumber >= 13131 && RunNumber <= 16201){
   analyzer->SetCutFile("DEF-files/PRODUCTION/PionLT_DEF/Aero_1p011/Offline_Physics_Coin_Cuts.def");
  }
  else if (RunNumber >= 16202 && RunNumber <= 16286){
   analyzer->SetCutFile("DEF-files/PRODUCTION/PionLT_DEF/Aero_1p030/Offline_Physics_Coin_Cuts.def");
  }
  else {
   analyzer->SetCutFile("DEF-files/PRODUCTION/PionLT_DEF/Aero_1p011/Offline_Physics_Coin_Cuts.def");
  }

  // File to record accounting information for cuts
  analyzer->SetSummaryFile(Form("REPORT_OUTPUT/Analysis/General/PionLT_summary_production_%d_%d.report", RunNumber, MaxEvent));  // optional
  // Start the actual analysis.
  analyzer->Process(run);
  // Create report file from template
  //  analyzer->PrintReport("TEMPLATES/COIN/PRODUCTION/COIN_PROD.template",
  analyzer->PrintReport("TEMPLATES/COIN/PRODUCTION/PionLT_TEMP/PionLT_Offline_Physics_Coin.template",
  Form("REPORT_OUTPUT/Analysis/General/PionLT_replay_coin_production_%d_%d.report", RunNumber, MaxEvent));  // optional
  // Helicity scalers output
//  analyzer->PrintReport("TEMPLATES/HMS/SCALERS/hhelscalers.template",
//  			Form("REPORT_OUTPUT/Scalers/replay_hms_helicity_scalers_%d_%d.report", RunNumber, MaxEvent));  // optional  
//  analyzer->PrintReport("TEMPLATES/SHMS/SCALERS/phelscalers.template",
//  			Form("REPORT_OUTPUT/Scalers/replay_shms_helicity_scalers_%d_%d.report", RunNumber, MaxEvent));  // optional  

}
