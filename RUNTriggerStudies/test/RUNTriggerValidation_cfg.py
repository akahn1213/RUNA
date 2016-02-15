import FWCore.ParameterSet.Config as cms

from FWCore.ParameterSet.VarParsing import VarParsing

###############################
####### Parameters ############
###############################

options = VarParsing ('python')

options.register('RUN', 
		'JetHT_Run2015C',
		VarParsing.multiplicity.singleton,
		VarParsing.varType.string,
		"name"
		)

options.register('local', 
		True,
		VarParsing.multiplicity.singleton,
		VarParsing.varType.bool,
		"Run locally or crab"
		)

options.parseArguments()

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

NAME = options.RUN

if options.local:
	process.load(NAME+'_cfi')
else:
	process.source = cms.Source("PoolSource",
	   fileNames = cms.untracked.vstring(
		   ##### 76X samples
		   #'/store/mc/RunIIFall15DR76/QCD_Pt-15to3000_TuneCUETP8M1_Flat_13TeV_pythia8/MINIAODSIM/25nsFlat10to25TSG_76X_mcRun2_asymptotic_v12-v1/00000/0AED6955-8B9A-E511-A6FF-0025907FD424.root',
		   #'/store/mc/RunIIFall15DR76/QCD_Pt-15to3000_TuneCUETP8M1_Flat_13TeV_pythia8/MINIAODSIM/25nsFlat10to25TSG_76X_mcRun2_asymptotic_v12-v1/00000/0C092B2C-A999-E511-B400-02163E00B0EB.root',
		   ##### miniAODv2 samples with 76X
		   #'/store/mc/RunIIFall15MiniAODv2/QCD_Pt-15to3000_TuneCUETP8M1_Flat_13TeV_pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/70000/0002078C-B0B9-E511-8907-0025905C431C.root',
		   #'/store/mc/RunIIFall15MiniAODv2/QCD_Pt-15to3000_TuneCUETP8M1_Flat_13TeV_pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/70000/0004527F-6BB9-E511-A522-001E67504255.root',
       		'/store/mc/RunIISpring15DR74/QCD_Pt-15to3000_TuneCUETP8M1_Flat_13TeV_pythia8/MINIAODSIM/HFscaleFlat10to30Asympt25ns_MCRUN2_74_V9-v1/10000/22041656-045F-E511-9683-003048FFD770.root',
       		'/store/mc/RunIISpring15DR74/QCD_Pt-15to3000_TuneCUETP8M1_Flat_13TeV_pythia8/MINIAODSIM/HFscaleFlat10to30Asympt25ns_MCRUN2_74_V9-v1/10000/220ECC54-045F-E511-A3D9-20CF3027A5CC.root',
       		'/store/mc/RunIISpring15DR74/QCD_Pt-15to3000_TuneCUETP8M1_Flat_13TeV_pythia8/MINIAODSIM/HFscaleFlat10to30Asympt25ns_MCRUN2_74_V9-v1/10000/22C134A3-035F-E511-BC96-0025905938D4.root',
	    )
	)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )


process.TFileService=cms.Service("TFileService",fileName=cms.string( 'RUNTriggerValidation_'+NAME+'.root' ) )

process.AK8PFHT650TrimMass50 = cms.EDAnalyzer('RUNTriggerValidation',
		bits = cms.InputTag("TriggerResults","","HLT"),
		prescales = cms.InputTag("patTrigger"),
		objects = cms.InputTag("selectedPatTrigger"),
		hltPath = cms.string("HLT_AK8PFHT650_TrimR0p1PT0p03Mass50"),
		denomPath = cms.string("HLT_PFHT475"),
		numerPath = cms.string("HLT_AK8PFHT650_TrimR0p1PT0p03Mass50"),
		orPath = cms.string("HLT_PFHT800"),
		hltTrigger = cms.InputTag("hltTriggerSummaryAOD","","HLT"),
		recoJets = cms.InputTag("slimmedJetsAK8")
)

#process.AK8PFHT650TrimMass50 = process.AK8PFHT700TrimMass50.clone( 
#process.AK8PFHT650TrimMass50 = cms.EDAnalyzer('RUNTriggerValidation', 
#		hltPath = cms.string("HLT_AK8PFHT650_TrimR0p1PT0p03Mass50"),
#		numerPath = cms.string("HLT_AK8PFHT650_TrimR0p1PT0p03Mass50"),
#		baseTrigger		= cms.string('HLT_PFHT475'),
#		triggerPass		= cms.vstring( ['HLT_AK8PFHT650_TrimR0p1PT0p03Mass50'] )
#		)


process.p = cms.Path(
		process.AK8PFHT650TrimMass50
#		 process.AK8PFHT650TrimMass50
		)
#process.p = cms.Path(
#		process.AK8PFHT650TrimMass50
#		)

process.MessageLogger.cerr.FwkReport.reportEvery = 10000
