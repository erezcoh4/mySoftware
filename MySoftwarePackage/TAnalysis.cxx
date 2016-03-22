//  TAnalysis.cpp
//  Created by Erez Cohen on 5/15/15.
#include "TAnalysis.h"

using namespace RooFit ;
#define MAX 100000


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TAnalysis::TAnalysis(){    i_ana = 0;   }

//
////....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
////----------- unbinned RooFit of 1d Gaussian ----------------------//
//RooPlot * TAnalysis::RooFit1D( TTree * Tree , TString VarName , Double_t Xlim[2] , Double_t Par[2] , Double_t ParErr[2] , TString fTitle
//                              , bool PlotFit , bool DoWeight){
//    // Par are input initial parameters (Par[0]=mean,Par[1]=sigma) and are returned as the results
//    // To get Or' results:
//    RooRealVar variable (VarName.Data(),VarName.Data()  ,-1     ,1) ;
//    RooRealVar  fMean   ("mean"     ,"mean"     , 0             ,-0.5   ,0.8        ) ;
//    RooRealVar  fSigma  ("sigma"    ,"sigma"    , 0.16          , 0.0   ,0.7        ) ;
//    RooGaussian fGauss  ("gauss"    ,"gauss"    , variable      ,fMean  ,fSigma     ) ;
//    
//    // And something more robust:
//    //    RooRealVar  variable (VarName.Data(),VarName.Data()  ,Xlim[0]  ,Xlim[1]) ;
//    //    RooRealVar  fMean   ("mean"     ,"mean"     ,Par[0]         ,Xlim[0]    ,Xlim[1]        ) ;
//    //    RooRealVar  fSigma  ("sigma"    ,"sigma"    ,Par[1]         ,Xlim[0]    ,Xlim[1]        ) ;
//    //    RooGaussian fGauss  ("gauss"    ,"gauss"    ,variable       ,fMean      ,fSigma          ) ;
//    
//    RooPlot* frame = variable.frame(Bins(20), Name(VarName.Data()),Title(fTitle)) ;
//    
//    if (DoWeight){
//        Printf("Doing Weight!!");
//        RooRealVar fWeight   ("rooWeight","rooWeight"      , -100000      ,1000000 ) ;
//        RooArgSet VarSet(variable,fWeight);
//        RooDataSet DataSet("DataSet","Data Set",VarSet,Import(*Tree)) ;
//        DataSet.Print();
//        if (PlotFit)    DataSet.plotOn(frame) ;
//        fGauss.fitTo(DataSet) ;
//    } else {
//        RooArgSet VarSet(variable);
//        RooDataSet DataSet("DataSet","Data Set",VarSet,Import(*Tree)) ;
//        DataSet.Print();
//        if (PlotFit)    DataSet.plotOn(frame) ;
//        fGauss.fitTo(DataSet) ;
//    }
//    fGauss.plotOn(frame,LineColor(kRed)) ;
//    Par[0]      = fMean.getValV();
//    Par[1]      = fSigma.getValV();
//    ParErr[0]   = fMean.getError();
//    ParErr[1]   = fSigma.getError();
//    
//    if (PlotFit)    frame -> Draw();
//    return frame;
//}











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






