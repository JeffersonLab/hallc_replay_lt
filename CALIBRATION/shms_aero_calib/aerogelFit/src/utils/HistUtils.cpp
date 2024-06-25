/*
 * HistUtils.cpp
 *
 *  Created on: Jul 28, 2020
 *      Author: petrstepanov
 */

#include "../utils/HistUtils.h"
#include "../model/Constants.h"
#include <TH1F.h>

HistUtils::HistUtils() {
	// TODO Auto-generated constructor stub

}

HistUtils::~HistUtils() {
	// TODO Auto-generated destructor stub
}

TH1* HistUtils::trimHistogram(TH1* hist){

	std::cout << hist->GetNbinsX() << std::endl;
	std::cout << hist->GetXaxis()->GetBinLowEdge(1) << std::endl;
	std::cout << hist->GetXaxis()->GetBinUpEdge(hist->GetNbinsX()) << std::endl;


	Int_t minBin = hist->FindFirstBinAbove(0);
	Int_t maxBin = hist->FindLastBinAbove(0);
	Int_t nBins = maxBin - minBin + 1;

	TAxis* xAxis = hist->GetXaxis();
	TString name = TString::Format("%s-trimmed", hist->GetName());
	TString title = TString::Format("%s Trimmed", hist->GetTitle());
	TH1F* trimmedHist = new TH1F(name, title, nBins, xAxis->GetBinLowEdge(minBin), xAxis->GetBinUpEdge(maxBin));

	for (Int_t i = 1; i <= nBins; i++){
		// Increase bin content certain number of times
		for (UInt_t c = 0; c<= hist->GetBinContent(i+minBin-1); c++){
			trimmedHist->AddBinContent(i);
		}

		// trimmedHist->SetBinContent(i, hist->GetBinContent(i+minBin-1));
		// trimmedHist->SetBinError(i, hist->GetBinError(i+minBin-1));
		std::cout << "bin: " << i << " content: " << trimmedHist->GetBinContent(i) << " error: " << trimmedHist->GetBinError(i) << std::endl;
	}

	return trimmedHist;
}

TList* HistUtils::trimHistogramList(TList* histograms, Double_t xMin, Double_t xMax){
	TList* histogramsTrimmed = new TList();
	for (TObject* object : *histograms){
		TH1* hist = (TH1F*)object;
		if (hist){
			Double_t chFitMin = Constants::getInstance()->parameters.chFitMin;
			Double_t chFitMax = Constants::getInstance()->parameters.chFitMax;
			TH1* trimmedHist = HistUtils::cutHistogram(hist, chFitMin, chFitMax);
			trimmedHist->Print();
			histogramsTrimmed->Add(trimmedHist);
		}
	}
	return histogramsTrimmed;
}

void HistUtils::rebinHistogramList(TList* histograms, Int_t nGroup){
	for (TObject* object : *histograms){
		TH1* hist = (TH1F*)object;
		if (hist) hist->Rebin(nGroup);
	}
}

TH1* HistUtils::cutHistogram(TH1* hist, Double_t xMin, Double_t xMax){
	Int_t minBin = hist->GetXaxis()->FindBin(xMin);
	Int_t maxBin = hist->GetXaxis()->FindBin(xMax);

	Int_t nBins = maxBin - minBin + 1;

	TAxis* xAxis = hist->GetXaxis();
	TString name = TString::Format("%s-trimmed", hist->GetName());
	// TString title = TString::Format("%s (trimmed)", hist->GetTitle());
	TH1D* trimmedHist = new TH1D(name, hist->GetTitle(), nBins, xAxis->GetBinLowEdge(minBin), xAxis->GetBinUpEdge(maxBin));
	trimmedHist->GetXaxis()->SetTitle(hist->GetXaxis()->GetTitle());
	trimmedHist->GetYaxis()->SetTitle(hist->GetYaxis()->GetTitle());

	for (Int_t i = 1; i <= nBins; i++){
		trimmedHist->SetBinContent(i, hist->GetBinContent(i+minBin-1));
		// trimmedHist->SetBinError(i, hist->GetBinError(i+minBin-1));
		// std::cout << "bin: " << i << " content: " << trimmedHist->GetBinContent(i) << " error: " << trimmedHist->GetBinError(i) << std::endl;
	}

	trimmedHist->SetEntries(trimmedHist->Integral());

	return trimmedHist;
}

