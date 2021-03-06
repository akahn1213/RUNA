#!/usr/bin/env python
'''
File: DrawHistogram.py
Author: Alejandro Gomez Espinosa
Email: gomez@physics.rutgers.edu
Description: My Draw histograms. Check for options at the end.
'''

#from ROOT import TFile, TH1F, THStack, TCanvas, TMath, gROOT, gPad
from ROOT import *
from tdrstyle import setSelection
import time, os, math, sys
import CMS_lumi, tdrstyle
import argparse


gROOT.Reset()
gROOT.SetBatch()
#setTDRStyle()
#gROOT.SetStyle('tdrStyle')
#set the tdr style
gROOT.ForceStyle()
tdrstyle.setTDRStyle()
#CMS_lumi.writeExtraText = 1
#CMS_lumi.extraText = ""


gStyle.SetOptStat(0)

def labels( name, PU, camp, X=0.92, Y=0.50, align='right', listSet=[] ):
	if 'cutHT' in name: setSelection( [ camp, PU, triggerUsed, 'jet p_{T} > 150 GeV', 'jet |#eta| < 2.4', 'HT > 800 GeV' ] , X, Y, align)
	elif 'cutDijet' in name: setSelection( [ camp, PU, triggerUsed, 'jet p_{T} > 150 GeV', 'jet |#eta| < 2.4', 'HT > 800 GeV', 'numJets > 1' ] , X, Y, align)
	elif ( 'cutAsym' in name ) or ('cutMassAsym' in name): setSelection( [ camp, PU, triggerUsed, 'HT > 800 GeV', 'numJets > 1', 'A < 0.1' ], X, Y, align )
	elif 'cutTau21' in name: setSelection( [ camp, PU, triggerUsed, 'HT > 800 GeV', 'numJets > 1', 'A < 0.1', '#tau_{21} < 0.5'],  X, Y, align )
	elif 'cutCosTheta' in name: setSelection( [ camp, PU, triggerUsed,  'HT > 800 GeV', 'numJets > 1','A < 0.1', '#tau_{21} < 0.5', '|cos(#theta*)| < 0.4'], X, Y, align )
	elif 'cutDEta' in name: setSelection( [ camp, PU, triggerUsed,  'HT > 800 GeV', 'numJets > 1','A < 0.1, #tau_{21} < 0.5', '|cos(#theta*)| < 0.4', '#Delta #eta (j^{1},j^{2}) > 1'], X, Y, align )
	elif 'cutBtag' in name: setSelection( [ camp, PU, triggerUsed,  'HT > 800 GeV', 'numJets > 1','A < 0.1, #tau_{21} < 0.5', '|cos(#theta*)| < 0.4', '#Delta #eta (j^{1},j^{2}) > 1', 'num Btag = 1'], X, Y, align )
	#elif 'cutSubjetPtRatio' in name: setSelection( [ camp, PU, triggerUsed,  'HT > 800 GeV', 'numJets > 1','A < 0.1', '|cos(#theta*)| < 0.3', 'subjet pt ratio > 0.3'],  X, Y, align )
	elif 'cutBtagAfterSubjetPtRatio' in name: setSelection( [ camp, PU, triggerUsed,  'HT > 800 GeV', 'numJets > 1','A < 0.1', '|cos(#theta*)| < 0.3', 'subjet pt ratio > 0.3', '1 btag CSVM'],  X, Y+0.05, align )
	elif 'Standard' in name: setSelection( [ camp, PU, triggerUsed, 'HT > 800 GeV', 'numJets > 1', 'A < 0.1', '|cos(#theta*)| < 0.3', 'subjet pt ratio > 0.3'],  X, Y, align )
	elif 'PFHT800' in name: setSelection( [ camp, PU, 'PFHT800', 'HT > 800 GeV', 'numJets > 1', 'A < 0.1', '|cos(#theta*)| < 0.3', 'subjet pt ratio > 0.3'],  X, Y, align )
	elif 'Brock' in name: setSelection( [ camp, PU, 'HT > 1600 TeV', 'HT > 800 GeV', 'numJets > 1', 'A < 0.1', '|cos(#theta*)| < 0.3', 'subjet pt ratio > 0.3'],  X, Y, align )
	elif 'cutTau31' in name: setSelection( [ camp, PU, triggerUsed, 'HT > 800 GeV', 'numJets > 1', 'A < 0.1', '|cos(#theta*)| < 0.3', '#tau_{31} < 0.4'],  X, Y, align )
	elif 'triggerDATA' in name: setSelection(  [ 'Eff. (AK8 H_{T} > 700 GeV, trimmed AK8 jet mass > 50 GeV)'], X, Y, align )
	#elif 'triggerSignal' in name: setSelection(  [ 'RPV Stop 100 GeV', triggerUsed.replace('650', '650TrimMass50')], X, Y, align )
	elif 'triggerSignal' in name: setSelection(  [ 'pp #rightarrow #tilde{t}(jj) #tilde{t}(jj), M(#tilde{t}) = 100 GeV', 'Eff. (AK8 H_{T} > 650 GeV, trimmed AK8 jet mass > 50 GeV)'], X, Y, align )
	elif 'trigger' in name: setSelection( [ 'pp #rightarrow #tilde{t}(jj) #tilde{t}(jj), M(#tilde{t}) = 100 GeV', 'AK4 H_{T} > 800 GeV AND', 'AK8 H_{T} > 650 GeV, trimmed AK8 jet mass > 50 GeV' ], X, Y, align) 
	#elif 'trigger' in name: setSelection( [ 'pp #rightarrow #tilde{t}(jj) #tilde{t}(jj), M(#tilde{t}) = 100 GeV', 'AK4 H_{T} > 800 GeV' ], X, Y, align) 
	#elif 'trigger' in name: setSelection( [ 'pp #rightarrow #tilde{t}(jj) #tilde{t}(jj), M(#tilde{t}) = 100 GeV', 'AK8 H_{T} > 650 GeV, trimmed AK8 jet mass > 50 GeV' ], X, Y, align) 
	#elif 'rigger' in name: setSelection( [ 'pp #rightarrow #tilde{t}(jj) #tilde{t}(jj), M(#tilde{t}) = 100 GeV', 'NO Trigger' ], X, Y, align) 
	else: setSelection( '', X, Y, align) 

def labelAxis(name, histo, Grom ):

	if 'massAve' in name: 
		if 'Trimmed' in Grom: histo.GetXaxis().SetTitle( 'Average Trimmed Mass [GeV]' )
		elif 'Pruned' in Grom: histo.GetXaxis().SetTitle( 'Average Pruned Mass [GeV]' )
		elif 'Filtered' in Grom: histo.GetXaxis().SetTitle( 'Average Filtered Mass [GeV]' )
		else: histo.GetXaxis().SetTitle( 'Average Mass [GeV]' )
	elif 'TrimmedMass' in name: histo.GetXaxis().SetTitle( 'Leading Trimmed Jet Mass [GeV]' )
	elif 'massAsymmetry' in name: histo.GetXaxis().SetTitle( 'Mass Asymmetry (A)' )
	elif 'cosThetaStar' in name: histo.GetXaxis().SetTitle( 'cos(#theta *)' )
	elif 'jetEta' in name: histo.GetXaxis().SetTitle( 'Jet #eta' )
	elif 'Tau1_' in name: histo.GetXaxis().SetTitle( '#tau_{1}' )
	elif 'Tau2_' in name: histo.GetXaxis().SetTitle( '#tau_{2}' )
	elif 'Tau3_' in name: histo.GetXaxis().SetTitle( '#tau_{3}' )
	elif 'Tau21_' in name: histo.GetXaxis().SetTitle( '#tau_{21} ' )
	elif 'Tau31_' in name: histo.GetXaxis().SetTitle( '#tau_{31} ' )
	elif 'Tau32_' in name: histo.GetXaxis().SetTitle( '#tau_{32} ' )
	elif 'PtRatio_' in name: histo.GetXaxis().SetTitle( 'Subjet Pt_{2}/Pt_{1}' )
	elif 'Mass21' in name: histo.GetXaxis().SetTitle( 'Subjet m_{2}/m_{1}' )
	elif '112Mass' in name: histo.GetXaxis().SetTitle( 'Subjet m_{1}/m_{12}' )
	elif '212Mass' in name: histo.GetXaxis().SetTitle( 'Subjet m_{2}/m_{12}' )
	elif 'PolAngle13412_' in name: histo.GetXaxis().SetTitle( 'cos #psi_{1(34)}^{[12]}' )
	elif 'PolAngle31234_' in name: histo.GetXaxis().SetTitle( 'cos #psi_{3(12)}^{[34]}' )
	elif 'jetMass' in name: histo.GetXaxis().SetTitle( 'Jet Mass [GeV]' )
	elif 'jetPt' in name: histo.GetXaxis().SetTitle( 'Jet p_{T} [GeV]' )
	elif 'jet1Pt' in name: histo.GetXaxis().SetTitle( 'Leading Jet p_{T} [GeV]' )
	elif 'jet1Mass' in name: histo.GetXaxis().SetTitle( 'Leading Pruned Jet Mass [GeV]' )
	elif 'NPV' in name: histo.GetXaxis().SetTitle( 'Number of Primary Vertex' )
	elif 'HT' in name: histo.GetXaxis().SetTitle( 'HT [GeV]' )
	else: histo.GetXaxis().SetTitle( 'NO LABEL' )


