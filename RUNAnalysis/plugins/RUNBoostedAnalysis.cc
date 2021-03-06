// -*- C++ -*-
//
// Package:    Ntuples/Ntuples
// Class:      RUNBoostedAnalysis
// 
/**\class RUNBoostedAnalysis RUNBoostedAnalysis.cc Ntuples/Ntuples/plugins/RUNBoostedAnalysis.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  alejandro gomez
//         Created:  Tue, 14 Oct 2014 23:13:13 GMT
//
//


// system include files
#include <memory>
#include <vector>
#include <TLorentzVector.h>
#include <TH2.h>
#include <TTree.h>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/Math/interface/LorentzVector.h"

#include "FWCore/Framework/interface/GetterOfProducts.h"
#include "FWCore/Framework/interface/ProcessMatch.h"

#include "RUNA/RUNAnalysis/interface/CommonVariablesStructure.h"

using namespace edm;
using namespace std;

//
// constants, enums and typedefs
//

//
// class declaration
//
class RUNBoostedAnalysis : public EDAnalyzer {
   public:
      explicit RUNBoostedAnalysis(const ParameterSet&);
      ~RUNBoostedAnalysis();

   private:
      virtual void beginJob() override;
      virtual void analyze(const Event&, const EventSetup&) override;
      virtual void endJob() override;

      //virtual void beginRun(Run const&, EventSetup const&) override;
      //virtual void endRun(Run const&, EventSetup const&) override;
      //virtual void beginLuminosityBlock(LuminosityBlock const&, EventSetup const&) override;
      //virtual void endLuminosityBlock(LuminosityBlock const&, EventSetup const&) override;

      // ----------member data ---------------------------
      //GetterOfProducts< vector<float> > getterOfProducts_;
      //EDGetTokenT<TriggerResults> triggerBits_;
      Service<TFileService> fs_;
      TTree *RUNAtree;
      map< string, TH1D* > histos1D_;
      map< string, TH2D* > histos2D_;
      vector< string > cutLabels;
      map< string, double > cutmap;

      bool bjSample;
      bool mkTree;
      TString HLTtriggerOne;
      TString HLTtriggerTwo;
      double scale;
      /*double cutAK4HTvalue;
      double cutjetAK4Ptvalue;
      double cutTrimmedMassvalue;*/
      double cutHTvalue;
      double cutjetPtvalue;
      double cutAsymvalue;
      double cutCosThetavalue;
      double cutSubjetPtRatiovalue;
      double cutTau31value;
      double cutTau21value;
      double cutBtagvalue;
      double cutDEtavalue;

      ULong64_t event = 0;
      int numJets = 0, numPV = 0;
      unsigned int lumi = 0, run=0;
      float AK4HT = 0, HT = 0, trimmedMass = -999, Scale = 0,
	    jet1Pt = -999, jet1Eta = -999, jet1Phi = -999, jet1E = -999, jet1Mass = -999, jet1btagCSV = -9999,
	    jet2Pt = -999, jet2Eta = -999, jet2Phi = -999, jet2E = -999, jet2Mass = -999, jet2btagCSV = -9999,
	    subjet11Pt = -999, subjet11Eta = -999, subjet11Phi = -999, subjet11E = -999, 
	    subjet12Pt = -999, subjet12Eta = -999, subjet12Phi = -999, subjet12E = -999, 
	    subjet21Pt = -999, subjet21Eta = -999, subjet21Phi = -999, subjet21E = -999, 
	    subjet22Pt = -999, subjet22Eta = -999, subjet22Phi = -999, subjet22E = -999,
	    massAve = -9999, massAsym = -9999, cosThetaStar = -9999, deltaEtaDijet = -9999,
	    jet1Tau21 = -9999, jet1Tau31 = -9999, jet1Tau32 = -9999,
	    jet2Tau21 = -9999, jet2Tau31 = -9999, jet2Tau32 = -9999,
	    jet1SubjetPtRatio = -999, jet2SubjetPtRatio = -999, jet1SubjetMass21Ratio = -999, jet1Subjet112MassRatio = -999, jet1Subjet1JetMassRatio = - 999, jet1Subjet212MassRatio = - 999, jet1Subjet2JetMassRatio = - 999,
	    jet2SubjetMass21Ratio = -999, jet2Subjet112MassRatio = -999, jet2Subjet1JetMassRatio = - 999, jet2Subjet212MassRatio = - 999, jet2Subjet2JetMassRatio = - 999, 
	    cosPhi13412 = -9999, cosPhi31234 = -9999,
	    dalitzY1 = -9999, dalitzY2 = -9999, dalitzY3 = -9999, dalitzY4 = -9999, dalitzY5 = -9999, dalitzY6 = -9999, 
	    dalitzX1 = -9999, dalitzX2 = -9999, dalitzX3 = -9999, dalitzX4 = -9999, dalitzX5 = -9999, dalitzX6 = -9999;

      EDGetTokenT<vector<float>> jetAK4Pt_;
      EDGetTokenT<vector<float>> jetAK4Eta_;
      EDGetTokenT<vector<float>> jetAK4Phi_;
      EDGetTokenT<vector<float>> jetAK4E_;
      EDGetTokenT<vector<float>> jetPt_;
      EDGetTokenT<vector<float>> jetEta_;
      EDGetTokenT<vector<float>> jetPhi_;
      EDGetTokenT<vector<float>> jetE_;
      EDGetTokenT<vector<float>> jetMass_;
      EDGetTokenT<vector<float>> jetTrimmedMass_;
      EDGetTokenT<vector<float>> jetTau1_;
      EDGetTokenT<vector<float>> jetTau2_;
      EDGetTokenT<vector<float>> jetTau3_;
      EDGetTokenT<vector<float>> jetNSubjets_;
      EDGetTokenT<vector<float>> jetSubjetIndex0_;
      EDGetTokenT<vector<float>> jetSubjetIndex1_;
      EDGetTokenT<vector<float>> jetSubjetIndex2_;
      EDGetTokenT<vector<float>> jetSubjetIndex3_;
      EDGetTokenT<vector<vector<int>>> jetKeys_;
      EDGetTokenT<vector<float>> jetCSV_;
      EDGetTokenT<vector<float>> jetCSVV1_;
      EDGetTokenT<int> NPV_;
      EDGetTokenT<unsigned int> lumi_;
      EDGetTokenT<unsigned int> run_;
      EDGetTokenT<ULong64_t> event_;

      // Trigger
      EDGetTokenT<vector<float>> triggerBit_;
      EDGetTokenT<vector<string>> triggerName_;

      //Jet ID
      EDGetTokenT<vector<float>> jecFactor_;
      EDGetTokenT<vector<float>> neutralHadronEnergy_;
      EDGetTokenT<vector<float>> neutralEmEnergy_;
      EDGetTokenT<vector<float>> chargedHadronEnergy_;
      EDGetTokenT<vector<float>> chargedEmEnergy_;
      EDGetTokenT<vector<float>> chargedHadronMultiplicity_;
      EDGetTokenT<vector<float>> neutralHadronMultiplicity_;
      EDGetTokenT<vector<float>> chargedMultiplicity_;
      EDGetTokenT<vector<float>> muonEnergy_; 

      // Subjets
      EDGetTokenT<vector<float>> subjetPt_;
      EDGetTokenT<vector<float>> subjetEta_;
      EDGetTokenT<vector<float>> subjetPhi_;
      EDGetTokenT<vector<float>> subjetE_;
      EDGetTokenT<vector<float>> subjetMass_;

};

//
// static data member definitions
//

//
// constructors and destructor
//
RUNBoostedAnalysis::RUNBoostedAnalysis(const ParameterSet& iConfig):
//	getterOfProducts_(ProcessMatch(*), this) {
//	triggerBits_(consumes<TriggerResults>(iConfig.getParameter<InputTag>("bits"))),
	jetAK4Pt_(consumes<vector<float>>(iConfig.getParameter<InputTag>("jetAK4Pt"))),
	jetAK4Eta_(consumes<vector<float>>(iConfig.getParameter<InputTag>("jetAK4Eta"))),
	jetAK4Phi_(consumes<vector<float>>(iConfig.getParameter<InputTag>("jetAK4Phi"))),
	jetAK4E_(consumes<vector<float>>(iConfig.getParameter<InputTag>("jetAK4E"))),
	jetPt_(consumes<vector<float>>(iConfig.getParameter<InputTag>("jetPt"))),
	jetEta_(consumes<vector<float>>(iConfig.getParameter<InputTag>("jetEta"))),
	jetPhi_(consumes<vector<float>>(iConfig.getParameter<InputTag>("jetPhi"))),
	jetE_(consumes<vector<float>>(iConfig.getParameter<InputTag>("jetE"))),
	jetMass_(consumes<vector<float>>(iConfig.getParameter<InputTag>("jetMass"))),
	jetTrimmedMass_(consumes<vector<float>>(iConfig.getParameter<InputTag>("jetTrimmedMass"))),
	jetTau1_(consumes<vector<float>>(iConfig.getParameter<InputTag>("jetTau1"))),
	jetTau2_(consumes<vector<float>>(iConfig.getParameter<InputTag>("jetTau2"))),
	jetTau3_(consumes<vector<float>>(iConfig.getParameter<InputTag>("jetTau3"))),
	jetNSubjets_(consumes<vector<float>>(iConfig.getParameter<InputTag>("jetNSubjets"))),
	jetSubjetIndex0_(consumes<vector<float>>(iConfig.getParameter<InputTag>("jetSubjetIndex0"))),
	jetSubjetIndex1_(consumes<vector<float>>(iConfig.getParameter<InputTag>("jetSubjetIndex1"))),
	jetSubjetIndex2_(consumes<vector<float>>(iConfig.getParameter<InputTag>("jetSubjetIndex2"))),
	jetSubjetIndex3_(consumes<vector<float>>(iConfig.getParameter<InputTag>("jetSubjetIndex3"))),
	jetKeys_(consumes<vector<vector<int>>>(iConfig.getParameter<InputTag>("jetKeys"))),
	jetCSV_(consumes<vector<float>>(iConfig.getParameter<InputTag>("jetCSV"))),
	jetCSVV1_(consumes<vector<float>>(iConfig.getParameter<InputTag>("jetCSVV1"))),
	NPV_(consumes<int>(iConfig.getParameter<InputTag>("NPV"))),
	lumi_(consumes<unsigned int>(iConfig.getParameter<InputTag>("Lumi"))),
	run_(consumes<unsigned int>(iConfig.getParameter<InputTag>("Run"))),
	event_(consumes<ULong64_t>(iConfig.getParameter<InputTag>("Event"))),
	// Trigger
	triggerBit_(consumes<vector<float>>(iConfig.getParameter<InputTag>("triggerBit"))),
	triggerName_(consumes<vector<string>>(iConfig.getParameter<InputTag>("triggerName"))),
	//Jet ID,
	jecFactor_(consumes<vector<float>>(iConfig.getParameter<InputTag>("jecFactor"))),
	neutralHadronEnergy_(consumes<vector<float>>(iConfig.getParameter<InputTag>("neutralHadronEnergy"))),
	neutralEmEnergy_(consumes<vector<float>>(iConfig.getParameter<InputTag>("neutralEmEnergy"))),
	chargedHadronEnergy_(consumes<vector<float>>(iConfig.getParameter<InputTag>("chargedHadronEnergy"))),
	chargedEmEnergy_(consumes<vector<float>>(iConfig.getParameter<InputTag>("chargedEmEnergy"))),
	chargedHadronMultiplicity_(consumes<vector<float>>(iConfig.getParameter<InputTag>("chargedHadronMultiplicity"))),
	neutralHadronMultiplicity_(consumes<vector<float>>(iConfig.getParameter<InputTag>("neutralHadronMultiplicity"))),
	chargedMultiplicity_(consumes<vector<float>>(iConfig.getParameter<InputTag>("chargedMultiplicity"))),
	muonEnergy_(consumes<vector<float>>(iConfig.getParameter<InputTag>("muonEnergy"))),
	// Subjets
	subjetPt_(consumes<vector<float>>(iConfig.getParameter<InputTag>("subjetPt"))),
	subjetEta_(consumes<vector<float>>(iConfig.getParameter<InputTag>("subjetEta"))),
	subjetPhi_(consumes<vector<float>>(iConfig.getParameter<InputTag>("subjetPhi"))),
	subjetE_(consumes<vector<float>>(iConfig.getParameter<InputTag>("subjetE"))),
	subjetMass_(consumes<vector<float>>(iConfig.getParameter<InputTag>("subjetMass")))
{
	scale = iConfig.getParameter<double>("scale");
	bjSample = iConfig.getParameter<bool>("bjSample");
	HLTtriggerOne = iConfig.getParameter<string>("HLTtriggerOne");
	HLTtriggerTwo = iConfig.getParameter<string>("HLTtriggerTwo");
	mkTree = iConfig.getParameter<bool>("mkTree");
	/*
	cutAK4HTvalue = iConfig.getParameter<double>("cutAK4HTvalue");
	cutjetAK4Ptvalue = iConfig.getParameter<double>("cutjetAK4Ptvalue");
	cutTrimmedMassvalue = iConfig.getParameter<double>("cutTrimmedMassvalue");
	*/
	cutHTvalue = iConfig.getParameter<double>("cutHTvalue");
	cutjetPtvalue = iConfig.getParameter<double>("cutjetPtvalue");
	cutAsymvalue = iConfig.getParameter<double>("cutAsymvalue");
	cutCosThetavalue = iConfig.getParameter<double>("cutCosThetavalue");
	cutSubjetPtRatiovalue = iConfig.getParameter<double>("cutSubjetPtRatiovalue");
	cutTau31value = iConfig.getParameter<double>("cutTau31value");
	cutTau21value = iConfig.getParameter<double>("cutTau21value");
	cutBtagvalue = iConfig.getParameter<double>("cutBtagvalue");
	cutDEtavalue = iConfig.getParameter<double>("cutDEtavalue");
}


