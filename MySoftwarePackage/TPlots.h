//  TPlots.h
//  Created by Erez Cohen on 2/24/15.

#ifndef __TPLOTS_H__
#define __TPLOTS_H__
#include "myIncludes.h"

class TPlots{
    
private:
    
    Int_t i_plot;
    
    
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
    void MergeFiles ( TString, const int N, char ** fName, char *, char *);
    void Close () {File->Close();} ;
    
    //plots
    TCanvas * CreateCanvas(TString Title, TString DoDivide="NoDivision", int Nx=4, int Ny=2, float w=800, float h=800);
    
    TH1F *                H1 ( TString, TCut, TString, int, double, double,TString T="",TString XT="",TString YT="",int c=1, int fc=38,int fStyle=1001);
    
    TH2F *                H2 ( TString, TString, TCut, TString, int, double, double, int, double, double,TString T="",TString XT="",TString YT="", int c=1,int s=7,double a=0.9, double mSize=1);
    
    TH3F *                H3 ( TString, TString, TString, TCut, TString
                              ,int,double,double,int,double,double,int,double,double, TString T="",TString XT="",TString YT="",TString ZT="",int c=1,int s=7,double a=0.3, double mSize=1);
    
    TPie *               Pie (TString , TString , const int , Float_t* , Int_t*, TString*, TString option="3d");
    
    TH2F * H2WithProjections ( TString, TString, TCut, int, double, double,int, double, double, TString T="", TString XT="", TString YT="");
    
    TH2F *            Dalitz ( TString, TString, TString, TCut, int Nx=100,double xl=-1.7,double xu=1.7,int Ny=100,double yl=-1.1,double yu=2, TString Tit1="", TString Tit2="", TString Tit3="", TString option="colz",int color=1, bool DoText=false);
    

    TH1F *             H1step ( TString, TCut, TString, int, double, double,TString T="",TString XT="",TString YT="",int c=1, int fc=38,int fStyle=1001);
    TH1F *       H1stepOfVarX ( TString, TString, TCut, TString, int, double, double, int, double, double,TString T="",TString XT="",TString YT="", double Ymin=0., double Ymax=5);

    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    void  MultipleHistograms (int,TH1 **,TString *,double xl=0,double xh=1,TString T="",TString XT="",TString YT="",int *colors=nullptr,int fStyle=0);
    
    
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    // legend
    void AddLegend(int N , TH1 ** h, TString * Labels ,Option_t * option = "F", bool mean = false){
        TLegend * leg = new TLegend( 0.1 , 0.8 , 0.8 , 0.85 );
        leg -> SetLineColor(1);
        leg -> SetTextSize(0.04);
        for (int i = 0 ; i < N ; i++){
            if (mean)
                leg -> AddEntry ( h[i] , Form("%s, #mu=%.3f",Labels[i].Data(),h[i]->GetMean()) , option );
            else
                leg -> AddEntry ( h[i] , Labels[i] , option );
        }
        leg -> Draw();
    }
    void AddLegend(TH1 * h1, TString l1, TH1 * h2, TString l2, Option_t * option = "p"){
        TH1 * h[2] = {h1,h2};
        TString Labels[2];
        Labels[0] = l1 ;//+ Form(" (%d)",(int)h1->GetEntries());
        Labels[1] = l2 ;//+ Form(" (%d)",(int)h2->GetEntries());
        AddLegend( 2 , h , Labels, option);
    }
    void AddLegend(TH1 * h1, TString l1, TH1 * h2, TString l2, TH1 * h3, TString l3, Option_t * option = "l"){
        TH1 * h[3] = {h1,h2,h3};
        TString Labels[3] = {l1,l2,l3};
        AddLegend( 3 , h , Labels, option);
    }

    
    
    
    
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    // general graph (with errors!)
    TGraphErrors * Graph ( TString, const int, double*, double*, double*, double*, TString T="", TString XT="", TString YT="", int c=4, double mSize = 0.5, int mStyle = 21, TString option = "");
    TGraphErrors * Graph ( TString, const int N , double* , double* , TString Title = "" , TString XTitle = "" , TString YTitle = "" , int color = 4 , double mSize = 0.5 , int mStyle = 21 , Option_t * option = "");
    TGraph       * Graph ( const int N , double* , double* , TString Title = "" , TString XTitle = "" , TString YTitle = "" , int color = 4 , int style = 1 , TString option = "");
    
