/*
 * GraphicsUtils.cpp
 *
 *  Created on: Jul 30, 2020
 *      Author: petrstepanov
 */

#include <TPaveStats.h>
#include <TLatex.h>
#include <TSystem.h>
#include <TDatime.h>
#include <TH1.h>
#include "../utils/GraphicsUtils.h"
#include "../utils/StringUtils.h"

GraphicsUtils::GraphicsUtils() {
}

GraphicsUtils::~GraphicsUtils() {
}

const Double_t GraphicsUtils::TEXT_SIZE_NORMAL = 0.03;
const Double_t GraphicsUtils::TEXT_SIZE_SMALL = TEXT_SIZE_NORMAL*0.75;
const Double_t GraphicsUtils::TEXT_SIZE_SMALLER = TEXT_SIZE_SMALL*0.75;

const Double_t GraphicsUtils::LINE_HEIGHT_NORMAL = 0.045;
const Double_t GraphicsUtils::LINE_HEIGHT_SMALL = LINE_HEIGHT_NORMAL*0.75;

const Int_t GraphicsUtils::FONT_REGULAR = 4;
const Int_t GraphicsUtils::FONT_BOLD = 6;

const Double_t GraphicsUtils::TOP_TO_BOTTOM_PAD_HEIGHT_RATIO = 2.5;

const Int_t GraphicsUtils::BEAM_CANVAS_WIDTH = 1440;
const Int_t GraphicsUtils::BEAM_CANVAS_HEIGHT = 900;


const Margin GraphicsUtils::padMargins = { 0.10, 0.02, 0.15, 0.05 }; // left, right, bottom, top

const std::vector<Int_t> GraphicsUtils::colorSet = { kViolet + 6, kSpring - 5, kAzure + 8,
		kPink + 1, kGray + 1, kViolet - 4, kRed - 7, kOrange};

TPaveStats* GraphicsUtils::getPaveStats(TVirtualPad* pad){
  // Update Pad - in case the histogram was just drawn - need to update
  pad->Update();

  // pad->GetListOfPrimitives()->Print();
  // If previously renamed PaveStats and added to the pad primitives - return it
  TPaveStats *pave = (TPaveStats*)pad->GetPrimitive("mystats");
  if (pave) return pave;

  // Else remove PaveText from histogram primitives, rename it and add to the list of Pad primitives
  // pad0->getPrimitive() searches across primitives of primitives
  pave = (TPaveStats*)pad->GetPrimitive("stats");

  if (pave){
    pave->SetName("mystats");
    TH1* parentHist = (TH1*)(pave->GetParent());
    parentHist->SetStats(0);
    pad->GetListOfPrimitives()->Add(pave);
    // pad->GetListOfPrimitives()->Print();
    return pave;
  }

  // If not found search object by file type
  // for (TObject* object : *(pad->GetListOfPrimitives())){
  //  std::cout << object->GetName() << std::endl;
  //  if (object->InheritsFrom(TPaveStats::Class())){
  //    return (TPaveStats*) object;
  //  }
  // }

  return NULL;
}

void GraphicsUtils::setStatsFitOption(TH1* hist, TVirtualPad* pad, Int_t num){
	pad->Update();
	TPaveStats *stats = (TPaveStats*) hist->FindObject("stats");

	if (stats){
		stats->SetOptFit(num);
	}
}

Double_t GraphicsUtils::statsLineHeight = 0.05;

void GraphicsUtils::alignStats(TVirtualPad* pad, Double_t statsWidth){
  // Retrieve the stat box
  TPaveStats *stats = getPaveStats(pad);
  if (!stats) return;

  //stats->GetX2NDC() - stats->GetX1NDC();
  Double_t statsHeight = statsLineHeight*stats->GetListOfLines()->GetSize(); // stats->GetY2NDC() - stats->GetY1NDC();
  // Move stats horizontally
  stats->SetX2NDC(1 - pad->GetRightMargin());
  stats->SetX1NDC(stats->GetX2NDC() - statsWidth);
  // Move stats vertically
  stats->SetY2NDC(1 - pad->GetTopMargin());
  stats->SetY1NDC(stats->GetY2NDC() - statsHeight);

  pad->Modified();
  pad->Update();
}


void GraphicsUtils::stylePaveText(TPaveText* paveText, TVirtualPad* pad){
	// Use smaller text size
	paveText->SetTextSize(0.03);

	// Align top right corner with the pad margin
	Double_t newX2 = 1.0-pad->GetRightMargin(); // Align right end
	Double_t newY2 = 1.0-pad->GetTopMargin();  // Align top end
	paveText->SetOption("NDC");
	paveText->SetX2NDC(newX2);
	paveText->SetY2NDC(newY2);
	paveText->Draw("NDC");

}

//void GraphicsUtils::addLineToStats(TH1* hist, const char* string, TVirtualPad* pad){
//	pad->Modified();
//	pad->Update();
//	TPaveStats *stats = (TPaveStats*)pad->GetPrimitive("stats");
//	// TPaveStats *stats = (TPaveStats*) hist->FindObject("stats");
//	if (stats){
//		stats->SetName("mystats");
//		TLatex *text = new TLatex(0, 0, string);
//		// text->SetTextFont(42);
//		// text->SetTextSize(0.04);
//		stats->GetListOfLines()->Add(text);
//	}
//	// Avoid the the automatic redrawing of stats
//	hist->SetStats(0);
//	pad->Modified();
//	pad->Update();
//}
//
//void GraphicsUtils::showChi2InStats(TH1* hist, TFitResultPtr fitResultPtr, TVirtualPad* pad){
//	TString string = TString::Format("\\chi^2 = %f", fitResultPtr->Chi2());
//	addLineToStats(hist, string.Data(), pad);
//}

