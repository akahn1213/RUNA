// system include files
#include <memory>
#include <cmath>
#include <TH1.h>
#include <TH2.h>
#include <TLorentzVector.h>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/JetReco/interface/Jet.h"

#include "RUNA/RUNAnalysis/interface/CommonVariablesStructure.h"

using namespace edm;
using namespace std;

class RUNTriggerValidation : public edm::EDAnalyzer {

	public:
		explicit RUNTriggerValidation(const edm::ParameterSet&);
		~RUNTriggerValidation() {}

	private:
		virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      		virtual void beginJob() override;

	edm::EDGetTokenT<edm::TriggerResults> triggerBits_;
	edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> triggerObjects_;
	edm::EDGetTokenT<pat::PackedTriggerPrescales> triggerPrescales_;
	edm::EDGetTokenT<trigger::TriggerEvent> triggerEvent_;
	edm::EDGetTokenT<pat::JetCollection> jetToken_;
	std::string hltPath_;
	std::string denomPath_;
	std::string numerPath_;
	std::string orPath_;
    	int triggerBitInt;

//      	edm::EDGetTokenT<vector<float>> triggerBit_;
//      	edm::EDGetTokenT<std::vector<std::string>> triggerName_;


      	TString baseTrigger;
      	vector<string> triggerPass;

	edm::Service<TFileService> fs_;
	map< string, TH1D* > histos1D_;
	map< string, TH2D* > histos2D_;
};

RUNTriggerValidation::RUNTriggerValidation(const edm::ParameterSet& iConfig):
	triggerBits_(consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("bits"))),
	triggerObjects_(consumes<pat::TriggerObjectStandAloneCollection>(iConfig.getParameter<edm::InputTag>("objects"))),
	triggerPrescales_(consumes<pat::PackedTriggerPrescales>(iConfig.getParameter<edm::InputTag>("prescales"))),
	triggerEvent_(consumes<trigger::TriggerEvent>(iConfig.getParameter<edm::InputTag>("hltTrigger"))),
	jetToken_(consumes<pat::JetCollection>(iConfig.getParameter<edm::InputTag>("recoJets"))),
	hltPath_(iConfig.getParameter<std::string>("hltPath")),
	denomPath_(iConfig.getParameter<std::string>("denomPath")),
	numerPath_(iConfig.getParameter<std::string>("numerPath")),
	orPath_(iConfig.getParameter<std::string>("orPath"))
//	triggerBit_(consumes<vector<float>>(iConfig.getParameter<InputTag>("triggerBit"))),
//	triggerName_(consumes<vector<string>>(iConfig.getParameter<InputTag>("triggerName")))
{
//	baseTrigger = cms.string('HLT_PFHT475');
//	triggerPass = cms.vstring( ['HLT_AK8PFHT700_TrimR0p1PT0p03Mass50'] ),
	baseTrigger = "HLT_PFHT475";
	triggerPass.push_back("HLT_AK8PFHT650_TrimR0p1PT0p03Mass50");
}

void RUNTriggerValidation::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

	edm::Handle<edm::TriggerResults> triggerBits;
	edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects;
	edm::Handle<pat::PackedTriggerPrescales> triggerPrescales;
	edm::Handle<trigger::TriggerEvent> trigEvent; 
	edm::Handle<pat::JetCollection> jets;

	iEvent.getByToken(triggerBits_, triggerBits);
	iEvent.getByToken(triggerObjects_, triggerObjects);
	iEvent.getByToken(triggerPrescales_, triggerPrescales);
	iEvent.getByToken(triggerEvent_,trigEvent);
	iEvent.getByToken(jetToken_, jets);

