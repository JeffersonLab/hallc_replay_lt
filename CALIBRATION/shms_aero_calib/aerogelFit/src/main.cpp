#ifndef __CINT__
#include <RooGlobalFunc.h>
#endif

#include <iostream>
#include <TApplication.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TObjString.h>
#include <TStopwatch.h>
#include <TSystem.h>

#include <Math/Factory.h>
#include <Math/Minimizer.h>
#include <Math/MinimizerOptions.h>
#include "model/Constants.h"
#include "model/FitParameters.h"
#include "utils/GraphicsUtils.h"
#include "utils/TreeUtils.h"
#include "utils/HistUtils.h"
#include <Math/IntegratorOptions.h>

#include "utils/TestSpectrum.h"
#include "utils/FitUtils.h"
#include "utils/StringUtils.h"
#include "utils/RootUtils.h"
#include "helper/TreeHelper.h"
#include "helper/BeamHelper.h"
#include "helper/BeamOutputHelper.h"
#include "fit/FuncSReal.h"
#include "fit/FuncSRealFFT.h"
#include "fit/FuncSRealNoTerm0.h"
#include "fit/FuncSRealFFTNoTerm0.h"

int runPrototype(TList* fileNamesList){
	// Initialize the tree from merged files
	TreeHelper::getInstance()->init(fileNamesList);

	// Plot the Tree if --plot-tree=kTRUE command line argument was passed
	if (Constants::getInstance()->parameters.plotTree == kTRUE){
		// for(TObject* object : *fileNamesList){
			// TObjString* fileName = (TObjString*) object;
			TreeHelper::getInstance()->plotTree();
		// }
	}

	// Prepare histograms for the PMT projection spectra
	Int_t chMin = Constants::getInstance()->parameters.chMin;
	Int_t chMax = Constants::getInstance()->parameters.chMax;
	Int_t chBins = Constants::getInstance()->parameters.chBins;
	TString pmt1HistTitle = TString::Format("ADC1 spectrum at tilel=%d, tiler>0", Constants::getInstance()->parameters.tileProfile);
	TH1* pmt1Hist = new TH1D("adc1Hist", pmt1HistTitle, chBins, chMin, chMax);
  pmt1Hist->GetXaxis()->SetTitle("ADC1 channel (ch_1)");
  pmt1Hist->GetYaxis()->SetTitle("Number of events");
  TString pmt2HistTitle = TString::Format("ADC2 spectrum at tilel=%d, tiler>0", Constants::getInstance()->parameters.tileProfile);
	TH1* pmt2Hist = new TH1D("adc2Hist", pmt2HistTitle, chBins, chMin, chMax);
	pmt2Hist->GetXaxis()->SetTitle("ADC2 channel (ch_2)");
	pmt2Hist->GetYaxis()->SetTitle("Number of events");

	// Fill PMT histograms from the Tree data
	TreeHelper::getInstance()->fillPmtHists(pmt1Hist, pmt2Hist);

	// Plot PMT profile spectra if needed
	// const char* fileURL = TreeHelper::getInstance()->getFileName();
	// const char* fileNameNoExt = StringUtils::extractFilenameNoExtension(fileURL)->Data();
	// const char* fileNameNoExt = TreeHelper::getInstance()->getFileName();
	if (Constants::getInstance()->parameters.plotProfiles == kTRUE){
		TString pmtsCanvasTitle = TString::Format("Profile of the PMT spectra (tilel = %d, tiler > 0)", Constants::getInstance()->parameters.tileProfile);
		TCanvas* pmtsCanvas = new TCanvas("pmtsCanvas", pmtsCanvasTitle.Data(), 1024, 512);
		pmtsCanvas->Divide(2,1);

		TVirtualPad* pmtsCanvasPad1 = pmtsCanvas->cd(1);
		// pmtsCanvasPad1->SetLogy();
		pmtsCanvasPad1->SetGrid();
		pmt1Hist->SetFillColor(EColor::kCyan-10);
		TH1* pmt1HistClone = dynamic_cast<TH1F*>(pmt1Hist->DrawClone());

		TVirtualPad* pmtsCanvasPad2 = pmtsCanvas->cd(2);
		// pmtsCanvasPad2->SetLogy();
    pmtsCanvasPad2->SetGrid();
    pmt2Hist->SetFillColor(EColor::kCyan-10);
		TH1* pmt2HistClone = dynamic_cast<TH1F*>(pmt2Hist->DrawClone());

		GraphicsUtils::alignStats(pmtsCanvasPad1);
		GraphicsUtils::alignStats(pmtsCanvasPad2);

		// Save canvas with PMT profiles to file

		TString pngFilePath = TString::Format("%s-profiles-tile%d.png", TreeHelper::getInstance()->getFileName(), Constants::getInstance()->parameters.tileProfile);
		pmtsCanvas->SaveAs(pngFilePath.Data());
	}

	// Fit and plot PMT spectra
	FitType fitType = Constants::getInstance()->parameters.fitType;
	const char* fitKind = FitUtils::getFitDescription(fitType);
	if (fitType == FitType::none) return 0;

	// Trim PMT spectra to remove zero bin noise
	// Select min channel value to skip the stretched noise bin
	// Int_t chMinVal = 1 * (Constants::CH_MAX_VAL - Constants::CH_MIN_VAL) / Constants::CH_BINS + 5;
	// chMinVal = 150;
	Int_t chFitMin = Constants::getInstance()->parameters.chFitMin;
	Int_t chFitMax = Constants::getInstance()->parameters.chFitMax;
	TH1* pmt1HistFit = HistUtils::cutHistogram(pmt1Hist, chFitMin, chFitMax);
	TH1* pmt2HistFit = HistUtils::cutHistogram(pmt2Hist, chFitMin, chFitMax);

	TString pmtsFitCanvasTitle = TString::Format("%s of the PMT profile spectra (tilel = %d, tiler > 0, terms = %d)", fitKind, Constants::getInstance()->parameters.tileProfile, Constants::getInstance()->parameters.termsNumber);
	TCanvas* pmtsFitCanvas = new TCanvas("pmtsFitCanvas", pmtsFitCanvasTitle.Data(), 1024, 512);
	pmtsFitCanvas->Divide(2,1);

	// Retreive parameters for KaonLT Prototype histogram
	TString* parametersFileName = new TString(TreeHelper::getInstance()->getFileName()); // TreStringUtils::extractFilenameWithExtension(fileURL);
	parametersFileName->Append("-params.txt");
	FitParameters* params = new FitParameters(parametersFileName->Data());
	if (params->getList()->getSize() != 7){
		std::cout << "Missing or incomplete fit parameters file \"" << parametersFileName->Data() << "\"" << std::endl;
		return 1;
	}

	// Perform fit of the first PMT histogram
	FitUtils::estimateFitParameters(pmt1HistFit, params);
	FitUtils::fitHistogramOnPad(pmt1HistFit, pmtsFitCanvas->cd(1), params, fitType);

	// Reset parameters and fit second PMT histogram
	params->readParametersFromFile();
	FitUtils::estimateFitParameters(pmt2HistFit, params);
	FitUtils::fitHistogramOnPad(pmt2HistFit, pmtsFitCanvas->cd(2), params, fitType);

	// Save canvas with PMT profiles to file
	TString pngFitFilePath = TString::Format("%s-fit-tile%d-terms%d-%s.png", TreeHelper::getInstance()->getFileName(), Constants::getInstance()->parameters.tileProfile, Constants::getInstance()->parameters.termsNumber, StringUtils::toString(fitType));
	pmtsFitCanvas->SaveAs(pngFitFilePath.Data());

	// Return success (0)
	return 0;
}

