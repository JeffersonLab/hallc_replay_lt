/*
Cameron Cotton - 01/10/2023
Used to get the calibration constants for the SHMS Noble Gas Cerenkov PMTs.

Sample Usage:
root -l pngcer_calib.C
*/

#include <ROOT/RDataFrame.hxx>
#include <TChain.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TLine.h>

//Initial Fit parameters for the multiGaus and multiGausNoBackground fit functions
Double_t startParam[9] = {50000, 1, 1, 1, 2, 5, 1, 0.5, 10};
Double_t startParamNB[5] = {50000, 1, 2, 5, 1};	

// approximate fitting function for pmts from E.H.Bellamy paper https://doi.org/10.1016/0168-9002(94)90183-X
Double_t multiGaus(Double_t *x, Double_t *par)
{
    int n = 2; // Number of gausians to use
    Double_t z = x[0];
    Double_t f = 0;
    
    // fit parameters
    Double_t c = par[0]; //overall constant
    Double_t q = par[1]; //Q0       - pedestal position
    Double_t s = par[2]; //sigma0   - standard deviation of the type I background process (pedestal)
    Double_t a = par[3]; //Alpha    - coefficient of the exponential decrease of the type II background
    Double_t u = par[4]; //mu       - number of photo-electrons
    Double_t Q = par[5]; //Q1       - average charge at the PM output
    Double_t S = par[6]; //Sigma1   - corresponding standard deviation of the charge distribution
    Double_t w = par[7]; //omega    - probability that signal is accompanied by type II background process
    Double_t b = par[8]; //overall constant for background
    
    
    // Background Term
    Double_t B = 0;
    /*    if ( (z - q) <= 0 ) // step function
    {
        B = TMath::Exp(-u)*(1-w)*TMath::Exp(-1*TMath::Power(z-q,2)/(2*TMath::Power(s,2)))/(s*TMath::Sqrt(2*TMath::Pi()));
    }else{
        B = TMath::Exp(-u)*( (1-w)*TMath::Exp(-1*TMath::Power(z-q,2)/(2*TMath::Power(s,2)))/(s*TMath::Sqrt(2*TMath::Pi())) + (w*a*TMath::Exp(-a*(z-q))) );
	}*/
    B = b*(TMath::Exp(-u)*( (1-w)*TMath::Exp(-1*TMath::Power(z-q,2)/(2*TMath::Power(s,2)))/(s*TMath::Sqrt(2*TMath::Pi())) + (w*a*TMath::Exp(-a*(z-q)))) );
	
    /*    
    // multi guasian being added together.
    for (int i = 1; i < (n+1); n++)
    {
      //This version is exactly how it's writen in the paper
      //f += (TMath::Power(u,i)*TMath::Exp(-u)/(TMath::Factorial(i)))*(1/(S*TMath::Sqrt(2*TMath::Pi()*i)))*TMath::Exp(-1*TMath::Power((z-q-(w/a)-i*Q),2)/(2*i*TMath::Power(S,2)));
      //this version is streamlined to reduce function calls
      f += (TMath::Power(u,i)/(TMath::Factorial(i)*S*2.506627*TMath::Sqrt(i)))*TMath::Exp(-u + (-1/(2*i))*((z-q-(w/a)-i*Q)/S)*((z-q-(w/a)-i*Q)/S));
    }
    */
    //Root does not like that for loop for whatever reason, so here are the first 5 terms explicitly
    f = c*((u/S)*TMath::Exp(-u-((z-q-(w/a)-Q)*(z-q-(w/a)-Q))/(2*S*S)) + (u/(2*S*TMath::Sqrt(2)))*TMath::Exp(-u-((z-q-(w/a)-2*Q)*(z-q-(w/a)-2*Q))/(4*S*S)) + (u/(6*S*TMath::Sqrt(3)))*TMath::Exp(-u-((z-q-(w/a)-3*Q)*(z-q-(w/a)-3*Q))/(6*S*S)) + (u/(24*S*TMath::Sqrt(4)))*TMath::Exp(-u-((z-q-(w/a)-4*Q)*(z-q-(w/a)-4*Q))/(8*S*S)) + (u/(120*S*TMath::Sqrt(5)))*TMath::Exp(-u-((z-q-(w/a)-5*Q)*(z-q-(w/a)-5*Q))/(10*S*S)));
    //f = c*((u/(S*2.506627)*TMath::Exp(-u+(-1/2)*((z-q-Q)/S)*((z-q-Q)/S))));
    return B+f;    
}