def plot( inFileSignal, inFileSignal2, inFileQCD, kfactor, inFileTTJets, inFileWJets, inFileZJets, Grom, nameInRoot, name, xmin, xmax, labX, labY, log, PU, Norm=False ):
	"""docstring for plot"""

	outputFileName = name+'_'+Grom+'_RPVSt'+mass+'to'+jj+'_'+PU+'_PlusBkg_AnalysisPlots.pdf' 
	print 'Processing.......', outputFileName

	histos = {}
	histos[ 'Signal' ] = inFileSignal.Get( nameInRoot )
	histos[ 'Signal2' ] = inFileSignal2.Get( nameInRoot )
	histos[ 'QCD' ] = inFileQCD.Get( nameInRoot )
	histos[ 'QCD' ].Scale( kfactor )
	histos[ 'TTJets' ] = inFileTTJets.Get( nameInRoot )
	histos[ 'WJets' ] = inFileWJets.Get( nameInRoot )
	histos[ 'ZJets' ] = inFileZJets.Get( nameInRoot )

	hSignal = histos[ 'Signal' ].Clone()
	hBkg = histos[ 'QCD' ].Clone() 
	hBkg.Add( histos[ 'TTJets' ].Clone() )
	hBkg.Add( histos[ 'WJets' ].Clone() )
	hBkg.Add( histos[ 'ZJets' ].Clone() )
	hSignalBkg = histos[ 'Signal' ].Clone()
	hSignalBkg.Add( hBkg )
	hSignal.Divide( hSignalBkg )
	
	hSignal2 = histos[ 'Signal2' ].Clone()
	hSignal2Bkg = histos[ 'Signal2' ].Clone()
	hSignal2Bkg.Add( hBkg )
	hSignal2.Divide( hSignal2Bkg )
	#hSoSB = histos[ 'Signal' ].Clone()

	'''
	for bin in range(0,  hSoSB.GetNbinsX()):
		hSoSB.SetBinContent(bin, 0.)
		hSoSB.SetBinError(bin, 0.)

	hSoSB2 = hSoSB.Clone()
	for ibin in range(0, hSoSB.GetNbinsX()):
	
		binContSignal = histos[ 'Signal' ].GetBinContent(ibin)
		binErrSignal = histos[ 'Signal' ].GetBinError(ibin)
		binContBkg = histos[ 'QCD' ].GetBinContent(ibin) + histos[ 'TTJets' ].GetBinContent(ibin) + histos[ 'WJets' ].GetBinContent(ibin) + histos[ 'ZJets' ].GetBinContent(ibin)    
		binErrBkg = histos[ 'QCD' ].GetBinError(ibin)
		try:
			value = binContSignal / TMath.Sqrt( binContSignal + binContBkg )
		except ZeroDivisionError: continue
		hSoSB.SetBinContent( ibin, value )
	'''

	binWidth = histos['Signal'].GetBinWidth(1)

	legend=TLegend(0.60,0.60,0.90,0.87)
	legend.SetFillStyle(0)
	legend.SetTextSize(0.04)
	legend.AddEntry( histos[ 'Signal' ], 'RPV #tilde{t}#rightarrow '+jj+' '+mass+' GeV' , 'f' )
	legend.AddEntry( histos[ 'Signal2' ], 'RPV #tilde{t}#rightarrow '+jj+' 200 GeV' , 'l' )
	legend.AddEntry( histos[ 'QCD' ], 'QCD', 'f' )
	legend.AddEntry( histos[ 'TTJets' ], 't #bar{t} + Jets' , 'f' )
	legend.AddEntry( histos[ 'WJets' ], 'W + Jets' , 'f' )
	legend.AddEntry( histos[ 'ZJets' ], 'Z + Jets' , 'f' )

	if not Norm:
		tmpHisto = histos[ 'Signal' ].Clone()
		tmpHisto.SetLineColor(kRed-4)
		tmpHisto.SetFillColor(0)
		tmpHisto.SetLineWidth(3)
		tmpHisto.SetLineStyle(2)
		histos[ 'Signal2' ].SetLineColor(kRed-5)
		histos[ 'Signal2'].SetLineWidth(3)
		histos[ 'Signal2'].SetLineStyle(2)
		histos[ 'Signal' ].SetFillColor(kRed-4)
		histos[ 'Signal' ].SetFillStyle(1001)
		histos[ 'QCD' ].SetFillColor(kBlue-4)
		histos[ 'QCD' ].SetFillStyle(1001)
		histos[ 'TTJets' ].SetFillColor(kGreen-4)
		histos[ 'TTJets' ].SetFillStyle(1001)
		histos[ 'WJets' ].SetFillColor(kMagenta-4)
		histos[ 'WJets' ].SetFillStyle(1001)
		histos[ 'ZJets' ].SetFillColor(kOrange-4)
		histos[ 'ZJets' ].SetFillStyle(1001)

		stackHisto = THStack('stackHisto', 'stack')
		stackHisto.Add( histos['QCD'] )
		#stackHisto.Add( histos['TTJets'] )
		stackHisto.Add( histos['WJets'] )
		stackHisto.Add( histos['ZJets'] )
		stackHisto.Add( histos['Signal'] )

  		tdrStyle.SetPadRightMargin(0.05)
  		tdrStyle.SetPadLeftMargin(0.15)
		can = TCanvas('c1', 'c1',  10, 10, 750, 750 )
		pad1 = TPad("pad1", "Fit",0,0.207,1.00,1.00,-1)
		pad2 = TPad("pad2", "Pull",0,0.00,1.00,0.30,-1);
		pad1.Draw()
		pad2.Draw()

		pad1.cd()
		if log: 
			pad1.SetLogy()
			outName = outputFileName.replace('_AnalysisPlots','_Log_AnalysisPlots')
		else:
			outName = outputFileName 

		#stackHisto.SetMinimum(10)
		stackHisto.Draw('hist')
		#stackHisto.GetYaxis().SetTitleOffset(1.2)
		if xmax: stackHisto.GetXaxis().SetRangeUser( xmin, xmax )
		tmpHisto.Draw("hist same")
		histos['Signal2'].Draw('hist same')
		stackHisto.GetYaxis().SetTitle( 'Events / '+str(binWidth) )

		CMS_lumi.CMS_lumi(pad1, 4, 0)
		CMS_lumi.relPosX = 0.14
		#labelAxis( name, stackHisto, Grom )
		legend.Draw()
		if not (labX and labY): labels( name, PU, camp )
		else: labels( name, PU, camp, labX, labY )

		pad2.cd()
		pad2.SetGrid()
		pad2.SetTopMargin(0)
		pad2.SetBottomMargin(0.3)
		'''
		hSoSB.SetFillColor(48)
		hSoSB.SetFillStyle(1001)
		hSoSB.GetYaxis().SetTitle("S / #sqrt{S+B}")
		hSoSB.GetYaxis().SetLabelSize(0.12)
		hSoSB.GetXaxis().SetLabelSize(0.12)
		hSoSB.GetYaxis().SetTitleSize(0.12)
		hSoSB.GetYaxis().SetTitleOffset(0.45)
		#hSoSB.SetMaximum(0.7)
		hSoSB.Sumw2()
		if xmax: hSoSB.GetXaxis().SetRangeUser( xmin, xmax )
		hSoSB.Draw("hist")
		'''
		hSignal.SetFillColor(kRed+1)
		hSignal.SetFillStyle(1001)
		hSignal2.SetFillColor(kRed-5)
		hSignal2.SetFillStyle(1001)
		labelAxis( name, hSignal, Grom )
		hSignal.GetYaxis().SetTitleOffset(1.2)
		hSignal.GetXaxis().SetLabelSize(0.12)
		hSignal.GetXaxis().SetTitleSize(0.12)
		hSignal.GetYaxis().SetTitle("S / B")
		hSignal.GetYaxis().SetLabelSize(0.12)
		hSignal.GetYaxis().SetTitleSize(0.12)
		hSignal.GetYaxis().SetTitleOffset(0.45)
		hSignal.SetMaximum(0.7)
		if xmax: hSignal.GetXaxis().SetRangeUser( xmin, xmax )
		hSignal.Draw("hist")
		hSignal2.Draw("hist same")

		can.SaveAs( 'Plots/'+outName )
		del can
	else:
		histos[ 'Signal' ].SetLineWidth(3)
		histos[ 'Signal' ].SetLineColor(kRed-4)
		histos[ 'QCD' ].SetLineColor(kBlue-4)
		histos[ 'QCD' ].SetLineWidth(3)
		histos[ 'TTJets' ].SetLineColor(kGreen-4)
		histos[ 'TTJets' ].SetLineWidth(3)
		histos[ 'WJets' ].SetLineColor(kMagenta-4)
		histos[ 'WJets' ].SetLineWidth(3)
		histos[ 'ZJets' ].SetLineColor(kOrange-4)
		histos[ 'ZJets' ].SetLineWidth(3)
		if xmax: histos['Signal'].GetXaxis().SetRangeUser( xmin, xmax )
		histos['Signal'].Scale( 1/ histos['Signal'].Integral() )
		histos['QCD'].Scale( 1/ histos['QCD'].Integral() )
		histos['TTJets'].Scale( 1/ histos['TTJets'].Integral() )
		histos['WJets'].Scale( 1/ histos['WJets'].Integral() )
		histos['ZJets'].Scale( 1/ histos['ZJets'].Integral() )

  		tdrStyle.SetPadRightMargin(0.05)
		can = TCanvas('c1', 'c1', 750, 500 )
		if log: 
			can.SetLogy()
			outName = outputFileName.replace('_AnalysisPlots','_Log_AnalysisPlots')
			histos['Signal'].GetYaxis().SetTitleOffset(1.2)
		else:
			outName = outputFileName 

		histos['Signal'].GetYaxis().SetTitleOffset(1.0)
		histos['Signal'].GetYaxis().SetTitle( 'Normalized / '+str(binWidth) )
		labelAxis( name, histos['Signal'], Grom )
		histos['Signal'].Draw('hist')
		histos['QCD'].Draw('hist same')
		histos['TTJets'].Draw('hist same')
		histos['WJets'].Draw('hist same')
		histos['ZJets'].Draw('hist same')
		hmax = 1.1* max( [ histos['Signal'].GetMaximum(), histos['QCD'].GetMaximum(), histos['TTJets'].GetMaximum(), histos['WJets'].GetMaximum(), histos['ZJets'].GetMaximum() ] )
		histos['Signal'].SetMaximum(hmax)

		CMS_lumi.CMS_lumi(can, 4, 0)
		CMS_lumi.relPosX = 0.14
		legend.Draw()
		if not (labX and labY): labels( name, PU, camp )
		else: labels( name, PU, camp, labX, labY )

		can.SaveAs( 'Plots/'+outName )
		del can


def plot2D( inFile, sample, Grom, name, titleXAxis, titleXAxis2, Xmin, Xmax, rebinx, Ymin, Ymax, rebiny, legX, legY, PU ):
	"""docstring for plot"""

	outputFileName = name+'_'+Grom+'_'+sample+'_'+camp+'_'+PU+'_AnalysisPlots.pdf' 
	print 'Processing.......', outputFileName
	h1 = inFile.Get( boosted+'AnalysisPlots'+Grom+'/'+name )
	#h1 = inFile.Get( 'AnalysisPlots'+Grom+'/'+name )
	#h1 = inFile.Get( 'TriggerEfficiency'+Grom+'/'+name )
	tmph1 = h1.Clone()
	
	### Rebinning
	nbinsx = h1.GetXaxis().GetNbins()
	nbinsy = h1.GetYaxis().GetNbins()
	xmin  = h1.GetXaxis().GetXmin()
	xmax  = h1.GetXaxis().GetXmax()
	ymin  = h1.GetYaxis().GetXmin()
	ymax  = h1.GetYaxis().GetXmax()
	nx = nbinsx/rebinx
	ny = nbinsy/rebiny
	h1.SetBins( nx, xmin, xmax, ny, ymin, ymax )

	for biny in range( 1, nbinsy):
		for binx in range(1, nbinsx):
			ibin1 = h1.GetBin(binx,biny)
			h1.SetBinContent( ibin1, 0 )
		
	for biny in range( 1, nbinsy):
		by = tmph1.GetYaxis().GetBinCenter( biny )
		iy = h1.GetYaxis().FindBin(by)
		for binx in range(1, nbinsx):
			bx = tmph1.GetXaxis().GetBinCenter(binx)
			ix  = h1.GetXaxis().FindBin(bx)
			bin = tmph1.GetBin(binx,biny)
			ibin= h1.GetBin(ix,iy)
			cu  = tmph1.GetBinContent(bin)
			h1.AddBinContent(ibin,cu)

	h1.GetXaxis().SetTitle( titleXAxis )
	h1.GetYaxis().SetTitleOffset( 1.0 )
	h1.GetYaxis().SetTitle( titleXAxis2 )

	if (Xmax or Ymax):
		h1.GetXaxis().SetRangeUser( Xmin, Xmax )
		h1.GetYaxis().SetRangeUser( Ymin, Ymax )

	tdrStyle.SetPadRightMargin(0.12)
	can = TCanvas('c1', 'c1',  750, 500 )
	can.SetLogz()
	h1.SetMaximum(5000)
	h1.Draw('colz')

	CMS_lumi.relPosX = 0.13
	CMS_lumi.CMS_lumi(can, 4, 0)
	if not (legX and legY): labels( name, PU, camp )
	else: labels( name, PU, camp, legX, legY )

	can.SaveAs( 'Plots/'+outputFileName )
	#can.SaveAs( 'Plots/'+outputFileName.replace('pdf', 'gif') )
	del can


