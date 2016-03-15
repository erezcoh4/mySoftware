//
//  TPlots.h
//
//
//  Created by Erez Cohen on 2/24/15.
//
//

#ifndef __TPLOTS_H__
#define __TPLOTS_H__

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>
#include <numeric>
#include <string>
#include <functional>
#include <stdlib.h>
#include <fstream>
#include <algorithm>
#include <functional>
#include "TRotation.h"
#include <TTimeStamp.h>
#include <TStopwatch.h>
#include <TString.h>
#include <TSystem.h>
#include <TLine.h>
#include <TArrow.h>
#include <TFile.h>
#include <TTree.h>
#include <TROOT.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TH3F.h>
#include <TProfile.h>
#include <TPad.h>
#include <TStyle.h>
#include <TMultiGraph.h>
#include <TGraphErrors.h>
#include <TLegend.h>
#include <TPaveStats.h>
#include <TChain.h>
#include <TBranch.h>
#include <TLeaf.h>
#include <TMath.h>
#include <TCut.h>
#include <TLorentzVector.h>
#include <TVector2.h>
#include <TVector3.h>
#include <TPie.h>
#include <TLatex.h>
#include <TEllipse.h>
#include <TPolyLine3D.h>
#include <TRandom2.h>
#include <THStack.h>
#include <TSpectrum.h>
#include <TSpectrum2.h>
#include <TUnfoldSys.h>
#include <TCutG.h>
#include <TGeoSphere.h>
#include <TBox.h>


using namespace std;

// important prints....
#define PrintLine() std::cout << "-------------------------------" << std::endl;
#define SHOW(a) std::cout << #a << ": " << (a) << std::endl
#define SHOWstdTVector3(v) { std::cout << #v << " ( " << v.size() << " entries ):\t";     for (std::vector<TVector3>::iterator it=v.begin(); it!=v.end(); ++it) std::cout << "(" << it -> X() << ","  << it -> Y() << "," << it -> Z() << ")\t"; std::cout << '\n';}

class TPlots{
    
private:
    
    Int_t i_plot;         // for ploting multiple histograms...
    
    
    
    
public:
    //date
    TTimeStamp ts;
    TString fName;
    
    //tree
    TFile * File;
    TTree * Tree;
    TChain * chain;
    int Nentries;
    
    TH1F * h[100];
    TH2F * h2[100];
    TH3F * h3[100];
    bool QuietMode;
    
    // constructors
    ~TPlots   (){};
    TPlots    (){i_plot = 0;};
    TPlots    ( TTree * tree , TString );
    TPlots    ( TString FileName, TString TreeName , TString Name="" , bool fQuietMode  = true);
    TPlots    ( TString TName, TString F1Name, TString F2Name, TString Path, TString NewFileName = "Merged", bool fQuietMode  = false);
    
    
    // methods
    TFile * GetFile (){ return File; };
    TTree * GetTree (){ return Tree; };
    
    
    void MergeFiles ( TString, const int N, char ** fName, char *, char *);
    
    //plots
    TCanvas * CreateCanvas(TString Title, TString DoDivide="NoDivision", int Nx=4, int Ny=2, float w=800, float h=800);
    
    TH1F *  H1 ( TString, TCut, TString, int Nbins=10, double Xlow=0, double Xup=1
                , TString T="",  TString XT="", TString YT="", int c=1, int fc=0,int fStyle=3004);
    TH2F *  H2 ( TString, TString, TCut, TString, int NbinX=6, double Xlow=-3, double Xup=3, int NbinY=4, double Ylow=0, double Yup=4
                , TString Title="", TString XTitle="", TString YTitle=""
                , int color=1, int style=7, float Alpha=0.9, double mSize=1. );
    TH3F *  H3 ( TString, TString, TString, TCut, TString
                , int NbinX=6, double Xlow=-3, double Xup=3, int NbinY=4, double Ylow=0, double Yup=4, int NbinZ=4, double Zlow=0, double Zup=4
                , TString Title="", TString XTitle="", TString YTitle="", TString ZTitle=""
                , int color=1, int style=7, float Alpha=0.3, double mSize=1. );
    
    
    TPie * Pie(TString , TString , const int , Float_t* , Int_t*, TString*, TString option="3d");
    
    
    TH2F * H2WithProjections( TString, TString, TCut, int NbinX=6, double Xlow=-3, double Xup=3, int NbinY=4, double Ylow=0, double Yup=4
                             , TString Title="", TString XTitle="", TString YTitle="");
    
    
    // angles
    TH1F * Angle(TString,TString, TCut cut="", TString o="", TString T="", TString XT="", TString YT="" , int c=1, int N=46, double Xl=0, double Xu=180.);
    TH1F * CosAngle(TString,TString, TCut cut="", TString o="", TString T="", TString XT="", TString YT="" , int c=1, int N=23, double Xl=-1, double Xu=1);
    
    
    TH2F * AngularCorrelation(TString, TString,TString, TString, TCut cut="", TString o=""
                              , TString T="", TString XT="", TString YT="" , int c=1, int N=46, double Xl=0, double Xu=180., int style=20, float Alpha=0.9, double mSize=0.4);
    
    
    
    
    //legend
    void AddLegend (TString , const int N, TH1F ** h , TString * Labels , int Ncol = 1 , Option_t * option = "F"  , bool mean = false );
    void AddLegend (TString , const int N, TH2F ** h , TString * Labels , int Ncol = 1 , Option_t * option = "p" );
    void AddLegend (TString , const int N, TGraphErrors ** g ,  TString * Labels , int Ncol = 1 , Option_t * option = "p");
    void AddLegend (TString , TH1F *, TString, TH1F *, TString, Option_t * o = "p");
    void AddLegend (TString , TH2F *, TString, TH2F *, TString, Option_t * o = "p");
    void AddLegend (TString , TH3F *, TString, TH3F *, TString, Option_t * o = "p");
    