#define NX 10
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
Double_t TAnalysis::EnergyTestHisto2D(Int_t Nx, Int_t Ny, TH2F* histoA, TH2F* histoB){
    // compare two 2-dim histograms using the energy test - return the test statistic ø
    // [https://indico.cern.ch/event/93877/session/14/contribution/56/attachments/1104144/1575267/epaper_final_26Apr2012.pdf]
    // NxN binning, ranged from 0 to 1 in X and Y axes
    // Definitions
    double  phiA=0.     , phiB=0.   , phiAB=0.;
    const int N     = (Nx + 2);       // underflow and overflow bins increase Nbins by 2 units
    double step     = 1./sqrt(Nx*Ny);
    double stepsq   = pow(step,2);
    double d00      = log(0.52140543316472*step);  //"square line picking" - avg. dist between 2 points
    double  hA[N][N]    , hB[N][N]  ,  dist[N][N];
    double *d0      = dist[0];
    double sumA     = 0., sumB = 0.;
    double *ntA , *ntB;
    // Initilization
    for (int i = 0; i < N; ++i){    // move to arrays instead of histogram to reduce expensive GetBinContent() calculation time
        for (int j = 0; j < N; ++j) {
            hA[i][j] = histoA -> GetBinContent(i,j);
            sumA    += hA[i][j];
            hB[i][j] = histoB -> GetBinContent(i,j);
            sumB    += hB[i][j];
        }
        if (i < N){
            d0[i] = (i==0) ? d00 : log(i*step);  //manually take sqrt()...
            for (int j = 0; j < N; ++j){
                dist[i][j] = ( j < i ) ? dist[j][i] : (log((i*i+j*j)*stepsq)/2.0) ;
            }
        }
    }
    // calculation of energy components
    for (int i = 0; i < N ; ++i){  // hA(i,j) vs. hB(k,l)
        for (int j = 0; j < N ; ++j){
            double  nA = hA[i][j] , nB = hB[i][j] , Apart=0. , Bpart=0. , *pl=0;
            if ( (nA !=0.) || (nB != 0.) ){  //skip empty cells
                for (int k = 0 ; k < i; ++k){  // k < i
                    double  *px = dist[i-k] + j + 1;
                    for ( int l = 0 ; l < N ; ++l ){ // calculate for l <= j seperatly from l > j
                        double temp1 = (l <= j) ? (*(--px)) : (*(++px));
                        Apart  += hA[k][l] * temp1;
                        Bpart  += hB[k][l] * temp1;
                    }
                }
                ntA = hA[i];
                ntB = hB[i];
                pl = d0 + j;
                for ( int l = 0; l < j; ++l,--pl,++ntA,++ntB){  // k==i, l<j
                    double temp1 = *pl;
                    Apart  += hA[i][l] * temp1;
                    Bpart  += hB[i][l] * temp1;
                }
                phiA  += nA * (Apart + 0.5*nA*d00); // k==i, l==j
                phiB  += nB * (Bpart + 0.5*nB*d00); //should really be n(n-1)/2
            }
            if (nA != 0){  //... then previous section must have run
                for (int ll = j+1 ; ll < N ; ++ll){
                    Bpart += (*(++ntB)) * (*(++pl));} //k==i, l > j
                for (int k = i+1; k < N ; ++k){ // k > i
                    double* px  = dist[k-i] + j;
                    double* hBx = hB[k];
                    int     l   = 0;
                    for (; l <= j; ++l,++hBx,--px)  // l <= j
                        Bpart += (*hBx) * (*px);
                    for (++px; l < N ; ++l,++hBx) // l > j
                        Bpart += (*hBx) * (*(++px));
                }
                phiAB += nA * (Bpart + nB*d00);
            }
        }
    }
    // normalization
    phiA  *= -1./(sumA*sumA);
    phiB  *= -1./(sumB*sumB);
    phiAB *= 1./(sumA*sumB);
    Printf("phiA = %g, phiB = %g, phiAB = %g",phiA,phiB,phiAB);
    return ( phiA + phiB + phiAB );
}







