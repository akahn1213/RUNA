{
	TFile out("stacked.root" , "RECREATE");

	TCanvas *can1 = new TCanvas("c1", "stacked histograms", 10, 10, 1300, 800);

	//TFile *StZ = new TFile("St2_500_toZSt1_RPVSt1_150_tojb_Analysis.root");
	TFile *f1 = new TFile("St2_600_toHSt1_RPVSt1_150_tojj_Analysis.root");
	TFile *f2 = new TFile("DYJets_741_Analysis_Hadronic.root");


	TH1F *sfactSig = (TH1F*)StZ->Get("AnalysisPlots/cutflowSimple");
	TH1F *sfactDY = (TH1F*)DY->Get("AnalysisPlots/cutflowSimple");




	h1->Scale( (10000.0 * ( xsecSig / (double)sfactSig->GetBinContent(1)) / fakeXSec ));
	//h2->Scale( 10000.0 * ( xsecDY / (double)sfactDY->GetBinContent(1) ));
	h3->Scale( (10000.0 * ( xsecTT / (double)sfactTT->GetBinContent(1)) / fakeXSec ));

	q1->Scale( 10000.0 * ( xsecQCD_170to300 / (double)sfactQCD_170to300->GetBinContent(1)));


//	q2->Scale( 10000.0 * ( xsecQCD_300to470 / (double)sfactQCD_300to470->GetBinContent(1)));

      q3->Scale( 10000.0 * ( xsecQCD_470to600 / (double)sfactQCD_470to600->GetBinContent(1)));
      q4->Scale( 10000.0 * ( xsecQCD_600to800 / (double)sfactQCD_600to800->GetBinContent(1)));
      q5->Scale( 10000.0 * ( xsecQCD_800to1000 / (double)sfactQCD_800to1000->GetBinContent(1)));
      q6->Scale( 10000.0 * ( xsecQCD_1000to1400 / (double)sfactQCD_1000to1400->GetBinContent(1)));
      q7->Scale( 10000.0 * ( xsecQCD_1400to1800 / (double)sfactQCD_1400to1800->GetBinContent(1)));

	qcd=q1;

//	qcd->Add(q2);
	qcd->Add(q3);
	qcd->Add(q4);
	qcd->Add(q5);
	qcd->Add(q6);
	qcd->Add(q7);

	h1->SetFillColor(kRed);
	//h2->SetFillColor(kBlue);
	h3->SetFillColor(kGreen);
	qcd->SetFillColor(kBlue);

	ttset.Add(h3);
	//dyset.Add(h2);
	signalSet.Add(h1);

	qcd->SetTitle("JJ(b) Mass with Subjet B-Tag and Diagonal Cut (QCD)");


	//h_stack.Add(h2);
	h_stack.Add(h3);
	h_stack.Add(h1);
	//h_stack.Add(qcd);





	leg = new TLegend(0.8, 0.7, 0.89, 0.89);
	leg->AddEntry(h1, "Signal", "f");
	//leg->AddEntry(h2, "DY", "f");
	leg->AddEntry(h3, "TT", "f");


	legdy = new TLegend(0.8, 0.7, 0.89, 0.89);
	//legdy->AddEntry(h2, "DY", "f");

	legtt = new TLegend(0.8, 0.7, 0.89, 0.89);
	legtt->AddEntry(h3, "TT", "f");

	legsig = new TLegend(0.8, 0.7, 0.89, 0.89);
	legsig->AddEntry(h1, "Signal", "f");




	can1->Divide(2,2);
	can1->cd(1);
	qcd->Draw("hist");
	//legdy->Draw();
	can1->cd(2);
	ttset.Draw("hist");
	//legtt->Draw();
	can1->cd(3);
	signalSet.Draw("hist");
	//legsig->Draw();
	can1->cd(4);
	h_stack.Draw("hist");
	//leg->Draw();

}