def plotCutFlow( inFileSignal, inFileQCD, inFileTTJets, inFileWJets, inFileZJets, Grom, name, xmax, log, PU, Norm=False ):
	"""docstring for plot"""

	outputFileName = name+'_'+Grom+'_RPVSt'+mass+'to'+jj+'_'+PU+'_Bkg_AnalysisPlots.pdf' 
	print 'Processing.......', outputFileName

	histos = {}
	histos[ 'Signal' ] = inFileSignal.Get( boosted+'AnalysisPlots'+Grom+'/'+name )
	histos[ 'QCD' ] = inFileQCD.Get( boosted+'AnalysisPlots'+Grom+'/'+name )
	histos[ 'TTJets' ] = inFileTTJets.Get( boosted+'AnalysisPlots'+Grom+'/'+name )
	histos[ 'WJets' ] = inFileWJets.Get( boosted+'AnalysisPlots'+Grom+'/'+name )
	histos[ 'ZJets' ] = inFileZJets.Get( boosted+'AnalysisPlots'+Grom+'/'+name )

	hSignal = histos[ 'Signal' ].Clone()
	hQCD = histos[ 'QCD' ].Clone()
	hTTJets = histos[ 'TTJets' ].Clone()
	hWJets = histos[ 'WJets' ].Clone()
	hZJets = histos[ 'ZJets' ].Clone()

	for bin in range(0,  hSignal.GetNbinsX()):
		hSignal.SetBinContent(bin, 0.)
		hSignal.SetBinError(bin, 0.)
		hQCD.SetBinContent(bin, 0.)
		hQCD.SetBinError(bin, 0.)
		hTTJets.SetBinContent(bin, 0.)
		hTTJets.SetBinError(bin, 0.)
		hWJets.SetBinContent(bin, 0.)
		hWJets.SetBinError(bin, 0.)
		hZJets.SetBinContent(bin, 0.)
		hZJets.SetBinError(bin, 0.)
	
	totalEventsSignal = histos[ 'Signal' ].GetBinContent(1)
	totalEventsQCD = histos[ 'QCD' ].GetBinContent(1)
	totalEventsTTJets = histos[ 'TTJets' ].GetBinContent(1)
	totalEventsWJets = histos[ 'WJets' ].GetBinContent(1)
	totalEventsZJets = histos[ 'ZJets' ].GetBinContent(1)
	#print totalEventsSignal, totalEventsQCD

	cutFlowSignalList = []
	cutFlowQCDList = []
	cutFlowTTJetsList = []
	cutFlowWJetsList = []
	cutFlowZJetsList = []

	for ibin in range(0, hQCD.GetNbinsX()+1):
	
		cutFlowSignalList.append( histos[ 'Signal' ].GetBinContent(ibin) )
		cutFlowQCDList.append( histos[ 'QCD' ].GetBinContent(ibin) )
		cutFlowTTJetsList.append( histos[ 'TTJets' ].GetBinContent(ibin) )
		cutFlowWJetsList.append( histos[ 'WJets' ].GetBinContent(ibin) )
		cutFlowZJetsList.append( histos[ 'ZJets' ].GetBinContent(ibin) )

		hSignal.SetBinContent( ibin , histos[ 'Signal' ].GetBinContent(ibin) / totalEventsSignal )
		hQCD.SetBinContent( ibin , histos[ 'QCD' ].GetBinContent(ibin) / totalEventsQCD )
		hTTJets.SetBinContent( ibin , histos[ 'TTJets' ].GetBinContent(ibin) / totalEventsTTJets )
		hWJets.SetBinContent( ibin , histos[ 'WJets' ].GetBinContent(ibin) / totalEventsWJets )
		hZJets.SetBinContent( ibin , histos[ 'ZJets' ].GetBinContent(ibin) / totalEventsZJets )
		
	hSB = hSignal.Clone()
	hBkg = hQCD.Clone()
	hBkg.Add( hTTJets )
	hBkg.Add( hWJets )
	hBkg.Add( hZJets )
	hSB.Divide( hBkg )
	hSB.GetXaxis().SetBinLabel( ibin, '')
	print "Signal", cutFlowSignalList
	print "QCD", cutFlowQCDList
	print "TTJets", cutFlowTTJetsList
	print "WJets", cutFlowWJetsList
	print "ZJets", cutFlowZJetsList

	#hSB = hSignal.Clone()
	#hSB.Divide( hQCD )

	binWidth = histos['Signal'].GetBinWidth(1)

	legend=TLegend(0.60,0.67,0.90,0.87)
	legend.SetFillStyle(0)
	legend.SetTextSize(0.03)

	hSignal.SetLineWidth(2)
	hSignal.SetLineColor(kRed-4)
	hQCD.SetLineWidth(2)
	hQCD.SetLineColor(kBlue-4)
	hTTJets.SetLineWidth(2)
	hTTJets.SetLineColor(kGreen-4)
	hWJets.SetLineWidth(2)
	hWJets.SetLineColor(kMagenta-4)
	hZJets.SetLineWidth(2)
	hZJets.SetLineColor(kOrange-4)

	can = TCanvas('c1', 'c1',  10, 10, 750, 750 )
	pad1 = TPad("pad1", "Fit",0,0.20,1.00,1.00,-1)
	pad2 = TPad("pad2", "Pull",0,0.00,1.00,0.30,-1);
	pad1.Draw()
	pad2.Draw()

	pad1.cd()
	if log: 
		pad1.SetLogy()
		outName = outputFileName.replace('_AnalysisPlots','_Log_AnalysisPlots')
		hSignal.GetYaxis().SetTitleOffset(0.9)
	else:
		outName = outputFileName 

	pad1.SetGridx()
	legend.AddEntry( hSignal, 'RPV #tilde{t}#rightarrow '+jj+' '+mass+' GeV' , 'l' )
	legend.AddEntry( hQCD, 'QCD', 'l' )
	legend.AddEntry( hTTJets, 't #bar{t} + Jets' , 'l' )
	legend.AddEntry( hWJets, 'W + Jets' , 'l' )
	legend.AddEntry( hZJets, 'Z + Jets' , 'l' )
	hSignal.GetYaxis().SetTitle( 'Percentage / '+str(binWidth) )
	hSignal.GetXaxis().SetRangeUser( 1, xmax )

	hSignal.SetMinimum(0.0001)
	hSignal.Draw()
	hQCD.Draw('same')
	hTTJets.Draw('same')
	hWJets.Draw('same')
	hZJets.Draw('same')

	legend.Draw()
	CMS_lumi.CMS_lumi(pad1, 4, 0)
	CMS_lumi.relPosX = 0.14
	#labels( name, '', '', '' )

	pad2.cd()
	pad2.SetGrid()
	pad2.SetTopMargin(0)
	pad2.SetBottomMargin(0.3)
	hSB.GetYaxis().SetTitle("S / B")
	hSB.GetYaxis().SetLabelSize(0.12)
	hSB.GetXaxis().SetLabelSize(0.12)
	hSB.GetYaxis().SetTitleSize(0.12)
	hSB.GetXaxis().SetTitleSize(0.12)
	hSB.GetYaxis().SetTitleOffset(0.45)
	#hSB.SetMaximum(0.7)
	hSB.GetXaxis().SetRangeUser( 1, xmax )
	hSB.Sumw2()
	hSB.Draw("hist")

	can.SaveAs( 'Plots/'+outName )
	del can

def plotSimple( inFile, sample, Grom, name, xmax, labX, labY, log, PU, Norm=False ):
	"""docstring for plot"""

	outputFileName = name+'_'+sample+'_AnalysisPlots.pdf' 
	print 'Processing.......', outputFileName

	histo = inFile.Get( boosted+'AnalysisPlots'+Grom+'/'+name )

#	histos.values()[0].SetMaximum( 2* max( listMax ) ) 
#	histos.values()[0].GetXaxis().SetRangeUser( 0, xmax )
	binWidth = histo.GetBinWidth(1)

	legend=TLegend(0.60,0.75,0.90,0.90)
	legend.SetFillStyle(0)
	legend.SetTextSize(0.03)

	#histo.SetFillColor(48)
	histo.SetFillStyle(1001)

	tdrStyle.SetPadRightMargin(0.05)
	can = TCanvas('c1', 'c1',  10, 10, 750, 500 )

	if log: 
		can.SetLogy()
		outName = outputFileName.replace('_AnalysisPlots','_Log_AnalysisPlots')
	else:
		outName = outputFileName 

	legend.AddEntry( histo, sample, 'f' )
	histo.GetYaxis().SetTitleOffset(0.90)
	histo.Draw('hist')
	histo.GetYaxis().SetTitle( 'Events / '+str(binWidth) )

	labelAxis( name, histo, '' )
	legend.Draw()
	if not (labX and labY): labels( '', sample, PU )
	else: labels( '', 'MC Truth', PU, labX, labY )
	can.SaveAs( 'Plots/'+outName )
	del can

def plotDiffSample( inFileSample1, inFileSample2, sample1, sample2, Grom, name, xmax, labX, labY, log, Diff , Norm=False):
	"""docstring for plot"""

	outputFileName = name+'_'+Grom+'_RPVSt'+mass+'to'+jj+'_Diff'+Diff+'.pdf' 
	print 'Processing.......', outputFileName

	histos = {}
	histos[ 'Sample1' ] = inFileSample1.Get( boosted+'AnalysisPlots'+Grom+'/'+name )
	histos[ 'Sample2' ] = inFileSample2.Get( boosted+'AnalysisPlots'+Grom+'/'+name )

	hSample1 = histos[ 'Sample2' ].Clone()
	hSample2 = histos[ 'Sample1' ].Clone()
	hSample1.Divide( hSample2 )

	binWidth = histos['Sample1'].GetBinWidth(1)

	legend=TLegend(0.60,0.75,0.90,0.90)
	legend.SetFillStyle(0)
	legend.SetTextSize(0.03)

	if not Norm:
		histos[ 'Sample1' ].SetLineWidth(2)
		histos[ 'Sample1' ].SetLineColor(48)
		histos[ 'Sample2' ].SetLineColor(38)
		histos[ 'Sample2' ].SetLineWidth(2)
		#histos[ 'Sample1' ].SetMaximum( 1.2* max( histos[ 'Sample1' ].GetMaximum(), histos[ 'Sample2' ].GetMaximum() ) ) 
		#histos.values()[0].GetXaxis().SetRangeUser( 0, xmax )

		can = TCanvas('c1', 'c1',  10, 10, 750, 750 )
		pad1 = TPad("pad1", "Fit",0,0.25,1.00,1.00,-1)
		pad2 = TPad("pad2", "Pull",0,0.00,1.00,0.25,-1);
		pad1.Draw()
		pad2.Draw()

		pad1.cd()
		if log: 
			pad1.SetLogy()
			outName = outputFileName.replace('_Diff','_Log_Diff')
		else:
			outName = outputFileName 

		legend.AddEntry( histos[ 'Sample1' ], sample1, 'l' )
		legend.AddEntry( histos[ 'Sample2' ], sample2, 'l' )
		histos['Sample1'].SetMinimum(10)
		histos['Sample1'].Draw('hist')
		histos['Sample1'].GetYaxis().SetTitleOffset(1.2)
		histos['Sample2'].Draw('hist same')
		histos['Sample1'].GetYaxis().SetTitle( 'Events / '+str(binWidth) )

		labelAxis( name, histos['Sample1'], Grom )
		legend.Draw()
		if not (labX and labY): labels( name, '13 TeV - Scaled to '+lumi+' fb^{-1}', '' )
		else: labels( name, '13 TeV - Scaled to '+lumi+' fb^{-1}', '', labX, labY )

		pad2.cd()
		hSample1.SetLineColor(48)
		#hSample1.SetFillStyle(1001)
		hSample1.GetYaxis().SetTitle("Ratio")
		hSample1.GetYaxis().SetLabelSize(0.12)
		hSample1.GetXaxis().SetLabelSize(0.12)
		hSample1.GetYaxis().SetTitleSize(0.12)
		hSample1.GetYaxis().SetTitleOffset(0.45)
		#hSample1.SetMaximum(1.0)
		hSample1.Sumw2()
		hSample1.Draw("histe")

		can.SaveAs( 'Plots/'+outName )
		del can
	else:
		histos[ 'Sample1' ].SetLineWidth(2)
		histos[ 'Sample1' ].SetLineColor(48)
		histos[ 'Sample2' ].SetLineColor(38)
		histos[ 'Sample2' ].SetLineWidth(2)

		can = TCanvas('c1', 'c1',  10, 10, 750, 500 )
		if log: 
			can.SetLogy()
			outName = outputFileName.replace('_Diff','_Log_Norm_Diff')
			histos[ 'Sample1' ].GetYaxis().SetTitleOffset(1.2)
		else:
			outName = outputFileName.replace('_Diff','_Norm_Diff')

		legend.AddEntry( histos[ 'Sample1' ], sample1 , 'l' )
		legend.AddEntry( histos[ 'Sample2' ], sample2 , 'l' )
		histos['Sample1'].GetYaxis().SetTitle( 'Normalized / '+str(binWidth) )

		histos['Sample1'].DrawNormalized()
		histos['Sample2'].DrawNormalized('same')

		legend.Draw()
		labelAxis( name, histos['Sample1'], Grom )
		if not (labX and labY): labels( name, '13 TeV - Scaled to '+lumi+' fb^{-1}', '' )
		else: labels( name, '13 TeV - Scaled to '+lumi+' fb^{-1}', '', labX, labY )

		can.SaveAs( 'Plots/'+outName )
		del can


