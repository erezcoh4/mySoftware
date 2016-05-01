//
//  TAnalysis.h
//
//
//  Created by Erez Cohen on 5/15/15.
//
//
#include "myIncludes.h"
#include "TPlots.h"




#ifndef __TANALYSIS_H__
#define __TANALYSIS_H__

class TAnalysis{
    
    
private:
    
    
public:
    
    int     i_ana;
    TPlots  plot;
    
    // constructor
    TAnalysis                   ();
    ~TAnalysis                  (){};
    
    //    //Unbinned RooFit of 1d Histogram
    //    RooPlot * RooFit1D          ( TTree * , TString , Double_t *  , Double_t * , Double_t * , TString , bool PlotFit = true , bool DoWeight = false );
    Double_t Kolmogorov1D       (Int_t, Double_t*, Int_t, Double_t*, Option_t* option="");
    Double_t Kolmogorov1DCriticalValue( Double_t , int , int );
    void Sort                   (Int_t, Double_t*);
    
    
    
    Double_t    IntegralH2D (TH2F * h,Double_t Xlow, Double_t Ylow, Double_t Xup, Double_t Yup,bool DoDrawBox=false, int color = 1);
    Double_t    IntegralH1D (TH1F * h,Double_t Xlow, Double_t Xup);
    Double_t        TH1Frac (TH1F * histo , Double_t Xlow, Double_t Xup);
    
    TH1F*   RatioOfHistograms (TString, TH1F *, TH1F *,TString,TString,int col = 38);
    void   PlotHRefAndHRatios (TString, TH1F *, int, const int, TH1F **, TString, TString, int*);
    TH1F*   CombineHistograms (char *, TH1F *, TH1F *,TString,TString,int col = 38);
    TH1F*  GetPartOfHistogram (char *, TH1F *, double, double);
    void   NormalizeHistogram (TH1F *);
    float              GetS2N (TH1 *, TH1 *);
    double            GetFWHM (TH1 *);
    
    
    
    
    
    // get from file...
    TH1F *      GetHistoFromAFile (TString, TString);
    TH2F *         GetH2FromAFile (TString, TString);
    TProfile * GetProfileFromFile (TString, TString);

    
    
  
    void       PlotGraphDataToFile (TString,const int,double*,double*,double*,double*);
    void     ReadGraphDataFromFile (TString,const int,double*,double*,double*,double*);
    void         ReadGraphFromFile (TString,const int,double*,double*);
    TGraph     * ReadGraphFromFile (TString,const int);
    
    
    
    TH2F               * Assymetry (TTree *, TString, TString, int, Float_t, Float_t, TString , int , Float_t, Float_t , TString, bool DoPrint = false);
    RooPlot             * RooFit1D (TTree *, TString, TCut, Double_t*, Double_t*, bool Plot = false );
    RooRealVar  SubtractBackground (TH2F *, float aSig, float axBkg, bool DoPlot = false);
   
    
    
};


#endif