TH1* HistUtils::cloneHistogram(TH1* hist, const char* newName, const char* title){
	const char* newTitle = title!=0 ? title : hist->GetTitle();

//	Int_t nBins = hist->GetXaxis()->GetNbins();
//	Int_t xMin =  hist->GetXaxis()->GetXmin();
//	Int_t xMax =  hist->GetXaxis()->GetXmax();
//
//	TH1* histClone = new TH1F(newName, newTitle, nBins, xMin, xMax);
//	for (Int_t i = 1; i <= hist->GetXaxis()->GetNbins(); i++){
//		histClone->SetBinContent(i, hist->GetBinContent(i));
//	}
//

	TH1* histClone = (TH1*)hist->Clone(newName);
	histClone->GetXaxis()->SetTitle(hist->GetXaxis()->GetTitle());
	histClone->GetYaxis()->SetTitle(hist->GetYaxis()->GetTitle());

	return histClone;
}

Int_t HistUtils::getNNonZeroBins(TH1* hist){
	Int_t nonZeroBins = 0;
	for (Int_t i = 1; i <= hist->GetNbinsX(); i++){
		if (hist->GetBinContent(i) != 0) nonZeroBins++;
	}
	return nonZeroBins;
}

void HistUtils::resetHistogram(TH1* hist){
	for (Int_t i = 1; i <= hist->GetNbinsX(); i++){
		hist->SetBinContent(i, 0);
		hist->SetBinError(i, 0);
	}
}

void HistUtils::normalizeHistogram(TH1* hist){
	Double_t integral = hist->Integral();
	for (Int_t i = 1; i <= hist->GetNbinsX(); i++){
		hist->SetBinContent(i, hist->GetBinContent(i)/integral);
	}
}

void HistUtils::removeHistogramZeros(TH1* hist){
	for (Int_t i = 1; i <= hist->GetNbinsX(); i++){
		if (hist->GetBinContent(i)==0){
			hist->SetBinContent(i, 1E-9);
		}
	};
}

void HistUtils::increaseCorrespondingBinContent(TH1* hist, Float_t val){
	Int_t bin = hist->GetXaxis()->FindBin(val);
	if (bin >= 1 && bin <= hist->GetNbinsX()){
		Float_t content = hist->GetBinContent(bin);
		hist->SetBinContent(bin, ++content);
	}
}

Chi2Struct HistUtils::getChi2(TH1* hist, RooCurve* curve, RooAbsPdf* model){
	// https://en.wikipedia.org/wiki/Goodness_of_fit
	Int_t degreesOfFreedom = 0;
	Double_t chiSum = 0;
	for (int i = 1; i <= hist->GetXaxis()->GetNbins(); i++){
		Double_t value = hist->GetBinContent(i);
		Double_t fit = curve->Eval(hist->GetXaxis()->GetBinCenter(i));
		Double_t error = hist->GetBinError(i);
		if (value != 0 && error != 0){
			// std::cout << "value: " << value << " fit: " << fit << "  error: " << error << std::endl;
			chiSum += pow(value - fit, 2) / value;
			degreesOfFreedom++;
		}
	}
	// Subtract number of free parameters + 1
	degreesOfFreedom -= (model->getVariables()->getSize() + 1);

	Chi2Struct chi2Struct = {chiSum, degreesOfFreedom, chiSum / (Double_t)(degreesOfFreedom)};

	//	Double_t chi2Err = TMath::Sqrt((Double_t)2 * freeParameters) / degreesFreedom;
	return chi2Struct;
}
