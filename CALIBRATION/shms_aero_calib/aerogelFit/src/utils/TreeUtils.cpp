/*
 * TreeUtils.cpp
 *
 *  Created on: Jul 28, 2020
 *      Author: petrstepanov
 */

#include "../utils/TreeUtils.h"

#include "TVirtualTreePlayer.h"
#include "TCanvas.h"
#include "TSystem.h"

TreeUtils::TreeUtils() {
	// TODO Auto-generated constructor stub

}

TreeUtils::~TreeUtils() {
	// TODO Auto-generated destructor stub
}

void TreeUtils::fillBranchToHistogram(TTree* tree, const char* branchName, const char* histName){
	// Create 1D histogram from the tree branch
	// ROOT TBrowser() does following command in Terminal (use up arrow in Terminal after plotting): tv__tree->Draw("tilel","","", 23458364, 0);
	// I've noticed the 3rd parameter is number of (tree entries -2): 23458364 = 23458366 - 2

	// TString tempCanvasName = TString::Format("%s_temp_canvas", branchName);
	// TCanvas* tempCanvas = new TCanvas(tempCanvasName);

	// Access histogram in batch mode
	// https://root.cern.ch/root/htmldoc/guides/users-guide/Trees.html#simple-analysis-using-ttreedraw#accessing-the-histogram-in-batch-mode
	// Specify binning of the histogram (default ROOT bining is poor)
	// https://root.cern.ch/root/htmldoc/guides/users-guide/Trees.html#filling-a-histogram
	TString varexp = TString::Format("%s >> %s", branchName, histName);
	tree->Draw(varexp, "", "", tree->GetEntries() - 2, 0);
	// TH1F *hist = (TH1F*)gPad->GetPrimitive("histName");

	// TH1* hist = (TH1*)(treePlayer->GetHistogram()->Clone(histName));
	// Set Directory to 0: https://root.cern.ch/root/roottalk/roottalk99/1796.html
	// hist->SetDirectory(0);

	// Close and delete temporary canvas
	// https://root-forum.cern.ch/t/how-to-close-or-delete-a-canvas-inside-a-macro/23619/3
	// tempCanvas->Close();
	// gSystem->ProcessEvents();
	// delete tempCanvas;
	// tempCanvas = 0;

}