    void Graphs( const int N , TGraphErrors** , TString* , int *, double* , double*
                , double** , double** , double*
                , TString Title = "", TString XTitle = "", TString YTitle = ""
                , double mSize = 1., int mStyle = 21
                , double XMin=0, double Xmax=10, double YMin=0, double Ymax=10
                , bool FitGraphs = false , int *LineColors = 0,  bool DoAddLegend = true, bool addfit2leg = false);
    
    
    // service to all classes
    TH1F * DrawFrame(TString, int, double, double, double Ymin = 0 , double Ymax = 1 , TString XTitle = ""  ,TString Ytitle = "" );
    void SetAxisTitle(TAxis * , TString , double Offset = 1.3 , double TitleSize = 0.055 , double LabelSize = 0.05);
    
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    template <typename T>
    void SetFrame( T * frame, TString Title="", TString XTitle="", TString YTitle="", TString ZTitle=""
                  , int color=4 , int FillColor=46, int FillStyle=1001, int mStyle=20 , double mSize=0.5 , double Alpha=0.99 ){
        frame -> SetTitle( Title );
        SetAxisTitle(frame -> GetXaxis() , XTitle);
        SetAxisTitle(frame -> GetYaxis() , YTitle);
        if(typeid(frame)==typeid(TH3F)) SetAxisTitle(((TH1F*)frame) -> GetZaxis() , ZTitle);
        frame -> SetLineColor(color);
        frame -> SetFillColor(FillColor);
        frame -> SetFillStyle(FillStyle);
        frame -> SetMarkerStyle(mStyle);
        frame -> SetMarkerSize(mSize);
        frame -> SetMarkerColorAlpha(color,Alpha);
    }
    
    
    
    
    
    
    void H1Frame ( int , double , double , TString Title = "" , TString XTitle = "" , TString YTitle = "" , double Ylow = 0 , double Yup = 1);
    void H2Frame ( double , double , double , double , TString Title = "" , TString XTitle = "" , TString YTitle = "" );
    
    Float_t CalculateRatioOfEvents2D( TH2F*, TH2F*, Float_t, Float_t, Float_t, Float_t );
    
    
    TGaxis        * Axis ( double , double , double , double , double , double , int , TString );
    TLine         * Line ( double , double , double , double , int c = 1 , int w = 1 , int s = 1 , double o = 1 );
    TArrow       * Arrow ( double , double , double , double , int c = 1 , int w = 1 , int s = 1 , double o = 1 , double size = 0.005);
    TLatex        * Text ( double X , double Y , TString label="" , int color = 1, double size = 0.05 , double Angle = 0 , float alpha = 1 );
    TLatex       * Latex ( double X , double Y , TString label="" , int color = 1, double size = 0.05 , double Angle = 0 );
    TBox           * Box ( double XMin , double YMin , double XMax , double YMax , int color = 46 , double opacity = 1 , int LineWidth = 1);
    TEllipse    * Circle ( double X , double Y , double R = 1. , int color = 1, double opacity = 1, int LineColor = 1 , int LineWidth = 1 );
    TPolyLine3D * Line3D ( TVector3 , int LineColor = 1 , int LineWidth = 1 , int LineStyle = 1 );
    void             ROI ( double XMin , double YMin , double XMax , double YMax , int color = 0);

    void Plot3DAxesSystem( float size = 0.5 );
    void Frame3D        (TString);
    
    
    
    
    // prints
    TString    PercentPrint (double x)  {return Form("%.1f\\%%",100.*x);};      // to Latex...
    TString    PercentPrint (float x)   {return PercentPrint((double)x);};
    TString      PercentStr (double x)  {return Form("%.1f%%",100.*x);};      // to screen...
    TString      PercentStr (float x)   {return PercentPrint((double)x);};
    void    PrintPercentStr (double x)  {Printf("[%s]",PercentStr(x).Data());};
    
    
    
    
    