//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
Double_t TAnalysis::EnergyTestUnbinned3D(std::vector<TVector3> Xd, std::vector<TVector3> Xmc){
    // conduct the unbinned energy test for 3-dim data using the log weighting function
    // to compare a vector-set of Xd to a vector-set of Xmc, both of TVector3 type
    double phi_d = 0. , phi_mc = 0. , phi_dmc = 0.;
    for ( size_t i = 0 ; i < Xmc.size() ; i ++ ){// unify the loops to only one - always N(MC) > N(D)
        for ( size_t j = i + 1 ; j < Xmc.size() ; j ++ ){
            if (i < Xd.size()) {
                phi_dmc += -log( (Xd.at(i) - Xmc.at(j)).Mag() + 0.75 );
                if (j < Xd.size()){
                    phi_d += -log( (Xd.at(i) - Xd.at(j)).Mag() + 0.75 );
                }
            }
            phi_mc += -log( (Xmc.at(i) - Xmc.at(j)).Mag() + 0.75 );
            //            Printf("i = %d, j = %d",i,j);
        }
    }
    return ( phi_d/(Xd.size()*Xd.size()) + phi_mc/(Xmc.size()*Xmc.size()) - phi_dmc/(Xd.size()*Xmc.size()) );
    //    float phiDD = 0 , phiMCMC = 0 , phiDMC = 0 , phi = 0;
    //    int ND  = TD -> GetEntries() , NMC = TMC-> GetEntries();
    //    TMatrix r2DD(ND , ND) , r2MCMC(NMC , NMC)  , r2DMC(ND , NMC) , PsiDD(ND , ND) , PsiMCMC(NMC , NMC) , PsiDMC(ND , NMC);
    //    for ( int i = 0 ; i < MC.size() ; i++ ){
    //        for ( int j = i+1 ; j < MC.size() ; j++ ){
    //            r2MCMC(i,j) = (MC.at(i) - MC.at(j)).Mag2();
    //            PsiMCMC(i,j) = -0.5*log(r2MCMC(i,j) + 0.01/(MC.size()*MC.size()) );
    //            phiMCMC += PsiMCMC(i,j);
    //        }
    //    }
    //    for ( int i = 0 ; i < D.size() ; i++ ){
    //        for ( int j = i+1 ; j < D.size() ; j++ ){
    //            r2DD(i,j) = (D.at(i) - D.at(j)).Mag2();
    ////            PsiDD(i,j) = 1/r2DD(i,j);
    //            PsiDD(i,j) = -0.5*log(r2DD(i,j) + 0.01/(D.size()*D.size()) );
    ////            float si = sBar;///hData->Interpolate(D.at(i).x() , D.at(i).y(), D.at(i).z());
    ////            float sj = sBar;///hData->Interpolate(D.at(j).x() , D.at(j).y(), D.at(j).z());
    ////            PsiDD(i,j) = exp(-r2DD(i,j)/(2.*si*sj));
    //            phiDD += PsiDD(i,j);
    //        }
    //    }
    //    for ( int i = 0 ; i < D.size() ; i++ ){
    //        for ( int j = 0 ; j < MC.size() ; j++ ){
    //            r2DMC(i,j) = (D.at(i) - MC.at(j)).Mag2();
    ////            PsiDMC(i,j) = 1/r2DMC(i,j);
    //            PsiDMC(i,j) = -0.5*log(r2DMC(i,j) + 0.01/(MC.size()*D.size()) );
    ////            float si  = sBar;///hData->Interpolate(D.at(i).x() , D.at(i).y() , D.at(i).z());
    ////            float sj = sBar;///hMC->Interpolate(MC.at(j).x() , MC.at(j).y() , MC.at(j).z());
    ////            PsiDMC(i,j) = exp(-r2DMC(i,j)/(2.*si*sj));
    //            phiDMC += PsiDMC(i,j);
    //        }
    //    }
    //    phi = phiDD/(ND*ND) + phiMCMC/(NMC*NMC) - phiDMC/(ND*NMC);
}






