//  TPlots.cpp
//  Created by Erez Cohen on 2/24/15.
#include "TPlots.h"



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TPlots::TPlots( TTree * tree , TString Name){
    i_plot = 0;
    Tree = tree;
    Nentries = Tree -> GetEntries();
    fName = Name;
    QuietMode = false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TPlots::TPlots( TString FileName , TString TreeName , TString Name , bool fQuietMode ){
    i_plot = 0;
    File = new TFile( FileName );
    Tree = (TTree*)File -> Get( TreeName );
    Nentries = Tree -> GetEntries();
    fName = Name;
    QuietMode = fQuietMode;
    if (!QuietMode) printf("Starting TPlots analysis of file \n%s\nwith %s (%s), Nentries = %d\n",FileName.Data(),Tree->GetName(),fName.Data(),Nentries);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TPlots::MergeFiles( TString TreeName, const int N, char ** FileName, char * Path, char * NewFileName ){
    TFile * OutFile = new TFile(Form("%s.root",NewFileName));
    chain = new TChain(TreeName);
    for (int j = 0; j < N; j++)
    chain -> Add(Form("%s/%s",Path,FileName[j]));
    chain -> Merge(Form("%s/%s.root",Path,NewFileName));
    OutFile -> Write();
    OutFile -> Close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TPlots::TPlots( TString TreeName , TString FileName1 , TString FileName2 , TString Path , TString NewFileName , bool QuietMode ){
    chain = new TChain(TreeName);
    chain -> Add(Form("%s/%s",Path.Data(),FileName1.Data()));
    chain -> Add(Form("%s/%s",Path.Data(),FileName2.Data()));
    chain -> Merge(Form("%s/%s.root",Path.Data(),NewFileName.Data()));
    if (!QuietMode)
    std::cout << Form("at date %d and time %d ",ts.GetDate(),ts.GetTime())
    << ", Generated\n"
    << Form("%s/%s.root",Path.Data(),NewFileName.Data()) << std::endl;
    i_plot = 0;
    File = new TFile( Form("%s/%s.root",Path.Data(),NewFileName.Data()) );
    Tree = (TTree*)File -> Get( TreeName );
    Nentries = Tree -> GetEntries();
    if (!QuietMode) printf("TPlots with %s, Nentries = %d\n",Tree->GetName(),Nentries);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TCanvas * TPlots::CreateCanvas(TString Title, TString DoDivide, int Nx, int Ny, float w, float h){
    i_plot++;
    TCanvas * c = new TCanvas(Form("c%s%s%d",fName.Data(),Title.Data(),i_plot),Title.Data(),w,h);
    if (DoDivide=="Divide")
    c -> Divide(Nx , Ny , 0.01 , 0.01);
    else if (DoDivide=="DivideSquare")
    c -> DivideSquare(Nx);
    
    c -> SetRightMargin(0.1);
    c -> SetLeftMargin(0.16);
    c -> SetTopMargin(0.05);
    c -> SetBottomMargin(0.16);
    c -> SetTicks(1,1);
    return c;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TH1F * TPlots::H1(TString  Var, TCut cut, TString option
                  , int Nbins, double Xlow, double Xup
                  , TString Title, TString XTitle, TString YTitle
                  , int color, int FillColor, int FillStyle){
    i_plot++;
    Tree -> Draw(Form("%s>>h%s%d(%d,%f,%f)",Var.Data(),fName.Data(),i_plot,Nbins,Xlow,Xup),cut,"goff");
    h[i_plot] = (TH1F *)gROOT->FindObject(Form("h%s%d",fName.Data(),i_plot));
    SetFrame( h[i_plot] , Title , XTitle , YTitle , "" ,  color , FillColor , FillStyle);
    if (option!="goff")
    h[i_plot] -> Draw(Form("%s",option.Data()));
    if (!QuietMode)
    std::cout << Form("%s %s with %d entries",fName.Data(),Var.Data(),(int)h[i_plot]->GetEntries()) << std::endl;
    return h[i_plot];
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TH2F * TPlots::H2( TString VarX, TString VarY, TCut cut, TString option
                  , int NbinX, double Xlow, double Xup, int NbinY, double Ylow, double Yup
                  , TString Title , TString XTitle , TString YTitle
                  , int color, int style, double Alpha, double mSize ){
    i_plot++;
    Tree -> SetMarkerColorAlpha( color , Alpha );
    Tree -> Draw(Form("%s:%s>>h2%s%d(%d,%f,%f,%d,%f,%f)"
                      ,VarY.Data(),VarX.Data(),fName.Data(),i_plot,NbinX,Xlow,Xup,NbinY,Ylow,Yup),cut,"goff");
    h2[i_plot] = (TH2F *)gROOT->FindObject(Form("h2%s%d",fName.Data(),i_plot));
    SetFrame( h2[i_plot] , Form("%s",Title.Data()) , XTitle , YTitle , "" , color , color , style , style , mSize , Alpha );
    if (option!="goff")
    h2[i_plot] -> Draw(Form("%s",option.Data()));
    if (!QuietMode)
    std::cout << Form("%s %s vs. %s with %d entries",fName.Data(),VarX.Data(),VarY.Data(),(int)h2[i_plot]->GetEntries()) << std::endl;
    return h2[i_plot];
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TH3F * TPlots::H3( TString VX, TString VY, TString VZ, TCut cut, TString option
                  , int NbinX, double Xlow, double Xup, int NbinY, double Ylow , double Yup, int NbinZ, double Zlow , double Zup
                  , TString Title, TString XTitle, TString YTitle, TString ZTitle
                  , int color, int style , double Alpha , double mSize ){
    i_plot++;
    Tree -> SetMarkerColorAlpha( color , Alpha );
    Tree -> Draw(Form("%s:%s:%s>>h%s%d(%d,%f,%f,%d,%f,%f,%d,%f,%f)"
                      ,VZ.Data(),VY.Data(),VX.Data(),fName.Data(),i_plot,NbinX,Xlow,Xup,NbinY,Ylow,Yup,NbinZ,Zlow,Zup),cut,"goff");
    h3[i_plot] = (TH3F *)gROOT->FindObject(Form("h%s%d",fName.Data(),i_plot));
    SetFrame( h3[i_plot] , Form("%s",Title.Data()), XTitle, YTitle, ZTitle, color , style , mSize , Alpha );
    if (option!="goff")
    h3[i_plot] -> Draw(Form("%s",option.Data()));
    if (!QuietMode)
    std::cout << Form("%s %s vs. %s vs. %s with %d entries",fName.Data(),VZ.Data(),VY.Data(),VX.Data(),(int)h3[i_plot]->GetEntries()) << std::endl;
    return h3[i_plot];
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void  TPlots::MultipleHistograms (int N,TH1 ** h,TString * Labels,double Xlow,double Xup,TString Title,TString XTitle,TString YTitle,int *colors,int fStyle){
    CreateCanvas("multiple histograms");
    float YMax = h[0]->GetMaximum()*1.05;
    for (int i = 0; i < N; i++) {
        if (h[i]->GetMaximum()*1.05 > YMax) {
            YMax = h[i]->GetMaximum()*1.05;
        }
    }
    SHOW(YMax);
    DrawFrame(Title , 10 , Xlow , Xup , 0 , YMax , XTitle , YTitle );
    for (int i = 0; i < N; i++) {
        //        h[i] -> Scale( 1. / h[i]->Integral() );
        if (colors!=nullptr) {
            h[i] -> SetFillColor(colors[i]);
            h[i] -> SetLineColor(colors[i]);
        } else {
            h[i] -> SetFillColor(i+1);
            h[i] -> SetLineColor(i+1);
        }
        h[i] -> SetFillStyle(fStyle);
        h[i] -> SetLineWidth(5);
        h[i] -> Draw("same hist");
    }
    AddLegend(N , h, Labels , "l");
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TPie * TPlots::Pie(TString Name, TString Title, const int N, Float_t *vals , Int_t *colors, TString * labels , TString option){
    TPie *pie = new TPie(Name, Title , N , vals , colors);
    pie -> SetAngularOffset(40.);
    pie -> SetRadius(.25);
    pie -> SetLabelsOffset(0.05);
    float sumofvals = 0;
    for ( int i = 0 ; i < N ;  i++ )
    sumofvals += vals[i];
    for ( int i = 0 ; i < N ;  i++ ) {
        pie -> SetEntryRadiusOffset( i, 0.1);
        pie -> SetEntryLabel(i, Form("%s(%.1f%%)",labels[i].Data(),100*vals[i]/sumofvals));
        //        SHOW(Form("%s(%.1f%%)",labels[i].Data(),100*vals[i]/sumofvals));
    }
    pie->Draw(option);
    return pie;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TH2F * TPlots::H2WithProjections( TString VarX, TString VarY, TCut cut
                                 , int NbinX, double Xlow, double Xup, int NbinY, double Ylow, double Yup
                                 , TString Title , TString XTitle , TString YTitle){
    i_plot++;
    TCanvas * c = CreateCanvas(Form("%s%d",Title.Data(),i_plot));
    c -> Divide(2,2,0,0);
    
    c -> cd(1);
    TH1F* hX = H1(VarX , cut ,"BAR", NbinX, Xlow, Xup,"" ,XTitle,"",2,2);
    SetAxisTitle(hX -> GetXaxis() , XTitle , -1. , 0.075 , 0.05);
    c -> cd(3);
    TH2F * h2 = H2(VarX, VarY, cut, "col", NbinX, Xlow, Xup, NbinY, Ylow, Yup ,Title ,XTitle,YTitle);
    SetAxisTitle(h2 -> GetXaxis() , XTitle , 1.8 , 0.075 , 0.05);
    SetAxisTitle(h2 -> GetYaxis() , YTitle , 1.8 , 0.075 , 0.05);
    h2 -> SetTitle("");
    c -> cd(4);
    TH1F* hY = H1(VarY, cut, "hbar2", NbinY, Ylow, Yup ,"" ,YTitle,"",2,2);
    SetAxisTitle(hY -> GetXaxis() , YTitle , -1. , 0.075 , 0.05);
    c -> cd(2);
    DrawFrame( Form("Projections%d",i_plot) , 10 , -1 , 1, -1 , 1 , "", "" );
    Text(-0.5,0.5,Title,1,0.075);
    Text(0,0.4,Form("%.0f entries",h2->GetEntries()),1);
    return h2;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TH2F * TPlots::Dalitz ( TString Tp1, TString Tp2, TString Tp3, TCut cut, int NbinsX, double Xlow, double Xup, int NbinsY, double Ylow, double Yup
                       ,TString Tit1, TString Tit2, TString Tit3, TString option, int color, bool DoText){
    // return a Dalitz plot of the 4-vectors v1,v2,v3
    // [http://www.bo.infn.it/rem/Giammaria_Tommaso_tesi.pdf]
    // x = √3(T₁-T₂)/T , y = (2T₃ - T₁ - T₂)/T
    TString T = Form("(%s+%s+%s)", Tp1.Data(), Tp2.Data(), Tp3.Data());
    TString Tit = Form("(%s+%s+%s)", Tit1.Data(), Tit2.Data(), Tit3.Data());
    Tit1 = Form("%s/%s",Tit1.Data(),Tit.Data());
    Tit2 = Form("%s/%s",Tit2.Data(),Tit.Data());
    Tit3 = Form("%s/%s",Tit3.Data(),Tit.Data());
    TString VarX = Form("sqrt(3)*(%s - %s)/%s",Tp1.Data(),Tp2.Data(),T.Data());
    TString VarY = Form("(2*%s - %s - %s)/%s",Tp3.Data(),Tp1.Data(),Tp2.Data(),T.Data());
    TH2F * h2 = H2( VarX, VarY, cut, option , NbinsX, Xlow, Xup, NbinsY, Ylow, Yup,"Dalitz plot", "" , "", color , 20 );
    if (DoText) {
        Arrow(0,0,0.8*Xup,0.8*Ylow);
        Text(0.6*Xup,0.6*Ylow,Tit1);
        Arrow(0,0,0.8*Xlow,0.8*Ylow);
        Text(0.6*Xlow,0.6*Ylow,Tit2);
        Arrow(0,0,0,0.8*Yup);
        Text(0.1,0.8*Yup,Tit3);
    }
    return h2;
}





//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TH1F* TPlots::H1step(TString  Var, TCut cut, TString option
                                , int Nbins, double Xlow, double Xup
                                , TString Title, TString XTitle, TString YTitle
                                , int color, int FillColor, int FillStyle){
    
    // return a histogram with 0 or 1 in each bin - if there was an event in each bin or not...
    
    TH1F * hVar = H1(Var, cut, option
                  , Nbins, Xlow, Xup
                  , Title, XTitle, YTitle
                  , color, FillColor, FillStyle);
    
    TH1F* h1step = (TH1F*)hVar->Clone(Form("%s step",Var.Data()));
    for (int binX = 0 ; binX < Nbins+1 ; binX++ ){
        h1step -> SetBinContent( binX, hVar->GetBinContent(binX)>0 ? 1 : 0 );
    }
    h1step -> Draw(option);
    return h1step;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TH1F* TPlots::H1stepOfVarX( TString VarX, TString VarY, TCut cut, TString option
                                    , int NbinX, double Xlow, double Xup, int NbinY, double Ylow, double Yup
                                    , TString Title , TString XTitle , TString YTitle
                                    , double Ymin , double Ymax ){
    
    // return a histogram with 0 or 1 in each bin - if there were events in each bin from the other variable in the range [Ymin,Ymax]
    
    TH2F * h2 = H2( VarX, VarY, cut,  option
                     , NbinX,  Xlow,  Xup,  NbinY,  Ylow,  Yup
                     , Title , XTitle ,  YTitle);
    
    TH1F* h1step = new TH1F(Form("%s step as a function of %s",VarY.Data(),VarX.Data()),XTitle,NbinX,Xlow,Xup);
    for (int binX = 0 ; binX < NbinX+1 ; binX++ ){
        int NeventesInbinX = 0;
        for (int binY = h2->GetYaxis()->FindBin(Ymin) ; binY < h2->GetYaxis()->FindBin(Ymax)+1 ; binY++ ){
            NeventesInbinX += h2->GetBinContent(binX,binY);
        }
        h1step -> SetBinContent( binX, NeventesInbinX>0 ? 1 : 0 );
    }
    SetFrame(h1step,"",XTitle,Form("recorded eventes with %.2f<%s<%.2f",Ymin,YTitle.Data(),Ymax));
    h1step -> Draw(option);
    return h1step;
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// general graph (with errors!)
TGraphErrors * TPlots::Graph( TString Name, const int N , double *X , double *Y , double *Xerr , double *Yerr , TString Title , TString XTitle , TString YTitle , int color , double mSize , int mStyle , TString option){
    i_plot++;
    TGraphErrors * g = new TGraphErrors( N , X , Y , Xerr , Yerr );
    g -> SetName(Name);
    SetFrame( g ,Title , XTitle , YTitle );
    g -> SetMarkerColor(color);
    g -> SetLineColor(color);
    g -> SetLineStyle(mStyle);
    g -> SetMarkerStyle(mStyle);
    g -> SetMarkerSize(mSize);
    if (option=="goff")
    return g;
    else
    g -> Draw(option);
    return g;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// general graph
TGraph * TPlots::Graph( const int N , double* X , double* Y, TString Title , TString XTitle , TString YTitle , int color  , int style , TString option){
    i_plot++;
    TGraph * g = new TGraph( N , X , Y );
    SetFrame( g ,Title , XTitle , YTitle );
    g -> SetMarkerColor(color);
    g -> SetLineColor(color);
    g -> SetLineStyle(style);
    if (option=="goff"){
        return g;
    }
    else {
        g -> Draw(option);
    }
    return g;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TGraphErrors * TPlots::Graph( TString Name, const int N , double *X , double *Y , TString Title , TString XTitle , TString YTitle , int color , double mSize , int mStyle , Option_t * option){
    double Xerr[1000] = {0.0} , Yerr[1000] = {0.0};
    return Graph( Name, N , X , Y , Xerr , Yerr , Title , XTitle , YTitle , color , mSize , mStyle , option);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// multiple graphs
void TPlots::Graphs( const int N, TGraphErrors ** g, TString * Labels, int *PolRank , double *xFitMin , double *xFitMax
                    , double ** FitPar , double ** FitParErr, double *chi2red
                    , TString Title, TString XTitle, TString YTitle, double mSize, int mStyle
                    , double Xmin, double Xmax, double YMin, double YMax
                    , bool FitGraphs , int *LineColors , bool DoAddLegend , bool AddFitToLegend ){
    
    TF1 * f[N];
    TString * newLabels = nullptr;
    DrawFrame(Title , 10*(Xmax-Xmin) , Xmin , Xmax, YMin , YMax , XTitle, YTitle );
    //    SetFrame( g[0] ,Title , XTitle , YTitle );
    for (int i = 0 ; i < N ; i++){
        newLabels[i] = Labels[i];
        g[i] -> SetMarkerSize(mSize);
        g[i] -> SetMarkerStyle(mStyle+i);
        g[i] -> SetMarkerColor(LineColors[i]);
        g[i] -> SetLineColor(LineColors[i]);  // errors will appear in the same color as the marker
        g[i] -> Draw("same p");
        if (FitGraphs){
            f[i] = new TF1(Form("f%d",i),Form("pol%d",PolRank[i]),xFitMin[i],xFitMax[i]);
            f[i] -> SetLineColor(LineColors[i]);
            f[i] -> SetLineStyle(2);
            g[i] -> Fit(f[i],"R");
            if (PolRank[i]==0){
                FitPar[i][0]    = f[i]->GetParameter(0);
                FitParErr[i][0] = f[i]->GetParError(0);
                chi2red[i]      =  f[i]->GetChisquare()/f[i]->GetNDF();
                if ( chi2red[i] > 1) FitParErr[i][0] *= sqrt(chi2red[i]);
                if (AddFitToLegend)
                newLabels[i] = Form("%s, y = %.3f(%.0f) {chi2/ndf=%.1f}"
                                    ,Labels[i].Data(),FitPar[i][0]
                                    ,1000*FitParErr[i][0]
                                    ,chi2red[i]);
            }
            else if (PolRank[i]==1){
                for (int j = 0 ; j < 2 ; j++){
                    FitPar[i][j]    = f[i]->GetParameter(j);
                    FitParErr[i][j] = f[i]->GetParError(j);
                }
                chi2red[i]  =  f[i]->GetChisquare()/f[i]->GetNDF();
                if ( chi2red[i] > 1) {FitPar[i][0] *= sqrt(chi2red[i]); FitPar[i][1] *= sqrt(chi2red[i]);}
                if (AddFitToLegend)
                newLabels[i] = Form("%s, y = %.3f(%.0f) + %.3f(%.0f)x {chi2/ndf=%.1f}"
                                    ,Labels[i].Data()
                                    ,FitPar[i][0],1000*FitParErr[i][0]
                                    ,FitPar[i][1],1000*FitParErr[i][1]
                                    ,chi2red[i]);
            }
        } else
        newLabels[i] = Labels[i];
    }
//    if (DoAddLegend)
//    AddLegend(N , g , newLabels , "lp");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// A service to all classes
TH1F * TPlots::DrawFrame(TString Title , int Nbins , double Xlow , double Xup , double Ymin , double Ymax , TString XTitle ,TString YTitle ){
    TH1F * frame = new TH1F(Title , Title , Nbins , Xlow , Xup );
    frame -> GetYaxis() -> SetRangeUser(Ymin,Ymax);
    SetFrame(frame , Title , XTitle , YTitle );
    frame -> Draw();
    return frame;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TPlots::SetAxisTitle(TAxis * axis , TString Title , double Offset , double TitleSize , double LabelSize){
    axis -> SetTitle(Title);
    axis -> SetTitleOffset(Offset);
    axis -> SetTitleSize(TitleSize);
    axis -> SetLabelSize(LabelSize);
    axis -> SetNdivisions(507);
    axis -> CenterTitle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TPlots::H2Frame( double Xlow , double Xup , double Ylow , double Yup , TString Title , TString XTitle , TString YTitle ) {
    i_plot++;
    TH2F * frame = new TH2F( Form("frame%d",i_plot) ,Title , 10 , Xlow , Xup , 10, Ylow , Yup );
    SetFrame( frame , Title , XTitle , YTitle );
    frame -> Draw();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TPlots::H1Frame( int Nbins , double Xlow , double Xup , TString Title , TString XTitle , TString YTitle , double Ylow , double Yup) {
    i_plot++;
    TH1F * frame = new TH1F( Form("%s_%d",Title.Data(),i_plot) ,Title , Nbins , Xlow , Xup );
    frame -> GetYaxis() -> SetRangeUser(Ylow , Yup);
    SetFrame( frame , Title , XTitle , YTitle );
    frame -> Draw("goff");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// Calculate the ratio of integrals for two TH2F histograms between xmin->xmax and ymin->ymax
Float_t TPlots::CalculateRatioOfEvents2D( TH2F* hA , TH2F* hB , Float_t XMin , Float_t XMax , Float_t YMin , Float_t YMax){
    int binXMinA = hA -> GetXaxis() -> FindBin(XMin) ,   binXMaxA = hA -> GetXaxis() -> FindBin(XMax);
    int binYMinA = hA -> GetYaxis() -> FindBin(YMin) ,   binYMaxA = hA -> GetYaxis() -> FindBin(YMax);
    int binXMinB = hB -> GetXaxis() -> FindBin(XMin) ,   binXMaxB = hB -> GetXaxis() -> FindBin(XMax);
    int binYMinB = hB -> GetYaxis() -> FindBin(YMin) ,   binYMaxB = hB -> GetYaxis() -> FindBin(YMax);
    if (!QuietMode)
    std:: cout << Form("binsA: %d,%d -> %d,%d,\t hA = %.2f,\t hB = %.2f"
                       ,binXMinA,binYMinA,binXMaxA,binYMaxA
                       ,hA->Integral(binXMinA,binXMaxA,binYMinA,binYMaxA)
                       ,hB->Integral(binXMinB,binXMaxB,binYMinB,binYMaxB)) << std::endl;
    return (hA->Integral(binXMinA,binXMaxA,binYMinA,binYMaxA) / hB->Integral(binXMinB,binXMaxB,binYMinB,binYMaxB));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// Draw a arrow / line / text / box / circle ...
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TGaxis * TPlots::Axis( double XMin , double YMin , double XMax , double YMax, double w_min , double w_max , int n_div , TString option){
    TGaxis *axis = new TGaxis(XMin,YMin,XMax,YMax,w_min,w_max,n_div,option);
    axis -> SetTextFont(0);
    axis -> SetLabelOffset(100.025);
    axis -> SetLabelSize(0.05);
    axis -> Draw();
    return axis;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TLine * TPlots::Line( double XMin , double YMin , double XMax , double YMax , int color , int width , int style , double opacity){
    TLine * line = new TLine( XMin , YMin , XMax , YMax );
    line -> SetLineColorAlpha( color , opacity );
    line -> SetLineWidth( width );
    line -> SetLineStyle( style );
    line -> Draw();
    return line;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TArrow * TPlots::Arrow( double XMin , double YMin , double XMax , double YMax , int color , int width , int style , double opacity , double size){
    TArrow * arrow = new TArrow( XMin , YMin , XMax , YMax );
    arrow -> SetLineColorAlpha( color , opacity );
    arrow -> SetLineWidth( width );
    arrow -> SetLineStyle( style );
    arrow -> SetArrowSize( size );
    arrow -> Draw();
    return arrow;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TLatex * TPlots::Text( double X, double Y, TString label, int color, double size, double Angle , float alpha ){
    TLatex * text = new TLatex( X , Y , label );
    text -> SetTextColorAlpha( color , alpha );
    text -> SetTextSize( size );
    text -> SetTextAngle( Angle );
    text -> Draw();
    return text;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TLatex * TPlots::Latex( double X, double Y, TString label, int color, double size, double Angle){
    TLatex * text = new TLatex();
    text -> SetTextColor( color );
    text -> SetTextSize( size );
    text -> SetTextAngle( Angle );
    text -> DrawLatexNDC( X , Y , label );
    return text;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TBox * TPlots::Box( double XMin , double YMin , double XMax , double YMax , int color, double opacity, int LineWidth){
    TBox * box = new TBox( XMin , YMin , XMax , YMax );
    box -> SetFillColorAlpha( color , opacity );
    box -> SetLineColor( color );
    box -> SetLineWidth( LineWidth );
    Line( XMin , YMin , XMin , YMax , color , LineWidth );
    Line( XMax , YMin , XMax , YMax , color , LineWidth );
    Line( XMin , YMin , XMax , YMin , color , LineWidth );
    Line( XMin , YMax , XMax , YMax , color , LineWidth );
    box -> Draw();
    return box;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TPlots::ROI( double XMin , double YMin , double XMax , double YMax , int color){
    // draw a ROI box around something...
    int LineWidth = 2;
    Line( XMin , YMin , XMin , YMax , color , LineWidth );
    Line( XMax , YMin , XMax , YMax , color , LineWidth );
    Line( XMin , YMin , XMax , YMin , color , LineWidth );
    Line( XMin , YMax , XMax , YMax , color , LineWidth );
    return;
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TEllipse * TPlots::Circle( double X , double Y , double R , int color, double opacity, int LineColor , int LineWidth ){
    TEllipse * circle = new TEllipse( X , Y , R );
    circle -> SetFillColorAlpha( color , opacity );
    circle -> SetLineColor( LineColor );
    circle -> SetLineWidth( LineWidth );
    circle -> Draw();
    return circle;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TPolyLine3D * TPlots::Line3D( TVector3 v , int LineColor , int LineWidth , int LineStyle){
    TPolyLine3D *l = new TPolyLine3D(2);
    l -> SetPoint(0,0,0,0);
    l -> SetPoint(1,v.x(),v.y(),v.z());
    l -> SetLineColor(LineColor);
    l -> SetLineWidth(LineWidth);
    l -> SetLineStyle(LineStyle);
    l -> Draw();
    return l;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TPlots::Plot3DAxesSystem( float size ){
    TVector3 x(size,0,0) , y(0,size,0) , z(0,0,size);
    Line3D( -x , 11 , 1 , 2 );
    Line3D( -y , 11 , 2 , 2 );
    Line3D( -z , 11 , 3 , 2 );
    Line3D( x , 11 , 2 , 1  );
    Line3D( y , 11 , 2 , 1  );
    Line3D( z , 11 , 2 , 1  );
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TPlots::Frame3D(TString Title){
    i_plot++;
    TH3F * Frame = new TH3F(Form("Frame%s%d",Title.Data(),i_plot),Title,10,-0.5,0.5,10,-0.5,0.5,10,-0.5,0.5);
    SetAxisTitle(Frame -> GetXaxis() , "x");
    SetAxisTitle(Frame -> GetYaxis() , "y");
    SetAxisTitle(Frame -> GetZaxis() , "z");
    Frame -> Draw();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TH1F * TPlots::ReScaleAxis(TH1F * h, double XMin, double XMax)
{
    TH1F * hRescaled = new TH1F("hRescaled",h->GetTitle(),h->GetNbinsX(),XMin,XMax);
    for (int i = 0 ; i < h -> GetXaxis() -> GetNbins() + 1 ; i++)
    hRescaled -> SetBinContent( i , h -> GetBinContent(i) );
    return hRescaled;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TString TPlots::Theta(TString v1, TString v2){
    return Form("(180./3.141528)*acos((%s.x()*%s.x() + %s.y()*%s.y() + %s.z()*%s.z() )/(%s.Mag()*%s.Mag()))"
                ,v1.Data(),v2.Data(),v1.Data(),v2.Data(),v1.Data(),v2.Data(),v1.Data(),v2.Data());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TString TPlots::CosTheta(TString v1, TString v2){
    return Form("(%s.x()*%s.x() + %s.y()*%s.y() + %s.z()*%s.z() )/(%s.Mag()*%s.Mag())"
                ,v1.Data(),v2.Data(),v1.Data(),v2.Data(),v1.Data(),v2.Data(),v1.Data(),v2.Data());
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TCut TPlots::CutOnAngle(TString v1, TString v2, float AngleMin, float AngleMax){
    TString Angle = Theta(v1,v2);
    return Form("%f<%s && %s<%f",AngleMin,Angle.Data(),Angle.Data(),AngleMax);
}

// Get The sum of all entries in a given branch
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
float TPlots::GetBranchSum(TString v1,TCut cut){
    if (Tree) {
        Tree -> Draw(Form("%s>>hBranch",v1.Data()),cut,"goff");
        TH1F * h = (TH1F *)gROOT->FindObject(Form("hBranch"));
        float res = h->GetMean()*h->GetEntries();
        //        Printf("%s total = %f",v1.Data(),res);
        return res;
    } else
    //    Printf("Tree does not exist....");
    return 0;
}

///....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// March-20,2016
void TPlots::Draw1DVarAndCut(TCanvas * c  , int i , TString varX ,
                             int NbinsX , float Xmin , float Xmax,
                             TString Title , TString XTitle , TCut cut , bool DoAddLegend , TString CutName){
    c -> cd(i);
    TH1F * hNoCut = H1(varX,"","BAR",NbinsX,Xmin,Xmax,Title,XTitle,"",1,48);
    TH1F * hCut   = H1(varX,cut,"BAR same",NbinsX,Xmin,Xmax,Title,XTitle,"",1,38);
    if (DoAddLegend) {
        AddLegend(hNoCut,Form("no cut - 100%% (%d)",(int)hNoCut->GetEntries()),hCut,Form("%s cut (%.1f%%)",CutName.Data(),100.*(float)hCut->GetEntries()/hNoCut->GetEntries()),"F");
    }
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// April-19,2016
TCanvas * TPlots::Draw1DVarAndCut( TString varX ,
                             int NbinsX , float Xmin , float Xmax,
                             TString Title , TString XTitle , TCut cut , bool DoAddLegend , TString CutName){
    TCanvas * c = CreateCanvas(varX);
    Draw1DVarAndCut(c  , 1 , varX , NbinsX , Xmin , Xmax, Title , XTitle , cut , DoAddLegend , CutName);
    return c;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// March-20,2016
void TPlots::Draw2DVarAndCut(TCanvas * c  , int i , TString varX , TString varY,
                             int NbinsX , float Xmin , float Xmax,
                             int NbinsY , float Ymin , float Ymax,
                             TString Title , TString XTitle , TString YTitle , TCut cut , bool DoAddLegend , TString CutName ){
    c -> cd(i);
    TH2F * hNoCut = H2(varX,varY,"","",NbinsX,Xmin,Xmax,NbinsY,Ymin,Ymax,Title,XTitle,YTitle,1,7,0.5);
    TH2F * hCut   = H2(varX,varY,cut,"same",NbinsX,Xmin,Xmax,NbinsY,Ymin,Ymax,Title,XTitle,YTitle,2,7,0.8);
    if (DoAddLegend) {
        AddLegend(hNoCut,Form("no cut - 100%% (%d)",(int)hNoCut->GetEntries()),hCut,Form("%s cut (%.1f%%)",CutName.Data(),100.*(float)hCut->GetEntries()/hNoCut->GetEntries()),"p");
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// April-31,2016
TCanvas * TPlots::Draw2DVarAndCut(TString varX , TString varY,
                             int NbinsX , float Xmin , float Xmax,
                             int NbinsY , float Ymin , float Ymax,
                             TString Title , TString XTitle , TString YTitle , TCut cut , bool DoAddLegend , TString CutName ){
    TCanvas * c = CreateCanvas(varX + " vs " + varY);
    Draw2DVarAndCut(c  , 1 , varX , varY, NbinsX , Xmin , Xmax, NbinsY , Ymin , Ymax, Title , XTitle , YTitle , cut , DoAddLegend , CutName );
    return c;
}