    // input / output files
    TH1F * ReScaleAxis  (TH1F *, double, double);
    
    
    // TCuts
    TCut     CutOnAngle (TString, TString, float, float);
    TString       Theta (TString, TString);
    TString    CosTheta (TString, TString);
    
    
    // TTree functionality
    float GetBranchSum (TString,TCut);
    void      SetAlias (TString v1,TString v2) {Tree->SetAlias(v1,v2);};
    
    
    // drawing with TCuts
    void      Draw1DVarAndCut (TCanvas *, int, TString, int, float, float, TString, TString, TCut, bool DoLeg = false, TString cName = "");
    TCanvas * Draw1DVarAndCut (TString , int, float, float, TString, TString, TCut, bool DoLeg = false, TString cName = "");
    void      Draw2DVarAndCut (TCanvas *, int, TString , TString, int, float, float, int, float, float, TString, TString, TString, TCut, bool DoAddLegend = false, TString CutName = "");
    TCanvas * Draw2DVarAndCut (TString , TString, int, float, float, int, float, float, TString, TString, TString, TCut, bool DoAddLegend = false, TString CutName = "");
    
    
    
    // GETs
    TFile *     GetFile (){ return File; };
    TTree *     GetTree (){ return Tree; };
    int      GetEntries ( TCut cut = "" ){ return (int)Tree->GetEntries(cut); };
    TString GetFileName (){return (TString)(File->GetName());};
    
};


#endif









//    //legend // delete may 19
//    template <typename T>
//    void AddLegend (int, T ** , TString *, Option_t * o = "F"  , bool mean = false );
//    template <typename T>
//    void AddLegend (T *, TString, T *, TString, Option_t * o = "p");
//    void AddLegend (TH1F *, TString, TH1F *, TString, TH1F *, TString, Option_t * o = "l");
//


//// angles
//TH1F * Angle(TString,TString, TCut cut="", TString o="", TString T="", TString XT="", TString YT="" , int c=1, int N=46, double Xl=0, double Xu=180.);
//TH1F * CosAngle(TString,TString, TCut cut="", TString o="", TString T="", TString XT="", TString YT="" , int c=1, int N=23, double Xl=-1, double Xu=1);

//    void AddLegend (int, TH1F ** , TString *, Option_t * option = "F"  , bool mean = false );
//    void AddLegend (int, TProfile ** , TString * );
//    void AddLegend (int, TH2F ** , TString * , Option_t * option = "p" );
//    void AddLegend (int, TGraphErrors ** ,  TString * Labels , Option_t * option = "l");
//    void AddLegend (int, TGraph ** ,  TString * Labels , Option_t * option = "l");
//    void AddLegend (TH1F *, TString, TH1F *, TString, Option_t * o = "p");
//    void AddLegend (TH2F *, TString, TH2F *, TString, Option_t * o = "p");
//    void AddLegend (TH3F *, TString, TH3F *, TString, Option_t * o = "p");


//    void SetFrame( TH1F *, TString t="", TString Xt="", TString Yt="", int c=1, int fc=0 , int fStyle=3003 );
//    void SetFrame( TH2F *, TString t="", TString Xt="", TString Yt="", int c=1, int mStyle=20 , double mSize=0.5 , double a=0.99);
//    void SetFrame( TH3F *, TString t="", TString Xt="", TString Yt="", TString Zt="", int c=1 , int mStyle=20 , double mSize=0.5 , double a=0.99);
//    void SetFrame( TGraphErrors *, TString T="", TString XT="", TString YT="",int c=1, int mStyle=20, double mSize=0.5, double Alpha=0.99);
//    void SetFrame( TGraph * g, TString T="", TString XT="", TString YT="",int c=1, int mStyle=20, double mSize=0.5, double Alpha=0.99);
//    void SetFrame( TProfile * p, TString t="", TString Xt="", TString Yt="", int c=1 );
//    void SetFrame( TF1 *, TString t="", TString Xt="", TString Yt="", int c=1, int fc=0 , int fStyle=3003 );
//    void SetFrame( TF2 *, TString t="", TString Xt="", TString Yt="", int c=1, int mStyle=20 , double mSize=0.5 , double a=0.99);