//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// speed the calculation using c++ arrays of the "distances" between points
Double_t TAnalysis::EnergyTestUnbinned3D(int ND, int NMC, float**rDD, float**rMCMC, float**rDMC){
    double phi_d = 0. , phi_mc = 0. , phi_dmc = 0.;
    for ( int i = 0 ; i < NMC ; i ++ ){// unify the loops to only one - always N(MC) > N(D)
        for ( int j = i + 1 ; j < NMC ; j ++ ){
            if (i < ND) {
                phi_dmc += -log( rDMC[i][j] + 0.75 );
                if (j < ND)
                    phi_d += -log( rDD[i][j] + 0.75 );
            }
            phi_mc += -log( rMCMC[i][j] + 0.75 );
            //            Printf("i = %d, j = %d",i,j);
        }
    }
    return ( phi_d/(ND*ND) + phi_mc/(NMC*NMC) - phi_dmc/(ND*NMC) );
}




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
Double_t TAnalysis::WeightingFunc(Double_t r, int func ){
    // a weighting function for the energy test, which is a function of a cartezian distance r
    switch (func) {
        case 1: // -log
            return ( -log( r + 0.75 ) ); //cutoff - minimal dist between 2 points, should be ~ the measurement resolution
            break;
        case 2: // 1/r
            return (1./r);
            break;
        case 3: // gaussian
            return (exp(-(r*r)/(0.0002)));    // sigma is ~ the measurement resolution 5 MeV, so 2x(sigma^2) = 0.0005
            break;
        default:
            Printf("No function specified...");
            break;
    }
    return -100;
}








//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
float TAnalysis::ppCMEnergyTest( char * name, TTree* TD , TTree * TMC, bool DrawHistos){
    int Nbins = 30 ;// , N = Nbins+2;
    TH3F * hD       = new TH3F(Form("hD%s",name),Form("D(%s)",name),Nbins,0,1,Nbins,0,1,Nbins,0,1);
    TH3F * hMC      = new TH3F(Form("hMC%s",name),Form("hMC(%s)",name),Nbins,0,1,Nbins,0,1,Nbins,0,1);
    TH2F * hD2      = new TH2F(Form("hD2%s",name),Form("D(%s)",name),Nbins,0,1,Nbins,0,1);
    TH2F * hMC2     = new TH2F(Form("hMC2%s",name),Form("MC(%s)",name),Nbins,0,1,Nbins,0,1);
    TD  -> Draw(Form("Pmiss.Mag():(Pcm_in_Pmiss_q_system.z()+0.5):Pcm_in_Pmiss_q_system.Pt() >> hD%s",name),"","goff");
    TMC -> Draw(Form("Pmiss.Mag():(Pcm_in_Pmiss_q_system.z()+0.5):Pcm_in_Pmiss_q_system.Pt() >> hMC%s",name),"","goff");
    //    TD  -> Draw(Form("Pmiss.Mag():(Pcm_in_Pmiss_q_system.z()+0.5) >> hD2%s",name),"",(DrawHistos) ? "" : "goff");
    //    TMC -> Draw(Form("Pmiss.Mag():(Pcm_in_Pmiss_q_system.z()+0.5) >> hMC2%s",name),"",(DrawHistos) ? "col same" : "goff");
    //    float phi = EnergyTestHisto2D(Nbins, Nbins, hD2, hMC2);
    float phi = ETestHisto3D(hD, hMC);
    Printf("ø (%s) = %g",name,phi);
    if(!DrawHistos){
        delete hD2;
        delete hMC2;
        delete hD;
        delete hMC;
    }
    return phi;
    //    std::vector<TVector3> D , MC;    // vector axes are p(c.m.)T-p(c.m.)L-|p(miss)|
    //    TVector3 * PcmD = 0 , * PmissD = 0 , * PcmMC = 0 , * PmissMC = 0 ;
    //    TD  -> SetBranchAddress("Pcm_in_Pmiss_q_system"   ,&PcmD);
    //    TD  -> SetBranchAddress("Pmiss" ,&PmissD);
    //    TMC -> SetBranchAddress("Pcm_in_Pmiss_q_system"   ,&PcmMC);
    //    TMC -> SetBranchAddress("Pmiss" ,&PmissMC);
    //    for ( int i = 0 ; i < ND ; i++ ){
    //        TD -> GetEntry(i);
    //        if(PcmD->Pt()<2 && fabs(PcmD->Z())<2 && PmissD->Mag()<1.1) {
    //            D.push_back(TVector3(PcmD->Pt(),PcmD->Z(),PmissD->Mag()));
    //        }
    //    }
    //    for ( int i = 0 ; i < NMC ; i++ ){
    //        TMC -> GetEntry(i);
    //        if(PcmMC->Pt()<2 && fabs(PcmMC->Z())<2 && PmissMC->Mag()<1.1) {
    //            MC.push_back(TVector3(PcmMC->Pt(),PcmMC->Z(),PmissMC->Mag()));
    //        }
    //    }
    //    phi = EnergyTestUnbinned3D(std::vector<TVector3> Xd, std::vector<TVector3> Xmc, int func)
}






