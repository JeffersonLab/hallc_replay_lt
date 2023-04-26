Int_t getFileNameIndex(const char *fileName){
	TString fileNameString = fileName;
	TObjArray *objArray = TPRegexp("_(\\d*)_").MatchS(fileNameString); // _(\d*)_
	if (objArray->GetLast() + 1 != 2){
		return 0;
	}
	const char *index = ((TObjString *)objArray->At(1))->GetString().Data();
	return atoi(index);
}

Bool_t fileNameMatch(const char *fileName){
	TString fileNameString = fileName;
	Int_t startIndex = 0;
	TPMERegexp regexp("coin_replay_Full_(\\d*)_-1.root", "g");
	return regexp.Match(fileNameString) && getFileNameIndex(fileName) >= startIndex;
}

Bool_t CheckValue(ROOT::Internal::TTreeReaderValueBase& value) {
	if (value.GetSetupStatus() < 0) {
		std::cout << "Error " << value.GetSetupStatus() << " setting up reader for " << value.GetBranchName() << std::endl;
		return kFALSE;
	}
	return kTRUE;
}

int run(const char *fileName){
	// Open input ROOT file
	std::cout << fileName << std::endl;
	TFile *file = new TFile(fileName);
	if (file->IsZombie()){
		file->Close();
		std::cout << "Error opening file \"" << fileName << "\". Skipping." << std::endl;
		return 0;
	}

	// Test File Baskets
	// https://root-forum.cern.ch/t/error-in-tbasket-readbasketbuffers/8932/3
	// file->Map();

	// Obtain the Tree named "T" from file
	TTree *tree = (TTree *)file->Get("T");
	if (!tree){
		std::cout << "Cannot find object with name \"T\". Skipping." << std::endl;
		return 0;
	}
	Int_t nEntries = tree->GetEntries();
	std ::cout << "Number of events in the tree: " << nEntries << std::endl;

	// Instantiate histograms to be saved in ROOT file
	const Int_t nHists = 7;
	TH1D **pmtPositive = new TH1D *[nHists];
	TH1D **pmtNegative = new TH1D *[nHists];
	for (UInt_t i = 0; i < nHists; i++){
		TString pmtPosName = TString::Format("Positive_PMT_%d", i);
		TString pmtPosTitle = TString::Format("Positive PMT %d spectrum", i);
		pmtPositive[i] = new TH1D(pmtPosName.Data(), pmtPosTitle.Data(), 10001, 0.05, 100.55);
		TString pmtNegName = TString::Format("Negative_PMT_%d", i).Data();
		TString pmtNegTitle = TString::Format("Negative PMT %d spectrum", i).Data();
		pmtNegative[i] = new TH1D(pmtNegName.Data(), pmtNegTitle.Data(), 10001, 0.05, 100.55);
	}

	// Try opening branches
	TBranch* branchPos = tree->GetBranch("P.aero.posNpe");
	TBranch* branchNeg = tree->GetBranch("P.aero.negNpe");
	if (!branchPos || !branchNeg){
		std::cout << "Branch could not be initialized. Skipping." << std::endl;
		return 0;
	}

	Double_t posNpe[7] = {0};
	Double_t negNpe[7] = {0};
	branchPos->SetAddress(&posNpe);
	branchPos->SetAutoDelete(kTRUE);
	branchNeg->SetAddress(&negNpe);
	branchNeg->SetAutoDelete(kTRUE);

	UInt_t maxEntries = 1E5;
	for (Int_t i=0; i<nEntries; i++) {
		Int_t nBytes = tree->GetEntry(i);
		// Check entry consistency
		if (nBytes <= 0){
			std::cout << "Tree read error!" << std::endl;
			file->Close();
			return 0;
		}
		// Check entry consistensy
		for (UInt_t i = 0; i < 7; i++){
			pmtPositive[i]->Fill(posNpe[i]);
			pmtNegative[i]->Fill(negNpe[i]);
		}
		// Manually stop reading the tree if more than 2E5 events
		if (i++ > maxEntries) break;
	}

	// Write histograms to file
	TString outputFileName = TString::Format("result_%d.root", getFileNameIndex(fileName));
	TFile* outputFile = new TFile(outputFileName.Data(), "RECREATE");
	for (UInt_t i=0; i < nHists; i++){
		pmtPositive[i]->Write();
		pmtNegative[i]->Write();
	}
	outputFile->Close();
	file->Close();

	// Return success
	return 0;
}

Bool_t isCorruptFile(const char* fileName){
	// Hardcoded indexes of files with corrupt headers
	Int_t badIndexes[] = {-1}; // {4941, 4900, 4901, 4950, 5005};
	Int_t index = getFileNameIndex(fileName);
	// https://stackoverflow.com/questions/19215027/check-if-element-found-in-array-c
	Int_t* found = std::find(std::begin(badIndexes), std::end(badIndexes), index);
	if (found != std::end(badIndexes)) {
		std::cout << "Found damadged file \"" << fileName << ". Skipping." << std::endl;
		return kTRUE;
	}
	return kFALSE;
}

Int_t replayConv(const char *dirPath = ""){
	// Open the directory for scanning
	TSystemDirectory *dir = new TSystemDirectory(dirPath, dirPath);
	TList *files = dir->GetListOfFiles();

	// Exit if directory is empty
	if (!files){
		std ::cout << "Directory \"" << dirPath << "\" is empty." << std::endl;
		return 1;
	}

	// Select files from directory that match our pattern
	TIter next(files);
	TSystemFile *file;
	TList *filesList = new TList();
	const char *workingDir = gSystem->WorkingDirectory();
	while ((file = (TSystemFile *)next())){
		const char* fName = file->GetName();
		// Make sure filename index is not present in the list of bad indexes
		if (!file->IsDirectory() && fileNameMatch(fName)){
			TObjString *fNameObjString = new TObjString(fName);
			filesList->Add(fNameObjString);
		}
	}
	filesList->Sort(kTRUE);
	filesList->Print();

	// Loop every file in the list
	gEnv->SetValue("TFile.Recover", 0); // Do not attempt to recover files
	for (TObject *object : *filesList){
		TObjString *fileName = (TObjString *)object;
		if (fileName){
			TString fileNameString = fileName->GetString().Data();
			const char *fileNamePath = gSystem->PrependPathName(dir->GetName(), fileNameString);
			run(fileNamePath);
		}
		// break;
	}
	return 1;
}