/*
	Handle<vector<float> > triggerBit;
	Event.getByToken(triggerBit_, triggerBit);

	Handle<vector<string> > triggerName;
	iEvent.getByToken(triggerName_, triggerName);
*/


	const edm::TriggerNames &names = iEvent.triggerNames(*triggerBits);
	triggerBitInt = -1;
  	bool pathFound = 0;
  	bool basedTriggerFired = 0;
  	bool ORTriggers = 0;
	std::string triggerNameVal;
	std::vector<std::string> triggerNamesVector;
	for (unsigned int i = 0, n = triggerBits->size(); i < n; ++i) {
		if (TString(names.triggerName(i)).Contains(hltPath_) && (triggerBits->accept(i))) {
			triggerBitInt = i;
			pathFound=1;
			triggerNameVal = names.triggerName(i);
			triggerNamesVector.push_back(triggerNameVal);
			//std::cout << "\n === TRIGGER PATHS === " << std::endl;
			//std::cout << "Trigger " << names.triggerName(i) << ", prescale " << triggerPrescales->getPrescaleForIndex(i) << ": " << (triggerBits->accept(i) ? "PASS" : "fail (or not run)") << std::endl;
		}
		if (TString(names.triggerName(i)).Contains(denomPath_) && (triggerBits->accept(i))) {
			basedTriggerFired = 1;
		}
		if (   (TString(names.triggerName(i)).Contains(numerPath_) || TString(names.triggerName(i)).Contains(orPath_)) && (triggerBits->accept(i))) {
			ORTriggers = 1;
		}
	}

	double HT = 0;
	int k = 0;
	if (pathFound) {
		//std::cout << "\n === TRIGGER OBJECTS === " << std::endl;
		double hltHT = 0;
		double hlttrimmedMass = 0;
		int numJets = 0;
		for (pat::TriggerObjectStandAlone obj : *triggerObjects) { // note: not "const &" since we want to call unpackPathNames
			obj.unpackPathNames(names);
			if ( TString(obj.collection()).Contains("hltAK8PFJetsTrimR0p1PT0p03") ) {
				//std::cout << "\tTrigger object Trimmed Mass:  pt " << obj.pt() << ", eta " << obj.eta() << ", phi " << obj.phi() << ", mass " << obj.mass() << std::endl;
				hlttrimmedMass = obj.mass();
				numJets++;
				histos1D_[ "hltTrimmedMass" ]->Fill( obj.mass() );
			}
			if ( TString(obj.collection()).Contains("hltAK8PFHT") ) {
				for (unsigned h = 0; h < obj.filterIds().size(); ++h) {
					if (obj.filterIds()[h] == 89 ) {
						hltHT = obj.pt();
						histos1D_[ "hltHT" ]->Fill( obj.pt() );
						//std::cout << "\tTrigger object HT:  pt " << obj.pt() << ", eta " << obj.eta() << ", phi " << obj.phi() << ", mass " << obj.mass() << std::endl;
					}
				}
			}
		}
		if ( hltHT > 0 ) histos2D_[ "hltTrimmedMassvsHT" ]->Fill( hlttrimmedMass, hltHT );
		if ( numJets > 0 ) histos1D_[ "hltNumJetsTrimmedMass" ]->Fill( numJets );

		for (unsigned int k = 0; k < jets->size(); k++) {
			HT += jets->at(k).pt();
		}
		for (const pat::Jet &jet : *jets) {
		//for (unsigned int k = 0; k < jets->size(); k++) {
			if (k==0){
				histos1D_[ "jet1Mass" ]->Fill( jet.mass() );
				histos1D_[ "jet1TrimmedMass" ]->Fill( jet.userFloat( "ak8PFJetsCHSTrimmedMass" ) );
				histos1D_[ "jet1PrunedMass" ]->Fill( jet.userFloat( "ak8PFJetsCHSPrunedMass" ) );
				histos1D_[ "jet1Pt" ]->Fill( jet.pt() );
			}
			if (k==1){
				histos1D_[ "jet2Mass" ]->Fill( jet.mass() );
				histos1D_[ "jet2TrimmedMass" ]->Fill( jet.userFloat( "ak8PFJetsCHSTrimmedMass" ) );
				histos1D_[ "jet2PrunedMass" ]->Fill( jet.userFloat( "ak8PFJetsCHSPrunedMass" ) );
				histos1D_[ "jet2Pt" ]->Fill( jet.pt() );
			}
		k++;
		}
		if ( HT > 0 ) histos1D_[ "HT" ]->Fill( HT );
	}
	HT = 0;
	k=0;
	for (unsigned int k = 0; k < jets->size(); k++) {
		HT += jets->at(k).pt();
	}
	for (const pat::Jet &jet : *jets) {
	//for (unsigned int k = 0; k < jets->size(); k++) {
		if ( basedTriggerFired ) {
			if (k==0){
				histos1D_[ "jet1MassDenom_cutDijet" ]->Fill( jet.userFloat( "ak8PFJetsCHSPrunedMass" )  );
				histos1D_[ "jetLeadMassDenom_cutDijet" ]->Fill( jet.mass()  );
				histos1D_[ "jet1PtDenom_cutDijet" ]->Fill( jet.pt()   );
				histos2D_[ "jet1PtHTDenom_cutDijet" ]->Fill( jet.pt(), HT );
					
					if ( ORTriggers ){
						histos1D_[ "jet1MassPassing_cutDijet" ]->Fill( jet.userFloat( "ak8PFJetsCHSPrunedMass" )  );
						histos1D_[ "jetLeadMassPassing_cutDijet" ]->Fill( jet.mass()  );
						histos1D_[ "jet1PtPassing_cutDijet" ]->Fill( jet.pt()   );
						histos2D_[ "jet1PtHTPassing_cutDijet" ]->Fill( jet.pt(), HT );
					}
			}
			if (k==1){
				histos1D_[ "jet2PtDenom_cutDijet" ]->Fill( jet.pt()   );
				histos2D_[ "jet2PtHTDenom_cutDijet" ]->Fill( jet.pt(), HT );
					
					if ( ORTriggers ){
						histos1D_[ "jet2PtPassing_cutDijet" ]->Fill( jet.pt()   );
						histos2D_[ "jet2PtHTPassing_cutDijet" ]->Fill( jet.pt(), HT );
					}
			}
			histos1D_[ "trimmedMassDenom_cutDijet" ]->Fill( jet.userFloat( "ak8PFJetsCHSTrimmedMass" )  );
			histos1D_[ "HTDenom_cutDijet" ]->Fill( HT  );
			histos2D_[ "jetMassHTDenom_cutDijet" ]->Fill( jet.userFloat( "ak8PFJetsCHSPrunedMass" ), HT );
			histos2D_[ "jetTrimmedMassHTDenom_cutDijet" ]->Fill( jet.userFloat( "ak8PFJetsCHSTrimmedMass" ), HT );

			if ( ORTriggers ){
				histos1D_[ "trimmedMassPassing_cutDijet" ]->Fill( jet.userFloat( "ak8PFJetsCHSTrimmedMass" )  );
				histos1D_[ "HTPassing_cutDijet" ]->Fill( HT  );
				histos2D_[ "jetMassHTPassing_cutDijet" ]->Fill( jet.userFloat( "ak8PFJetsCHSPrunedMass" ), HT );
				histos2D_[ "jetTrimmedMassHTPassing_cutDijet" ]->Fill( jet.userFloat( "ak8PFJetsCHSTrimmedMass" ), HT );
			}
		}
	k++;
	}
}