RUNBoostedAnalysis::~RUNBoostedAnalysis()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void RUNBoostedAnalysis::analyze(const Event& iEvent, const EventSetup& iSetup) {


	/*vector<Handle< vector<float> > > handles;
	getterOfProducts_.fillHandles(event, handles);
	*/

	Handle<vector<float> > jetAK4Pt;
	iEvent.getByToken(jetAK4Pt_, jetAK4Pt);

	Handle<vector<float> > jetAK4Eta;
	iEvent.getByToken(jetAK4Eta_, jetAK4Eta);

	Handle<vector<float> > jetAK4Phi;
	iEvent.getByToken(jetAK4Phi_, jetAK4Phi);

	Handle<vector<float> > jetAK4E;
	iEvent.getByToken(jetAK4E_, jetAK4E);

	Handle<vector<float> > jetPt;
	iEvent.getByToken(jetPt_, jetPt);

	Handle<vector<float> > jetEta;
	iEvent.getByToken(jetEta_, jetEta);

	Handle<vector<float> > jetPhi;
	iEvent.getByToken(jetPhi_, jetPhi);

	Handle<vector<float> > jetE;
	iEvent.getByToken(jetE_, jetE);

	Handle<vector<float> > jetMass;
	iEvent.getByToken(jetMass_, jetMass);

	Handle<vector<float> > jetTrimmedMass;
	iEvent.getByToken(jetTrimmedMass_, jetTrimmedMass);

	Handle<vector<float> > jetTau1;
	iEvent.getByToken(jetTau1_, jetTau1);

	Handle<vector<float> > jetTau2;
	iEvent.getByToken(jetTau2_, jetTau2);

	Handle<vector<float> > jetTau3;
	iEvent.getByToken(jetTau3_, jetTau3);

	Handle<vector<float> > jetNSubjets;
	iEvent.getByToken(jetNSubjets_, jetNSubjets);

	Handle<vector<float> > jetSubjetIndex0;
	iEvent.getByToken(jetSubjetIndex0_, jetSubjetIndex0);

	Handle<vector<float> > jetSubjetIndex1;
	iEvent.getByToken(jetSubjetIndex1_, jetSubjetIndex1);

	Handle<vector<float> > jetSubjetIndex2;
	iEvent.getByToken(jetSubjetIndex2_, jetSubjetIndex2);

	Handle<vector<float> > jetSubjetIndex3;
	iEvent.getByToken(jetSubjetIndex3_, jetSubjetIndex3);

	Handle<vector<vector<int> > > jetKeys;
	iEvent.getByToken(jetKeys_, jetKeys);

	Handle<vector<float> > jetCSV;
	iEvent.getByToken(jetCSV_, jetCSV);

	Handle<vector<float> > jetCSVV1;
	iEvent.getByToken(jetCSVV1_, jetCSVV1);

	Handle<int> NPV;
	iEvent.getByToken(NPV_, NPV);

	Handle<unsigned int> Lumi;
	iEvent.getByToken(lumi_, Lumi);

	Handle<unsigned int> Run;
	iEvent.getByToken(run_, Run);

	Handle<ULong64_t> ievent;
	iEvent.getByToken(event_, ievent);

	/// Trigger
	Handle<vector<float> > triggerBit;
	iEvent.getByToken(triggerBit_, triggerBit);

	Handle<vector<string> > triggerName;
	iEvent.getByToken(triggerName_, triggerName);

	/// Jet ID
	Handle<vector<float> > jecFactor;
	iEvent.getByToken(jecFactor_, jecFactor);

	Handle<vector<float> > neutralHadronEnergy;
	iEvent.getByToken(neutralHadronEnergy_, neutralHadronEnergy);

	Handle<vector<float> > neutralEmEnergy;
	iEvent.getByToken(neutralEmEnergy_, neutralEmEnergy);

	Handle<vector<float> > chargedHadronEnergy;
	iEvent.getByToken(chargedHadronEnergy_, chargedHadronEnergy);

	Handle<vector<float> > chargedEmEnergy;
	iEvent.getByToken(chargedEmEnergy_, chargedEmEnergy);

	Handle<vector<float> > chargedHadronMultiplicity;
	iEvent.getByToken(chargedHadronMultiplicity_, chargedHadronMultiplicity);

	Handle<vector<float> > neutralHadronMultiplicity;
	iEvent.getByToken(neutralHadronMultiplicity_, neutralHadronMultiplicity);

	Handle<vector<float> > chargedMultiplicity;
	iEvent.getByToken(chargedMultiplicity_, chargedMultiplicity);

	Handle<vector<float> > muonEnergy;
	iEvent.getByToken(muonEnergy_, muonEnergy);

	/// Subjets
	Handle<vector<float> > subjetPt;
	iEvent.getByToken(subjetPt_, subjetPt);

	Handle<vector<float> > subjetEta;
	iEvent.getByToken(subjetEta_, subjetEta);

	Handle<vector<float> > subjetPhi;
	iEvent.getByToken(subjetPhi_, subjetPhi);

	Handle<vector<float> > subjetE;
	iEvent.getByToken(subjetE_, subjetE);

	Handle<vector<float> > subjetMass;
	iEvent.getByToken(subjetMass_, subjetMass);


	float triggerFiredOne = 0;
	float triggerFiredTwo = 0;
	for (size_t t = 0; t < triggerName->size(); t++) {
		if ( TString( (*triggerName)[t] ).Contains( HLTtriggerOne ) ) {
			triggerFiredOne = (*triggerBit)[t];
			//LogWarning("triggerbit") << (*triggerName)[t] << " " <<  (*triggerBit)[t];
		}
		if ( TString( (*triggerName)[t] ).Contains( HLTtriggerTwo ) ) triggerFiredTwo = (*triggerBit)[t];
	}
	if ( HLTtriggerTwo.Contains( "NOTRIGGER" ) ) triggerFiredTwo = 1;
	if ( HLTtriggerOne.Contains( "NOTRIGGER" ) ) triggerFiredOne = 1;
	//LogWarning("BITS") << triggerFiredOne << " " << triggerFiredTwo;
	
	///////// AK4 jets to model PFHT trigger
	//bool cutAK4HT = 0;
	AK4HT = 0;
	for (size_t q = 0; q < jetAK4Pt->size(); q++) {

		if ( TMath::Abs( (*jetAK4Eta)[q] ) > 2.4 ) continue;
		if ( (*jetAK4Pt)[q] < 40.0 ) continue;
		AK4HT += (*jetAK4Pt)[q];
	}
	//if ( AK4HT > cutAK4HTvalue ) cutAK4HT = 1;
	///////////////////////////////////////////////////*/

	Scale = scale;

	/// Applying kinematic, trigger and jet ID
	cutmap["Processed"] += 1;
	vector< JETtype > JETS;
	vector< float > tmpTriggerMass, tmpMass;
	double rawHT = 0;
	bool cutHT = 0;
	//bool cutMass = 0;
	//bool bTagCSV = 0;
	numJets = 0;
	HT = 0;

	for (size_t i = 0; i < jetPt->size(); i++) {

		if( TMath::Abs( (*jetEta)[i] ) > 2.4 ) continue;

		tmpTriggerMass.push_back( (*jetTrimmedMass)[i] );

		rawHT += (*jetPt)[i];
		histos1D_[ "rawJetPt" ]->Fill( (*jetPt)[i], scale  );

		double jec = 1. / ( (*jecFactor)[i] * (*jetE)[i] );
		double nhf = (*neutralHadronEnergy)[i] * jec;
		double nEMf = (*neutralEmEnergy)[i] * jec;
		double chf = (*chargedHadronEnergy)[i] * jec;
		//double muf = (*muonEnergy)[i] * jec;
		double cEMf = (*chargedEmEnergy)[i] * jec;
		int numConst = (*chargedHadronMultiplicity)[i] + (*neutralHadronMultiplicity)[i] ;  //// REMEMBER TO INCLUDE # of constituents
		double chm = (*chargedMultiplicity)[i] * jec;

		//bool idL = ( (nhf<0.99) && (nEMf<0.99) && (muf<0.8) && (cEMf<0.9) );  /// 8TeV recommendation
		//if( !idL ) LogWarning("jetID") << (*jetPt)[i] << " " << jec << " " << nhf << " " << nEMf << " " << muf << " " << cEMf;
		bool idL = ( (nhf<0.99) && (nEMf<0.99) && (numConst>1) && (chf>0) && (chm>0) && (cEMf<0.99) );

		if( (*jetPt)[i] > cutjetPtvalue  && idL ) { 
			//LogWarning("jetInfo") << i << " " << (*jetPt)[i] << " " << (*jetEta)[i] << " " << (*jetPhi)[i] << " " << (*jetMass)[i];

			HT += (*jetPt)[i];
			++numJets;

			TLorentzVector tmpJet;
			tmpJet.SetPtEtaPhiE( (*jetPt)[i], (*jetEta)[i], (*jetPhi)[i], (*jetE)[i] );
			tmpMass.push_back( (*jetMass)[i] );

			/// Vector of zeros
			TLorentzVector tmpSubjet0, tmpSubjet1, tmpZeros;
			tmpZeros.SetPtEtaPhiE( 0, 0, 0, 0 );

			for (size_t j = 0; j < subjetPt->size(); j++) {
				if( j == (*jetSubjetIndex0)[i] ) {
					//LogWarning("subjets0") << j << " " << (*jetSubjetIndex0)[i] << " " <<  subjetPt->size() << " " << (*subjetPt)[j];
					tmpSubjet0.SetPtEtaPhiE( (*subjetPt)[j], (*subjetEta)[j], (*subjetPhi)[j], (*subjetE)[j] );
				} //else tmpSubjet0 = tmpZeros ; 
					
				if( j == (*jetSubjetIndex1)[i] ) {
					tmpSubjet1.SetPtEtaPhiE( (*subjetPt)[j], (*subjetEta)[j], (*subjetPhi)[j], (*subjetE)[j] );
				} //else tmpSubjet1 = tmpZeros ; 
			}

			//if ( (*jetCSV)[i] > 0.244 ) bTagCSV = 1; 	// CSVL
			//if ( (*jetCSV)[i] > 0.679 ) bTagCSV = 1; 	// CSVM
			//if ( (*jetCSVV1)[i] > 0.405 ) bTagCSV = 1; 	// CSVV1L
			//if ( (*jetCSVV1)[i] > 0.783 ) bTagCSV = 1; 	// CSVV1M

			JETtype tmpJET;
			tmpJET.p4 = tmpJet;
			tmpJET.subjet0 = tmpSubjet0;
			tmpJET.subjet1 = tmpSubjet1;
			tmpJET.mass = (*jetMass)[i];
			tmpJET.tau1 = (*jetTau1)[i];
			tmpJET.tau2 = (*jetTau2)[i];
			tmpJET.tau3 = (*jetTau3)[i];
			tmpJET.btagCSV = (*jetCSV)[i];
			JETS.push_back( tmpJET );
	   
			histos1D_[ "jetPt" ]->Fill( (*jetPt)[i], scale  );
			histos1D_[ "jetEta" ]->Fill( (*jetEta)[i], scale  );
			histos1D_[ "jetMass" ]->Fill( (*jetMass)[i], scale  );
		}
	}

	numPV = *NPV;
	//sort(JETS.begin(), JETS.end(), [](const JETtype &p1, const JETtype &p2) { TLorentzVector tmpP1, tmpP2; tmpP1 = p1.p4; tmpP2 = p2.p4;  return tmpP1.M() > tmpP2.M(); }); 
	histos1D_[ "jetNum" ]->Fill( numJets, scale );
	histos1D_[ "NPV" ]->Fill( numPV, scale );
	if ( HT > 0 ) histos1D_[ "HT" ]->Fill( HT, scale  );
	if ( rawHT > 0 ) histos1D_[ "rawHT" ]->Fill( rawHT, scale  );
	if ( HT > cutHTvalue ) cutHT = 1;

	sort(tmpTriggerMass.begin(), tmpTriggerMass.end(), [](const float p1, const float p2) { return p1 > p2; }); 
	if ( ( tmpTriggerMass.size()> 0 ) ) { //&& ( tmpTriggerMass[0] > cutTrimmedMassvalue) ){
		//cutMass = 1;
		trimmedMass = tmpTriggerMass[0];
		histos1D_[ "jetTrimmedMass" ]->Fill( tmpTriggerMass[0], scale  );
		if (HT > 0) histos2D_[ "jetTrimmedMassHT" ]->Fill( tmpTriggerMass[0], HT, scale  );
	}
	tmpTriggerMass.clear();
	
	sort(tmpMass.begin(), tmpMass.end(), [](const float p1, const float p2) { return p1 > p2; }); 
	float leadMass = 0;
	if ( ( tmpMass.size()> 0 ) ) { //&& ( tmpMass[0] > cutTrimmedMassvalue) ){
		leadMass = tmpMass[0];
		histos1D_[ "leadMass" ]->Fill( tmpMass[0], scale  );
		if (HT > 0) histos2D_[ "leadMassHT" ]->Fill( tmpMass[0], HT, scale  );
	}
	tmpMass.clear();

	//if ( HT > 0 ) 	LogWarning("NOT fired") << HT << " " << trimmedMass;
	if ( triggerFiredOne && triggerFiredTwo ) {
		//LogWarning("fired") << HT << " " << trimmedMass;
		cutmap["Trigger"] += 1; 
		histos1D_[ "HT_cutTrigger" ]->Fill( HT, scale  );
		histos1D_[ "NPV_cutTrigger" ]->Fill( numPV, scale );
		histos1D_[ "jetNum_cutTrigger" ]->Fill( numJets, scale );
		histos2D_[ "jetTrimmedMassHT_cutTrigger" ]->Fill( trimmedMass, HT, scale  );
		histos2D_[ "leadMassHT_cutTrigger" ]->Fill( leadMass, HT, scale  );

		int kdum = 0;
		for (size_t k = 0; k < JETS.size(); k++) {
			histos1D_[ "jetPt_cutTrigger" ]->Fill( JETS[k].p4.Pt(), scale  );
			histos1D_[ "jetEta_cutTrigger" ]->Fill( JETS[k].p4.Eta(), scale  );
			histos1D_[ "jetMass_cutTrigger" ]->Fill( JETS[k].mass, scale );

			if ( (++kdum) == 1 ) {
				histos1D_[ "jet1Pt_cutTrigger" ]->Fill( JETS[0].p4.Pt(), scale  );
				histos1D_[ "jet1Mass_cutTrigger" ]->Fill( JETS[0].mass, scale );
				histos1D_[ "jet1Eta_cutTrigger" ]->Fill( JETS[0].p4.Eta(), scale  );
			}
		 }
		//////////////////////////////////////////////////////////////////////////////
		
		if ( cutHT ){

			cutmap["HT"] += 1; 
			if ( !mkTree ) {
				histos1D_[ "HT_cutHT" ]->Fill( HT, scale  );
				histos1D_[ "NPV_cutHT" ]->Fill( numPV, scale );
				histos1D_[ "jetNum_cutHT" ]->Fill( numJets, scale );
				histos2D_[ "jetTrimmedMassHT_cutHT" ]->Fill( trimmedMass, HT, scale  );
				histos2D_[ "leadMassHT_cutHT" ]->Fill( leadMass, HT, scale  );

				int tdum = 0;
				for (size_t k = 0; k < JETS.size(); k++) {
					histos1D_[ "jetPt_cutHT" ]->Fill( JETS[k].p4.Pt(), scale  );
					histos1D_[ "jetEta_cutHT" ]->Fill( JETS[k].p4.Eta(), scale  );
					histos1D_[ "jetMass_cutHT" ]->Fill( JETS[k].mass, scale );

					if ( (++tdum) == 1 ) {
						histos1D_[ "jet1Pt_cutHT" ]->Fill( JETS[0].p4.Pt(), scale  );
						histos1D_[ "jet1Mass_cutHT" ]->Fill( JETS[0].mass, scale );
						histos1D_[ "jet1Eta_cutHT" ]->Fill( JETS[0].p4.Eta(), scale  );
					}
				}
			 }
						
			vector<double> dalitz1, dalitz2;
			vector<TLorentzVector> jet1SubjetsTLV, jet2SubjetsTLV;

			if ( JETS.size() > 1 ) {

				cutmap["Dijet"] += 1;

				// Mass average and asymmetry
				jet1Mass = JETS[0].mass;
				jet2Mass = JETS[1].mass;
				massAve = massAverage( jet1Mass, jet2Mass );
				massAsym = massAsymmetry( jet1Mass, jet2Mass );
				//////////////////////////////////////////////////////////////////////////
				
				// Btag
				jet1btagCSV = JETS[0].btagCSV;
				jet2btagCSV = JETS[1].btagCSV;

				// Dijet eta
				deltaEtaDijet = deltaValue( JETS[0].p4.Eta(), JETS[1].p4.Eta() );

				// Cos theta star
				cosThetaStar = calculateCosThetaStar( JETS[0].p4, JETS[1].p4 ) ;

				// Nsubjetiness
				jet1Tau21 = JETS[0].tau2 / JETS[0].tau1;
				jet1Tau31 = JETS[0].tau3 / JETS[0].tau1;
				jet1Tau32 = JETS[0].tau3 / JETS[0].tau2;
				jet2Tau21 = JETS[1].tau2 / JETS[1].tau1;
				jet2Tau31 = JETS[1].tau3 / JETS[1].tau1;
				jet2Tau32 = JETS[1].tau3 / JETS[1].tau2;
				////////////////////////////////////////////////////////////////////////////////


				// Subjet variables
				jet1SubjetsTLV.push_back( JETS[0].subjet0 );
				jet1SubjetsTLV.push_back( JETS[0].subjet1 );
				//LogWarning("subjet0") <<  jet1SubjetsTLV[0].M() << " " <<  jet1SubjetsTLV[1].M();
				sort(jet1SubjetsTLV.begin(), jet1SubjetsTLV.end(), [](const TLorentzVector &p1, const TLorentzVector &p2) { return p1.M() > p2.M(); }); 
				//LogWarning("subjet0") <<  jet1SubjetsTLV[0].M() << " " <<  jet1SubjetsTLV[1].M();
				jet2SubjetsTLV.push_back( JETS[1].subjet0 );
				jet2SubjetsTLV.push_back( JETS[1].subjet1 );
				sort(jet2SubjetsTLV.begin(), jet2SubjetsTLV.end(), [](const TLorentzVector &p1, const TLorentzVector &p2) { return p1.M() > p2.M(); }); 

				if( ( jet1SubjetsTLV.size() > 0 ) && ( jet2SubjetsTLV.size() > 0 ) ) {

					// Subjet Pt ratio, subjet mass ratio 
					//LogWarning("subjet0") <<  jet1SubjetsTLV[0].Pt() << " " <<  jet1SubjetsTLV[1].Pt();
					jet1SubjetPtRatio = min( jet1SubjetsTLV[0].Pt(), jet1SubjetsTLV[1].Pt() ) / max( jet1SubjetsTLV[0].Pt(), jet1SubjetsTLV[1].Pt() );
					jet1SubjetMass21Ratio =  jet1SubjetsTLV[1].M() / jet1SubjetsTLV[0].M() ;
					jet1Subjet112MassRatio = jet1SubjetsTLV[0].M() / ( jet1SubjetsTLV[0] + jet1SubjetsTLV[1] ).M();
					jet1Subjet1JetMassRatio = jet1SubjetsTLV[0].M() /jet1Mass;
					jet1Subjet212MassRatio = jet1SubjetsTLV[1].M() / ( jet1SubjetsTLV[0] + jet1SubjetsTLV[1] ).M();
					jet1Subjet2JetMassRatio = jet1SubjetsTLV[1].M() /jet1Mass;

					jet2SubjetPtRatio = min( jet2SubjetsTLV[0].Pt(), jet2SubjetsTLV[1].Pt() ) / max( jet2SubjetsTLV[0].Pt(), jet2SubjetsTLV[1].Pt() );
					jet2SubjetMass21Ratio =  jet2SubjetsTLV[1].M()/jet2SubjetsTLV[0].M();
					jet2Subjet112MassRatio = jet2SubjetsTLV[0].M()/ ( jet2SubjetsTLV[0] + jet2SubjetsTLV[1] ).M();
					jet2Subjet1JetMassRatio = jet2SubjetsTLV[0].M()/jet2Mass;
					jet2Subjet212MassRatio = jet2SubjetsTLV[1].M()/ ( jet2SubjetsTLV[0] + jet2SubjetsTLV[1] ).M();
					jet2Subjet2JetMassRatio = jet2SubjetsTLV[1].M()/jet2Mass;
					//////////////////////////////////////////////////////////////////////////////////

				
					// SUbjet Polarization angle & dalitz variables
					double m1 = jet1SubjetsTLV[0].M();
					double m2 = jet1SubjetsTLV[1].M();
					double m3 = jet2SubjetsTLV[0].M();
					double m4 = jet2SubjetsTLV[1].M();

					double m12 = ( jet1SubjetsTLV[0] + jet1SubjetsTLV[1] ).M() ;
					double m34 = ( jet2SubjetsTLV[0] + jet2SubjetsTLV[1] ).M() ;
					double m134 = ( jet1SubjetsTLV[0] + jet2SubjetsTLV[0] + jet2SubjetsTLV[1] ).M() ;
					double m123 = ( jet1SubjetsTLV[0] + jet1SubjetsTLV[1] + jet2SubjetsTLV[0] ).M() ;
					double m124 = ( jet1SubjetsTLV[0] + jet1SubjetsTLV[1] + jet2SubjetsTLV[1] ).M() ;
					double m234 = ( jet1SubjetsTLV[1] + jet2SubjetsTLV[0] + jet2SubjetsTLV[1] ).M() ;
					double m1234 = ( jet1SubjetsTLV[0] + jet1SubjetsTLV[1] + jet2SubjetsTLV[0] + jet2SubjetsTLV[1] ).M() ;
					
					// subjet polarization angles
					double tmpX1 = pow(m1234,2) * ( ( 2 * ( pow(m12,2) + pow(m1,2) ) ) - pow(m2,2) ) ;
					double tmpX2 = pow(m12,2) * ( pow(m134,2) - pow(m34,2) - pow(m1,2) );
					double tmpX3 = pow(m1234,4) - ( pow(m12,2) * pow(m34,2) ) ; 
					double tmpX4 = ( 2 * ( pow(m12,2) + pow(m1,2) ) ) - pow(m2,2);
					double tmpX5 = pow(m12,2) * pow(m1,2);
					double tmpx1 = tmpX1 - (tmpX2/2);
					double tmpx2 = tmpX3 * ( pow(tmpX4,2) - tmpX5 );
					cosPhi13412 = TMath::Abs( tmpx1 / TMath::Sqrt( tmpx2 ) );

					double tmpY1 = pow(m1234,2) * ( ( 2 * ( pow(m34,2) + pow(m3,2) ) ) - pow(m4,2) ) ;
					double tmpY2 = pow(m34,2) * ( pow(m123,2) - pow(m12,2) - pow(m3,2) );
					double tmpY3 = pow(m1234,4) - ( pow(m12,2) * pow(m34,2) ) ; 
					double tmpY4 = ( 2 * ( pow(m34,2) + pow(m3,2) ) ) - pow(m4,2);
					double tmpY5 = pow(m34,2) * pow(m3,2);
					double tmpy1 = tmpY1 - (tmpY2/2);
					double tmpy2 = tmpY3 * ( pow(tmpY4,2) - tmpY5 );
					cosPhi31234 = TMath::Abs( tmpy1 / TMath::Sqrt( tmpy2 ) );

					// dalitz
					double tmptilde1 = pow( m1, 2 ) + pow( m2, 2) + pow( m34, 2 ) + pow( m1234, 2);
					double mtilde12 = pow( m12, 2 ) / tmptilde1;
					double mtilde134 = pow( m134, 2 ) / tmptilde1;
					double mtilde234 = pow( m234, 2 ) / tmptilde1;
					//double tmpMtilde = mtilde12 + mtilde134 + mtilde234;
					//LogWarning("dalitz0") << tmpMtilde << " " << mtilde12 << " " << mtilde134 << " " <<  mtilde234;
					dalitz1.push_back( mtilde12 );
					dalitz1.push_back( mtilde134 );
					dalitz1.push_back( mtilde234 );
					sort( dalitz1.begin(), dalitz1.end(), [](const double &p1, const double &p2) { return p1 > p2; }); 
					//LogWarning("dalitz1") << dalitz1[0] << " " << dalitz1[1] << " " << dalitz1[2];

					dalitzX1 = ( dalitz1[1] + ( 2 * dalitz1[0] ) ) / TMath::Sqrt(3);
					//LogWarning("X1") << dalitzX1 << " " << dalitz1[1] ;
					dalitzX2 = ( dalitz1[2] + ( 2 * dalitz1[0] ) ) / TMath::Sqrt(3);
					//LogWarning("X2") << dalitzX2 << " " << dalitz1[2] ;
					dalitzX3 = ( dalitz1[0] + ( 2 * dalitz1[1] ) ) / TMath::Sqrt(3);
					//LogWarning("X3") << dalitzX3 << " " << dalitz1[0] ;
					dalitzX4 = ( dalitz1[2] + ( 2 * dalitz1[1] ) ) / TMath::Sqrt(3);
					//LogWarning("X4") << dalitzX4 << " " << dalitz1[2] ;
					dalitzX5 = ( dalitz1[0] + ( 2 * dalitz1[2] ) ) / TMath::Sqrt(3);
					//LogWarning("X5") << dalitzX5 << " " << dalitz1[0] ;
					dalitzX6 = ( dalitz1[1] + ( 2 * dalitz1[2] ) ) / TMath::Sqrt(3);
					//LogWarning("X6") << dalitzX6 << " " << dalitz1[1] ;


					double tmptilde2 = pow( m3, 2 ) + pow( m4, 2) + pow( m12, 2 ) + pow( m1234, 2);
					double mtilde34 = pow( m34, 2 ) / tmptilde2;
					double mtilde123 = pow( m123, 2 ) / tmptilde2;
					double mtilde124 = pow( m124, 2 ) / tmptilde2;
					dalitz2.push_back( mtilde34 );
					dalitz2.push_back( mtilde123 );
					dalitz2.push_back( mtilde124 );
					sort( dalitz2.begin(), dalitz2.end(), [](const double &p1, const double &p2) { return p1 > p2; }); 

					dalitzY1 = ( dalitz2[1] + ( 2 * dalitz2[0] ) ) / TMath::Sqrt(3);
					dalitzY2 = ( dalitz2[2] + ( 2 * dalitz2[0] ) ) / TMath::Sqrt(3);
					dalitzY3 = ( dalitz2[0] + ( 2 * dalitz2[1] ) ) / TMath::Sqrt(3);
					dalitzY4 = ( dalitz2[2] + ( 2 * dalitz2[1] ) ) / TMath::Sqrt(3);
					dalitzY5 = ( dalitz2[0] + ( 2 * dalitz2[2] ) ) / TMath::Sqrt(3);
					dalitzY6 = ( dalitz2[1] + ( 2 * dalitz2[2] ) ) / TMath::Sqrt(3);
					///////////////////////////////////////////////////////////////////////////////////////

				}

				///// Variables for tree
				event		= *ievent;
				run		= *Run;
				lumi		= *Lumi;
				jet1Pt 		= JETS[0].p4.Pt();
				jet1Eta 	= JETS[0].p4.Eta();
				jet1Phi 	= JETS[0].p4.Phi();
				jet1E 		= JETS[0].p4.E();
				jet2Pt 		= JETS[1].p4.Pt();
				jet2Eta 	= JETS[1].p4.Eta();
				jet2Phi 	= JETS[1].p4.Phi();
				jet2E 		= JETS[1].p4.E();
				subjet11Pt	= jet1SubjetsTLV[0].Pt();
				subjet11Eta	= jet1SubjetsTLV[0].Eta();
				subjet11Phi	= jet1SubjetsTLV[0].Phi();
				subjet11E	= jet1SubjetsTLV[0].E();
				subjet12Pt	= jet1SubjetsTLV[1].Pt();
				subjet12Eta	= jet1SubjetsTLV[1].Eta();
				subjet12Phi	= jet1SubjetsTLV[1].Phi();
				subjet12E	= jet1SubjetsTLV[1].E();
				subjet21Pt	= jet2SubjetsTLV[0].Pt();
				subjet21Eta	= jet2SubjetsTLV[0].Eta();
				subjet21Phi	= jet2SubjetsTLV[0].Phi();
				subjet21E	= jet2SubjetsTLV[0].E();
				subjet22Pt	= jet2SubjetsTLV[1].Pt();
				subjet22Eta	= jet2SubjetsTLV[1].Eta();
				subjet22Phi	= jet2SubjetsTLV[1].Phi();
				subjet22E	= jet2SubjetsTLV[1].E();

				if ( mkTree ) {
					RUNAtree->Fill();

				} else {

					histos1D_[ "HT_cutDijet" ]->Fill( HT, scale  );
					histos1D_[ "NPV_cutDijet" ]->Fill( numPV, scale );
					histos1D_[ "jetNum_cutDijet" ]->Fill( numJets, scale );
					histos1D_[ "jet1Pt_cutDijet" ]->Fill( JETS[0].p4.Pt(), scale  );
					histos1D_[ "jet1Eta_cutDijet" ]->Fill( JETS[0].p4.Eta(), scale  );
					histos1D_[ "jet1Mass_cutDijet" ]->Fill( JETS[0].mass, scale );
					histos1D_[ "jet2Pt_cutDijet" ]->Fill( JETS[1].p4.Pt(), scale  );
					histos1D_[ "jet2Eta_cutDijet" ]->Fill( JETS[1].p4.Eta(), scale  );
					histos1D_[ "jet2Mass_cutDijet" ]->Fill( JETS[1].mass, scale );

					histos1D_[ "massAsymmetry_cutDijet" ]->Fill( massAsym, scale  );
					histos1D_[ "massAve_cutDijet" ]->Fill( massAve, scale  );
					histos1D_[ "cosThetaStar_cutDijet" ]->Fill( cosThetaStar, scale  );
					histos1D_[ "jet1Tau1_cutDijet" ]->Fill( JETS[0].tau1, scale );
					histos1D_[ "jet1Tau2_cutDijet" ]->Fill( JETS[0].tau2, scale );
					histos1D_[ "jet1Tau3_cutDijet" ]->Fill( JETS[0].tau3, scale );
					histos1D_[ "jet1Tau21_cutDijet" ]->Fill( jet1Tau21, scale );
					histos1D_[ "jet1Tau31_cutDijet" ]->Fill( jet1Tau31, scale );
					histos1D_[ "jet1Tau32_cutDijet" ]->Fill( jet1Tau32, scale );
					histos1D_[ "jet2Tau1_cutDijet" ]->Fill( JETS[1].tau1, scale );
					histos1D_[ "jet2Tau2_cutDijet" ]->Fill( JETS[1].tau2, scale );
					histos1D_[ "jet2Tau3_cutDijet" ]->Fill( JETS[1].tau3, scale );
					histos1D_[ "jet2Tau21_cutDijet" ]->Fill( jet2Tau21, scale );
					histos1D_[ "jet2Tau31_cutDijet" ]->Fill( jet2Tau31, scale );
					histos1D_[ "jet2Tau32_cutDijet" ]->Fill( jet2Tau32, scale );
					histos1D_[ "deltaEtaDijet_cutDijet" ]->Fill( deltaEtaDijet, scale );
					histos1D_[ "jet1SubjetPtRatio_cutDijet" ]->Fill( jet1SubjetPtRatio, scale );
					histos1D_[ "jet2SubjetPtRatio_cutDijet" ]->Fill( jet2SubjetPtRatio, scale );
					histos1D_[ "subjetPtRatio_cutDijet" ]->Fill( jet1SubjetPtRatio, scale );
					histos1D_[ "subjetPtRatio_cutDijet" ]->Fill( jet2SubjetPtRatio, scale );

					histos2D_[ "jetTrimmedMassHT_cutDijet" ]->Fill( trimmedMass, HT, scale  );
					histos2D_[ "leadMassHT_cutDijet" ]->Fill( leadMass, HT, scale  );
					histos2D_[ "massAveHT_cutDijet" ]->Fill( massAve, HT, scale  );

					histos2D_[ "massAvevsJet1Mass_cutDijet" ]->Fill( massAve, jet1Mass, scale );
					histos2D_[ "massAvevsJet2Mass_cutDijet" ]->Fill( massAve, jet2Mass, scale );
					histos2D_[ "massAvevsMassAsym_cutDijet" ]->Fill( massAve, massAsym, scale );
					histos2D_[ "massAvevsDEta_cutDijet" ]->Fill( massAve, deltaEtaDijet, scale );
					histos2D_[ "massAvevsCosThetaStar_cutDijet" ]->Fill( massAve, cosThetaStar, scale );
					histos2D_[ "massAvevsJet1Tau21_cutDijet" ]->Fill( massAve, jet1Tau21, scale );
					histos2D_[ "massAvevsJet1Tau31_cutDijet" ]->Fill( massAve, jet1Tau31, scale );
					histos2D_[ "massAvevsJet1Tau32_cutDijet" ]->Fill( massAve, jet1Tau32, scale );
					histos2D_[ "massAvevsJet2Tau21_cutDijet" ]->Fill( massAve, jet1Tau21, scale );
					histos2D_[ "massAvevsJet2Tau31_cutDijet" ]->Fill( massAve, jet1Tau31, scale );
					histos2D_[ "massAvevsJet2Tau32_cutDijet" ]->Fill( massAve, jet1Tau32, scale );
					histos2D_[ "massAvevsJet1SubjetPtRatio_cutDijet" ]->Fill( massAve, jet1SubjetPtRatio, scale );
					histos2D_[ "massAvevsJet2SubjetPtRatio_cutDijet" ]->Fill( massAve, jet2SubjetPtRatio, scale );
					histos2D_[ "jet1vs2Mass_cutDijet" ]->Fill( jet1Mass, jet2Mass, scale );
					histos2D_[ "dijetCorr_cutDijet" ]->Fill( JETS[0].p4.Eta(), JETS[1].p4.Eta(), scale );
					histos2D_[ "dijetCorrPhi_cutDijet" ]->Fill( JETS[0].p4.Phi(), JETS[1].p4.Phi(), scale );

					histos1D_[ "subjetPolAngle13412_cutDijet" ]->Fill( cosPhi13412, scale );
					histos1D_[ "subjetPolAngle31234_cutDijet" ]->Fill( cosPhi31234, scale );
					histos1D_[ "mu1_cutDijet" ]->Fill( dalitz1[0], scale );
					histos1D_[ "mu2_cutDijet" ]->Fill( dalitz1[1], scale );
					histos1D_[ "mu3_cutDijet" ]->Fill( dalitz1[2], scale );
					histos1D_[ "mu4_cutDijet" ]->Fill( dalitz2[0], scale );
					histos1D_[ "mu5_cutDijet" ]->Fill( dalitz2[1], scale );
					histos1D_[ "mu6_cutDijet" ]->Fill( dalitz2[2], scale );
					histos2D_[ "subjetPolAngle13412vs31234_cutDijet" ]->Fill( cosPhi13412, cosPhi31234, scale );
					histos2D_[ "subjetPolAngle31234vsSubjetPtRatio_cutDijet" ]->Fill( cosPhi31234, jet2SubjetPtRatio, scale );
					histos2D_[ "mu1234_cutDijet" ]->Fill( dalitz1[0], dalitz1[2], scale );
					histos2D_[ "mu1234_cutDijet" ]->Fill( dalitz1[1], dalitz1[2], scale );
					histos2D_[ "mu1234_cutDijet" ]->Fill( dalitz1[0], dalitz1[1], scale );
					histos2D_[ "dalitz1234_cutDijet" ]->Fill( dalitzX1, dalitz1[1], scale );
					histos2D_[ "dalitz1234_cutDijet" ]->Fill( dalitzX2, dalitz1[2], scale );
					histos2D_[ "dalitz1234_cutDijet" ]->Fill( dalitzX3, dalitz1[0], scale );
					histos2D_[ "dalitz1234_cutDijet" ]->Fill( dalitzX4, dalitz1[2], scale );
					histos2D_[ "dalitz1234_cutDijet" ]->Fill( dalitzX5, dalitz1[0], scale );
					histos2D_[ "dalitz1234_cutDijet" ]->Fill( dalitzX6, dalitz1[1], scale );
					histos2D_[ "mu3412_cutDijet" ]->Fill( dalitz2[0], dalitz2[2], scale );
					histos2D_[ "mu3412_cutDijet" ]->Fill( dalitz2[1], dalitz2[2], scale );
					histos2D_[ "mu3412_cutDijet" ]->Fill( dalitz2[0], dalitz2[1], scale );
					histos2D_[ "dalitz3412_cutDijet" ]->Fill( dalitzY1, dalitz2[1], scale );
					histos2D_[ "dalitz3412_cutDijet" ]->Fill( dalitzY2, dalitz2[2], scale );
					histos2D_[ "dalitz3412_cutDijet" ]->Fill( dalitzY3, dalitz2[0], scale );
					histos2D_[ "dalitz3412_cutDijet" ]->Fill( dalitzY4, dalitz2[2], scale );
					histos2D_[ "dalitz3412_cutDijet" ]->Fill( dalitzY5, dalitz2[0], scale );
					histos2D_[ "dalitz3412_cutDijet" ]->Fill( dalitzY6, dalitz2[1], scale );

					if( massAsym < cutAsymvalue ){
						cutmap["Asymmetry"] += 1;

						histos1D_[ "HT_cutMassAsym" ]->Fill( HT, scale  );
						histos1D_[ "NPV_cutMassAsym" ]->Fill( numPV, scale );
						histos1D_[ "jetNum_cutMassAsym" ]->Fill( numJets, scale );
						histos1D_[ "jet1Pt_cutMassAsym" ]->Fill( JETS[0].p4.Pt(), scale  );
						histos1D_[ "jet1Eta_cutMassAsym" ]->Fill( JETS[0].p4.Eta(), scale  );
						histos1D_[ "jet1Mass_cutMassAsym" ]->Fill( JETS[0].mass, scale );
						histos1D_[ "jet2Pt_cutMassAsym" ]->Fill( JETS[1].p4.Pt(), scale  );
						histos1D_[ "jet2Eta_cutMassAsym" ]->Fill( JETS[1].p4.Eta(), scale  );
						histos1D_[ "jet2Mass_cutMassAsym" ]->Fill( JETS[1].mass, scale );

						histos1D_[ "massAsymmetry_cutMassAsym" ]->Fill( massAsym, scale  );
						histos1D_[ "massAve_cutMassAsym" ]->Fill( massAve, scale  );
						histos1D_[ "cosThetaStar_cutMassAsym" ]->Fill( cosThetaStar, scale  );
						histos1D_[ "jet1Tau1_cutMassAsym" ]->Fill( JETS[0].tau1, scale );
						histos1D_[ "jet1Tau2_cutMassAsym" ]->Fill( JETS[0].tau2, scale );
						histos1D_[ "jet1Tau3_cutMassAsym" ]->Fill( JETS[0].tau3, scale );
						histos1D_[ "jet1Tau21_cutMassAsym" ]->Fill( jet1Tau21, scale );
						histos1D_[ "jet1Tau31_cutMassAsym" ]->Fill( jet1Tau31, scale );
						histos1D_[ "jet1Tau32_cutMassAsym" ]->Fill( jet1Tau32, scale );
						histos1D_[ "jet2Tau1_cutMassAsym" ]->Fill( JETS[1].tau1, scale );
						histos1D_[ "jet2Tau2_cutMassAsym" ]->Fill( JETS[1].tau2, scale );
						histos1D_[ "jet2Tau3_cutMassAsym" ]->Fill( JETS[1].tau3, scale );
						histos1D_[ "jet2Tau21_cutMassAsym" ]->Fill( jet2Tau21, scale );
						histos1D_[ "jet2Tau31_cutMassAsym" ]->Fill( jet2Tau31, scale );
						histos1D_[ "jet2Tau32_cutMassAsym" ]->Fill( jet2Tau32, scale );
						histos1D_[ "deltaEtaDijet_cutMassAsym" ]->Fill( deltaEtaDijet, scale );
						histos1D_[ "jet1SubjetPtRatio_cutMassAsym" ]->Fill( jet1SubjetPtRatio, scale );
						histos1D_[ "jet2SubjetPtRatio_cutMassAsym" ]->Fill( jet2SubjetPtRatio, scale );
						histos1D_[ "subjetPtRatio_cutMassAsym" ]->Fill( jet1SubjetPtRatio, scale );
						histos1D_[ "subjetPtRatio_cutMassAsym" ]->Fill( jet2SubjetPtRatio, scale );

						histos2D_[ "jetTrimmedMassHT_cutMassAsym" ]->Fill( trimmedMass, HT, scale  );
						histos2D_[ "leadMassHT_cutMassAsym" ]->Fill( leadMass, HT, scale  );
						histos2D_[ "massAveHT_cutMassAsym" ]->Fill( massAve, HT, scale  );

						histos2D_[ "massAvevsJet1Mass_cutMassAsym" ]->Fill( massAve, jet1Mass, scale );
						histos2D_[ "massAvevsJet2Mass_cutMassAsym" ]->Fill( massAve, jet2Mass, scale );
						histos2D_[ "massAvevsMassAsym_cutMassAsym" ]->Fill( massAve, massAsym, scale );
						histos2D_[ "massAvevsDEta_cutMassAsym" ]->Fill( massAve, deltaEtaDijet, scale );
						histos2D_[ "massAvevsCosThetaStar_cutMassAsym" ]->Fill( massAve, cosThetaStar, scale );
						histos2D_[ "massAvevsJet1Tau21_cutMassAsym" ]->Fill( massAve, jet1Tau21, scale );
						histos2D_[ "massAvevsJet1Tau31_cutMassAsym" ]->Fill( massAve, jet1Tau31, scale );
						histos2D_[ "massAvevsJet1Tau32_cutMassAsym" ]->Fill( massAve, jet1Tau32, scale );
						histos2D_[ "massAvevsJet2Tau21_cutMassAsym" ]->Fill( massAve, jet1Tau21, scale );
						histos2D_[ "massAvevsJet2Tau31_cutMassAsym" ]->Fill( massAve, jet1Tau31, scale );
						histos2D_[ "massAvevsJet2Tau32_cutMassAsym" ]->Fill( massAve, jet1Tau32, scale );
						histos2D_[ "massAvevsJet1SubjetPtRatio_cutMassAsym" ]->Fill( massAve, jet1SubjetPtRatio, scale );
						histos2D_[ "massAvevsJet2SubjetPtRatio_cutMassAsym" ]->Fill( massAve, jet2SubjetPtRatio, scale );
						histos2D_[ "jet1vs2Mass_cutMassAsym" ]->Fill( jet1Mass, jet2Mass, scale );
						histos2D_[ "dijetCorr_cutMassAsym" ]->Fill( JETS[0].p4.Eta(), JETS[1].p4.Eta(), scale );
						histos2D_[ "dijetCorrPhi_cutMassAsym" ]->Fill( JETS[0].p4.Phi(), JETS[1].p4.Phi(), scale );

						if(  ( jet1Tau21 < cutTau21value ) && ( jet2Tau21 < cutTau21value ) ){

							cutmap["Tau21"] += 1;
							histos1D_[ "HT_cutTau21" ]->Fill( HT, scale  );
							histos1D_[ "NPV_cutTau21" ]->Fill( numPV, scale );
							histos1D_[ "jetNum_cutTau21" ]->Fill( numJets, scale );
							histos1D_[ "jet1Pt_cutTau21" ]->Fill( JETS[0].p4.Pt(), scale  );
							histos1D_[ "jet1Eta_cutTau21" ]->Fill( JETS[0].p4.Eta(), scale  );
							histos1D_[ "jet1Mass_cutTau21" ]->Fill( JETS[0].mass, scale );
							histos1D_[ "jet2Pt_cutTau21" ]->Fill( JETS[1].p4.Pt(), scale  );
							histos1D_[ "jet2Eta_cutTau21" ]->Fill( JETS[1].p4.Eta(), scale  );
							histos1D_[ "jet2Mass_cutTau21" ]->Fill( JETS[1].mass, scale );

							histos1D_[ "massAsymmetry_cutTau21" ]->Fill( massAsym, scale  );
							histos1D_[ "massAve_cutTau21" ]->Fill( massAve, scale  );
							histos1D_[ "cosThetaStar_cutTau21" ]->Fill( cosThetaStar, scale  );
							histos1D_[ "jet1Tau1_cutTau21" ]->Fill( JETS[0].tau1, scale );
							histos1D_[ "jet1Tau2_cutTau21" ]->Fill( JETS[0].tau2, scale );
							histos1D_[ "jet1Tau3_cutTau21" ]->Fill( JETS[0].tau3, scale );
							histos1D_[ "jet1Tau21_cutTau21" ]->Fill( jet1Tau21, scale );
							histos1D_[ "jet1Tau31_cutTau21" ]->Fill( jet1Tau31, scale );
							histos1D_[ "jet1Tau32_cutTau21" ]->Fill( jet1Tau32, scale );
							histos1D_[ "jet2Tau1_cutTau21" ]->Fill( JETS[1].tau1, scale );
							histos1D_[ "jet2Tau2_cutTau21" ]->Fill( JETS[1].tau2, scale );
							histos1D_[ "jet2Tau3_cutTau21" ]->Fill( JETS[1].tau3, scale );
							histos1D_[ "jet2Tau21_cutTau21" ]->Fill( jet2Tau21, scale );
							histos1D_[ "jet2Tau31_cutTau21" ]->Fill( jet2Tau31, scale );
							histos1D_[ "jet2Tau32_cutTau21" ]->Fill( jet2Tau32, scale );
							histos1D_[ "deltaEtaDijet_cutTau21" ]->Fill( deltaEtaDijet, scale );
							histos1D_[ "jet1SubjetPtRatio_cutTau21" ]->Fill( jet1SubjetPtRatio, scale );
							histos1D_[ "jet2SubjetPtRatio_cutTau21" ]->Fill( jet2SubjetPtRatio, scale );
							histos1D_[ "subjetPtRatio_cutTau21" ]->Fill( jet1SubjetPtRatio, scale );
							histos1D_[ "subjetPtRatio_cutTau21" ]->Fill( jet2SubjetPtRatio, scale );

							histos2D_[ "jetTrimmedMassHT_cutTau21" ]->Fill( trimmedMass, HT, scale  );
							histos2D_[ "leadMassHT_cutTau21" ]->Fill( leadMass, HT, scale  );
							histos2D_[ "massAveHT_cutTau21" ]->Fill( massAve, HT, scale  );

							histos2D_[ "massAvevsJet1Mass_cutTau21" ]->Fill( massAve, jet1Mass, scale );
							histos2D_[ "massAvevsJet2Mass_cutTau21" ]->Fill( massAve, jet2Mass, scale );
							histos2D_[ "massAvevsMassAsym_cutTau21" ]->Fill( massAve, massAsym, scale );
							histos2D_[ "massAvevsDEta_cutTau21" ]->Fill( massAve, deltaEtaDijet, scale );
							histos2D_[ "massAvevsCosThetaStar_cutTau21" ]->Fill( massAve, cosThetaStar, scale );
							histos2D_[ "massAvevsJet1Tau21_cutTau21" ]->Fill( massAve, jet1Tau21, scale );
							histos2D_[ "massAvevsJet1Tau31_cutTau21" ]->Fill( massAve, jet1Tau31, scale );
							histos2D_[ "massAvevsJet1Tau32_cutTau21" ]->Fill( massAve, jet1Tau32, scale );
							histos2D_[ "massAvevsJet2Tau21_cutTau21" ]->Fill( massAve, jet1Tau21, scale );
							histos2D_[ "massAvevsJet2Tau31_cutTau21" ]->Fill( massAve, jet1Tau31, scale );
							histos2D_[ "massAvevsJet2Tau32_cutTau21" ]->Fill( massAve, jet1Tau32, scale );
							histos2D_[ "massAvevsJet1SubjetPtRatio_cutTau21" ]->Fill( massAve, jet1SubjetPtRatio, scale );
							histos2D_[ "massAvevsJet2SubjetPtRatio_cutTau21" ]->Fill( massAve, jet2SubjetPtRatio, scale );
							histos2D_[ "jet1vs2Mass_cutTau21" ]->Fill( jet1Mass, jet2Mass, scale );
							histos2D_[ "dijetCorr_cutTau21" ]->Fill( JETS[0].p4.Eta(), JETS[1].p4.Eta(), scale );
							histos2D_[ "dijetCorrPhi_cutTau21" ]->Fill( JETS[0].p4.Phi(), JETS[1].p4.Phi(), scale );

							if( TMath::Abs( cosThetaStar ) < cutCosThetavalue ){
							
								cutmap["CosTheta"] += 1;
								histos1D_[ "HT_cutCosTheta" ]->Fill( HT, scale  );
								histos1D_[ "NPV_cutCosTheta" ]->Fill( numPV, scale );
								histos1D_[ "jetNum_cutCosTheta" ]->Fill( numJets, scale );
								histos1D_[ "jet1Pt_cutCosTheta" ]->Fill( JETS[0].p4.Pt(), scale  );
								histos1D_[ "jet1Eta_cutCosTheta" ]->Fill( JETS[0].p4.Eta(), scale  );
								histos1D_[ "jet1Mass_cutCosTheta" ]->Fill( JETS[0].mass, scale );
								histos1D_[ "jet2Pt_cutCosTheta" ]->Fill( JETS[1].p4.Pt(), scale  );
								histos1D_[ "jet2Eta_cutCosTheta" ]->Fill( JETS[1].p4.Eta(), scale  );
								histos1D_[ "jet2Mass_cutCosTheta" ]->Fill( JETS[1].mass, scale );

								histos1D_[ "massAsymmetry_cutCosTheta" ]->Fill( massAsym, scale  );
								histos1D_[ "massAve_cutCosTheta" ]->Fill( massAve, scale  );
								histos1D_[ "cosThetaStar_cutCosTheta" ]->Fill( cosThetaStar, scale  );
								histos1D_[ "jet1Tau1_cutCosTheta" ]->Fill( JETS[0].tau1, scale );
								histos1D_[ "jet1Tau2_cutCosTheta" ]->Fill( JETS[0].tau2, scale );
								histos1D_[ "jet1Tau3_cutCosTheta" ]->Fill( JETS[0].tau3, scale );
								histos1D_[ "jet1Tau21_cutCosTheta" ]->Fill( jet1Tau21, scale );
								histos1D_[ "jet1Tau31_cutCosTheta" ]->Fill( jet1Tau31, scale );
								histos1D_[ "jet1Tau32_cutCosTheta" ]->Fill( jet1Tau32, scale );
								histos1D_[ "jet2Tau1_cutCosTheta" ]->Fill( JETS[1].tau1, scale );
								histos1D_[ "jet2Tau2_cutCosTheta" ]->Fill( JETS[1].tau2, scale );
								histos1D_[ "jet2Tau3_cutCosTheta" ]->Fill( JETS[1].tau3, scale );
								histos1D_[ "jet2Tau21_cutCosTheta" ]->Fill( jet2Tau21, scale );
								histos1D_[ "jet2Tau31_cutCosTheta" ]->Fill( jet2Tau31, scale );
								histos1D_[ "jet2Tau32_cutCosTheta" ]->Fill( jet2Tau32, scale );
								histos1D_[ "deltaEtaDijet_cutCosTheta" ]->Fill( deltaEtaDijet, scale );
								histos1D_[ "jet1SubjetPtRatio_cutCosTheta" ]->Fill( jet1SubjetPtRatio, scale );
								histos1D_[ "jet2SubjetPtRatio_cutCosTheta" ]->Fill( jet2SubjetPtRatio, scale );
								histos1D_[ "subjetPtRatio_cutCosTheta" ]->Fill( jet1SubjetPtRatio, scale );
								histos1D_[ "subjetPtRatio_cutCosTheta" ]->Fill( jet2SubjetPtRatio, scale );

								histos2D_[ "jetTrimmedMassHT_cutCosTheta" ]->Fill( trimmedMass, HT, scale  );
								histos2D_[ "leadMassHT_cutCosTheta" ]->Fill( leadMass, HT, scale  );
								histos2D_[ "massAveHT_cutCosTheta" ]->Fill( massAve, HT, scale  );

								histos2D_[ "massAvevsJet1Mass_cutCosTheta" ]->Fill( massAve, jet1Mass, scale );
								histos2D_[ "massAvevsJet2Mass_cutCosTheta" ]->Fill( massAve, jet2Mass, scale );
								histos2D_[ "massAvevsMassAsym_cutCosTheta" ]->Fill( massAve, massAsym, scale );
								histos2D_[ "massAvevsDEta_cutCosTheta" ]->Fill( massAve, deltaEtaDijet, scale );
								histos2D_[ "massAvevsCosThetaStar_cutCosTheta" ]->Fill( massAve, cosThetaStar, scale );
								histos2D_[ "massAvevsJet1Tau21_cutCosTheta" ]->Fill( massAve, jet1Tau21, scale );
								histos2D_[ "massAvevsJet1Tau31_cutCosTheta" ]->Fill( massAve, jet1Tau31, scale );
								histos2D_[ "massAvevsJet1Tau32_cutCosTheta" ]->Fill( massAve, jet1Tau32, scale );
								histos2D_[ "massAvevsJet2Tau21_cutCosTheta" ]->Fill( massAve, jet1Tau21, scale );
								histos2D_[ "massAvevsJet2Tau31_cutCosTheta" ]->Fill( massAve, jet1Tau31, scale );
								histos2D_[ "massAvevsJet2Tau32_cutCosTheta" ]->Fill( massAve, jet1Tau32, scale );
								histos2D_[ "massAvevsJet1SubjetPtRatio_cutCosTheta" ]->Fill( massAve, jet1SubjetPtRatio, scale );
								histos2D_[ "massAvevsJet2SubjetPtRatio_cutCosTheta" ]->Fill( massAve, jet2SubjetPtRatio, scale );
								histos2D_[ "jet1vs2Mass_cutCosTheta" ]->Fill( jet1Mass, jet2Mass, scale );
								histos2D_[ "dijetCorr_cutCosTheta" ]->Fill( JETS[0].p4.Eta(), JETS[1].p4.Eta(), scale );
								histos2D_[ "dijetCorrPhi_cutCosTheta" ]->Fill( JETS[0].p4.Phi(), JETS[1].p4.Phi(), scale );
							
								if( ( deltaEtaDijet  > cutDEtavalue ) ){

									cutmap["DEta"] += 1;
									histos1D_[ "HT_cutDEta" ]->Fill( HT, scale  );
									histos1D_[ "NPV_cutDEta" ]->Fill( numPV, scale );
									histos1D_[ "jetNum_cutDEta" ]->Fill( numJets, scale );
									histos1D_[ "jet1Pt_cutDEta" ]->Fill( JETS[0].p4.Pt(), scale  );
									histos1D_[ "jet1Eta_cutDEta" ]->Fill( JETS[0].p4.Eta(), scale  );
									histos1D_[ "jet1Mass_cutDEta" ]->Fill( JETS[0].mass, scale );
									histos1D_[ "jet2Pt_cutDEta" ]->Fill( JETS[1].p4.Pt(), scale  );
									histos1D_[ "jet2Eta_cutDEta" ]->Fill( JETS[1].p4.Eta(), scale  );
									histos1D_[ "jet2Mass_cutDEta" ]->Fill( JETS[1].mass, scale );

									histos1D_[ "massAsymmetry_cutDEta" ]->Fill( massAsym, scale  );
									histos1D_[ "massAve_cutDEta" ]->Fill( massAve, scale  );
									histos1D_[ "massAve_cutDEta_1GeVBin" ]->Fill( massAve, scale  );
									histos1D_[ "cosThetaStar_cutDEta" ]->Fill( cosThetaStar, scale  );
									histos1D_[ "jet1Tau1_cutDEta" ]->Fill( JETS[0].tau1, scale );
									histos1D_[ "jet1Tau2_cutDEta" ]->Fill( JETS[0].tau2, scale );
									histos1D_[ "jet1Tau3_cutDEta" ]->Fill( JETS[0].tau3, scale );
									histos1D_[ "jet1Tau21_cutDEta" ]->Fill( jet1Tau21, scale );
									histos1D_[ "jet1Tau31_cutDEta" ]->Fill( jet1Tau31, scale );
									histos1D_[ "jet1Tau32_cutDEta" ]->Fill( jet1Tau32, scale );
									histos1D_[ "jet2Tau1_cutDEta" ]->Fill( JETS[1].tau1, scale );
									histos1D_[ "jet2Tau2_cutDEta" ]->Fill( JETS[1].tau2, scale );
									histos1D_[ "jet2Tau3_cutDEta" ]->Fill( JETS[1].tau3, scale );
									histos1D_[ "jet2Tau21_cutDEta" ]->Fill( jet2Tau21, scale );
									histos1D_[ "jet2Tau31_cutDEta" ]->Fill( jet2Tau31, scale );
									histos1D_[ "jet2Tau32_cutDEta" ]->Fill( jet2Tau32, scale );
									histos1D_[ "deltaEtaDijet_cutDEta" ]->Fill( deltaEtaDijet, scale );
									histos1D_[ "jet1SubjetPtRatio_cutDEta" ]->Fill( jet1SubjetPtRatio, scale );
									histos1D_[ "jet2SubjetPtRatio_cutDEta" ]->Fill( jet2SubjetPtRatio, scale );
									histos1D_[ "subjetPtRatio_cutDEta" ]->Fill( jet1SubjetPtRatio, scale );
									histos1D_[ "subjetPtRatio_cutDEta" ]->Fill( jet2SubjetPtRatio, scale );

									histos2D_[ "jetTrimmedMassHT_cutDEta" ]->Fill( trimmedMass, HT, scale  );
									histos2D_[ "leadMassHT_cutDEta" ]->Fill( leadMass, HT, scale  );
									histos2D_[ "massAveHT_cutDEta" ]->Fill( massAve, HT, scale  );

									histos2D_[ "massAvevsJet1Mass_cutDEta" ]->Fill( massAve, jet1Mass, scale );
									histos2D_[ "massAvevsJet2Mass_cutDEta" ]->Fill( massAve, jet2Mass, scale );
									histos2D_[ "massAvevsMassAsym_cutDEta" ]->Fill( massAve, massAsym, scale );
									histos2D_[ "massAvevsDEta_cutDEta" ]->Fill( massAve, deltaEtaDijet, scale );
									histos2D_[ "massAvevsCosThetaStar_cutDEta" ]->Fill( massAve, cosThetaStar, scale );
									histos2D_[ "massAvevsJet1Tau21_cutDEta" ]->Fill( massAve, jet1Tau21, scale );
									histos2D_[ "massAvevsJet1Tau31_cutDEta" ]->Fill( massAve, jet1Tau31, scale );
									histos2D_[ "massAvevsJet1Tau32_cutDEta" ]->Fill( massAve, jet1Tau32, scale );
									histos2D_[ "massAvevsJet2Tau21_cutDEta" ]->Fill( massAve, jet1Tau21, scale );
									histos2D_[ "massAvevsJet2Tau31_cutDEta" ]->Fill( massAve, jet1Tau31, scale );
									histos2D_[ "massAvevsJet2Tau32_cutDEta" ]->Fill( massAve, jet1Tau32, scale );
									histos2D_[ "massAvevsJet1SubjetPtRatio_cutDEta" ]->Fill( massAve, jet1SubjetPtRatio, scale );
									histos2D_[ "massAvevsJet2SubjetPtRatio_cutDEta" ]->Fill( massAve, jet2SubjetPtRatio, scale );
									histos2D_[ "jet1vs2Mass_cutDEta" ]->Fill( jet1Mass, jet2Mass, scale );
									histos2D_[ "dijetCorr_cutDEta" ]->Fill( JETS[0].p4.Eta(), JETS[1].p4.Eta(), scale );
									histos2D_[ "dijetCorrPhi_cutDEta" ]->Fill( JETS[0].p4.Phi(), JETS[1].p4.Phi(), scale );
							
									if ( jet1btagCSV > cutBtagvalue || jet2btagCSV > cutBtagvalue ){

										cutmap["Btag"] += 1;
										histos1D_[ "HT_cutBtag" ]->Fill( HT, scale  );
										histos1D_[ "NPV_cutBtag" ]->Fill( numPV, scale );
										histos1D_[ "jetNum_cutBtag" ]->Fill( numJets, scale );
										histos1D_[ "jet1Pt_cutBtag" ]->Fill( JETS[0].p4.Pt(), scale  );
										histos1D_[ "jet1Eta_cutBtag" ]->Fill( JETS[0].p4.Eta(), scale  );
										histos1D_[ "jet1Mass_cutBtag" ]->Fill( JETS[0].mass, scale );
										histos1D_[ "jet2Pt_cutBtag" ]->Fill( JETS[1].p4.Pt(), scale  );
										histos1D_[ "jet2Eta_cutBtag" ]->Fill( JETS[1].p4.Eta(), scale  );
										histos1D_[ "jet2Mass_cutBtag" ]->Fill( JETS[1].mass, scale );

										histos1D_[ "massAsymmetry_cutBtag" ]->Fill( massAsym, scale  );
										histos1D_[ "massAve_cutBtag" ]->Fill( massAve, scale  );
										histos1D_[ "cosThetaStar_cutBtag" ]->Fill( cosThetaStar, scale  );
										histos1D_[ "jet1Tau1_cutBtag" ]->Fill( JETS[0].tau1, scale );
										histos1D_[ "jet1Tau2_cutBtag" ]->Fill( JETS[0].tau2, scale );
										histos1D_[ "jet1Tau3_cutBtag" ]->Fill( JETS[0].tau3, scale );
										histos1D_[ "jet1Tau21_cutBtag" ]->Fill( jet1Tau21, scale );
										histos1D_[ "jet1Tau31_cutBtag" ]->Fill( jet1Tau31, scale );
										histos1D_[ "jet1Tau32_cutBtag" ]->Fill( jet1Tau32, scale );
										histos1D_[ "jet2Tau1_cutBtag" ]->Fill( JETS[1].tau1, scale );
										histos1D_[ "jet2Tau2_cutBtag" ]->Fill( JETS[1].tau2, scale );
										histos1D_[ "jet2Tau3_cutBtag" ]->Fill( JETS[1].tau3, scale );
										histos1D_[ "jet2Tau21_cutBtag" ]->Fill( jet2Tau21, scale );
										histos1D_[ "jet2Tau31_cutBtag" ]->Fill( jet2Tau31, scale );
										histos1D_[ "jet2Tau32_cutBtag" ]->Fill( jet2Tau32, scale );
										histos1D_[ "deltaEtaDijet_cutBtag" ]->Fill( deltaEtaDijet, scale );
										histos1D_[ "jet1SubjetPtRatio_cutBtag" ]->Fill( jet1SubjetPtRatio, scale );
										histos1D_[ "jet2SubjetPtRatio_cutBtag" ]->Fill( jet2SubjetPtRatio, scale );
										histos1D_[ "subjetPtRatio_cutBtag" ]->Fill( jet1SubjetPtRatio, scale );
										histos1D_[ "subjetPtRatio_cutBtag" ]->Fill( jet2SubjetPtRatio, scale );

										histos2D_[ "jetTrimmedMassHT_cutBtag" ]->Fill( trimmedMass, HT, scale  );
										histos2D_[ "leadMassHT_cutBtag" ]->Fill( leadMass, HT, scale  );
										histos2D_[ "massAveHT_cutBtag" ]->Fill( massAve, HT, scale  );

										histos2D_[ "massAvevsJet1Mass_cutBtag" ]->Fill( massAve, jet1Mass, scale );
										histos2D_[ "massAvevsJet2Mass_cutBtag" ]->Fill( massAve, jet2Mass, scale );
										histos2D_[ "massAvevsMassAsym_cutBtag" ]->Fill( massAve, massAsym, scale );
										histos2D_[ "massAvevsDEta_cutBtag" ]->Fill( massAve, deltaEtaDijet, scale );
										histos2D_[ "massAvevsCosThetaStar_cutBtag" ]->Fill( massAve, cosThetaStar, scale );
										histos2D_[ "massAvevsJet1Tau21_cutBtag" ]->Fill( massAve, jet1Tau21, scale );
										histos2D_[ "massAvevsJet1Tau31_cutBtag" ]->Fill( massAve, jet1Tau31, scale );
										histos2D_[ "massAvevsJet1Tau32_cutBtag" ]->Fill( massAve, jet1Tau32, scale );
										histos2D_[ "massAvevsJet2Tau21_cutBtag" ]->Fill( massAve, jet1Tau21, scale );
										histos2D_[ "massAvevsJet2Tau31_cutBtag" ]->Fill( massAve, jet1Tau31, scale );
										histos2D_[ "massAvevsJet2Tau32_cutBtag" ]->Fill( massAve, jet1Tau32, scale );
										histos2D_[ "massAvevsJet1SubjetPtRatio_cutBtag" ]->Fill( massAve, jet1SubjetPtRatio, scale );
										histos2D_[ "massAvevsJet2SubjetPtRatio_cutBtag" ]->Fill( massAve, jet2SubjetPtRatio, scale );
										histos2D_[ "jet1vs2Mass_cutBtag" ]->Fill( jet1Mass, jet2Mass, scale );
										histos2D_[ "dijetCorr_cutBtag" ]->Fill( JETS[0].p4.Eta(), JETS[1].p4.Eta(), scale );
										histos2D_[ "dijetCorrPhi_cutBtag" ]->Fill( JETS[0].p4.Phi(), JETS[1].p4.Phi(), scale );
									}
								}
							}
						}
					} else {

						histos1D_[ "HT_cutNOMassAsym" ]->Fill( HT, scale  );
						histos1D_[ "NPV_cutNOMassAsym" ]->Fill( numPV, scale );
						histos1D_[ "jetNum_cutNOMassAsym" ]->Fill( numJets, scale );
						histos1D_[ "jet1Pt_cutNOMassAsym" ]->Fill( JETS[0].p4.Pt(), scale  );
						histos1D_[ "jet1Eta_cutNOMassAsym" ]->Fill( JETS[0].p4.Eta(), scale  );
						histos1D_[ "jet1Mass_cutNOMassAsym" ]->Fill( JETS[0].mass, scale );
						histos1D_[ "jet2Pt_cutNOMassAsym" ]->Fill( JETS[1].p4.Pt(), scale  );
						histos1D_[ "jet2Eta_cutNOMassAsym" ]->Fill( JETS[1].p4.Eta(), scale  );
						histos1D_[ "jet2Mass_cutNOMassAsym" ]->Fill( JETS[1].mass, scale );

						histos1D_[ "massAsymmetry_cutNOMassAsym" ]->Fill( massAsym, scale  );
						histos1D_[ "massAve_cutNOMassAsym" ]->Fill( massAve, scale  );
						histos1D_[ "cosThetaStar_cutNOMassAsym" ]->Fill( cosThetaStar, scale  );
						histos1D_[ "jet1Tau1_cutNOMassAsym" ]->Fill( JETS[0].tau1, scale );
						histos1D_[ "jet1Tau2_cutNOMassAsym" ]->Fill( JETS[0].tau2, scale );
						histos1D_[ "jet1Tau3_cutNOMassAsym" ]->Fill( JETS[0].tau3, scale );
						histos1D_[ "jet1Tau21_cutNOMassAsym" ]->Fill( jet1Tau21, scale );
						histos1D_[ "jet1Tau31_cutNOMassAsym" ]->Fill( jet1Tau31, scale );
						histos1D_[ "jet1Tau32_cutNOMassAsym" ]->Fill( jet1Tau32, scale );
						histos1D_[ "jet2Tau1_cutNOMassAsym" ]->Fill( JETS[1].tau1, scale );
						histos1D_[ "jet2Tau2_cutNOMassAsym" ]->Fill( JETS[1].tau2, scale );
						histos1D_[ "jet2Tau3_cutNOMassAsym" ]->Fill( JETS[1].tau3, scale );
						histos1D_[ "jet2Tau21_cutNOMassAsym" ]->Fill( jet2Tau21, scale );
						histos1D_[ "jet2Tau31_cutNOMassAsym" ]->Fill( jet2Tau31, scale );
						histos1D_[ "jet2Tau32_cutNOMassAsym" ]->Fill( jet2Tau32, scale );
						histos1D_[ "deltaEtaDijet_cutNOMassAsym" ]->Fill( deltaEtaDijet, scale );
						histos1D_[ "jet1SubjetPtRatio_cutNOMassAsym" ]->Fill( jet1SubjetPtRatio, scale );
						histos1D_[ "jet2SubjetPtRatio_cutNOMassAsym" ]->Fill( jet2SubjetPtRatio, scale );
						histos1D_[ "subjetPtRatio_cutNOMassAsym" ]->Fill( jet1SubjetPtRatio, scale );
						histos1D_[ "subjetPtRatio_cutNOMassAsym" ]->Fill( jet2SubjetPtRatio, scale );

						histos2D_[ "jetTrimmedMassHT_cutNOMassAsym" ]->Fill( trimmedMass, HT, scale  );
						histos2D_[ "leadMassHT_cutNOMassAsym" ]->Fill( leadMass, HT, scale  );
						histos2D_[ "massAveHT_cutNOMassAsym" ]->Fill( massAve, HT, scale  );

						histos2D_[ "massAvevsJet1Mass_cutNOMassAsym" ]->Fill( massAve, jet1Mass, scale );
						histos2D_[ "massAvevsJet2Mass_cutNOMassAsym" ]->Fill( massAve, jet2Mass, scale );
						histos2D_[ "massAvevsMassAsym_cutNOMassAsym" ]->Fill( massAve, massAsym, scale );
						histos2D_[ "massAvevsDEta_cutNOMassAsym" ]->Fill( massAve, deltaEtaDijet, scale );
						histos2D_[ "massAvevsCosThetaStar_cutNOMassAsym" ]->Fill( massAve, cosThetaStar, scale );
						histos2D_[ "massAvevsJet1Tau21_cutNOMassAsym" ]->Fill( massAve, jet1Tau21, scale );
						histos2D_[ "massAvevsJet1Tau31_cutNOMassAsym" ]->Fill( massAve, jet1Tau31, scale );
						histos2D_[ "massAvevsJet1Tau32_cutNOMassAsym" ]->Fill( massAve, jet1Tau32, scale );
						histos2D_[ "massAvevsJet2Tau21_cutNOMassAsym" ]->Fill( massAve, jet1Tau21, scale );
						histos2D_[ "massAvevsJet2Tau31_cutNOMassAsym" ]->Fill( massAve, jet1Tau31, scale );
						histos2D_[ "massAvevsJet2Tau32_cutNOMassAsym" ]->Fill( massAve, jet1Tau32, scale );
						histos2D_[ "massAvevsJet1SubjetPtRatio_cutNOMassAsym" ]->Fill( massAve, jet1SubjetPtRatio, scale );
						histos2D_[ "massAvevsJet2SubjetPtRatio_cutNOMassAsym" ]->Fill( massAve, jet2SubjetPtRatio, scale );
						histos2D_[ "jet1vs2Mass_cutNOMassAsym" ]->Fill( jet1Mass, jet2Mass, scale );
						histos2D_[ "dijetCorr_cutNOMassAsym" ]->Fill( JETS[0].p4.Eta(), JETS[1].p4.Eta(), scale );
						histos2D_[ "dijetCorrPhi_cutNOMassAsym" ]->Fill( JETS[0].p4.Phi(), JETS[1].p4.Phi(), scale );

						if(  ( jet1Tau21 < cutTau21value ) && ( jet2Tau21 < cutTau21value ) ){

							histos1D_[ "HT_cutTau21_NOMA" ]->Fill( HT, scale  );
							histos1D_[ "NPV_cutTau21_NOMA" ]->Fill( numPV, scale );
							histos1D_[ "jetNum_cutTau21_NOMA" ]->Fill( numJets, scale );
							histos1D_[ "jet1Pt_cutTau21_NOMA" ]->Fill( JETS[0].p4.Pt(), scale  );
							histos1D_[ "jet1Eta_cutTau21_NOMA" ]->Fill( JETS[0].p4.Eta(), scale  );
							histos1D_[ "jet1Mass_cutTau21_NOMA" ]->Fill( JETS[0].mass, scale );
							histos1D_[ "jet2Pt_cutTau21_NOMA" ]->Fill( JETS[1].p4.Pt(), scale  );
							histos1D_[ "jet2Eta_cutTau21_NOMA" ]->Fill( JETS[1].p4.Eta(), scale  );
							histos1D_[ "jet2Mass_cutTau21_NOMA" ]->Fill( JETS[1].mass, scale );

							histos1D_[ "massAsymmetry_cutTau21_NOMA" ]->Fill( massAsym, scale  );
							histos1D_[ "massAve_cutTau21_NOMA" ]->Fill( massAve, scale  );
							histos1D_[ "cosThetaStar_cutTau21_NOMA" ]->Fill( cosThetaStar, scale  );
							histos1D_[ "jet1Tau1_cutTau21_NOMA" ]->Fill( JETS[0].tau1, scale );
							histos1D_[ "jet1Tau2_cutTau21_NOMA" ]->Fill( JETS[0].tau2, scale );
							histos1D_[ "jet1Tau3_cutTau21_NOMA" ]->Fill( JETS[0].tau3, scale );
							histos1D_[ "jet1Tau21_cutTau21_NOMA" ]->Fill( jet1Tau21, scale );
							histos1D_[ "jet1Tau31_cutTau21_NOMA" ]->Fill( jet1Tau31, scale );
							histos1D_[ "jet1Tau32_cutTau21_NOMA" ]->Fill( jet1Tau32, scale );
							histos1D_[ "jet2Tau1_cutTau21_NOMA" ]->Fill( JETS[1].tau1, scale );
							histos1D_[ "jet2Tau2_cutTau21_NOMA" ]->Fill( JETS[1].tau2, scale );
							histos1D_[ "jet2Tau3_cutTau21_NOMA" ]->Fill( JETS[1].tau3, scale );
							histos1D_[ "jet2Tau21_cutTau21_NOMA" ]->Fill( jet2Tau21, scale );
							histos1D_[ "jet2Tau31_cutTau21_NOMA" ]->Fill( jet2Tau31, scale );
							histos1D_[ "jet2Tau32_cutTau21_NOMA" ]->Fill( jet2Tau32, scale );
							histos1D_[ "deltaEtaDijet_cutTau21_NOMA" ]->Fill( deltaEtaDijet, scale );
							histos1D_[ "jet1SubjetPtRatio_cutTau21_NOMA" ]->Fill( jet1SubjetPtRatio, scale );
							histos1D_[ "jet2SubjetPtRatio_cutTau21_NOMA" ]->Fill( jet2SubjetPtRatio, scale );
							histos1D_[ "subjetPtRatio_cutTau21_NOMA" ]->Fill( jet1SubjetPtRatio, scale );
							histos1D_[ "subjetPtRatio_cutTau21_NOMA" ]->Fill( jet2SubjetPtRatio, scale );

							histos2D_[ "jetTrimmedMassHT_cutTau21_NOMA" ]->Fill( trimmedMass, HT, scale  );
							histos2D_[ "leadMassHT_cutTau21_NOMA" ]->Fill( leadMass, HT, scale  );
							histos2D_[ "massAveHT_cutTau21_NOMA" ]->Fill( massAve, HT, scale  );

							histos2D_[ "massAvevsJet1Mass_cutTau21_NOMA" ]->Fill( massAve, jet1Mass, scale );
							histos2D_[ "massAvevsJet2Mass_cutTau21_NOMA" ]->Fill( massAve, jet2Mass, scale );
							histos2D_[ "massAvevsMassAsym_cutTau21_NOMA" ]->Fill( massAve, massAsym, scale );
							histos2D_[ "massAvevsDEta_cutTau21_NOMA" ]->Fill( massAve, deltaEtaDijet, scale );
							histos2D_[ "massAvevsCosThetaStar_cutTau21_NOMA" ]->Fill( massAve, cosThetaStar, scale );
							histos2D_[ "massAvevsJet1Tau21_cutTau21_NOMA" ]->Fill( massAve, jet1Tau21, scale );
							histos2D_[ "massAvevsJet1Tau31_cutTau21_NOMA" ]->Fill( massAve, jet1Tau31, scale );
							histos2D_[ "massAvevsJet1Tau32_cutTau21_NOMA" ]->Fill( massAve, jet1Tau32, scale );
							histos2D_[ "massAvevsJet2Tau21_cutTau21_NOMA" ]->Fill( massAve, jet1Tau21, scale );
							histos2D_[ "massAvevsJet2Tau31_cutTau21_NOMA" ]->Fill( massAve, jet1Tau31, scale );
							histos2D_[ "massAvevsJet2Tau32_cutTau21_NOMA" ]->Fill( massAve, jet1Tau32, scale );
							histos2D_[ "massAvevsJet1SubjetPtRatio_cutTau21_NOMA" ]->Fill( massAve, jet1SubjetPtRatio, scale );
							histos2D_[ "massAvevsJet2SubjetPtRatio_cutTau21_NOMA" ]->Fill( massAve, jet2SubjetPtRatio, scale );
							histos2D_[ "jet1vs2Mass_cutTau21_NOMA" ]->Fill( jet1Mass, jet2Mass, scale );
							histos2D_[ "dijetCorr_cutTau21_NOMA" ]->Fill( JETS[0].p4.Eta(), JETS[1].p4.Eta(), scale );
							histos2D_[ "dijetCorrPhi_cutTau21_NOMA" ]->Fill( JETS[0].p4.Phi(), JETS[1].p4.Phi(), scale );

							if( TMath::Abs( cosThetaStar ) < cutCosThetavalue ){
							
								histos1D_[ "HT_cutCosTheta_NOMA" ]->Fill( HT, scale  );
								histos1D_[ "NPV_cutCosTheta_NOMA" ]->Fill( numPV, scale );
								histos1D_[ "jetNum_cutCosTheta_NOMA" ]->Fill( numJets, scale );
								histos1D_[ "jet1Pt_cutCosTheta_NOMA" ]->Fill( JETS[0].p4.Pt(), scale  );
								histos1D_[ "jet1Eta_cutCosTheta_NOMA" ]->Fill( JETS[0].p4.Eta(), scale  );
								histos1D_[ "jet1Mass_cutCosTheta_NOMA" ]->Fill( JETS[0].mass, scale );
								histos1D_[ "jet2Pt_cutCosTheta_NOMA" ]->Fill( JETS[1].p4.Pt(), scale  );
								histos1D_[ "jet2Eta_cutCosTheta_NOMA" ]->Fill( JETS[1].p4.Eta(), scale  );
								histos1D_[ "jet2Mass_cutCosTheta_NOMA" ]->Fill( JETS[1].mass, scale );

								histos1D_[ "massAsymmetry_cutCosTheta_NOMA" ]->Fill( massAsym, scale  );
								histos1D_[ "massAve_cutCosTheta_NOMA" ]->Fill( massAve, scale  );
								histos1D_[ "cosThetaStar_cutCosTheta_NOMA" ]->Fill( cosThetaStar, scale  );
								histos1D_[ "jet1Tau1_cutCosTheta_NOMA" ]->Fill( JETS[0].tau1, scale );
								histos1D_[ "jet1Tau2_cutCosTheta_NOMA" ]->Fill( JETS[0].tau2, scale );
								histos1D_[ "jet1Tau3_cutCosTheta_NOMA" ]->Fill( JETS[0].tau3, scale );
								histos1D_[ "jet1Tau21_cutCosTheta_NOMA" ]->Fill( jet1Tau21, scale );
								histos1D_[ "jet1Tau31_cutCosTheta_NOMA" ]->Fill( jet1Tau31, scale );
								histos1D_[ "jet1Tau32_cutCosTheta_NOMA" ]->Fill( jet1Tau32, scale );
								histos1D_[ "jet2Tau1_cutCosTheta_NOMA" ]->Fill( JETS[1].tau1, scale );
								histos1D_[ "jet2Tau2_cutCosTheta_NOMA" ]->Fill( JETS[1].tau2, scale );
								histos1D_[ "jet2Tau3_cutCosTheta_NOMA" ]->Fill( JETS[1].tau3, scale );
								histos1D_[ "jet2Tau21_cutCosTheta_NOMA" ]->Fill( jet2Tau21, scale );
								histos1D_[ "jet2Tau31_cutCosTheta_NOMA" ]->Fill( jet2Tau31, scale );
								histos1D_[ "jet2Tau32_cutCosTheta_NOMA" ]->Fill( jet2Tau32, scale );
								histos1D_[ "deltaEtaDijet_cutCosTheta_NOMA" ]->Fill( deltaEtaDijet, scale );
								histos1D_[ "jet1SubjetPtRatio_cutCosTheta_NOMA" ]->Fill( jet1SubjetPtRatio, scale );
								histos1D_[ "jet2SubjetPtRatio_cutCosTheta_NOMA" ]->Fill( jet2SubjetPtRatio, scale );
								histos1D_[ "subjetPtRatio_cutCosTheta_NOMA" ]->Fill( jet1SubjetPtRatio, scale );
								histos1D_[ "subjetPtRatio_cutCosTheta_NOMA" ]->Fill( jet2SubjetPtRatio, scale );

								histos2D_[ "jetTrimmedMassHT_cutCosTheta_NOMA" ]->Fill( trimmedMass, HT, scale  );
								histos2D_[ "leadMassHT_cutCosTheta_NOMA" ]->Fill( leadMass, HT, scale  );
								histos2D_[ "massAveHT_cutCosTheta_NOMA" ]->Fill( massAve, HT, scale  );

								histos2D_[ "massAvevsJet1Mass_cutCosTheta_NOMA" ]->Fill( massAve, jet1Mass, scale );
								histos2D_[ "massAvevsJet2Mass_cutCosTheta_NOMA" ]->Fill( massAve, jet2Mass, scale );
								histos2D_[ "massAvevsMassAsym_cutCosTheta_NOMA" ]->Fill( massAve, massAsym, scale );
								histos2D_[ "massAvevsDEta_cutCosTheta_NOMA" ]->Fill( massAve, deltaEtaDijet, scale );
								histos2D_[ "massAvevsCosThetaStar_cutCosTheta_NOMA" ]->Fill( massAve, cosThetaStar, scale );
								histos2D_[ "massAvevsJet1Tau21_cutCosTheta_NOMA" ]->Fill( massAve, jet1Tau21, scale );
								histos2D_[ "massAvevsJet1Tau31_cutCosTheta_NOMA" ]->Fill( massAve, jet1Tau31, scale );
								histos2D_[ "massAvevsJet1Tau32_cutCosTheta_NOMA" ]->Fill( massAve, jet1Tau32, scale );
								histos2D_[ "massAvevsJet2Tau21_cutCosTheta_NOMA" ]->Fill( massAve, jet1Tau21, scale );
								histos2D_[ "massAvevsJet2Tau31_cutCosTheta_NOMA" ]->Fill( massAve, jet1Tau31, scale );
								histos2D_[ "massAvevsJet2Tau32_cutCosTheta_NOMA" ]->Fill( massAve, jet1Tau32, scale );
								histos2D_[ "massAvevsJet1SubjetPtRatio_cutCosTheta_NOMA" ]->Fill( massAve, jet1SubjetPtRatio, scale );
								histos2D_[ "massAvevsJet2SubjetPtRatio_cutCosTheta_NOMA" ]->Fill( massAve, jet2SubjetPtRatio, scale );
								histos2D_[ "jet1vs2Mass_cutCosTheta_NOMA" ]->Fill( jet1Mass, jet2Mass, scale );
								histos2D_[ "dijetCorr_cutCosTheta_NOMA" ]->Fill( JETS[0].p4.Eta(), JETS[1].p4.Eta(), scale );
								histos2D_[ "dijetCorrPhi_cutCosTheta_NOMA" ]->Fill( JETS[0].p4.Phi(), JETS[1].p4.Phi(), scale );
							
								if( ( deltaEtaDijet  > cutDEtavalue ) ){

									histos1D_[ "HT_cutDEta_NOMA" ]->Fill( HT, scale  );
									histos1D_[ "NPV_cutDEta_NOMA" ]->Fill( numPV, scale );
									histos1D_[ "jetNum_cutDEta_NOMA" ]->Fill( numJets, scale );
									histos1D_[ "jet1Pt_cutDEta_NOMA" ]->Fill( JETS[0].p4.Pt(), scale  );
									histos1D_[ "jet1Eta_cutDEta_NOMA" ]->Fill( JETS[0].p4.Eta(), scale  );
									histos1D_[ "jet1Mass_cutDEta_NOMA" ]->Fill( JETS[0].mass, scale );
									histos1D_[ "jet2Pt_cutDEta_NOMA" ]->Fill( JETS[1].p4.Pt(), scale  );
									histos1D_[ "jet2Eta_cutDEta_NOMA" ]->Fill( JETS[1].p4.Eta(), scale  );
									histos1D_[ "jet2Mass_cutDEta_NOMA" ]->Fill( JETS[1].mass, scale );

									histos1D_[ "massAsymmetry_cutDEta_NOMA" ]->Fill( massAsym, scale  );
									histos1D_[ "massAve_cutDEta_NOMA" ]->Fill( massAve, scale  );
									histos1D_[ "cosThetaStar_cutDEta_NOMA" ]->Fill( cosThetaStar, scale  );
									histos1D_[ "jet1Tau1_cutDEta_NOMA" ]->Fill( JETS[0].tau1, scale );
									histos1D_[ "jet1Tau2_cutDEta_NOMA" ]->Fill( JETS[0].tau2, scale );
									histos1D_[ "jet1Tau3_cutDEta_NOMA" ]->Fill( JETS[0].tau3, scale );
									histos1D_[ "jet1Tau21_cutDEta_NOMA" ]->Fill( jet1Tau21, scale );
									histos1D_[ "jet1Tau31_cutDEta_NOMA" ]->Fill( jet1Tau31, scale );
									histos1D_[ "jet1Tau32_cutDEta_NOMA" ]->Fill( jet1Tau32, scale );
									histos1D_[ "jet2Tau1_cutDEta_NOMA" ]->Fill( JETS[1].tau1, scale );
									histos1D_[ "jet2Tau2_cutDEta_NOMA" ]->Fill( JETS[1].tau2, scale );
									histos1D_[ "jet2Tau3_cutDEta_NOMA" ]->Fill( JETS[1].tau3, scale );
									histos1D_[ "jet2Tau21_cutDEta_NOMA" ]->Fill( jet2Tau21, scale );
									histos1D_[ "jet2Tau31_cutDEta_NOMA" ]->Fill( jet2Tau31, scale );
									histos1D_[ "jet2Tau32_cutDEta_NOMA" ]->Fill( jet2Tau32, scale );
									histos1D_[ "deltaEtaDijet_cutDEta_NOMA" ]->Fill( deltaEtaDijet, scale );
									histos1D_[ "jet1SubjetPtRatio_cutDEta_NOMA" ]->Fill( jet1SubjetPtRatio, scale );
									histos1D_[ "jet2SubjetPtRatio_cutDEta_NOMA" ]->Fill( jet2SubjetPtRatio, scale );
									histos1D_[ "subjetPtRatio_cutDEta_NOMA" ]->Fill( jet1SubjetPtRatio, scale );
									histos1D_[ "subjetPtRatio_cutDEta_NOMA" ]->Fill( jet2SubjetPtRatio, scale );

									histos2D_[ "jetTrimmedMassHT_cutDEta_NOMA" ]->Fill( trimmedMass, HT, scale  );
									histos2D_[ "leadMassHT_cutDEta_NOMA" ]->Fill( leadMass, HT, scale  );
									histos2D_[ "massAveHT_cutDEta_NOMA" ]->Fill( massAve, HT, scale  );

									histos2D_[ "massAvevsJet1Mass_cutDEta_NOMA" ]->Fill( massAve, jet1Mass, scale );
									histos2D_[ "massAvevsJet2Mass_cutDEta_NOMA" ]->Fill( massAve, jet2Mass, scale );
									histos2D_[ "massAvevsMassAsym_cutDEta_NOMA" ]->Fill( massAve, massAsym, scale );
									histos2D_[ "massAvevsDEta_cutDEta_NOMA" ]->Fill( massAve, deltaEtaDijet, scale );
									histos2D_[ "massAvevsCosThetaStar_cutDEta_NOMA" ]->Fill( massAve, cosThetaStar, scale );
									histos2D_[ "massAvevsJet1Tau21_cutDEta_NOMA" ]->Fill( massAve, jet1Tau21, scale );
									histos2D_[ "massAvevsJet1Tau31_cutDEta_NOMA" ]->Fill( massAve, jet1Tau31, scale );
									histos2D_[ "massAvevsJet1Tau32_cutDEta_NOMA" ]->Fill( massAve, jet1Tau32, scale );
									histos2D_[ "massAvevsJet2Tau21_cutDEta_NOMA" ]->Fill( massAve, jet1Tau21, scale );
									histos2D_[ "massAvevsJet2Tau31_cutDEta_NOMA" ]->Fill( massAve, jet1Tau31, scale );
									histos2D_[ "massAvevsJet2Tau32_cutDEta_NOMA" ]->Fill( massAve, jet1Tau32, scale );
									histos2D_[ "massAvevsJet1SubjetPtRatio_cutDEta_NOMA" ]->Fill( massAve, jet1SubjetPtRatio, scale );
									histos2D_[ "massAvevsJet2SubjetPtRatio_cutDEta_NOMA" ]->Fill( massAve, jet2SubjetPtRatio, scale );
									histos2D_[ "jet1vs2Mass_cutDEta_NOMA" ]->Fill( jet1Mass, jet2Mass, scale );
									histos2D_[ "dijetCorr_cutDEta_NOMA" ]->Fill( JETS[0].p4.Eta(), JETS[1].p4.Eta(), scale );
									histos2D_[ "dijetCorrPhi_cutDEta_NOMA" ]->Fill( JETS[0].p4.Phi(), JETS[1].p4.Phi(), scale );
							
									if ( jet1btagCSV > cutBtagvalue || jet2btagCSV > cutBtagvalue ){

										histos1D_[ "HT_cutBtag_NOMA" ]->Fill( HT, scale  );
										histos1D_[ "NPV_cutBtag_NOMA" ]->Fill( numPV, scale );
										histos1D_[ "jetNum_cutBtag_NOMA" ]->Fill( numJets, scale );
										histos1D_[ "jet1Pt_cutBtag_NOMA" ]->Fill( JETS[0].p4.Pt(), scale  );
										histos1D_[ "jet1Eta_cutBtag_NOMA" ]->Fill( JETS[0].p4.Eta(), scale  );
										histos1D_[ "jet1Mass_cutBtag_NOMA" ]->Fill( JETS[0].mass, scale );
										histos1D_[ "jet2Pt_cutBtag_NOMA" ]->Fill( JETS[1].p4.Pt(), scale  );
										histos1D_[ "jet2Eta_cutBtag_NOMA" ]->Fill( JETS[1].p4.Eta(), scale  );
										histos1D_[ "jet2Mass_cutBtag_NOMA" ]->Fill( JETS[1].mass, scale );

										histos1D_[ "massAsymmetry_cutBtag_NOMA" ]->Fill( massAsym, scale  );
										histos1D_[ "massAve_cutBtag_NOMA" ]->Fill( massAve, scale  );
										histos1D_[ "cosThetaStar_cutBtag_NOMA" ]->Fill( cosThetaStar, scale  );
										histos1D_[ "jet1Tau1_cutBtag_NOMA" ]->Fill( JETS[0].tau1, scale );
										histos1D_[ "jet1Tau2_cutBtag_NOMA" ]->Fill( JETS[0].tau2, scale );
										histos1D_[ "jet1Tau3_cutBtag_NOMA" ]->Fill( JETS[0].tau3, scale );
										histos1D_[ "jet1Tau21_cutBtag_NOMA" ]->Fill( jet1Tau21, scale );
										histos1D_[ "jet1Tau31_cutBtag_NOMA" ]->Fill( jet1Tau31, scale );
										histos1D_[ "jet1Tau32_cutBtag_NOMA" ]->Fill( jet1Tau32, scale );
										histos1D_[ "jet2Tau1_cutBtag_NOMA" ]->Fill( JETS[1].tau1, scale );
										histos1D_[ "jet2Tau2_cutBtag_NOMA" ]->Fill( JETS[1].tau2, scale );
										histos1D_[ "jet2Tau3_cutBtag_NOMA" ]->Fill( JETS[1].tau3, scale );
										histos1D_[ "jet2Tau21_cutBtag_NOMA" ]->Fill( jet2Tau21, scale );
										histos1D_[ "jet2Tau31_cutBtag_NOMA" ]->Fill( jet2Tau31, scale );
										histos1D_[ "jet2Tau32_cutBtag_NOMA" ]->Fill( jet2Tau32, scale );
										histos1D_[ "deltaEtaDijet_cutBtag_NOMA" ]->Fill( deltaEtaDijet, scale );
										histos1D_[ "jet1SubjetPtRatio_cutBtag_NOMA" ]->Fill( jet1SubjetPtRatio, scale );
										histos1D_[ "jet2SubjetPtRatio_cutBtag_NOMA" ]->Fill( jet2SubjetPtRatio, scale );
										histos1D_[ "subjetPtRatio_cutBtag_NOMA" ]->Fill( jet1SubjetPtRatio, scale );
										histos1D_[ "subjetPtRatio_cutBtag_NOMA" ]->Fill( jet2SubjetPtRatio, scale );

										histos2D_[ "jetTrimmedMassHT_cutBtag_NOMA" ]->Fill( trimmedMass, HT, scale  );
										histos2D_[ "leadMassHT_cutBtag_NOMA" ]->Fill( leadMass, HT, scale  );
										histos2D_[ "massAveHT_cutBtag_NOMA" ]->Fill( massAve, HT, scale  );

										histos2D_[ "massAvevsJet1Mass_cutBtag_NOMA" ]->Fill( massAve, jet1Mass, scale );
										histos2D_[ "massAvevsJet2Mass_cutBtag_NOMA" ]->Fill( massAve, jet2Mass, scale );
										histos2D_[ "massAvevsMassAsym_cutBtag_NOMA" ]->Fill( massAve, massAsym, scale );
										histos2D_[ "massAvevsDEta_cutBtag_NOMA" ]->Fill( massAve, deltaEtaDijet, scale );
										histos2D_[ "massAvevsCosThetaStar_cutBtag_NOMA" ]->Fill( massAve, cosThetaStar, scale );
										histos2D_[ "massAvevsJet1Tau21_cutBtag_NOMA" ]->Fill( massAve, jet1Tau21, scale );
										histos2D_[ "massAvevsJet1Tau31_cutBtag_NOMA" ]->Fill( massAve, jet1Tau31, scale );
										histos2D_[ "massAvevsJet1Tau32_cutBtag_NOMA" ]->Fill( massAve, jet1Tau32, scale );
										histos2D_[ "massAvevsJet2Tau21_cutBtag_NOMA" ]->Fill( massAve, jet1Tau21, scale );
										histos2D_[ "massAvevsJet2Tau31_cutBtag_NOMA" ]->Fill( massAve, jet1Tau31, scale );
										histos2D_[ "massAvevsJet2Tau32_cutBtag_NOMA" ]->Fill( massAve, jet1Tau32, scale );
										histos2D_[ "massAvevsJet1SubjetPtRatio_cutBtag_NOMA" ]->Fill( massAve, jet1SubjetPtRatio, scale );
										histos2D_[ "massAvevsJet2SubjetPtRatio_cutBtag_NOMA" ]->Fill( massAve, jet2SubjetPtRatio, scale );
										histos2D_[ "jet1vs2Mass_cutBtag_NOMA" ]->Fill( jet1Mass, jet2Mass, scale );
										histos2D_[ "dijetCorr_cutBtag_NOMA" ]->Fill( JETS[0].p4.Eta(), JETS[1].p4.Eta(), scale );
										histos2D_[ "dijetCorrPhi_cutBtag_NOMA" ]->Fill( JETS[0].p4.Phi(), JETS[1].p4.Phi(), scale );
									}
								}
							}
						}
					}
				}
			}
		}
	}
	JETS.clear();

}