int runBeamSingle(const char* fileNamePath){
	// If input file contains the beam data
	BeamHelper* beamHelper = new BeamHelper(fileNamePath);

	// Trim histograms
	TList* histogramsPos = beamHelper->getHistogramsPositive();
	TList* histogramsPosTrimmed = HistUtils::trimHistogramList(histogramsPos, Constants::getInstance()->parameters.chFitMin, Constants::getInstance()->parameters.chFitMax);
	HistUtils::rebinHistogramList(histogramsPosTrimmed, 2);
	TList* histogramsNeg = beamHelper->getHistogramsNegative();
	TList* histogramsNegTrimmed = HistUtils::trimHistogramList(histogramsNeg, Constants::getInstance()->parameters.chFitMin, Constants::getInstance()->parameters.chFitMax);
	HistUtils::rebinHistogramList(histogramsNegTrimmed, 2);

	// Determine fit type
	FitType fitType = Constants::getInstance()->parameters.fitType;
	const char* fitKind = FitUtils::getFitDescription(fitType);

	// Plot spectra for Positive and Negative PMTs
	const char* fileURL = beamHelper->getFileName();
	const char* fileNameNoExt = StringUtils::extractFilenameNoExtension(fileURL)->Data();
	if (Constants::getInstance()->parameters.plotProfiles == kTRUE){
		TCanvas* beamCanvasPos = GraphicsUtils::getCanvasForNPads("beamCanvasPos", "Beam PMT Positive spectra", 1280, 640, histogramsPosTrimmed->LastIndex()+1, 3);
		for (UInt_t i = 0; i <= histogramsPosTrimmed->LastIndex(); i++){
			TH1* hist = (TH1*)histogramsPosTrimmed->At(i);
			if (hist){
				TVirtualPad* pad = beamCanvasPos->cd(i+1);
				hist->SetTitle(hist->GetName());
				hist->DrawClone();
			}
		}
		BeamOutputHelper::getInstance()->writeObjectToRootFile(beamCanvasPos);
		TString beamCanvasPosPath = TString::Format("%s-pos-profiles-tile%d.png", fileNameNoExt, Constants::getInstance()->parameters.tileProfile);
		beamCanvasPos->SaveAs(beamCanvasPosPath.Data());

		TCanvas* beamCanvasNeg= GraphicsUtils::getCanvasForNPads("beamCanvasNeg", "Beam PMT Negative spectra", 1280, 640, histogramsNegTrimmed->LastIndex()+1, 3);
		for (UInt_t i = 0; i <= histogramsNegTrimmed->LastIndex(); i++){
			TH1* hist = (TH1*)histogramsNegTrimmed->At(i);
			if (hist){
				TVirtualPad* pad = beamCanvasNeg->cd(i+1);
				hist->SetTitle(hist->GetName());
				hist->DrawClone();
			}
		}
		BeamOutputHelper::getInstance()->writeObjectToRootFile(beamCanvasNeg);
		TString beamCanvasNegPath = TString::Format("%s-neg-profiles-tile%d.png", fileNameNoExt, Constants::getInstance()->parameters.tileProfile);
		beamCanvasNeg->SaveAs(beamCanvasNegPath.Data());
	}

	if (fitType == FitType::none) return 1;

	// Retreive parameters for KaonLT Prototype histogram
	TString* parametersFileName = StringUtils::extractFilenameWithExtension(fileURL);
	parametersFileName->ReplaceAll(".root", "-params.txt");
	FitParameters* params = new FitParameters(parametersFileName->Data());
	if (params->getList()->getSize() != 7){
		std::cout << "Missing or incomplete fit parameters file \"" << parametersFileName->Data() << "\"" << std::endl;
		return 1;
	}

	// Check if histogram is empty (some beam data is empty, this crashes the program)
	TH1* hist = (TH1F*)(histogramsPosTrimmed->At(0));
	if (hist->Integral() == 0){
		return 1;
	}

	// Write output file name and file run index
	const char* fileName = StringUtils::extractFilenameWithExtension(fileNamePath)->Data();
	BeamOutputHelper::getInstance()->writeToAscii(fileName);
	Int_t fileIndex = StringUtils::extractFileIndex(fileNamePath);
	BeamOutputHelper::getInstance()->writeToAscii(fileIndex);

	// Fit and plot Positive histograms
	TString beamFitCanvasPosName = TString::Format("%s-pos-fit", fileNameNoExt);
	TString beamFitCanvasPosTitle = TString::Format("\"%s\" %s of the beam PMT Positive spectra (terms = %d)", fileName, fitKind, Constants::getInstance()->parameters.termsNumber);
	TCanvas* beamFitCanvasPos = GraphicsUtils::getCanvasForNPads(beamFitCanvasPosName.Data(), beamFitCanvasPosTitle.Data(), GraphicsUtils::BEAM_CANVAS_WIDTH, GraphicsUtils::BEAM_CANVAS_HEIGHT, histogramsPosTrimmed->LastIndex()+1, 3);
	for (UInt_t i = 0; i <= histogramsPosTrimmed->LastIndex(); i++){
		TH1* hist = (TH1*)histogramsPosTrimmed->At(i);
		if (hist){
			hist->SetTitle(hist->GetName());
			// Instantiate fresh parameter values
			params->readParametersFromFile();
			// Estimate fitting parameters if requested
			if (Constants::getInstance()->parameters.paramDeviation != 0){
				FitUtils::estimateFitParameters(hist, params);
			}
			TVirtualPad* pad = beamFitCanvasPos->cd(i+1);
			Double_t chi2 = FitUtils::fitHistogramOnPad(hist, pad, params, fitType);
			// Write fitted parameter values and errors to output file
			BeamOutputHelper::getInstance()->writeToAscii(params);
			// Write chi2 to output file
			BeamOutputHelper::getInstance()->writeToAscii(chi2);
		}
	}
	// Save canvas to RootFile and to png
	BeamOutputHelper::getInstance()->writeObjectToRootFile(beamFitCanvasPos);
	TString beamFitCanvasPosPath = TString::Format("%s-pos-fit-tile%d-terms%d-%s.png", fileNameNoExt, Constants::getInstance()->parameters.tileProfile, Constants::getInstance()->parameters.termsNumber, StringUtils::toString(fitType));
	beamFitCanvasPos->SaveAs(beamFitCanvasPosPath.Data());

	// Fit and plot Negative histograms
	TString beamFitCanvasNegName = TString::Format("%s-neg-fit", fileNameNoExt);
	TString beamFitCanvasNegTitle = TString::Format("\"%s\" %s of the beam PMT Negative spectra (terms = %d)", fileName, fitKind, Constants::getInstance()->parameters.termsNumber);
	TCanvas* beamFitCanvasNeg = GraphicsUtils::getCanvasForNPads(beamFitCanvasNegName.Data(), beamFitCanvasNegTitle.Data(), GraphicsUtils::BEAM_CANVAS_WIDTH, GraphicsUtils::BEAM_CANVAS_HEIGHT, histogramsNegTrimmed->LastIndex()+1, 3);
	for (UInt_t i = 0; i <= histogramsNegTrimmed->LastIndex(); i++){
		TH1* hist = (TH1*)histogramsNegTrimmed->At(i);
		if (hist){
			hist->SetTitle(hist->GetName());
			// Instantiate fresh parameter values
			params->readParametersFromFile();
			// Estimate fitting parameters if requested
			if (Constants::getInstance()->parameters.paramDeviation != 0){
				FitUtils::estimateFitParameters(hist, params);
			}
			TVirtualPad* pad = beamFitCanvasNeg->cd(i+1);
			Double_t chi2 = FitUtils::fitHistogramOnPad(hist, pad, params, fitType);
			// Write fitted parameter values and errors to output file
			BeamOutputHelper::getInstance()->writeToAscii(params);
			// Write chi2 to output file
			BeamOutputHelper::getInstance()->writeToAscii(chi2);
		}
	}

	// Save canvas to RootFile and to png
	BeamOutputHelper::getInstance()->writeObjectToRootFile(beamFitCanvasNeg);
	TString beamFitCanvasNegPath = TString::Format("%s-neg-fit-tile%d-terms%d-%s.png", fileNameNoExt, Constants::getInstance()->parameters.tileProfile, Constants::getInstance()->parameters.termsNumber, StringUtils::toString(fitType));
	beamFitCanvasNeg->SaveAs(beamFitCanvasNegPath.Data());

	// Write new line to output file
	BeamOutputHelper::getInstance()->writeToAsciiNoIndent("\n");

	return 0;
}