    // general graph (with errors!)
    TGraphErrors * Graph( TString, const int, double*, double*, double*, double*, TString T="", TString XT="", TString YT="", int c=4, double mSize = 0.5, int mStyle = 21, TString option = "");
    TGraphErrors * Graph( TString, const int N , double* , double* , TString Title = "" , TString XTitle = "" , TString YTitle = "" , int color = 4 , double mSize = 0.5 , int mStyle = 21 , Option_t * option = "");
    
    void Graphs( const int N , TGraphErrors** , TString* , int *, double* , double*
                , double** , double** , double*
                , TString Title = "", TString XTitle = "", TString YTitle = ""
                , double mSize = 1., int mStyle = 21
                , double XMin=0, double Xmax=10, double YMin=0, double Ymax=10
                , bool FitGraphs = false , int LineColors[N] = 0,  bool DoAddLegend = true, bool addfit2leg = false);
    
    //    void Graphs( const int, TGraphErrors**, TString*
    //                , TString, TString, TString
    //                , double, int
    //                , double, double, double, double
    //                , int* , bool addleg = true);
    
    
    
    // multiple histograms
    void Histograms( const int NHist , TH1F ** h  , TString * Labels, TString Title = "" , TString XTitle = "" , TString YTitle = "" ,double XMin = 0 , double XMax = 10 , double YMax = 1 , bool mean = true );
    
    // service to all classes
    TH1F * DrawFrame(char *, TString, int, double, double, double Ymin = 0 , double Ymax = 1 , TString XTitle = ""  ,TString Ytitle = "" );
    void SetAxisTitle(TAxis * , TString , double Offset = 1 , double TitleSize = 0.055 , double LabelSize = 0.05);
    void SetFrame( TH1F *, TString t="", TString Xt="", TString Yt="", int c=1, int fc=0 , int fStyle=3003 );
    void SetFrame( TH2F *, TString t="", TString Xt="", TString Yt="", int c=1, int mStyle=20 , double mSize=0.5 , double a=0.99);
    void SetFrame( TH3F *, TString t="", TString Xt="", TString Yt="", TString Zt="", int c=1 , int mStyle=20 , double mSize=0.5 , double a=0.99);
    void SetFrame( TGraphErrors *, TString T="", TString XT="", TString YT="",int c=1, int mStyle=20, double mSize=0.5, double Alpha=0.99);
    void SetFrame( TGraph * g, TString T="", TString XT="", TString YT="",int c=1, int mStyle=20, double mSize=0.5, double Alpha=0.99);
    
    
    
    
    void H1Frame( int , double , double , TString Title = "" , TString XTitle = "" , TString YTitle = "" , double Ylow = 0 , double Yup = 1);
    void H2Frame( double , double , double , double , TString Title = "" , TString XTitle = "" , TString YTitle = "" );
    
    Float_t CalculateRatioOfEvents2D( TH2F*, TH2F*, Float_t, Float_t, Float_t, Float_t );
    
    
    TLine * Line        ( double , double , double , double , int c = 1 , int w = 1 , int s = 1 , double o = 1 );
    TArrow * Arrow      ( double , double , double , double , int c = 1 , int w = 1 , int s = 1 , double o = 1 , double size = 0.005);
    TLatex * Text       ( double X , double Y , TString label="" , int color = 1, double size = 0.05 , double Angle = 0 );
    TLatex * Latex      ( double X , double Y , TString label="" , int color = 1, double size = 0.05 , double Angle = 0 );
    TBox * Box          ( double XMin , double YMin , double XMax , double YMax , int color = 46 , double opacity = 1 , int LineWidth = 1);
    TEllipse * Circle   ( double X , double Y , double R = 1. , int color = 1, double opacity = 1, int LineColor = 1 , int LineWidth = 1 );
    TPolyLine3D * Line3D( TVector3 , int LineColor = 1 , int LineWidth = 1 , int LineStyle = 1 );
    void Plot3DAxesSystem( float size = 0.5 );
    void Frame3D        (TString);
    
    
    
    
    // prints
    void PrintOut3Vector(  TVector3 , TString );
    void Print4Momentum ( TLorentzVector Vec4 , TString Name );
    void PrintstdTVector3(char * , std::vector<TVector3>);
    void PrintOutMatrix (char *, const int N, const int M, double **mat);
    TString PercentPrint(double x)  {return Form("%.1f\\%%",100.*x);};      // to Latex...
    TString PercentPrint(float x)   {return PercentPrint((double)x);};
    TString PercentStr(double x)  {return Form("%.1f%%",100.*x);};      // to screen...
    TString PercentStr(float x)   {return PercentPrint((double)x);};
    
    
    
    
    // input / output files
    void PlotGraphDataToFile(char *,const int,double*,double*,double*,double*);
    void ReadGraphDataFromFile(char *,const int,double*,double*,double*,double*);
    TH1F * ReScaleAxis  (TH1F *, double, double);
    
    
    // TCuts
    TCut CutOnAngle     (TString, TString, float, float);
    TString Theta       (TString, TString);
    TString CosTheta    (TString, TString);
    
    
    // TTree functionality
    float GetBranchSum  (TString,TCut);
    void SetAlias       (TString v1,TString v2) {Tree->SetAlias(v1,v2);};
    
    
    
};


#endif