// approximate fitting function for pmts from E.H.Bellamy paper https://doi.org/10.1016/0168-9002(94)90183-X
Double_t multiGausNoBackground(Double_t *x, Double_t *par)
{
    int n = 2; // Number of gausians to use
    Double_t z = x[0];
    Double_t f = 0;
    
    // fit parameters
    //Double_t w = par[0]; //omega    - probability that signal is accompanied by type II background process
    Double_t c = par[0]; //overall constant
    Double_t q = par[1]; //Q0       - pedestal position
    Double_t u = par[2]; //mu       - number of photo-electrons
    Double_t Q = par[3]; //Q1       - average charge at the PM output
    Double_t S = par[4]; //Sigma1   - corresponding standard deviation of the charge distribution
    
    //f = c*((u/(S*2.506627)*TMath::Exp(-u+(-1/2)*((z-q-Q)/S)*((z-q-Q)/S)))+(u*u/(S*7.089812))*TMath::Exp(-u+(-1/(4))*((z-q-2*Q)/S)*((z-q-2*Q)/S))+(u*u*u/(S*26.049632))*TMath::Exp(-u+(-1/(6))*((z-q-3*Q)/S)*((z-q-3*Q)/S))+(u*u*u*u/(S*120.318096))*TMath::Exp(-u+(-1/(8))*((z-q-4*Q)/S)*((z-q-4*Q)/S))+(u*u*u*u*u/(S*672.598604))*TMath::Exp(-u+(-1/(10))*((z-q-5*Q)/S)*((z-q-5*Q)/S)));
    //f = c*(u/(S*2.506627)*TMath::Exp(-u+((-1/2)*((z-q-Q)/S)*((z-q-Q)/S))));
    
    f = c*((u/S)*TMath::Exp(-u-((z-q-Q)*(z-q-Q))/(2*S*S)) + (u/(2*S*TMath::Sqrt(2)))*TMath::Exp(-u-((z-q-2*Q)*(z-q-2*Q))/(4*S*S)) + (u/(6*S*TMath::Sqrt(3)))*TMath::Exp(-u-((z-q-3*Q)*(z-q-3*Q))/(6*S*S)) + (u/(24*S*TMath::Sqrt(4)))*TMath::Exp(-u-((z-q-4*Q)*(z-q-4*Q))/(8*S*S)) + (u/(120*S*TMath::Sqrt(5)))*TMath::Exp(-u-((z-q-5*Q)*(z-q-5*Q))/(10*S*S)) + (u/(720*S*TMath::Sqrt(6)))*TMath::Exp(-u-((z-q-6*Q)*(z-q-6*Q))/(12*S*S)) + (u/(5040*S*TMath::Sqrt(7)))*TMath::Exp(-u-((z-q-7*Q)*(z-q-7*Q))/(14*S*S)));
    
    return f;
}