int runBeam(TList* fileNamesList){
	// Open ASCII and ROOT files for output
	BeamOutputHelper::getInstance()->init();

	// Run analysis for every file
	for (TObject* object : *fileNamesList){
		TObjString* fileName = (TObjString*) object;
		if (fileName){
			runBeamSingle(fileName->GetString().Data());
		}
	}

	// Close output files
	BeamOutputHelper::getInstance()->finalize();

	return 0;
}

int run(TList* fileNamesList) {
	const char* firstFileName = ((TObjString*)fileNamesList->At(0))->GetString().Data();
	InputFileType fileType = RootUtils::getInputFileType(firstFileName);

	if (fileType == InputFileType::Prototype){
		return runPrototype(fileNamesList);
	}
	if (fileType == InputFileType::Beam){
		return runBeam(fileNamesList);
	}
	return 1;
}

// Test fit histogram digitized from the paper
int testDigitized(){
	// Get digitized histogram from paper
	// TH1* h = TestSpectrum::getHistogramPaper();
	TH1* h = TestSpectrum::getHistogramDigitized();

	h->Print();
	for (Int_t i = 1; i <= h->GetXaxis()->GetNbins(); i++){
	  std::cout << h->GetBinCenter(i) << ": " << h->GetBinContent(i) << std::endl;
	}
	// Retreive parameters for test Bellamy histogram
	FitParameters* params = new FitParameters(ParametersType::forBellamyHist);

	// Instantiate fitting function object
	AbsComponentFunc* funcObject = new FuncSReal(h);

	FitUtils::doFit(h, params, funcObject);
	return 0;
}