// ------------ method called once each job just before starting event loop  ------------
void RUNBoostedAnalysis::beginJob() {

	histos1D_[ "rawJetPt" ] = fs_->make< TH1D >( "rawJetPt", "rawJetPt", 100, 0., 1000. );
	histos1D_[ "rawJetPt" ]->Sumw2();
	histos1D_[ "rawHT" ] = fs_->make< TH1D >( "rawHT", "rawHT", 500, 0., 5000. );
	histos1D_[ "rawHT" ]->Sumw2();

	histos1D_[ "jetPt" ] = fs_->make< TH1D >( "jetPt", "jetPt", 100, 0., 1000. );
	histos1D_[ "jetPt" ]->Sumw2();
	histos1D_[ "jetEta" ] = fs_->make< TH1D >( "jetEta", "jetEta", 100, -5., 5. );
	histos1D_[ "jetEta" ]->Sumw2();
	histos1D_[ "jetNum" ] = fs_->make< TH1D >( "jetNum", "jetNum", 10, 0., 10. );
	histos1D_[ "jetNum" ]->Sumw2();
	histos1D_[ "jetMass" ] = fs_->make< TH1D >( "jetMass", "jetMass", 60, 0., 600. );
	histos1D_[ "jetMass" ]->Sumw2();
	histos1D_[ "jetTrimmedMass" ] = fs_->make< TH1D >( "jetTrimmedMass", "jetTrimmedMass", 60, 0., 600. );
	histos1D_[ "jetTrimmedMass" ]->Sumw2();
	histos1D_[ "leadMass" ] = fs_->make< TH1D >( "leadMass", "leadMass", 60, 0., 600. );
	histos1D_[ "leadMass" ]->Sumw2();
	histos1D_[ "HT" ] = fs_->make< TH1D >( "HT", "HT", 500, 0., 5000. );
	histos1D_[ "HT" ]->Sumw2();
	histos1D_[ "NPV" ] = fs_->make< TH1D >( "NPV", "NPV", 80, 0., 80. );
	histos1D_[ "NPV" ]->Sumw2();
	histos2D_[ "jetTrimmedMassHT" ] = fs_->make< TH2D >( "jetTrimmedMassHT", "jetTrimmedMassHT", 30, 0., 300., 500, 0., 5000. );
	histos2D_[ "jetTrimmedMassHT" ]->Sumw2();
	histos2D_[ "leadMassHT" ] = fs_->make< TH2D >( "leadMassHT", "leadMassHT", 30, 0., 300., 500, 0., 5000. );
	histos2D_[ "leadMassHT" ]->Sumw2();

	histos1D_[ "HT_cutTrigger" ] = fs_->make< TH1D >( "HT_cutTrigger", "HT_cutTrigger", 500, 0., 5000. );
	histos1D_[ "HT_cutTrigger" ]->Sumw2();
	histos1D_[ "NPV_cutTrigger" ] = fs_->make< TH1D >( "NPV_cutTrigger", "NPV_cutTrigger", 80, 0., 80. );
	histos1D_[ "NPV_cutTrigger" ]->Sumw2();
	histos1D_[ "jetPt_cutTrigger" ] = fs_->make< TH1D >( "jetPt_cutTrigger", "jetPt_cutTrigger", 100, 0., 1000. );
	histos1D_[ "jetPt_cutTrigger" ]->Sumw2();
	histos1D_[ "jetEta_cutTrigger" ] = fs_->make< TH1D >( "jetEta_cutTrigger", "jetEta_cutTrigger", 100, -5., 5. );
	histos1D_[ "jetEta_cutTrigger" ]->Sumw2();
	histos1D_[ "jetNum_cutTrigger" ] = fs_->make< TH1D >( "jetNum_cutTrigger", "jetNum_cutTrigger", 10, 0., 10. );
	histos1D_[ "jetNum_cutTrigger" ]->Sumw2();
	histos1D_[ "jetMass_cutTrigger" ] = fs_->make< TH1D >( "jetMass_cutTrigger", "jetMass_cutTrigger", 60, 0., 600. );
	histos1D_[ "jetMass_cutTrigger" ]->Sumw2();
	histos1D_[ "jet1Pt_cutTrigger" ] = fs_->make< TH1D >( "jet1Pt_cutTrigger", "jet1Pt_cutTrigger", 100, 0., 1000. );
	histos1D_[ "jet1Pt_cutTrigger" ]->Sumw2();
	histos1D_[ "jet1Eta_cutTrigger" ] = fs_->make< TH1D >( "jet1Eta_cutTrigger", "jet1Eta_cutTrigger", 100, -5., 5. );
	histos1D_[ "jet1Eta_cutTrigger" ]->Sumw2();
	histos1D_[ "jet1Mass_cutTrigger" ] = fs_->make< TH1D >( "jet1Mass_cutTrigger", "jet1Mass_cutTrigger", 60, 0., 600. );
	histos1D_[ "jet1Mass_cutTrigger" ]->Sumw2();
	histos2D_[ "jetTrimmedMassHT_cutTrigger" ] = fs_->make< TH2D >( "jetTrimmedMassHT_cutTrigger", "jetTrimmedMassHT_cutTrigger", 30, 0., 300., 500, 0., 5000. );
	histos2D_[ "jetTrimmedMassHT_cutTrigger" ]->Sumw2();
	histos2D_[ "leadMassHT_cutTrigger" ] = fs_->make< TH2D >( "leadMassHT_cutTrigger", "leadMassHT_cutTrigger", 30, 0., 300., 500, 0., 5000. );
	histos2D_[ "leadMassHT_cutTrigger" ]->Sumw2();

	if (mkTree) {
		RUNAtree = fs_->make< TTree >("RUNATree", "RUNATree"); 
		RUNAtree->Branch( "run", &run, "run/I" );
		RUNAtree->Branch( "lumi", &lumi, "lumi/I" );
		RUNAtree->Branch( "event", &event, "event/I" );
		RUNAtree->Branch( "Scale", &Scale, "Scale/F" );
		RUNAtree->Branch( "numJets", &numJets, "numJets/I" );
		RUNAtree->Branch( "numPV", &numPV, "numPV/I" );
		RUNAtree->Branch( "HT", &HT, "HT/F" );
		RUNAtree->Branch( "AK4HT", &AK4HT, "AK4HT/F" );
		RUNAtree->Branch( "trimmedMass", &trimmedMass, "trimmedMass/F" );
		RUNAtree->Branch( "jet1Pt", &jet1Pt, "jet1Pt/F" );
		RUNAtree->Branch( "jet1Eta", &jet1Eta, "jet1Eta/F" );
		RUNAtree->Branch( "jet1Phi", &jet1Phi, "jet1Phi/F" );
		RUNAtree->Branch( "jet1E", &jet1E, "jet1E/F" );
		RUNAtree->Branch( "jet1btagCSV", &jet1btagCSV, "jet1btagCSV/F" );
		RUNAtree->Branch( "jet1Mass", &jet1Mass, "jet1Mass/F" );
		RUNAtree->Branch( "jet2Pt", &jet2Pt, "jet2Pt/F" );
		RUNAtree->Branch( "jet2Eta", &jet2Eta, "jet2Eta/F" );
		RUNAtree->Branch( "jet2Phi", &jet2Phi, "jet2Phi/F" );
		RUNAtree->Branch( "jet2E", &jet2E, "jet2E/F" );
		RUNAtree->Branch( "jet2btagCSV", &jet2btagCSV, "jet2btagCSV/F" );
		RUNAtree->Branch( "jet2Mass", &jet2Mass, "jet2Mass/F" );
		RUNAtree->Branch( "subjet11Pt", &subjet11Pt, "subjet11Pt/F" );
		RUNAtree->Branch( "subjet11Eta", &subjet11Eta, "subjet11Eta/F" );
		RUNAtree->Branch( "subjet11Phi", &subjet11Phi, "subjet11Phi/F" );
		RUNAtree->Branch( "subjet11E", &subjet11E, "subjet11E/F" );
		RUNAtree->Branch( "subjet12Pt", &subjet12Pt, "subjet12Pt/F" );
		RUNAtree->Branch( "subjet12Eta", &subjet12Eta, "subjet12Eta/F" );
		RUNAtree->Branch( "subjet12Phi", &subjet12Phi, "subjet12Phi/F" );
		RUNAtree->Branch( "subjet12E", &subjet12E, "subjet12E/F" );
		RUNAtree->Branch( "subjet21Pt", &subjet21Pt, "subjet21Pt/F" );
		RUNAtree->Branch( "subjet21Eta", &subjet21Eta, "subjet21Eta/F" );
		RUNAtree->Branch( "subjet21Phi", &subjet21Phi, "subjet21Phi/F" );
		RUNAtree->Branch( "subjet21E", &subjet21E, "subjet21E/F" );
		RUNAtree->Branch( "subjet22Pt", &subjet22Pt, "subjet22Pt/F" );
		RUNAtree->Branch( "subjet22Eta", &subjet22Eta, "subjet22Eta/F" );
		RUNAtree->Branch( "subjet22Phi", &subjet22Phi, "subjet22Phi/F" );
		RUNAtree->Branch( "subjet22E", &subjet22E, "subjet22E/F" );
		RUNAtree->Branch( "massAve", &massAve, "massAve/F" );
		RUNAtree->Branch( "massAsym", &massAsym, "massAsym/F" );
		RUNAtree->Branch( "cosThetaStar", &cosThetaStar, "cosThetaStar/F" );
		RUNAtree->Branch( "jet1Tau21", &jet1Tau21, "jet1Tau21/F" );
		RUNAtree->Branch( "jet1Tau31", &jet1Tau31, "jet1Tau31/F" );
		RUNAtree->Branch( "jet1Tau32", &jet1Tau32, "jet1Tau32/F" );	
		RUNAtree->Branch( "jet2Tau21", &jet2Tau21, "jet2Tau21/F" );
		RUNAtree->Branch( "jet2Tau31", &jet2Tau31, "jet2Tau31/F" );
		RUNAtree->Branch( "jet2Tau32", &jet2Tau32, "jet2Tau32/F" );	
		RUNAtree->Branch( "jet1SubjetPtRatio", &jet1SubjetPtRatio, "jet1SubjetPtRatio/F" );
		RUNAtree->Branch( "jet2SubjetPtRatio", &jet2SubjetPtRatio, "jet2SubjetPtRatio/F" );
		RUNAtree->Branch( "cosPhi13412", &cosPhi13412, "cosPhi13412/F" );
		RUNAtree->Branch( "cosPhi31234", &cosPhi31234, "cosPhi31234/F" );

	} else { 

		histos1D_[ "HT_cutHT" ] = fs_->make< TH1D >( "HT_cutHT", "HT_cutHT", 500, 0., 5000. );
		histos1D_[ "HT_cutHT" ]->Sumw2();
		histos1D_[ "NPV_cutHT" ] = fs_->make< TH1D >( "NPV_cutHT", "NPV_cutHT", 80, 0., 80. );
		histos1D_[ "NPV_cutHT" ]->Sumw2();
		histos1D_[ "jetPt_cutHT" ] = fs_->make< TH1D >( "jetPt_cutHT", "jetPt_cutHT", 100, 0., 1000. );
		histos1D_[ "jetPt_cutHT" ]->Sumw2();
		histos1D_[ "jetEta_cutHT" ] = fs_->make< TH1D >( "jetEta_cutHT", "jetEta_cutHT", 100, -5., 5. );
		histos1D_[ "jetEta_cutHT" ]->Sumw2();
		histos1D_[ "jetNum_cutHT" ] = fs_->make< TH1D >( "jetNum_cutHT", "jetNum_cutHT", 10, 0., 10. );
		histos1D_[ "jetNum_cutHT" ]->Sumw2();
		histos1D_[ "jetMass_cutHT" ] = fs_->make< TH1D >( "jetMass_cutHT", "jetMass_cutHT", 60, 0., 600. );
		histos1D_[ "jetMass_cutHT" ]->Sumw2();
		histos1D_[ "jet1Pt_cutHT" ] = fs_->make< TH1D >( "jet1Pt_cutHT", "jet1Pt_cutHT", 100, 0., 1000. );
		histos1D_[ "jet1Pt_cutHT" ]->Sumw2();
		histos1D_[ "jet1Eta_cutHT" ] = fs_->make< TH1D >( "jet1Eta_cutHT", "jet1Eta_cutHT", 100, -5., 5. );
		histos1D_[ "jet1Eta_cutHT" ]->Sumw2();
		histos1D_[ "jet1Mass_cutHT" ] = fs_->make< TH1D >( "jet1Mass_cutHT", "jet1Mass_cutHT", 60, 0., 600. );
		histos1D_[ "jet1Mass_cutHT" ]->Sumw2();
		histos2D_[ "jetTrimmedMassHT_cutHT" ] = fs_->make< TH2D >( "jetTrimmedMassHT_cutHT", "jetTrimmedMassHT_cutHT", 30, 0., 300., 500, 0., 5000. );
		histos2D_[ "jetTrimmedMassHT_cutHT" ]->Sumw2();
		histos2D_[ "leadMassHT_cutHT" ] = fs_->make< TH2D >( "leadMassHT_cutHT", "leadMassHT_cutHT", 30, 0., 300., 500, 0., 5000. );
		histos2D_[ "leadMassHT_cutHT" ]->Sumw2();

		histos1D_[ "HT_cutDijet" ] = fs_->make< TH1D >( "HT_cutDijet", "HT_cutDijet", 500, 0., 5000. );
		histos1D_[ "HT_cutDijet" ]->Sumw2();
		histos1D_[ "NPV_cutDijet" ] = fs_->make< TH1D >( "NPV_cutDijet", "NPV_cutDijet", 80, 0., 80. );
		histos1D_[ "NPV_cutDijet" ]->Sumw2();
		histos1D_[ "jetNum_cutDijet" ] = fs_->make< TH1D >( "jetNum_cutDijet", "jetNum_cutDijet", 10, 0., 10. );
		histos1D_[ "jetNum_cutDijet" ]->Sumw2();
		histos1D_[ "jet1Pt_cutDijet" ] = fs_->make< TH1D >( "jet1Pt_cutDijet", "jet1Pt_cutDijet", 100, 0., 1000. );
		histos1D_[ "jet1Pt_cutDijet" ]->Sumw2();
		histos1D_[ "jet1Eta_cutDijet" ] = fs_->make< TH1D >( "jet1Eta_cutDijet", "jet1Eta_cutDijet", 100, -5., 5. );
		histos1D_[ "jet1Eta_cutDijet" ]->Sumw2();
		histos1D_[ "jet1Mass_cutDijet" ] = fs_->make< TH1D >( "jet1Mass_cutDijet", "jet1Mass_cutDijet", 60, 0., 600. );
		histos1D_[ "jet1Mass_cutDijet" ]->Sumw2();
		histos1D_[ "jet2Pt_cutDijet" ] = fs_->make< TH1D >( "jet2Pt_cutDijet", "jet2Pt_cutDijet", 100, 0., 1000. );
		histos1D_[ "jet2Pt_cutDijet" ]->Sumw2();
		histos1D_[ "jet2Eta_cutDijet" ] = fs_->make< TH1D >( "jet2Eta_cutDijet", "jet2Eta_cutDijet", 100, -5., 5. );
		histos1D_[ "jet2Eta_cutDijet" ]->Sumw2();
		histos1D_[ "jet2Mass_cutDijet" ] = fs_->make< TH1D >( "jet2Mass_cutDijet", "jet2Mass_cutDijet", 60, 0., 600. );
		histos1D_[ "jet2Mass_cutDijet" ]->Sumw2();

		histos1D_[ "massAsymmetry_cutDijet" ] = fs_->make< TH1D >( "massAsymmetry_cutDijet", "massAsymmetry_cutDijet", 20, 0., 1. );
		histos1D_[ "massAsymmetry_cutDijet" ]->Sumw2();
		histos1D_[ "massAve_cutDijet" ] = fs_->make< TH1D >( "massAve_cutDijet", "massAve_cutDijet", 60, 0., 600. );
		histos1D_[ "massAve_cutDijet" ]->Sumw2();
		histos1D_[ "cosThetaStar_cutDijet" ] = fs_->make< TH1D >( "cosThetaStar_cutDijet", "cosThetaStar_cutDijet", 20, 0., 1. );
		histos1D_[ "cosThetaStar_cutDijet" ]->Sumw2();
		histos1D_[ "jet1Tau1_cutDijet" ] = fs_->make< TH1D >( "jet1Tau1_cutDijet", "jet1Tau1_cutDijet", 20, 0., 1. );
		histos1D_[ "jet1Tau1_cutDijet" ]->Sumw2();
		histos1D_[ "jet1Tau2_cutDijet" ] = fs_->make< TH1D >( "jet1Tau2_cutDijet", "jet1Tau2_cutDijet", 20, 0., 1. );
		histos1D_[ "jet1Tau2_cutDijet" ]->Sumw2();
		histos1D_[ "jet1Tau3_cutDijet" ] = fs_->make< TH1D >( "jet1Tau3_cutDijet", "jet1Tau3_cutDijet", 20, 0., 1. );
		histos1D_[ "jet1Tau3_cutDijet" ]->Sumw2();
		histos1D_[ "jet1Tau21_cutDijet" ] = fs_->make< TH1D >( "jet1Tau21_cutDijet", "jet1Tau21_cutDijet", 20, 0., 1. );
		histos1D_[ "jet1Tau21_cutDijet" ]->Sumw2();
		histos1D_[ "jet1Tau31_cutDijet" ] = fs_->make< TH1D >( "jet1Tau31_cutDijet", "jet1Tau31_cutDijet", 20, 0., 1. );
		histos1D_[ "jet1Tau31_cutDijet" ]->Sumw2();
		histos1D_[ "jet1Tau32_cutDijet" ] = fs_->make< TH1D >( "jet1Tau32_cutDijet", "jet1Tau32_cutDijet", 20, 0., 1. );
		histos1D_[ "jet1Tau32_cutDijet" ]->Sumw2();
		histos1D_[ "jet2Tau1_cutDijet" ] = fs_->make< TH1D >( "jet2Tau1_cutDijet", "jet2Tau1_cutDijet", 20, 0., 1. );
		histos1D_[ "jet2Tau1_cutDijet" ]->Sumw2();
		histos1D_[ "jet2Tau2_cutDijet" ] = fs_->make< TH1D >( "jet2Tau2_cutDijet", "jet2Tau2_cutDijet", 20, 0., 1. );
		histos1D_[ "jet2Tau2_cutDijet" ]->Sumw2();
		histos1D_[ "jet2Tau3_cutDijet" ] = fs_->make< TH1D >( "jet2Tau3_cutDijet", "jet2Tau3_cutDijet", 20, 0., 1. );
		histos1D_[ "jet2Tau3_cutDijet" ]->Sumw2();
		histos1D_[ "jet2Tau21_cutDijet" ] = fs_->make< TH1D >( "jet2Tau21_cutDijet", "jet2Tau21_cutDijet", 20, 0., 1. );
		histos1D_[ "jet2Tau21_cutDijet" ]->Sumw2();
		histos1D_[ "jet2Tau31_cutDijet" ] = fs_->make< TH1D >( "jet2Tau31_cutDijet", "jet2Tau31_cutDijet", 20, 0., 1. );
		histos1D_[ "jet2Tau31_cutDijet" ]->Sumw2();
		histos1D_[ "jet2Tau32_cutDijet" ] = fs_->make< TH1D >( "jet2Tau32_cutDijet", "jet2Tau32_cutDijet", 20, 0., 1. );
		histos1D_[ "jet2Tau32_cutDijet" ]->Sumw2();
		histos1D_[ "deltaEtaDijet_cutDijet" ] = fs_->make< TH1D >( "deltaEtaDijet_cutDijet", "deltaEtaDijet_cutDijet", 50, 0., 5. );
		histos1D_[ "deltaEtaDijet_cutDijet" ]->Sumw2();
		histos1D_[ "jet1SubjetPtRatio_cutDijet" ] = fs_->make< TH1D >( "jet1SubjetPtRatio_cutDijet", "jet1SubjetPtRatio_cutDijet", 20, 0, 1.);
		histos1D_[ "jet1SubjetPtRatio_cutDijet" ]->Sumw2();
		histos1D_[ "jet2SubjetPtRatio_cutDijet" ] = fs_->make< TH1D >( "jet2SubjetPtRatio_cutDijet", "jet2SubjetPtRatio_cutDijet", 20, 0., 1. );
		histos1D_[ "jet2SubjetPtRatio_cutDijet" ]->Sumw2();
		histos1D_[ "subjetPtRatio_cutDijet" ] = fs_->make< TH1D >( "subjetPtRatio_cutDijet", "subjetPtRatio_cutDijet", 20, 0., 1. );
		histos1D_[ "subjetPtRatio_cutDijet" ]->Sumw2();

		histos2D_[ "jetTrimmedMassHT_cutDijet" ] = fs_->make< TH2D >( "jetTrimmedMassHT_cutDijet", "jetTrimmedMassHT_cutDijet", 30, 0., 300., 500, 0., 5000. );
		histos2D_[ "jetTrimmedMassHT_cutDijet" ]->Sumw2();
		histos2D_[ "leadMassHT_cutDijet" ] = fs_->make< TH2D >( "leadMassHT_cutDijet", "leadMassHT_cutDijet", 30, 0., 300., 500, 0., 5000. );
		histos2D_[ "leadMassHT_cutDijet" ]->Sumw2();
		histos2D_[ "massAveHT_cutDijet" ] = fs_->make< TH2D >( "massAveHT_cutDijet", "massAveHT_cutDijet", 30, 0., 300., 500, 0., 5000. );
		histos2D_[ "massAveHT_cutDijet" ]->Sumw2();

		histos2D_[ "massAvevsJet1Mass_cutDijet" ] = fs_->make< TH2D >( "massAvevsJet1Mass_cutDijet", "massAvevsJet1Mass_cutDijet", 60, 0., 600., 30, 0., 300. );
		histos2D_[ "massAvevsJet1Mass_cutDijet" ]->Sumw2();
		histos2D_[ "massAvevsJet2Mass_cutDijet" ] = fs_->make< TH2D >( "massAvevsJet2Mass_cutDijet", "massAvevsJet2Mass_cutDijet", 60, 0., 600., 30, 0., 300. );
		histos2D_[ "massAvevsJet2Mass_cutDijet" ]->Sumw2();
		histos2D_[ "massAvevsMassAsym_cutDijet" ] = fs_->make< TH2D >( "massAvevsMassAsym_cutDijet", "massAvevsMassAsym_cutDijet", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsMassAsym_cutDijet" ]->Sumw2();
		histos2D_[ "massAvevsDEta_cutDijet" ] = fs_->make< TH2D >( "massAvevsDEta_cutDijet", "massAvevsDEta_cutDijet", 60, 0., 600., 50, 0., 5. );
		histos2D_[ "massAvevsDEta_cutDijet" ]->Sumw2();
		histos2D_[ "massAvevsCosThetaStar_cutDijet" ] = fs_->make< TH2D >( "massAvevsCosThetaStar_cutDijet", "massAvevsCosThetaStar_cutDijet", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsCosThetaStar_cutDijet" ]->Sumw2();
		histos2D_[ "massAvevsJet1Tau21_cutDijet" ] = fs_->make< TH2D >( "massAvevsJet1Tau21_cutDijet", "massAvevsJet1Tau21_cutDijet", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1Tau21_cutDijet" ]->Sumw2();
		histos2D_[ "massAvevsJet1Tau31_cutDijet" ] = fs_->make< TH2D >( "massAvevsJet1Tau31_cutDijet", "massAvevsJet1Tau31_cutDijet", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1Tau31_cutDijet" ]->Sumw2();
		histos2D_[ "massAvevsJet1Tau32_cutDijet" ] = fs_->make< TH2D >( "massAvevsJet1Tau32_cutDijet", "massAvevsJet1Tau32_cutDijet", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1Tau32_cutDijet" ]->Sumw2();
		histos2D_[ "massAvevsJet2Tau21_cutDijet" ] = fs_->make< TH2D >( "massAvevsJet2Tau21_cutDijet", "massAvevsJet2Tau21_cutDijet", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2Tau21_cutDijet" ]->Sumw2();
		histos2D_[ "massAvevsJet2Tau31_cutDijet" ] = fs_->make< TH2D >( "massAvevsJet2Tau31_cutDijet", "massAvevsJet2Tau31_cutDijet", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2Tau31_cutDijet" ]->Sumw2();
		histos2D_[ "massAvevsJet2Tau32_cutDijet" ] = fs_->make< TH2D >( "massAvevsJet2Tau32_cutDijet", "massAvevsJet2Tau32_cutDijet", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2Tau32_cutDijet" ]->Sumw2();
		histos2D_[ "massAvevsJet1SubjetPtRatio_cutDijet" ] = fs_->make< TH2D >( "massAvevsJet1SubjetPtRatio_cutDijet", "massAvevsJet1SubjetPtRatio_cutDijet", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1SubjetPtRatio_cutDijet" ]->Sumw2();
		histos2D_[ "massAvevsJet2SubjetPtRatio_cutDijet" ] = fs_->make< TH2D >( "massAvevsJet2SubjetPtRatio_cutDijet", "massAvevsJet2SubjetPtRatio_cutDijet", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2SubjetPtRatio_cutDijet" ]->Sumw2();

		histos2D_[ "jet1vs2Mass_cutDijet" ] = fs_->make< TH2D >( "jet1vs2Mass_cutDijet", "jet1vs2Mass_cutDijet", 60, 0., 600., 30, 0., 300. );
		histos2D_[ "jet1vs2Mass_cutDijet" ]->Sumw2();
		histos2D_[ "dijetCorr_cutDijet" ] = fs_->make< TH2D >( "dijetCorr_cutDijet", "dijetCorr_cutDijet", 56, -3.5, 3.5, 56, -3.5, 3.5 );
		histos2D_[ "dijetCorr_cutDijet" ]->Sumw2();
		histos2D_[ "dijetCorrPhi_cutDijet" ] = fs_->make< TH2D >( "dijetCorrPhi_cutDijet", "dijetCorrPhi_cutDijet", 56, -3.5, 3.5, 56, -3.5, 3.5 );
		histos2D_[ "dijetCorrPhi_cutDijet" ]->Sumw2();

		histos1D_[ "subjetPolAngle13412_cutDijet" ] = fs_->make< TH1D >( "subjetPolAngle13412_cutDijet", "subjetPolAngle13412_cutDijet", 100, 0., 1. );
		histos1D_[ "subjetPolAngle13412_cutDijet" ]->Sumw2();
		histos1D_[ "subjetPolAngle31234_cutDijet" ] = fs_->make< TH1D >( "subjetPolAngle31234_cutDijet", "subjetPolAngle31234_cutDijet", 100, 0., 1. );
		histos1D_[ "subjetPolAngle31234_cutDijet" ]->Sumw2();
		histos1D_[ "mu1_cutDijet" ] = fs_->make< TH1D >( "mu1_cutDijet", "mu1_cutDijet", 150, 0., 1.5 );
		histos1D_[ "mu1_cutDijet" ]->Sumw2();
		histos1D_[ "mu2_cutDijet" ] = fs_->make< TH1D >( "mu2_cutDijet", "mu2_cutDijet", 150, 0., 1.5 );
		histos1D_[ "mu2_cutDijet" ]->Sumw2();
		histos1D_[ "mu3_cutDijet" ] = fs_->make< TH1D >( "mu3_cutDijet", "mu3_cutDijet", 150, 0., 1.5 );
		histos1D_[ "mu3_cutDijet" ]->Sumw2();
		histos1D_[ "mu4_cutDijet" ] = fs_->make< TH1D >( "mu4_cutDijet", "mu4_cutDijet", 150, 0., 1.5 );
		histos1D_[ "mu4_cutDijet" ]->Sumw2();
		histos1D_[ "mu5_cutDijet" ] = fs_->make< TH1D >( "mu5_cutDijet", "mu5_cutDijet", 150, 0., 1.5 );
		histos1D_[ "mu5_cutDijet" ]->Sumw2();
		histos1D_[ "mu6_cutDijet" ] = fs_->make< TH1D >( "mu6_cutDijet", "mu6_cutDijet", 150, 0., 1.5 );
		histos1D_[ "mu6_cutDijet" ]->Sumw2();
		histos2D_[ "subjetPolAngle13412vs31234_cutDijet" ] = fs_->make< TH2D >( "subjetPolAngle13412vs31234_cutDijet", "subjetPolAngle13412vs31234_cutDijet", 100, 0., 1., 100, 0., 1. );
		histos2D_[ "subjetPolAngle13412vs31234_cutDijet" ]->Sumw2();
		histos2D_[ "subjetPolAngle31234vsSubjetPtRatio_cutDijet" ] = fs_->make< TH2D >( "subjetPolAngle31234vsSubjetPtRatio_cutDijet", "subjetPolAngle31234vsSubjetPtRatio_cutDijet", 100, 0., 1., 20, 0., 1. );
		histos2D_[ "subjetPolAngle31234vsSubjetPtRatio_cutDijet" ]->Sumw2();
		histos2D_[ "mu1234_cutDijet" ] = fs_->make< TH2D >( "mu1234_cutDijet", "mu1234_cutDijet", 150, 0., 1.5, 150, 0., 1.5 );
		histos2D_[ "mu1234_cutDijet" ]->Sumw2();
		histos2D_[ "dalitz1234_cutDijet" ] = fs_->make< TH2D >( "dalitz1234_cutDijet", "dalitz1234_cutDijet", 150, 0., 1.5, 150, 0., 1.5 );
		histos2D_[ "dalitz1234_cutDijet" ]->Sumw2();
		histos2D_[ "mu3412_cutDijet" ] = fs_->make< TH2D >( "mu3412_cutDijet", "mu3412_cutDijet", 150, 0., 1.5, 150, 0., 1.5 );
		histos2D_[ "mu3412_cutDijet" ]->Sumw2();
		histos2D_[ "dalitz3412_cutDijet" ] = fs_->make< TH2D >( "dalitz3412_cutDijet", "dalitz3412_cutDijet", 150, 0., 1.5, 150, 0., 1.5 );
		histos2D_[ "dalitz3412_cutDijet" ]->Sumw2();


		histos1D_[ "HT_cutMassAsym" ] = fs_->make< TH1D >( "HT_cutMassAsym", "HT_cutMassAsym", 500, 0., 5000. );
		histos1D_[ "HT_cutMassAsym" ]->Sumw2();
		histos1D_[ "NPV_cutMassAsym" ] = fs_->make< TH1D >( "NPV_cutMassAsym", "NPV_cutMassAsym", 80, 0., 80. );
		histos1D_[ "NPV_cutMassAsym" ]->Sumw2();
		histos1D_[ "jetNum_cutMassAsym" ] = fs_->make< TH1D >( "jetNum_cutMassAsym", "jetNum_cutMassAsym", 10, 0., 10. );
		histos1D_[ "jetNum_cutMassAsym" ]->Sumw2();
		histos1D_[ "jet1Pt_cutMassAsym" ] = fs_->make< TH1D >( "jet1Pt_cutMassAsym", "jet1Pt_cutMassAsym", 100, 0., 1000. );
		histos1D_[ "jet1Pt_cutMassAsym" ]->Sumw2();
		histos1D_[ "jet1Eta_cutMassAsym" ] = fs_->make< TH1D >( "jet1Eta_cutMassAsym", "jet1Eta_cutMassAsym", 100, -5., 5. );
		histos1D_[ "jet1Eta_cutMassAsym" ]->Sumw2();
		histos1D_[ "jet1Mass_cutMassAsym" ] = fs_->make< TH1D >( "jet1Mass_cutMassAsym", "jet1Mass_cutMassAsym", 60, 0., 600. );
		histos1D_[ "jet1Mass_cutMassAsym" ]->Sumw2();
		histos1D_[ "jet2Pt_cutMassAsym" ] = fs_->make< TH1D >( "jet2Pt_cutMassAsym", "jet2Pt_cutMassAsym", 100, 0., 1000. );
		histos1D_[ "jet2Pt_cutMassAsym" ]->Sumw2();
		histos1D_[ "jet2Eta_cutMassAsym" ] = fs_->make< TH1D >( "jet2Eta_cutMassAsym", "jet2Eta_cutMassAsym", 100, -5., 5. );
		histos1D_[ "jet2Eta_cutMassAsym" ]->Sumw2();
		histos1D_[ "jet2Mass_cutMassAsym" ] = fs_->make< TH1D >( "jet2Mass_cutMassAsym", "jet2Mass_cutMassAsym", 60, 0., 600. );
		histos1D_[ "jet2Mass_cutMassAsym" ]->Sumw2();

		histos1D_[ "massAsymmetry_cutMassAsym" ] = fs_->make< TH1D >( "massAsymmetry_cutMassAsym", "massAsymmetry_cutMassAsym", 20, 0., 1. );
		histos1D_[ "massAsymmetry_cutMassAsym" ]->Sumw2();
		histos1D_[ "massAve_cutMassAsym" ] = fs_->make< TH1D >( "massAve_cutMassAsym", "massAve_cutMassAsym", 60, 0., 600. );
		histos1D_[ "massAve_cutMassAsym" ]->Sumw2();
		histos1D_[ "cosThetaStar_cutMassAsym" ] = fs_->make< TH1D >( "cosThetaStar_cutMassAsym", "cosThetaStar_cutMassAsym", 20, 0., 1. );
		histos1D_[ "cosThetaStar_cutMassAsym" ]->Sumw2();
		histos1D_[ "jet1Tau1_cutMassAsym" ] = fs_->make< TH1D >( "jet1Tau1_cutMassAsym", "jet1Tau1_cutMassAsym", 20, 0., 1. );
		histos1D_[ "jet1Tau1_cutMassAsym" ]->Sumw2();
		histos1D_[ "jet1Tau2_cutMassAsym" ] = fs_->make< TH1D >( "jet1Tau2_cutMassAsym", "jet1Tau2_cutMassAsym", 20, 0., 1. );
		histos1D_[ "jet1Tau2_cutMassAsym" ]->Sumw2();
		histos1D_[ "jet1Tau3_cutMassAsym" ] = fs_->make< TH1D >( "jet1Tau3_cutMassAsym", "jet1Tau3_cutMassAsym", 20, 0., 1. );
		histos1D_[ "jet1Tau3_cutMassAsym" ]->Sumw2();
		histos1D_[ "jet1Tau21_cutMassAsym" ] = fs_->make< TH1D >( "jet1Tau21_cutMassAsym", "jet1Tau21_cutMassAsym", 20, 0., 1. );
		histos1D_[ "jet1Tau21_cutMassAsym" ]->Sumw2();
		histos1D_[ "jet1Tau31_cutMassAsym" ] = fs_->make< TH1D >( "jet1Tau31_cutMassAsym", "jet1Tau31_cutMassAsym", 20, 0., 1. );
		histos1D_[ "jet1Tau31_cutMassAsym" ]->Sumw2();
		histos1D_[ "jet1Tau32_cutMassAsym" ] = fs_->make< TH1D >( "jet1Tau32_cutMassAsym", "jet1Tau32_cutMassAsym", 20, 0., 1. );
		histos1D_[ "jet1Tau32_cutMassAsym" ]->Sumw2();
		histos1D_[ "jet2Tau1_cutMassAsym" ] = fs_->make< TH1D >( "jet2Tau1_cutMassAsym", "jet2Tau1_cutMassAsym", 20, 0., 1. );
		histos1D_[ "jet2Tau1_cutMassAsym" ]->Sumw2();
		histos1D_[ "jet2Tau2_cutMassAsym" ] = fs_->make< TH1D >( "jet2Tau2_cutMassAsym", "jet2Tau2_cutMassAsym", 20, 0., 1. );
		histos1D_[ "jet2Tau2_cutMassAsym" ]->Sumw2();
		histos1D_[ "jet2Tau3_cutMassAsym" ] = fs_->make< TH1D >( "jet2Tau3_cutMassAsym", "jet2Tau3_cutMassAsym", 20, 0., 1. );
		histos1D_[ "jet2Tau3_cutMassAsym" ]->Sumw2();
		histos1D_[ "jet2Tau21_cutMassAsym" ] = fs_->make< TH1D >( "jet2Tau21_cutMassAsym", "jet2Tau21_cutMassAsym", 20, 0., 1. );
		histos1D_[ "jet2Tau21_cutMassAsym" ]->Sumw2();
		histos1D_[ "jet2Tau31_cutMassAsym" ] = fs_->make< TH1D >( "jet2Tau31_cutMassAsym", "jet2Tau31_cutMassAsym", 20, 0., 1. );
		histos1D_[ "jet2Tau31_cutMassAsym" ]->Sumw2();
		histos1D_[ "jet2Tau32_cutMassAsym" ] = fs_->make< TH1D >( "jet2Tau32_cutMassAsym", "jet2Tau32_cutMassAsym", 20, 0., 1. );
		histos1D_[ "jet2Tau32_cutMassAsym" ]->Sumw2();
		histos1D_[ "deltaEtaDijet_cutMassAsym" ] = fs_->make< TH1D >( "deltaEtaDijet_cutMassAsym", "deltaEtaDijet_cutMassAsym", 50, 0., 5. );
		histos1D_[ "deltaEtaDijet_cutMassAsym" ]->Sumw2();
		histos1D_[ "jet1SubjetPtRatio_cutMassAsym" ] = fs_->make< TH1D >( "jet1SubjetPtRatio_cutMassAsym", "jet1SubjetPtRatio_cutMassAsym", 20, 0, 1.);
		histos1D_[ "jet1SubjetPtRatio_cutMassAsym" ]->Sumw2();
		histos1D_[ "jet2SubjetPtRatio_cutMassAsym" ] = fs_->make< TH1D >( "jet2SubjetPtRatio_cutMassAsym", "jet2SubjetPtRatio_cutMassAsym", 20, 0., 1. );
		histos1D_[ "jet2SubjetPtRatio_cutMassAsym" ]->Sumw2();
		histos1D_[ "subjetPtRatio_cutMassAsym" ] = fs_->make< TH1D >( "subjetPtRatio_cutMassAsym", "subjetPtRatio_cutMassAsym", 20, 0., 1. );
		histos1D_[ "subjetPtRatio_cutMassAsym" ]->Sumw2();

		histos2D_[ "jetTrimmedMassHT_cutMassAsym" ] = fs_->make< TH2D >( "jetTrimmedMassHT_cutMassAsym", "jetTrimmedMassHT_cutMassAsym", 30, 0., 300., 500, 0., 5000. );
		histos2D_[ "jetTrimmedMassHT_cutMassAsym" ]->Sumw2();
		histos2D_[ "leadMassHT_cutMassAsym" ] = fs_->make< TH2D >( "leadMassHT_cutMassAsym", "leadMassHT_cutMassAsym", 30, 0., 300., 500, 0., 5000. );
		histos2D_[ "leadMassHT_cutMassAsym" ]->Sumw2();
		histos2D_[ "massAveHT_cutMassAsym" ] = fs_->make< TH2D >( "massAveHT_cutMassAsym", "massAveHT_cutMassAsym", 30, 0., 300., 500, 0., 5000. );
		histos2D_[ "massAveHT_cutMassAsym" ]->Sumw2();

		histos2D_[ "massAvevsJet1Mass_cutMassAsym" ] = fs_->make< TH2D >( "massAvevsJet1Mass_cutMassAsym", "massAvevsJet1Mass_cutMassAsym", 60, 0., 600., 30, 0., 300. );
		histos2D_[ "massAvevsJet1Mass_cutMassAsym" ]->Sumw2();
		histos2D_[ "massAvevsJet2Mass_cutMassAsym" ] = fs_->make< TH2D >( "massAvevsJet2Mass_cutMassAsym", "massAvevsJet2Mass_cutMassAsym", 60, 0., 600., 30, 0., 300. );
		histos2D_[ "massAvevsJet2Mass_cutMassAsym" ]->Sumw2();
		histos2D_[ "massAvevsMassAsym_cutMassAsym" ] = fs_->make< TH2D >( "massAvevsMassAsym_cutMassAsym", "massAvevsMassAsym_cutMassAsym", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsMassAsym_cutMassAsym" ]->Sumw2();
		histos2D_[ "massAvevsDEta_cutMassAsym" ] = fs_->make< TH2D >( "massAvevsDEta_cutMassAsym", "massAvevsDEta_cutMassAsym", 60, 0., 600., 50, 0., 5. );
		histos2D_[ "massAvevsDEta_cutMassAsym" ]->Sumw2();
		histos2D_[ "massAvevsCosThetaStar_cutMassAsym" ] = fs_->make< TH2D >( "massAvevsCosThetaStar_cutMassAsym", "massAvevsCosThetaStar_cutMassAsym", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsCosThetaStar_cutMassAsym" ]->Sumw2();
		histos2D_[ "massAvevsJet1Tau21_cutMassAsym" ] = fs_->make< TH2D >( "massAvevsJet1Tau21_cutMassAsym", "massAvevsJet1Tau21_cutMassAsym", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1Tau21_cutMassAsym" ]->Sumw2();
		histos2D_[ "massAvevsJet1Tau31_cutMassAsym" ] = fs_->make< TH2D >( "massAvevsJet1Tau31_cutMassAsym", "massAvevsJet1Tau31_cutMassAsym", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1Tau31_cutMassAsym" ]->Sumw2();
		histos2D_[ "massAvevsJet1Tau32_cutMassAsym" ] = fs_->make< TH2D >( "massAvevsJet1Tau32_cutMassAsym", "massAvevsJet1Tau32_cutMassAsym", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1Tau32_cutMassAsym" ]->Sumw2();
		histos2D_[ "massAvevsJet2Tau21_cutMassAsym" ] = fs_->make< TH2D >( "massAvevsJet2Tau21_cutMassAsym", "massAvevsJet2Tau21_cutMassAsym", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2Tau21_cutMassAsym" ]->Sumw2();
		histos2D_[ "massAvevsJet2Tau31_cutMassAsym" ] = fs_->make< TH2D >( "massAvevsJet2Tau31_cutMassAsym", "massAvevsJet2Tau31_cutMassAsym", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2Tau31_cutMassAsym" ]->Sumw2();
		histos2D_[ "massAvevsJet2Tau32_cutMassAsym" ] = fs_->make< TH2D >( "massAvevsJet2Tau32_cutMassAsym", "massAvevsJet2Tau32_cutMassAsym", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2Tau32_cutMassAsym" ]->Sumw2();
		histos2D_[ "massAvevsJet1SubjetPtRatio_cutMassAsym" ] = fs_->make< TH2D >( "massAvevsJet1SubjetPtRatio_cutMassAsym", "massAvevsJet1SubjetPtRatio_cutMassAsym", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1SubjetPtRatio_cutMassAsym" ]->Sumw2();
		histos2D_[ "massAvevsJet2SubjetPtRatio_cutMassAsym" ] = fs_->make< TH2D >( "massAvevsJet2SubjetPtRatio_cutMassAsym", "massAvevsJet2SubjetPtRatio_cutMassAsym", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2SubjetPtRatio_cutMassAsym" ]->Sumw2();
		histos2D_[ "jet1vs2Mass_cutMassAsym" ] = fs_->make< TH2D >( "jet1vs2Mass_cutMassAsym", "jet1vs2Mass_cutMassAsym", 60, 0., 600., 30, 0., 300. );
		histos2D_[ "jet1vs2Mass_cutMassAsym" ]->Sumw2();
		histos2D_[ "dijetCorr_cutMassAsym" ] = fs_->make< TH2D >( "dijetCorr_cutMassAsym", "dijetCorr_cutMassAsym", 56, -3.5, 3.5, 56, -3.5, 3.5 );
		histos2D_[ "dijetCorr_cutMassAsym" ]->Sumw2();
		histos2D_[ "dijetCorrPhi_cutMassAsym" ] = fs_->make< TH2D >( "dijetCorrPhi_cutMassAsym", "dijetCorrPhi_cutMassAsym", 56, -3.5, 3.5, 56, -3.5, 3.5 );
		histos2D_[ "dijetCorrPhi_cutMassAsym" ]->Sumw2();


		histos1D_[ "HT_cutTau21" ] = fs_->make< TH1D >( "HT_cutTau21", "HT_cutTau21", 500, 0., 5000. );
		histos1D_[ "HT_cutTau21" ]->Sumw2();
		histos1D_[ "NPV_cutTau21" ] = fs_->make< TH1D >( "NPV_cutTau21", "NPV_cutTau21", 80, 0., 80. );
		histos1D_[ "NPV_cutTau21" ]->Sumw2();
		histos1D_[ "jetNum_cutTau21" ] = fs_->make< TH1D >( "jetNum_cutTau21", "jetNum_cutTau21", 10, 0., 10. );
		histos1D_[ "jetNum_cutTau21" ]->Sumw2();
		histos1D_[ "jet1Pt_cutTau21" ] = fs_->make< TH1D >( "jet1Pt_cutTau21", "jet1Pt_cutTau21", 100, 0., 1000. );
		histos1D_[ "jet1Pt_cutTau21" ]->Sumw2();
		histos1D_[ "jet1Eta_cutTau21" ] = fs_->make< TH1D >( "jet1Eta_cutTau21", "jet1Eta_cutTau21", 100, -5., 5. );
		histos1D_[ "jet1Eta_cutTau21" ]->Sumw2();
		histos1D_[ "jet1Mass_cutTau21" ] = fs_->make< TH1D >( "jet1Mass_cutTau21", "jet1Mass_cutTau21", 60, 0., 600. );
		histos1D_[ "jet1Mass_cutTau21" ]->Sumw2();
		histos1D_[ "jet2Pt_cutTau21" ] = fs_->make< TH1D >( "jet2Pt_cutTau21", "jet2Pt_cutTau21", 100, 0., 1000. );
		histos1D_[ "jet2Pt_cutTau21" ]->Sumw2();
		histos1D_[ "jet2Eta_cutTau21" ] = fs_->make< TH1D >( "jet2Eta_cutTau21", "jet2Eta_cutTau21", 100, -5., 5. );
		histos1D_[ "jet2Eta_cutTau21" ]->Sumw2();
		histos1D_[ "jet2Mass_cutTau21" ] = fs_->make< TH1D >( "jet2Mass_cutTau21", "jet2Mass_cutTau21", 60, 0., 600. );
		histos1D_[ "jet2Mass_cutTau21" ]->Sumw2();

		histos1D_[ "massAsymmetry_cutTau21" ] = fs_->make< TH1D >( "massAsymmetry_cutTau21", "massAsymmetry_cutTau21", 20, 0., 1. );
		histos1D_[ "massAsymmetry_cutTau21" ]->Sumw2();
		histos1D_[ "massAve_cutTau21" ] = fs_->make< TH1D >( "massAve_cutTau21", "massAve_cutTau21", 60, 0., 600. );
		histos1D_[ "massAve_cutTau21" ]->Sumw2();
		histos1D_[ "cosThetaStar_cutTau21" ] = fs_->make< TH1D >( "cosThetaStar_cutTau21", "cosThetaStar_cutTau21", 20, 0., 1. );
		histos1D_[ "cosThetaStar_cutTau21" ]->Sumw2();
		histos1D_[ "jet1Tau1_cutTau21" ] = fs_->make< TH1D >( "jet1Tau1_cutTau21", "jet1Tau1_cutTau21", 20, 0., 1. );
		histos1D_[ "jet1Tau1_cutTau21" ]->Sumw2();
		histos1D_[ "jet1Tau2_cutTau21" ] = fs_->make< TH1D >( "jet1Tau2_cutTau21", "jet1Tau2_cutTau21", 20, 0., 1. );
		histos1D_[ "jet1Tau2_cutTau21" ]->Sumw2();
		histos1D_[ "jet1Tau3_cutTau21" ] = fs_->make< TH1D >( "jet1Tau3_cutTau21", "jet1Tau3_cutTau21", 20, 0., 1. );
		histos1D_[ "jet1Tau3_cutTau21" ]->Sumw2();
		histos1D_[ "jet1Tau21_cutTau21" ] = fs_->make< TH1D >( "jet1Tau21_cutTau21", "jet1Tau21_cutTau21", 20, 0., 1. );
		histos1D_[ "jet1Tau21_cutTau21" ]->Sumw2();
		histos1D_[ "jet1Tau31_cutTau21" ] = fs_->make< TH1D >( "jet1Tau31_cutTau21", "jet1Tau31_cutTau21", 20, 0., 1. );
		histos1D_[ "jet1Tau31_cutTau21" ]->Sumw2();
		histos1D_[ "jet1Tau32_cutTau21" ] = fs_->make< TH1D >( "jet1Tau32_cutTau21", "jet1Tau32_cutTau21", 20, 0., 1. );
		histos1D_[ "jet1Tau32_cutTau21" ]->Sumw2();
		histos1D_[ "jet2Tau1_cutTau21" ] = fs_->make< TH1D >( "jet2Tau1_cutTau21", "jet2Tau1_cutTau21", 20, 0., 1. );
		histos1D_[ "jet2Tau1_cutTau21" ]->Sumw2();
		histos1D_[ "jet2Tau2_cutTau21" ] = fs_->make< TH1D >( "jet2Tau2_cutTau21", "jet2Tau2_cutTau21", 20, 0., 1. );
		histos1D_[ "jet2Tau2_cutTau21" ]->Sumw2();
		histos1D_[ "jet2Tau3_cutTau21" ] = fs_->make< TH1D >( "jet2Tau3_cutTau21", "jet2Tau3_cutTau21", 20, 0., 1. );
		histos1D_[ "jet2Tau3_cutTau21" ]->Sumw2();
		histos1D_[ "jet2Tau21_cutTau21" ] = fs_->make< TH1D >( "jet2Tau21_cutTau21", "jet2Tau21_cutTau21", 20, 0., 1. );
		histos1D_[ "jet2Tau21_cutTau21" ]->Sumw2();
		histos1D_[ "jet2Tau31_cutTau21" ] = fs_->make< TH1D >( "jet2Tau31_cutTau21", "jet2Tau31_cutTau21", 20, 0., 1. );
		histos1D_[ "jet2Tau31_cutTau21" ]->Sumw2();
		histos1D_[ "jet2Tau32_cutTau21" ] = fs_->make< TH1D >( "jet2Tau32_cutTau21", "jet2Tau32_cutTau21", 20, 0., 1. );
		histos1D_[ "jet2Tau32_cutTau21" ]->Sumw2();
		histos1D_[ "deltaEtaDijet_cutTau21" ] = fs_->make< TH1D >( "deltaEtaDijet_cutTau21", "deltaEtaDijet_cutTau21", 50, 0., 5. );
		histos1D_[ "deltaEtaDijet_cutTau21" ]->Sumw2();
		histos1D_[ "jet1SubjetPtRatio_cutTau21" ] = fs_->make< TH1D >( "jet1SubjetPtRatio_cutTau21", "jet1SubjetPtRatio_cutTau21", 20, 0, 1.);
		histos1D_[ "jet1SubjetPtRatio_cutTau21" ]->Sumw2();
		histos1D_[ "jet2SubjetPtRatio_cutTau21" ] = fs_->make< TH1D >( "jet2SubjetPtRatio_cutTau21", "jet2SubjetPtRatio_cutTau21", 20, 0., 1. );
		histos1D_[ "jet2SubjetPtRatio_cutTau21" ]->Sumw2();
		histos1D_[ "subjetPtRatio_cutTau21" ] = fs_->make< TH1D >( "subjetPtRatio_cutTau21", "subjetPtRatio_cutTau21", 20, 0., 1. );
		histos1D_[ "subjetPtRatio_cutTau21" ]->Sumw2();

		histos2D_[ "jetTrimmedMassHT_cutTau21" ] = fs_->make< TH2D >( "jetTrimmedMassHT_cutTau21", "jetTrimmedMassHT_cutTau21", 30, 0., 300., 500, 0., 5000. );
		histos2D_[ "jetTrimmedMassHT_cutTau21" ]->Sumw2();
		histos2D_[ "leadMassHT_cutTau21" ] = fs_->make< TH2D >( "leadMassHT_cutTau21", "leadMassHT_cutTau21", 30, 0., 300., 500, 0., 5000. );
		histos2D_[ "leadMassHT_cutTau21" ]->Sumw2();
		histos2D_[ "massAveHT_cutTau21" ] = fs_->make< TH2D >( "massAveHT_cutTau21", "massAveHT_cutTau21", 30, 0., 300., 500, 0., 5000. );
		histos2D_[ "massAveHT_cutTau21" ]->Sumw2();

		histos2D_[ "massAvevsJet1Mass_cutTau21" ] = fs_->make< TH2D >( "massAvevsJet1Mass_cutTau21", "massAvevsJet1Mass_cutTau21", 60, 0., 600., 30, 0., 300. );
		histos2D_[ "massAvevsJet1Mass_cutTau21" ]->Sumw2();
		histos2D_[ "massAvevsJet2Mass_cutTau21" ] = fs_->make< TH2D >( "massAvevsJet2Mass_cutTau21", "massAvevsJet2Mass_cutTau21", 60, 0., 600., 30, 0., 300. );
		histos2D_[ "massAvevsJet2Mass_cutTau21" ]->Sumw2();
		histos2D_[ "massAvevsMassAsym_cutTau21" ] = fs_->make< TH2D >( "massAvevsMassAsym_cutTau21", "massAvevsMassAsym_cutTau21", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsMassAsym_cutTau21" ]->Sumw2();
		histos2D_[ "massAvevsDEta_cutTau21" ] = fs_->make< TH2D >( "massAvevsDEta_cutTau21", "massAvevsDEta_cutTau21", 60, 0., 600., 50, 0., 5. );
		histos2D_[ "massAvevsDEta_cutTau21" ]->Sumw2();
		histos2D_[ "massAvevsCosThetaStar_cutTau21" ] = fs_->make< TH2D >( "massAvevsCosThetaStar_cutTau21", "massAvevsCosThetaStar_cutTau21", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsCosThetaStar_cutTau21" ]->Sumw2();
		histos2D_[ "massAvevsJet1Tau21_cutTau21" ] = fs_->make< TH2D >( "massAvevsJet1Tau21_cutTau21", "massAvevsJet1Tau21_cutTau21", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1Tau21_cutTau21" ]->Sumw2();
		histos2D_[ "massAvevsJet1Tau31_cutTau21" ] = fs_->make< TH2D >( "massAvevsJet1Tau31_cutTau21", "massAvevsJet1Tau31_cutTau21", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1Tau31_cutTau21" ]->Sumw2();
		histos2D_[ "massAvevsJet1Tau32_cutTau21" ] = fs_->make< TH2D >( "massAvevsJet1Tau32_cutTau21", "massAvevsJet1Tau32_cutTau21", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1Tau32_cutTau21" ]->Sumw2();
		histos2D_[ "massAvevsJet2Tau21_cutTau21" ] = fs_->make< TH2D >( "massAvevsJet2Tau21_cutTau21", "massAvevsJet2Tau21_cutTau21", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2Tau21_cutTau21" ]->Sumw2();
		histos2D_[ "massAvevsJet2Tau31_cutTau21" ] = fs_->make< TH2D >( "massAvevsJet2Tau31_cutTau21", "massAvevsJet2Tau31_cutTau21", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2Tau31_cutTau21" ]->Sumw2();
		histos2D_[ "massAvevsJet2Tau32_cutTau21" ] = fs_->make< TH2D >( "massAvevsJet2Tau32_cutTau21", "massAvevsJet2Tau32_cutTau21", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2Tau32_cutTau21" ]->Sumw2();
		histos2D_[ "massAvevsJet1SubjetPtRatio_cutTau21" ] = fs_->make< TH2D >( "massAvevsJet1SubjetPtRatio_cutTau21", "massAvevsJet1SubjetPtRatio_cutTau21", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1SubjetPtRatio_cutTau21" ]->Sumw2();
		histos2D_[ "massAvevsJet2SubjetPtRatio_cutTau21" ] = fs_->make< TH2D >( "massAvevsJet2SubjetPtRatio_cutTau21", "massAvevsJet2SubjetPtRatio_cutTau21", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2SubjetPtRatio_cutTau21" ]->Sumw2();
		histos2D_[ "jet1vs2Mass_cutTau21" ] = fs_->make< TH2D >( "jet1vs2Mass_cutTau21", "jet1vs2Mass_cutTau21", 60, 0., 600., 30, 0., 300. );
		histos2D_[ "jet1vs2Mass_cutTau21" ]->Sumw2();
		histos2D_[ "dijetCorr_cutTau21" ] = fs_->make< TH2D >( "dijetCorr_cutTau21", "dijetCorr_cutTau21", 56, -3.5, 3.5, 56, -3.5, 3.5 );
		histos2D_[ "dijetCorr_cutTau21" ]->Sumw2();
		histos2D_[ "dijetCorrPhi_cutTau21" ] = fs_->make< TH2D >( "dijetCorrPhi_cutTau21", "dijetCorrPhi_cutTau21", 56, -3.5, 3.5, 56, -3.5, 3.5 );
		histos2D_[ "dijetCorrPhi_cutTau21" ]->Sumw2();



		histos1D_[ "HT_cutCosTheta" ] = fs_->make< TH1D >( "HT_cutCosTheta", "HT_cutCosTheta", 500, 0., 5000. );
		histos1D_[ "HT_cutCosTheta" ]->Sumw2();
		histos1D_[ "NPV_cutCosTheta" ] = fs_->make< TH1D >( "NPV_cutCosTheta", "NPV_cutCosTheta", 80, 0., 80. );
		histos1D_[ "NPV_cutCosTheta" ]->Sumw2();
		histos1D_[ "jetNum_cutCosTheta" ] = fs_->make< TH1D >( "jetNum_cutCosTheta", "jetNum_cutCosTheta", 10, 0., 10. );
		histos1D_[ "jetNum_cutCosTheta" ]->Sumw2();
		histos1D_[ "jet1Pt_cutCosTheta" ] = fs_->make< TH1D >( "jet1Pt_cutCosTheta", "jet1Pt_cutCosTheta", 100, 0., 1000. );
		histos1D_[ "jet1Pt_cutCosTheta" ]->Sumw2();
		histos1D_[ "jet1Eta_cutCosTheta" ] = fs_->make< TH1D >( "jet1Eta_cutCosTheta", "jet1Eta_cutCosTheta", 100, -5., 5. );
		histos1D_[ "jet1Eta_cutCosTheta" ]->Sumw2();
		histos1D_[ "jet1Mass_cutCosTheta" ] = fs_->make< TH1D >( "jet1Mass_cutCosTheta", "jet1Mass_cutCosTheta", 60, 0., 600. );
		histos1D_[ "jet1Mass_cutCosTheta" ]->Sumw2();
		histos1D_[ "jet2Pt_cutCosTheta" ] = fs_->make< TH1D >( "jet2Pt_cutCosTheta", "jet2Pt_cutCosTheta", 100, 0., 1000. );
		histos1D_[ "jet2Pt_cutCosTheta" ]->Sumw2();
		histos1D_[ "jet2Eta_cutCosTheta" ] = fs_->make< TH1D >( "jet2Eta_cutCosTheta", "jet2Eta_cutCosTheta", 100, -5., 5. );
		histos1D_[ "jet2Eta_cutCosTheta" ]->Sumw2();
		histos1D_[ "jet2Mass_cutCosTheta" ] = fs_->make< TH1D >( "jet2Mass_cutCosTheta", "jet2Mass_cutCosTheta", 60, 0., 600. );
		histos1D_[ "jet2Mass_cutCosTheta" ]->Sumw2();

		histos1D_[ "massAsymmetry_cutCosTheta" ] = fs_->make< TH1D >( "massAsymmetry_cutCosTheta", "massAsymmetry_cutCosTheta", 20, 0., 1. );
		histos1D_[ "massAsymmetry_cutCosTheta" ]->Sumw2();
		histos1D_[ "massAve_cutCosTheta" ] = fs_->make< TH1D >( "massAve_cutCosTheta", "massAve_cutCosTheta", 60, 0., 600. );
		histos1D_[ "massAve_cutCosTheta" ]->Sumw2();
		histos1D_[ "cosThetaStar_cutCosTheta" ] = fs_->make< TH1D >( "cosThetaStar_cutCosTheta", "cosThetaStar_cutCosTheta", 20, 0., 1. );
		histos1D_[ "cosThetaStar_cutCosTheta" ]->Sumw2();
		histos1D_[ "jet1Tau1_cutCosTheta" ] = fs_->make< TH1D >( "jet1Tau1_cutCosTheta", "jet1Tau1_cutCosTheta", 20, 0., 1. );
		histos1D_[ "jet1Tau1_cutCosTheta" ]->Sumw2();
		histos1D_[ "jet1Tau2_cutCosTheta" ] = fs_->make< TH1D >( "jet1Tau2_cutCosTheta", "jet1Tau2_cutCosTheta", 20, 0., 1. );
		histos1D_[ "jet1Tau2_cutCosTheta" ]->Sumw2();
		histos1D_[ "jet1Tau3_cutCosTheta" ] = fs_->make< TH1D >( "jet1Tau3_cutCosTheta", "jet1Tau3_cutCosTheta", 20, 0., 1. );
		histos1D_[ "jet1Tau3_cutCosTheta" ]->Sumw2();
		histos1D_[ "jet1Tau21_cutCosTheta" ] = fs_->make< TH1D >( "jet1Tau21_cutCosTheta", "jet1Tau21_cutCosTheta", 20, 0., 1. );
		histos1D_[ "jet1Tau21_cutCosTheta" ]->Sumw2();
		histos1D_[ "jet1Tau31_cutCosTheta" ] = fs_->make< TH1D >( "jet1Tau31_cutCosTheta", "jet1Tau31_cutCosTheta", 20, 0., 1. );
		histos1D_[ "jet1Tau31_cutCosTheta" ]->Sumw2();
		histos1D_[ "jet1Tau32_cutCosTheta" ] = fs_->make< TH1D >( "jet1Tau32_cutCosTheta", "jet1Tau32_cutCosTheta", 20, 0., 1. );
		histos1D_[ "jet1Tau32_cutCosTheta" ]->Sumw2();
		histos1D_[ "jet2Tau1_cutCosTheta" ] = fs_->make< TH1D >( "jet2Tau1_cutCosTheta", "jet2Tau1_cutCosTheta", 20, 0., 1. );
		histos1D_[ "jet2Tau1_cutCosTheta" ]->Sumw2();
		histos1D_[ "jet2Tau2_cutCosTheta" ] = fs_->make< TH1D >( "jet2Tau2_cutCosTheta", "jet2Tau2_cutCosTheta", 20, 0., 1. );
		histos1D_[ "jet2Tau2_cutCosTheta" ]->Sumw2();
		histos1D_[ "jet2Tau3_cutCosTheta" ] = fs_->make< TH1D >( "jet2Tau3_cutCosTheta", "jet2Tau3_cutCosTheta", 20, 0., 1. );
		histos1D_[ "jet2Tau3_cutCosTheta" ]->Sumw2();
		histos1D_[ "jet2Tau21_cutCosTheta" ] = fs_->make< TH1D >( "jet2Tau21_cutCosTheta", "jet2Tau21_cutCosTheta", 20, 0., 1. );
		histos1D_[ "jet2Tau21_cutCosTheta" ]->Sumw2();
		histos1D_[ "jet2Tau31_cutCosTheta" ] = fs_->make< TH1D >( "jet2Tau31_cutCosTheta", "jet2Tau31_cutCosTheta", 20, 0., 1. );
		histos1D_[ "jet2Tau31_cutCosTheta" ]->Sumw2();
		histos1D_[ "jet2Tau32_cutCosTheta" ] = fs_->make< TH1D >( "jet2Tau32_cutCosTheta", "jet2Tau32_cutCosTheta", 20, 0., 1. );
		histos1D_[ "jet2Tau32_cutCosTheta" ]->Sumw2();
		histos1D_[ "deltaEtaDijet_cutCosTheta" ] = fs_->make< TH1D >( "deltaEtaDijet_cutCosTheta", "deltaEtaDijet_cutCosTheta", 50, 0., 5. );
		histos1D_[ "deltaEtaDijet_cutCosTheta" ]->Sumw2();
		histos1D_[ "jet1SubjetPtRatio_cutCosTheta" ] = fs_->make< TH1D >( "jet1SubjetPtRatio_cutCosTheta", "jet1SubjetPtRatio_cutCosTheta", 20, 0, 1.);
		histos1D_[ "jet1SubjetPtRatio_cutCosTheta" ]->Sumw2();
		histos1D_[ "jet2SubjetPtRatio_cutCosTheta" ] = fs_->make< TH1D >( "jet2SubjetPtRatio_cutCosTheta", "jet2SubjetPtRatio_cutCosTheta", 20, 0., 1. );
		histos1D_[ "jet2SubjetPtRatio_cutCosTheta" ]->Sumw2();
		histos1D_[ "subjetPtRatio_cutCosTheta" ] = fs_->make< TH1D >( "subjetPtRatio_cutCosTheta", "subjetPtRatio_cutCosTheta", 20, 0., 1. );
		histos1D_[ "subjetPtRatio_cutCosTheta" ]->Sumw2();

		histos2D_[ "jetTrimmedMassHT_cutCosTheta" ] = fs_->make< TH2D >( "jetTrimmedMassHT_cutCosTheta", "jetTrimmedMassHT_cutCosTheta", 30, 0., 300., 500, 0., 5000. );
		histos2D_[ "jetTrimmedMassHT_cutCosTheta" ]->Sumw2();
		histos2D_[ "leadMassHT_cutCosTheta" ] = fs_->make< TH2D >( "leadMassHT_cutCosTheta", "leadMassHT_cutCosTheta", 30, 0., 300., 500, 0., 5000. );
		histos2D_[ "leadMassHT_cutCosTheta" ]->Sumw2();
		histos2D_[ "massAveHT_cutCosTheta" ] = fs_->make< TH2D >( "massAveHT_cutCosTheta", "massAveHT_cutCosTheta", 30, 0., 300., 500, 0., 5000. );
		histos2D_[ "massAveHT_cutCosTheta" ]->Sumw2();

		histos2D_[ "massAvevsJet1Mass_cutCosTheta" ] = fs_->make< TH2D >( "massAvevsJet1Mass_cutCosTheta", "massAvevsJet1Mass_cutCosTheta", 60, 0., 600., 30, 0., 300. );
		histos2D_[ "massAvevsJet1Mass_cutCosTheta" ]->Sumw2();
		histos2D_[ "massAvevsJet2Mass_cutCosTheta" ] = fs_->make< TH2D >( "massAvevsJet2Mass_cutCosTheta", "massAvevsJet2Mass_cutCosTheta", 60, 0., 600., 30, 0., 300. );
		histos2D_[ "massAvevsJet2Mass_cutCosTheta" ]->Sumw2();
		histos2D_[ "massAvevsMassAsym_cutCosTheta" ] = fs_->make< TH2D >( "massAvevsMassAsym_cutCosTheta", "massAvevsMassAsym_cutCosTheta", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsMassAsym_cutCosTheta" ]->Sumw2();
		histos2D_[ "massAvevsDEta_cutCosTheta" ] = fs_->make< TH2D >( "massAvevsDEta_cutCosTheta", "massAvevsDEta_cutCosTheta", 60, 0., 600., 50, 0., 5. );
		histos2D_[ "massAvevsDEta_cutCosTheta" ]->Sumw2();
		histos2D_[ "massAvevsCosThetaStar_cutCosTheta" ] = fs_->make< TH2D >( "massAvevsCosThetaStar_cutCosTheta", "massAvevsCosThetaStar_cutCosTheta", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsCosThetaStar_cutCosTheta" ]->Sumw2();
		histos2D_[ "massAvevsJet1Tau21_cutCosTheta" ] = fs_->make< TH2D >( "massAvevsJet1Tau21_cutCosTheta", "massAvevsJet1Tau21_cutCosTheta", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1Tau21_cutCosTheta" ]->Sumw2();
		histos2D_[ "massAvevsJet1Tau31_cutCosTheta" ] = fs_->make< TH2D >( "massAvevsJet1Tau31_cutCosTheta", "massAvevsJet1Tau31_cutCosTheta", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1Tau31_cutCosTheta" ]->Sumw2();
		histos2D_[ "massAvevsJet1Tau32_cutCosTheta" ] = fs_->make< TH2D >( "massAvevsJet1Tau32_cutCosTheta", "massAvevsJet1Tau32_cutCosTheta", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1Tau32_cutCosTheta" ]->Sumw2();
		histos2D_[ "massAvevsJet2Tau21_cutCosTheta" ] = fs_->make< TH2D >( "massAvevsJet2Tau21_cutCosTheta", "massAvevsJet2Tau21_cutCosTheta", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2Tau21_cutCosTheta" ]->Sumw2();
		histos2D_[ "massAvevsJet2Tau31_cutCosTheta" ] = fs_->make< TH2D >( "massAvevsJet2Tau31_cutCosTheta", "massAvevsJet2Tau31_cutCosTheta", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2Tau31_cutCosTheta" ]->Sumw2();
		histos2D_[ "massAvevsJet2Tau32_cutCosTheta" ] = fs_->make< TH2D >( "massAvevsJet2Tau32_cutCosTheta", "massAvevsJet2Tau32_cutCosTheta", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2Tau32_cutCosTheta" ]->Sumw2();
		histos2D_[ "massAvevsJet1SubjetPtRatio_cutCosTheta" ] = fs_->make< TH2D >( "massAvevsJet1SubjetPtRatio_cutCosTheta", "massAvevsJet1SubjetPtRatio_cutCosTheta", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1SubjetPtRatio_cutCosTheta" ]->Sumw2();
		histos2D_[ "massAvevsJet2SubjetPtRatio_cutCosTheta" ] = fs_->make< TH2D >( "massAvevsJet2SubjetPtRatio_cutCosTheta", "massAvevsJet2SubjetPtRatio_cutCosTheta", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2SubjetPtRatio_cutCosTheta" ]->Sumw2();
		histos2D_[ "jet1vs2Mass_cutCosTheta" ] = fs_->make< TH2D >( "jet1vs2Mass_cutCosTheta", "jet1vs2Mass_cutCosTheta", 60, 0., 600., 30, 0., 300. );
		histos2D_[ "jet1vs2Mass_cutCosTheta" ]->Sumw2();
		histos2D_[ "dijetCorr_cutCosTheta" ] = fs_->make< TH2D >( "dijetCorr_cutCosTheta", "dijetCorr_cutCosTheta", 56, -3.5, 3.5, 56, -3.5, 3.5 );
		histos2D_[ "dijetCorr_cutCosTheta" ]->Sumw2();
		histos2D_[ "dijetCorrPhi_cutCosTheta" ] = fs_->make< TH2D >( "dijetCorrPhi_cutCosTheta", "dijetCorrPhi_cutCosTheta", 56, -3.5, 3.5, 56, -3.5, 3.5 );
		histos2D_[ "dijetCorrPhi_cutCosTheta" ]->Sumw2();



		histos1D_[ "HT_cutDEta" ] = fs_->make< TH1D >( "HT_cutDEta", "HT_cutDEta", 500, 0., 5000. );
		histos1D_[ "HT_cutDEta" ]->Sumw2();
		histos1D_[ "NPV_cutDEta" ] = fs_->make< TH1D >( "NPV_cutDEta", "NPV_cutDEta", 80, 0., 80. );
		histos1D_[ "NPV_cutDEta" ]->Sumw2();
		histos1D_[ "jetNum_cutDEta" ] = fs_->make< TH1D >( "jetNum_cutDEta", "jetNum_cutDEta", 10, 0., 10. );
		histos1D_[ "jetNum_cutDEta" ]->Sumw2();
		histos1D_[ "jet1Pt_cutDEta" ] = fs_->make< TH1D >( "jet1Pt_cutDEta", "jet1Pt_cutDEta", 100, 0., 1000. );
		histos1D_[ "jet1Pt_cutDEta" ]->Sumw2();
		histos1D_[ "jet1Eta_cutDEta" ] = fs_->make< TH1D >( "jet1Eta_cutDEta", "jet1Eta_cutDEta", 100, -5., 5. );
		histos1D_[ "jet1Eta_cutDEta" ]->Sumw2();
		histos1D_[ "jet1Mass_cutDEta" ] = fs_->make< TH1D >( "jet1Mass_cutDEta", "jet1Mass_cutDEta", 60, 0., 600. );
		histos1D_[ "jet1Mass_cutDEta" ]->Sumw2();
		histos1D_[ "jet2Pt_cutDEta" ] = fs_->make< TH1D >( "jet2Pt_cutDEta", "jet2Pt_cutDEta", 100, 0., 1000. );
		histos1D_[ "jet2Pt_cutDEta" ]->Sumw2();
		histos1D_[ "jet2Eta_cutDEta" ] = fs_->make< TH1D >( "jet2Eta_cutDEta", "jet2Eta_cutDEta", 100, -5., 5. );
		histos1D_[ "jet2Eta_cutDEta" ]->Sumw2();
		histos1D_[ "jet2Mass_cutDEta" ] = fs_->make< TH1D >( "jet2Mass_cutDEta", "jet2Mass_cutDEta", 60, 0., 600. );
		histos1D_[ "jet2Mass_cutDEta" ]->Sumw2();

		histos1D_[ "massAsymmetry_cutDEta" ] = fs_->make< TH1D >( "massAsymmetry_cutDEta", "massAsymmetry_cutDEta", 20, 0., 1. );
		histos1D_[ "massAsymmetry_cutDEta" ]->Sumw2();
		histos1D_[ "massAve_cutDEta" ] = fs_->make< TH1D >( "massAve_cutDEta", "massAve_cutDEta", 60, 0., 600. );
		histos1D_[ "massAve_cutDEta" ]->Sumw2();
		histos1D_[ "massAve_cutDEta_1GeVBin" ] = fs_->make< TH1D >( "massAve_cutDEta_1GeVBin", "massAve_cutDEta_1GeVBin", 600, 0., 600. );
		histos1D_[ "massAve_cutDEta_1GeVBin" ]->Sumw2();
		histos1D_[ "cosThetaStar_cutDEta" ] = fs_->make< TH1D >( "cosThetaStar_cutDEta", "cosThetaStar_cutDEta", 20, 0., 1. );
		histos1D_[ "cosThetaStar_cutDEta" ]->Sumw2();
		histos1D_[ "jet1Tau1_cutDEta" ] = fs_->make< TH1D >( "jet1Tau1_cutDEta", "jet1Tau1_cutDEta", 20, 0., 1. );
		histos1D_[ "jet1Tau1_cutDEta" ]->Sumw2();
		histos1D_[ "jet1Tau2_cutDEta" ] = fs_->make< TH1D >( "jet1Tau2_cutDEta", "jet1Tau2_cutDEta", 20, 0., 1. );
		histos1D_[ "jet1Tau2_cutDEta" ]->Sumw2();
		histos1D_[ "jet1Tau3_cutDEta" ] = fs_->make< TH1D >( "jet1Tau3_cutDEta", "jet1Tau3_cutDEta", 20, 0., 1. );
		histos1D_[ "jet1Tau3_cutDEta" ]->Sumw2();
		histos1D_[ "jet1Tau21_cutDEta" ] = fs_->make< TH1D >( "jet1Tau21_cutDEta", "jet1Tau21_cutDEta", 20, 0., 1. );
		histos1D_[ "jet1Tau21_cutDEta" ]->Sumw2();
		histos1D_[ "jet1Tau31_cutDEta" ] = fs_->make< TH1D >( "jet1Tau31_cutDEta", "jet1Tau31_cutDEta", 20, 0., 1. );
		histos1D_[ "jet1Tau31_cutDEta" ]->Sumw2();
		histos1D_[ "jet1Tau32_cutDEta" ] = fs_->make< TH1D >( "jet1Tau32_cutDEta", "jet1Tau32_cutDEta", 20, 0., 1. );
		histos1D_[ "jet1Tau32_cutDEta" ]->Sumw2();
		histos1D_[ "jet2Tau1_cutDEta" ] = fs_->make< TH1D >( "jet2Tau1_cutDEta", "jet2Tau1_cutDEta", 20, 0., 1. );
		histos1D_[ "jet2Tau1_cutDEta" ]->Sumw2();
		histos1D_[ "jet2Tau2_cutDEta" ] = fs_->make< TH1D >( "jet2Tau2_cutDEta", "jet2Tau2_cutDEta", 20, 0., 1. );
		histos1D_[ "jet2Tau2_cutDEta" ]->Sumw2();
		histos1D_[ "jet2Tau3_cutDEta" ] = fs_->make< TH1D >( "jet2Tau3_cutDEta", "jet2Tau3_cutDEta", 20, 0., 1. );
		histos1D_[ "jet2Tau3_cutDEta" ]->Sumw2();
		histos1D_[ "jet2Tau21_cutDEta" ] = fs_->make< TH1D >( "jet2Tau21_cutDEta", "jet2Tau21_cutDEta", 20, 0., 1. );
		histos1D_[ "jet2Tau21_cutDEta" ]->Sumw2();
		histos1D_[ "jet2Tau31_cutDEta" ] = fs_->make< TH1D >( "jet2Tau31_cutDEta", "jet2Tau31_cutDEta", 20, 0., 1. );
		histos1D_[ "jet2Tau31_cutDEta" ]->Sumw2();
		histos1D_[ "jet2Tau32_cutDEta" ] = fs_->make< TH1D >( "jet2Tau32_cutDEta", "jet2Tau32_cutDEta", 20, 0., 1. );
		histos1D_[ "jet2Tau32_cutDEta" ]->Sumw2();
		histos1D_[ "deltaEtaDijet_cutDEta" ] = fs_->make< TH1D >( "deltaEtaDijet_cutDEta", "deltaEtaDijet_cutDEta", 50, 0., 5. );
		histos1D_[ "deltaEtaDijet_cutDEta" ]->Sumw2();
		histos1D_[ "jet1SubjetPtRatio_cutDEta" ] = fs_->make< TH1D >( "jet1SubjetPtRatio_cutDEta", "jet1SubjetPtRatio_cutDEta", 20, 0, 1.);
		histos1D_[ "jet1SubjetPtRatio_cutDEta" ]->Sumw2();
		histos1D_[ "jet2SubjetPtRatio_cutDEta" ] = fs_->make< TH1D >( "jet2SubjetPtRatio_cutDEta", "jet2SubjetPtRatio_cutDEta", 20, 0., 1. );
		histos1D_[ "jet2SubjetPtRatio_cutDEta" ]->Sumw2();
		histos1D_[ "subjetPtRatio_cutDEta" ] = fs_->make< TH1D >( "subjetPtRatio_cutDEta", "subjetPtRatio_cutDEta", 20, 0., 1. );
		histos1D_[ "subjetPtRatio_cutDEta" ]->Sumw2();

		histos2D_[ "jetTrimmedMassHT_cutDEta" ] = fs_->make< TH2D >( "jetTrimmedMassHT_cutDEta", "jetTrimmedMassHT_cutDEta", 30, 0., 300., 500, 0., 5000. );
		histos2D_[ "jetTrimmedMassHT_cutDEta" ]->Sumw2();
		histos2D_[ "leadMassHT_cutDEta" ] = fs_->make< TH2D >( "leadMassHT_cutDEta", "leadMassHT_cutDEta", 30, 0., 300., 500, 0., 5000. );
		histos2D_[ "leadMassHT_cutDEta" ]->Sumw2();
		histos2D_[ "massAveHT_cutDEta" ] = fs_->make< TH2D >( "massAveHT_cutDEta", "massAveHT_cutDEta", 30, 0., 300., 500, 0., 5000. );
		histos2D_[ "massAveHT_cutDEta" ]->Sumw2();

		histos2D_[ "massAvevsJet1Mass_cutDEta" ] = fs_->make< TH2D >( "massAvevsJet1Mass_cutDEta", "massAvevsJet1Mass_cutDEta", 60, 0., 600., 30, 0., 300. );
		histos2D_[ "massAvevsJet1Mass_cutDEta" ]->Sumw2();
		histos2D_[ "massAvevsJet2Mass_cutDEta" ] = fs_->make< TH2D >( "massAvevsJet2Mass_cutDEta", "massAvevsJet2Mass_cutDEta", 60, 0., 600., 30, 0., 300. );
		histos2D_[ "massAvevsJet2Mass_cutDEta" ]->Sumw2();
		histos2D_[ "massAvevsMassAsym_cutDEta" ] = fs_->make< TH2D >( "massAvevsMassAsym_cutDEta", "massAvevsMassAsym_cutDEta", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsMassAsym_cutDEta" ]->Sumw2();
		histos2D_[ "massAvevsDEta_cutDEta" ] = fs_->make< TH2D >( "massAvevsDEta_cutDEta", "massAvevsDEta_cutDEta", 60, 0., 600., 50, 0., 5. );
		histos2D_[ "massAvevsDEta_cutDEta" ]->Sumw2();
		histos2D_[ "massAvevsCosThetaStar_cutDEta" ] = fs_->make< TH2D >( "massAvevsCosThetaStar_cutDEta", "massAvevsCosThetaStar_cutDEta", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsCosThetaStar_cutDEta" ]->Sumw2();
		histos2D_[ "massAvevsJet1Tau21_cutDEta" ] = fs_->make< TH2D >( "massAvevsJet1Tau21_cutDEta", "massAvevsJet1Tau21_cutDEta", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1Tau21_cutDEta" ]->Sumw2();
		histos2D_[ "massAvevsJet1Tau31_cutDEta" ] = fs_->make< TH2D >( "massAvevsJet1Tau31_cutDEta", "massAvevsJet1Tau31_cutDEta", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1Tau31_cutDEta" ]->Sumw2();
		histos2D_[ "massAvevsJet1Tau32_cutDEta" ] = fs_->make< TH2D >( "massAvevsJet1Tau32_cutDEta", "massAvevsJet1Tau32_cutDEta", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1Tau32_cutDEta" ]->Sumw2();
		histos2D_[ "massAvevsJet2Tau21_cutDEta" ] = fs_->make< TH2D >( "massAvevsJet2Tau21_cutDEta", "massAvevsJet2Tau21_cutDEta", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2Tau21_cutDEta" ]->Sumw2();
		histos2D_[ "massAvevsJet2Tau31_cutDEta" ] = fs_->make< TH2D >( "massAvevsJet2Tau31_cutDEta", "massAvevsJet2Tau31_cutDEta", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2Tau31_cutDEta" ]->Sumw2();
		histos2D_[ "massAvevsJet2Tau32_cutDEta" ] = fs_->make< TH2D >( "massAvevsJet2Tau32_cutDEta", "massAvevsJet2Tau32_cutDEta", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2Tau32_cutDEta" ]->Sumw2();
		histos2D_[ "massAvevsJet1SubjetPtRatio_cutDEta" ] = fs_->make< TH2D >( "massAvevsJet1SubjetPtRatio_cutDEta", "massAvevsJet1SubjetPtRatio_cutDEta", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1SubjetPtRatio_cutDEta" ]->Sumw2();
		histos2D_[ "massAvevsJet2SubjetPtRatio_cutDEta" ] = fs_->make< TH2D >( "massAvevsJet2SubjetPtRatio_cutDEta", "massAvevsJet2SubjetPtRatio_cutDEta", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2SubjetPtRatio_cutDEta" ]->Sumw2();
		histos2D_[ "jet1vs2Mass_cutDEta" ] = fs_->make< TH2D >( "jet1vs2Mass_cutDEta", "jet1vs2Mass_cutDEta", 60, 0., 600., 30, 0., 300. );
		histos2D_[ "jet1vs2Mass_cutDEta" ]->Sumw2();
		histos2D_[ "dijetCorr_cutDEta" ] = fs_->make< TH2D >( "dijetCorr_cutDEta", "dijetCorr_cutDEta", 56, -3.5, 3.5, 56, -3.5, 3.5 );
		histos2D_[ "dijetCorr_cutDEta" ]->Sumw2();
		histos2D_[ "dijetCorrPhi_cutDEta" ] = fs_->make< TH2D >( "dijetCorrPhi_cutDEta", "dijetCorrPhi_cutDEta", 56, -3.5, 3.5, 56, -3.5, 3.5 );
		histos2D_[ "dijetCorrPhi_cutDEta" ]->Sumw2();



		histos1D_[ "HT_cutBtag" ] = fs_->make< TH1D >( "HT_cutBtag", "HT_cutBtag", 500, 0., 5000. );
		histos1D_[ "HT_cutBtag" ]->Sumw2();
		histos1D_[ "NPV_cutBtag" ] = fs_->make< TH1D >( "NPV_cutBtag", "NPV_cutBtag", 80, 0., 80. );
		histos1D_[ "NPV_cutBtag" ]->Sumw2();
		histos1D_[ "jetNum_cutBtag" ] = fs_->make< TH1D >( "jetNum_cutBtag", "jetNum_cutBtag", 10, 0., 10. );
		histos1D_[ "jetNum_cutBtag" ]->Sumw2();
		histos1D_[ "jet1Pt_cutBtag" ] = fs_->make< TH1D >( "jet1Pt_cutBtag", "jet1Pt_cutBtag", 100, 0., 1000. );
		histos1D_[ "jet1Pt_cutBtag" ]->Sumw2();
		histos1D_[ "jet1Eta_cutBtag" ] = fs_->make< TH1D >( "jet1Eta_cutBtag", "jet1Eta_cutBtag", 100, -5., 5. );
		histos1D_[ "jet1Eta_cutBtag" ]->Sumw2();
		histos1D_[ "jet1Mass_cutBtag" ] = fs_->make< TH1D >( "jet1Mass_cutBtag", "jet1Mass_cutBtag", 60, 0., 600. );
		histos1D_[ "jet1Mass_cutBtag" ]->Sumw2();
		histos1D_[ "jet2Pt_cutBtag" ] = fs_->make< TH1D >( "jet2Pt_cutBtag", "jet2Pt_cutBtag", 100, 0., 1000. );
		histos1D_[ "jet2Pt_cutBtag" ]->Sumw2();
		histos1D_[ "jet2Eta_cutBtag" ] = fs_->make< TH1D >( "jet2Eta_cutBtag", "jet2Eta_cutBtag", 100, -5., 5. );
		histos1D_[ "jet2Eta_cutBtag" ]->Sumw2();
		histos1D_[ "jet2Mass_cutBtag" ] = fs_->make< TH1D >( "jet2Mass_cutBtag", "jet2Mass_cutBtag", 60, 0., 600. );
		histos1D_[ "jet2Mass_cutBtag" ]->Sumw2();

		histos1D_[ "massAsymmetry_cutBtag" ] = fs_->make< TH1D >( "massAsymmetry_cutBtag", "massAsymmetry_cutBtag", 20, 0., 1. );
		histos1D_[ "massAsymmetry_cutBtag" ]->Sumw2();
		histos1D_[ "massAve_cutBtag" ] = fs_->make< TH1D >( "massAve_cutBtag", "massAve_cutBtag", 60, 0., 600. );
		histos1D_[ "massAve_cutBtag" ]->Sumw2();
		histos1D_[ "cosThetaStar_cutBtag" ] = fs_->make< TH1D >( "cosThetaStar_cutBtag", "cosThetaStar_cutBtag", 20, 0., 1. );
		histos1D_[ "cosThetaStar_cutBtag" ]->Sumw2();
		histos1D_[ "jet1Tau1_cutBtag" ] = fs_->make< TH1D >( "jet1Tau1_cutBtag", "jet1Tau1_cutBtag", 20, 0., 1. );
		histos1D_[ "jet1Tau1_cutBtag" ]->Sumw2();
		histos1D_[ "jet1Tau2_cutBtag" ] = fs_->make< TH1D >( "jet1Tau2_cutBtag", "jet1Tau2_cutBtag", 20, 0., 1. );
		histos1D_[ "jet1Tau2_cutBtag" ]->Sumw2();
		histos1D_[ "jet1Tau3_cutBtag" ] = fs_->make< TH1D >( "jet1Tau3_cutBtag", "jet1Tau3_cutBtag", 20, 0., 1. );
		histos1D_[ "jet1Tau3_cutBtag" ]->Sumw2();
		histos1D_[ "jet1Tau21_cutBtag" ] = fs_->make< TH1D >( "jet1Tau21_cutBtag", "jet1Tau21_cutBtag", 20, 0., 1. );
		histos1D_[ "jet1Tau21_cutBtag" ]->Sumw2();
		histos1D_[ "jet1Tau31_cutBtag" ] = fs_->make< TH1D >( "jet1Tau31_cutBtag", "jet1Tau31_cutBtag", 20, 0., 1. );
		histos1D_[ "jet1Tau31_cutBtag" ]->Sumw2();
		histos1D_[ "jet1Tau32_cutBtag" ] = fs_->make< TH1D >( "jet1Tau32_cutBtag", "jet1Tau32_cutBtag", 20, 0., 1. );
		histos1D_[ "jet1Tau32_cutBtag" ]->Sumw2();
		histos1D_[ "jet2Tau1_cutBtag" ] = fs_->make< TH1D >( "jet2Tau1_cutBtag", "jet2Tau1_cutBtag", 20, 0., 1. );
		histos1D_[ "jet2Tau1_cutBtag" ]->Sumw2();
		histos1D_[ "jet2Tau2_cutBtag" ] = fs_->make< TH1D >( "jet2Tau2_cutBtag", "jet2Tau2_cutBtag", 20, 0., 1. );
		histos1D_[ "jet2Tau2_cutBtag" ]->Sumw2();
		histos1D_[ "jet2Tau3_cutBtag" ] = fs_->make< TH1D >( "jet2Tau3_cutBtag", "jet2Tau3_cutBtag", 20, 0., 1. );
		histos1D_[ "jet2Tau3_cutBtag" ]->Sumw2();
		histos1D_[ "jet2Tau21_cutBtag" ] = fs_->make< TH1D >( "jet2Tau21_cutBtag", "jet2Tau21_cutBtag", 20, 0., 1. );
		histos1D_[ "jet2Tau21_cutBtag" ]->Sumw2();
		histos1D_[ "jet2Tau31_cutBtag" ] = fs_->make< TH1D >( "jet2Tau31_cutBtag", "jet2Tau31_cutBtag", 20, 0., 1. );
		histos1D_[ "jet2Tau31_cutBtag" ]->Sumw2();
		histos1D_[ "jet2Tau32_cutBtag" ] = fs_->make< TH1D >( "jet2Tau32_cutBtag", "jet2Tau32_cutBtag", 20, 0., 1. );
		histos1D_[ "jet2Tau32_cutBtag" ]->Sumw2();
		histos1D_[ "deltaEtaDijet_cutBtag" ] = fs_->make< TH1D >( "deltaEtaDijet_cutBtag", "deltaEtaDijet_cutBtag", 50, 0., 5. );
		histos1D_[ "deltaEtaDijet_cutBtag" ]->Sumw2();
		histos1D_[ "jet1SubjetPtRatio_cutBtag" ] = fs_->make< TH1D >( "jet1SubjetPtRatio_cutBtag", "jet1SubjetPtRatio_cutBtag", 20, 0, 1.);
		histos1D_[ "jet1SubjetPtRatio_cutBtag" ]->Sumw2();
		histos1D_[ "jet2SubjetPtRatio_cutBtag" ] = fs_->make< TH1D >( "jet2SubjetPtRatio_cutBtag", "jet2SubjetPtRatio_cutBtag", 20, 0., 1. );
		histos1D_[ "jet2SubjetPtRatio_cutBtag" ]->Sumw2();
		histos1D_[ "subjetPtRatio_cutBtag" ] = fs_->make< TH1D >( "subjetPtRatio_cutBtag", "subjetPtRatio_cutBtag", 20, 0., 1. );
		histos1D_[ "subjetPtRatio_cutBtag" ]->Sumw2();

		histos2D_[ "jetTrimmedMassHT_cutBtag" ] = fs_->make< TH2D >( "jetTrimmedMassHT_cutBtag", "jetTrimmedMassHT_cutBtag", 30, 0., 300., 500, 0., 5000. );
		histos2D_[ "jetTrimmedMassHT_cutBtag" ]->Sumw2();
		histos2D_[ "leadMassHT_cutBtag" ] = fs_->make< TH2D >( "leadMassHT_cutBtag", "leadMassHT_cutBtag", 30, 0., 300., 500, 0., 5000. );
		histos2D_[ "leadMassHT_cutBtag" ]->Sumw2();
		histos2D_[ "massAveHT_cutBtag" ] = fs_->make< TH2D >( "massAveHT_cutBtag", "massAveHT_cutBtag", 30, 0., 300., 500, 0., 5000. );
		histos2D_[ "massAveHT_cutBtag" ]->Sumw2();

		histos2D_[ "massAvevsJet1Mass_cutBtag" ] = fs_->make< TH2D >( "massAvevsJet1Mass_cutBtag", "massAvevsJet1Mass_cutBtag", 60, 0., 600., 30, 0., 300. );
		histos2D_[ "massAvevsJet1Mass_cutBtag" ]->Sumw2();
		histos2D_[ "massAvevsJet2Mass_cutBtag" ] = fs_->make< TH2D >( "massAvevsJet2Mass_cutBtag", "massAvevsJet2Mass_cutBtag", 60, 0., 600., 30, 0., 300. );
		histos2D_[ "massAvevsJet2Mass_cutBtag" ]->Sumw2();
		histos2D_[ "massAvevsMassAsym_cutBtag" ] = fs_->make< TH2D >( "massAvevsMassAsym_cutBtag", "massAvevsMassAsym_cutBtag", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsMassAsym_cutBtag" ]->Sumw2();
		histos2D_[ "massAvevsDEta_cutBtag" ] = fs_->make< TH2D >( "massAvevsDEta_cutBtag", "massAvevsDEta_cutBtag", 60, 0., 600., 50, 0., 5. );
		histos2D_[ "massAvevsDEta_cutBtag" ]->Sumw2();
		histos2D_[ "massAvevsCosThetaStar_cutBtag" ] = fs_->make< TH2D >( "massAvevsCosThetaStar_cutBtag", "massAvevsCosThetaStar_cutBtag", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsCosThetaStar_cutBtag" ]->Sumw2();
		histos2D_[ "massAvevsJet1Tau21_cutBtag" ] = fs_->make< TH2D >( "massAvevsJet1Tau21_cutBtag", "massAvevsJet1Tau21_cutBtag", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1Tau21_cutBtag" ]->Sumw2();
		histos2D_[ "massAvevsJet1Tau31_cutBtag" ] = fs_->make< TH2D >( "massAvevsJet1Tau31_cutBtag", "massAvevsJet1Tau31_cutBtag", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1Tau31_cutBtag" ]->Sumw2();
		histos2D_[ "massAvevsJet1Tau32_cutBtag" ] = fs_->make< TH2D >( "massAvevsJet1Tau32_cutBtag", "massAvevsJet1Tau32_cutBtag", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1Tau32_cutBtag" ]->Sumw2();
		histos2D_[ "massAvevsJet2Tau21_cutBtag" ] = fs_->make< TH2D >( "massAvevsJet2Tau21_cutBtag", "massAvevsJet2Tau21_cutBtag", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2Tau21_cutBtag" ]->Sumw2();
		histos2D_[ "massAvevsJet2Tau31_cutBtag" ] = fs_->make< TH2D >( "massAvevsJet2Tau31_cutBtag", "massAvevsJet2Tau31_cutBtag", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2Tau31_cutBtag" ]->Sumw2();
		histos2D_[ "massAvevsJet2Tau32_cutBtag" ] = fs_->make< TH2D >( "massAvevsJet2Tau32_cutBtag", "massAvevsJet2Tau32_cutBtag", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2Tau32_cutBtag" ]->Sumw2();
		histos2D_[ "massAvevsJet1SubjetPtRatio_cutBtag" ] = fs_->make< TH2D >( "massAvevsJet1SubjetPtRatio_cutBtag", "massAvevsJet1SubjetPtRatio_cutBtag", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1SubjetPtRatio_cutBtag" ]->Sumw2();
		histos2D_[ "massAvevsJet2SubjetPtRatio_cutBtag" ] = fs_->make< TH2D >( "massAvevsJet2SubjetPtRatio_cutBtag", "massAvevsJet2SubjetPtRatio_cutBtag", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2SubjetPtRatio_cutBtag" ]->Sumw2();
		histos2D_[ "jet1vs2Mass_cutBtag" ] = fs_->make< TH2D >( "jet1vs2Mass_cutBtag", "jet1vs2Mass_cutBtag", 60, 0., 600., 30, 0., 300. );
		histos2D_[ "jet1vs2Mass_cutBtag" ]->Sumw2();
		histos2D_[ "dijetCorr_cutBtag" ] = fs_->make< TH2D >( "dijetCorr_cutBtag", "dijetCorr_cutBtag", 56, -3.5, 3.5, 56, -3.5, 3.5 );
		histos2D_[ "dijetCorr_cutBtag" ]->Sumw2();
		histos2D_[ "dijetCorrPhi_cutBtag" ] = fs_->make< TH2D >( "dijetCorrPhi_cutBtag", "dijetCorrPhi_cutBtag", 56, -3.5, 3.5, 56, -3.5, 3.5 );
		histos2D_[ "dijetCorrPhi_cutBtag" ]->Sumw2();


		histos1D_[ "HT_cutNOMassAsym" ] = fs_->make< TH1D >( "HT_cutNOMassAsym", "HT_cutNOMassAsym", 500, 0., 5000. );
		histos1D_[ "HT_cutNOMassAsym" ]->Sumw2();
		histos1D_[ "NPV_cutNOMassAsym" ] = fs_->make< TH1D >( "NPV_cutNOMassAsym", "NPV_cutNOMassAsym", 80, 0., 80. );
		histos1D_[ "NPV_cutNOMassAsym" ]->Sumw2();
		histos1D_[ "jetNum_cutNOMassAsym" ] = fs_->make< TH1D >( "jetNum_cutNOMassAsym", "jetNum_cutNOMassAsym", 10, 0., 10. );
		histos1D_[ "jetNum_cutNOMassAsym" ]->Sumw2();
		histos1D_[ "jet1Pt_cutNOMassAsym" ] = fs_->make< TH1D >( "jet1Pt_cutNOMassAsym", "jet1Pt_cutNOMassAsym", 100, 0., 1000. );
		histos1D_[ "jet1Pt_cutNOMassAsym" ]->Sumw2();
		histos1D_[ "jet1Eta_cutNOMassAsym" ] = fs_->make< TH1D >( "jet1Eta_cutNOMassAsym", "jet1Eta_cutNOMassAsym", 100, -5., 5. );
		histos1D_[ "jet1Eta_cutNOMassAsym" ]->Sumw2();
		histos1D_[ "jet1Mass_cutNOMassAsym" ] = fs_->make< TH1D >( "jet1Mass_cutNOMassAsym", "jet1Mass_cutNOMassAsym", 60, 0., 600. );
		histos1D_[ "jet1Mass_cutNOMassAsym" ]->Sumw2();
		histos1D_[ "jet2Pt_cutNOMassAsym" ] = fs_->make< TH1D >( "jet2Pt_cutNOMassAsym", "jet2Pt_cutNOMassAsym", 100, 0., 1000. );
		histos1D_[ "jet2Pt_cutNOMassAsym" ]->Sumw2();
		histos1D_[ "jet2Eta_cutNOMassAsym" ] = fs_->make< TH1D >( "jet2Eta_cutNOMassAsym", "jet2Eta_cutNOMassAsym", 100, -5., 5. );
		histos1D_[ "jet2Eta_cutNOMassAsym" ]->Sumw2();
		histos1D_[ "jet2Mass_cutNOMassAsym" ] = fs_->make< TH1D >( "jet2Mass_cutNOMassAsym", "jet2Mass_cutNOMassAsym", 60, 0., 600. );
		histos1D_[ "jet2Mass_cutNOMassAsym" ]->Sumw2();

		histos1D_[ "massAsymmetry_cutNOMassAsym" ] = fs_->make< TH1D >( "massAsymmetry_cutNOMassAsym", "massAsymmetry_cutNOMassAsym", 20, 0., 1. );
		histos1D_[ "massAsymmetry_cutNOMassAsym" ]->Sumw2();
		histos1D_[ "massAve_cutNOMassAsym" ] = fs_->make< TH1D >( "massAve_cutNOMassAsym", "massAve_cutNOMassAsym", 60, 0., 600. );
		histos1D_[ "massAve_cutNOMassAsym" ]->Sumw2();
		histos1D_[ "cosThetaStar_cutNOMassAsym" ] = fs_->make< TH1D >( "cosThetaStar_cutNOMassAsym", "cosThetaStar_cutNOMassAsym", 20, 0., 1. );
		histos1D_[ "cosThetaStar_cutNOMassAsym" ]->Sumw2();
		histos1D_[ "jet1Tau1_cutNOMassAsym" ] = fs_->make< TH1D >( "jet1Tau1_cutNOMassAsym", "jet1Tau1_cutNOMassAsym", 20, 0., 1. );
		histos1D_[ "jet1Tau1_cutNOMassAsym" ]->Sumw2();
		histos1D_[ "jet1Tau2_cutNOMassAsym" ] = fs_->make< TH1D >( "jet1Tau2_cutNOMassAsym", "jet1Tau2_cutNOMassAsym", 20, 0., 1. );
		histos1D_[ "jet1Tau2_cutNOMassAsym" ]->Sumw2();
		histos1D_[ "jet1Tau3_cutNOMassAsym" ] = fs_->make< TH1D >( "jet1Tau3_cutNOMassAsym", "jet1Tau3_cutNOMassAsym", 20, 0., 1. );
		histos1D_[ "jet1Tau3_cutNOMassAsym" ]->Sumw2();
		histos1D_[ "jet1Tau21_cutNOMassAsym" ] = fs_->make< TH1D >( "jet1Tau21_cutNOMassAsym", "jet1Tau21_cutNOMassAsym", 20, 0., 1. );
		histos1D_[ "jet1Tau21_cutNOMassAsym" ]->Sumw2();
		histos1D_[ "jet1Tau31_cutNOMassAsym" ] = fs_->make< TH1D >( "jet1Tau31_cutNOMassAsym", "jet1Tau31_cutNOMassAsym", 20, 0., 1. );
		histos1D_[ "jet1Tau31_cutNOMassAsym" ]->Sumw2();
		histos1D_[ "jet1Tau32_cutNOMassAsym" ] = fs_->make< TH1D >( "jet1Tau32_cutNOMassAsym", "jet1Tau32_cutNOMassAsym", 20, 0., 1. );
		histos1D_[ "jet1Tau32_cutNOMassAsym" ]->Sumw2();
		histos1D_[ "jet2Tau1_cutNOMassAsym" ] = fs_->make< TH1D >( "jet2Tau1_cutNOMassAsym", "jet2Tau1_cutNOMassAsym", 20, 0., 1. );
		histos1D_[ "jet2Tau1_cutNOMassAsym" ]->Sumw2();
		histos1D_[ "jet2Tau2_cutNOMassAsym" ] = fs_->make< TH1D >( "jet2Tau2_cutNOMassAsym", "jet2Tau2_cutNOMassAsym", 20, 0., 1. );
		histos1D_[ "jet2Tau2_cutNOMassAsym" ]->Sumw2();
		histos1D_[ "jet2Tau3_cutNOMassAsym" ] = fs_->make< TH1D >( "jet2Tau3_cutNOMassAsym", "jet2Tau3_cutNOMassAsym", 20, 0., 1. );
		histos1D_[ "jet2Tau3_cutNOMassAsym" ]->Sumw2();
		histos1D_[ "jet2Tau21_cutNOMassAsym" ] = fs_->make< TH1D >( "jet2Tau21_cutNOMassAsym", "jet2Tau21_cutNOMassAsym", 20, 0., 1. );
		histos1D_[ "jet2Tau21_cutNOMassAsym" ]->Sumw2();
		histos1D_[ "jet2Tau31_cutNOMassAsym" ] = fs_->make< TH1D >( "jet2Tau31_cutNOMassAsym", "jet2Tau31_cutNOMassAsym", 20, 0., 1. );
		histos1D_[ "jet2Tau31_cutNOMassAsym" ]->Sumw2();
		histos1D_[ "jet2Tau32_cutNOMassAsym" ] = fs_->make< TH1D >( "jet2Tau32_cutNOMassAsym", "jet2Tau32_cutNOMassAsym", 20, 0., 1. );
		histos1D_[ "jet2Tau32_cutNOMassAsym" ]->Sumw2();
		histos1D_[ "deltaEtaDijet_cutNOMassAsym" ] = fs_->make< TH1D >( "deltaEtaDijet_cutNOMassAsym", "deltaEtaDijet_cutNOMassAsym", 50, 0., 5. );
		histos1D_[ "deltaEtaDijet_cutNOMassAsym" ]->Sumw2();
		histos1D_[ "jet1SubjetPtRatio_cutNOMassAsym" ] = fs_->make< TH1D >( "jet1SubjetPtRatio_cutNOMassAsym", "jet1SubjetPtRatio_cutNOMassAsym", 20, 0, 1.);
		histos1D_[ "jet1SubjetPtRatio_cutNOMassAsym" ]->Sumw2();
		histos1D_[ "jet2SubjetPtRatio_cutNOMassAsym" ] = fs_->make< TH1D >( "jet2SubjetPtRatio_cutNOMassAsym", "jet2SubjetPtRatio_cutNOMassAsym", 20, 0., 1. );
		histos1D_[ "jet2SubjetPtRatio_cutNOMassAsym" ]->Sumw2();
		histos1D_[ "subjetPtRatio_cutNOMassAsym" ] = fs_->make< TH1D >( "subjetPtRatio_cutNOMassAsym", "subjetPtRatio_cutNOMassAsym", 20, 0., 1. );
		histos1D_[ "subjetPtRatio_cutNOMassAsym" ]->Sumw2();

		histos2D_[ "jetTrimmedMassHT_cutNOMassAsym" ] = fs_->make< TH2D >( "jetTrimmedMassHT_cutNOMassAsym", "jetTrimmedMassHT_cutNOMassAsym", 30, 0., 300., 500, 0., 5000. );
		histos2D_[ "jetTrimmedMassHT_cutNOMassAsym" ]->Sumw2();
		histos2D_[ "leadMassHT_cutNOMassAsym" ] = fs_->make< TH2D >( "leadMassHT_cutNOMassAsym", "leadMassHT_cutNOMassAsym", 30, 0., 300., 500, 0., 5000. );
		histos2D_[ "leadMassHT_cutNOMassAsym" ]->Sumw2();
		histos2D_[ "massAveHT_cutNOMassAsym" ] = fs_->make< TH2D >( "massAveHT_cutNOMassAsym", "massAveHT_cutNOMassAsym", 30, 0., 300., 500, 0., 5000. );
		histos2D_[ "massAveHT_cutNOMassAsym" ]->Sumw2();

		histos2D_[ "massAvevsJet1Mass_cutNOMassAsym" ] = fs_->make< TH2D >( "massAvevsJet1Mass_cutNOMassAsym", "massAvevsJet1Mass_cutNOMassAsym", 60, 0., 600., 30, 0., 300. );
		histos2D_[ "massAvevsJet1Mass_cutNOMassAsym" ]->Sumw2();
		histos2D_[ "massAvevsJet2Mass_cutNOMassAsym" ] = fs_->make< TH2D >( "massAvevsJet2Mass_cutNOMassAsym", "massAvevsJet2Mass_cutNOMassAsym", 60, 0., 600., 30, 0., 300. );
		histos2D_[ "massAvevsJet2Mass_cutNOMassAsym" ]->Sumw2();
		histos2D_[ "massAvevsMassAsym_cutNOMassAsym" ] = fs_->make< TH2D >( "massAvevsMassAsym_cutNOMassAsym", "massAvevsMassAsym_cutNOMassAsym", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsMassAsym_cutNOMassAsym" ]->Sumw2();
		histos2D_[ "massAvevsDEta_cutNOMassAsym" ] = fs_->make< TH2D >( "massAvevsDEta_cutNOMassAsym", "massAvevsDEta_cutNOMassAsym", 60, 0., 600., 50, 0., 5. );
		histos2D_[ "massAvevsDEta_cutNOMassAsym" ]->Sumw2();
		histos2D_[ "massAvevsCosThetaStar_cutNOMassAsym" ] = fs_->make< TH2D >( "massAvevsCosThetaStar_cutNOMassAsym", "massAvevsCosThetaStar_cutNOMassAsym", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsCosThetaStar_cutNOMassAsym" ]->Sumw2();
		histos2D_[ "massAvevsJet1Tau21_cutNOMassAsym" ] = fs_->make< TH2D >( "massAvevsJet1Tau21_cutNOMassAsym", "massAvevsJet1Tau21_cutNOMassAsym", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1Tau21_cutNOMassAsym" ]->Sumw2();
		histos2D_[ "massAvevsJet1Tau31_cutNOMassAsym" ] = fs_->make< TH2D >( "massAvevsJet1Tau31_cutNOMassAsym", "massAvevsJet1Tau31_cutNOMassAsym", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1Tau31_cutNOMassAsym" ]->Sumw2();
		histos2D_[ "massAvevsJet1Tau32_cutNOMassAsym" ] = fs_->make< TH2D >( "massAvevsJet1Tau32_cutNOMassAsym", "massAvevsJet1Tau32_cutNOMassAsym", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1Tau32_cutNOMassAsym" ]->Sumw2();
		histos2D_[ "massAvevsJet2Tau21_cutNOMassAsym" ] = fs_->make< TH2D >( "massAvevsJet2Tau21_cutNOMassAsym", "massAvevsJet2Tau21_cutNOMassAsym", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2Tau21_cutNOMassAsym" ]->Sumw2();
		histos2D_[ "massAvevsJet2Tau31_cutNOMassAsym" ] = fs_->make< TH2D >( "massAvevsJet2Tau31_cutNOMassAsym", "massAvevsJet2Tau31_cutNOMassAsym", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2Tau31_cutNOMassAsym" ]->Sumw2();
		histos2D_[ "massAvevsJet2Tau32_cutNOMassAsym" ] = fs_->make< TH2D >( "massAvevsJet2Tau32_cutNOMassAsym", "massAvevsJet2Tau32_cutNOMassAsym", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2Tau32_cutNOMassAsym" ]->Sumw2();
		histos2D_[ "massAvevsJet1SubjetPtRatio_cutNOMassAsym" ] = fs_->make< TH2D >( "massAvevsJet1SubjetPtRatio_cutNOMassAsym", "massAvevsJet1SubjetPtRatio_cutNOMassAsym", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1SubjetPtRatio_cutNOMassAsym" ]->Sumw2();
		histos2D_[ "massAvevsJet2SubjetPtRatio_cutNOMassAsym" ] = fs_->make< TH2D >( "massAvevsJet2SubjetPtRatio_cutNOMassAsym", "massAvevsJet2SubjetPtRatio_cutNOMassAsym", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2SubjetPtRatio_cutNOMassAsym" ]->Sumw2();
		histos2D_[ "jet1vs2Mass_cutNOMassAsym" ] = fs_->make< TH2D >( "jet1vs2Mass_cutNOMassAsym", "jet1vs2Mass_cutNOMassAsym", 60, 0., 600., 30, 0., 300. );
		histos2D_[ "jet1vs2Mass_cutNOMassAsym" ]->Sumw2();
		histos2D_[ "dijetCorr_cutNOMassAsym" ] = fs_->make< TH2D >( "dijetCorr_cutNOMassAsym", "dijetCorr_cutNOMassAsym", 56, -3.5, 3.5, 56, -3.5, 3.5 );
		histos2D_[ "dijetCorr_cutNOMassAsym" ]->Sumw2();
		histos2D_[ "dijetCorrPhi_cutNOMassAsym" ] = fs_->make< TH2D >( "dijetCorrPhi_cutNOMassAsym", "dijetCorrPhi_cutNOMassAsym", 56, -3.5, 3.5, 56, -3.5, 3.5 );
		histos2D_[ "dijetCorrPhi_cutNOMassAsym" ]->Sumw2();


		histos1D_[ "HT_cutTau21_NOMA" ] = fs_->make< TH1D >( "HT_cutTau21_NOMA", "HT_cutTau21_NOMA", 500, 0., 5000. );
		histos1D_[ "HT_cutTau21_NOMA" ]->Sumw2();
		histos1D_[ "NPV_cutTau21_NOMA" ] = fs_->make< TH1D >( "NPV_cutTau21_NOMA", "NPV_cutTau21_NOMA", 80, 0., 80. );
		histos1D_[ "NPV_cutTau21_NOMA" ]->Sumw2();
		histos1D_[ "jetNum_cutTau21_NOMA" ] = fs_->make< TH1D >( "jetNum_cutTau21_NOMA", "jetNum_cutTau21_NOMA", 10, 0., 10. );
		histos1D_[ "jetNum_cutTau21_NOMA" ]->Sumw2();
		histos1D_[ "jet1Pt_cutTau21_NOMA" ] = fs_->make< TH1D >( "jet1Pt_cutTau21_NOMA", "jet1Pt_cutTau21_NOMA", 100, 0., 1000. );
		histos1D_[ "jet1Pt_cutTau21_NOMA" ]->Sumw2();
		histos1D_[ "jet1Eta_cutTau21_NOMA" ] = fs_->make< TH1D >( "jet1Eta_cutTau21_NOMA", "jet1Eta_cutTau21_NOMA", 100, -5., 5. );
		histos1D_[ "jet1Eta_cutTau21_NOMA" ]->Sumw2();
		histos1D_[ "jet1Mass_cutTau21_NOMA" ] = fs_->make< TH1D >( "jet1Mass_cutTau21_NOMA", "jet1Mass_cutTau21_NOMA", 60, 0., 600. );
		histos1D_[ "jet1Mass_cutTau21_NOMA" ]->Sumw2();
		histos1D_[ "jet2Pt_cutTau21_NOMA" ] = fs_->make< TH1D >( "jet2Pt_cutTau21_NOMA", "jet2Pt_cutTau21_NOMA", 100, 0., 1000. );
		histos1D_[ "jet2Pt_cutTau21_NOMA" ]->Sumw2();
		histos1D_[ "jet2Eta_cutTau21_NOMA" ] = fs_->make< TH1D >( "jet2Eta_cutTau21_NOMA", "jet2Eta_cutTau21_NOMA", 100, -5., 5. );
		histos1D_[ "jet2Eta_cutTau21_NOMA" ]->Sumw2();
		histos1D_[ "jet2Mass_cutTau21_NOMA" ] = fs_->make< TH1D >( "jet2Mass_cutTau21_NOMA", "jet2Mass_cutTau21_NOMA", 60, 0., 600. );
		histos1D_[ "jet2Mass_cutTau21_NOMA" ]->Sumw2();

		histos1D_[ "massAsymmetry_cutTau21_NOMA" ] = fs_->make< TH1D >( "massAsymmetry_cutTau21_NOMA", "massAsymmetry_cutTau21_NOMA", 20, 0., 1. );
		histos1D_[ "massAsymmetry_cutTau21_NOMA" ]->Sumw2();
		histos1D_[ "massAve_cutTau21_NOMA" ] = fs_->make< TH1D >( "massAve_cutTau21_NOMA", "massAve_cutTau21_NOMA", 60, 0., 600. );
		histos1D_[ "massAve_cutTau21_NOMA" ]->Sumw2();
		histos1D_[ "cosThetaStar_cutTau21_NOMA" ] = fs_->make< TH1D >( "cosThetaStar_cutTau21_NOMA", "cosThetaStar_cutTau21_NOMA", 20, 0., 1. );
		histos1D_[ "cosThetaStar_cutTau21_NOMA" ]->Sumw2();
		histos1D_[ "jet1Tau1_cutTau21_NOMA" ] = fs_->make< TH1D >( "jet1Tau1_cutTau21_NOMA", "jet1Tau1_cutTau21_NOMA", 20, 0., 1. );
		histos1D_[ "jet1Tau1_cutTau21_NOMA" ]->Sumw2();
		histos1D_[ "jet1Tau2_cutTau21_NOMA" ] = fs_->make< TH1D >( "jet1Tau2_cutTau21_NOMA", "jet1Tau2_cutTau21_NOMA", 20, 0., 1. );
		histos1D_[ "jet1Tau2_cutTau21_NOMA" ]->Sumw2();
		histos1D_[ "jet1Tau3_cutTau21_NOMA" ] = fs_->make< TH1D >( "jet1Tau3_cutTau21_NOMA", "jet1Tau3_cutTau21_NOMA", 20, 0., 1. );
		histos1D_[ "jet1Tau3_cutTau21_NOMA" ]->Sumw2();
		histos1D_[ "jet1Tau21_cutTau21_NOMA" ] = fs_->make< TH1D >( "jet1Tau21_cutTau21_NOMA", "jet1Tau21_cutTau21_NOMA", 20, 0., 1. );
		histos1D_[ "jet1Tau21_cutTau21_NOMA" ]->Sumw2();
		histos1D_[ "jet1Tau31_cutTau21_NOMA" ] = fs_->make< TH1D >( "jet1Tau31_cutTau21_NOMA", "jet1Tau31_cutTau21_NOMA", 20, 0., 1. );
		histos1D_[ "jet1Tau31_cutTau21_NOMA" ]->Sumw2();
		histos1D_[ "jet1Tau32_cutTau21_NOMA" ] = fs_->make< TH1D >( "jet1Tau32_cutTau21_NOMA", "jet1Tau32_cutTau21_NOMA", 20, 0., 1. );
		histos1D_[ "jet1Tau32_cutTau21_NOMA" ]->Sumw2();
		histos1D_[ "jet2Tau1_cutTau21_NOMA" ] = fs_->make< TH1D >( "jet2Tau1_cutTau21_NOMA", "jet2Tau1_cutTau21_NOMA", 20, 0., 1. );
		histos1D_[ "jet2Tau1_cutTau21_NOMA" ]->Sumw2();
		histos1D_[ "jet2Tau2_cutTau21_NOMA" ] = fs_->make< TH1D >( "jet2Tau2_cutTau21_NOMA", "jet2Tau2_cutTau21_NOMA", 20, 0., 1. );
		histos1D_[ "jet2Tau2_cutTau21_NOMA" ]->Sumw2();
		histos1D_[ "jet2Tau3_cutTau21_NOMA" ] = fs_->make< TH1D >( "jet2Tau3_cutTau21_NOMA", "jet2Tau3_cutTau21_NOMA", 20, 0., 1. );
		histos1D_[ "jet2Tau3_cutTau21_NOMA" ]->Sumw2();
		histos1D_[ "jet2Tau21_cutTau21_NOMA" ] = fs_->make< TH1D >( "jet2Tau21_cutTau21_NOMA", "jet2Tau21_cutTau21_NOMA", 20, 0., 1. );
		histos1D_[ "jet2Tau21_cutTau21_NOMA" ]->Sumw2();
		histos1D_[ "jet2Tau31_cutTau21_NOMA" ] = fs_->make< TH1D >( "jet2Tau31_cutTau21_NOMA", "jet2Tau31_cutTau21_NOMA", 20, 0., 1. );
		histos1D_[ "jet2Tau31_cutTau21_NOMA" ]->Sumw2();
		histos1D_[ "jet2Tau32_cutTau21_NOMA" ] = fs_->make< TH1D >( "jet2Tau32_cutTau21_NOMA", "jet2Tau32_cutTau21_NOMA", 20, 0., 1. );
		histos1D_[ "jet2Tau32_cutTau21_NOMA" ]->Sumw2();
		histos1D_[ "deltaEtaDijet_cutTau21_NOMA" ] = fs_->make< TH1D >( "deltaEtaDijet_cutTau21_NOMA", "deltaEtaDijet_cutTau21_NOMA", 50, 0., 5. );
		histos1D_[ "deltaEtaDijet_cutTau21_NOMA" ]->Sumw2();
		histos1D_[ "jet1SubjetPtRatio_cutTau21_NOMA" ] = fs_->make< TH1D >( "jet1SubjetPtRatio_cutTau21_NOMA", "jet1SubjetPtRatio_cutTau21_NOMA", 20, 0, 1.);
		histos1D_[ "jet1SubjetPtRatio_cutTau21_NOMA" ]->Sumw2();
		histos1D_[ "jet2SubjetPtRatio_cutTau21_NOMA" ] = fs_->make< TH1D >( "jet2SubjetPtRatio_cutTau21_NOMA", "jet2SubjetPtRatio_cutTau21_NOMA", 20, 0., 1. );
		histos1D_[ "jet2SubjetPtRatio_cutTau21_NOMA" ]->Sumw2();
		histos1D_[ "subjetPtRatio_cutTau21_NOMA" ] = fs_->make< TH1D >( "subjetPtRatio_cutTau21_NOMA", "subjetPtRatio_cutTau21_NOMA", 20, 0., 1. );
		histos1D_[ "subjetPtRatio_cutTau21_NOMA" ]->Sumw2();

		histos2D_[ "jetTrimmedMassHT_cutTau21_NOMA" ] = fs_->make< TH2D >( "jetTrimmedMassHT_cutTau21_NOMA", "jetTrimmedMassHT_cutTau21_NOMA", 30, 0., 300., 500, 0., 5000. );
		histos2D_[ "jetTrimmedMassHT_cutTau21_NOMA" ]->Sumw2();
		histos2D_[ "leadMassHT_cutTau21_NOMA" ] = fs_->make< TH2D >( "leadMassHT_cutTau21_NOMA", "leadMassHT_cutTau21_NOMA", 30, 0., 300., 500, 0., 5000. );
		histos2D_[ "leadMassHT_cutTau21_NOMA" ]->Sumw2();
		histos2D_[ "massAveHT_cutTau21_NOMA" ] = fs_->make< TH2D >( "massAveHT_cutTau21_NOMA", "massAveHT_cutTau21_NOMA", 30, 0., 300., 500, 0., 5000. );
		histos2D_[ "massAveHT_cutTau21_NOMA" ]->Sumw2();

		histos2D_[ "massAvevsJet1Mass_cutTau21_NOMA" ] = fs_->make< TH2D >( "massAvevsJet1Mass_cutTau21_NOMA", "massAvevsJet1Mass_cutTau21_NOMA", 60, 0., 600., 30, 0., 300. );
		histos2D_[ "massAvevsJet1Mass_cutTau21_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsJet2Mass_cutTau21_NOMA" ] = fs_->make< TH2D >( "massAvevsJet2Mass_cutTau21_NOMA", "massAvevsJet2Mass_cutTau21_NOMA", 60, 0., 600., 30, 0., 300. );
		histos2D_[ "massAvevsJet2Mass_cutTau21_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsMassAsym_cutTau21_NOMA" ] = fs_->make< TH2D >( "massAvevsMassAsym_cutTau21_NOMA", "massAvevsMassAsym_cutTau21_NOMA", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsMassAsym_cutTau21_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsDEta_cutTau21_NOMA" ] = fs_->make< TH2D >( "massAvevsDEta_cutTau21_NOMA", "massAvevsDEta_cutTau21_NOMA", 60, 0., 600., 50, 0., 5. );
		histos2D_[ "massAvevsDEta_cutTau21_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsCosThetaStar_cutTau21_NOMA" ] = fs_->make< TH2D >( "massAvevsCosThetaStar_cutTau21_NOMA", "massAvevsCosThetaStar_cutTau21_NOMA", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsCosThetaStar_cutTau21_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsJet1Tau21_cutTau21_NOMA" ] = fs_->make< TH2D >( "massAvevsJet1Tau21_cutTau21_NOMA", "massAvevsJet1Tau21_cutTau21_NOMA", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1Tau21_cutTau21_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsJet1Tau31_cutTau21_NOMA" ] = fs_->make< TH2D >( "massAvevsJet1Tau31_cutTau21_NOMA", "massAvevsJet1Tau31_cutTau21_NOMA", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1Tau31_cutTau21_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsJet1Tau32_cutTau21_NOMA" ] = fs_->make< TH2D >( "massAvevsJet1Tau32_cutTau21_NOMA", "massAvevsJet1Tau32_cutTau21_NOMA", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1Tau32_cutTau21_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsJet2Tau21_cutTau21_NOMA" ] = fs_->make< TH2D >( "massAvevsJet2Tau21_cutTau21_NOMA", "massAvevsJet2Tau21_cutTau21_NOMA", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2Tau21_cutTau21_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsJet2Tau31_cutTau21_NOMA" ] = fs_->make< TH2D >( "massAvevsJet2Tau31_cutTau21_NOMA", "massAvevsJet2Tau31_cutTau21_NOMA", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2Tau31_cutTau21_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsJet2Tau32_cutTau21_NOMA" ] = fs_->make< TH2D >( "massAvevsJet2Tau32_cutTau21_NOMA", "massAvevsJet2Tau32_cutTau21_NOMA", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2Tau32_cutTau21_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsJet1SubjetPtRatio_cutTau21_NOMA" ] = fs_->make< TH2D >( "massAvevsJet1SubjetPtRatio_cutTau21_NOMA", "massAvevsJet1SubjetPtRatio_cutTau21_NOMA", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1SubjetPtRatio_cutTau21_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsJet2SubjetPtRatio_cutTau21_NOMA" ] = fs_->make< TH2D >( "massAvevsJet2SubjetPtRatio_cutTau21_NOMA", "massAvevsJet2SubjetPtRatio_cutTau21_NOMA", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2SubjetPtRatio_cutTau21_NOMA" ]->Sumw2();
		histos2D_[ "jet1vs2Mass_cutTau21_NOMA" ] = fs_->make< TH2D >( "jet1vs2Mass_cutTau21_NOMA", "jet1vs2Mass_cutTau21_NOMA", 60, 0., 600., 30, 0., 300. );
		histos2D_[ "jet1vs2Mass_cutTau21_NOMA" ]->Sumw2();
		histos2D_[ "dijetCorr_cutTau21_NOMA" ] = fs_->make< TH2D >( "dijetCorr_cutTau21_NOMA", "dijetCorr_cutTau21_NOMA", 56, -3.5, 3.5, 56, -3.5, 3.5 );
		histos2D_[ "dijetCorr_cutTau21_NOMA" ]->Sumw2();
		histos2D_[ "dijetCorrPhi_cutTau21_NOMA" ] = fs_->make< TH2D >( "dijetCorrPhi_cutTau21_NOMA", "dijetCorrPhi_cutTau21_NOMA", 56, -3.5, 3.5, 56, -3.5, 3.5 );
		histos2D_[ "dijetCorrPhi_cutTau21_NOMA" ]->Sumw2();



		histos1D_[ "HT_cutCosTheta_NOMA" ] = fs_->make< TH1D >( "HT_cutCosTheta_NOMA", "HT_cutCosTheta_NOMA", 500, 0., 5000. );
		histos1D_[ "HT_cutCosTheta_NOMA" ]->Sumw2();
		histos1D_[ "NPV_cutCosTheta_NOMA" ] = fs_->make< TH1D >( "NPV_cutCosTheta_NOMA", "NPV_cutCosTheta_NOMA", 80, 0., 80. );
		histos1D_[ "NPV_cutCosTheta_NOMA" ]->Sumw2();
		histos1D_[ "jetNum_cutCosTheta_NOMA" ] = fs_->make< TH1D >( "jetNum_cutCosTheta_NOMA", "jetNum_cutCosTheta_NOMA", 10, 0., 10. );
		histos1D_[ "jetNum_cutCosTheta_NOMA" ]->Sumw2();
		histos1D_[ "jet1Pt_cutCosTheta_NOMA" ] = fs_->make< TH1D >( "jet1Pt_cutCosTheta_NOMA", "jet1Pt_cutCosTheta_NOMA", 100, 0., 1000. );
		histos1D_[ "jet1Pt_cutCosTheta_NOMA" ]->Sumw2();
		histos1D_[ "jet1Eta_cutCosTheta_NOMA" ] = fs_->make< TH1D >( "jet1Eta_cutCosTheta_NOMA", "jet1Eta_cutCosTheta_NOMA", 100, -5., 5. );
		histos1D_[ "jet1Eta_cutCosTheta_NOMA" ]->Sumw2();
		histos1D_[ "jet1Mass_cutCosTheta_NOMA" ] = fs_->make< TH1D >( "jet1Mass_cutCosTheta_NOMA", "jet1Mass_cutCosTheta_NOMA", 60, 0., 600. );
		histos1D_[ "jet1Mass_cutCosTheta_NOMA" ]->Sumw2();
		histos1D_[ "jet2Pt_cutCosTheta_NOMA" ] = fs_->make< TH1D >( "jet2Pt_cutCosTheta_NOMA", "jet2Pt_cutCosTheta_NOMA", 100, 0., 1000. );
		histos1D_[ "jet2Pt_cutCosTheta_NOMA" ]->Sumw2();
		histos1D_[ "jet2Eta_cutCosTheta_NOMA" ] = fs_->make< TH1D >( "jet2Eta_cutCosTheta_NOMA", "jet2Eta_cutCosTheta_NOMA", 100, -5., 5. );
		histos1D_[ "jet2Eta_cutCosTheta_NOMA" ]->Sumw2();
		histos1D_[ "jet2Mass_cutCosTheta_NOMA" ] = fs_->make< TH1D >( "jet2Mass_cutCosTheta_NOMA", "jet2Mass_cutCosTheta_NOMA", 60, 0., 600. );
		histos1D_[ "jet2Mass_cutCosTheta_NOMA" ]->Sumw2();

		histos1D_[ "massAsymmetry_cutCosTheta_NOMA" ] = fs_->make< TH1D >( "massAsymmetry_cutCosTheta_NOMA", "massAsymmetry_cutCosTheta_NOMA", 20, 0., 1. );
		histos1D_[ "massAsymmetry_cutCosTheta_NOMA" ]->Sumw2();
		histos1D_[ "massAve_cutCosTheta_NOMA" ] = fs_->make< TH1D >( "massAve_cutCosTheta_NOMA", "massAve_cutCosTheta_NOMA", 60, 0., 600. );
		histos1D_[ "massAve_cutCosTheta_NOMA" ]->Sumw2();
		histos1D_[ "cosThetaStar_cutCosTheta_NOMA" ] = fs_->make< TH1D >( "cosThetaStar_cutCosTheta_NOMA", "cosThetaStar_cutCosTheta_NOMA", 20, 0., 1. );
		histos1D_[ "cosThetaStar_cutCosTheta_NOMA" ]->Sumw2();
		histos1D_[ "jet1Tau1_cutCosTheta_NOMA" ] = fs_->make< TH1D >( "jet1Tau1_cutCosTheta_NOMA", "jet1Tau1_cutCosTheta_NOMA", 20, 0., 1. );
		histos1D_[ "jet1Tau1_cutCosTheta_NOMA" ]->Sumw2();
		histos1D_[ "jet1Tau2_cutCosTheta_NOMA" ] = fs_->make< TH1D >( "jet1Tau2_cutCosTheta_NOMA", "jet1Tau2_cutCosTheta_NOMA", 20, 0., 1. );
		histos1D_[ "jet1Tau2_cutCosTheta_NOMA" ]->Sumw2();
		histos1D_[ "jet1Tau3_cutCosTheta_NOMA" ] = fs_->make< TH1D >( "jet1Tau3_cutCosTheta_NOMA", "jet1Tau3_cutCosTheta_NOMA", 20, 0., 1. );
		histos1D_[ "jet1Tau3_cutCosTheta_NOMA" ]->Sumw2();
		histos1D_[ "jet1Tau21_cutCosTheta_NOMA" ] = fs_->make< TH1D >( "jet1Tau21_cutCosTheta_NOMA", "jet1Tau21_cutCosTheta_NOMA", 20, 0., 1. );
		histos1D_[ "jet1Tau21_cutCosTheta_NOMA" ]->Sumw2();
		histos1D_[ "jet1Tau31_cutCosTheta_NOMA" ] = fs_->make< TH1D >( "jet1Tau31_cutCosTheta_NOMA", "jet1Tau31_cutCosTheta_NOMA", 20, 0., 1. );
		histos1D_[ "jet1Tau31_cutCosTheta_NOMA" ]->Sumw2();
		histos1D_[ "jet1Tau32_cutCosTheta_NOMA" ] = fs_->make< TH1D >( "jet1Tau32_cutCosTheta_NOMA", "jet1Tau32_cutCosTheta_NOMA", 20, 0., 1. );
		histos1D_[ "jet1Tau32_cutCosTheta_NOMA" ]->Sumw2();
		histos1D_[ "jet2Tau1_cutCosTheta_NOMA" ] = fs_->make< TH1D >( "jet2Tau1_cutCosTheta_NOMA", "jet2Tau1_cutCosTheta_NOMA", 20, 0., 1. );
		histos1D_[ "jet2Tau1_cutCosTheta_NOMA" ]->Sumw2();
		histos1D_[ "jet2Tau2_cutCosTheta_NOMA" ] = fs_->make< TH1D >( "jet2Tau2_cutCosTheta_NOMA", "jet2Tau2_cutCosTheta_NOMA", 20, 0., 1. );
		histos1D_[ "jet2Tau2_cutCosTheta_NOMA" ]->Sumw2();
		histos1D_[ "jet2Tau3_cutCosTheta_NOMA" ] = fs_->make< TH1D >( "jet2Tau3_cutCosTheta_NOMA", "jet2Tau3_cutCosTheta_NOMA", 20, 0., 1. );
		histos1D_[ "jet2Tau3_cutCosTheta_NOMA" ]->Sumw2();
		histos1D_[ "jet2Tau21_cutCosTheta_NOMA" ] = fs_->make< TH1D >( "jet2Tau21_cutCosTheta_NOMA", "jet2Tau21_cutCosTheta_NOMA", 20, 0., 1. );
		histos1D_[ "jet2Tau21_cutCosTheta_NOMA" ]->Sumw2();
		histos1D_[ "jet2Tau31_cutCosTheta_NOMA" ] = fs_->make< TH1D >( "jet2Tau31_cutCosTheta_NOMA", "jet2Tau31_cutCosTheta_NOMA", 20, 0., 1. );
		histos1D_[ "jet2Tau31_cutCosTheta_NOMA" ]->Sumw2();
		histos1D_[ "jet2Tau32_cutCosTheta_NOMA" ] = fs_->make< TH1D >( "jet2Tau32_cutCosTheta_NOMA", "jet2Tau32_cutCosTheta_NOMA", 20, 0., 1. );
		histos1D_[ "jet2Tau32_cutCosTheta_NOMA" ]->Sumw2();
		histos1D_[ "deltaEtaDijet_cutCosTheta_NOMA" ] = fs_->make< TH1D >( "deltaEtaDijet_cutCosTheta_NOMA", "deltaEtaDijet_cutCosTheta_NOMA", 50, 0., 5. );
		histos1D_[ "deltaEtaDijet_cutCosTheta_NOMA" ]->Sumw2();
		histos1D_[ "jet1SubjetPtRatio_cutCosTheta_NOMA" ] = fs_->make< TH1D >( "jet1SubjetPtRatio_cutCosTheta_NOMA", "jet1SubjetPtRatio_cutCosTheta_NOMA", 20, 0, 1.);
		histos1D_[ "jet1SubjetPtRatio_cutCosTheta_NOMA" ]->Sumw2();
		histos1D_[ "jet2SubjetPtRatio_cutCosTheta_NOMA" ] = fs_->make< TH1D >( "jet2SubjetPtRatio_cutCosTheta_NOMA", "jet2SubjetPtRatio_cutCosTheta_NOMA", 20, 0., 1. );
		histos1D_[ "jet2SubjetPtRatio_cutCosTheta_NOMA" ]->Sumw2();
		histos1D_[ "subjetPtRatio_cutCosTheta_NOMA" ] = fs_->make< TH1D >( "subjetPtRatio_cutCosTheta_NOMA", "subjetPtRatio_cutCosTheta_NOMA", 20, 0., 1. );
		histos1D_[ "subjetPtRatio_cutCosTheta_NOMA" ]->Sumw2();

		histos2D_[ "jetTrimmedMassHT_cutCosTheta_NOMA" ] = fs_->make< TH2D >( "jetTrimmedMassHT_cutCosTheta_NOMA", "jetTrimmedMassHT_cutCosTheta_NOMA", 30, 0., 300., 500, 0., 5000. );
		histos2D_[ "jetTrimmedMassHT_cutCosTheta_NOMA" ]->Sumw2();
		histos2D_[ "leadMassHT_cutCosTheta_NOMA" ] = fs_->make< TH2D >( "leadMassHT_cutCosTheta_NOMA", "leadMassHT_cutCosTheta_NOMA", 30, 0., 300., 500, 0., 5000. );
		histos2D_[ "leadMassHT_cutCosTheta_NOMA" ]->Sumw2();
		histos2D_[ "massAveHT_cutCosTheta_NOMA" ] = fs_->make< TH2D >( "massAveHT_cutCosTheta_NOMA", "massAveHT_cutCosTheta_NOMA", 30, 0., 300., 500, 0., 5000. );
		histos2D_[ "massAveHT_cutCosTheta_NOMA" ]->Sumw2();

		histos2D_[ "massAvevsJet1Mass_cutCosTheta_NOMA" ] = fs_->make< TH2D >( "massAvevsJet1Mass_cutCosTheta_NOMA", "massAvevsJet1Mass_cutCosTheta_NOMA", 60, 0., 600., 30, 0., 300. );
		histos2D_[ "massAvevsJet1Mass_cutCosTheta_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsJet2Mass_cutCosTheta_NOMA" ] = fs_->make< TH2D >( "massAvevsJet2Mass_cutCosTheta_NOMA", "massAvevsJet2Mass_cutCosTheta_NOMA", 60, 0., 600., 30, 0., 300. );
		histos2D_[ "massAvevsJet2Mass_cutCosTheta_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsMassAsym_cutCosTheta_NOMA" ] = fs_->make< TH2D >( "massAvevsMassAsym_cutCosTheta_NOMA", "massAvevsMassAsym_cutCosTheta_NOMA", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsMassAsym_cutCosTheta_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsDEta_cutCosTheta_NOMA" ] = fs_->make< TH2D >( "massAvevsDEta_cutCosTheta_NOMA", "massAvevsDEta_cutCosTheta_NOMA", 60, 0., 600., 50, 0., 5. );
		histos2D_[ "massAvevsDEta_cutCosTheta_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsCosThetaStar_cutCosTheta_NOMA" ] = fs_->make< TH2D >( "massAvevsCosThetaStar_cutCosTheta_NOMA", "massAvevsCosThetaStar_cutCosTheta_NOMA", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsCosThetaStar_cutCosTheta_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsJet1Tau21_cutCosTheta_NOMA" ] = fs_->make< TH2D >( "massAvevsJet1Tau21_cutCosTheta_NOMA", "massAvevsJet1Tau21_cutCosTheta_NOMA", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1Tau21_cutCosTheta_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsJet1Tau31_cutCosTheta_NOMA" ] = fs_->make< TH2D >( "massAvevsJet1Tau31_cutCosTheta_NOMA", "massAvevsJet1Tau31_cutCosTheta_NOMA", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1Tau31_cutCosTheta_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsJet1Tau32_cutCosTheta_NOMA" ] = fs_->make< TH2D >( "massAvevsJet1Tau32_cutCosTheta_NOMA", "massAvevsJet1Tau32_cutCosTheta_NOMA", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1Tau32_cutCosTheta_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsJet2Tau21_cutCosTheta_NOMA" ] = fs_->make< TH2D >( "massAvevsJet2Tau21_cutCosTheta_NOMA", "massAvevsJet2Tau21_cutCosTheta_NOMA", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2Tau21_cutCosTheta_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsJet2Tau31_cutCosTheta_NOMA" ] = fs_->make< TH2D >( "massAvevsJet2Tau31_cutCosTheta_NOMA", "massAvevsJet2Tau31_cutCosTheta_NOMA", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2Tau31_cutCosTheta_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsJet2Tau32_cutCosTheta_NOMA" ] = fs_->make< TH2D >( "massAvevsJet2Tau32_cutCosTheta_NOMA", "massAvevsJet2Tau32_cutCosTheta_NOMA", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2Tau32_cutCosTheta_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsJet1SubjetPtRatio_cutCosTheta_NOMA" ] = fs_->make< TH2D >( "massAvevsJet1SubjetPtRatio_cutCosTheta_NOMA", "massAvevsJet1SubjetPtRatio_cutCosTheta_NOMA", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1SubjetPtRatio_cutCosTheta_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsJet2SubjetPtRatio_cutCosTheta_NOMA" ] = fs_->make< TH2D >( "massAvevsJet2SubjetPtRatio_cutCosTheta_NOMA", "massAvevsJet2SubjetPtRatio_cutCosTheta_NOMA", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2SubjetPtRatio_cutCosTheta_NOMA" ]->Sumw2();
		histos2D_[ "jet1vs2Mass_cutCosTheta_NOMA" ] = fs_->make< TH2D >( "jet1vs2Mass_cutCosTheta_NOMA", "jet1vs2Mass_cutCosTheta_NOMA", 60, 0., 600., 30, 0., 300. );
		histos2D_[ "jet1vs2Mass_cutCosTheta_NOMA" ]->Sumw2();
		histos2D_[ "dijetCorr_cutCosTheta_NOMA" ] = fs_->make< TH2D >( "dijetCorr_cutCosTheta_NOMA", "dijetCorr_cutCosTheta_NOMA", 56, -3.5, 3.5, 56, -3.5, 3.5 );
		histos2D_[ "dijetCorr_cutCosTheta_NOMA" ]->Sumw2();
		histos2D_[ "dijetCorrPhi_cutCosTheta_NOMA" ] = fs_->make< TH2D >( "dijetCorrPhi_cutCosTheta_NOMA", "dijetCorrPhi_cutCosTheta_NOMA", 56, -3.5, 3.5, 56, -3.5, 3.5 );
		histos2D_[ "dijetCorrPhi_cutCosTheta_NOMA" ]->Sumw2();



		histos1D_[ "HT_cutDEta_NOMA" ] = fs_->make< TH1D >( "HT_cutDEta_NOMA", "HT_cutDEta_NOMA", 500, 0., 5000. );
		histos1D_[ "HT_cutDEta_NOMA" ]->Sumw2();
		histos1D_[ "NPV_cutDEta_NOMA" ] = fs_->make< TH1D >( "NPV_cutDEta_NOMA", "NPV_cutDEta_NOMA", 80, 0., 80. );
		histos1D_[ "NPV_cutDEta_NOMA" ]->Sumw2();
		histos1D_[ "jetNum_cutDEta_NOMA" ] = fs_->make< TH1D >( "jetNum_cutDEta_NOMA", "jetNum_cutDEta_NOMA", 10, 0., 10. );
		histos1D_[ "jetNum_cutDEta_NOMA" ]->Sumw2();
		histos1D_[ "jet1Pt_cutDEta_NOMA" ] = fs_->make< TH1D >( "jet1Pt_cutDEta_NOMA", "jet1Pt_cutDEta_NOMA", 100, 0., 1000. );
		histos1D_[ "jet1Pt_cutDEta_NOMA" ]->Sumw2();
		histos1D_[ "jet1Eta_cutDEta_NOMA" ] = fs_->make< TH1D >( "jet1Eta_cutDEta_NOMA", "jet1Eta_cutDEta_NOMA", 100, -5., 5. );
		histos1D_[ "jet1Eta_cutDEta_NOMA" ]->Sumw2();
		histos1D_[ "jet1Mass_cutDEta_NOMA" ] = fs_->make< TH1D >( "jet1Mass_cutDEta_NOMA", "jet1Mass_cutDEta_NOMA", 60, 0., 600. );
		histos1D_[ "jet1Mass_cutDEta_NOMA" ]->Sumw2();
		histos1D_[ "jet2Pt_cutDEta_NOMA" ] = fs_->make< TH1D >( "jet2Pt_cutDEta_NOMA", "jet2Pt_cutDEta_NOMA", 100, 0., 1000. );
		histos1D_[ "jet2Pt_cutDEta_NOMA" ]->Sumw2();
		histos1D_[ "jet2Eta_cutDEta_NOMA" ] = fs_->make< TH1D >( "jet2Eta_cutDEta_NOMA", "jet2Eta_cutDEta_NOMA", 100, -5., 5. );
		histos1D_[ "jet2Eta_cutDEta_NOMA" ]->Sumw2();
		histos1D_[ "jet2Mass_cutDEta_NOMA" ] = fs_->make< TH1D >( "jet2Mass_cutDEta_NOMA", "jet2Mass_cutDEta_NOMA", 60, 0., 600. );
		histos1D_[ "jet2Mass_cutDEta_NOMA" ]->Sumw2();

		histos1D_[ "massAsymmetry_cutDEta_NOMA" ] = fs_->make< TH1D >( "massAsymmetry_cutDEta_NOMA", "massAsymmetry_cutDEta_NOMA", 20, 0., 1. );
		histos1D_[ "massAsymmetry_cutDEta_NOMA" ]->Sumw2();
		histos1D_[ "massAve_cutDEta_NOMA" ] = fs_->make< TH1D >( "massAve_cutDEta_NOMA", "massAve_cutDEta_NOMA", 60, 0., 600. );
		histos1D_[ "massAve_cutDEta_NOMA" ]->Sumw2();
		histos1D_[ "cosThetaStar_cutDEta_NOMA" ] = fs_->make< TH1D >( "cosThetaStar_cutDEta_NOMA", "cosThetaStar_cutDEta_NOMA", 20, 0., 1. );
		histos1D_[ "cosThetaStar_cutDEta_NOMA" ]->Sumw2();
		histos1D_[ "jet1Tau1_cutDEta_NOMA" ] = fs_->make< TH1D >( "jet1Tau1_cutDEta_NOMA", "jet1Tau1_cutDEta_NOMA", 20, 0., 1. );
		histos1D_[ "jet1Tau1_cutDEta_NOMA" ]->Sumw2();
		histos1D_[ "jet1Tau2_cutDEta_NOMA" ] = fs_->make< TH1D >( "jet1Tau2_cutDEta_NOMA", "jet1Tau2_cutDEta_NOMA", 20, 0., 1. );
		histos1D_[ "jet1Tau2_cutDEta_NOMA" ]->Sumw2();
		histos1D_[ "jet1Tau3_cutDEta_NOMA" ] = fs_->make< TH1D >( "jet1Tau3_cutDEta_NOMA", "jet1Tau3_cutDEta_NOMA", 20, 0., 1. );
		histos1D_[ "jet1Tau3_cutDEta_NOMA" ]->Sumw2();
		histos1D_[ "jet1Tau21_cutDEta_NOMA" ] = fs_->make< TH1D >( "jet1Tau21_cutDEta_NOMA", "jet1Tau21_cutDEta_NOMA", 20, 0., 1. );
		histos1D_[ "jet1Tau21_cutDEta_NOMA" ]->Sumw2();
		histos1D_[ "jet1Tau31_cutDEta_NOMA" ] = fs_->make< TH1D >( "jet1Tau31_cutDEta_NOMA", "jet1Tau31_cutDEta_NOMA", 20, 0., 1. );
		histos1D_[ "jet1Tau31_cutDEta_NOMA" ]->Sumw2();
		histos1D_[ "jet1Tau32_cutDEta_NOMA" ] = fs_->make< TH1D >( "jet1Tau32_cutDEta_NOMA", "jet1Tau32_cutDEta_NOMA", 20, 0., 1. );
		histos1D_[ "jet1Tau32_cutDEta_NOMA" ]->Sumw2();
		histos1D_[ "jet2Tau1_cutDEta_NOMA" ] = fs_->make< TH1D >( "jet2Tau1_cutDEta_NOMA", "jet2Tau1_cutDEta_NOMA", 20, 0., 1. );
		histos1D_[ "jet2Tau1_cutDEta_NOMA" ]->Sumw2();
		histos1D_[ "jet2Tau2_cutDEta_NOMA" ] = fs_->make< TH1D >( "jet2Tau2_cutDEta_NOMA", "jet2Tau2_cutDEta_NOMA", 20, 0., 1. );
		histos1D_[ "jet2Tau2_cutDEta_NOMA" ]->Sumw2();
		histos1D_[ "jet2Tau3_cutDEta_NOMA" ] = fs_->make< TH1D >( "jet2Tau3_cutDEta_NOMA", "jet2Tau3_cutDEta_NOMA", 20, 0., 1. );
		histos1D_[ "jet2Tau3_cutDEta_NOMA" ]->Sumw2();
		histos1D_[ "jet2Tau21_cutDEta_NOMA" ] = fs_->make< TH1D >( "jet2Tau21_cutDEta_NOMA", "jet2Tau21_cutDEta_NOMA", 20, 0., 1. );
		histos1D_[ "jet2Tau21_cutDEta_NOMA" ]->Sumw2();
		histos1D_[ "jet2Tau31_cutDEta_NOMA" ] = fs_->make< TH1D >( "jet2Tau31_cutDEta_NOMA", "jet2Tau31_cutDEta_NOMA", 20, 0., 1. );
		histos1D_[ "jet2Tau31_cutDEta_NOMA" ]->Sumw2();
		histos1D_[ "jet2Tau32_cutDEta_NOMA" ] = fs_->make< TH1D >( "jet2Tau32_cutDEta_NOMA", "jet2Tau32_cutDEta_NOMA", 20, 0., 1. );
		histos1D_[ "jet2Tau32_cutDEta_NOMA" ]->Sumw2();
		histos1D_[ "deltaEtaDijet_cutDEta_NOMA" ] = fs_->make< TH1D >( "deltaEtaDijet_cutDEta_NOMA", "deltaEtaDijet_cutDEta_NOMA", 50, 0., 5. );
		histos1D_[ "deltaEtaDijet_cutDEta_NOMA" ]->Sumw2();
		histos1D_[ "jet1SubjetPtRatio_cutDEta_NOMA" ] = fs_->make< TH1D >( "jet1SubjetPtRatio_cutDEta_NOMA", "jet1SubjetPtRatio_cutDEta_NOMA", 20, 0, 1.);
		histos1D_[ "jet1SubjetPtRatio_cutDEta_NOMA" ]->Sumw2();
		histos1D_[ "jet2SubjetPtRatio_cutDEta_NOMA" ] = fs_->make< TH1D >( "jet2SubjetPtRatio_cutDEta_NOMA", "jet2SubjetPtRatio_cutDEta_NOMA", 20, 0., 1. );
		histos1D_[ "jet2SubjetPtRatio_cutDEta_NOMA" ]->Sumw2();
		histos1D_[ "subjetPtRatio_cutDEta_NOMA" ] = fs_->make< TH1D >( "subjetPtRatio_cutDEta_NOMA", "subjetPtRatio_cutDEta_NOMA", 20, 0., 1. );
		histos1D_[ "subjetPtRatio_cutDEta_NOMA" ]->Sumw2();

		histos2D_[ "jetTrimmedMassHT_cutDEta_NOMA" ] = fs_->make< TH2D >( "jetTrimmedMassHT_cutDEta_NOMA", "jetTrimmedMassHT_cutDEta_NOMA", 30, 0., 300., 500, 0., 5000. );
		histos2D_[ "jetTrimmedMassHT_cutDEta_NOMA" ]->Sumw2();
		histos2D_[ "leadMassHT_cutDEta_NOMA" ] = fs_->make< TH2D >( "leadMassHT_cutDEta_NOMA", "leadMassHT_cutDEta_NOMA", 30, 0., 300., 500, 0., 5000. );
		histos2D_[ "leadMassHT_cutDEta_NOMA" ]->Sumw2();
		histos2D_[ "massAveHT_cutDEta_NOMA" ] = fs_->make< TH2D >( "massAveHT_cutDEta_NOMA", "massAveHT_cutDEta_NOMA", 30, 0., 300., 500, 0., 5000. );
		histos2D_[ "massAveHT_cutDEta_NOMA" ]->Sumw2();

		histos2D_[ "massAvevsJet1Mass_cutDEta_NOMA" ] = fs_->make< TH2D >( "massAvevsJet1Mass_cutDEta_NOMA", "massAvevsJet1Mass_cutDEta_NOMA", 60, 0., 600., 30, 0., 300. );
		histos2D_[ "massAvevsJet1Mass_cutDEta_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsJet2Mass_cutDEta_NOMA" ] = fs_->make< TH2D >( "massAvevsJet2Mass_cutDEta_NOMA", "massAvevsJet2Mass_cutDEta_NOMA", 60, 0., 600., 30, 0., 300. );
		histos2D_[ "massAvevsJet2Mass_cutDEta_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsMassAsym_cutDEta_NOMA" ] = fs_->make< TH2D >( "massAvevsMassAsym_cutDEta_NOMA", "massAvevsMassAsym_cutDEta_NOMA", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsMassAsym_cutDEta_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsDEta_cutDEta_NOMA" ] = fs_->make< TH2D >( "massAvevsDEta_cutDEta_NOMA", "massAvevsDEta_cutDEta_NOMA", 60, 0., 600., 50, 0., 5. );
		histos2D_[ "massAvevsDEta_cutDEta_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsCosThetaStar_cutDEta_NOMA" ] = fs_->make< TH2D >( "massAvevsCosThetaStar_cutDEta_NOMA", "massAvevsCosThetaStar_cutDEta_NOMA", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsCosThetaStar_cutDEta_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsJet1Tau21_cutDEta_NOMA" ] = fs_->make< TH2D >( "massAvevsJet1Tau21_cutDEta_NOMA", "massAvevsJet1Tau21_cutDEta_NOMA", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1Tau21_cutDEta_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsJet1Tau31_cutDEta_NOMA" ] = fs_->make< TH2D >( "massAvevsJet1Tau31_cutDEta_NOMA", "massAvevsJet1Tau31_cutDEta_NOMA", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1Tau31_cutDEta_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsJet1Tau32_cutDEta_NOMA" ] = fs_->make< TH2D >( "massAvevsJet1Tau32_cutDEta_NOMA", "massAvevsJet1Tau32_cutDEta_NOMA", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1Tau32_cutDEta_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsJet2Tau21_cutDEta_NOMA" ] = fs_->make< TH2D >( "massAvevsJet2Tau21_cutDEta_NOMA", "massAvevsJet2Tau21_cutDEta_NOMA", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2Tau21_cutDEta_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsJet2Tau31_cutDEta_NOMA" ] = fs_->make< TH2D >( "massAvevsJet2Tau31_cutDEta_NOMA", "massAvevsJet2Tau31_cutDEta_NOMA", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2Tau31_cutDEta_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsJet2Tau32_cutDEta_NOMA" ] = fs_->make< TH2D >( "massAvevsJet2Tau32_cutDEta_NOMA", "massAvevsJet2Tau32_cutDEta_NOMA", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2Tau32_cutDEta_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsJet1SubjetPtRatio_cutDEta_NOMA" ] = fs_->make< TH2D >( "massAvevsJet1SubjetPtRatio_cutDEta_NOMA", "massAvevsJet1SubjetPtRatio_cutDEta_NOMA", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1SubjetPtRatio_cutDEta_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsJet2SubjetPtRatio_cutDEta_NOMA" ] = fs_->make< TH2D >( "massAvevsJet2SubjetPtRatio_cutDEta_NOMA", "massAvevsJet2SubjetPtRatio_cutDEta_NOMA", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2SubjetPtRatio_cutDEta_NOMA" ]->Sumw2();
		histos2D_[ "jet1vs2Mass_cutDEta_NOMA" ] = fs_->make< TH2D >( "jet1vs2Mass_cutDEta_NOMA", "jet1vs2Mass_cutDEta_NOMA", 60, 0., 600., 30, 0., 300. );
		histos2D_[ "jet1vs2Mass_cutDEta_NOMA" ]->Sumw2();
		histos2D_[ "dijetCorr_cutDEta_NOMA" ] = fs_->make< TH2D >( "dijetCorr_cutDEta_NOMA", "dijetCorr_cutDEta_NOMA", 56, -3.5, 3.5, 56, -3.5, 3.5 );
		histos2D_[ "dijetCorr_cutDEta_NOMA" ]->Sumw2();
		histos2D_[ "dijetCorrPhi_cutDEta_NOMA" ] = fs_->make< TH2D >( "dijetCorrPhi_cutDEta_NOMA", "dijetCorrPhi_cutDEta_NOMA", 56, -3.5, 3.5, 56, -3.5, 3.5 );
		histos2D_[ "dijetCorrPhi_cutDEta_NOMA" ]->Sumw2();



		histos1D_[ "HT_cutBtag_NOMA" ] = fs_->make< TH1D >( "HT_cutBtag_NOMA", "HT_cutBtag_NOMA", 500, 0., 5000. );
		histos1D_[ "HT_cutBtag_NOMA" ]->Sumw2();
		histos1D_[ "NPV_cutBtag_NOMA" ] = fs_->make< TH1D >( "NPV_cutBtag_NOMA", "NPV_cutBtag_NOMA", 80, 0., 80. );
		histos1D_[ "NPV_cutBtag_NOMA" ]->Sumw2();
		histos1D_[ "jetNum_cutBtag_NOMA" ] = fs_->make< TH1D >( "jetNum_cutBtag_NOMA", "jetNum_cutBtag_NOMA", 10, 0., 10. );
		histos1D_[ "jetNum_cutBtag_NOMA" ]->Sumw2();
		histos1D_[ "jet1Pt_cutBtag_NOMA" ] = fs_->make< TH1D >( "jet1Pt_cutBtag_NOMA", "jet1Pt_cutBtag_NOMA", 100, 0., 1000. );
		histos1D_[ "jet1Pt_cutBtag_NOMA" ]->Sumw2();
		histos1D_[ "jet1Eta_cutBtag_NOMA" ] = fs_->make< TH1D >( "jet1Eta_cutBtag_NOMA", "jet1Eta_cutBtag_NOMA", 100, -5., 5. );
		histos1D_[ "jet1Eta_cutBtag_NOMA" ]->Sumw2();
		histos1D_[ "jet1Mass_cutBtag_NOMA" ] = fs_->make< TH1D >( "jet1Mass_cutBtag_NOMA", "jet1Mass_cutBtag_NOMA", 60, 0., 600. );
		histos1D_[ "jet1Mass_cutBtag_NOMA" ]->Sumw2();
		histos1D_[ "jet2Pt_cutBtag_NOMA" ] = fs_->make< TH1D >( "jet2Pt_cutBtag_NOMA", "jet2Pt_cutBtag_NOMA", 100, 0., 1000. );
		histos1D_[ "jet2Pt_cutBtag_NOMA" ]->Sumw2();
		histos1D_[ "jet2Eta_cutBtag_NOMA" ] = fs_->make< TH1D >( "jet2Eta_cutBtag_NOMA", "jet2Eta_cutBtag_NOMA", 100, -5., 5. );
		histos1D_[ "jet2Eta_cutBtag_NOMA" ]->Sumw2();
		histos1D_[ "jet2Mass_cutBtag_NOMA" ] = fs_->make< TH1D >( "jet2Mass_cutBtag_NOMA", "jet2Mass_cutBtag_NOMA", 60, 0., 600. );
		histos1D_[ "jet2Mass_cutBtag_NOMA" ]->Sumw2();

		histos1D_[ "massAsymmetry_cutBtag_NOMA" ] = fs_->make< TH1D >( "massAsymmetry_cutBtag_NOMA", "massAsymmetry_cutBtag_NOMA", 20, 0., 1. );
		histos1D_[ "massAsymmetry_cutBtag_NOMA" ]->Sumw2();
		histos1D_[ "massAve_cutBtag_NOMA" ] = fs_->make< TH1D >( "massAve_cutBtag_NOMA", "massAve_cutBtag_NOMA", 60, 0., 600. );
		histos1D_[ "massAve_cutBtag_NOMA" ]->Sumw2();
		histos1D_[ "cosThetaStar_cutBtag_NOMA" ] = fs_->make< TH1D >( "cosThetaStar_cutBtag_NOMA", "cosThetaStar_cutBtag_NOMA", 20, 0., 1. );
		histos1D_[ "cosThetaStar_cutBtag_NOMA" ]->Sumw2();
		histos1D_[ "jet1Tau1_cutBtag_NOMA" ] = fs_->make< TH1D >( "jet1Tau1_cutBtag_NOMA", "jet1Tau1_cutBtag_NOMA", 20, 0., 1. );
		histos1D_[ "jet1Tau1_cutBtag_NOMA" ]->Sumw2();
		histos1D_[ "jet1Tau2_cutBtag_NOMA" ] = fs_->make< TH1D >( "jet1Tau2_cutBtag_NOMA", "jet1Tau2_cutBtag_NOMA", 20, 0., 1. );
		histos1D_[ "jet1Tau2_cutBtag_NOMA" ]->Sumw2();
		histos1D_[ "jet1Tau3_cutBtag_NOMA" ] = fs_->make< TH1D >( "jet1Tau3_cutBtag_NOMA", "jet1Tau3_cutBtag_NOMA", 20, 0., 1. );
		histos1D_[ "jet1Tau3_cutBtag_NOMA" ]->Sumw2();
		histos1D_[ "jet1Tau21_cutBtag_NOMA" ] = fs_->make< TH1D >( "jet1Tau21_cutBtag_NOMA", "jet1Tau21_cutBtag_NOMA", 20, 0., 1. );
		histos1D_[ "jet1Tau21_cutBtag_NOMA" ]->Sumw2();
		histos1D_[ "jet1Tau31_cutBtag_NOMA" ] = fs_->make< TH1D >( "jet1Tau31_cutBtag_NOMA", "jet1Tau31_cutBtag_NOMA", 20, 0., 1. );
		histos1D_[ "jet1Tau31_cutBtag_NOMA" ]->Sumw2();
		histos1D_[ "jet1Tau32_cutBtag_NOMA" ] = fs_->make< TH1D >( "jet1Tau32_cutBtag_NOMA", "jet1Tau32_cutBtag_NOMA", 20, 0., 1. );
		histos1D_[ "jet1Tau32_cutBtag_NOMA" ]->Sumw2();
		histos1D_[ "jet2Tau1_cutBtag_NOMA" ] = fs_->make< TH1D >( "jet2Tau1_cutBtag_NOMA", "jet2Tau1_cutBtag_NOMA", 20, 0., 1. );
		histos1D_[ "jet2Tau1_cutBtag_NOMA" ]->Sumw2();
		histos1D_[ "jet2Tau2_cutBtag_NOMA" ] = fs_->make< TH1D >( "jet2Tau2_cutBtag_NOMA", "jet2Tau2_cutBtag_NOMA", 20, 0., 1. );
		histos1D_[ "jet2Tau2_cutBtag_NOMA" ]->Sumw2();
		histos1D_[ "jet2Tau3_cutBtag_NOMA" ] = fs_->make< TH1D >( "jet2Tau3_cutBtag_NOMA", "jet2Tau3_cutBtag_NOMA", 20, 0., 1. );
		histos1D_[ "jet2Tau3_cutBtag_NOMA" ]->Sumw2();
		histos1D_[ "jet2Tau21_cutBtag_NOMA" ] = fs_->make< TH1D >( "jet2Tau21_cutBtag_NOMA", "jet2Tau21_cutBtag_NOMA", 20, 0., 1. );
		histos1D_[ "jet2Tau21_cutBtag_NOMA" ]->Sumw2();
		histos1D_[ "jet2Tau31_cutBtag_NOMA" ] = fs_->make< TH1D >( "jet2Tau31_cutBtag_NOMA", "jet2Tau31_cutBtag_NOMA", 20, 0., 1. );
		histos1D_[ "jet2Tau31_cutBtag_NOMA" ]->Sumw2();
		histos1D_[ "jet2Tau32_cutBtag_NOMA" ] = fs_->make< TH1D >( "jet2Tau32_cutBtag_NOMA", "jet2Tau32_cutBtag_NOMA", 20, 0., 1. );
		histos1D_[ "jet2Tau32_cutBtag_NOMA" ]->Sumw2();
		histos1D_[ "deltaEtaDijet_cutBtag_NOMA" ] = fs_->make< TH1D >( "deltaEtaDijet_cutBtag_NOMA", "deltaEtaDijet_cutBtag_NOMA", 50, 0., 5. );
		histos1D_[ "deltaEtaDijet_cutBtag_NOMA" ]->Sumw2();
		histos1D_[ "jet1SubjetPtRatio_cutBtag_NOMA" ] = fs_->make< TH1D >( "jet1SubjetPtRatio_cutBtag_NOMA", "jet1SubjetPtRatio_cutBtag_NOMA", 20, 0, 1.);
		histos1D_[ "jet1SubjetPtRatio_cutBtag_NOMA" ]->Sumw2();
		histos1D_[ "jet2SubjetPtRatio_cutBtag_NOMA" ] = fs_->make< TH1D >( "jet2SubjetPtRatio_cutBtag_NOMA", "jet2SubjetPtRatio_cutBtag_NOMA", 20, 0., 1. );
		histos1D_[ "jet2SubjetPtRatio_cutBtag_NOMA" ]->Sumw2();
		histos1D_[ "subjetPtRatio_cutBtag_NOMA" ] = fs_->make< TH1D >( "subjetPtRatio_cutBtag_NOMA", "subjetPtRatio_cutBtag_NOMA", 20, 0., 1. );
		histos1D_[ "subjetPtRatio_cutBtag_NOMA" ]->Sumw2();

		histos2D_[ "jetTrimmedMassHT_cutBtag_NOMA" ] = fs_->make< TH2D >( "jetTrimmedMassHT_cutBtag_NOMA", "jetTrimmedMassHT_cutBtag_NOMA", 30, 0., 300., 500, 0., 5000. );
		histos2D_[ "jetTrimmedMassHT_cutBtag_NOMA" ]->Sumw2();
		histos2D_[ "leadMassHT_cutBtag_NOMA" ] = fs_->make< TH2D >( "leadMassHT_cutBtag_NOMA", "leadMassHT_cutBtag_NOMA", 30, 0., 300., 500, 0., 5000. );
		histos2D_[ "leadMassHT_cutBtag_NOMA" ]->Sumw2();
		histos2D_[ "massAveHT_cutBtag_NOMA" ] = fs_->make< TH2D >( "massAveHT_cutBtag_NOMA", "massAveHT_cutBtag_NOMA", 30, 0., 300., 500, 0., 5000. );
		histos2D_[ "massAveHT_cutBtag_NOMA" ]->Sumw2();

		histos2D_[ "massAvevsJet1Mass_cutBtag_NOMA" ] = fs_->make< TH2D >( "massAvevsJet1Mass_cutBtag_NOMA", "massAvevsJet1Mass_cutBtag_NOMA", 60, 0., 600., 30, 0., 300. );
		histos2D_[ "massAvevsJet1Mass_cutBtag_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsJet2Mass_cutBtag_NOMA" ] = fs_->make< TH2D >( "massAvevsJet2Mass_cutBtag_NOMA", "massAvevsJet2Mass_cutBtag_NOMA", 60, 0., 600., 30, 0., 300. );
		histos2D_[ "massAvevsJet2Mass_cutBtag_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsMassAsym_cutBtag_NOMA" ] = fs_->make< TH2D >( "massAvevsMassAsym_cutBtag_NOMA", "massAvevsMassAsym_cutBtag_NOMA", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsMassAsym_cutBtag_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsDEta_cutBtag_NOMA" ] = fs_->make< TH2D >( "massAvevsDEta_cutBtag_NOMA", "massAvevsDEta_cutBtag_NOMA", 60, 0., 600., 50, 0., 5. );
		histos2D_[ "massAvevsDEta_cutBtag_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsCosThetaStar_cutBtag_NOMA" ] = fs_->make< TH2D >( "massAvevsCosThetaStar_cutBtag_NOMA", "massAvevsCosThetaStar_cutBtag_NOMA", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsCosThetaStar_cutBtag_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsJet1Tau21_cutBtag_NOMA" ] = fs_->make< TH2D >( "massAvevsJet1Tau21_cutBtag_NOMA", "massAvevsJet1Tau21_cutBtag_NOMA", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1Tau21_cutBtag_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsJet1Tau31_cutBtag_NOMA" ] = fs_->make< TH2D >( "massAvevsJet1Tau31_cutBtag_NOMA", "massAvevsJet1Tau31_cutBtag_NOMA", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1Tau31_cutBtag_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsJet1Tau32_cutBtag_NOMA" ] = fs_->make< TH2D >( "massAvevsJet1Tau32_cutBtag_NOMA", "massAvevsJet1Tau32_cutBtag_NOMA", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1Tau32_cutBtag_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsJet2Tau21_cutBtag_NOMA" ] = fs_->make< TH2D >( "massAvevsJet2Tau21_cutBtag_NOMA", "massAvevsJet2Tau21_cutBtag_NOMA", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2Tau21_cutBtag_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsJet2Tau31_cutBtag_NOMA" ] = fs_->make< TH2D >( "massAvevsJet2Tau31_cutBtag_NOMA", "massAvevsJet2Tau31_cutBtag_NOMA", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2Tau31_cutBtag_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsJet2Tau32_cutBtag_NOMA" ] = fs_->make< TH2D >( "massAvevsJet2Tau32_cutBtag_NOMA", "massAvevsJet2Tau32_cutBtag_NOMA", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2Tau32_cutBtag_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsJet1SubjetPtRatio_cutBtag_NOMA" ] = fs_->make< TH2D >( "massAvevsJet1SubjetPtRatio_cutBtag_NOMA", "massAvevsJet1SubjetPtRatio_cutBtag_NOMA", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet1SubjetPtRatio_cutBtag_NOMA" ]->Sumw2();
		histos2D_[ "massAvevsJet2SubjetPtRatio_cutBtag_NOMA" ] = fs_->make< TH2D >( "massAvevsJet2SubjetPtRatio_cutBtag_NOMA", "massAvevsJet2SubjetPtRatio_cutBtag_NOMA", 60, 0., 600., 20, 0., 1. );
		histos2D_[ "massAvevsJet2SubjetPtRatio_cutBtag_NOMA" ]->Sumw2();
		histos2D_[ "jet1vs2Mass_cutBtag_NOMA" ] = fs_->make< TH2D >( "jet1vs2Mass_cutBtag_NOMA", "jet1vs2Mass_cutBtag_NOMA", 60, 0., 600., 30, 0., 300. );
		histos2D_[ "jet1vs2Mass_cutBtag_NOMA" ]->Sumw2();
		histos2D_[ "dijetCorr_cutBtag_NOMA" ] = fs_->make< TH2D >( "dijetCorr_cutBtag_NOMA", "dijetCorr_cutBtag_NOMA", 56, -3.5, 3.5, 56, -3.5, 3.5 );
		histos2D_[ "dijetCorr_cutBtag_NOMA" ]->Sumw2();
		histos2D_[ "dijetCorrPhi_cutBtag_NOMA" ] = fs_->make< TH2D >( "dijetCorrPhi_cutBtag_NOMA", "dijetCorrPhi_cutBtag_NOMA", 56, -3.5, 3.5, 56, -3.5, 3.5 );
		histos2D_[ "dijetCorrPhi_cutBtag_NOMA" ]->Sumw2();


		cutLabels.push_back("Processed");
		cutLabels.push_back("Trigger");
		cutLabels.push_back("HT");
		cutLabels.push_back("Dijet");
		cutLabels.push_back("Asymmetry");
		cutLabels.push_back("Tau21");
		cutLabels.push_back("CosTheta");
		cutLabels.push_back("DEta");
		cutLabels.push_back("btag");
		histos1D_[ "hcutflow" ] = fs_->make< TH1D >("cutflow","cut flow", cutLabels.size(), 0.5, cutLabels.size() +0.5 );
		histos1D_[ "hcutflow" ]->Sumw2();
		histos1D_[ "hcutflowSimple" ] = fs_->make< TH1D >("cutflowSimple","simple cut flow", cutLabels.size(), 0.5, cutLabels.size() +0.5 );
		histos1D_[ "hcutflowSimple" ]->Sumw2();
		for( const string &ivec : cutLabels ) cutmap[ ivec ] = 0;

	}
}

// ------------ method called once each job just after ending the event loop  ------------
void RUNBoostedAnalysis::endJob() {

	int ibin = 1;
	for( const string &ivec : cutLabels ) {
		histos1D_["hcutflow"]->SetBinContent( ibin, cutmap[ ivec ] * scale );
		histos1D_["hcutflow"]->GetXaxis()->SetBinLabel( ibin, ivec.c_str() );
		histos1D_["hcutflowSimple"]->SetBinContent( ibin, cutmap[ ivec ] );
		histos1D_["hcutflowSimple"]->GetXaxis()->SetBinLabel( ibin, ivec.c_str() );
		ibin++;
	}

}

//define this as a plug-in
DEFINE_FWK_MODULE(RUNBoostedAnalysis);