int pngcer_calib(string cmdInput) {
	// Input file format
	std::string replay_file_form = "../../ROOTfiles/Calib/CER/Pion_coin_replay_calibration_%i_-1.root";

	// Taking user input
	std::string raw_run_input;
	std::vector<int> run_list;
	bool valid_runs = true;
	do {
		std::cout << "Please Enter Run Numbers for Calibation, Space Separated: ";
		if (cmdInput == ""){
		  std::getline(std::cin, raw_run_input);
		}else{
		  raw_run_input = cmdInput;
		}
		std::istringstream iss(raw_run_input);
		int run_num;
		run_list.clear();
		while (iss >> run_num) run_list.push_back(run_num);
		for (int run_number : run_list){
			if (run_number == 0){
				std::cout << "Ending Program...\n\n";
				return 1;
			}
			std::string replay_file = Form(replay_file_form.c_str(),run_number);
			if (FILE *file = fopen(replay_file.c_str(), "r")) { // check if file can be found
				fclose(file);
				std::cout << "Was able to open file at " << replay_file << "\n";
			} 
			else {
				std::cout << "Could not open file at " <<  replay_file 
				          << "\nDoes it exist? Try again or enter 0 to exit...\n\n";
				valid_runs = false;
				break;
			}
		}
	} 	while (!valid_runs);
	
	// Setting up RDataFrame
	ROOT::EnableImplicitMT(8);
	TChain chain("T");
	for(int run_number : run_list){
		chain.Add(Form(replay_file_form.c_str(), run_number));
		std::cout << "Adding run " << run_number << " to the chain...\n";
	}
	ROOT::RDataFrame df(chain);

	// Defining Cut Parameters
	int adcMultCut = 1;
	double xmin = 2;
	double ymin = 2;
	double xmax = 25;
	double ymax = 25;
	double emin = 0.7;
	double emax = 3.0;
	double dpmin = -10;
	double dpmax = 22;

	// Plotting Calorimeter distribution for entire dataset
	ROOT::RDF::TH1DModel m_etottracknorm ("h_etotnorm","P.cal.etotnorm Cuts on All Events", 300, 0, 3);
	auto h_etottracknorm = df.Filter(Form("P.cal.etotnorm > 0.01 && P.gtr.dp > %.1f && P.gtr.dp < %.1f"
										  ,dpmin,dpmax)).Histo1D(m_etottracknorm,"P.cal.etotnorm");

	// New RDataFrame with general good electron cuts applied
	auto df2 = df.Filter(Form("P.cal.etotnorm > %.1f && P.cal.etotnorm < %.1f && P.gtr.dp > %.1f"
							  "&& P.gtr.dp < %.1f",emin,emax,dpmin,dpmax));
	
	// Making Cerenkov position and pulse integral plots for each PMT
	ROOT::RDF::TH1DModel m_pmt1_int ("h_pmt1_int","PMT 1 goodAdcPulseInt Distribution", 80, 1, 161);
	ROOT::RDF::TH2DModel m_pmt1_pos ("h_pmt1_pos","PMT 1 Cerenkov Position Cuts", 60, -30, 30, 60, -30, 30);
	auto h_pmt1_int = df2.Filter(Form("P.ngcer.goodAdcMult[0] == %i && P.ngcer.goodAdcMult[1] == 0"
	                                  "&& P.ngcer.goodAdcMult[2] == 0 && P.ngcer.goodAdcMult[3] == 0"
									  "&& P.ngcer.xAtCer > %.1f && P.ngcer.xAtCer < %.1f" 
									  "&& P.ngcer.yAtCer > %.1f && P.ngcer.yAtCer < %.1f"
									  ,adcMultCut, xmin, xmax, ymin, ymax)).Histo1D(m_pmt1_int,"P.ngcer.goodAdcPulseInt");
	auto h_pmt1_pos = df2.Filter(Form("P.ngcer.goodAdcMult[0] == %i && P.ngcer.goodAdcMult[1] == 0"
	                                  "&& P.ngcer.goodAdcMult[2] == 0 && P.ngcer.goodAdcMult[3] == 0"
									  ,adcMultCut)).Histo2D(m_pmt1_pos,"P.ngcer.xAtCer","P.ngcer.yAtCer");
	
	ROOT::RDF::TH1DModel m_pmt2_int ("h_pmt2_int","PMT 2 goodAdcPulseInt Distribution", 80, 1, 161);
	ROOT::RDF::TH2DModel m_pmt2_pos ("h_pmt2_pos","PMT 2 Cerenkov Position Cuts", 60, -30, 30, 60, -30, 30);
	auto h_pmt2_int = df2.Filter(Form("P.ngcer.goodAdcMult[0] == 0 && P.ngcer.goodAdcMult[1] == %i"
	                                  "&& P.ngcer.goodAdcMult[2] == 0 && P.ngcer.goodAdcMult[3] == 0"
									  "&& P.ngcer.xAtCer > %.1f && P.ngcer.xAtCer < %.1f"
									  "&& P.ngcer.yAtCer < -1*%.1f && P.ngcer.yAtCer > -1*%.1f"
									  ,adcMultCut, xmin, xmax, ymin, ymax)).Histo1D(m_pmt2_int,"P.ngcer.goodAdcPulseInt");
	auto h_pmt2_pos = df2.Filter(Form("P.ngcer.goodAdcMult[0] == 0 && P.ngcer.goodAdcMult[1] == %i"
	                                  "&& P.ngcer.goodAdcMult[2] == 0 && P.ngcer.goodAdcMult[3] == 0"
									  ,adcMultCut)).Histo2D(m_pmt2_pos,"P.ngcer.xAtCer","P.ngcer.yAtCer");

	ROOT::RDF::TH1DModel m_pmt3_int ("h_pmt3_int","PMT 3 goodAdcPulseInt Distribution", 80, 1, 161);
	ROOT::RDF::TH2DModel m_pmt3_pos ("h_pmt3_pos","PMT 3 Cerenkov Position Cuts", 60, -30, 30, 60, -30, 30);
	auto h_pmt3_int = df2.Filter(Form("P.ngcer.goodAdcMult[0] == 0 && P.ngcer.goodAdcMult[1] == 0"
	                                  "&& P.ngcer.goodAdcMult[2] == %i && P.ngcer.goodAdcMult[3] == 0"
									  "&& P.ngcer.xAtCer < -1*%.1f && P.ngcer.xAtCer > -1*%.1f"
									  "&& P.ngcer.yAtCer > %.1f && P.ngcer.yAtCer < %.1f"
									  ,adcMultCut, xmin, xmax, ymin, ymax)).Histo1D(m_pmt3_int,"P.ngcer.goodAdcPulseInt");
	auto h_pmt3_pos = df2.Filter(Form("P.ngcer.goodAdcMult[0] == 0 && P.ngcer.goodAdcMult[1] == 0"
	                                  "&& P.ngcer.goodAdcMult[2] == %i && P.ngcer.goodAdcMult[3] == 0"
									  ,adcMultCut)).Histo2D(m_pmt3_pos,"P.ngcer.xAtCer","P.ngcer.yAtCer");

	ROOT::RDF::TH1DModel m_pmt4_int ("h_pmt4_int","PMT 4 goodAdcPulseInt Distribution", 80, 1, 161);
	ROOT::RDF::TH2DModel m_pmt4_pos ("h_pmt4_pos","PMT 4 Cerenkov Position Cuts", 60, -30, 30, 60, -30, 30);
	auto h_pmt4_int = df2.Filter(Form("P.ngcer.goodAdcMult[0] == 0 && P.ngcer.goodAdcMult[1] == 0"
									  "&& P.ngcer.goodAdcMult[2] == 0 && P.ngcer.goodAdcMult[3] == %i"
									  "&& P.ngcer.xAtCer < -1*%.1f && P.ngcer.xAtCer > -1*%.1f"
									  "&& P.ngcer.yAtCer < -1*%.1f && P.ngcer.yAtCer > -1*%.1f"
									  ,adcMultCut, xmin, xmax, ymin, ymax)).Histo1D(m_pmt4_int,"P.ngcer.goodAdcPulseInt");
	auto h_pmt4_pos = df2.Filter(Form("P.ngcer.goodAdcMult[0] == 0 && P.ngcer.goodAdcMult[1] == 0"
									  "&& P.ngcer.goodAdcMult[2] == 0 && P.ngcer.goodAdcMult[3] == %i"
									  ,adcMultCut)).Histo2D(m_pmt4_pos,"P.ngcer.xAtCer","P.ngcer.yAtCer");

	// Fitting pulse integral distribution for each PMT to determine calibration constant
	TCanvas* c1 = new TCanvas("c1", "Cerenkov Calibration", 1200, 1200);
	c1->Divide(2,2);
	c1->cd(1);
	
	TF1* g1 = new TF1("G1",multiGaus,0,150,9);
	g1->SetParameters(startParam);
	g1->SetParLimits(0,1,1000000000);
	g1->SetParLimits(1,-1,40);
	g1->SetParLimits(2,0,20);
	g1->SetParLimits(3,0,400);
	g1->SetParLimits(4,0,400);
	g1->SetParLimits(5,-1,400);
	g1->SetParLimits(6,0.01,500);
	g1->SetParLimits(7,0,1);
	g1->SetParLimits(8,0,1000000000);
	/*g1->SetParLimits(0,1,100000000);
	g1->SetParLimits(1,0,4000);
	g1->SetParLimits(2,1,200);
	//g1->SetParLimits(3,0,400);
	g1->SetParLimits(4,0.01,400);
	*/
	cout << "Starting Fit of multiGuass (May take awhile)\n";
	h_pmt1_int->Fit(g1,"R");
	
	TF1* f1 = new TF1("f1","[0]*TMath::Power(([1]/[2]),(x/[2]))*(TMath::Exp(-([1]/[2])))/TMath::Gamma((x/[2])+1)",30,120);
	f1->SetLineColor(kViolet-6);
	f1->SetParameters(2000,50,3);
	h_pmt1_int->Fit(f1,"R+");
	double yscale1 = f1->GetParameter(0);
	double mean1 = f1->GetParameter(1);
	double xscale1 = f1->GetParameter(2); // this is the calibration constant	
	h_pmt1_int->SetTitle("PMT 1 Cerenkov Calibration Poisson Fit; Pulse Integral");
	//	h_pmt1_int->GetXaxis()->SetRangeUser(0, h_pmt1_int->GetMaximum(h_pmt1_int->GetMaximumBin(1,1000)));
	auto h_pmt1_int_clone = h_pmt1_int->DrawClone();

	const int Ngaus = 5;
	TF1* manyGaus[Ngaus]; 
	for (int i = 0; i < Ngaus; i++)
        {
	    int b = i+1;
	    manyGaus[i] = new TF1(Form("G1_%d",i+1), "[0]*([2]/([5]*[4]*TMath::Sqrt([5])))*TMath::Exp(-[2]-((x-[1]-[5]*[3])*(x-[1]-[5]*[3]))/(2*[5]*[4]*[4]))", 0, 150);
	    manyGaus[i]->SetLineColor(kAzure-3);
	    manyGaus[i]->SetParameter(0,g1->GetParameter(0));
	    manyGaus[i]->SetParameter(1,g1->GetParameter(1) + (g1->GetParameter(7)/g1->GetParameter(3)));
	    manyGaus[i]->SetParameter(2,g1->GetParameter(4));
	    manyGaus[i]->SetParameter(3,g1->GetParameter(5));
	    manyGaus[i]->SetParameter(4,g1->GetParameter(6));
	    manyGaus[i]->SetParameter(5,b);
	    
	    manyGaus[i]->Draw("Same");
	}

	c1->cd(2);
	TF1* g2 = new TF1("G2",multiGaus,0,100,9);
	g2->SetParameters(startParam);
	g2->SetParLimits(0,1,1000000000);
	g2->SetParLimits(1,-1,40);
	g2->SetParLimits(2,0,20);
	g2->SetParLimits(3,0,400);
	g2->SetParLimits(4,0,400);
	g2->SetParLimits(5,-1,400);
	g2->SetParLimits(6,0.01,500);
	g2->SetParLimits(7,0,1);
	g2->SetParLimits(8,0,1000000000);
	h_pmt2_int->Fit(g2,"R");
    
	TF1* f2 = new TF1("f2","[0]*TMath::Power(([1]/[2]),(x/[2]))*(TMath::Exp(-([1]/[2])))/TMath::Gamma((x/[2])+1)",30,70);
	f2->SetParameters(2000,50,3);
	f2->SetLineColor(kViolet-6);
	h_pmt2_int->Fit(f2,"R+");
	double yscale2 = f2->GetParameter(0);
	double mean2 = f2->GetParameter(1);
	double xscale2 = f2->GetParameter(2); // this is the calibration constant
	h_pmt2_int->SetTitle("PMT 2 Cerenkov Calibration Poisson Fit; Pulse Integral");
	auto h_pmt2_int_clone = h_pmt2_int->DrawClone();

	TF1* manyGaus2[Ngaus]; 
	for (int i = 0; i < Ngaus; i++)
        {
	    int b = i+1;
	    manyGaus2[i] = new TF1(Form("G2_%d",i+1), "[0]*([2]/([5]*[4]*TMath::Sqrt([5])))*TMath::Exp(-[2]-((x-[1]-[5]*[3])*(x-[1]-[5]*[3]))/(2*[5]*[4]*[4]))", 0, 150);
	    manyGaus2[i]->SetLineColor(kAzure-3);
	    manyGaus2[i]->SetParameter(0,g2->GetParameter(0));
	    manyGaus2[i]->SetParameter(1,g2->GetParameter(1) + (g2->GetParameter(7)/g2->GetParameter(3)));
	    manyGaus2[i]->SetParameter(2,g2->GetParameter(4));
	    manyGaus2[i]->SetParameter(3,g2->GetParameter(5));
	    manyGaus2[i]->SetParameter(4,g2->GetParameter(6));
	    manyGaus2[i]->SetParameter(5,b);
	    
	    manyGaus2[i]->Draw("Same");
	}
	
	c1->cd(3);
	TF1* g3 = new TF1("G2",multiGaus,0,100,9);
	g3->SetParameters(startParam);
	g3->SetParLimits(0,1,1000000000);
	g3->SetParLimits(1,-1,40);
	g3->SetParLimits(2,0,20);
	g3->SetParLimits(3,0,400);
	g3->SetParLimits(4,0,400);
	g3->SetParLimits(5,-1,400);
	g3->SetParLimits(6,0.01,500);
	g3->SetParLimits(7,0,1);
	g3->SetParLimits(8,0,1000000000);
	h_pmt3_int->Fit(g3,"R");
    
	TF1* f3 = new TF1("f3","[0]*TMath::Power(([1]/[2]),(x/[2]))*(TMath::Exp(-([1]/[2])))/TMath::Gamma((x/[2])+1)",30,70);
	f3->SetParameters(2000,50,3);
	f3->SetLineColor(kViolet-6);
	h_pmt3_int->Fit(f3,"R+");
	double yscale3 = f3->GetParameter(0);
	double mean3 = f3->GetParameter(1);
	double xscale3 = f3->GetParameter(2); // this is the calibration constant
	h_pmt3_int->SetTitle("PMT 3 Cerenkov Calibration Poisson Fit; Pulse Integral");
	auto h_pmt3_int_clone = h_pmt3_int->DrawClone();
	
	TF1* manyGaus3[Ngaus]; 
	for (int i = 0; i < Ngaus; i++)
        {
	    int b = i+1;
	    manyGaus3[i] = new TF1(Form("G2_%d",i+1), "[0]*([2]/([5]*[4]*TMath::Sqrt([5])))*TMath::Exp(-[2]-((x-[1]-[5]*[3])*(x-[1]-[5]*[3]))/(2*[5]*[4]*[4]))", 0, 150);
	    manyGaus3[i]->SetLineColor(kAzure-3);
	    manyGaus3[i]->SetParameter(0,g3->GetParameter(0));
	    manyGaus3[i]->SetParameter(1,g3->GetParameter(1) + (g3->GetParameter(7)/g3->GetParameter(3)));
	    manyGaus3[i]->SetParameter(2,g3->GetParameter(4));
	    manyGaus3[i]->SetParameter(3,g3->GetParameter(5));
	    manyGaus3[i]->SetParameter(4,g3->GetParameter(6));
	    manyGaus3[i]->SetParameter(5,b);
	    
	    manyGaus3[i]->Draw("Same");
	}
	
	c1->cd(4);
	TF1* g4 = new TF1("G2",multiGaus,0,100,9);
	g4->SetParameters(startParam);
	g4->SetParLimits(0,1,1000000000);
	g4->SetParLimits(1,-1,40);
	g4->SetParLimits(2,0,20);
	g4->SetParLimits(3,0,400);
	g4->SetParLimits(4,0,400);
	g4->SetParLimits(5,-1,400);
	g4->SetParLimits(6,0.01,500);
	g4->SetParLimits(7,0,1);
	g4->SetParLimits(8,0,1000000000);
	h_pmt4_int->Fit(g4,"R");
	
	TF1* f4 = new TF1("f4","[0]*TMath::Power(([1]/[2]),(x/[2]))*(TMath::Exp(-([1]/[2])))/TMath::Gamma((x/[2])+1)",30,70);
	f4->SetParameters(2000,50,3);
	f4->SetLineColor(kViolet-6);
	h_pmt4_int->Fit(f4,"R+");
	double yscale4 = f4->GetParameter(0);
	double mean4 = f4->GetParameter(1);
	double xscale4 = f4->GetParameter(2); // this is the calibration constant
	h_pmt4_int->SetTitle("PMT 4 Cerenkov Calibration Poisson Fit; Pulse Integral");
	auto h_pmt4_int_clone = h_pmt4_int->DrawClone();
	
	TF1* manyGaus4[Ngaus]; 
	for (int i = 0; i < Ngaus; i++)
        {
	    int b = i+1;
	    manyGaus4[i] = new TF1(Form("G2_%d",i+1), "[0]*([2]/([5]*[4]*TMath::Sqrt([5])))*TMath::Exp(-[2]-((x-[1]-[5]*[3])*(x-[1]-[5]*[3]))/(2*[5]*[4]*[4]))", 0, 150);
	    manyGaus4[i]->SetLineColor(kAzure-3);
	    manyGaus4[i]->SetParameter(0,g4->GetParameter(0));
	    manyGaus4[i]->SetParameter(1,g4->GetParameter(1) + (g4->GetParameter(7)/g4->GetParameter(3)));
	    manyGaus4[i]->SetParameter(2,g4->GetParameter(4));
	    manyGaus4[i]->SetParameter(3,g4->GetParameter(5));
	    manyGaus4[i]->SetParameter(4,g4->GetParameter(6));
	    manyGaus4[i]->SetParameter(5,b);
	    
	    manyGaus4[i]->Draw("Same");
	}
	
	c1->Print("pngcer_fit_1.pdf(");
	
	// Drawing Cerenkov position distribution histograms
	TCanvas* c2 = new TCanvas("c2", "Cerenkov Position Cuts", 1200, 1200);
	c2->Divide(2,2);

	c2->cd(1);
	h_pmt1_pos->SetTitle("PMT 1 Cerenkov Position Cuts; xAtCer; yAtCer");
	auto h_pmt1_pos_clone = h_pmt1_pos->DrawClone("COLZ");
	TLine *l1 = new TLine(xmin,ymin,xmax,ymin);
    l1->SetLineColor(kRed);
    l1->Draw();
    TLine *l2 = new TLine(xmin,ymax,xmax,ymax);
    l2->SetLineColor(kRed);
    l2->Draw();
    TLine *l3 = new TLine(xmin,ymin,xmin,ymax);
    l3->SetLineColor(kRed);
    l3->Draw();
    TLine *l4 = new TLine(xmax,ymin,xmax,ymax);
    l4->SetLineColor(kRed);
    l4->Draw();
    
	c2->cd(2);
	h_pmt2_pos->SetTitle("PMT 2 Cerenkov Position Cuts; xAtCer; yAtCer");
	auto h_pmt2_pos_clone = h_pmt2_pos->DrawClone("COLZ");
	TLine *l5 = new TLine(xmin,-ymin,xmax,-ymin);
    l5->SetLineColor(kRed);
    l5->Draw();
    TLine *l6 = new TLine(xmin,-ymax,xmax,-ymax);
    l6->SetLineColor(kRed);
    l6->Draw();
    TLine *l7 = new TLine(xmin,-ymin,xmin,-ymax);
    l7->SetLineColor(kRed);
    l7->Draw();
    TLine *l8 = new TLine(xmax,-ymin,xmax,-ymax);
    l8->SetLineColor(kRed);
    l8->Draw();
	
	c2->cd(3);
	h_pmt3_pos->SetTitle("PMT 3 Cerenkov Position Cuts; xAtCer; yAtCer");
	auto h_pmt3_pos_clone = h_pmt3_pos->DrawClone("COLZ");
	TLine *l9 = new TLine(-xmin,ymin,-xmax,ymin);
    l9->SetLineColor(kRed);
    l9->Draw();
    TLine *l10 = new TLine(-xmin,ymax,-xmax,ymax);
    l10->SetLineColor(kRed);
    l10->Draw();
    TLine *l11 = new TLine(-xmin,ymin,-xmin,ymax);
    l11->SetLineColor(kRed);
    l11->Draw();
    TLine *l12 = new TLine(-xmax,ymin,-xmax,ymax);
    l12->SetLineColor(kRed);
    l12->Draw();
	
	c2->cd(4);
	h_pmt4_pos->SetTitle("PMT 4 Cerenkov Position Cuts; xAtCer; yAtCer");
	auto h_pmt4_pos_clone = h_pmt4_pos->DrawClone("COLZ");
	TLine *l13 = new TLine(-xmin,-ymin,-xmax,-ymin);
    l13->SetLineColor(kRed);
    l13->Draw();
    TLine *l14 = new TLine(-xmin,-ymax,-xmax,-ymax);
    l14->SetLineColor(kRed);
    l14->Draw();
    TLine *l15 = new TLine(-xmin,-ymin,-xmin,-ymax);
    l15->SetLineColor(kRed);
    l15->Draw();
    TLine *l16 = new TLine(-xmax,-ymin,-xmax,-ymax);
    l16->SetLineColor(kRed);
    l16->Draw();
	
	c2->Print("pngcer_fit_1.pdf");
	
	// Drawing calorimeter distribution histogram
	TCanvas* c3 = new TCanvas("c3", "P.cal.etottracknorm Cuts", 1200, 1200);
	auto h_etottracknorm_clone = h_etottracknorm->DrawClone();
	c3->Update();
	TLine *l17 = new TLine(emin,0,emin,c3->GetUymax());
    l17->SetLineColor(kRed);
    l17->Draw();
    TLine *l18 = new TLine(emax,0,emax,c3->GetUymax());
    l18->SetLineColor(kRed);
    l18->Draw();

    c3->Print("pngcer_fit_1.pdf)");
	
	// Printing calibration constants to terminal
	std::cout << "1/PMT1 Calibration Constant: " << xscale1 << std::endl;
	std::cout << "1/PMT2 Calibration Constant: " << xscale2 << std::endl;
	std::cout << "1/PMT3 Calibration Constant: " << xscale3 << std::endl;
	std::cout << "1/PMT4 Calibration Constant: " << xscale4 << std::endl;
	
	return 0;
}