def plotOptimization( inFileSignal, inFileBkg, Grom, name, Range, xmax, labX, labY, log, Norm=False):
	"""docstring for plot"""

	outputFileName = name+'_'+Grom+'_Optimization.pdf' 
	print 'Processing.......', outputFileName

	histosSignal = {}
	histosBkg = {}
	for x in Range:
		histosSignal[ x ] = inFileSignal.Get( name+x )
		histosBkg[ x ] = inFileBkg.Get( name+x )
		print histosSignal[x].Integral()

	'''
	binWidth = histos['Sample1'].GetBinWidth(1)

	legend=TLegend(0.60,0.75,0.90,0.90)
	legend.SetFillStyle(0)
	legend.SetTextSize(0.03)

	histos[ 'Sample1' ].SetLineWidth(2)
	histos[ 'Sample1' ].SetLineColor(48)
	histos[ 'Sample2' ].SetLineColor(38)
	histos[ 'Sample2' ].SetLineWidth(2)
	histos[ 'Sample3' ].SetLineColor(30)
	histos[ 'Sample3' ].SetLineWidth(2)
	histos[ 'Sample1' ].SetMaximum( 1.2* max( histos[ 'Sample1' ].GetMaximum(), histos[ 'Sample2' ].GetMaximum() ) ) 
	#histos.values()[0].GetXaxis().SetRangeUser( 0, xmax )

	can = TCanvas('c1', 'c1',  10, 10, 750, 500 )
	if log: 
		outName = outputFileName.replace('_Diff','_Log_Diff')
	else:
		outName = outputFileName 

	legend.AddEntry( histos[ 'Sample1' ], 'Low PU', 'l' )
	legend.AddEntry( histos[ 'Sample2' ], 'Med PU', 'l' )
	legend.AddEntry( histos[ 'Sample3' ], 'High PU', 'l' )
	#histos['Sample1'].SetMinimum(10)
	histos['Sample1'].Draw('hist')
	histos['Sample1'].GetYaxis().SetTitleOffset(1.2)
	histos['Sample2'].Draw('hist same')
	histos['Sample3'].Draw('hist same')
	histos['Sample1'].GetYaxis().SetTitle( 'Events / '+str(binWidth) )

	labelAxis( name, histos['Sample1'], Grom )
	legend.Draw()
	if not (labX and labY): labels( name, '13 TeV - Scaled to '+lumi+' fb^{-1}', '', '' )
	else: labels( name, '13 TeV - Scaled to '+lumi+' fb^{-1}', '', labX, labY )

	can.SaveAs( 'Plots/'+outName )
	del can
	'''
def plot2DOptimization( inFileSig, inFileBkg, Grom, name, titleXAxis, titleXAxis2, Xmin, Xmax, rebinx, Ymin, Ymax, rebiny, legX, legY, PU ):
	"""docstring for plot"""

	outputFileName = name+'_'+Grom+'_'+camp+'_'+PU+'_OptimizationPlots.pdf' 
	print 'Processing.......', outputFileName
	hSig = inFileSig.Get( name )
	hBkg = inFileBkg.Get( name )
	
	hD = hSig.Clone( "hD" )
	hsum = hSig.Clone( "hsum" )
	hsum.Add( hBkg )
	hD.Divide( hsum )

	hD.GetXaxis().SetTitle( titleXAxis )
	hD.GetYaxis().SetTitleOffset( 1.0 )
	hD.GetYaxis().SetTitle( titleXAxis2 )

	hD.GetXaxis().SetRangeUser( Xmin, Xmax )
	hD.GetYaxis().SetRangeUser( Ymin, Ymax )

	tdrStyle.SetPadRightMargin(0.12)
	can = TCanvas('c1', 'c1',  750, 500 )
	#can.SetLogz()
	#hD.SetMaximum(5000)
	hD.Draw('cont1')

	CMS_lumi.relPosX = 0.13
	CMS_lumi.CMS_lumi(can, 4, 0)
	if not (legX and legY): labels( name, PU, camp )
	else: labels( name, PU, camp, legX, legY )

	can.SaveAs( 'Plots/'+outputFileName )
	#can.SaveAs( 'Plots/'+outputFileName.replace('pdf', 'gif') )
	del can


def plotTriggerEfficiency( inFileSample, sample, triggerDenom, triggerPass, name, cut, xmin, xmax, rebin, labX, labY, log ):
	"""docstring for plot"""

	outputFileName = name+'_'+cut+'_'+triggerDenom+"_"+triggerPass+'_'+sample+'_TriggerEfficiency.pdf' 
	print 'Processing.......', outputFileName

	#DenomOnly = inFileSample.Get( 'TriggerEfficiency'+triggerDenom+triggerPass.replace('AK8PFHT700TrimMass50','')+'/'+name+'Denom_'+cut )
	DenomOnly = inFileSample.Get( 'TriggerEfficiency'+triggerPass.replace('AK8PFHT700TrimMass50','')+'/'+name+'Denom_'+cut )
	DenomOnly.Rebin(rebin)
	Denom = DenomOnly.Clone()
	#PassingOnly = inFileSample.Get( 'TriggerEfficiency'+triggerDenom+triggerPass.replace('AK8PFHT700TrimMass50','')+'/'+name+'Passing_'+cut )
	PassingOnly = inFileSample.Get( 'TriggerEfficiency'+triggerPass.replace('AK8PFHT700TrimMass50','')+'/'+name+'Passing_'+cut )
	PassingOnly.Rebin(rebin)
	Passing = PassingOnly.Clone()
	Efficiency = TGraphAsymmErrors( Passing, Denom, 'cp'  )

	binWidth = DenomOnly.GetBinWidth(1)

	legend=TLegend(0.50,0.75,0.90,0.90)
	legend.SetFillStyle(0)
	legend.SetTextSize(0.04)

	DenomOnly.SetLineWidth(2)
	DenomOnly.SetLineColor(kRed-4)
	PassingOnly.SetLineWidth(2)
	PassingOnly.SetLineColor(kBlue-4)

	can = TCanvas('c1', 'c1',  10, 10, 750, 750 )
	pad1 = TPad("pad1", "Histo",0,0.46,1.00,1.00,-1)
	pad2 = TPad("pad2", "Efficiency",0,0.00,1.00,0.49,-1);
	pad2.Draw()
	pad1.Draw()

	pad1.cd()
	if log: pad1.SetLogy()

	legend.AddEntry( DenomOnly, triggerDenom+' (basedline trigger)', 'l' )
	legend.AddEntry( PassingOnly, triggerPass, 'l' )
	#DenomOnly.SetMinimum(10)
	DenomOnly.GetXaxis().SetRangeUser( xmin, xmax )
	DenomOnly.Draw('histe')
	DenomOnly.GetYaxis().SetTitleSize(0.06)
	DenomOnly.GetYaxis().SetTitleOffset(0.8)
	DenomOnly.GetYaxis().SetLabelSize(0.06)
	DenomOnly.GetXaxis().SetTitleOffset(0.8)
	DenomOnly.GetXaxis().SetTitleSize(0.06)
	DenomOnly.GetXaxis().SetLabelSize(0.05)
	PassingOnly.Draw('histe same')
	DenomOnly.GetYaxis().SetTitle( 'Events / '+str(binWidth) )

	CMS_lumi.CMS_lumi(pad1, 4, 0)
	labelAxis( name, DenomOnly, 'Pruned')
	legend.Draw()
	if 'JetHT' in sample:
		if not (labX and labY): labels( 'trigger', PU, camp)
		else: labels( 'trigger', PU, camp, labX, labY ) #, sel1='AK8PFHT700TrimMass50' )
	else:
		if not (labX and labY): labels( 'trigger', PU, camp,   )
		else: labels( 'trigger', PU, camp, labX, labY )

	pad2.cd()
	Efficiency.SetLineWidth(2)
	Efficiency.SetLineColor(kBlue-4)
	#Efficiency.SetFillStyle(1001)
	Efficiency.GetYaxis().SetTitle("Efficiency")
	Efficiency.GetYaxis().SetLabelSize(0.06)
	Efficiency.GetXaxis().SetLabelSize(0.06)
	Efficiency.GetYaxis().SetTitleSize(0.06)
	Efficiency.GetYaxis().SetTitleOffset(0.8)
	Efficiency.SetMinimum(-0.1)
	Efficiency.GetXaxis().SetLimits( xmin, xmax )
	Efficiency.Draw()

	can.SaveAs( 'Plots/'+outputFileName )
	del can

	can1 = TCanvas('c1', 'c1',  10, 10, 750, 500 )
	Efficiency.SetMinimum(0)
	Efficiency.SetMaximum(1.15)
	Efficiency.GetYaxis().SetLabelSize(0.05)
	Efficiency.GetXaxis().SetLabelSize(0.05)
	Efficiency.GetYaxis().SetTitleSize(0.06)
	Efficiency.GetYaxis().SetTitleOffset(0.8)
	Efficiency.GetXaxis().SetTitleOffset(0.8)
	Efficiency.Draw()
	can1.Update()

	rightmax = 1.2*PassingOnly.GetMaximum()
	rightmin = PassingOnly.GetMinimum()
	scale = gPad.GetUymax()/rightmax
	PassingOnly.SetLineColor(kBlue-5)
	PassingOnly.Scale( scale )
	PassingOnly.Draw( 'hist same' )
	#axis = TGaxis( gPad.GetUxmax(), gPad.GetUymin(), gPad.GetUxmax(), gPad.GetUymax(),-3,rightmax,710,"+L")
	axis = TGaxis( gPad.GetUxmax(), gPad.GetUymin(), gPad.GetUxmax(), gPad.GetUymax(),rightmin,rightmax,10,"+L")
	axis.SetTitle('Events / '+str(binWidth) )
	axis.SetTitleColor(kBlue-5)
	axis.SetTitleSize(0.06)
	axis.SetLabelSize(0.05)
	axis.SetTitleFont(42)
	axis.SetLabelFont(42)
	axis.SetLineColor(kBlue-5)
	axis.SetLabelColor(kBlue-5)
	axis.SetTitleOffset(0.7)
	axis.Draw()
	labelAxis( name, Efficiency, 'Pruned')
	CMS_lumi.relPosX = 0.11
	CMS_lumi.cmsTextSize = 0.7
	CMS_lumi.extraOverCmsTextSize = 0.6
	CMS_lumi.CMS_lumi(can1, 4, 0)
	if 'JetHT' in sample:
		if not (labX and labY): labels( 'triggerDATA',PU, camp,  )
		else: labels( 'triggerDATA', PU, camp, labX, labY-0.05 ) #, sel1= [ 'AK8PFHT700TrimMass50' ] )
	else:
		if not (labX and labY): labels( 'triggerSignal', PU, camp  )
		else: labels( 'triggerSignal', PU, camp, labX, labY)

	can1.SaveAs( 'Plots/'+outputFileName.replace('.pdf','Merged.pdf') )
	#can1.SaveAs( 'Plots/'+outputFileName.replace('.pdf','Merged.gif') )
	del can1


def plot2DTriggerEfficiency( inFileSample, sample, triggerDenom, triggerPass, name, cut, Xmin, Xmax, rebinx, Ymin, Ymax, rebiny, labX, labY ):
	"""docstring for plot"""

	outputFileName = name+'_'+cut+'_'+triggerDenom+"_"+triggerPass+'_'+sample+'_TriggerEfficiency.pdf' 
	print 'Processing.......', outputFileName

	#Denom = inFileSample.Get( 'TriggerEfficiency'+triggerDenom+triggerPass.replace('AK8PFHT700TrimMass50','')+'/'+name+'Denom_'+cut )
	Denom = inFileSample.Get( 'TriggerEfficiency'+triggerPass.replace('AK8PFHT700TrimMass50','')+'/'+name+'Denom_'+cut )
	#Passing = inFileSample.Get( 'TriggerEfficiency'+triggerDenom+triggerPass.replace('AK8PFHT700TrimMass50','')+'/'+name+'Passing_'+cut )
	Passing = inFileSample.Get( 'TriggerEfficiency'+triggerPass.replace('AK8PFHT700TrimMass50','')+'/'+name+'Passing_'+cut )
	tmpDenom = Denom.Clone()
	tmpPassing = Passing.Clone()
	
	### Rebinning
	nbinsx = Denom.GetXaxis().GetNbins()
	nbinsy = Denom.GetYaxis().GetNbins()
	xmin  = Denom.GetXaxis().GetXmin()
	xmax  = Denom.GetXaxis().GetXmax()
	ymin  = Denom.GetYaxis().GetXmin()
	ymax  = Denom.GetYaxis().GetXmax()
	nx = nbinsx/rebinx
	ny = nbinsy/rebiny
	Denom.SetBins( nx, xmin, xmax, ny, ymin, ymax )
	Passing.SetBins( nx, xmin, xmax, ny, ymin, ymax )

	for biny in range( 1, nbinsy):
		for binx in range(1, nbinsx):
			ibin1 = Denom.GetBin(binx,biny)
			Denom.SetBinContent( ibin1, 0 )
			ibin2 = Denom.GetBin(binx,biny)
			Passing.SetBinContent( ibin2, 0 )
		
	for biny in range( 1, nbinsy):
		by = tmpDenom.GetYaxis().GetBinCenter( biny )
		iy = Denom.GetYaxis().FindBin(by)
		by2 = tmpPassing.GetYaxis().GetBinCenter( biny )
		iy2 = Passing.GetYaxis().FindBin(by2)
		for binx in range(1, nbinsx):
			bx = tmpDenom.GetXaxis().GetBinCenter(binx)
			ix  = Denom.GetXaxis().FindBin(bx)
			bin = tmpDenom.GetBin(binx,biny)
			ibin= Denom.GetBin(ix,iy)
			cu  = tmpDenom.GetBinContent(bin)
			Denom.AddBinContent(ibin,cu)

			bx2 = tmpPassing.GetXaxis().GetBinCenter(binx)
			ix2  = Passing.GetXaxis().FindBin(bx2)
			bin2 = tmpPassing.GetBin(binx,biny)
			ibin2 = Passing.GetBin(ix2,iy2)
			cu2  = tmpPassing.GetBinContent(bin2)
			Passing.AddBinContent(ibin2,cu2)

	Efficiency = Denom.Clone() #TH2D( '', '', nx, xmin, xmax, ny, ymin, ymax )
	Efficiency.Reset()
	Efficiency.Divide( Passing, Denom, 1, 1, 'B' )


	can = TCanvas('c1', 'c1',  10, 10, 750, 500 )
	gStyle.SetPaintTextFormat("4.2f")
	Efficiency.Draw('colz')
	Efficiency.Draw('same text')
	Efficiency.GetYaxis().SetTitleOffset(1.0)
	Efficiency.SetMarkerSize(2)
	Efficiency.GetXaxis().SetRange( int(Xmin/(10.*rebinx)), int(Xmax/(10.*rebinx)) )
	#Efficiency.GetXaxis().SetTitle( 'Leading Trimmed Jet Mass [GeV]' )
	Efficiency.GetYaxis().SetTitle( 'H_{T} [GeV]' )
	Efficiency.GetYaxis().SetRange( int(Ymin/(10.*rebiny)), int(Ymax/(10.*rebiny)) )

	CMS_lumi.relPosX = 0.13
	CMS_lumi.CMS_lumi(can, 4, 0)
	if 'JetHT' in sample:
		if not (labX and labY): labels( 'triggerDATA',PU, camp,  )
		else: labels( 'triggerDATA', PU, camp, labX, labY-0.05 ) #, sel1= [ 'AK8PFHT700TrimMass50' ] )
	else:
		if not (labX and labY): labels( 'triggerSignal', PU, camp  )
		else: labels( 'triggerSignal', PU, camp, labX, labY)

	can.SaveAs( 'Plots/'+outputFileName )
	#can.SaveAs( 'Plots/'+outputFileName.replace('pdf', 'gif')  )
	del can