void RUNTriggerValidation::beginJob() {

	histos1D_[ "hltTrimmedMass" ] = fs_->make< TH1D >( "hltTrimmedMass", "hltTrimmedMass", 100, 0., 1000. );
	histos1D_[ "hltTrimmedMass" ]->Sumw2();
	histos1D_[ "hltNumJetsTrimmedMass" ] = fs_->make< TH1D >( "hltNumJetsTrimmedMass", "hltNumJetsTrimmedMass", 10, 0., 10. );
	histos1D_[ "hltNumJetsTrimmedMass" ]->Sumw2();
	histos1D_[ "hltHT" ] = fs_->make< TH1D >( "hltHT", "hltHT", 100, 0., 2000. );
	histos1D_[ "hltHT" ]->Sumw2();
	histos1D_[ "jet1Mass" ] = fs_->make< TH1D >( "jet1Mass", "jet1Mass", 100, 0., 1000. );
	histos1D_[ "jet1Mass" ]->Sumw2();
	histos1D_[ "jet1TrimmedMass" ] = fs_->make< TH1D >( "jet1TrimmedMass", "jet1TrimmedMass", 100, 0., 1000. );
	histos1D_[ "jet1TrimmedMass" ]->Sumw2();
	histos1D_[ "jet1PrunedMass" ] = fs_->make< TH1D >( "jet1PrunedMass", "jet1PrunedMass", 100, 0., 1000. );
	histos1D_[ "jet1PrunedMass" ]->Sumw2();
	histos1D_[ "jet1Pt" ] = fs_->make< TH1D >( "jet1Pt", "jet1Pt", 100, 0., 1000. );
	histos1D_[ "jet1Pt" ]->Sumw2();
	histos1D_[ "jet2Mass" ] = fs_->make< TH1D >( "jet2Mass", "jet2Mass", 100, 0., 1000. );
	histos1D_[ "jet2Mass" ]->Sumw2();
	histos1D_[ "jet2TrimmedMass" ] = fs_->make< TH1D >( "jet2TrimmedMass", "jet2TrimmedMass", 100, 0., 1000. );
	histos1D_[ "jet2TrimmedMass" ]->Sumw2();
	histos1D_[ "jet2PrunedMass" ] = fs_->make< TH1D >( "jet2PrunedMass", "jet2PrunedMass", 100, 0., 1000. );
	histos1D_[ "jet2PrunedMass" ]->Sumw2();
	histos1D_[ "jet2Pt" ] = fs_->make< TH1D >( "jet2Pt", "jet2Pt", 100, 0., 1000. );
	histos1D_[ "jet2Pt" ]->Sumw2();
	histos1D_[ "HT" ] = fs_->make< TH1D >( "HT", "HT", 100, 0., 2000. );
	histos1D_[ "HT" ]->Sumw2();

	histos2D_[ "hltTrimmedMassvsHT" ] = fs_->make< TH2D >( "hltTrimmedMassvsHT", "hltTrimmedMassvsHT", 100, 0., 1000., 100, 0., 2000. );
	histos2D_[ "hltTrimmedMassvsHT" ]->Sumw2();



	histos1D_[ "HTDenom_cutDijet" ] = fs_->make< TH1D >( "HTDenom_cutDijet", "HTDenom_cutDijet", 150, 0., 1500. );
	histos1D_[ "HTDenom_cutDijet" ]->Sumw2();
	histos1D_[ "HTPassing_cutDijet" ] = fs_->make< TH1D >( "HTPassing_cutDijet", "HTPassing_cutDijet", 150, 0., 1500. );
	histos1D_[ "HTPassing_cutDijet" ]->Sumw2();

	histos1D_[ "trimmedMassDenom_cutDijet" ] = fs_->make< TH1D >( "trimmedMassDenom_cutDijet", "trimmedMassDenom_cutDijet", 60, 0., 600. );
	histos1D_[ "trimmedMassDenom_cutDijet" ]->Sumw2();
	histos1D_[ "trimmedMassPassing_cutDijet" ] = fs_->make< TH1D >( "trimmedMassPassing_cutDijet", "trimmedMassPassing_cutDijet", 60, 0., 600. );
	histos1D_[ "trimmedMassPassing_cutDijet" ]->Sumw2();

	histos1D_[ "jet1PtDenom_cutDijet" ] = fs_->make< TH1D >( "jet1PtDenom_cutDijet", "jet1PtDenom_cutDijet", 100, 0., 1000. );
	histos1D_[ "jet1PtDenom_cutDijet" ]->Sumw2();
	histos1D_[ "jet1PtPassing_cutDijet" ] = fs_->make< TH1D >( "jet1PtPassing_cutDijet", "jet1PtPassing_cutDijet", 100, 0., 1000. );
	histos1D_[ "jet1PtPassing_cutDijet" ]->Sumw2();

	histos1D_[ "jet2PtDenom_cutDijet" ] = fs_->make< TH1D >( "jet2PtDenom_cutDijet", "jet2PtDenom_cutDijet", 100, 0., 1000. );
	histos1D_[ "jet2PtDenom_cutDijet" ]->Sumw2();
	histos1D_[ "jet2PtPassing_cutDijet" ] = fs_->make< TH1D >( "jet2PtPassing_cutDijet", "jet2PtPassing_cutDijet", 100, 0., 1000. );
	histos1D_[ "jet2PtPassing_cutDijet" ]->Sumw2();

	histos1D_[ "jet1MassDenom_cutDijet" ] = fs_->make< TH1D >( "jet1MassDenom_cutDijet", "jet1MassDenom_cutDijet", 60, 0., 600. );
	histos1D_[ "jet1MassDenom_cutDijet" ]->Sumw2();
	histos1D_[ "jet1MassPassing_cutDijet" ] = fs_->make< TH1D >( "jet1MassPassing_cutDijet", "jet1MassPassing_cutDijet", 60, 0., 600. );
	histos1D_[ "jet1MassPassing_cutDijet" ]->Sumw2();

	histos1D_[ "jetLeadMassDenom_cutDijet" ] = fs_->make< TH1D >( "jetLeadMassDenom_cutDijet", "jetLeadMassDenom_cutDijet", 60, 0., 600. );
	histos1D_[ "jetLeadMassDenom_cutDijet" ]->Sumw2();
	histos1D_[ "jetLeadMassPassing_cutDijet" ] = fs_->make< TH1D >( "jetLeadMassPassing_cutDijet", "jetLeadMassPassing_cutDijet", 60, 0., 600. );
	histos1D_[ "jetLeadMassPassing_cutDijet" ]->Sumw2();

	histos2D_[ "jet1PtHTDenom_cutDijet" ] = fs_->make< TH2D >( "jet1PtHTDenom_cutDijet", "HT vs Leading Jet Pt", 60, 0., 600., 150, 0., 1500.);
	histos2D_[ "jet1PtHTDenom_cutDijet" ]->SetYTitle( "HT [GeV]" );
	histos2D_[ "jet1PtHTDenom_cutDijet" ]->SetXTitle( "Leading Jet Pruned Pt [GeV]" );
	histos2D_[ "jet1PtHTDenom_cutDijet" ]->Sumw2();

	histos2D_[ "jet1PtHTPassing_cutDijet" ] = fs_->make< TH2D >( "jet1PtHTPassing_cutDijet", "HT vs Leading Jet Pt", 60, 0., 600., 150, 0., 1500.);
	histos2D_[ "jet1PtHTPassing_cutDijet" ]->SetYTitle( "HT [GeV]" );
	histos2D_[ "jet1PtHTPassing_cutDijet" ]->SetXTitle( "Leading Jet Pruned Pt [GeV]" );
	histos2D_[ "jet1PtHTPassing_cutDijet" ]->Sumw2();

	histos2D_[ "jet2PtHTDenom_cutDijet" ] = fs_->make< TH2D >( "jet2PtHTDenom_cutDijet", "HT vs Leading Jet Pt", 60, 0., 600., 150, 0., 1500.);
	histos2D_[ "jet2PtHTDenom_cutDijet" ]->SetYTitle( "HT [GeV]" );
	histos2D_[ "jet2PtHTDenom_cutDijet" ]->SetXTitle( "Leading Jet Pruned Pt [GeV]" );
	histos2D_[ "jet2PtHTDenom_cutDijet" ]->Sumw2();

	histos2D_[ "jet2PtHTPassing_cutDijet" ] = fs_->make< TH2D >( "jet2PtHTPassing_cutDijet", "HT vs 2nd Leading Jet Pt", 60, 0., 600., 150, 0., 1500.);
	histos2D_[ "jet2PtHTPassing_cutDijet" ]->SetYTitle( "HT [GeV]" );
	histos2D_[ "jet2PtHTPassing_cutDijet" ]->SetXTitle( "2nd Leading Jet Pruned Pt [GeV]" );
	histos2D_[ "jet2PtHTPassing_cutDijet" ]->Sumw2();

	histos2D_[ "jetMassHTDenom_cutDijet" ] = fs_->make< TH2D >( "jetMassHTDenom_cutDijet", "HT vs 2nd Leading Jet Mass", 60, 0., 600., 150, 0., 1500.);
	histos2D_[ "jetMassHTDenom_cutDijet" ]->SetYTitle( "HT [GeV]" );
	histos2D_[ "jetMassHTDenom_cutDijet" ]->SetXTitle( "2nd Leading Jet Pruned Mass [GeV]" );
	histos2D_[ "jetMassHTDenom_cutDijet" ]->Sumw2();

	histos2D_[ "jetMassHTPassing_cutDijet" ] = fs_->make< TH2D >( "jetMassHTPassing_cutDijet", "HT vs Leading Jet Mass", 60, 0., 600., 150, 0., 1500.);
	histos2D_[ "jetMassHTPassing_cutDijet" ]->SetYTitle( "HT [GeV]" );
	histos2D_[ "jetMassHTPassing_cutDijet" ]->SetXTitle( "Leading Jet Pruned Mass [GeV]" );
	histos2D_[ "jetMassHTPassing_cutDijet" ]->Sumw2();

	histos2D_[ "jetTrimmedMassHTDenom_cutDijet" ] = fs_->make< TH2D >( "jetTrimmedMassHTDenom_cutDijet", "HT vs Leading Jet Mass", 60, 0., 600., 150, 0., 1500.);
	histos2D_[ "jetTrimmedMassHTDenom_cutDijet" ]->SetYTitle( "HT [GeV]" );
	histos2D_[ "jetTrimmedMassHTDenom_cutDijet" ]->SetXTitle( "Leading Jet Trimmed Mass [GeV]" );
	histos2D_[ "jetTrimmedMassHTDenom_cutDijet" ]->Sumw2();

	histos2D_[ "jetTrimmedMassHTPassing_cutDijet" ] = fs_->make< TH2D >( "jetTrimmedMassHTPassing_cutDijet", "HT vs Leading Jet Mass", 60, 0., 600., 150, 0., 1500.);
	histos2D_[ "jetTrimmedMassHTPassing_cutDijet" ]->SetYTitle( "HT [GeV]" );
	histos2D_[ "jetTrimmedMassHTPassing_cutDijet" ]->SetXTitle( "Leading Jet Trimmed Mass [GeV]" );
	histos2D_[ "jetTrimmedMassHTPassing_cutDijet" ]->Sumw2();













}







//define this as a plug-in
DEFINE_FWK_MODULE(RUNTriggerValidation);
