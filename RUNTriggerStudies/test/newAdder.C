{


	TCanvas *c1 = new TCanvas();
	//TFile out("scaled_plots_test0.root" , "RECREATE");
	//TFile out2("scaled_plots_test0_eff.root" , "RECREATE");


/*	fB = TFile("plots/asofOct19/histos_2.root");
	fC = TFile("plots/asofOct19/histos_3.root");
	fD = TFile("plots/asofOct19/histos_4.root");
	fE = TFile("plots/asofOct19/histos_5.root");
	fF = TFile("plots/asofOct19/histos_6.root");
	fG = TFile("plots/asofOct19/histos_7.root");
	fH = TFile("plots/asofOct19/histos_8.root");
	fI = TFile("plots/asofOct19/histos_9.root");
	fJ = TFile("plots/asofOct19/histos_10.root");
	fK = TFile("plots/asofOct19/histos_11.root");
	fL = TFile("plots/asofOct19/histos_12.root");
	fM = TFile("plots/asofOct19/histos_13.root");	
	fS = TFile("plots/asofOct19/signal.root"); */

	TFile *f1 = new TFile("/eos/uscms/store/user/alkahn/QCD_Pt-15to3000_TuneCUETP8M1_Flat_13TeV_pythia8/crab_RunIIFall15DR76-25nsFlat10to25TSG_76X_mcRun2_asymptotic_v12-v1_RUNTriggerValidation_v763/160204_154314/combined/QCD_Pt-15to3000_TuneCUETP8M1_Flat_13TeV_RunIIFall15DR76-25nsFlat10to25TSG.root");
	TFile *f2 = new TFile("/eos/uscms/store/user/alkahn/QCD_Pt-15to3000_TuneCUETP8M1_Flat_13TeV_pythia8/crab_RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1_RUNTriggerValidation_v763/160204_154324/combined/QCD_Pt-15to3000_TuneCUETP8M1_Flat_13TeV_RunIIFall15MiniAODv2-PU25nsData2015v1_76X.root");
	/// CREATE HISTOGRAMS ///

	gStyle->SetOptStat(1111);
	gStyle->SetStatX(0.90);
	gStyle->SetStatY(0.90);
	gStyle->SetStatW(0.25);
	gStyle->SetStatH(0.20);
	gStyle->SetPalette(1);


	TH1D *j1M_f1  = (TH1D*)f1->Get("AK8PFHT650TrimMass50/jet1Mass");
	TH1D *j1M_f2  = (TH1D*)f2->Get("AK8PFHT650TrimMass50/jet1Mass");
	TH1D *j1TM_f1  = (TH1D*)f1->Get("AK8PFHT650TrimMass50/jet1TrimmedMass");
	TH1D *j1TM_f2  = (TH1D*)f2->Get("AK8PFHT650TrimMass50/jet1TrimmedMass");
	TH1D *j1PM_f1  = (TH1D*)f1->Get("AK8PFHT650TrimMass50/jet1PrunedMass");
	TH1D *j1PM_f2  = (TH1D*)f2->Get("AK8PFHT650TrimMass50/jet1PrunedMass");
	TH1D *j1Pt_f1  = (TH1D*)f1->Get("AK8PFHT650TrimMass50/jet1Pt");
	TH1D *j1Pt_f2  = (TH1D*)f2->Get("AK8PFHT650TrimMass50/jet1Pt");

	TH1D *j2M_f1  = (TH1D*)f1->Get("AK8PFHT650TrimMass50/jet2Mass");
	TH1D *j2M_f2  = (TH1D*)f2->Get("AK8PFHT650TrimMass50/jet2Mass");
	TH1D *j2TM_f1  = (TH1D*)f1->Get("AK8PFHT650TrimMass50/jet2TrimmedMass");
	TH1D *j2TM_f2  = (TH1D*)f2->Get("AK8PFHT650TrimMass50/jet2TrimmedMass");
	TH1D *j2PM_f1  = (TH1D*)f1->Get("AK8PFHT650TrimMass50/jet2PrunedMass");
	TH1D *j2PM_f2  = (TH1D*)f2->Get("AK8PFHT650TrimMass50/jet2PrunedMass");
	TH1D *j2Pt_f1  = (TH1D*)f1->Get("AK8PFHT650TrimMass50/jet2Pt");
	TH1D *j2Pt_f2  = (TH1D*)f2->Get("AK8PFHT650TrimMass50/jet2Pt");


	j1M_f1->Scale(1/j1M_f1->GetEntries());
	j1TM_f1->Scale(1/j1TM_f1->GetEntries());
	j1PM_f1->Scale(1/j1PM_f1->GetEntries());
	j1Pt_f1->Scale(1/j1Pt_f1->GetEntries());
	j2M_f1->Scale(1/j2M_f1->GetEntries());
	j2TM_f1->Scale(1/j2TM_f1->GetEntries());
	j2PM_f1->Scale(1/j2PM_f1->GetEntries());
	j2Pt_f1->Scale(1/j2Pt_f1->GetEntries());
	j1M_f2->Scale(1/j1M_f2->GetEntries());
	j1TM_f2->Scale(1/j1TM_f2->GetEntries());
	j1PM_f2->Scale(1/j1PM_f2->GetEntries());
	j1Pt_f2->Scale(1/j1Pt_f2->GetEntries());
	j2M_f2->Scale(1/j2M_f2->GetEntries());
	j2TM_f2->Scale(1/j2TM_f2->GetEntries());
	j2PM_f2->Scale(1/j2PM_f2->GetEntries());
	j2Pt_f2->Scale(1/j2Pt_f2->GetEntries());





	j1M_f1->GetXaxis()->SetTitle("Leading Jet Mass (GeV)");
	j1TM_f1->GetXaxis()->SetTitle("Leading Jet Trimmed Mass (GeV)");
	j1PM_f1->GetXaxis()->SetTitle("Leading Jet Pruned Mass (GeV)");
	j1Pt_f1->GetXaxis()->SetTitle("Leading Jet P_{t} (GeV)");
	j2M_f1->GetXaxis()->SetTitle("Second Leading Jet Mass (GeV)");
	j2TM_f1->GetXaxis()->SetTitle("Second Leading Jet Trimmed Mass (GeV)");
	j2PM_f1->GetXaxis()->SetTitle("Second Leading Jet Pruned Mass (GeV)");
	j2Pt_f1->GetXaxis()->SetTitle("Second Leading Jet P_{t} (GeV)");
	j1M_f2->GetXaxis()->SetTitle("Leading Jet Mass (GeV)");
	j1TM_f2->GetXaxis()->SetTitle("Leading Jet Trimmed Mass (GeV)");
	j1PM_f2->GetXaxis()->SetTitle("Leading Jet Pruned Mass (GeV)");
	j1Pt_f2->GetXaxis()->SetTitle("Leading Jet P_{t} (GeV)");
	j2M_f2->GetXaxis()->SetTitle("Second Leading Jet Mass (GeV)");
	j2TM_f2->GetXaxis()->SetTitle("Second Leading Jet Trimmed Mass (GeV)");
	j2PM_f2->GetXaxis()->SetTitle("Second Leading Jet Pruned Mass (GeV)");
	j2Pt_f2->GetXaxis()->SetTitle("Second Leading Jet P_{t} (GeV)");



	j1M_f1->SetLineColor(kRed);
	j1TM_f1->SetLineColor(kRed);
	j1PM_f1->SetLineColor(kRed);
	j1Pt_f1->SetLineColor(kRed);
	j2M_f1->SetLineColor(kRed);
	j2TM_f1->SetLineColor(kRed);
	j2PM_f1->SetLineColor(kRed);
	j2Pt_f1->SetLineColor(kRed);
	j1M_f2->SetLineColor(kBlue);
	j1TM_f2->SetLineColor(kBlue);
	j1PM_f2->SetLineColor(kBlue);
	j1Pt_f2->SetLineColor(kBlue);
	j2M_f2->SetLineColor(kBlue);
	j2TM_f2->SetLineColor(kBlue);
	j2PM_f2->SetLineColor(kBlue);
	j2Pt_f2->SetLineColor(kBlue);








	leg = new TLegend(0.6, 0.7, 0.9, 0.9);
	leg->AddEntry(j1M_f1, "Fall15DR76", "f");
	leg->AddEntry(j1M_f2, "Fall15MiniAODv2", "f");







	j1M_f1->Draw("h");
	j1M_f2->Draw("h same");
	leg->Draw();
	c1->Print("Plots/jet1Mass_QCD_Pt-15to3000.png");

	TCanvas *c2 = new TCanvas();
	j1TM_f1->Draw("h");
	j1TM_f2->Draw("h same");
	leg->Draw();
	c2->Print("Plots/jet1TrimmedMass_QCD_Pt-15to3000.png");

	TCanvas *c3 = new TCanvas();
	j1PM_f1->Draw("h");
	j1PM_f2->Draw("h same");
	leg->Draw();
	c3->Print("Plots/jet1PrunedMass_QCD_Pt-15to3000.png");

	TCanvas *c4 = new TCanvas();
	j1Pt_f1->Draw("h");
	j1Pt_f2->Draw("h same");
	leg->Draw();
	c4->Print("Plots/jet1Pt_QCD_Pt-15to3000.png");

	TCanvas *c5 = new TCanvas();
	j2M_f1->Draw("h");
	j2M_f2->Draw("h same");
	leg->Draw();
	c5->Print("Plots/jet2Mass_QCD_Pt-15to3000.png");

	TCanvas *c6 = new TCanvas();
	j2TM_f1->Draw("h");
	j2TM_f2->Draw("h same");
	leg->Draw();
	c6->Print("Plots/jet2TrimmedMass_QCD_Pt-15to3000.png");

	TCanvas *c7 = new TCanvas();
	j2PM_f1->Draw("h");
	j2PM_f2->Draw("h same");
	leg->Draw();
	c7->Print("Plots/jet2PrunedMass_QCD_Pt-15to3000.png");

	TCanvas *c8 = new TCanvas();
	j2Pt_f1->Draw("h");
	j2Pt_f2->Draw("h same");
	leg->Draw();
	c8->Print("Plots/jet2Pt_QCD_Pt-15to3000.png");



}
