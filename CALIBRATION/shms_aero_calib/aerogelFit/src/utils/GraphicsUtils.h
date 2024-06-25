/*
 * GraphicsUtils.h
 *
 *  Created on: Jul 30, 2020
 *      Author: petrstepanov
 */

#ifndef SRC_HELPER_GraphicsUtils_H_
#define SRC_HELPER_GraphicsUtils_H_

#include <TH1.h>
#include <TF1.h>
#include <TVirtualPad.h>
#include <TFitResult.h>
#include <TPaveText.h>
#include <TFitResultPtr.h>
#include <TCanvas.h>
#include <RooAbsPdf.h>
#include <TPaveStats.h>
#include <vector>

struct Margin {
	Double_t left;
	Double_t right;
	Double_t bottom;
	Double_t top;
};

class GraphicsUtils {
public:
	GraphicsUtils();
	virtual ~GraphicsUtils();

	static const Double_t TEXT_SIZE_NORMAL;
	static const Double_t TEXT_SIZE_SMALL;
	static const Double_t TEXT_SIZE_SMALLER;

	static const Double_t LINE_HEIGHT_NORMAL;
	static const Double_t LINE_HEIGHT_SMALL;

	static const Int_t FONT_REGULAR;
	static const Int_t FONT_BOLD;

	static const Double_t TOP_TO_BOTTOM_PAD_HEIGHT_RATIO;

	static const Margin padMargins;

	static const Int_t BEAM_CANVAS_WIDTH;
	static const Int_t BEAM_CANVAS_HEIGHT;

  static const std::vector<Int_t> colorSet;

	static Style_t getFontCode(Int_t fontSize);
	static Double_t getFontSizeScale(Bool_t isTopPad);

	static void setStatsFitOption(TH1*, TVirtualPad*, Int_t);
	static void alignStats(TVirtualPad* pad, Double_t statsWidth = 0.536);
	static void stylePaveText(TPaveText* paveText, TVirtualPad* pad);
//	static void addLineToStats(TH1*, const char*, TVirtualPad*);
//	static void showChi2InStats(TH1*, TFitResultPtr, TVirtualPad*);
	static void styleAxis(TAxis* axis, const char* title, Double_t titleOffset, Double_t labelOffset, Bool_t isTopPad);
	static void addLineToPave(TVirtualPad* canvas, RooAbsPdf* pdf, const char* line);

	static TCanvas* getCanvasForNPads(const char* name, const char* title, Int_t width, Int_t height, Int_t nPads, Int_t nCols);
	static TCanvas* getCanvasForNPads(const char* title, Int_t width, Int_t height, Int_t nPads, Int_t nCols);

	static void hilightLimitParameters(TF1* func, TVirtualPad* pad);
	static void addChi2Value(TVirtualPad* pad);

	static TPaveStats* getPaveStats(TVirtualPad* pad);

private:
  static Double_t statsLineHeight;
};

#endif /* SRC_HELPER_GRAPHICSUTILS_H_ */
