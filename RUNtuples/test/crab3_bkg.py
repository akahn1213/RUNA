##################################################################
########   TO RUN THIS: python crab3_QCD.py
########   DO NOT DO: crab submit crab3_QCD.py
##################################################################

from CRABClient.UserUtilities import config
from httplib import HTTPException
config = config()

name = 'RunIISpring15DR74_RUNA_Asympt25ns'
version = 'v03p1'

config.General.requestName = ''
config.General.workArea = 'crab_projects'

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'RUNtuples_cfg.py'
config.JobType.allowUndistributedCMSSW = True

config.Data.inputDataset = ''
config.Data.splitting = 'LumiBased'
config.Data.publication = True
config.Data.ignoreLocality = True
config.Data.publishDataName = name+'_'+version

config.Site.storageSite = 'T3_US_FNALLPC'

def submit(config):

	try:
		crabCommand('submit', config = config)
	except HTTPException, hte:
		print 'Cannot execute commend'
		print hte.headers

if __name__ == '__main__':

	from CRABAPI.RawCommand import crabCommand

	Samples = [ 
			### CSA14 samples
			#'/QCD_Pt-80to120_Tune4C_13TeV_pythia8/Spring14miniaod-141029_PU40bx50_castor_PLS170_V6AN2-v1/MINIAODSIM',
			#'/QCD_Pt-120to170_Tune4C_13TeV_pythia8/Spring14miniaod-141029_PU40bx50_castor_PLS170_V6AN2-v1/MINIAODSIM',
			#'/QCD_Pt-170to300_Tune4C_13TeV_pythia8/Spring14miniaod-141029_PU40bx50_castor_PLS170_V6AN2-v1/MINIAODSIM',
			#'/QCD_Pt-300to470_Tune4C_13TeV_pythia8/Spring14miniaod-141029_PU40bx50_castor_PLS170_V6AN2-v1/MINIAODSIM',
			#'/QCD_Pt-470to600_Tune4C_13TeV_pythia8/Spring14miniaod-141029_PU40bx50_castor_PLS170_V6AN2-v1/MINIAODSIM',
			#'/QCD_Pt-600to800_Tune4C_13TeV_pythia8/Spring14miniaod-141029_PU40bx50_castor_PLS170_V6AN2-v1/MINIAODSIM',
			#'/QCD_Pt-800to1000_Tune4C_13TeV_pythia8/Spring14miniaod-141029_PU40bx50_castor_PLS170_V6AN2-v1/MINIAODSIM',
			###### PHYS14
			#'/QCD_Pt-170to300_Tune4C_13TeV_pythia8/Phys14DR-PU20bx25_trkalmb_castor_PHYS14_25_V1-v2/MINIAODSIM',
			#'/QCD_Pt-300to470_Tune4C_13TeV_pythia8/Phys14DR-PU20bx25_trkalmb_castor_PHYS14_25_V1-v2/MINIAODSIM',
			#'/QCD_Pt-470to600_Tune4C_13TeV_pythia8/Phys14DR-PU20bx25_trkalmb_castor_PHYS14_25_V1-v2/MINIAODSIM',
			#'/QCD_Pt-600to800_Tune4C_13TeV_pythia8/Phys14DR-PU20bx25_trkalmb_castor_PHYS14_25_V1-v1/MINIAODSIM',
			#'/QCD_Pt-800to1000_Tune4C_13TeV_pythia8/Phys14DR-PU20bx25_trkalmb_castor_PHYS14_25_V1-v2/MINIAODSIM',
			#'/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/Phys14DR-PU20bx25_trkalmb_castor_PHYS14_25_V1-v1/MINIAODSIM',
			#'/QCD_Pt-1400to1800_Tune4C_13TeV_pythia8/Phys14DR-PU20bx25_trkalmb_castor_PHYS14_25_V1-v1/MINIAODSIM',

			#'/QCD_HT-100To250_13TeV-madgraph/Phys14DR-PU20bx25_PHYS14_25_V1-v1/MINIAODSIM',
			#'/QCD_HT_250To500_13TeV-madgraph/Phys14DR-PU20bx25_PHYS14_25_V1-v1/MINIAODSIM',
			#'/QCD_HT-500To1000_13TeV-madgraph/Phys14DR-PU20bx25_PHYS14_25_V1-v1/MINIAODSIM',
			#'/QCD_HT-500To1000_13TeV-madgraph/Phys14DR-PU20bx25_PHYS14_25_V1_ext1-v1/MINIAODSIM',
			#'/QCD_HT_1000ToInf_13TeV-madgraph/Phys14DR-PU20bx25_PHYS14_25_V1-v1/MINIAODSIM',
			#'/QCD_HT_1000ToInf_13TeV-madgraph/Phys14DR-PU20bx25_PHYS14_25_V1_ext1-v1/MINIAODSIM'

			#### RunIISpring15DR74 Asympt50ns
			#'/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v2/MINIAODSIM',
			#'/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v2/MINIAODSIM',
			#'/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v2/MINIAODSIM',

			#### RunIISpring15DR74 Asympt25ns
			##'/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v3/MINIAODSIM',
			##'/QCD_Pt_120to170_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM',
			#'/QCD_Pt_170to300_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/MINIAODSIM',
			#'/QCD_Pt_170to300_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25nsRecodebug_MCRUN2_74_V9-v1/MINIAODSIM',
			#'/QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM',
			#'/QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25nsRecodebug_MCRUN2_74_V9-v1/MINIAODSIM',
			#'/QCD_Pt_470to600_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/MINIAODSIM',
			#'/QCD_Pt_470to600_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25nsRecodebug_MCRUN2_74_V9-v1/MINIAODSIM',
			#'/QCD_Pt_600to800_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25nsRecodebug_MCRUN2_74_V9-v1/MINIAODSIM',
			#'/QCD_Pt_600to800_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v3/MINIAODSIM',
			#'/QCD_Pt_800to1000_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/MINIAODSIM',
			#'/QCD_Pt_800to1000_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25nsRecodebug_MCRUN2_74_V9-v1/MINIAODSIM',
			#'/QCD_Pt_1000to1400_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM',
			#'/QCD_Pt_1000to1400_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25nsRecodebug_MCRUN2_74_V9-v1/MINIAODSIM',
			#'/QCD_Pt_1400to1800_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM',
			#'/QCD_Pt_1800to2400_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM',
			##'/QCD_Pt_2400to3200_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM',
			##'/QCD_Pt_3200toInf_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM',
			##'/ST_t-channel_5f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM',
			#'/TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM',
			##'/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/MINIAODSIM',
			##'/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM',
			##'/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM',
			##'/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM',
			##'/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v3/MINIAODSIM',
			##'/WJetsToLNu_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM',
			#'/WJetsToQQ_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/MINIAODSIM',
			#'/ZJetsToQQ_HT600toInf_13TeV-madgraph/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM',
			#'/JetHT/Run2015B-PromptReco-v1/MINIAOD',
			'/JetHT/Run2015C-PromptReco-v1/MINIAOD',
			##'/MET/Run2015B-PromptReco-v1/MINIAOD',
			##'/SingleMu/Run2015B-PromptReco-v1/MINIAOD',
			]
	
	from multiprocessing import Process
	for dataset in Samples:
		config.Data.inputDataset = dataset
		config.General.requestName = dataset.split('/')[1]+"_"+dataset.split('/')[2]+'_'+name+'_'+version
		if 'Run2015' in dataset: 
			config.JobType.pyCfgParams = [ 'isData=1', 'globalTag=74X_dataRun2_v2' ]
			config.Data.publishDataName = dataset.split('/')[2]+'_'+name+'_'+version
			if 'Run2015B' in dataset: config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions15/13TeV/Cert_246908-255031_13TeV_PromptReco_Collisions15_50ns_JSON.txt'
			elif 'Run2015C' in dataset: config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions15/13TeV/Cert_246908-255031_13TeV_PromptReco_Collisions15_25ns_JSON_v2.txt'
		elif 'Asympt50ns' in dataset: config.JobType.pyCfgParams = [ 'globalTag=74X_mcRun2_startup_v2' ]  
		elif 'Asympt25ns' in dataset: config.JobType.pyCfgParams = [ 'globalTag=74X_mcRun2_asymptotic_v2' ]  
		if 'TTJets' in dataset: config.Data.unitsPerJob = 100
		else: config.Data.unitsPerJob = 10
		p = Process(target=submit, args=(config,))
		p.start()
		p.join()