//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
float TAnalysis::stdev(std::vector<float> v){
    double m =  std::accumulate(v.begin(), v.end(), 0.0) / v.size() , accum = 0.0;
    for (size_t i = 0; i < v.size(); i++)
        accum += (v.at(i) - m) * (v.at(i) - m);
    return sqrt(accum / (v.size()-1));
}







//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
Double_t TAnalysis::ETestHisto3D(TH3F* hD, TH3F* hMC/*, const int Nx*/){
    // compare two 3d histograms using the energy test - return the test statistic ø
    // NxNxN binning
    // Definitions
    const int N     = 32; // N = Nbins+2
    double  phiD    = 0.    , phiMC=0.      , phiDMC=0.;
    double step     = 1./(N-2);
    double stepsq   = pow(step,2);
    double d000     = log(0.66170*step);                //"cube line picking" - avg. dist between 2 points
    double D[N][N][N]       , MC[N][N][N]   ,  psi[N][N][N];
    double nD       = 0.    , nMC = 0.;
    
    // Initilization
    for (int i1 = 0; i1 < N; i1++){    // move to arrays instead of histogram to reduce expensive GetBinContent() calculation time
        for (int i2 = 0; i2 < N; i2++) {
            for (int i3 = 0; i3 < N; i3++) {
                D[i1][i2][i3] = hD->GetBinContent(i1,i2,i3);
                nD    += D[i1][i2][i3];
                MC[i1][i2][i3] = hMC -> GetBinContent(i1,i2,i3);
                nMC   += MC[i1][i2][i3];
                psi[i1][i2][i3] = (i1==0 && i2==0 && i3==0) ? d000 : 0.5*log((i1*i1 + i2*i2 + i3*i3)*stepsq) ;
            }
        }
    }
    double Dpart = 0,  MCpart = 0, DMCpart = 0;
    
    for (int i1 = 0; i1 < N; i1++){
        for (int i2 = 0; i2 < N; i2++) {
            for (int i3 = 0; i3 < N; i3++) {
                double nDi = D[i1][i2][i3], nMCi = MC[i1][i2][i3];
                if (nDi!=0 || nMCi!=0) { // skip empty cells
                    
                    Dpart   += 0.5*nDi*nDi*psi[0][0][0];
                    MCpart  += 0.5*nMCi*nMCi*psi[0][0][0];
                    
                    for (int j3 = 0; j3 < N; j3++){
                        if((j3 < i3) && (D[i1][i2][j3]!=0 || MC[i1][i2][j3]!=0)){
                            Dpart   += nDi*D[i1][i2][j3]*psi[0][0][i3-j3];
                            MCpart  += nMCi*MC[i1][i2][j3]*psi[0][0][i3-j3];
                        }
                        for (int j2 = 0; j2 < N; j2++){
                            if( (j2 < i2) && (D[i1][j2][j3]!=0 || MC[i1][j2][j3]!=0)){
                                Dpart   += nDi*D[i1][j2][j3]*psi[0][i2-j2][abs(i3-j3)];
                                MCpart  += nMCi*MC[i1][j2][j3]*psi[0][i2-j2][abs(i3-j3)];
                            }
                            for (int j1 = 0; j1 < N; j1++){
                                if (D[j1][j2][j3]!=0 || MC[j1][j2][j3]!=0) {
                                    if((j1 < i1) ){
                                        Dpart   += nDi*D[j1][j2][j3]*psi[i1-j1][abs(i2-j2)][abs(i3-j3)];
                                        MCpart  += nMCi*MC[j1][j2][j3]*psi[i1-j1][abs(i2-j2)][abs(i3-j3)];
                                    }
                                    DMCpart += nDi*MC[j1][j2][j3]*psi[abs(i1-j1)][abs(i2-j2)][abs(i3-j3)];
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    // normalization
    phiD    = -Dpart  /(nD  * nD);
    phiMC   = -MCpart /(nMC * nMC);
    phiDMC  = DMCpart /(nD  * nMC);
    //    Printf("ø(D) = %f, ø(MC) = %f, ø(D-MC) = %f",phiD,phiMC,phiDMC);
    return ( phiD + phiMC + phiDMC );
}










//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
Double_t TAnalysis::IntegralH2D(TH2F * h, Double_t Xlow, Double_t Ylow, Double_t Xup, Double_t Yup, bool DoDrawBox){
    // integrate [Xlow,Ylow]->[Xup,Yup]
    int binX , binY;
    float integral = 0;
    for (binX = h -> GetXaxis() -> FindBin(Xlow) ; binX < h -> GetXaxis() -> FindBin(Xup); binX++) {
        for (binY = h -> GetYaxis() -> FindBin(Ylow) ; binY < h -> GetYaxis() -> FindBin(Yup); binY++) {
            integral += h -> GetBinContent(binX,binY);
        }
    }
    if (DoDrawBox){
        Printf("∫(%.1f,%.1f)->(%.1f,%.1f)=%.1f",Xlow ,Ylow,Xup,Yup,integral);
        //        TPlots::Box(Xlow ,Ylow,Xup,Yup,1,0.1);
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
TH1F * TAnalysis::GetHistoFromAFile(char * filename , char * histoname){
    TFile * File = new TFile(filename);
    return (TH1F*)File->Get(histoname);
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





// signal on background (2d)
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
double * TAnalysis::SubtractBackground(TH2F * h2, double a, float Bkg2SigBox, float x0, float y0){
    SHOW(a);
    // reutrns Nrealevents and NrealErr, where "real" events are the signal inside an a-side size ....
//    float N             = h2 -> Integral();
    float Nsignal       = IntegralH2D(h2,x0-a/2     ,y0-a/2     ,x0+a/2     ,y0+a/2     , true);
    float Nbackground   = 0;
    Nbackground        += IntegralH2D(h2,x0-(Bkg2SigBox+2)*a/2  ,y0-Bkg2SigBox*a/2      ,x0-Bkg2SigBox*a/2      ,y0+Bkg2SigBox*a/2      , true);
    Nbackground        += IntegralH2D(h2,x0-Bkg2SigBox*a/2      ,y0-(Bkg2SigBox+2)*a/2  ,x0+Bkg2SigBox*a/2      ,y0-Bkg2SigBox*a/2      , true);
    Nbackground        += IntegralH2D(h2,x0+Bkg2SigBox*a/2      ,y0-Bkg2SigBox*a/2      ,x0+(Bkg2SigBox+2)*a/2  ,y0+Bkg2SigBox*a/2      , true);
    Nbackground        += IntegralH2D(h2,x0-Bkg2SigBox*a/2      ,y0+Bkg2SigBox*a/2      ,x0+Bkg2SigBox*a/2      ,y0+(Bkg2SigBox+2)*a/2  , true);
    double NReal        = Nsignal - (float)Nbackground/(4*Bkg2SigBox);
    double NRealErr     = sqrt(Nsignal + (float)Nbackground/(4*Bkg2SigBox));
    double NRealEvents[2] = {NReal , NRealErr};
    //    TPlots::Text( x0-7*a/2 , 1.*(y0+6*a/2) , Form("Signal = %.0f+/-%.0f",Nsignal,sqrt(Nsignal)) );
    //    TPlots::Text( x0-7*a/2 , 0.8*(y0+6*a/2) , Form("Background = %.0f+/-%.0f",Nbackground,sqrt(Nbackground)) );
    //    TPlots::Text( x0-7*a/2 , 0.6*(y0+6*a/2) , Form("Real events = %.0f+/-%.0f",NReal,NRealErr) );
    return NRealEvents;
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