def plotQuality( inFileData, inFileQCD, kfactor, inFileTTJets, inFileWJets, inFileZJets, Grom, nameInRoot, name, xmin, xmax, labX, labY, log, PU ):
	"""docstring for plot"""

	outputFileName = name+'_'+Grom+'_dataQualityPlots.pdf' 
	print 'Processing.......', outputFileName

	histos = {}
	histos[ 'Data' ] = inFileData.Get( nameInRoot )
	histos[ 'QCD' ] = inFileQCD.Get( nameInRoot )
	histos[ 'QCD' ].Scale( kfactor )
	histos[ 'TTJets' ] = inFileTTJets.Get( nameInRoot )
	histos[ 'WJets' ] = inFileWJets.Get( nameInRoot )
	histos[ 'ZJets' ] = inFileZJets.Get( nameInRoot )

	hData = histos[ 'Data' ].Clone()
	hBkg = histos[ 'QCD' ].Clone() 
	#hBkg.Add( histos[ 'TTJets' ].Clone() )
	hBkg.Add( histos[ 'WJets' ].Clone() )
	hBkg.Add( histos[ 'ZJets' ].Clone() )
	hRatio = histos[ 'Data' ].Clone()
	hRatio.Divide( hBkg )
	
	'''
	for bin in range(0,  hSoSB.GetNbinsX()):
		hSoSB.SetBinContent(bin, 0.)
		hSoSB.SetBinError(bin, 0.)

	hSoSB2 = hSoSB.Clone()
	for ibin in range(0, hSoSB.GetNbinsX()):
	
		binContData = histos[ 'Data' ].GetBinContent(ibin)
		binErrData = histos[ 'Data' ].GetBinError(ibin)
		binContBkg = histos[ 'QCD' ].GetBinContent(ibin) + histos[ 'TTJets' ].GetBinContent(ibin) + histos[ 'WJets' ].GetBinContent(ibin) + histos[ 'ZJets' ].GetBinContent(ibin)    
		binErrBkg = histos[ 'QCD' ].GetBinError(ibin)
		try:
			value = binContData / TMath.Sqrt( binContData + binContBkg )
		except ZeroDivisionError: continue
		hSoSB.SetBinContent( ibin, value )
	'''

	binWidth = histos['Data'].GetBinWidth(1)

	legend=TLegend(0.60,0.75,0.90,0.87)
	legend.SetFillStyle(0)
	legend.SetTextSize(0.04)
	legend.AddEntry( hData, 'Data' , 'ep' )
	legend.AddEntry( hBkg, 'Background', 'l' )

	hBkg.SetLineColor(kRed-4)
	hData.SetMarkerStyle(8)

	tdrStyle.SetPadRightMargin(0.05)
	tdrStyle.SetPadLeftMargin(0.15)
	can = TCanvas('c1', 'c1',  10, 10, 750, 750 )
	pad1 = TPad("pad1", "Fit",0,0.207,1.00,1.00,-1)
	pad2 = TPad("pad2", "Pull",0,0.00,1.00,0.30,-1);
	pad1.Draw()
	pad2.Draw()

	pad1.cd()
	if log: pad1.SetLogy() 	
	hData.Draw("E")
	hBkg.Draw('hist same')
	#hData.GetYaxis().SetTitleOffset(1.2)
	if xmax: hData.GetXaxis().SetRangeUser( xmin, xmax )
	hData.GetYaxis().SetTitle( 'Events / '+str(binWidth) )

	CMS_lumi.relPosX = 0.13
	CMS_lumi.CMS_lumi(pad1, 4, 0)
	#labelAxis( name, hData, Grom )
	legend.Draw()
	if not (labX and labY): labels( name, '', '' )
	else: labels( name, '', '', labX, labY )

	pad2.cd()
	pad2.SetGrid()
	pad2.SetTopMargin(0)
	pad2.SetBottomMargin(0.3)
	'''
	hSoSB.SetFillColor(48)
	hSoSB.SetFillStyle(1001)
	hSoSB.GetYaxis().SetTitle("S / #sqrt{S+B}")
	hSoSB.GetYaxis().SetLabelSize(0.12)
	hSoSB.GetXaxis().SetLabelSize(0.12)
	hSoSB.GetYaxis().SetTitleSize(0.12)
	hSoSB.GetYaxis().SetTitleOffset(0.45)
	#hSoSB.SetMaximum(0.7)
	hSoSB.Sumw2()
	if xmax: hSoSB.GetXaxis().SetRangeUser( xmin, xmax )
	hSoSB.Draw("hist")
	'''
	labelAxis( name, hRatio, Grom )
	hRatio.SetMarkerStyle(8)
	hRatio.GetXaxis().SetTitleOffset(1.1)
	hRatio.GetXaxis().SetLabelSize(0.12)
	hRatio.GetXaxis().SetTitleSize(0.12)
	hRatio.GetYaxis().SetTitle("Data/Bkg")
	hRatio.GetYaxis().SetLabelSize(0.12)
	hRatio.GetYaxis().SetTitleSize(0.12)
	hRatio.GetYaxis().SetTitleOffset(0.55)
	if( hRatio.GetMaximum() > 2 ): hRatio.SetMaximum( 2.0 )
	hRatio.SetMinimum( 0.6 )
	if xmax: hRatio.GetXaxis().SetRangeUser( xmin, xmax )
	hRatio.Draw()

	can.SaveAs( 'Plots/'+ outputFileName )
	del can