// Test fit histogram filled from the fitting function from the paper
int testFillRandom(){
	// Retreive parameters for test Bellamy histogram
	FitParameters* params = new FitParameters(ParametersType::forBellamyHist);

	// Instantiate histogram
	// TH1* h = TestSpectrum::getHistogramPaperFix();
	TH1* h = TestSpectrum::getHistogramGenerated(params);

	// Fit histogram with ROOT Fit
	TH1* hist1 = HistUtils::cloneHistogram(h, "hist");
	AbsComponentFunc* funcObject = new FuncSReal(hist1);
	FitUtils::doFit(hist1, params, funcObject);

	// Fit histogram with ROOT Fit with Convolution
	TH1* hist2 = HistUtils::cloneHistogram(h, "hist_conv");
	AbsComponentFunc* funcObjectFFT = new FuncSRealFFT(hist2);
	FitUtils::doFit(hist2, params, funcObjectFFT);

	// Fit histogram with RooFit with Convolution
	TH1* hist3 = HistUtils::cloneHistogram(h, "hist_conv_roofit");
	FitUtils::doRooFit(hist3, params, kTRUE);

	return 0;
}

int testNoTerm0(){
	// Retreive parameters for test Bellamy histogram
	FitParameters* params = new FitParameters(ParametersType::forBellamyHist);

	// Fix sigma_0
	RooRealVar* s0 = (RooRealVar*) params->getList()->find("#sigma_{0}");
	s0->setVal(0.32);
	s0->setConstant();

	// Instantiate histogram
	TH1* h = TestSpectrum::getHistogramGeneratedNoTerm0(params);

	// Fit histogram with ROOT Fit
	TH1* hist1 = HistUtils::cloneHistogram(h, "hist_no_term0");
	AbsComponentFunc* funcObject = new FuncSRealNoTerm0(hist1);
	FitUtils::doFit(hist1, params, funcObject);

	// Fit histogram with ROOT Fit with Convolution
	TH1* hist2 = HistUtils::cloneHistogram(h, "hist_no_term0_conv");
	AbsComponentFunc* funcObjectFFT = new FuncSRealFFTNoTerm0(hist2);
	FitUtils::doFit(hist2, params, funcObjectFFT);

	// Fit histogram with RooFit with Convolution
	TH1* hist3 = HistUtils::cloneHistogram(h, "hist_no_term0_conv_roofit");
	FitUtils::doRooFit(hist3, params, kFALSE);

	return 0;
}

