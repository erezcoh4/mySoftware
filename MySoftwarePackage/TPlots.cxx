//  TPlots.cpp
//  Created by Erez Cohen on 2/24/15.
#include "TPlots.h" // my mac


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
    if (!QuietMode) printf("TPlots with %s (%s), Nentries = %d\n",Tree->GetName(),fName.Data(),Nentries);
}





//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TPlots::MergeFiles( TString TreeName, const int N, char * FileName[N], char * Path, char * NewFileName ){
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
        c -> Divide(Nx , Ny);
    else if (DoDivide=="DivideSquare")
        c -> DivideSquare(Nx);
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
    SetFrame( h[i_plot] , Title , XTitle , YTitle , color , FillColor , FillStyle);
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
                  , int color, int style, float Alpha, double mSize ){
    i_plot++;
    Tree -> SetMarkerColorAlpha( color , Alpha );
    Tree -> Draw(Form("%s:%s>>h2%s%d(%d,%f,%f,%d,%f,%f)"
                      ,VarY.Data(),VarX.Data(),fName.Data(),i_plot,NbinX,Xlow,Xup,NbinY,Ylow,Yup),cut,"goff");
    h2[i_plot] = (TH2F *)gROOT->FindObject(Form("h2%s%d",fName.Data(),i_plot));
    SetFrame( h2[i_plot] , Form("%s",Title.Data()) , XTitle , YTitle , color , style , mSize , Alpha );
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
                  , int color, int style , float Alpha , double mSize ){
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
TPie * TPlots::Pie(TString Name, TString Title, const int N, Float_t vals[N] , Int_t colors[N], TString * labels , TString option){
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
    DrawFrame(Form("Projections%d",i_plot) , "" , 10 , -1 , 1, -1 , 1 , "", "" );
    Text(-0.5,0.5,Title,1,0.075);
    Text(0,0.4,Form("%.0f entries",h2->GetEntries()),1);
    return h2;
}






//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TH1F * TPlots::Angle(TString v1, TString v2 , TCut cut , TString option, TString Title, TString XTitle, TString YTitle , int color, int Nbins, double Tlow, double Tup ){
    return H1( Form("TMath::RadToDeg()*acos((%s.X()*%s.X() + %s.Y()*%s.Y() + %s.Z()*%s.Z() )/(%s.Mag()*%s.Mag()))"
                    ,v1.Data(),v2.Data(),v1.Data(),v2.Data(),v1.Data(),v2.Data(),v1.Data(),v2.Data())
              , cut, option, Nbins, Tlow, Tup, Title, XTitle, YTitle, color);
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TH1F * TPlots::CosAngle(TString v1, TString v2 , TCut cut , TString option, TString Title, TString XTitle, TString YTitle , int color, int Nbins, double Tlow, double Tup ){
    return H1( Form("(%s.X()*%s.X() + %s.Y()*%s.Y() + %s.Z()*%s.Z() )/(%s.Mag()*%s.Mag())"
                    ,v1.Data(),v2.Data(),v1.Data(),v2.Data(),v1.Data(),v2.Data(),v1.Data(),v2.Data())
              , cut, option, Nbins, Tlow, Tup, Title, XTitle, YTitle, color);
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TH2F * TPlots::AngularCorrelation(TString v1, TString v2 , TString v3, TString v4
                                  , TCut cut , TString option, TString Title, TString XTitle, TString YTitle
                                  , int color, int Nbins, double Tlow, double Tup , int style, float Alpha, double mSize ){
    return H2(  Form("TMath::RadToDeg()*acos((%s.x()*%s.x() + %s.y()*%s.y() + %s.z()*%s.z() )/(%s.Mag()*%s.Mag()))"
                     ,v1.Data(),v2.Data(),v1.Data(),v2.Data(),v1.Data(),v2.Data(),v1.Data(),v2.Data())
              , Form("TMath::RadToDeg()*acos((%s.x()*%s.x() + %s.y()*%s.y() + %s.z()*%s.z() )/(%s.Mag()*%s.Mag()))"
                     ,v3.Data(),v4.Data(),v3.Data(),v4.Data(),v3.Data(),v4.Data(),v3.Data(),v4.Data())
              , cut, option, Nbins, Tlow, Tup, Nbins, Tlow, Tup, Title, XTitle, YTitle, color, style, Alpha, mSize);
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// legend
void TPlots::AddLegend(TString Title , const int N , TH1F * h[N], TString * Labels , int Ncol , Option_t * option , bool mean ){
    TLegend * leg = new TLegend( 0.35 , 0.7 , 0.8 , 0.85 );
    leg -> SetHeader (Title);
    leg -> SetLineColor(0);
    leg -> SetNColumns(Ncol);
    leg -> SetTextSize(0.04);
    for (int i = 0 ; i < N ; i++){
        if (mean)
            leg -> AddEntry ( h[i] , Form("%s, #mu=%.3f",Labels[i].Data(),h[i]->GetMean()) , option );
        else
            leg -> AddEntry ( h[i] , Labels[i] , option );
    }
    leg -> Draw();
}




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TPlots::AddLegend(TString Title , const int N , TH2F * h[N], TString * Labels , int Ncol , Option_t * option){
    AddLegend( Title ,  N , (TH1F **) h, Labels , Ncol , option , false );
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TPlots::AddLegend(TString Title, TH1F * h1, TString l1, TH1F * h2, TString l2, Option_t * option){
    TH1F * h[2] = {h1,h2};
    TString Labels[2];
    Labels[0] = l1 ;//+ Form(" (%d)",(int)h1->GetEntries());
    Labels[1] = l2 ;//+ Form(" (%d)",(int)h2->GetEntries());
    AddLegend( Title ,  2 , h , Labels , 1 , option);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TPlots::AddLegend(TString Title, TH2F * h1, TString l1, TH2F * h2, TString l2, Option_t * option){
    AddLegend( Title , (TH1F *) h1 , l1, (TH1F *) h2, l2, option);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TPlots::AddLegend(TString Title, TH3F * h1, TString l1, TH3F * h2, TString l2, Option_t * option){
    AddLegend( Title , (TH1F *) h1 , l1, (TH1F *) h2, l2, option);
}




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TPlots::AddLegend(TString Title , const int N , TGraphErrors * g[N] ,  TString * Labels, int Ncol , Option_t * option){
    TLegend * leg = new TLegend( 0.15 , 0.7 , 0.5 , 0.9 );
    leg -> SetHeader (Title);
    leg -> SetLineColor (0);
    leg -> SetTextSize (0.04);
    leg-> SetNColumns(Ncol);
    for (int i = 0 ; i < N ; i++)
        leg -> AddEntry ( g[i] , Labels[i] , option );
    leg -> Draw();
}




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// general graph (with errors!)
TGraphErrors * TPlots::Graph( TString Name, const int N , double X[N] , double Y[N] , double Xerr[N] , double Yerr[N] , TString Title , TString XTitle , TString YTitle , int color , double mSize , int mStyle , TString option){
    i_plot++;
    TGraphErrors * g = new TGraphErrors( N , X , Y , Xerr , Yerr );
    g -> SetName(Name);
    SetFrame( g ,Title , XTitle , YTitle );
    g -> SetMarkerColor(color);
    g -> SetLineColor(color);
    g -> SetMarkerStyle(mStyle);
    g -> SetMarkerSize(mSize);
    if (option=="goff")
        return g;
    else
        g -> Draw(option);
    return g;
}




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TGraphErrors * TPlots::Graph( TString Name, const int N , double X[N] , double Y[N] , TString Title , TString XTitle , TString YTitle , int color , double mSize , int mStyle , Option_t * option){
    double Xerr[1000] = {0.0} , Yerr[1000] = {0.0};
    return Graph( Name, N , X , Y , Xerr , Yerr , Title , XTitle , YTitle , color , mSize , mStyle , option);
}





//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// multiple graphs
void TPlots::Graphs( const int N, TGraphErrors ** g, TString * Labels, int PolRank[N] , double xFitMin[N] , double xFitMax[N]
                    , double ** FitPar , double ** FitParErr, double chi2red[N]
                    , TString Title, TString XTitle, TString YTitle, double mSize, int mStyle
                    , double Xmin, double Xmax, double YMin, double YMax
                    , bool FitGraphs , int LineColors[N] , bool DoAddLegend , bool AddFitToLegend ){
    
    TF1 * f[N];
    TString * newLabels = nullptr;
    DrawFrame((char*)"graphs" , Title , 10*(Xmax-Xmin) , Xmin , Xmax, YMin , YMax , XTitle, YTitle );
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
    if (DoAddLegend)
        AddLegend("" , N , g , newLabels , 1 , "lp");
}
////....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//void TPlots::Graphs( const int N, TGraphErrors * g[N], TString * Labels,  TString Title, TString XTitle, TString YTitle, double mSize, int mStyle
//                    , double Xmin, double Xmax, double YMin, double YMax , int LineColors[N] , bool DoAddLegend ){
//    int PolRank[N];
//    double xFitMin[N] , xFitMax[N];
//    double FitPar[N][3] , FitParErr[N][3], chi2red[N];
//    for (int i=0;i<N;i++) PolRank[i]=xFitMin[i]=xFitMax[i]=0;
//    Graphs( N, g , Labels ,PolRank , xFitMin , xFitMax,FitPar,FitParErr,chi2red
//           ,Title, XTitle, YTitle, mSize, mStyle
//           ,Xmin ,Xmax , YMin, YMax
//           , false , LineColors ,DoAddLegend );
//}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TPlots::Histograms( const int NHist , TH1F * h[NHist]  , TString * Labels, TString Title , TString XTitle , TString YTitle , double XMin , double XMax , double YMax , bool DoMean ){
    
    TH1F *frame = new TH1F("frame","",100, XMin , XMax);
    frame -> SetMaximum(YMax);
    SetFrame( frame ,Title , XTitle , YTitle );
    frame -> Draw();
    for (int i = 0 ; i < NHist ; i++ ){
        h[i] -> SetLineColor(5*i+31);
        h[i] -> SetLineWidth(3);
        h[i] -> Draw("same");
    }
    AddLegend("Legend" , NHist , h , Labels  , 1 , "l" , DoMean);
}





//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// A service to all classes
TH1F * TPlots::DrawFrame(char * name , TString Title , int Nbins , double Xlow , double Xup , double Ymin , double Ymax , TString XTitle ,TString YTitle ){
    TH1F * frame = new TH1F(name , Title , Nbins , Xlow , Xup );
    frame -> GetYaxis() -> SetRangeUser(Ymin,Ymax*1.05);
    SetFrame(frame , Title , XTitle , YTitle );
    frame -> Draw("goff");
    return frame;
}





//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TPlots::SetAxisTitle(TAxis * axis , TString Title , double Offset , double TitleSize , double LabelSize){
    axis -> SetTitle(Title);
    axis -> SetTitleOffset(Offset);
    axis -> SetTitleSize(TitleSize);
    axis -> SetLabelSize(LabelSize);
    axis -> CenterTitle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TPlots::SetFrame( TH1F * frame , TString Title , TString XTitle , TString YTitle , int color , int FillColor , int FillStyle ){
    frame -> SetTitle( Title );
    SetAxisTitle(frame -> GetXaxis() , XTitle );//, 1. , 0.075 , 0.05); // for plots
    SetAxisTitle(frame -> GetYaxis() , YTitle );//, 1. , 0.075 , 0.05);
    frame -> SetLineColor(color);
    frame -> SetFillColor(FillColor);
    frame -> SetFillStyle(FillStyle);
}




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TPlots::SetFrame( TH2F * frame , TString Title , TString XTitle , TString YTitle
                      , int color , int mStyle , double mSize , double Alpha ){
    frame -> SetTitle( Title );
    frame -> SetTitleSize(0.1);
    SetAxisTitle(frame -> GetXaxis() , XTitle);//, 1. , 0.075 , 0.05);
    SetAxisTitle(frame -> GetYaxis() , YTitle);//, 1. , 0.075 , 0.05);
    frame -> SetMarkerStyle(mStyle);
    frame -> SetMarkerSize(mSize);
    frame -> SetMarkerColorAlpha(color,Alpha);
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TPlots::SetFrame( TH3F * frame, TString Title, TString XTitle, TString YTitle, TString ZTitle
                      , int color , int mStyle , double mSize , double Alpha ){
    frame -> SetTitle( Title );
    frame -> SetTitleSize(0.1);
    SetAxisTitle(frame -> GetXaxis() , XTitle);
    SetAxisTitle(frame -> GetYaxis() , YTitle);
    SetAxisTitle(frame -> GetZaxis() , ZTitle);
    frame -> SetMarkerStyle(mStyle);
    frame -> SetMarkerSize(mSize);
    frame -> SetMarkerColorAlpha(color,Alpha);
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TPlots::SetFrame( TGraph * g , TString Title , TString XTitle , TString YTitle,int color, int mStyle, double mSize, double Alpha){
    g -> SetTitle( Title );
    SetAxisTitle(g -> GetXaxis() , XTitle);//, 0.8 , 0.055 , 0.03);
    SetAxisTitle(g -> GetYaxis() , YTitle);//, 0.8 , 0.055 , 0.03);
    g -> SetMarkerStyle(mStyle);
    g -> SetMarkerSize(mSize);
    g -> SetMarkerColorAlpha(color,Alpha);
    g -> SetLineColorAlpha(color,Alpha);
    //    gPad -> SetTicks(1,1);
}




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TPlots::SetFrame( TGraphErrors * frame , TString Title , TString XTitle , TString YTitle,int color, int mStyle, double mSize, double Alpha){
    SetFrame( (TGraph *)frame , Title , XTitle , YTitle, color, mStyle, mSize, Alpha);
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
TLatex * TPlots::Text( double X, double Y, TString label, int color, double size, double Angle ){
    TLatex * text = new TLatex( X , Y , label );
    text -> SetTextColor( color );
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
void TPlots::PrintOut3Vector( TVector3 v , TString name){
    Printf("%12s: (%5.2f,%5.2f,%5.2f) |%s|=%5.2f",name.Data(),v.x(),v.y(),v.z(),name.Data(),v.Mag());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TPlots::Print4Momentum( TLorentzVector Vec4 , TString Name ){
    printf("%12s: ( ( %5.2f , %5.2f , %5.2f ) , %5.2f ) ||%s-4 vec||=%5.2f |%s-3 vec|=%5.2f\n"
           , Name.Data() , Vec4.Vect().x() , Vec4.Vect().y() , Vec4.Vect().z(), Vec4.Energy(), Name.Data(), Vec4.Mag(), Name.Data(), Vec4.Vect().Mag());
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TPlots::PrintstdTVector3(char * name , std::vector<TVector3> v){
    std::cout << v.size() << " entries of " << name << ":" << '\n';
    for (std::vector<TVector3>::iterator it=v.begin(); it!=v.end(); ++it)
        std::cout << "(" << it -> X() << "," << it -> Y() << "," << it -> Z() << ")\n" ;
    std::cout << "----------\n";
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TPlots::PrintOutMatrix(char * name , const int N , const int M , double **mat){
    Printf("%s:\n------------------",name);
    for (int i = 0 ; i < N ; i++ ){
        printf("|");
        for (int j = 0 ; j < M ; j++){
            printf("%10.2f",mat[i][j]);
        }
        printf("|\n");
    }
    Printf("------------------");
}








//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TPlots::PlotGraphDataToFile(char * FileName,const int N,double X[N],double Xerr[N],double Y[N],double Yerr[N]){
    ofstream OutFile;
    OutFile.open(FileName);
    for (int i = 0; i < N; i++)
        OutFile << X[i] << " " << Xerr[i] << " " << Y[i] << " " << Yerr[i] << std::endl;
    OutFile.close();
}




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TPlots::ReadGraphDataFromFile(char * FileName,const int N,double X[N],double Xerr[N],double Y[N],double Yerr[N]){
    ifstream InFile;
    InFile.open(FileName);
    for (int i = 0; i < N; i++)
        InFile >> X[i] >> Xerr[i] >> Y[i] >> Yerr[i];
    InFile.close();
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
        Printf("%s total = %f",v1.Data(),res);
        return res;
    } else
        Printf("Tree does not exist....");
    return 0;
}




