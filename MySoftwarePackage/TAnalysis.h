//
//  TAnalysis.h
//
//
//  Created by Erez Cohen on 5/15/15.
//
//
#include "TPlots.h"


#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "RooConstVar.h"
#include "RooFormulaVar.h"
#include "RooGenericPdf.h"
#include "RooPolynomial.h"
#include "RooChi2Var.h"
#include "RooMinuit.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TMatrix.h"
#include "RooPlot.h"




#ifndef __TANALYSIS_H__
#define __TANALYSIS_H__

class TAnalysis{
    
    
private:
    
    
public:
    
    int i_ana;
    
    // constructor
    TAnalysis                   ();
    ~TAnalysis                  (){};
    
    //    //RooFit 1d Histogram
    //    RooPlot * RooFitHistogram   ( TH1F * , double & , double & , double & , double & , TString  , bool PlotFit = true);
    //
    //
    //    //Unbinned RooFit of 1d Histogram
    //    RooPlot * RooFit1D          ( TTree * , TString , Double_t *  , Double_t * , Double_t * , TString , bool PlotFit = true , bool DoWeight = false );
    Double_t Kolmogorov1D       (Int_t, Double_t*, Int_t, Double_t*, Option_t* option="");
    Double_t Kolmogorov1DCriticalValue( Double_t , int , int );
    void Sort                   (Int_t, Double_t*);
    
    Double_t EnergyTestHisto2D  (Int_t, Int_t, TH2F*, TH2F*);
    Double_t EnergyTestUnbinned3D(std::vector<TVector3>, std::vector<TVector3>);
    Double_t WeightingFunc      (Double_t, int);
    
    
    // particular used for ppCM motion analysis (acceptance corrections...)
    float ppCMEnergyTest        (char * name, TTree* , TTree *,bool histos=false);
    Double_t EnergyTestUnbinned3D(int ND, int NMC, float**, float**, float**);
    float stdev                 (std::vector<float> v);
    
    Double_t ETestHisto3D       (TH3F*, TH3F*/*, const int*/);
    //    Double_t EtestPsi           (int i1, int i2, int i3, int j1,int j2, int j3, double);
    
    Double_t IntegralH2D        (TH2F * h,Double_t Xlow, Double_t Ylow, Double_t Xup, Double_t Yup,bool DoDrawBox=false);
    Double_t IntegralH1D        (TH1F * h,Double_t Xlow, Double_t Xup);
    Double_t TH1Frac            (TH1F * histo , Double_t Xlow, Double_t Xup);
    
    TH1F* RatioOfHistograms     (TString, TH1F *, TH1F *,TString,TString,int col = 38);
    void PlotHRefAndHRatios     (TString, TH1F *, int, const int, TH1F **, TString, TString, int*);
    TH1F* CombineHistograms     (char *, TH1F *, TH1F *,TString,TString,int col = 38);
    TH1F* GetHistoFromAFile     (char *, char *);
    TH1F* GetPartOfHistogram    (char *, TH1F *, double, double);
    void NormalizeHistogram     (TH1F *);
    float GetS2N                (TH1 *, TH1 *);
    double * SubtractBackground (TH2F *, double , float Bkg2SigBox= 1, float x0 = 0, float y0 = 0);
    
    
};


#endif