int main(int argc, char* argv[]) {
	// Create ROOT application
	// https://github.com/root-project/root/blob/master/tutorials/gui/mditest.C#L409
	TApplication* app = new TApplication(Constants::APPLICATION_NAME, &argc, argv);
	gROOT->SetBatch(kTRUE);
	// Parse command-line parameters
	// TApplication::TApplication() modifies the original list of parameters
	// Need to use ROOT's gApplication->Argc() and gApplication->Argv();
	Constants* constants = Constants::getInstance();
	constants->parseParameters(gApplication->Argc(), gApplication->Argv());

	// Warning in <TF1::IntegralOneDim>: Error found in integrating function term11_1714168353 in [10.000000,2010.000000] using AdaptiveSingular. Result = 3818596.214063 +/- 453.771721  - status = 18
	// Info in <TF1::IntegralOneDim>: 		Function Parameters = { p0 =  220.198026 , p1 =  0.044300 , p2 =  165.000000 , p3 =  63.506987 , p4 =  0.700397 , p5 =  0.027247 , p6 =  0.500000 }
	// ROOT::Math::IntegratorOneDimOptions::SetDefaultRelTolerance(1.E-4);

	if (Constants::getInstance()->parameters.fitType == FitType::test){
		// Test fitting function on the digitized test histogram
		testDigitized();
		// Test fitting function on the filled random test histogram
		// testFillRandom();
		// testNoTerm0();
	}
	else {
    // Parse wildcards in the input files
    RootUtils::parseWildcardFileNames(constants->parameters.inputFiles);

    // Sort filenames
    constants->parameters.inputFiles->Sort(kFALSE);

		// Check if input files are provided
		if (constants->parameters.inputFiles->GetSize() < 1){
			std::cout << "No spectra files specified." << std::endl;
			return 1;
		}

		// NOTE: ROOT default "kADAPTIVESINGULAR" integrator crashes when integrating FuncSRealNoTerm0...?
		// Even when we are not fitting at all, just drawing the function and its components
		// ROOT::Math::IntegratorOneDimOptions::SetDefaultIntegrator("GAUSSLEGENDRE");

		// TF1 integral for FuncSReal not matches TH1 integral...
		// ROOT::Math::IntegratorOneDimOptions::SetDefaultAbsTolerance(1E-3);
		// ROOT::Math::IntegratorOneDimOptions::SetDefaultRelTolerance(1E-3);
		// ROOT::Math::IntegratorOneDimOptions::SetDefaultIntegrator("Gauss");
		// ROOT::Math::IntegratorOneDimOptions::SetDefaultNPoints(n);

		// ROOT::Math::MinimizerOptions::SetDefaultMinimizer("FUMILI");
		// ROOT::Math::MinimizerOptions::SetDefaultTolerance(1.E-4);

		// Abnormal termination of minimization
		ROOT::Math::MinimizerOptions::SetDefaultTolerance(1); // Default: 1.E-2
		ROOT::Math::MinimizerOptions::SetDefaultMaxFunctionCalls(100000);
		// ROOT::Math::MinimizerOptions::SetDefaultMaxFunctionCalls(2147483647);

		// ROOT::Math::MinimizerOptions::SetDefaultMinimizer("Minuit", "Migrad"); // Default
		// ROOT::Math::MinimizerOptions::SetDefaultMinimizer("Minuit", "Simplex");

		// The probelm was that MIGRAD was unable to do a correct error estimates for 60 parameters although it was displaying a perfect fit. With Minosit takes more time but it does a good error estimate.

		// ROOT::Math::IntegratorOneDimOptions:: ROOT::Math::Integrator GSLIntegrator(double absTol = 1.0000000000000001E-9, double relTol = 9.9999999999999995E-7, size_t size = 1000)

		// Run analysis
		run(constants->parameters.inputFiles);
	}

	app->Run();
	return 0;
}
