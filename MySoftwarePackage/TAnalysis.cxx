//  TAnalysis.cpp
//  Created by Erez Cohen on 5/15/15.
#include "TAnalysis.h"

using namespace RooFit ;
#define MAX 100000


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TAnalysis::TAnalysis(){    i_ana = 0;   }








//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
Double_t TAnalysis::Kolmogorov1D(Int_t Na, Double_t* a, Int_t Nb, Double_t* b, Option_t* option){
    // compare two 1-dim variables of type Double_t and perform Kolomogorov test: are the sets of points  compatible with coming from the same parent distribution
    // experimental distributions of unbinned data
    // [https://root.cern.ch/root/htmldoc/TMath.html#TMath:KolmogorovTest]
    // option: "D" = debug , "M" = Maximum Kolmogorov distance instead of prob
    Sort(Na , a);
    Sort(Nb , b);
    return TMath::KolmogorovTest(Na , a , Nb , b , option);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
Double_t TAnalysis::Kolmogorov1DCriticalValue( Double_t alpha , int N1 , int N2 ){
    // [http://www.soest.hawaii.edu/wessel/courses/gg313/Critical_KS.pdf]
    // If one chooses a critical value of the test statistic Dα such that P(Dn > Dα) = α, then a band of width ±Dα around Fn(x) will entirely contain F(x) with probability 1 − α
    Double_t c_alpha;
    if      (alpha == 0.1)
        c_alpha = 1.22;
    else if (alpha == 0.05)
        c_alpha = 1.36;
    else if (alpha == 0.025)
        c_alpha = 1.48;
    else if (alpha == 0.01)
        c_alpha = 1.63;
    else{
        Printf("alpha must be one of the following values: 0.1 , 0.05 , 0.025 , 0.01");
        return -1;
    }
    return (c_alpha*(sqrt((float)(N1+N2)/(N1*N2))));
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TAnalysis::Sort(Int_t Nv, Double_t* v){
    for (int i = 0; i < Nv; ++i)
        for (int j = i + 1; j < Nv; ++j)
            if ( v[i] > v[j] )
            {   Double_t a =  v[i];  v[i] = v[j];    v[j] = a;   }
}










//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
Double_t TAnalysis::IntegralH2D(TH2F * h, Double_t Xlow, Double_t Ylow, Double_t Xup, Double_t Yup, bool DoDrawBox, int color){
    // integrate [Xlow,Ylow]->[Xup,Yup]
    int binX , binY;
    float integral = 0;
    for (binX = h -> GetXaxis() -> FindBin(Xlow) ; binX < h -> GetXaxis() -> FindBin(Xup); binX++) {
        for (binY = h -> GetYaxis() -> FindBin(Ylow) ; binY < h -> GetYaxis() -> FindBin(Yup); binY++) {
            integral += h -> GetBinContent(binX,binY);
        }
    }
    if (DoDrawBox){
        Printf("∫%s(%.1f,%.1f)->(%.1f,%.1f)=%.1f",h->GetName(),Xlow ,Ylow,Xup,Yup,integral);
        plot.Box(Xlow ,Ylow,Xup,Yup,color,0.3);
    }
    
    return integral;
}




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
Double_t TAnalysis::IntegralH1D(TH1F * h, Double_t Xlow, Double_t Xup){ // integrate [Xlow -> Xup]
    float integral = h -> Integral(h -> GetXaxis() -> FindBin(Xlow),h -> GetXaxis() -> FindBin(Xup) );
    return integral;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
Double_t TAnalysis::TH1Frac(TH1F * histo , Double_t Xlow, Double_t Xup){
    return IntegralH1D(histo, Xlow, Xup)/histo->Integral();
}






//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TH1F* TAnalysis::RatioOfHistograms(TString name, TH1F * hNum, TH1F * hDen,TString Title,TString XTitle, int color){
    TH1F * hRatio = new TH1F(name,Title
                             ,hNum->GetNbinsX(),hNum->GetXaxis()->GetBinCenter(1),hNum->GetXaxis()->GetBinCenter(hNum->GetNbinsX()+1));
    for (int binX = 1 ; binX < hNum->GetNbinsX()+1 ; binX++ ){
        if ( ! hDen->GetBinContent(binX) )
            hRatio -> SetBinContent( binX , 0 );
        else if ((float)hDen->GetBinContent(binX)/hNum->GetBinContent(binX) < 0.01)
            hRatio -> SetBinContent( binX , 0 );
        else if ((float)hDen->GetBinContent(binX)/hNum->GetBinContent(binX) < 0.1)
            hRatio -> SetBinContent( binX , 100 );
        else
            hRatio -> SetBinContent( binX , 100.*((float)hNum->GetBinContent(binX) / hDen->GetBinContent(binX)));
    }
    //    TPlots::SetFrame(hRatio,Title,XTitle,"ratio [%]", color , color );
    return hRatio;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TAnalysis::PlotHRefAndHRatios(TString name, TH1F * hRef, int colorRef, const int Nratios, TH1F * h[Nratios] , TString Title , TString XTitle, int colors[Nratios] ){
    float Maximum = 100 ,   Minimum = 100;
    for (int i = 0; i < Nratios ; i++ ){
        h[i] = RatioOfHistograms(Form("%sratio%d",name.Data(),i), h[i] , hRef , Title , XTitle, colors[i]);
        if (h[i]->GetMaximum() > Maximum)
            Maximum = h[i]->GetMaximum();
        if (Minimum > h[i]->GetMinimum())
            Minimum = h[i]->GetMinimum();
    }
    hRef = RatioOfHistograms(Form("%sreference",name.Data()), hRef , hRef , Title , XTitle, colorRef);
    hRef -> GetYaxis() -> SetRangeUser(0.9*Minimum,1.1*Maximum);
    hRef -> Draw();
    for (int i = 0; i < Nratios ; i++ )
        h[i] -> Draw("same");
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TH1F* TAnalysis::CombineHistograms(char * name, TH1F * hNum, TH1F * hDen,TString Title,TString XTitle, int color){
    TH1F * hCombined = new TH1F(name,Title
                                ,hNum->GetNbinsX(),hNum->GetXaxis()->GetBinCenter(1),hNum->GetXaxis()->GetBinCenter(hNum->GetNbinsX()+1));
    for (int binX = 1 ; binX < hNum->GetNbinsX()+1 ; binX++ ){
        hCombined -> SetBinContent( binX , hNum->GetBinContent(binX) + hDen->GetBinContent(binX) );
    }
    //    TPlots::SetFrame(hCombined,Title,XTitle,"counts", color , color );
    return hCombined;
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TH1F * TAnalysis::GetHistoFromAFile(TString filename , TString histoname){
    TFile * File = new TFile(filename);
    TH1F* histo =  (TH1F*)File->Get(histoname);
    return histo;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TH2F * TAnalysis::GetH2FromAFile(TString filename , TString histoname){
    cout << "opening" << filename << ", to get " << histoname << endl;
    TFile * File = new TFile(filename);
    TH2F* histo =  (TH2F*)File->Get(histoname);
    return histo;
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TProfile * TAnalysis::GetProfileFromFile(TString filename , TString profilename){
    cout << "opening" << filename << ", to get " << profilename << endl;
    TFile     * File = new TFile(filename);
    TProfile  * prof = (TProfile*)File->Get(profilename);
    return prof;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TAnalysis::NormalizeHistogram(TH1F * h){
    h -> Scale (1./h->Integral());
}


// signal to noise
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
float TAnalysis::GetS2N(TH1 * hSignal, TH1 * hNoise){
    return hSignal->Integral() / hNoise->Integral();
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
double TAnalysis::GetFWHM(TH1 * h){
    
    int bin1    = h->FindFirstBinAbove(h->GetMaximum()/2);
    Float_t X1  = h->GetBinCenter(bin1 - 10);
    int bin2 = h->FindLastBinAbove(h->GetMaximum()/2);
    Float_t X2  = h->GetBinCenter(bin2 + 10);
    TF1* fGaus = new TF1(Form("f%s",h->GetName()),"gaus",X1,X2);
    h -> Fit(fGaus,"","SAME",X1 , X2);
    fGaus -> SetLineColor(h->GetLineColor());
    fGaus -> Draw("same");
    Float_t sigma   = fGaus -> GetParameter(2);
    Float_t FWHM    = 2. * sqrt( 2. * log (2.) ) * sigma;
    return FWHM;
//    plot.Line(X1 ,h->GetMaximum()/2. , X2 , h->GetMaximum()/2. ,2 , 2 );
//    return ( X2 - X1 );
    
    
    
    
}





// signal on background (2d) - last editted March 24
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
RooRealVar TAnalysis::SubtractBackground(TH2F * h, float aSig, float axBkg , bool DoPlot){
    // reutrns "real" events - the signal inside an [aSig x aSig] size box
    float ayBkg     = aSig;
    float VSig      = aSig * aSig   ,   VBkg    = axBkg * ayBkg;

    float Peak      = IntegralH2D(h, -aSig/2.       , -aSig/2.          ,  aSig/2.          ,  aSig/2.      , DoPlot , 4)
    , PeakErr    = sqrt(Peak);
    
    float BkgLeft   = IntegralH2D(h, -axBkg-aSig/2. , -ayBkg/2.         , -aSig/2.          ,  ayBkg/2.     , DoPlot , 1)
    , BkgLeftErr = sqrt(BkgLeft);
    
    float BkgBottom = IntegralH2D(h, -aSig/2.       , -axBkg-aSig/2.    ,  aSig/2.          , -aSig/2.      , DoPlot , 1)
    , BkgBottomErr = sqrt(BkgBottom);
    
    float BkgRight  = IntegralH2D(h,  aSig/2.       , -ayBkg/2.         ,  axBkg+aSig/2.    ,  ayBkg/2.     , DoPlot , 1)
    , BkgRightErr= sqrt(BkgRight);
    
    float BkgTop    = IntegralH2D(h, -aSig/2.       ,  aSig/2.          ,  aSig/2.          ,  axBkg+aSig/2., DoPlot , 1)
    , BkgTopErr  = sqrt(BkgTop);
    
    float BkgAvg    = (BkgLeft + BkgBottom + BkgRight + BkgTop) / 4.
    , BkgAvgErr = sqrt(BkgLeftErr*BkgLeftErr + BkgBottomErr*BkgBottomErr + BkgRightErr*BkgRightErr + BkgTopErr*BkgTopErr) / 4. ;
    
    float Bkg       = BkgAvg    * ( VSig / VBkg );
    float BkgErr    = BkgAvgErr * ( VSig / VBkg );
    
    if(DoPlot) {
        plot.Text(-15 , 14, Form("Peak: %.1f  #pm  %.1f",Peak   ,PeakErr),2);
        plot.Text(-15 , 12, Form("Bkgd: %.1f  #pm  %.1f",Bkg    ,BkgErr) ,1);
    }
    Printf("average background %.1f ± %.1f in (%.0fx%.0f) box, and %.1f ± %.1f in (%.0fx%.0f) box"
           , BkgAvg,BkgAvgErr,aSig,axBkg,Bkg,BkgErr,aSig,aSig);
    
    Printf("BkgLeft - BkgAvg = %.1f ± %.1f"     , BkgLeft-BkgAvg , sqrt(BkgLeftErr*BkgLeftErr + BkgAvgErr*BkgAvgErr));
    Printf("BkgBottom - BkgAvg = %.1f ± %.1f"   , BkgBottom-BkgAvg , sqrt(BkgBottomErr*BkgBottomErr + BkgAvgErr*BkgAvgErr));
    Printf("BkgRight - BkgAvg = %.1f ± %.1f"    , BkgRight-BkgAvg , sqrt(BkgRightErr*BkgRightErr + BkgAvgErr*BkgAvgErr));
    Printf("BkgTop - BkgAvg = %.1f ± %.1f"      , BkgTop-BkgAvg , sqrt(BkgTopErr*BkgTopErr + BkgAvgErr*BkgAvgErr));
    
    RooRealVar signal("signal","signal", Peak - Bkg , -1e5 , 1e5 , "");
    signal.setError(sqrt(PeakErr*PeakErr + BkgErr*BkgErr));
    return signal;


}







//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TH1F* TAnalysis::GetPartOfHistogram(char * name, TH1F * h, double Xlow, double Xup){
    TH1F * hPart = new TH1F(name,name,h->GetNbinsX(),h->GetXaxis()->GetBinCenter(1),h->GetXaxis()->GetBinCenter(h->GetNbinsX()+1));
    for (int binX = h -> GetXaxis() -> FindBin(Xlow) ; binX < h -> GetXaxis() -> FindBin(Xup); binX++) {
        hPart -> SetBinContent(binX,h -> GetBinContent(binX));
    }
    return hPart;
}











//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TAnalysis::PlotGraphDataToFile(TString FileName,const int N,double X[N],double Xerr[N],double Y[N],double Yerr[N]){
    ofstream OutFile;
    OutFile.open(FileName);
    for (int i = 0; i < N; i++)
    OutFile << X[i] << " " << Xerr[i] << " " << Y[i] << " " << Yerr[i] << std::endl;
    OutFile.close();
}




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TAnalysis::ReadGraphDataFromFile(TString FileName,const int N,double X[N],double Xerr[N],double Y[N],double Yerr[N]){
    ifstream InFile;
    InFile.open(FileName);
    for (int i = 0; i < N; i++){
        InFile >> X[i] >> Xerr[i] >> Y[i] >> Yerr[i];
    }
    InFile.close();
}




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void TAnalysis::ReadGraphFromFile(TString FileName,const int N,double X[N],double Y[N]){
    ifstream InFile;
    InFile.open(FileName);
    cout << "reading "<< FileName << endl;
    for (int i = 0; i < N; i++){
        InFile >> X[i] >>  Y[i] ;
        //        Printf("point %i: (%.3f , %.3f)",i,X[i],Y[i]);
    }
    InFile.close();
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TGraph * TAnalysis::ReadGraphFromFile(TString FileName,const int N){
    double X[N], Y[N];
    ReadGraphFromFile(FileName, N , X ,  Y );
    TGraph * g = new TGraph( N , X , Y  );
    return g;
}






//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TH2F* TAnalysis::Assymetry(TTree * Tree , TString vZ
                           , TString vX , int NbinsX , Float_t XMin, Float_t XMax
                           , TString vY , int NbinsY , Float_t YMin, Float_t YMax
                           , TString Weight
                           , bool DoPrint ){
    // read all entries from the variable "var" and bin them in NbinsX of vX and NbinsY of vY
    Printf("For VariableIn2DBins, the branches type must be Double_t...");
    TH2F * h2 = new TH2F(vZ+"_binnedin_"+vX+"_and_"+vY,vZ+" binned in "+vX+" and "+vY,NbinsX,XMin,XMax,NbinsY,YMin,YMax);
    TH2F * Nforw = new TH2F("Nforw","Nforw",NbinsX,XMin,XMax,NbinsY,YMin,YMax);
    TH2F * NBack = new TH2F("NBack","NBack",NbinsX,XMin,XMax,NbinsY,YMin,YMax);
    
    TLorentzVector *X = 0 , *Y = 0 , *Z = 0;
    Double_t weight;
//    Tree -> SetBranchAddress( vX , &X );
    Tree -> SetBranchAddress( vY , &Y );
    Tree -> SetBranchAddress( vZ , &Z );
    Tree -> SetBranchAddress( Weight , &weight );
    
    for (int i = 0 ; i < Tree -> GetEntries() ; i++ ) {
        Tree -> GetEntry(i);
        if(DoPrint) Printf(" n.Pz() = %f", Z->Pz());
        if ( Z->Pz() > 0) {
            Nforw -> Fill( Z->P() , Y->E() , weight ); // change this for special usage or FIXME - make it modular
            if(DoPrint) printf("filling Nforw");
        }
        else {
            NBack -> Fill( Z->P() , Y->E() , weight );
            if(DoPrint) printf("filling NBack");
        }
        if(DoPrint) Printf(" in binx=%d ,biny=%d with weight %f "
               ,NBack -> GetXaxis() -> FindBin(Z->P()) , NBack -> GetYaxis() -> FindBin(Y->E()),weight);
        
    }
    
    for (int binX = 1;binX < NbinsX ; binX++ ) {
        for (int binY = 1 ;binY < NbinsY ; binY++ ) {
            h2 -> SetBinContent( binX , binY
                                , (NBack->GetBinContent( binX , binY ) - Nforw->GetBinContent( binX , binY ))
                                / (NBack->GetBinContent( binX , binY ) + Nforw->GetBinContent( binX , binY )));
        }
    }
    delete Nforw;
    delete NBack;
    
    return h2;
}




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//----------- unbinned RooFit of 1d Gaussian ----------------------//
RooPlot * TAnalysis::RooFit1D( TTree * Tree , TString name , TCut cut , Double_t Par[2] , Double_t ParErr[2], bool PlotFit ){
    
    // Par are input initial parameters (Par[0]=mean,Par[1]=sigma) and are returned as the results
    
    RooRealVar  var     (name       ,name           ,0      ,-0.8       ,0.8       ) ;
    RooRealVar  fMean   ("mean"     ,"mean"         ,0      ,-0.8       ,0.8         ) ;
    RooRealVar  fSigma  ("sigma"    ,"sigma"        ,0.15   ,0          ,0.5         ) ;
    RooGaussian fGauss  ("gauss"    ,"gauss"        ,var    ,fMean      ,fSigma     ) ;
    
    RooPlot* frame = var.frame( Bins(50), Name(name.Data()) , Title(name)) ;
    TTree * ReducedTree = Tree -> CopyTree(cut);
    RooDataSet DataSet("DataSet","Data Set",RooArgSet(var),Import(*ReducedTree)) ;
    if(PlotFit) {
        DataSet.Print();
        DataSet.plotOn(frame) ;
    }
    fGauss.fitTo(DataSet) ;
    fGauss.plotOn(frame,LineColor(kRed)) ;
    Par[0]      = fMean.getValV();
    Par[1]      = fSigma.getValV();
    ParErr[0]   = fMean.getError();
    ParErr[1]   = fSigma.getError();

    if (PlotFit)    frame -> Draw();
    return frame;
}