void GraphicsUtils::styleAxis(TAxis* axis, const char* title, Double_t titleOffset, Double_t labelOffset, Bool_t isTopPad){
    Style_t fontCode = getFontCode(FONT_REGULAR);

    axis->SetLabelFont(fontCode);
    axis->SetLabelOffset(labelOffset);
    axis->SetLabelSize(TEXT_SIZE_SMALL*getFontSizeScale(isTopPad));

    axis->SetTitleFont(fontCode);
    axis->SetTitleOffset(titleOffset);
    axis->SetTitleSize(TEXT_SIZE_NORMAL*getFontSizeScale(isTopPad));

    axis->CenterTitle(kTRUE);
    axis->SetTitle(title);
}

Style_t GraphicsUtils::getFontCode(Int_t fontNumber){
    // https://root.cern.ch/doc/master/classTAttText.html#T5
	Int_t precision = 2;  // if "1" then problems rendering
	return fontNumber * 10 + precision;
}

Double_t GraphicsUtils::getFontSizeScale(Bool_t isTopPad){
	if (isTopPad){
		Double_t scale = 1/(TOP_TO_BOTTOM_PAD_HEIGHT_RATIO/(TOP_TO_BOTTOM_PAD_HEIGHT_RATIO+1));
		return scale;
	}
	Double_t scale = 1/(1/(TOP_TO_BOTTOM_PAD_HEIGHT_RATIO+1));
	return scale;
}

void GraphicsUtils::addLineToPave(TVirtualPad* pad, RooAbsPdf* pdf, const char* line){
	TString paveTextName = TString::Format("%s_paramBox", pdf->GetName());
	TPaveText* paveText = (TPaveText*)pad->GetListOfPrimitives()->FindObject(paveTextName.Data());
	paveText->AddText(line);
	paveText->SetTextSize(0.03);
}

TCanvas* GraphicsUtils::getCanvasForNPads(const char* title, Int_t width, Int_t height, Int_t nPads, Int_t nCols){
	// Wait for the unique timestamp
	gSystem->Sleep(1000);
	TDatime* timestamp = new TDatime();
	TString name = TString::Format("canvas_%d", timestamp->Get());
	return getCanvasForNPads(name.Data(), title, width, height, nPads, nCols);
}

TCanvas* GraphicsUtils::getCanvasForNPads(const char* name, const char* title, Int_t width, Int_t height, Int_t nPads, Int_t nCols){
	TCanvas* canvas = new TCanvas(name, title, width, height);
	UInt_t nPadsTotal = nPads % nCols == 0 ?	nPads : nPads + nCols - nPads%nCols;
	canvas->Divide(nCols, nPadsTotal/nCols);
	return canvas;
}

void GraphicsUtils::hilightLimitParameters(TF1* func, TVirtualPad* pad){
	// Retrieve the stat box
	TPaveStats *paveStats = getPaveStats(pad);

	if (paveStats){
		for (Int_t i = 0; i < func->GetNpar(); i++){
			Double_t value = func->GetParameter(i);
			Double_t error = func->GetParError(i);
			Double_t min=0;
			Double_t max=0;
			func->GetParLimits(i, min, max);
			if (value-error < min || value+error > max){
				TText *text = paveStats->GetLineWith(func->GetParName(i));
				if (text) text->SetTextColor(kRed);
				TString newTitle = TString::Format("%s (at %s)", text->GetTitle(), value-error <= min ? "min" : "max");
				text->SetTitle(newTitle.Data());
			}
			if (min == max){
				TText *text = paveStats->GetLineWith(func->GetParName(i));
				TString newTitle = TString::Format("%s (fixed)", text->GetTitle());
				text->SetTitle(newTitle.Data());
			}
		}

//		TList *listOfLines = myPave->GetListOfLines();
//		   TLatex *myt = new TLatex(0,0,"Test = 10");
//		   myt ->SetTextFont(42);
//		   myt ->SetTextSize(0.04);
//		   myt ->SetTextColor(kRed);
//		   listOfLines->Add(myt);

//		   pad->GetListOfPrimitives()->Remove(ps);
//		   pad->GetListOfPrimitives()->Add(myPave);
	}

	pad->Modified();
	pad->Update();
}

void GraphicsUtils::addChi2Value(TVirtualPad* pad){
	// Retrieve the stat box
	TPaveStats *paveStats = getPaveStats(pad);

	if (paveStats){
		 TText *tText = paveStats->GetLineWith("chi");
		 const char* text = tText->GetTitle();
		 Double_t chi2;
		 Double_t nPars;
		 StringUtils::extractChiNPars(text, chi2, nPars);
		 Double_t chi2Value = chi2/nPars;
		 TString newText = TString::Format("%s #approx %.2f", text, chi2Value);
		 const char* newTextString = newText.Data();
		 tText->SetTitle(newTextString);
	}

	pad->Modified();
	pad->Update();
}