if __name__ == '__main__':

	parser = argparse.ArgumentParser()
	parser.add_argument('-p', '--proc', action='store', default='1D', help='Process to draw, example: 1D, 2D, MC.' )
	parser.add_argument('-d', '--decay', action='store', default='jj', help='Decay, example: jj, bj.' )
	parser.add_argument('-b', '--boosted', action='store', default='Boosted', help='Boosted or non boosted, example: Boosted' )
	parser.add_argument('-g', '--grom', action='store', default='Pruned', help='Grooming Algorithm, example: Pruned, Filtered.' )
	parser.add_argument('-m', '--mass', action='store', default='100', help='Mass of Stop, example: 100' )
	parser.add_argument('-C', '--cut', action='store', default='_cutDEta', help='cut, example: cutDEta' )
	parser.add_argument('-pu', '--PU', action='store', default='Asympt25ns', help='PU, example: PU40bx25.' )
	parser.add_argument('-s', '--single', action='store', default='all', help='single histogram, example: massAve_cutDijet.' )
	parser.add_argument('-q', '--QCD', action='store', default='Pt', help='Type of QCD binning, example: HT.' )
	parser.add_argument('-c', '--campaign', action='store', default='RunIISpring15DR74', help='Campaign, example: PHYS14.' )
	parser.add_argument('-l', '--lumi', action='store', default='15.5', help='Luminosity, example: 1.' )
	parser.add_argument('-t', '--trigger', action='store', default='AK8PFHT700TrimMass50', help='Trigger used, example PFHT800.' )

	try:
		args = parser.parse_args()
	except:
		parser.print_help()
		sys.exit(0)

	process = args.proc
	jj = args.decay
	PU = args.PU
	qcd = args.QCD
	camp = args.campaign
	lumi = args.lumi
	histo = args.single
	mass = args.mass
	cut = args.cut
	grom = args.grom
	single = args.single
	boosted = args.boosted
	triggerUsed = args.trigger
	
	#if 'DATA' in process: 
	CMS_lumi.lumi_13TeV = "15.5 pb^{-1}"
	CMS_lumi.extraText = "Preliminary"
	#else:
	#	CMS_lumi.lumi_13TeV = lumi+" fb^{-1}"
	#	CMS_lumi.extraText = "Preliminary Simulation"

	#inputFileSample = TFile.Open('RUNAnalysis_RPVSt100tojj_pythia8_13TeV_PU40bx50_PHYS14.root')
	#inputFileMCSignal = TFile.Open('RUNMCAnalysis_RPVSt100tojj_pythia8_13TeV_PU20bx25.root')
	if 'trig' in process:
		if 'DATA' in process: 
			if 'MET' in process:
				inputTrigger = TFile.Open('Rootfiles/RUNTriggerEfficiency_MET_Asympt50ns_v01p2_ts_v10.root')
				SAMPLE = 'MET'
				BASEDTrigger = 'PFMET170'
			else:
				inputTrigger = TFile.Open('Rootfiles/RUNTriggerEfficiency_JetHT_Asympt50ns_v01p2_ts_v10.root')
				SAMPLE = 'JetHT'
				BASEDTrigger = 'PFHT475'
		else: 
			inputTrigger = TFile.Open('Rootfiles/RUNTriggerEfficiency_RPVSt100tojj_RunIISpring15DR74_Asympt25ns_TS_v02_v10.root')
			SAMPLE = 'RPVStop100tojj'
			BASEDTrigger = 'PFHT475'
	elif ( 'mini' in process ) or ( '2dOpt' in process ):
		inputMiniFileSignal = TFile.Open('Rootfiles/RUNMiniAnalysis_RPVSt'+mass+'to'+jj+'_'+camp+'_'+PU+'_v02p2_v06.root')
		inputMiniFileQCD = TFile.Open('Rootfiles/RUNMiniAnalysis_QCDPtAll_RunIISpring15DR74_Asympt25ns_v01_v06.root')
		inputMiniFileSignal200 = TFile.Open('Rootfiles/RUNMiniAnalysis_RPVSt200to'+jj+'_'+camp+'_'+PU+'_v02p2_v06.root')
		inputMiniFileTTJets = TFile.Open('Rootfiles/RUNMiniAnalysis_TTJets_'+camp+'_'+PU+'_v01_v06.root')
		inputMiniFileWJetsToQQ = TFile.Open('Rootfiles/RUNMiniAnalysis_WJetsToQQ_HT-600ToInf_RunIISpring15DR74_Asympt25ns_v01p2_v06.root')
		inputMiniFileZJetsToQQ = TFile.Open('Rootfiles/RUNMiniAnalysis_ZJetsToQQ_HT600ToInf_RunIISpring15DR74_Asympt25ns_v01p2_v06.root')
	else:
		inputFileData = TFile.Open('Rootfiles/RUNAnalysis_JetHT_Run2015C_Asympt25ns_v03_v01p3.root')
		inputFileSignal = TFile.Open('Rootfiles/RUNAnalysis_RPVSt'+mass+'to'+jj+'_'+camp+'_'+PU+'_v03_v01p3.root')
		inputFileSignal200 = TFile.Open('Rootfiles/RUNAnalysis_RPVSt350tojj_'+camp+'_'+PU+'_v03_v01p3.root')
		#inputFileSignal350 = TFile.Open('Rootfiles/RUNAnalysis_RPVSt350to'+jj+'_'+camp+'_'+PU+'_v02p3_v06.root')
		#inputFileSignal = TFile.Open('Rootfiles/RUNTriggerEfficiency_RPVSt100tojj_RunIISpring16DR74_Asympt25ns_TS_v02_v09.root')
		inputFileQCD = TFile.Open('Rootfiles/RUNAnalysis_QCD'+qcd+'All_'+camp+'_'+PU+'_v03_v01p3.root')
		#inputFileTTJets = TFile.Open('Rootfiles/RUNAnalysis_TTJets_'+camp+'_'+PU+'_v03_v01p3p2.root')
		inputFileWJetsToQQ = TFile.Open('Rootfiles/RUNAnalysis_WJetsToQQ_HT-600ToInf_RunIISpring15DR74_Asympt25ns_v03_v01p3.root')
		inputFileZJetsToQQ = TFile.Open('Rootfiles/RUNAnalysis_ZJetsToQQ_HT600ToInf_RunIISpring15DR74_Asympt25ns_v03_v01p3.root')

	dijetlabX = 0.15
	dijetlabY = 0.88
	triggerlabX = 0.88
	triggerlabY = 0.90  #0.50
	subjet112vs212labX = 0.7
	subjet112vs212labY = 0.88
	jetMassHTlabX = 0.85
	jetMassHTlabY = 0.20
	polAnglabX = 0.2
	polAnglabY = 0.88
	taulabX = '' #0.6
	taulabY = '' #0.40
	cosPhilabX = 0.15
	cosPhilabY = 0.45

	massMinX = 0
	massMaxX = 3*(int(mass))
	polAngXmin = 0.7
	polAngXmax = 1.0
	HTMinX = 300
	HTMaxX = 1300
	ptMinX = 100
	ptMaxX = 800


	plotList = [ 
		[ '2D', 'jetTrimmedMassHT', 'Leading Trimmed Jet Mass [GeV]', 'HT [GeV]', 0, massMaxX, 1, 100, HTMaxX, 1, jetMassHTlabX, jetMassHTlabY],
		[ '2D', 'leadMassHT', 'Leading Jet Mass [GeV]', 'HT [GeV]', 0, massMaxX, 1, 100, HTMaxX, 1, jetMassHTlabX, jetMassHTlabY],

		[ '2D', 'leadMassHT_cutTrigger', 'Leading Jet Mass [GeV]', 'HT [GeV]', 0, massMaxX, 1, 100, HTMaxX, 1, jetMassHTlabX, jetMassHTlabY],

		[ '2D', 'jet1Subjet112vs212MassRatio_cutDijet', 'm_{1}/m_{12}', 'm_{2}/m_{12}', '', '', 1, '', '', 1, subjet112vs212labX, subjet112vs212labY  ],
		[ '2D', 'jet1Subjet1JetvsSubjet2JetMassRatio_cutDijet', 'm_{1}/M_{12}', 'm_{2}/M_{12}', '', '', 1, '', '', 1, subjet112vs212labX, subjet112vs212labY  ],
		[ '2D', 'jet2Subjet112vs212MassRatio_cutDijet', 'm_{3}/m_{34}', 'm_{4}/m_{34}', '', '', 1, '', '', 1, subjet112vs212labX, subjet112vs212labY  ],
		[ '2D', 'jet2Subjet1JetvsSubjet2JetMassRatio_cutDijet', 'm_{3}/M_{34}', 'm_{4}/M_{34}', '', '', 1, '', '', 1, subjet112vs212labX, subjet112vs212labY  ],
		[ '2D', 'subjet12Mass_cutDijet', 'm_{1}', 'm_{2}', '', '', 1, '', '', 1, dijetlabX, dijetlabY  ],
		[ '2D', 'dijetCorr_cutDijet', '#eta_{sjet1}', '#eta_{sjet2}', '', '', 1, '', '', 1, dijetlabX, dijetlabY  ],
		[ '2D', 'dijetCorrPhi_cutDijet', '#phi_{sjet1}', '#phi_{sjet2}', '', '', 1, '', '', 1, dijetlabX, dijetlabY  ],
		[ '2D', 'subjet112vs212MassRatio_cutDijet', 'm_{1}/m_{12}', 'm_{2}/m_{12}', '', '', 1, '', '', 1, subjet112vs212labX, subjet112vs212labY  ],
		[ '2D', 'subjet1JetvsSubjet2JetMassRatio_cutDijet', 'm_{1}/M_{12}', 'm_{2}/M_{12}', '', '', 1, '', '', 1, subjet112vs212labX, subjet112vs212labY  ],
		[ '2D', 'subjetPolAngle13412vs31234_cutDijet', 'cos #psi_{1(34)}^{[12]}', 'cos #psi_{3(12)}^{[34]}', polAngXmin, polAngXmax, 1, polAngXmin, polAngXmax, 1, cosPhilabX, cosPhilabY  ],
		[ '2D', 'mu1234_cutDijet', '', '', '', '', 1, '', '', 1, dijetlabX, dijetlabY  ],
		[ '2D', 'mu3412_cutDijet', '', '', '', '', 1, '', '', 1, dijetlabX, dijetlabY  ],
		[ '2D', 'dalitz1234_cutDijet', 'X', 'Y', '', '', 1, '', '', 1, dijetlabX, dijetlabY  ],
		[ '2D', 'dalitz3412_cutDijet', 'X', 'Y', '', '', 1, '', '', 1, dijetlabX, dijetlabY  ],
		[ '2D', 'leadMassHT_cutDijet', 'Leading Jet Mass [GeV]', 'HT [GeV]', 0, massMaxX, 1, 100, HTMaxX, 1, jetMassHTlabX, jetMassHTlabY],

		#[ '2D', 'subjet12Mass_cutAsym', 'm_{1}', 'm_{2}', '', '', 1, '', '', 1, dijetlabX, dijetlabY  ],
		[ '2D', 'dijetCorr_cutAsym', '#eta_{sjet1}', '#eta_{sjet2}', '', '', 1, '', '', 1, dijetlabX, dijetlabY  ],
		[ '2D', 'dijetCorrPhi_cutAsym', '#phi_{sjet1}', '#phi_{sjet2}', '', '', 1, '', '', 1, dijetlabX, dijetlabY  ],
		#[ '2D', 'subjet112vs212MassRatio_cutAsym', 'm_{1}/m_{12}', 'm_{2}/m_{12}', '', '', 1, '', '', 1, subjet112vs212labX, subjet112vs212labY  ],
		#[ '2D', 'subjet1JetvsSubjet2JetMassRatio_cutAsym', 'm_{1}/M_{12}', 'm_{2}/M_{12}', '', '', 1, '', '', 1, subjet112vs212labX, subjet112vs212labY  ],
		#[ '2D', 'subjetPolAngle13412vs31234_cutAsym', 'cos #psi_{1(34)}^{[12]}', 'cos #psi_{3(12)}^{[34]}', '', '', 1, '', '', 1, '', ''  ],
		#[ '2D', 'mu1234_cutAsym', '', '', 1, '', '', 1, '', '', 1, dijetlabX, dijetlabY  ],
		#[ '2D', 'mu3412_cutAsym', '', '', 1, '', '', 1, '', '', 1, dijetlabX, dijetlabY  ],
		#[ '2D', 'dalitz1234_cutAsym', 'X', 'Y', '', '', 1, '', '', 1, dijetlabX, dijetlabY  ],
		#[ '2D', 'dalitz3412_cutAsym', 'X', 'Y', '', '', 1, '', '', 1, dijetlabX, dijetlabY  ],

		#[ '2D', 'subjet12Mass_cutCosTheta', 'm_{1}', 'm_{2}', '', '', 1, '', '', 1, dijetlabX, dijetlabY  ],
		#[ '2D', 'dijetCorr_cutCosTheta', '#eta_{sjet1}', '#eta_{sjet2}', '', '', 1, '', '', 1, dijetlabX, dijetlabY  ],
		#[ '2D', 'dijetCorrPhi_cutCosTheta', '#phi_{sjet1}', '#phi_{sjet2}', '', '', 1, '', '', 1, dijetlabX, dijetlabY  ],
		#[ '2D', 'subjet112vs212MassRatio_cutCosTheta', 'm_{1}/m_{12}', 'm_{2}/m_{12}', '', '', 1, '', '', 1, subjet112vs212labX, subjet112vs212labY  ],
		#[ '2D', 'subjet1JetvsSubjet2JetMassRatio_cutCosTheta', 'm_{1}/M_{12}', 'm_{2}/M_{12}', '', '', 1, '', '', 1, subjet112vs212labX, subjet112vs212labY  ],
		#[ '2D', 'subjetPolAngle13412vs31234_cutCosTheta', 'cos #psi_{1(34)}^{[12]}', 'cos #psi_{3(12)}^{[34]}', '', '', 1, '', '', 1, '', ''  ],
		#[ '2D', 'mu1234_cutCosTheta', '', '', 1, '', '', 1, '', '', 1, dijetlabX, dijetlabY  ],
		#[ '2D', 'mu3412_cutCosTheta', '', '', 1, '', '', 1, '', '', 1, dijetlabX, dijetlabY  ],
		#[ '2D', 'dalitz1234_cutCosTheta', 'X', 'Y', '', '', 1, '', '', 1, dijetlabX, dijetlabY  ],
		#[ '2D', 'dalitz3412_cutCosTheta', 'X', 'Y', '', '', 1, '', '', 1, dijetlabX, dijetlabY  ],

		[ '2D', 'subjet12Mass_cutSubjetPtRatio', 'm_{1}', 'm_{2}', '', '', 1, '', '', 1, dijetlabX, dijetlabY  ],
		[ '2D', 'dijetCorr_cutSubjetPtRatio', '#eta_{sjet1}', '#eta_{sjet2}', '', '', 1, '', '', 1, dijetlabX, dijetlabY  ],
		[ '2D', 'dijetCorrPhi_cutSubjetPtRatio', '#phi_{sjet1}', '#phi_{sjet2}', '', '', 1, '', '', 1, dijetlabX, dijetlabY  ],
		[ '2D', 'subjet112vs212MassRatio_cutSubjetPtRatio', 'm_{1}/m_{12}', 'm_{2}/m_{12}', '', '', 1, '', '', 1, subjet112vs212labX, subjet112vs212labY  ],
		[ '2D', 'subjet1JetvsSubjet2JetMassRatio_cutSubjetPtRatio', 'm_{1}/M_{12}', 'm_{2}/M_{12}', '', '', 1, '', '', 1, subjet112vs212labX, subjet112vs212labY  ],
		[ '2D', 'subjetPolAngle13412vs31234_cutSubjetPtRatio', 'cos #psi_{1(34)}^{[12]}', 'cos #psi_{3(12)}^{[34]}', polAngXmin, polAngXmax, 1, polAngXmin, polAngXmax, 1, cosPhilabX, cosPhilabY  ],
		#[ '2D', 'subjetPolAngle13412vsSubjetPtRatio_cutSubjePtRatio', 'cos #psi_{1(34)}^{[12]}', 'Subjet Pt Ratio', polAngXmin, polAngXmax, 1, polAngXmin, polAngXmax, 1, cosPhilabX, cosPhilabY  ],
		[ '2D', 'mu1234_cutSubjetPtRatio', '', '', '', '', 1, '', '', 1, dijetlabX, dijetlabY  ],
		[ '2D', 'mu3412_cutSubjetPtRatio', '', '', '', '', 1, '', '', 1, dijetlabX, dijetlabY  ],
		[ '2D', 'dalitz1234_cutSubjetPtRatio', 'X', 'Y', '', '', 1, '', '', 1, dijetlabX, dijetlabY  ],
		[ '2D', 'dalitz3412_cutSubjetPtRatio', 'X', 'Y', '', '', 1, '', '', 1, dijetlabX, dijetlabY  ],

		#[ '2D', 'subjet12Mass_cutTau31', 'm_{1}', 'm_{2}', '', '', 1, '', '', 1, dijetlabX, dijetlabY  ],
		#[ '2D', 'dijetCorr_cutTau31', '#eta_{sjet1}', '#eta_{sjet2}', '', '', 1, '', '', 1, dijetlabX, dijetlabY  ],
		#[ '2D', 'dijetCorrPhi_cutTau31', '#phi_{sjet1}', '#phi_{sjet2}', '', '', 1, '', '', 1, dijetlabX, dijetlabY  ],
		#[ '2D', 'subjet112vs212MassRatio_cutTau31', 'm_{1}/m_{12}', 'm_{2}/m_{12}', '', '', 1, '', '', 1, subjet112vs212labX, subjet112vs212labY  ],
		#[ '2D', 'subjet1JetvsSubjet2JetMassRatio_cutTau31', 'm_{1}/M_{12}', 'm_{2}/M_{12}', '', '', 1, '', '', 1, subjet112vs212labX, subjet112vs212labY  ],
		#[ '2D', 'subjetPolAngle13412vs31234_cutTau31', 'cos #psi_{1(34)}^{[12]}', 'cos #psi_{3(12)}^{[34]}', '', '', 1, '', '', 1, '', ''  ],
		#[ '2D', 'mu1234_cutTau31', '', '', 1, '', '', 1, '', '', 1, dijetlabX, dijetlabY  ],
		#[ '2D', 'mu3412_cutTau31', '', '', 1, '', '', 1, '', '', 1, dijetlabX, dijetlabY  ],
		#[ '2D', 'dalitz1234_cutTau31', 'y', 'x', '', '', 1, '', '', 1, dijetlabX, dijetlabY  ],
		#[ '2D', 'dalitz3412_cutTau31', 'y', 'x', '', '', 1, '', '', 1, dijetlabX, dijetlabY  ],

		[ '1D', 'jetPt', 10, 1000, '', '', True],
		[ '1D', 'jetEta', '', '', '', '', True],
		[ '1D', 'jetMass', 0, massMaxX, '', '', True],
		[ '1D', 'HT', 0, 1000, '', '', False],
		[ '1D', 'massAve', 0, massMaxX, '', '', False],

		[ 'qual', 'jetPt', 100, 1500, 0.92, 0.8, True],
		[ 'qual', 'jetEta', -3, 3, 0.92, 0.8, False],
		[ 'qual', 'jetMass', 0, 1000, 0.92, 0.8, True],
		[ 'qual', 'HT', 700, 2000, 0.92, 0.8, True],

		[ 'Norm', 'NPV', '', '', '', '', False],
		#[ 'Norm', 'jet1Subjet1Pt_cutDijet', '', '', '', '', True],
		#[ 'Norm', 'jet1Subjet2Pt_cutDijet', '', '', '', True],
		#[ 'Norm', 'jet2Subjet1Pt_cutDijet', '', '', '', True],
		#[ 'Norm', 'jet2Subjet2Pt_cutDijet', '', '', '', True],
		#[ 'Norm', 'jet1Subjet1Mass_cutDijet', '', '', '', True],
		#[ 'Norm', 'jet1Subjet2Mass_cutDijet', '', '', '', True],
		#[ 'Norm', 'jet2Subjet1Mass_cutDijet', '', '', '', True],
		#[ 'Norm', 'jet2Subjet2Mass_cutDijet', '', '', '', True],
		[ 'Norm', 'jet1Tau1_cutDijet', '', '', taulabX, taulabY, False],
		[ 'Norm', 'jet1Tau2_cutDijet', '', '', taulabX, taulabY, False],
		[ 'Norm', 'jet1Tau3_cutDijet', '', '', taulabX, taulabY, False],
		[ 'Norm', 'jet1Tau21_cutDijet', '', '', taulabX, taulabY, False],
		[ 'Norm', 'jet1Tau31_cutDijet', '', '', taulabX, taulabY, False],
		[ 'Norm', 'jet1Tau32_cutDijet', '', '', taulabX, taulabY, False],
		[ 'Norm', 'jet2Tau21_cutDijet', '', '', taulabX, taulabY, False],
		[ 'Norm', 'jet2Tau31_cutDijet', '', '', taulabX, taulabY, False],
		[ 'Norm', 'jet2Tau32_cutDijet', '', '', taulabX, taulabY, False],
		[ 'Norm', 'jet1SubjetPtRatio_cutDijet', '', '', '', '', True],
		[ 'Norm', 'jet2SubjetPtRatio_cutDijet', '', '', '', '', True],
		[ 'Norm', 'subjetPtRatio_cutDijet', '', '', '', '', True],
		[ 'Norm', 'massAsymmetry_cutDijet', '', '', 0.92, 0.60, False],
		[ 'Norm', 'cosThetaStar_cutDijet', '', '', '', '', False],
		#[ 'Norm', 'jet1Subjet21MassRatio_cutDijet', '', '', '', '', False],
		[ 'Norm', 'jet1Subjet112MassRatio_cutDijet', '', '', '', '', False],
		[ 'Norm', 'jet1Subjet1JetMassRatio_cutDijet', '', '', '', '', False],
		[ 'Norm', 'jet1Subjet212MassRatio_cutDijet', '', '', '', '', False],
		[ 'Norm', 'jet1Subjet2JetMassRatio_cutDijet', '', '', '', '', False],
		[ 'Norm', 'jet2Subjet112MassRatio_cutDijet', '', '', '', '', False],
		[ 'Norm', 'jet2Subjet1JetMassRatio_cutDijet', '', '', '', '', False],
		[ 'Norm', 'jet2Subjet212MassRatio_cutDijet', '', '', '', '', False],
		[ 'Norm', 'jet2Subjet2JetMassRatio_cutDijet', '', '', '', '', False],
		[ 'Norm', 'subjetPtRatio_cutDijet', '', '', '', '', False],
		[ 'Norm', 'subjetMass21Ratio_cutDijet', '', '', '', '', False],
		[ 'Norm', 'subjet112MassRatio_cutDijet', '', '', '', '', False],
		[ 'Norm', 'subjet212MassRatio_cutDijet', '', '', '', '', False],
		[ 'Norm', 'subjetPolAngle13412_cutDijet', polAngXmin, polAngXmax, '', '', False],
		[ 'Norm', 'subjetPolAngle31234_cutDijet', polAngXmin, polAngXmax, '', '', False],
		[ 'Norm', 'cosThetaStar_cutAsym', '', '', '', '', False],
		#[ 'Norm', 'jet1Tau21_cutAsym', '', '', taulabX, taulabY, False],
		#[ 'Norm', 'jet1Tau31_cutAsym', '', '', taulabX, taulabY, False],
		#[ 'Norm', 'jet1Tau32_cutAsym', '', '', taulabX, taulabY, False],
		#[ 'Norm', 'subjetPtRatio_cutAsym', '', '', '', '', False],
		#[ 'Norm', 'subjetMass21Ratio_cutAsym', '', '', '', '', True],
		#[ 'Norm', 'subjet112MassRatio_cutAsym', '', '', '', '', True],
		#[ 'Norm', 'subjet212MassRatio_cutAsym', '', '', '', '', True],
		#[ 'Norm', 'subjetPolAngle13412_cutAsym', '', '', '', '', True],
		#[ 'Norm', 'subjetPolAngle31234_cutAsym', '', '', '', '', False],
		[ 'Norm', 'jet1Tau21_cutCosTheta', '', '', taulabX, taulabY, False],
		[ 'Norm', 'jet1Tau31_cutCosTheta', '', '', taulabX, taulabY, False],
		[ 'Norm', 'jet1Tau32_cutCosTheta', '', '', taulabX, taulabY, False],
		[ 'Norm', 'subjetPtRatio_cutCosTheta', '', '', '', '', False],
		#[ 'Norm', 'subjetMass21Ratio_cutCosTheta', '', '', '', '', True],
		#[ 'Norm', 'subjet112MassRatio_cutCosTheta', '', '', '', '', True],
		#[ 'Norm', 'subjet212MassRatio_cutCosTheta', '', '', '', '', True],
		[ 'Norm', 'subjetPolAngle13412_cutCosTheta', polAngXmin, polAngXmax, polAnglabX, polAnglabY, True],
		[ 'Norm', 'subjetPolAngle31234_cutCosTheta', polAngXmin, polAngXmax, polAnglabX, polAnglabY, True],
		#[ 'Norm', 'jet1Tau21_cutSubjetPtRatio', '', '', taulabX, taulabY, True],
		#[ 'Norm', 'jet1Tau31_cutSubjetPtRatio', '', '', taulabX, taulabY, True],
		#[ 'Norm', 'jet1Tau32_cutSubjetPtRatio', '', '', taulabX, taulabY, True],
		[ 'Norm', 'subjetMass21Ratio_cutSubjetPtRatio', '', '', '', '', True],
		[ 'Norm', 'subjet112MassRatio_cutSubjetPtRatio', '', '', '', '', True],
		[ 'Norm', 'subjet212MassRatio_cutSubjetPtRatio', '', '', '', '', True],
		[ 'Norm', 'subjetPolAngle13412_cutSubjetPtRatio', polAngXmin, polAngXmax, polAnglabX, polAnglabY, True],
		[ 'Norm', 'subjetPolAngle31234_cutSubjetPtRatio', polAngXmin, polAngXmax, polAnglabX, polAnglabY, True],
		[ 'Norm', 'subjetMass21Ratio_cutTau31', '', '', '', '', True],
		[ 'Norm', 'subjet112MassRatio_cutTau31', '', '', '', '', True],
		[ 'Norm', 'subjet212MassRatio_cutTau31', '', '', '', '', True],
		[ 'Norm', 'subjetPolAngle13412_cutTau31', polAngXmin, polAngXmax, polAnglabX, polAnglabY, True],
		[ 'Norm', 'subjetPolAngle31234_cutTau31', polAngXmin, polAngXmax, polAnglabX, polAnglabY, True],

		[ 'CF', 'cutflow', 10, True],
		[ 'CF', 'cutflowSimple', 10, True],

		[ 'simple', 'HT',  1000, '', '', False],
		[ 'simple', 'HT',  1000, '', '', True],
		[ 'simple', 'massAve_cutDijet',  massMaxX, '', '', False],
		[ 'simple', 'massAve_cutAsym',  massMaxX, '', '', False],
		[ 'simple', 'massAve_cutCosTheta',  massMaxX, '', '', False],
		[ 'simple', 'massAve_cutSubjetPtRatio',  massMaxX, '', '', False],
		#[ 'simple', 'massAve_cutSubjetPtRatio',  massMaxX, '', '', True ],
		[ 'simple', 'massAve_cutTau31',  massMaxX, '', '', False],
		[ 'simple', 'massAve_cutTau21',  massMaxX, '', '', False],

		[ 'mini', 'massAve_Standard', 0, massMaxX, '', '', False],
		[ 'mini', 'massAve_DeltaEtaSubjet', 0, massMaxX, '', '', False],
		[ 'mini', 'massAve_DeltaEtaTau21', 0, massMaxX, '', '', False],
		[ 'mini', 'massAve_Tau21', 0, massMaxX, '', '', False],
		[ 'mini', 'massAve_Tau21CosTheta', 0, massMaxX, '', '', False],
		[ 'mini', 'massAve_Tau21CosThetaDEta', 0, massMaxX, '', '', False],
		[ 'mini', 'massAve_DeltaEtaTau31', 0, massMaxX, '', '', False],
		[ 'mini', 'massAve_EffPFHT800', 0, massMaxX, '', '', False],
		[ 'mini', 'massAve_Brock', 0, massMaxX, '', '', False],
		[ '2dOpt', 'massAveVsHT', 'Average Pruned Mass [GeV]', 'HT [GeV]', 0, massMaxX, 1, 700, HTMaxX, 1, jetMassHTlabX, jetMassHTlabY],
		[ '2dOpt', 'massAsymVscosThetaStar', 'Mass asymmetry', 'cos #theta^{*}', 0, 1, 1, 0, 1, 1, jetMassHTlabX, jetMassHTlabY],

		[ 'opt', 'massAve_massAsym', ["%02d" % x for x in range(10)], 0, massMaxX, '', '', False],

		[ 'trigger', 'jetTrimmedMass', 'cutHT', 0, massMaxX, 1, triggerlabX, triggerlabY, True],
		[ 'trigger', 'jet1Mass', 'cutHT', 0, massMaxX, 1, triggerlabX, triggerlabY, True],
		[ 'trigger', 'massAve', 'cutDijet', 0, massMaxX, 2, triggerlabX, triggerlabY, True],
		[ 'trigger', 'massAve', 'cutMassAsym', 0, massMaxX, 2, triggerlabX, triggerlabY, False],
		[ 'trigger', 'massAve', 'cutCosTheta', 0, massMaxX, 2, triggerlabX, triggerlabY, False],
		[ 'trigger', 'massAve', 'cutSubjetPtRatio', 0, massMaxX, 2, triggerlabX, triggerlabY, False],
		[ 'trigger', 'HT', 'cutDijet', HTMinX, HTMaxX, 5, triggerlabX, triggerlabY, True],
		[ 'trigger', 'HT', 'cutMassAsym', HTMinX, HTMaxX, 5, triggerlabX, triggerlabY, True],
		[ 'trigger', 'HT', 'cutCosTheta', HTMinX, HTMaxX, 5, triggerlabX, triggerlabY, True],
		[ 'trigger', 'HT', 'cutSubjetPtRatio', HTMinX, HTMaxX, 5, triggerlabX, triggerlabY, True],
		[ 'trigger', 'jet1Mass', 'cutDijet', 0, massMaxX, 2, triggerlabX, triggerlabY, True],
		[ 'trigger', 'jet1Mass', 'cutMassAsym', 0, massMaxX, 2, triggerlabX, triggerlabY, True],
		[ 'trigger', 'jet1Mass', 'cutCosTheta', 0, massMaxX, 2, triggerlabX, triggerlabY, True],
		[ 'trigger', 'jet1Mass', 'cutSubjetPtRatio', 0, massMaxX, 2, triggerlabX, triggerlabY, True],
		[ 'trigger', 'jet1Pt', 'cutDijet', ptMinX, ptMaxX, 2, triggerlabX, triggerlabY, True],
		[ 'trigger', 'jet1Pt', 'cutMassAsym', ptMinX, ptMaxX, 2, triggerlabX, triggerlabY, True],
		[ 'trigger', 'jet1Pt', 'cutCosTheta', ptMinX, ptMaxX, 2, triggerlabX, triggerlabY, True],
		[ 'trigger', 'jet1Pt', 'cutSubjetPtRatio', ptMinX, ptMaxX, 2, triggerlabX, triggerlabY, True],
		[ 'trigger', 'trimmedMass', 'cutDijet', massMinX, massMaxX, 2, triggerlabX, triggerlabY, True],
		[ 'trigger', 'trimmedMass', 'cutMassAsym', massMinX, massMaxX, 2, triggerlabX, triggerlabY, True],
		[ 'trigger', 'trimmedMass', 'cutCosTheta', massMinX, massMaxX, 2, triggerlabX, triggerlabY, True],
		[ 'trigger', 'trimmedMass', 'cutSubjetPtRatio', massMinX, massMaxX, 2, triggerlabX, triggerlabY, True],
		[ 'trigger', 'ak4HT', 'cutDijet', HTMinX, HTMaxX, 5, triggerlabX, triggerlabY, True],
		[ 'trigger', 'ak4HT', 'cutMassAsym', HTMinX, HTMaxX, 5, triggerlabX, triggerlabY, True],
		[ 'trigger', 'ak4HT', 'cutCosTheta', HTMinX, HTMaxX, 5, triggerlabX, triggerlabY, True],
		[ 'trigger', 'ak4HT', 'cutSubjetPtRatio', HTMinX, HTMaxX, 5, triggerlabX, triggerlabY, True],

		#[ '2D', 'jetMassHTDenom_noTrigger', 'Leading Trimmed Jet Mass [GeV]', 'H_{T} [GeV]', 0, 200, 2, 100, HTMaxX, 5, 0.85, 0.2],
		#[ '2D', 'jetTrimmedMassHTDenom_noTrigger', 'Leading Trimmed Jet Mass [GeV]', 'H_{T} [GeV]', 0, 200, 2, 100, HTMaxX, 5, 0.85, 0.2],
		#[ '2D', 'jetMassHTDenom_triggerOne', 'Leading Trimmed Jet Mass [GeV]', 'H_{T} [GeV]', 0, 200, 2, 100, HTMaxX, 5, 0.85, 0.2],
		#[ '2D', 'jetMassHTDenom_triggerTwo', 'Leading Trimmed Jet Mass [GeV]', 'H_{T} [GeV]', 0, 200, 2, 100, HTMaxX, 5, 0.85, 0.2],
		#[ '2D', 'jetMassHTDenom_triggerOneAndTwo', 'Leading Trimmed Jet Mass [GeV]', 'H_{T} [GeV]', 0, 200, 2, 100, HTMaxX, 5, 0.85, 0.25],
		[ '2dtrig', 'jetMassHT', 'cutDijet', 20, 200, 2, HTMinX, 1200, 10, jetMassHTlabX+0.02, jetMassHTlabY+0.01],
		[ '2dtrig', 'jetMassHT', 'cutMassAsym', 20, 200, 2, HTMinX, 1200, 10, jetMassHTlabX+0.02, jetMassHTlabY+0.01],
		[ '2dtrig', 'jetMassHT', 'cutCosTheta', 20, 200, 2, HTMinX, 1200, 10, jetMassHTlabX+0.02, jetMassHTlabY+0.01],
		[ '2dtrig', 'jetMassHT', 'cutSubjetPtRatio', 20, 200, 2, HTMinX, 1200, 10, jetMassHTlabX+0.02, jetMassHTlabY+0.01],
		[ '2dtrig', 'jetTrimmedMassHT', 'cutDijet', 20, 200, 2, HTMinX, 1200, 10, jetMassHTlabX+0.02, jetMassHTlabY+0.01],
		[ '2dtrig', 'jetTrimmedMassHT', 'cutMassAsym', 20, 200, 2, HTMinX, 1200, 10, jetMassHTlabX+0.02, jetMassHTlabY+0.01],
		[ '2dtrig', 'jetTrimmedMassHT', 'cutCosTheta', 20, 200, 2, HTMinX, 1200, 10, jetMassHTlabX+0.02, jetMassHTlabY+0.01],
		[ '2dtrig', 'jetTrimmedMassHT', 'cutSubjetPtRatio', 20, 200, 2, HTMinX, 1200, 10, jetMassHTlabX+0.02, jetMassHTlabY+0.01],
		[ '2dtrig', 'massAveHT', 'cutDijet', 20, 200, 2, HTMinX, 1200, 10, jetMassHTlabX+0.02, jetMassHTlabY+0.01],
		[ '2dtrig', 'massAveHT', 'cutMassAsym', 20, 200, 2, HTMinX, 1200, 10, jetMassHTlabX+0.02, jetMassHTlabY+0.01],
		[ '2dtrig', 'massAveHT', 'cutCosTheta', 20, 200, 2, HTMinX, 1200, 10, jetMassHTlabX+0.02, jetMassHTlabY+0.01],
		[ '2dtrig', 'massAveHT', 'cutSubjetPtRatio', 20, 200, 2, HTMinX, 1200, 10, jetMassHTlabX+0.02, jetMassHTlabY+0.01],
		]

	if 'all' in single: Plots = [ x[1:] for x in plotList if x[0] in process ]
	else: Plots = [ y[1:] for y in plotList if ( ( y[0] in process ) and ( y[1] in single ) )  ]

	if 'all' in grom: Groomers = [ '', 'Trimmed', 'Pruned', 'Filtered' ]
	else: Grommers = [ grom ]

	if 'all' in triggerUsed: Triggers = [ 'PFHT800', 'AK8PFHT700TrimMass50' ]
	#else: Triggers = [ triggerUsed.replace('TrimMass50','').replace('AK8','AK') ]
	else: Triggers = [ triggerUsed ]

	if 'all' in cut: selection = [ '_cutDijet', '_cutMassAsym', '_cutTau21', '_cutCosTheta', '_cutDEta', '_cutBtag' ]
	elif 'NO' in cut: selection = [ '_cutNOMassAsym', '_cutTau21_NOMA', '_cutCosTheta_NOMA', '_cutDEta_NOMA', '_cutBtag_NOMA' ]
	else: selection = [ cut ]

	for i in Plots:
		for optGrom in Grommers:
			if '2D' in process: 
				plot2D( inputFileSignal, 'RPVSt100to'+jj, optGrom, i[0], i[1], i[2], i[3], i[4], i[5], i[6], i[7], i[8], i[9], i[10], PU )
				plot2D( inputFileQCD, 'QCD'+qcd, optGrom, i[0], i[1], i[2], i[3], i[4], i[5], i[6], i[7], i[8], i[9], i[10], PU )
				plot2D( inputFileTTJets, 'TTJets', optGrom, i[0], i[1], i[2], i[3], i[4], i[5], i[6], i[7], i[8], i[9], i[10], PU )
				plot2D( inputFileWJetsToQQ, 'WJets', optGrom, i[0], i[1], i[2], i[3], i[4], i[5], i[6], i[7], i[8], i[9], i[10], PU )
				plot2D( inputFileZJetsToQQ, 'ZJets', optGrom, i[0], i[1], i[2], i[3], i[4], i[5], i[6], i[7], i[8], i[9], i[10], PU )

			elif '1D' in process:
				for cut1 in selection:
					print cut1
					plot( inputFileSignal, inputFileSignal200, inputFileQCD, 0.8, inputFileWJetsToQQ, inputFileWJetsToQQ, inputFileZJetsToQQ, optGrom, boosted+'AnalysisPlots'+optGrom+'/'+i[0]+cut1, i[0]+cut1, i[1], i[2], i[3], i[4], i[5], PU )
			
			elif 'qual' in process:
				for cut1 in selection:
					plotQuality( inputFileData, inputFileQCD, 1.0, inputFileWJetsToQQ, inputFileWJetsToQQ, inputFileZJetsToQQ, optGrom, boosted+'AnalysisPlots'+optGrom+'/'+i[0]+cut1, i[0]+cut1, i[1], i[2], i[3], i[4], i[5], PU )
			
			elif 'mini' in process:
				plot( inputMiniFileSignal, inputMiniFileSignal200, inputMiniFileQCD, 0.8, inputMiniFileTTJets, inputMiniFileWJetsToQQ, inputMiniFileZJetsToQQ, optGrom, i[0], i[0], i[1], i[2], i[3], i[4], i[5], PU )
			
			elif 'Norm' in process:
				plot( inputFileSignal, inputFileSignal200, inputFileQCD, 0.8, inputFileTTJets, inputFileWJetsToQQ, inputFileZJetsToQQ, optGrom, boosted+'AnalysisPlots'+optGrom+'/'+i[0], i[0], i[1], i[2], i[3], i[4], i[5], PU, True )

			elif 'CF' in process:
				plotCutFlow( inputFileSignal, inputFileQCD, inputFileTTJets, inputFileWJetsToQQ, inputFileZJetsToQQ, optGrom, i[0], i[1], i[2], PU, True )

			elif 'simple' in process:
				plotSimple( inputFileTTJets, 'TTJets', optGrom, i[0], i[1], i[2], i[3], i[4], PU )
				plotSimple( inputFileWJetsToQQ, 'WJets', optGrom, i[0], i[1], i[2], i[3], i[4], PU )
				plotSimple( inputFileZJetsToQQ, 'ZJets', optGrom, i[0], i[1], i[2], i[3], i[4], PU )
			
			elif 'opt' in process:
				plotOptimization( inputMiniFileSignal, inputMiniFileQCD, optGrom, i[0], i[1], i[2], i[3], i[4], True )

			elif '2dOpt' in process: 
				plot2DOptimization( inputMiniFileSignal, inputMiniFileQCD, optGrom, i[0], i[1], i[2], i[3], i[4], i[5], i[6], i[7], i[8], i[9], i[10], PU )

			elif 'trigger' in process:
				for trig in Triggers:
					#tmpplotTriggerEfficiency( inputTrigger, SAMPLE, 'PFHT475', trig, i[0], i[1], i[2], i[3], i[4], i[5], i[6], i[7] )
					plotTriggerEfficiency( inputTrigger, SAMPLE, 'PFHT475', trig, i[0], i[1], i[2], i[3], i[4], i[5], i[6], i[7] )
					#plotTriggerEfficiency( inputTrigger, SAMPLE, 'PFMET170', trig, i[0], i[1], i[2], i[3], i[4], i[5], i[6], i[7] )
					#plotTriggerEfficiency( inputTrigger, SAMPLE, 'IsoMu17', trig, i[0], i[1], i[2], i[3], i[4], i[5], i[6], i[7] )
			elif '2dtrig' in process:
				for trig in Triggers:
					plot2DTriggerEfficiency( inputTrigger, SAMPLE, BASEDTrigger, trig, i[0], i[1], i[2], i[3], i[4], i[5], i[6], i[7], i[8], i[9] )
					#plot2DTriggerEfficiency( inputTrigger, SAMPLE, 'IsoMu17', trig, i[0], i[1], i[2], i[3], i[4], i[5], i[6], i[7], i[8], i[9] )



